#pragma once

#ifndef MAIN_INTERFACE_H
#define MAIN_INTERFACE_H

#include <iostream>
#include "readme.h"
#include "menuoptions.h"


class MainInterface
{
private:
	
	const string PROJECT_DIR = "projects\\"; //directory of projects
	const string PUBLISH_DIR = "publishedFiles\\"; //directory of published files
	
	string fileName_;
	int sectionNumber_ = -1;
	Readme readme_;
	string versionNumber_ = "1.0";
	MenuOptions currentOption_;
	bool loadedFile_ = false; //check whether or not the user loaded the file
	bool changedFile_ = false; //checks whether or not the user changed the file since the last save
	bool savedFile_ = false; //checks whether or not the user saved the file

	

protected:

	string introduction();
	MenuOptions getCurrentOption();
	///////////////////////////
	//
	//		MUTATORS
	//
	///////////////////////////
	void setFileName(string fileName);

	void setReadMe(Readme r);
	void setCurrentOption(MenuOptions m);
public:
	///////////////////////////
	//
	//		CONSTRUCTORS
	//
	///////////////////////////
	MainInterface();

	///////////////////////////
	//
	//		INSPECTORS
	//
	///////////////////////////
	string getFileName() const;

	Readme getReadMe() const;

	///////////////////////////
	//
	//		FACILITATORS
	//
	///////////////////////////	
	void clearConsole();
	void play(ostream & os, istream & is);
	void mainMenu(ostream & os, istream & is);
	bool load(ostream & os, istream & is);
	bool create(ostream & os, istream & is);
	bool save(ostream & os, istream & is);
	bool publish(ostream & os, istream & is);
	void help(ostream & os, string s);
	bool quit(ostream & os, istream & is);
	string requestInput(ostream & os, istream & is, string question = "");
	string lower(string s) const;
	bool validateInput(string & s, string process = "");
	bool isAlpha(string s, vector<char>) const;
};


#endif