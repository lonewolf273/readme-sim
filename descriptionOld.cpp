#include "descriptionOld.h"
#include <cassert>
#include <string>
#include <iostream>
#include <vector>

//Private methds
unsigned int Description::findChapter(chapter * c, unsigned int low, unsigned int high) const
{
	//finds chapters
	if (low < high)
	{
		unsigned int mid = (high + low) / 2;
		if (&c == &chapters_[mid]) return mid;
		if (&c > &chapters_[mid]) return findChapter(c, mid + 1, high);
	}
	if (low == high)
		if (&c == &chapters_[low])
			return low;
	return -1;
}


void Description::unsort()
{
	titlesSorted = false;
	contentsSorted = true;
}

void Description::sorted(bool & trueSorted, bool & falseSorted)
{
	trueSorted = true;
	falseSorted = false;
}

unsigned int Description::sortedFindTitle(string title, unsigned int low, unsigned int hi) const
{
	if (low <= hi)
	{
		if (low == hi) return title == titles_[low] ? low : -1;
		
		unsigned int mid = (low + hi) / 2;

		if (titles_[mid] == title) return mid;
		if (titles_[mid] > title) return sortedFindTitle(title, low, mid - 1);
		if (titles_[mid] < title) return sortedFindTitle(title, mid + 1, low);
	}
	return -1;
}

unsigned int Description::sortedFindContent(string content, unsigned int low, unsigned int hi) const
{
	if (low <= hi)
	{
		if (low == hi) return content == content_[low] ? low : -1;

		unsigned int mid = (low + hi) / 2;

		if (content_[mid] == content) return mid;
		if (content_[mid] < content) return  sortedFindContent(content, low, mid - 1);
		if (content_[mid] > content) return sortedFindContent(content, mid + 1, hi);
	}
	return -1;
}

//TODO: WORK ON FIND CONTENTS, SORTS, AND PUBLIC FIND/SORT

void Description::sortTitles(unsigned int low, unsigned int hi)
{
		if (low < hi)
		{
			int p = partitionTitle(low, hi);
			sortTitles(p + 1, hi);
			sortTitles(low, p - 1);
			
			sorted(titlesSorted, contentsSorted);
		}
}

void Description::sortContents(unsigned int low, unsigned int hi)
{
	if (low < hi)
	{
		int p = partitionContents(low, hi);
		sortContents(p + 1, hi);
		sortContents(low, p - 1);
	
		sorted(titlesSorted, contentsSorted);
	}
}

unsigned int Description::partitionTitle(unsigned int low, unsigned int hi)
{
	string pivot = titles_[low];
	int i = low;
	int j = hi + 1;
	while (true) //infinite loop until it can return
	{
		do
		{
			++i;
		} while (titles_[i] < pivot);
		do
		{
			--j;
		} while (titles_[j] > pivot);
		if (i >= j) return j;
		swap(i, j);
	}
}

unsigned int Description::partitionContents(unsigned int low, unsigned int hi)
{
	string pivot = content_[low];
	int i = low;
	int j = hi + 1;
	while (true)
	{
		do
		{
			++i;
		} while (content_[i] < pivot);

		do
		{
			--j;
		} while (content_[j] > pivot);
		if (i >= j) return j;
		swap(i, j);
	}
}

void Description::swap(unsigned int low, unsigned int hi)
{
	string _temp = titles_[low];
	titles_[low] = titles_[hi];
	titles_[hi] = _temp;

	_temp = content_[low];
	content_[low] = content_[hi];
	content_[hi] = _temp;

	unsort();
}

bool Description::quickFindTitle(string title) const
{
	Description d(titles_, content_);
	d.sortTitles(0, d.titles_.size() - 1);
	return (d.sortedFindTitle(title, 0, d.titles_.size() - 1) != -1);
}

bool Description::quickFindContent(string content) const
{
	Description d(titles_, content_);
	d.sortContents(0, d.content_.size() - 1);
	return (d.sortedFindContent(content, 0, d.content_.size() - 1) != -1);
}

Description::Description(vector<string>titles, vector<string>content)
{
	titles_ = titles;
	content_ = content;
	unsort();
}

vector<string> Description::getTitles() const
{
	return titles_;
}
vector<string> Description::getContent() const
{
	return content_;
}

string* Description::getChapter(unsigned int i)
{
	if (chapter_ != oldChapter_)
	{
		titles_[chapterIndex_] = chapter_[chapterIndex_];
		content_[chapterIndex_] = chapter_[chapterIndex_];
	}
	chapter_[0] = titles_[i];
	chapter_[1] = content_[i];
	oldChapter_[0] = chapter_[0];
	oldChapter_[1] = chapter_[1];
	chapterIndex_ = i;
	return chapter_;
}


