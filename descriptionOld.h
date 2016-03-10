/*
	@file:		description.h
	@author:	Vincent Mills
	@version:	v. 0.1.1
	@date:		22 February 2016
*/

#ifndef _DESCRIPTION_H
#define _DESCRIPTION_H

#include <vector>
#include <map>
#include "chapter.h"

using namespace std;

class Description
{
private:

	vector<chapter * >chapters_; //list of chapters in alphabetical order
	chapter * chapterHead_;
	chapter * currentChapter_;

	vector<string>titles_;
		//list of titles in description
	vector<string>content_;
		//list of contents that goes with titles

	unsigned int chapterIndex_ = -1; // what chapter the user is currently on
	vector<int> blanks_; //list of blank spots that are in the description
	string oldChapter_[2] = { "", "" }; //old way. trying to see if it's needed
	string chapter_[2] = { "", "" };
	bool titlesSorted = false; //makes sure that the computer doesn't unnecessarily sort titles
	bool contentsSorted = false; //makes suere that the computer doesn't unnecessarily sort contents

	unsigned int findChapter(chapter * c, unsigned int low, unsigned int high) const;
	unsigned int findChapter(chapter * c, unsigned int low, unsigned int high) const;
	unsigned int findChapter(string s) const;
	unsigned int sortChapter(chapter * c, unsigned int low, unsigned int high);


	unsigned int sortedFindTitle(string title, unsigned int low, unsigned int high) const;
		//searches for a title given that the title is sorted
	unsigned int sortedFindContent(string content, unsigned int low, unsigned int high) const; 
		//searches for a content given that content is sorted
	
	unsigned int partitionTitle(unsigned int low, unsigned int hi);
		// helps with sorting titles
	unsigned int partitionContents(unsigned int low, unsigned int hi);
		// helps with sorting contents
	void swap(unsigned int i, unsigned int j);
		// swaps both titles and contents
	void sortTitles(unsigned int low, unsigned int hi); // sorts titles only
	void sortContents(unsigned int low, unsigned int hi); // sorts contents only

	void unsort(); // turns both titles sorted and contentsSorted to false
	void sorted(bool & trueSorted, bool & falseSorted); // turns one true and the other false

	//TODO: MAKE A CHECK TO SEE IF TITLES / CONTENTS ARE SORTED
	//TODO: MAKE CHAPTER CLASS AND MAKE IT SO THAT IT'S A VECTOR OF CHAPTERS INSTEAD
public:
	const string DEFAULT_TITLE = "Untitled";

	Description(vector<string>titles = {}, vector<string>content = {});

	vector<string> getTitles() const;
	vector<string> getContent() const;
	string * getChapter(unsigned int i);

	string getTitleAt(unsigned int i) const;
	string getContentAt(unsigned int i) const;

	void setChapter(unsigned int i, string title, string content);
	void setTitles(vector<string>titles);
	void setTitleAt(unsigned int i, string title);
	void setContents(vector<string>contents);
	void setContentAt(unsigned int i, string content);

	void swapTitlesOnly(unsigned int i, unsigned int j);
	void swapTitlesOnly(string title1, string title2);

	void sortTitles();
	void sortContents();

	bool add(string contents = "", string title = "");

	unsigned int findTitle(string title) const;
	unsigned int findContent(string content) const;

	unsigned int sortAndSearchTitle(string title); //does a sorted search on title
		//if the list isn't sorted, it will sort it for you
	unsigned int sortedSearchTitle(string title) const; //same as normal counterpart
		//but it doesn't sort the list for you. Just returns -1
	unsigned int sortAndSearchContent(string content); //does a sorted search on content
		//if the list isn't sorted, it will sort it for you
	unsigned int sortedSearchContent(string content) const; //same as normal counterpart
		//but it doesn't sort the list for you. Just returns -1

	bool quickFindTitle(string title) const; //just tells whether or not the title exists
		//will not make any edits to original
	bool quickFindContent(string content) const; //just telss whether or not the content exists
		//will not make any edits to original
	
	bool removeChapter(string title); //removes title to list
		//actually just makes a blank title

	//TODO: MAKE INPUT AND OUTPUT FUNCTIONS
	void output(ostream & os);
};

//TODO: MAKE OPERATORS FOR << AND >>

#endif

