#include "pch.h"

CommandHandler::CommandHandler() : arg("")
{

}

CommandHandler::CommandHandler(string _arg) : arg(_arg)
{
	
}

CommandHandler::CommandHandler(const CommandHandler& other) : arg(other.arg)
{

}

CommandHandler::~CommandHandler()
{

}

void CommandHandler::setCommand(string _arg)
{
	arg = _arg;
}

int CommandHandler::whatCommand(string& command, string& param)
{
	if (arg.empty()) return -1;
	int index;

	for (index = 0; index < arg.size(); index++)
	{
		if (arg[index] == ' ')
		{
			if (index == 0) return -1;
			command.append(arg, 0, index);
			break;
		}
	}

	if (command.empty())
	{
		command = arg;
	}

	if (arg.size() != command.size())
	{
		param.append(arg, index + 1, arg.size() - 1);
	}

	for (int i = 0; i < size; i++)
	{
		if (command == commands[i])
		{
			return i;
		}
	}
	
	return -1;
}

bool CommandHandler::enterCommand(vector<Record>& vectorRecord, string path)
{
	string arg, command, param;
	getline(cin, arg);
	CommandHandler cmd(arg);
	int commands_index = cmd.whatCommand(command, param);
	if (commands_index == -1)
	{
		std::cout << "Error" << endl;
		return false;
	}

	switch (commands_index)
	{
	case 0:
		if(param.empty()) cmdAdd(vectorRecord);
		else cmdAdd(vectorRecord, param);
		break;

	case 1:
		if (param.empty()) cmdOut(vectorRecord);
		else cmdOut(vectorRecord, param);
		break;

	case 2:
		if (param.empty()) cmdDelete(vectorRecord);
		else cmdDelete(vectorRecord, param);
		break;

	case 3:
		if (param.empty()) cmdSave(vectorRecord, path);
		else std::cout << "Error" << endl;
		break;

	case 4:
		if (param.empty()) cmdHelp();
		else std::cout << "Error" << endl;
		break;

	case 5:
		if (param.empty()) return true;
		else std::cout << "Error" << endl;
		break;

	default:
		std::cout << "Error" << endl;
		break;
	}
	return false;
}

//********************************************************//

int toInt(string str)
{
	int temp = 0;

	for (size_t i = 0; i < str.length(); i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (str[i] == j + '0')
			{
				temp = (temp + j) * 10;
				break;
			}
		}
	}
	return temp / 10;
}

void readFile(vector<Record>& vectorRecord, string path)
{
	fstream fs;
	fs.open(path, fstream::in | fstream::app);
	if (!fs.is_open())
	{
		std::cout << "FileError" << endl;
	}
	else
	{
		Record temp;
		//cout << "open" << endl;

		while (true)
		{
			fs >> temp;
						
			if (fs.eof())
			{
				break;
			}

			vectorRecord.push_back(temp);

			//cout << temp << endl;
		}
	}
	fs.close();
	//cout << "close" << endl;
}

void writeToFile(vector<Record>& vectorRecord, string path)
{
	fstream fs;
	fs.open(path, fstream::out);

	if (!fs.is_open())
	{
		std::cout << "FileError" << endl;
	}
	else
	{
		//cout << "open" << endl;

		for (int i = 0; i < vectorRecord.size(); i++)
		{
			fs << vectorRecord.at(i) << endl;
		}
	}
	fs.close();
	//cout << "close" << endl;
}

//********************************************************//

void cmdAdd(vector<Record>& vectorRecord)
{
	Record record;
	Date date;
	int sum;
	string info;
	std::cout << "¬ведите дату: ";
	cin >> date;
	std::cout << "¬ведите сумму: ";
	cin >> sum;
	cin.ignore();
	std::cout << "¬ведите информацию: ";
	getline(cin, info);

	record.setRecord(date, sum, info);

	vectorRecord.push_back(record);
}

void cmdAdd(vector<Record>& vectorRecord, string param)
{
	Record record;
	Date date(time(0));
	int sum;
	string info;
	std::cout << "¬ведите сумму: ";
	cin >> sum;
	cin.ignore();
	std::cout << "¬ведите информацию: ";
	getline(cin, info);

	record.setRecord(date, sum, info);

	vectorRecord.push_back(record);
}

void cmdOut(vector<Record>& vectorRecord)
{
	for (int i = 0; i < vectorRecord.size(); i++)
	{
		vectorRecord.at(i).printRecord();
	}
}

void cmdOut(vector<Record>& vectorRecord, string param)
{
	int temp = toInt(param);
	if (temp > 0 && temp < vectorRecord.size())
	{
		for (int i = vectorRecord.size() - temp; i < vectorRecord.size(); i++)
		{
			vectorRecord.at(i).printRecord();
		}
	}

}

void cmdDelete(vector<Record>& vectorRecord)
{
	if(vectorRecord.size() > 0)	vectorRecord.pop_back();
	else std::cout << "Error" << endl;
}

void cmdDelete(vector<Record>& vectorRecord, string param)
{
	if (param == "all")
	{
		vectorRecord.clear();
		return;
	}
	int temp = toInt(param);
	if (temp > 0 && temp <= vectorRecord.size())
	{
		auto iter = vectorRecord.cbegin();
		vectorRecord.erase(iter + temp - 1);
	}
	else std::cout << "Error" << endl;
}

void cmdHelp()
{
	std::cout << "\"add\"\t\tдобавить запись\n\"add p\"\t\tдобавить запись сегодн€шним числом\n\
\"out\"\t\tвывести все записи\n\"out n\"\t\tпоследние n записей\n\
\"delete\"\tудалить последнюю запись\n\"delete n\"\tудалить запись под номером n\n\
\"delete all\"\tудалить все записи\n\"save\"\t\tсохранить изменени€\n\
\"help\"\t\tсправка\n\"close\"\t\tзакрыть программу\n";
}

void cmdSave(vector<Record>& vectorRecord, string path)
{
	std::cout << "Save..." << endl;
	writeToFile(vectorRecord, path);
	std::cout << "Finish" << endl;
}