string Description::getTitleAt(unsigned int i) const
{
	return titles_[i];
}

string Description::getContentAt(unsigned int i) const
{
	return content_[i];
}

void Description::setChapter(unsigned int i, string title, string content)
{
	assert(i < titles_.size());

	setTitleAt(i, title);
	setContentAt(i, content);
	unsort();
}
void Description::setTitles(vector<string>titles)
{
	int size = titles.size() - titles_.size();
	// size == 0 when they're the same size
	// size > 0 when you pass in a larger vector
	// size < 0 when you pass in a smaller vector

	titles_ = titles;
	for (int i = 0; i < size; i++) content_.push_back("");
	for (int i = 0; i > size; i--) titles_.push_back(DEFAULT_TITLE);
	unsort();

}

void Description::setTitleAt(unsigned int i, string title)
{
	assert(i < titles_.size());
	
	Description d(titles_, content_);

	if (d.findTitle(title) == -1)
	{
		titles_[i] == title;
	}
	unsort();
}

void Description::setContents(vector<string>contents)
{
	int size = contents.size() - content_.size();
	// size == 0 when they're the same size
	// size > 0 when you pass in a larger vector
	// size < 0 when you pass in a smaller vector

	content_ = contents;
	for (int i = 0; i > size; i++) content_.push_back("");
	for (int i = 0; i < size; i--) titles_.push_back(DEFAULT_TITLE);
	unsort();
}

void Description::setContentAt(unsigned int i, string content)
{
	assert(i < content_.size());
	content_[i] = content;
}

void Description::swapTitlesOnly(unsigned int i, unsigned int j)
{
	string _temp = titles_[i];
	titles_[i] = titles_[j];
	titles_[j] = _temp;

	unsort();

}

void Description::swapTitlesOnly(string title1, string title2)
{
	Description d(titles_, content_);

	int t1 = d.findTitle(title1);
	int t2 = d.findTitle(title2);

	unsort();
}

void Description::sortTitles()
{
	if (titlesSorted) return;

	sortTitles(0, titles_.size() - 1);
	sorted(titlesSorted, contentsSorted);
}

void Description::sortContents()
{
	if (contentsSorted) return;
	sortContents(0, content_.size() - 1);
	sorted(contentsSorted, titlesSorted);
}

bool Description::add(string title, string contents)
{
	if (title == "") title = DEFAULT_TITLE;

	if (quickFindTitle(title))
	{
		if (blanks_.size() == 0)
		{
			content_.push_back(contents);
			titles_.push_back(title);
			unsort();
			return true;
		}
		else
		{
			titles_[blanks_[blanks_.size() - 1]] = title;
			content_[blanks_[blanks_.size() - 1]] = contents;
		}
	}
	return false;
}

unsigned int Description::findTitle(string title) const
{
	if (title == "" || title == DEFAULT_TITLE) return -1;
	
	if (titlesSorted) return sortedSearchTitle(title);
	

	unsigned int i = 0;
	unsigned int j = titles_.size() - 1;
	while (true)
	{
		if (i > j) return -1;

		if (titles_[i] == title) return i;
		else ++i;

		if (titles_[j] == title) return j;
		else --j;
	}
	return -1;
}

unsigned int Description::findContent(string content) const
{
	if (content == "") return -1;
	if (contentsSorted) return sortedSearchContent(content);

	unsigned int i = 0;
	unsigned int j = titles_.size() - 1;
	while (true)
	{
		if (i > j) return -1;
		
		if (content_[i] == content) return i;
		i++;

		if (content_[j] == content) return j;
		j--;
	}
	return -1;
}

unsigned int Description::sortAndSearchTitle(string title)
{
	if (!titlesSorted) sortTitles(0, titles_.size() - 1);

	return sortedFindTitle(title, 0, titles_.size() - 1);
}

unsigned int Description::sortedSearchTitle(string title) const
{
	if (!titlesSorted) return -1;

	return sortedFindTitle(title, 0, titles_.size() - 1);
}

unsigned int Description::sortAndSearchContent(string content)
{
	if (!contentsSorted) sortContents(0, content_.size() - 1);
	
	return sortedFindContent(content, 0, content_.size() - 1);
}

unsigned int Description::sortedSearchContent(string content) const
{
	if (!contentsSorted) return -1;
	return sortedFindContent(content, 0, content_.size() - 1);
}

bool Description::removeChapter(string title)
{
	if (title == "") return false;
	int index = findTitle(title);
	
	if (index == -1) return false;
	setTitleAt(index, "");
	setContentAt(index, "");
	unsort();
	return true;
}