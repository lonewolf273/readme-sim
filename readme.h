#pragma once
#ifndef README_H
#define README_H

#include <string>
#include "section.h"
#include <vector>

using namespace std;

class Readme
{
private:
	const string FILE_NAME_DEFAULT = "README.txt";
	string fileName_;
	vector<Section>table_;
	string description_;
	vector<int>missingSections_;

	void sortSections(int firstIndex, int lastIndex);
	int partition(int firstIndex, int lastIndex);
	void swap(int firstIndex, int lastIndex);

public:
	Readme();
	Readme(vector<Section>table, string description = "", string fileName = "");
	Readme::Readme(const Readme & r);

	~Readme();

	vector<Section> getTable() const;
	vector<Section> & getTable();
	string getDescription() const;
	string getFileName() const;

	Section & getSectionAt(int index);
	Section getSectionAt(int index) const;

	Section & operator[](int i);
	Section operator[](int i) const;

	void operator=(Readme & r);
	int findSection(Section s, int firstIndex = 0, int lastIndex = -1);
	int findSection(string content, int firstIndex = 0, int lastIndex = -1);

	void setFileName(string fileName);
	void addSection(Section s);
	void addSection(string content = "", string location = "", string section = "");
	void removeSection(unsigned int i);
	void removeSection(Section s);
	bool changeSectionTo(unsigned int index, Section s);

	bool checkSorted(int firstIndex, int lastIndex);
	bool Readme::checkSorted(int firstIndex, int lastIndex) const;

	void sort();
	void output(ostream & os) const;
	bool publish(ostream & os) const;
	bool publish(string fileName = "");
	
	bool save(string = "");
	bool load(string fileName = "");
	bool create(string = "");
	bool fexists(const string fileName);
};

ostream & operator<<(ostream & os, const Readme & r);
#endif