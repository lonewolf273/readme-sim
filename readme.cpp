#include "readme.h"
#include "section.h"
#include <string>
#include <iostream>
#include <fstream>

void Readme::sortSections(int firstIndex, int lastIndex)
{
	if (firstIndex > lastIndex)
	{
		int p = partition(firstIndex, lastIndex);
		sortSections(p + 1, lastIndex);
		sortSections(firstIndex, p - 1);
	}
}

int Readme::partition(int firstIndex, int lastIndex)
{
	Section pivot = table_[firstIndex];
	int i = firstIndex;
	int j = lastIndex + 1;
	while (true) //infinite loop until it can return
	{
		do
		{
			++i;
		} while (table_[i] < pivot);
		do
		{
			--j;
		} while (table_[j] > pivot);
		if (i >= j) return j;
		swap(i, j);
	}
}

void Readme::swap(int firstIndex, int lastIndex)
{
	Section _temp = table_[firstIndex];
	table_[firstIndex] = table_[lastIndex];
	table_[lastIndex] = _temp;
}



Readme::Readme()
{
	fileName_ = "";
	description_ = "";
}

Readme::Readme(vector<Section>table, string description, string fileName)
{
	table_ = table;
	description_ = description;
	fileName_ = fileName;
}

Readme::Readme(const Readme & r)
{
	fileName_ = r.getFileName();
	table_ = r.getTable();
	description_ = r.getDescription();
}

Readme::~Readme()
{
	save();
	table_.clear();
	fileName_ = "";
	description_ = "";
}

vector<Section> Readme::getTable() const
{
	return table_;
}

vector<Section> & Readme::getTable()
{
	return table_;
}

string Readme::getDescription() const
{
	return description_;
}

string Readme::getFileName() const
{
	return fileName_;
}

Section & Readme::getSectionAt(int index)
{
	return table_[index];
}

Section Readme::getSectionAt(int index) const
{
	return table_[index];
}

Section & Readme::operator[](int i)
{
	return getSectionAt(i);
}

Section Readme::operator[](int i) const
{
	return getSectionAt(i);
}

void Readme::operator=(Readme & r)
{
	fileName_ = r.getFileName();
	table_ = r.getTable();
	description_ = r.getDescription();
}



int Readme::findSection(Section s, int firstIndex, int lastIndex)
{
	if (lastIndex < 0) lastIndex = table_.size() - 1;

	if (firstIndex > lastIndex) return -1;
	if (firstIndex == lastIndex) return s == table_[firstIndex] ? firstIndex : -1;
	
	if (!checkSorted(firstIndex, lastIndex))
	{
		sortSections(firstIndex, lastIndex);
	}

	int mid = (firstIndex + lastIndex) / 2;
	
	if (s == table_[mid]) return mid;
	if (s < table_[mid]) return findSection(s, firstIndex, mid - 1);
	return findSection(s, mid + 1, lastIndex);

}

int Readme::findSection(string content, int firstIndex, int lastIndex)
{
	return findSection(Section(content), firstIndex, lastIndex);
}

void Readme::setFileName(string fileName)
{
	fileName_ = fileName;
}

void Readme::addSection(Section s)
{
	if (findSection(s) != -1)
	{
		if (missingSections_.size() < 1)
			table_.push_back(s);
		else
		{
			table_[missingSections_[missingSections_.size() - 1]] = s;
			missingSections_.pop_back();
		}
	}

}

void Readme::addSection(string content, string location, string section)
{
	addSection(Section(content, location, section));
}

void Readme::removeSection(unsigned int i)
{
	table_[i] = Section();
	missingSections_.push_back(i);
}

void Readme::removeSection(Section s)
{
	removeSection(findSection(s));
}

bool Readme::changeSectionTo(unsigned int index, Section s)
{
	if (index < 1 || index >= table_.size()) return false;

	table_[index] = s;
	return true;
}

