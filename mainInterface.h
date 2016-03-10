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
	bool savedFile_ = true; //checks whether or not the user saved the file

	

protected:

	string introduction(); //prints the introduction
	MenuOptions getCurrentOption(); //gets the current placement
	///////////////////////////
	//
	//		MUTATORS
	//
	///////////////////////////
	void setFileName(string fileName); //sets the file name for the readme

	void setReadMe(Readme r); //sets the readme to a specific readme
	void setCurrentOption(MenuOptions m); //sets the current place to an area
public:
	///////////////////////////
	//
	//		CONSTRUCTORS
	//
	///////////////////////////
	MainInterface(); //default constuctor

	///////////////////////////
	//
	//		INSPECTORS
	//
	///////////////////////////
	string getFileName() const; //shows the current file name

	Readme getReadMe() const; //shows the current readme

	///////////////////////////
	//
	//		FACILITATORS
	//
	///////////////////////////	
	void clearStream(istream & is); //clears the console
	void play(ostream & os, istream & is); //starts the program
	void mainMenu(ostream & os, istream & is); //goes to the main menu
	void addItem(ostream & os, istream & is); //asks which item to add and adjust accordingly
	void addChapter(ostream & os, istream & is); //adds a chapter
	void addSection(ostream & os, istream & is); //adds a section to the current section
	void viewReadme(ostream & os, istream & is); //allows you to view readme on the console
	bool load(ostream & os, istream & is); //loads the file if it exists
	bool create(ostream & os, istream & is); //creates a file
	bool save(ostream & os, istream & is); //saves a file if it's loaded
	bool publish(ostream & os, istream & is); //publishes a file 
	void help(ostream & os, string s); //goes to help screen
	bool quit(ostream & os, istream & is); //quits the program
	string requestInput(ostream & os, istream & is, string question = ""); //general input
	string lower(string s) const; //turns a string lowercase
	bool validateInput(string & s, string process = ""); //checks if a string is a valid
	bool isAlpha(string s, vector<char>) const; //checks if a string is an alpha character
};


#endif