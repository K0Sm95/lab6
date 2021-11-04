#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h"


int main(int argc, char** argv)
{
    sqlite3* dataBase;
    sqlite3_stmt *statement;
    std::string sqlQuery = "CREATE TABLE IF NOT EXISTS people("
                      "id INT PRIMARY KEY     NOT NULL, "
                      "lastname       TEXT    NOT NULL, "
                      "residence      TEXT    NOT NULL, "
                      "birthyear      INT     NOT NULL);";
    int dbHandleQuery = 0;
    dbHandleQuery = sqlite3_open("newDavidBoopoiooi.db", &dataBase);
    if (dbHandleQuery = sqlite3_prepare_v2(dataBase, sqlQuery.c_str(), sqlQuery.size(), &statement, NULL) != SQLITE_OK) 
    {
        std::cerr << "Error: " << sqlite3_errmsg(dataBase) << std::endl;
        return -1;
    }
    if (sqlite3_step(statement) != SQLITE_DONE) 
    {
        std::cerr << "Error: " << sqlite3_errmsg(dataBase) << std::endl;
        return -1;
    }
    std::cout << "Table loaded successfully!" << std::endl;
    sqlite3_reset(statement);

    std::vector<std::string> sqlInsert = {"INSERT OR IGNORE INTO people(id, lastname, residence, birthyear) VALUES(1, 'Bender', 'Russia', 1990);",
               "INSERT OR IGNORE INTO people(id, lastname, residence, birthyear) VALUES(2, 'Panikovskiy', 'Belarus', 1987);",
               "INSERT OR IGNORE INTO people(id, lastname, residence, birthyear) VALUES(3, 'Balaganov', 'Ukraine', 1973);",
               "INSERT OR IGNORE INTO people(id, lastname, residence, birthyear) VALUES(4, 'Kozlevich', 'Russia', 1980);",
               "INSERT OR IGNORE INTO people(id, lastname, residence, birthyear) VALUES(5, 'Koreyko', 'Latvia', 1989);"};
    for (int i = 0; i < sqlInsert.size(); i++)
    {
        std::cout << "Checking registry #" << i << "..." << std::endl;
        if (dbHandleQuery = sqlite3_prepare_v2(dataBase, sqlInsert[i].c_str(), sqlInsert[i].size(), &statement, NULL) != SQLITE_OK) 
        {
            std::cerr << "Error: " << sqlite3_errmsg(dataBase) << std::endl;
            return -1;
        }
        if (sqlite3_step(statement) != SQLITE_DONE)
        {
            std::cerr << "Error: " << sqlite3_errmsg(dataBase) << std::endl;
            return -1;
        }
        sqlite3_reset(statement);
    }
    std::cout << "Registries checked successfully!" << std::endl;
    std::cout << std::endl;

    std::cout << "Printing all registries..." << std::endl;
    std::string sqlSelectAll = "SELECT * FROM people;";
    if (dbHandleQuery = sqlite3_prepare_v2(dataBase, sqlSelectAll.c_str(), sqlSelectAll.size(), &statement, NULL) != SQLITE_OK) 
    {
        std::cerr << "Error: " << sqlite3_errmsg(dataBase) << std::endl;
        return 0;
    }
    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(statement, 0);
        std::string lastname = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
        std::string residence = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
        int birthyear = sqlite3_column_int(statement, 3);

        std::cout  << id << ' ' << lastname << ' ' << residence << ' ' << birthyear << std::endl; 
    }
    std::cout << std::endl;
    sqlite3_reset(statement);

    std::cout << "Printing people from Russia in reverse order by lastname..." << std::endl;
    std::string sqlSelect = "SELECT lastname, birthyear FROM people WHERE residence = 'Russia' ORDER BY lastname DESC;";
    if (dbHandleQuery = sqlite3_prepare_v2(dataBase, sqlSelect.c_str(), sqlSelect.size(), &statement, NULL) != SQLITE_OK) 
    {
        std::cerr << "Error: " << sqlite3_errmsg(dataBase) << std::endl;
        return 0;
    }
    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        std::string lastname = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
        int birthyear = sqlite3_column_int(statement, 1);

        std::cout << lastname << ' ' << birthyear << std::endl; 
    }
    std::cout << std::endl;
    sqlite3_reset(statement);

    std::cout << "Printing average age of registries..." << std::endl;
    std::string sqlAvearge = "SELECT AVG(strftime('%Y','now')-birthyear) FROM people;";
    if (dbHandleQuery = sqlite3_prepare_v2(dataBase, sqlAvearge.c_str(), sqlAvearge.size(), &statement, NULL) != SQLITE_OK) 
    {
        std::cerr << "Error: " << sqlite3_errmsg(dataBase) << std::endl;
        return -1;
    }
    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        int avgAge = sqlite3_column_int(statement, 0);
        std::cout << "Average age is " << avgAge << '.' <<std::endl << std::endl;
    }
    sqlite3_reset(statement);

    sqlite3_finalize(statement);
    sqlite3_close(dataBase);
    
    return 0;
}