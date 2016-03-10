/*
	@file:		chapter.cpp
	@author:	Vincent Mills
	@version:	v. 0.2.1
	@date:		2 March 2016
*/

#include "chapter.h"
#include <iostream>
#include <sstream>
#include <cassert>


chapter::chapter(string title, string content)
{
	title_ = title;
	content_ = content;
	chapterNumber_ = -1;

	nextChapter_ = nullptr; //there's no next chapter or prev chapter for now
	prevChapter_ = nullptr;
}

chapter::chapter(const chapter & c)
{
	title_ = c.getTitle();
	content_ = c.getContent();
	nextChapter_ = c.getNextChapter();
	prevChapter_ = c.getPrevChapter();
	chapterNumber_ = c.chapterNumber_;
}

chapter::~chapter()
{
	if (nextChapter_ != nullptr)
		nextChapter_ = nullptr;
	if (prevChapter_ != nullptr)
		prevChapter_ = nullptr;
}

string chapter::getTitle() const
{
	return title_;
}

string chapter::getContent() const
{
	return content_;
}

chapter * chapter::getNextChapter() const
{
	return nextChapter_;
}

chapter * chapter::getPrevChapter() const
{
	return prevChapter_;
}

chapter * chapter::getNextChapter()
{
	return nextChapter_;
}
chapter * chapter::getPrevChapter()
{
	return prevChapter_;
}

void chapter::setTitle(string title)
{
	title_ = title;
}

void chapter::setContent(string content)
{
	content_ = content;
}

void chapter::setNextChapter(chapter * next)
{
	if (next == nextChapter_) return;
	nextChapter_ = next;
	if (next != nullptr) next->setPrevChapter(this);
}

void chapter::setPrevChapter(chapter * prev)
{
	if (prev == prevChapter_) return;
	prevChapter_ = prev;
	if (prev != nullptr)
	{
		prev->setNextChapter(this);
	}
}

void chapter::swapChapters(chapter * c)
{
	assert(*this != *c);

	chapter * input[4] =
	{
		prevChapter_,
		nextChapter_,
		c->getNextChapter(),
		c->getPrevChapter()
	};
	if (nextChapter_ == c)
	{
		c->setPrevChapter(input[0]);
		c->setNextChapter(this);
		setNextChapter(input[2]);
	}
	else if (prevChapter_ == c)
	{
		c->setPrevChapter(this);
		c->setNextChapter(input[1]);
		setPrevChapter(input[3]);
	}
	else
	{
		setPrevChapter(input[3]);
		setNextChapter(input[2]);
		c->setNextChapter(input[1]);
		c->setPrevChapter(input[0]);
	}
}

void chapter::setChapterBefore(chapter * c)
{
	assert(*this != *c);
	if (nextChapter_ == c) return; //leave if c is already ahead of the chapter
	if (prevChapter_ == c) //swap if they're right next to each other
	{
		swapChapters(c);
		return;
	}
	chapter * input[4] =
	{
		prevChapter_,
		nextChapter_,
		c->getNextChapter(),
		c->getPrevChapter()
	};
	//fills in the gap between next and previous
	if (nextChapter_ != nullptr)
		input[1]->setPrevChapter(input[0]);
	else if (prevChapter_ != nullptr)
		input[0]->setNextChapter(input[1]);

	setNextChapter(c);
	setPrevChapter(input[3]);
}

void chapter::setChapterAfter(chapter * c)
{
	assert(*this != *c);
	if (prevChapter_ == c) return; //leave if c is already ahead of the chapter
	if (nextChapter_ == c) //swap if they're right next to each other
	{
		swapChapters(c);
		return;
	}

	chapter * input[4] =
	{
		prevChapter_,
		nextChapter_,
		c->getNextChapter(),
		c->getPrevChapter()
	};
	//fills in the gap between next and previous
	if (nextChapter_ != nullptr)
		input[1]->setPrevChapter(input[0]);
	else if (prevChapter_ != nullptr)
		input[0]->setNextChapter(input[1]);

	//align two chapters
	setPrevChapter(c);
	setNextChapter(input[2]);
}

string chapter::toString() const
{
	ostringstream os;
	os << title_ << endl;
	os << content_ << endl;

	return os.str();
}


bool chapter::isEqualTo(const chapter & c) const
{
	return title_ == c.getTitle();
}

bool chapter::isLessThan(const chapter & c) const
{
	return title_ < c.getTitle();
}

void chapter::output(ostream & os) const
{
	os << toString();
}

bool operator==(const chapter & c, const chapter & d)
{
	return c.isEqualTo(d);
}

bool operator!=(const chapter & c, const chapter & d)
{
	return !(c == d);
}

bool operator<(const chapter & c, const chapter & d)
{
	return (c.isLessThan(d));
}
bool operator<=(const chapter & c, const chapter & d)
{
	return c < d && c == c;
}
bool operator>(const chapter & c, const chapter & d)
{
	return !(c <= d);
}

bool operator>=(const chapter & c, const chapter & d)
{
	return !(c < d);
}
ostream & operator<<(ostream & os, const chapter & c)
{
	c.output(os);
	return os;
}