/*
	@file:		description.h
	@author:	Vincent Mills
	@version:	v. 0.2.1
	@date:		2 March 2016
*/

#ifndef _DESCRIPTION_H
#define _DESCRIPTION_H

#include "chapter.h"
#include <vector>

class description
{
	//Description class
	//Made with a list of chapters
	//Organizes based on the chapters
	//uses pointers for optimization
private:
	vector<chapter *>chapters_; //alphabetical list of chapters
	chapter * head_; //top of list of chapters
		//can find all chapters based on this
	chapter * tail_; //bottom of list of chapters
	chapter * current_; //current chapter that the description is on
	bool isSorted_;


	///////////////////////////////
	//
	//	   Private Inspectors
	//
	///////////////////////////////
	chapter * getChapterPtrAt(unsigned int index);
	chapter * getChapterPtrAt(unsigned int index) const;
	chapter * getCurrentChapterPtr() const; // gets the current chapter pointer

	///////////////////////////////
	//
	//	   Private Mutators
	//
	///////////////////////////////
	void fullSort(); // does full sort of contents if sorted (use this)
	void sort(unsigned int low, unsigned int high); //sorts contents
	unsigned int partition(unsigned int low, unsigned int high); //helps with sorting
	void vectorSwap(unsigned int one, unsigned int two); //swaps two objects' position in vector
	void pointerSwap(unsigned int one, unsigned int two); //swaps two objects' vector position
	void pointerOverwrite(chapter * overwritten, chapter * overwriter); //overwrite pointers
	void setCurrentChapterPtr(chapter * c); // sets the current chapter pointer to that chapter
	void setCurrentChapterPtr(unsigned int index); //sets the currrent chapter pointer to that chapter
	void insertChapters(vector<chapter *>c);
	void insertChapter(chapter * c);

	///////////////////////////////
	//
	//	   Private Facilitators
	//
	///////////////////////////////
	unsigned int find(const chapter & c, unsigned int low, unsigned int high) const; //finds the chapter that you're looking for
		// uses the chapter address


public:
	///////////////////////////////
	//
	// Constructors and Destructors
	//
	///////////////////////////////
	description(); //default constructor
	description(const description & d); //copy constructord
		// should almost never be used but just in case.

	description(vector<string>titles, vector<string>contents); //alternate constructor
		//given titles and contents
	
	description(vector<chapter>c);

	~description(); //destructor
	///////////////////////////////
	//
	//		  Inspectors
	//
	///////////////////////////////
	chapter & getChapterAt(unsigned int index); //gets chapter at index
	chapter & getChapterAt(unsigned int index) const; //same as before but const
	unsigned int size() const; //gets how many chapters are in the description
	chapter & getCurrentChapter() const;
	chapter & getNextChapter() const;
	chapter & getPrevChapter() const;

	chapter & operator[](unsigned int index); 
	chapter & operator[](unsigned int index) const;

	description & operator=(const description & d);
	///////////////////////////////
	//
	//		  Mutators
	//
	///////////////////////////////
	void insertChapter(string title, string content = "");
	void insertChapters(vector<string>title, vector<string>contents);
	void insertChapters(vector<string>descriptions);


	bool contains(string title) const;
	void beginChapters(); //starts at the beginning of the description
	bool gotoNextChapter(); //true if it can move to the next chapter
	bool gotoPrevChapter(); //true if it can move to the previous chapter
	bool deleteChapter(const chapter & c);
	bool deleteChapter(string title);
	///////////////////////////////
	//
	//		  Facilitators
	//
	///////////////////////////////
	void output(ostream & os) const;
};
ostream & operator<<(ostream & os, const description & d);

#endif