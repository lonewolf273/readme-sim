#include "menuoptions.h"
#include <iostream>
#include <cassert>

unsigned int MenuOptions::getIndex(Options o) const
{
	for (unsigned int i = 0; i < s_.size(); i++)
	{
		if (getOption(i) == o) return i;
	}

	return -1;
}

unsigned int MenuOptions::getIndex() const
{
	return index_;
}

void MenuOptions::setIndex(unsigned int i)
{
	index_ = i;
	option_ = getOption(i);
}
void MenuOptions::setOption(Options o)
{
	option_ = o;
	index_ = getIndex(o);
}

MenuOptions::MenuOptions(Options o)
{
	option_ = o;
	index_ = getIndex(o);
}
MenuOptions::MenuOptions(unsigned int index)
{
	index_ = index % s_.size();
	option_ = getOption(index_);
}


unsigned int MenuOptions::maxSize()
{
	return s_.size();
}


Options MenuOptions::getOption(unsigned int i) const
{
	switch (i)
	{
	case 0:
		return MAIN_MENU;
	case 1:
		return LOAD_FILE;
	case 2:
		return CREATE_FILE;
	case 3:
		return DISPLAY_CONTENT;
	case 4:
		return ADD_ITEM;
	case 5:
		return EDIT_DESCRIPTION;
	case 6:
		return EDIT_ITEM;
	case 7:
		return SAVE_FILE;
	case 8:
		return VIEW_README;
	case 9:
		return PUBLISH_FILE;
	case 10:
		return CONTACT_US;
	case 11:
		return HELP;
	default:
		return QUIT;
	}
}

Options MenuOptions::getOption() const
{
	return getOption(index_);
}

Options MenuOptions::operator[](unsigned int i)
{
	return getOption(i);
}

void  MenuOptions::operator=(Options o)
{
	setOption(o);
}

void MenuOptions::operator=(unsigned int i)
{
	assert(i < s_.size());
	setIndex(i);
}

MenuOptions MenuOptions::add(unsigned int i) const
{
	return MenuOptions((index_ + i) % s_.size());
}

MenuOptions MenuOptions::add(const MenuOptions & n) const
{
	return MenuOptions((index_ + n.index_) % s_.size());
}

MenuOptions MenuOptions::subtract(unsigned int i) const
{
	int index = int(index_) - i;

	if (index < 0) index += s_.size();

	return MenuOptions(index);
}
MenuOptions MenuOptions::subtract(const MenuOptions & n) const
{
	return subtract(n.getIndex());
}

MenuOptions MenuOptions::operator++()
{
	index_++;
	if (index_ >= s_.size()) index_ = 0;
	option_ = getOption();

	return(MenuOptions(index_));
}

MenuOptions MenuOptions::operator++(int)
{
	MenuOptions m(index_);
	index_++;
	if (index_ >= s_.size()) index_ = 0;
	option_ = getOption();

	return m;
}

MenuOptions MenuOptions::operator--()
{
	index_--;
	if (index_ < 0) index_ = s_.size() - 1;
	option_ = getOption();
	return MenuOptions(index_);
}

MenuOptions MenuOptions::operator--(int)
{
	MenuOptions m(index_);
	index_--;
	if (index_ < 0) index_ = s_.size() - 1;
	option_ = getOption();
	return m;
}

void MenuOptions::operator+=(unsigned int i)
{
	MenuOptions m(add(i));
	setIndex(m.getIndex());
	setOption(m.getOption());
}

void MenuOptions::operator+=(const MenuOptions & n)
{
	MenuOptions m(add(n));
	setIndex(m.getIndex());
	setOption(m.getOption());
}

void MenuOptions::operator-=(unsigned int i)
{
	MenuOptions m(subtract(i));
	setIndex(m.getIndex());
	setOption(m.getOption());
}

void MenuOptions::operator-=(const MenuOptions & n)
{
	MenuOptions m(subtract(n));
	setIndex(m.getIndex());
	setOption(m.getOption());
}

bool MenuOptions::isEqualTo(unsigned int i) const
{
	if (index_ == i) return true;
	return false;
}

bool MenuOptions::isEqualTo(const MenuOptions & n) const
{
	if (getIndex() == n.getIndex()) return true;
	return false;
}

bool MenuOptions::isGreaterThan(const MenuOptions & n) const
{
	if (index_ > n.getIndex()) return true;
	return false;
}

bool MenuOptions::isGreaterThan(unsigned int i) const
{
	if (index_ > i) return true;
	return false;
}

string MenuOptions::toString() const
{
	return s_[index_];
}

string MenuOptions::toString(Options o) const
{
	return s_[getIndex(o)];
}

string MenuOptions::toString(unsigned int i) const
{
	assert(i < s_.size());
	return s_[i];
}

string MenuOptions::indexToString() const
{
	return to_string(index_);
}

string MenuOptions::indexToString(unsigned int i) const
{
	return MenuOptions(i).indexToString();
}

string MenuOptions::indexToString(Options o) const
{
	return MenuOptions(o).indexToString();
}

void MenuOptions::output(ostream & os) const
{
	os << toString(index_);
}

ostream & operator<<(ostream & os, const MenuOptions & m)
{
	m.output(os);
	return os;
}

bool operator==(const MenuOptions & m, const MenuOptions & n)
{
	return m.isEqualTo(n);
}

bool operator>(const MenuOptions & m, const MenuOptions & n)
{
	return m.isGreaterThan(n);
}

bool operator!=(const MenuOptions & m, const MenuOptions & n)
{
	return !(m == n);
}

bool operator<(const MenuOptions & m, const MenuOptions & n)
{
	return !(m > n || m == n);
}
bool operator<=(const MenuOptions & m, const MenuOptions & n)
{
	return !(m > n);
}

bool operator>=(const MenuOptions & m, const MenuOptions & n)
{
	return m > n || m == n;
}

MenuOptions operator+(const MenuOptions & m, const unsigned int i)
{
	return m.add(i);
}


MenuOptions operator+(const unsigned int i, const MenuOptions & m)
{
	return m.add(i);
}

MenuOptions operator-(const MenuOptions & m, const unsigned int i)
{
	return m.subtract(i);
}

MenuOptions operator-(const MenuOptions & m, const MenuOptions & n)
{
	return m.subtract(n.getIndex());
}

bool operator==(const MenuOptions & m, Options & n)
{
	return m == MenuOptions(n);
}
bool operator!=(const MenuOptions & m, Options & n)
{
	return m != MenuOptions(n);
}