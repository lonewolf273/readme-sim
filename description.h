#ifndef _DESCRIPTION_H
#define _DESCRIPTION_H

#include <vector>
#include <map>

using namespace std;

class Description
{
private:
	vector<string>titles_;
	vector<string>content_;

	

	unsigned int chapterIndex_ = -1;
	map<string, string> chapters_;
	string oldChapter_[2] = { "", "" };
	string chapter_[2] = { "", "" };
	bool titlesSorted = false;
	bool contentsSorted = false;

	unsigned int sortedFindTitle(string title, unsigned int low, unsigned int high) const;
	unsigned int sortedFindContent(string content, unsigned int low, unsigned int high) const;
	
	unsigned int partitionTitle(unsigned int low, unsigned int hi);
	unsigned int partitionContents(unsigned int low, unsigned int hi);

	void swap(unsigned int i, unsigned int j);

	void sortTitles(unsigned int low, unsigned int hi);
	void sortContents(unsigned int low, unsigned int hi);

	void unsort();
	void sorted(bool & trueSorted, bool & falseSorted);



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
};

#endif

