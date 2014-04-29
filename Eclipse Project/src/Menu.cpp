#ifndef iostream
#include <iostream>
#endif // !iostream

#ifndef conio
#include <conio.h>
#endif // !conio


#include "Menu.h"

using namespace std;

/////////////////////////////// MENU /////////////////////////////////////////

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Menu::Menu()
{
}
Menu::Menu(const string& title)
{
	mTitle = title;
}
Menu::~Menu()
{
}


//============================= OPERATIONS ===================================

void Menu::addFunction(const string& description, void(*function)())
{
	mEntries.push_back(MenuEntry(description, function));
}
void Menu::addSubMenu(const string& description, Menu* subMenu)
{
	mEntries.push_back(MenuEntry(description, subMenu));
}
void Menu::run()
{
	unsigned int answer;

	while (true)
	{
		print();
		answer = _getch();
		answer -= 0x30;

		if (answer == mEntries.size() + 1)
			return;

		if (answer > 0 && answer <= mEntries.size())
		{
			mEntries[answer - 1].run();
		}
	}
}
bool Menu::inputData(string& input)
{
	bool done = false;

	while (!done)
	{
		cin >> input;
		if (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return false;
			}

			cin.clear();
			cin.ignore(1000, '\n');


			cout << "Invalid input." << endl;
		}
		else
			done = true;
	}

	return true;
}


/////////////////////////////// PRIVATE    ///////////////////////////////////

//============================= OPERATIONS ===================================

void Menu::print()
{
	cout << mTitle << endl << endl;

	for (unsigned int i = 0; i < mEntries.size(); i++)
		cout << i + 1 << " - " << mEntries[i] << endl;

	cout << mEntries.size() + 1 << " - Exit." << endl;
}


/////////////////////////////// MENU ENTRY ////////////////////////////////////

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

MenuEntry::MenuEntry()
{
}
MenuEntry::MenuEntry(const std::string& description, Menu* subMenu)
{
	mDescription = description;
	mSubMenu = subMenu;
	mIsMenu = true;


	mFunction = 0;
}
MenuEntry::MenuEntry(const std::string& description, void(*function)())
{
	mDescription = description;
	mFunction = function;
	mIsMenu = false;


	mSubMenu = 0;
}


//============================= OPERATIONS ===================================

void MenuEntry::run()
{
	if (mIsMenu)
		mSubMenu->run();
	else
		mFunction();
}


//============================= OPERATORS ====================================

ostream& operator<<(ostream& os, const MenuEntry& entry)
{
	os << entry.description();

	return os;
}


//============================== ACCESS ======================================

string MenuEntry::description() const
{
	return mDescription;
}


//============================= FUNCTIONS ====================================

