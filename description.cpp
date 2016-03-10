#include <cassert>
#include "description.h"

///////////////////////////////
//
//	   Private Inspectors
//
///////////////////////////////

void description::fullSort()
{
	if (!isSorted_) sort(0, chapters_.size() - 1);
	isSorted_ = true;
}

chapter * description::getChapterPtrAt(unsigned int index)
{
	return chapters_[index];
}

chapter * description::getChapterPtrAt(unsigned int index) const
{
	return chapters_[index];
}

void description::sort(unsigned int low, unsigned int high)
{
		if (low < high)
		{
			unsigned int p = partition(low, high);
			sort(low, p - 1);
			sort(p + 1, high);
			
		}
}

unsigned int description::partition(unsigned int low, unsigned int high)
{
	
	chapter * pivot = chapters_[low];
	unsigned int i = low;
	unsigned int j = high + 1;
	while (true)
	{
		do
		{
			++i;
		} while (*chapters_[i] < *pivot);

		do
		{
			--j;
		} while (*chapters_[j] < *pivot);
		if (i >= j) return j;
		vectorSwap(i, j);
	}
}

void description::vectorSwap(unsigned int one, unsigned int two)
{
	
	chapter * _temp = chapters_[one];
	
	chapters_[one] = chapters_[two];
	chapters_[two] = _temp;
}



chapter * description::getCurrentChapterPtr() const
{
	return current_;
}

void description::setCurrentChapterPtr(chapter * c)
{
	current_ = c;
}

void description::setCurrentChapterPtr(unsigned int index)
{
	assert(index >= chapters_.size());
	current_ = chapters_[index];
}

void description::pointerSwap(unsigned int one, unsigned int two)
{
	if (head_ == chapters_[one])
	{
		head_ = chapters_[two];
	}
	else if (head_ == chapters_[two])
	{
		head_ = chapters_[one];
	}

	if (tail_ == chapters_[one])
	{
		tail_ = chapters_[two];
	}
	else if (tail_ == chapters_[two])
	{
		tail_ = chapters_[one];
	}

	chapters_[one]->swapChapters(chapters_[two]);

}

void description::pointerOverwrite(chapter * overwritten, chapter * overwriter)
{
	overwriter->setNextChapter(overwritten->getNextChapter());
	overwriter->setPrevChapter(overwritten->getPrevChapter());

	delete overwritten;
}

void description::insertChapters(vector<chapter *>c)
{
	for (unsigned int i = 0; i < c.size(); i++)
	{
		chapter * k = &(*c[i]);

		if (head_ == nullptr)
		{
			head_ = k;
			tail_ = k;
			chapters_.push_back(k);
			isSorted_ = true;
		}
		else if (find(*k, 0, chapters_.size() - 1) == -1)
		{
			tail_->setNextChapter(k);
			tail_ = k;
			chapters_.push_back(k);
		}
	}
	isSorted_ = head_ == tail_ || tail_ == nullptr;
	fullSort();
}

bool description::contains(string title) const
{
	chapter * k = new chapter(title);
	int i = find(title, 0, chapters_.size() - 1);
	delete k;
	return i != -1;
}

void description::insertChapter(chapter * c)
{
	if (head_ == nullptr)
	{
		head_ = &(*c);
		tail_ = &(*c);
		chapters_.push_back(&(*c));
		isSorted_ = true;
	}
	else if (find(*c, 0, chapters_.size() - 1) == -1)
	{
		tail_->setNextChapter(&(*c));
		tail_ = &(*c);
		chapters_.push_back(&(*c));
	}
}

unsigned int description::find(const chapter & c, unsigned int low, unsigned int high) const
{
	if (low <= high)
	{
		if (low == high) return c == *chapters_[low] ? low : -1;
		unsigned int mid = (low + high) / 2;
		if (c == *chapters_[mid]) return mid;
		if (c < *chapters_[mid]) return find(c, low, mid - 1);
		if (c > *chapters_[mid]) return find(c, mid + 1, high);
	}
	return -1;
}
///////////////////////////////
//
// Constructors and Destructors
//
///////////////////////////////

description::description()
{
	head_ = nullptr;
	tail_ = nullptr;
	current_ = nullptr;
	isSorted_ = true;
}

description::description(const description & d)
{
	int heading = d.find(*d.head_, 0, d.chapters_.size() - 1);
	int tailing = d.find(*d.tail_, 0, d.chapters_.size() - 1);
	int curr = d.find(*d.current_, 0, d.chapters_.size() - 1);

	insertChapters(d.chapters_);

	head_ = chapters_[heading];
	tail_ = chapters_[tailing];
	current_ = chapters_[curr];
}

description::description(vector<string>titles, vector<string>contents)
{
	head_ = nullptr;
	tail_ = nullptr;
	current_ = nullptr;
	isSorted_ = true;
	insertChapters(titles, contents);
}

