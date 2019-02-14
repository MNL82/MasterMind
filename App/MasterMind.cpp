#include "MasterMind.h"

#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>

using namespace MM;
using namespace std;

int getInteger(int minValue, int defaultValue, int maxValue, const char *start = "> ")
{
	char textIn[20];
	while (true) {
		cout << start;
		cin.getline(textIn, 20);

		std::string t(textIn);
		if (t.empty() && defaultValue >= 0) {
			return defaultValue;
		}
		try {
			int number = std::stoi(t);
			if (number >= minValue && number <= maxValue) {
				return number;
			}
		}
		catch (exception) {}
	}
}

std::vector<int> getIntegerList(int minValue, int maxValue, int count)
{
	char textIn[200];
	while (true) {
		cout << "> ";
		cin.getline(textIn, 200);

		stringstream test(textIn);
		std::string segment;
		std::vector<int> seglist;

		try {
			while (std::getline(test, segment, ','))
			{
				int number = std::stoi(segment);
				if (number >= minValue && number <= maxValue) {
					seglist.push_back(number);
				}
				continue;
			}
			if (static_cast<int>(seglist.size()) == count) {
				return seglist;
			}
		}
		catch (exception) {}
	}
}

ColorCombination getGuess(const MasterMind &MM)
{
	cout << "Guess " << MM.currentGuessIndex() + 1 << endl;
	ColorCombination cc(MM.config().columnCount());

	// >>>> Enter all color value in one line comma seperated <<<<
	std::vector<int> intList = getIntegerList(1, MM.config().colorCount(), MM.config().columnCount());
	for (int i = 0; i < static_cast<int>(intList.size()); i++)
	{
		cc.setColor(i, intList[i]);
	}

	// >>>> Enter one color value for each line <<<<
	//for (int i = 0; i < MM.config().columnCount(); i++)
	//{
	//	cout << (i + 1) << ". ";
	//	cc.setColor(i, getInteger(1, -1, MM.config().colorCount(), ": "));
	//}
	return cc;
}

int main()
{
    cout << "Welcome to MasterMind" << endl; 
	cout << "Configuration (Enter for default):" << endl;

	Configuration c;
	cout << "Number of Columns[" << MM_COLUMNS_MIN_COUNT << "-" << MM_COLUMNS_MAX_COUNT << "] (" << MM_COLUMNS_DEFAULT << "):" << endl;
	c.setColumnCount(getInteger(MM_COLUMNS_MIN_COUNT, MM_COLUMNS_DEFAULT, MM_COLUMNS_MAX_COUNT));
	cout << "Number of Colors[" << MM_COLOR_MIN_COUNT << "-" << MM_COLOR_MAX_COUNT << "] (" << MM_COLOR_DEFAULT << "):" << endl;
	c.setColorCount(getInteger(MM_COLOR_MIN_COUNT, MM_COLOR_DEFAULT, MM_COLOR_MAX_COUNT));
	cout << "Number of Tries[" << MM_TRIES_MIN_COUNT << "-" << MM_TRIES_MAX_COUNT << "] (" << MM_TRIES_DEFAULT << "):" << endl;
	c.setTriesCount(getInteger(MM_TRIES_MIN_COUNT, MM_TRIES_DEFAULT, MM_TRIES_MAX_COUNT));

	cout << "Available colors:" << endl;

	for (int i = 1; i <= c.colorCount(); i++)
	{
		cout << Configuration::colorNameFromInt(i) << "(" << i << ")" << endl;
	}

	while (true) {
		MasterMind MM(c);
		MM.randomCodeColors();
		
		cout << endl << ">>>> Game started <<<<" << endl << endl;
		cout << "Each guess is entered as " << MM.config().columnCount() << " comma seperated integers" << endl;
		while (!MM.finished()) {
			MM.setGuessColors(getGuess(MM));
			MM.calculateGuessResult();
			int resultIndex = MM.currentGuessIndex() + (MM.finished() ? 0 : -1);
			cout << "Correct Posistion: " << MM.guess(resultIndex).result().rightPosition << " - Correct Color: " << MM.guess(resultIndex).result().rightColor << endl;
		}
		cout << endl << "Game Over" << endl;
		cout << "You ";
		if (MM.state() == MasterMind::State::Success) {
			cout << "Won!" << endl;
		}
		else {
			cout << "Lost :(" << endl;
		}
		cout << "Penalty points: " << MM.points() << endl;

		cout << endl << "Type 'a' to try again or enter to exit" << endl;
		cout << "> ";
		char textIn[20];
		cin.getline(textIn, 200);
		std::string t(textIn);
		if (t == "a" | t == "A") {
			cout << endl;
			continue;
		}
		return 0;
	}
}

// COLORS!!!
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//// you can loop k higher to see more color choices
//for (int k = 1; k < 255; k++)
//{
//	// pick the colorattribute k you want
//	SetConsoleTextAttribute(hConsole, k);
//	cout << k << " I want to be nice today!" << endl;
//}