#include "stdafx.h"
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <map>
#include <functional>
#include <regex>

using namespace std;

class cppParser
{
private:
	const string DEFAULT_PATH = "C://test.cpp";
	multimap <string, function<void()>> commands;
	string path;
	bool exitMenu;
	void menu()
	{
		std::string choise;
		do
		{
			system("cls");
			cout << "Commands:\n" << "\tPath - change path to file" <<
				"\n\tDelete - delete all comments in CPP file"
				"\n\tShow - display code from CPP file"
				"\n\tExit - exit from the program"
				"\n\nCurrent path: " << path << endl << endl;

			std::cout << "\n > ";
			std::cin >> choise;
			std::transform(choise.begin(), choise.end(), choise.begin(), ::tolower);

			if (commands.count(choise) != 0)
			{
				std::multimap <string, function<void()>>::iterator it = commands.find(choise);
				(*it).second();
			}
			else
			{
				cout << "\n\tInvaild command" << endl;
				Sleep(1500);
			}
		} while (!exitMenu);
	}

	////Commands////

	void changePath()
	{
		std::string newPath;
		std::cout << "\nNew path: ";
		std::cin >> newPath;

		ifstream checkFile(newPath);
		if (checkFile)
		{
			path = newPath;
		}
		else
		{
			std::cout << "\nCan't find path (" + newPath + ")";
			Sleep(1500);
		}
		checkFile.close();
	}

	void deleteAllComments()
	{
		fstream cppFile(path);
		if (cppFile)
		{
			vector<string> newLines;
			string line;
			while (getline(cppFile, line)) 
			{
				string tempLine;
				//regex regular("[^\"]{1}((\\/\\*[^\\*\\/]*\\*\\/)|(//.*))");
				regex regular("(\\/\\*[^\\*\\/]*\\*\\/)|(//.*)");
				newLines.push_back(regex_replace(line.c_str(), regular, ""));
			}
			cppFile.close();
			cppFile.open(path, std::ofstream::out | std::ofstream::trunc);
			for each (string newLine in newLines)
				cppFile << newLine << "\n";
			cppFile.close();
		}
		else
		{
			cout << "Can't find file";
			Sleep(1500);
		}
	}

	void show()
	{
		fstream cppFile(path);
		if (cppFile)
		{
			system("cls");
			string line;
			while (getline(cppFile, line))
				cout << line << endl;
			system("pause");
		}
		else
		{
			cout << "Can't find file";
			Sleep(1500);
		}
		cppFile.close();
	}

	void exit()
	{
		exitMenu = true;
	}

	////Commands////

public:
	cppParser()
	{
		path = DEFAULT_PATH;
		exitMenu = false;

		commands.insert(std::pair<string, function<void()> >("path", [&] {changePath(); }));
		commands.insert(std::pair<string, function<void()> >("delete", [&] {deleteAllComments(); }));
		commands.insert(std::pair<string, function<void()> >("show", [&] {show(); }));
		commands.insert(std::pair<string, function<void()> >("exit", [&] {exit(); }));

		menu();
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	cppParser one;
	return 0;
}