description::description(vector<chapter>c)
{
	vector<chapter *> k(c.size());
	for (unsigned int i = 0; i < c.size(); i++)
	{
		k[i] = &c[i];
	}
	insertChapters(k);
	k.clear();
}

description::~description()
{
	if (chapters_.size() > 0)
	{
		for (unsigned int i = 0; i < chapters_.size(); i++)
		{
			delete chapters_[i];
			chapters_[i] = nullptr;
		}
	}
}


///////////////////////////////
//
//		  Inspectors
//
///////////////////////////////

chapter & description::getChapterAt(unsigned int index)
{
	return *chapters_[index];
}

chapter & description::getChapterAt(unsigned int index) const
{
	return *chapters_[index];
}

unsigned int description::size() const
{
	return chapters_.size();
}

chapter & description::getCurrentChapter() const
{
	return *getCurrentChapterPtr();
}

chapter & description::getNextChapter() const
{
	if (getCurrentChapter().getNextChapter() == nullptr)
		return *tail_;
	
	return *getCurrentChapter().getNextChapter();
}

chapter & description::getPrevChapter() const
{
	if (getCurrentChapter().getNextChapter() == nullptr)
		return *head_;
	
	return *getCurrentChapter().getPrevChapter();
}

chapter & description::operator[](unsigned int index)
{
	return getChapterAt(index);
}

chapter & description::operator[](unsigned int index) const
{
	return getChapterAt(index);
}

///////////////////////////////
//
//		  Mutators
//
///////////////////////////////
void description::insertChapters(vector<string>title, vector<string>contents)
{
	assert(title.size() >= contents.size());
	contents.resize(title.size(), "");
	for (unsigned int i = 0; i < title.size(); i++)
	{
		chapter * c = new chapter(title[i], contents[i]);

		if (head_ == nullptr)
		{
			head_ = c;
			tail_ = c;
			chapters_.push_back(c);
			isSorted_ = true;
		}
		else if (find(*c, 0, chapters_.size() - 1) == -1)
		{
			tail_->setNextChapter(c);
			tail_ = c;
			chapters_.push_back(c);
		}
		else
		{
			delete c;
		}
	}
	isSorted_ = false;
	fullSort();
}

void description::insertChapters(vector<string>descriptions)
{
  //TODO: MAKE INSERT CHAPTERS FUNCTIONALITY
}

void description::insertChapter(string title, string content)
{
	
	chapter * c = new chapter(title, content);

	if (head_ == nullptr)
	{
		head_ = &(*c);
		tail_ = &(*c);
		chapters_.push_back(&(*c));
		isSorted_ = true;
	}
	else if (find(*c, 0, chapters_.size() - 1) == -1)
	{
		tail_->setNextChapter(&(*c));
		tail_ = &(*c);
		chapters_.push_back(&(*c));
		
		isSorted_ = *c <= *tail_;
		fullSort();
	}
	else
	{
		delete c;
	}
}


void description::beginChapters()
{
	current_ = head_;
}

bool description::gotoNextChapter()
{
	if (current_->getNextChapter() == nullptr) return false;

	current_ = current_->getNextChapter();
	return true;
}

bool description::gotoPrevChapter()
{
	if (current_->getPrevChapter() == nullptr) return false;
	current_ = current_->getPrevChapter();
	return true;
}

bool description::deleteChapter(const chapter & c)
{
	int k = find(c, 0, chapters_.size() - 1);
	if (k == -1) return false;

	delete chapters_[k];
	chapters_[k] = nullptr;
	vectorSwap(k, chapters_.size() - 1);
	chapters_.pop_back();
	isSorted_ = false;
	fullSort();
	return true;
}

bool description::deleteChapter(string title)
{
	chapter c(title);
	deleteChapter(c);
	return true;
}

description & description::operator=(const description & d)
{
	int heading = d.find(*d.head_, 0, d.chapters_.size() - 1);
	int tailing = d.find(*d.tail_, 0, d.chapters_.size() - 1);
	int curr = d.find(*d.current_, 0, d.chapters_.size() - 1);

	insertChapters(d.chapters_);

	head_ = chapters_[heading];
	tail_ = chapters_[tailing];
	current_ = chapters_[curr];
	return *this;
}
///////////////////////////////
//
//		  Facilitators
//
///////////////////////////////
void description::output(ostream & os) const
{
	if (size() == 0)
	{
		return;
	}
	chapter * currentPtr = head_;
	os << *currentPtr << endl;
	while (currentPtr->getNextChapter() != nullptr)
	{
		currentPtr = currentPtr->getNextChapter();
		os << *currentPtr << endl;
	}
}

///////////////////////////////
//
//		  Operators
//
///////////////////////////////

ostream & operator<<(ostream & os, const description & d)
{
	d.output(os);
	return os;
}