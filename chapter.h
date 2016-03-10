#pragma once

#ifndef CHAPTER_H
#define CHAPTER_H

#include <string>
#include <iostream>

using namespace std;
class chapter
{
private:
	string title_; //title of the chapter
	string content_; //contents within the chapter

	chapter * nextChapter_; //next chapter (not alphabetical)
	chapter * prevChapter_; //previous chapter (not alphabetical)
	
	int chapterNumber_;
public:

	chapter(string title = "", string content = ""); //default and alternate constructor
	chapter(const chapter & c); //copy constructor
	~chapter(); //destructor

	string getTitle() const; //returns the title of the chapter
	string getContent() const; //returns the content of the chapter
	chapter * getNextChapter() const; //returns the POINTER of the next chapter, constant
	chapter * getNextChapter(); //return the POINTER of the next chapter, not constant
	chapter * getPrevChapter(); //returns the POINTER of the previous chapter, not constant
	chapter * getPrevChapter() const; //returns the POINTER of the previous chapter, constant

	void setTitle(string title); //sets the title
	void setContent(string content); //sets the content
	void setNextChapter(chapter * next); //sets the pointer of the next chapter
	void setPrevChapter(chapter * prev); //sets the pointer of the previous chapter
	void swapChapters(chapter * c); //swap the two chapters
	void setChapterBefore(chapter * c); //sets the current chapter before the given chapter
	void setChapterAfter(chapter * c); //sets the current chapter after the given chapter

	bool isEqualTo(const chapter & c) const; //checks if both chapters are equal to
	bool isLessThan(const chapter & c) const; //checks if the chapters are less than

	string toString() const; //turns the chapter to a string
	void output(ostream & os) const; //outputs the chapter
};

bool operator==(const chapter & c, const chapter & d); //overloaded ==
bool operator>(const chapter & c, const chapter & d); //overloaded >
bool operator>=(const chapter & c, const chapter & d); //overloaded >=
bool operator<(const chapter & c, const chapter & d); //overloaded <
bool operator <=(const chapter & c, const chapter & d); //overloaded <=
bool operator != (const chapter & c, const chapter & d); //overloaded !=
ostream & operator<<(ostream & os, const chapter & c); //overloaded <<
#endif