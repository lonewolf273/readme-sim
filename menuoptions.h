#pragma once

#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H


#include <vector>
#include <string>

using namespace std;

enum Options
{
	MAIN_MENU,
	LOAD_FILE,
	CREATE_FILE,
	DISPLAY_CONTENT,
	ADD_ITEM,
	EDIT_DESCRIPTION,
	EDIT_ITEM,
	SAVE_FILE,
	VIEW_README,
	PUBLISH_FILE,
	CONTACT_US,
	HELP,
	QUIT
};

class MenuOptions
{
private:


	vector<string> s_ = {
		"Main Menu",
		"Load File",
		"Create File",
		"Display Content",
		"Add Item",
		"Change Description",
		"Edit Section",
		"Save File",
		"View Readme",
		"Publish File",
		"Contact Us",
		"Help",
		"Quit"
	};
	Options option_;
	unsigned int index_;


	unsigned int getIndex(Options o) const;
	void setIndex(unsigned int i);
	void setOption(Options o);

public:
	MenuOptions(Options o = MAIN_MENU);
	MenuOptions(unsigned int index);

	unsigned int maxSize();
	Options getOption(unsigned int i) const;
	Options getOption() const;
	unsigned int getIndex() const;

	Options operator[](unsigned int i);

	void operator=(Options o);
	void operator=(unsigned int i);

	MenuOptions add(unsigned int i) const;
	MenuOptions add(const MenuOptions & n) const;
	
	MenuOptions subtract(unsigned int i) const;
	MenuOptions subtract(const MenuOptions & n) const;

	MenuOptions operator++();
	MenuOptions operator++(int);
	MenuOptions operator--();
	MenuOptions operator--(int);

	void operator+=(unsigned int i);
	void operator+=(const MenuOptions & n);
	void operator-=(unsigned int i);
	void operator-=(const MenuOptions & n);

	bool isEqualTo(unsigned int i) const;
	bool isEqualTo(const MenuOptions & n) const;
	bool isGreaterThan(const MenuOptions & n) const;
	bool isGreaterThan(unsigned int i) const;

	string toString() const;
	string toString(Options o) const;
	string toString(unsigned int i) const ;

	string indexToString() const;
	string indexToString(unsigned int i) const;
	string indexToString(Options o) const;
	void output(ostream & os) const;
};

ostream & operator<<(ostream & os, const MenuOptions & m);


bool operator==(const MenuOptions & m,const MenuOptions & n);
bool operator!=(const MenuOptions & m, const MenuOptions & n);
bool operator<(const MenuOptions & m, const MenuOptions & n);
bool operator<=(const MenuOptions & m, const MenuOptions & n);
bool operator>(const MenuOptions & m, const MenuOptions & n);
bool operator>=(const MenuOptions & m, const MenuOptions & n);

MenuOptions operator+(const MenuOptions & m, const unsigned int i);
MenuOptions operator+(const unsigned int i, const MenuOptions & m);
MenuOptions operator-(const MenuOptions & m, const unsigned int i);
MenuOptions operator-(const MenuOptions & m, const MenuOptions & n);

bool operator==(const MenuOptions & m, Options & n);
bool operator!=(const MenuOptions & m, Options & n);
#endif