bool Readme::checkSorted(int firstIndex, int lastIndex)
{
	
	if (firstIndex >= lastIndex) return true;
	if (lastIndex - firstIndex == 1) return true;

	return table_[firstIndex] < table_[firstIndex + 1] && checkSorted(firstIndex + 1, lastIndex);
}

bool Readme::checkSorted(int firstIndex, int lastIndex) const
{

	if (firstIndex >= lastIndex) return true;
	if (lastIndex - firstIndex == 1) return true;

	return table_[firstIndex] < table_[firstIndex + 1] && checkSorted(firstIndex + 1, lastIndex);
}

void Readme::sort()
{
	if (!checkSorted(0, table_.size() - 1))
		sortSections(0, table_.size() - 1);
}


void Readme::output(ostream & os) const
{
	for (unsigned int i = 0; i < table_.size(); i++)
	{
		if (table_[i] != Section())
			os << table_[i] << endl;
	}
	os << endl << endl;

	os << "<Description>" << endl;
	os << description_;
	os << "<DescriptionEnd>" << endl;
}

bool Readme::publish(ostream & os) const
{
	for (unsigned int i = 0; i < table_.size(); i++)
	{
		os << table_[i] << endl;
	}
	os << endl << endl;

	os << description_;
	return true;
}

bool Readme::publish(string fileName)
{
	if (fileName == "")
	{
		if (fileName_ == "") fileName = "README.txt";
		else fileName = fileName_;
	}
	
	fstream fs;
	fs.open(fileName, ios::out | ios::trunc);

	if (!fs.good() || !fs.is_open()) return false;
	if (!publish(fs)) return false;

	fs.close();
	fs.clear();
	return true;
}


bool Readme::save(string file)
{
	string fileName;
	if (file == "")
	{
		fileName = fileName_;
		if (fileName == "") fileName = "README.txt";
	}
	else
	{
		fileName = file;
		fileName = fileName_;
	}
	
	fstream of(fileName, ios::out | ios::in | ios::trunc);

	if (!of.is_open()) return false;

	output(of);

	of.close();
	of.clear();

	if (of.is_open()) return false;
	return true;
}

bool Readme::load(string fileName)
{
	ifstream is;
	if (is.is_open())
	{
		is.close();
		is.clear();
	}
	if (fileName == "")
	{
		if (fileName_ == "") fileName = FILE_NAME_DEFAULT;
		else fileName = fileName_;
	}

	is.open(fileName);
	if (!is.is_open() || !is.good()) return false;

	bool onDescription = false;
	vector<Section>table;
	string description;
	string str[3];
	int i = 0;
	while (!is.eof())
	{
		if (!onDescription)
		{
			is >> description;
			if (i == 3)
			{
				table.push_back(Section());
				i = 0;
			}
			if (description == "<Description>") onDescription = true;
			if (!onDescription) str[i] = description;
			else description = "";
		}
		else
		{
			string inputString;
			getline(is, inputString);
			if (inputString != "<DescriptionEnd>")
			{
				description += inputString + '\n';
			}
		}
	}
	is.close();
	is.clear();
	fileName_ = fileName;
	if (description == "" && table.size() == 0) return false;

	table_.clear();
	table_ = table;
	description_ = description;
	return true;
}

bool Readme::create(string fileName)
{
	if (fileName == "")
	{
		if (fileName_ == "")
			fileName = FILE_NAME_DEFAULT;
		else
			fileName = fileName_;
	}

	ofstream of(fileName.c_str());

	if (!of.is_open() || !of.good())
	{
		of.close();
		of.clear();
		return false;
	}

	fileName_ = fileName;
	of.close();
	of.clear();
	return save(fileName);
}

bool Readme::fexists(const string fileName)
{
	ifstream ifile(fileName);
	return ifile.is_open() && ifile.good();
}

ostream & operator<<(ostream & os, const Readme & r)
{
	r.output(os);
	return os;
}