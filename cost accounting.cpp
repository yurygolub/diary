#include "pch.h"

int main()
{
    setlocale(LC_ALL, "ru");
    string path = "database.txt";
    vector<Record> vectorRecord;
    
    readFile(vectorRecord, path);

    while (true)
    {
        cout << "Введите команду : ";
        if (CommandHandler::enterCommand(vectorRecord, path)) break;
    }

}

