#ifndef MENU_H
#define MENU_H

#ifndef string
#include <string>
#endif // !string

#ifndef vector
#include <vector>
#endif // !vector

#ifndef fstream
#include <fstream>
#endif // !fstream

class MenuEntry;

class Menu
{
public:

	Menu();
	Menu(const std::string& title);
	~Menu();

	void addFunction(const std::string& description, void(*function)());
	void addSubMenu(const std::string& description, Menu* subMenu);

	void run();



private:
	void print();
	static bool inputData(std::string& data);

private:
	std::string mTitle;
	std::vector<MenuEntry> mEntries;
};

class MenuEntry
{
public:
	MenuEntry();
	MenuEntry(const std::string& description, Menu* subMenu);
	MenuEntry(const std::string& description, void(*function)());

	void run();
	std::string description() const;

private:
	std::string mDescription;
	Menu* mSubMenu;
	void(*mFunction)();

	bool mIsMenu;
};

std::ostream& operator<<(std::ostream& os, const MenuEntry& entry);

#endif
