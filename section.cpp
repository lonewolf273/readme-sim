#include "section.h"
#include <iomanip>
#include <string>

using namespace std;

void Section::trimString(string & s, unsigned int maximum)
{
	if (s.size() > maximum)
	{
		s.replace(maximum, s.length() - maximum, "");
	}
}
Section::Section(string content, string location, string section)
{
	if (content == "")
		content_ = content;
	if (location == "") 
		location_ = location;
	if (section == "")
		section_ = section;

	setContent(content);
	setLocation(location);
	setSection(section);
	
}

Section::Section(string s[3])
{
	content_ = s[0];
	location_ = s[1];
	section_ = s[2];
}

Section::Section(vector<string> s, unsigned int firstIndex, unsigned int lastIndex)
{
	content_ = "";
	location_ = "";
	section_ = "";
	if (firstIndex > lastIndex || firstIndex >= s.size() || firstIndex < 0)
	{
		return;
	}
	string str[3] = { "", "", "" };
	if (lastIndex >= s.size())
	{
		if (s.size() - firstIndex > 3)
		{
			for (unsigned int i = firstIndex; i < firstIndex + 3; i++)
			{
				str[i - firstIndex] = s[i];
			}

		}
	}
	else if (lastIndex - firstIndex >= 3)
	{
		for (unsigned int i = firstIndex; i < firstIndex + 3; i++)
		{
			str[i - firstIndex] = s[i];
		}
	}
	else
	{
		for (unsigned int i = firstIndex; i < lastIndex; i++)
		{
			str[i - firstIndex] = s[i];
		}
	}
	content_ = str[0];
	location_ = str[1];
	section_ = str[2];
}


Section::Section(const Section & s)
{
	content_ = s.getContent();
	location_ = s.getLocation();
	section_ = s.getSection();
}

Section & Section::operator=(const Section & s)
{
	return Section(s.getContent(), s.getLocation(), s.getSection());
}



int Section::size() const
{
	return size_;
}

string Section::getContent() const
{
	return content_;
}

string Section::getLocation() const
{
	return location_;
}

string Section::getSection() const
{
	return section_;
}

string & Section::at(int i)
{
	switch (i)
	{
	case 0:
		return content_;
		break;
	case 1:
		return location_;
		break;
	case 2:
		return section_;
		break;
	default:
		return default_;

	}
}

string Section::at(int i) const
{
	switch (i)
	{
	case 0:
		return content_;
		break;
	case 1:
		return location_;
		break;
	case 2:
		return section_;
		break;
	default:
		return default_;
	}

}

string & Section::operator[](int i)
{
	return at(i);
}

string Section::operator[](int i) const
{
	return at(i);
}

void Section::setContent(string content)
{
	if (content != "")
		content_ = content;
	trimString(content_, MAX_CONTENT);
}

void Section::setLocation(string location)
{
	if (location != "") location_ = location;
	trimString(location_, MAX_LOCATION);
}

void Section::setSection(string section)
{
	if (section != "") section_ = section;
	trimString(section_, MAX_SECTION);
}

string Section::upper(string str) const
{
	const char TO_UPPER = 'a' - 'A';
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z') str[i] -= TO_UPPER;
	}
	return str;
}


bool Section::isEqualTo(const Section & s) const
{
	if (content_ == s.content_) return true;
	return false;
}

bool Section::isLessThan(const Section & s) const
{
	if (content_ < s.content_) return true;
	return false;
}
void Section::output(ostream & os)
{
	os << left << setw(20) << content_ << setw(20) << location_ << setw(20) << section_;
}
void Section::output(ostream & os) const
{
	os << left << setw(20) << upper(content_) << setw(20) << location_ << setw(20) << upper(section_);
}

void Section::input(istream & is)
{
	getline(is, content_);
	getline(is, location_);
	getline(is, section_);
}

bool operator==(const Section & s,const Section & t)
{
	return s.isEqualTo(t);
}

bool operator<(const Section & s, const Section & t)
{
	return s.isLessThan(t);
}
bool operator>(const Section & s, const Section & t)
{
	return !(s.isEqualTo(t) || s.isLessThan(t));
}
bool operator<=(const Section & s, const Section & t)
{
	return s.isEqualTo(t) || s.isLessThan(t);
}
bool operator>=(const Section & s, const Section & t)
{
	return !s.isLessThan(t);
}
bool operator != (const Section & s, const Section & t)
{
	return !s.isEqualTo(t);
}

ostream & operator<<(ostream & os, const Section & s)
{
	s.output(os);
	return os;
}
istream & operator>>(istream & is, Section & s)
{
	s.input(is);
	return is;
}

