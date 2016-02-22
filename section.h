#ifndef SECTION_H
#define SECTION_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Section
{

private:
	int size_ = 3;
	string content_ = "";
	string location_ = "";
	string section_ = "";

	string default_ = "INVALID";

	const int MAX_CONTENT = 24;
	const int MAX_LOCATION = 30;
	const int MAX_SECTION = 20;
	
	void trimString(string & s, unsigned int maximum);
public:
	Section(string content = "", string location = "", string section = "");
	Section(string s[3]);
	Section(vector<string> s, unsigned int firstIndex = 0,unsigned int lastIndex = 3);
	Section(const Section & s);
	Section & operator=(const Section & s);

	int size() const;
	string getContent() const;
	string getLocation() const;
	string getSection() const;
	string & at(int i);
	string at(int i) const;


	string & operator[](int i);
	string operator[](int i) const;

	void setContent(string content);
	void setLocation(string location);
	void setSection(string Section);
	string upper(string str) const;
	bool isEqualTo(const Section & s) const;
	bool isLessThan(const Section & s) const;

	void output(ostream & os);
	void output(ostream & os) const;

	void input(istream & is);
};

bool operator==(const Section & s, const Section & t);
bool operator<(const Section & s, const Section & t);
bool operator>(const Section & s, const Section & t);
bool operator<=(const Section & s, const Section & t);
bool operator>=(const Section & s, const Section & t);
bool operator != (const Section & s, const Section & t);

ostream & operator<<(ostream & os, const Section & s);
istream & operator>>(istream & is, Section & s);

#endif