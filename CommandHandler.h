#pragma once

class CommandHandler
{
private:
	string arg;
	static const int size = 6;
	const string commands[size] = { "add", "out", "delete", "save", "help" , "close" };
	
public:
	CommandHandler();

	CommandHandler(string _arg);

	CommandHandler(const CommandHandler& other);

	~CommandHandler();

	static bool enterCommand(vector<Record>& vectorRecord, string path);

private:
	void setCommand(string _arg);

	int whatCommand(string& command, string& param);
};

int toInt(string str);

void readFile(vector<Record>& vectorRecord, string path);

void writeToFile(vector<Record>& vectorRecord, string path);


void cmdAdd(vector<Record>& vectorRecord);

void cmdAdd(vector<Record>& vectorRecord, string param);

void cmdOut(vector<Record>& vectorRecord);

void cmdOut(vector<Record>& vectorRecord, string param);

void cmdDelete(vector<Record>& vectorRecord);

void cmdDelete(vector<Record>& vectorRecord, string param);

void cmdHelp();

void cmdSave(vector<Record>& vectorRecord, string path);
