#include "maininterface.h"
#include "description.h"
#include "chapter.h"
#include <iostream>

using namespace std;

void display(chapter * c);

int main()
{
#if 1
	MainInterface n;
	n.play(cout, cin);
	return 0;
#endif
#if 0
	
	description c;

	c.insertChapter("title", "content");
	c.insertChapter("What is this", "This is sparta");
	c.insertChapter("we", "people");
	c.output(cout);
#endif
#if 0
	chapter * c = new chapter("a");
	chapter * d = new chapter("b");
	chapter * e = new chapter("c");

	c->setNextChapter(d);
	d->setNextChapter(e);
	d->setNextChapter(e);


	display(c);
	cout << endl;
	display(d);
	cout << endl;
	display(e);
	cout << endl;
	//d.setPrevChapter(&c);
	//d.setNextChapter(&e);
	//e.setPrevChapter(&d);
	//c->swapNextChapters(d);
	//d->swapPrevChapters(c);
	cout << *c;// *c->getNextChapter() << endl;// << *c->getNextChapter()->getPrevChapter() << endl;

	e->setChapterAfter(c);

	display(c);
	cout << endl;
	display(d);
	cout << endl;
	display(e);
	cout << endl;
	//cout << *d << endl;
	//cout << *d->getNextChapter() << endl;
	delete c;
	delete d;
	delete e;
#endif


	int dummyVal;
	cout << "Please type anything and press enter to exit" << endl;
	cin >> dummyVal;
	return 0;
}

void display(chapter * c)
{
	if (c->getPrevChapter() == nullptr) cout << 0 << ' ' ;
	else cout << c->getPrevChapter()->getTitle() << ' ';
	if (c == nullptr) cout << 0 << ' ';
	else cout << c->getTitle() << ' ';
	if (c->getNextChapter() == nullptr) cout << 0 << ' ';
	else cout << c-> getNextChapter()->getTitle() << ' ';
}