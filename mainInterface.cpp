#include <iomanip>
#include <sstream>
#include <direct.h>
#include "mainInterface.h"
#include "menuoptions.h"



///////////////////////////
//
//		CONSTRUCTORS
//
///////////////////////////
MainInterface::MainInterface()
{
	fileName_ = "";
}

///////////////////////////
//
//		INSPECTORS
//
///////////////////////////
string MainInterface::getFileName() const
{
	return fileName_;
}

Readme MainInterface::getReadMe() const
{
	return readme_;
}

string MainInterface::introduction()
{
	string s = "";

	s += "Welcome to the READ_ME creation program. \n";
	s += "This is version number " + versionNumber_ + ". \n";
	s += "If you have any questions and concerns, please go to the \" Contact Us \" section to help this get better! \n \n";

	return s;
}

MenuOptions MainInterface::getCurrentOption()
{
	return currentOption_;
}

///////////////////////////
//
//		MUTATORS
//
///////////////////////////
void MainInterface::setFileName(string fileName)
{
	if (fileName != "") fileName_ = fileName;
	if (fileName.find(".") == -1) fileName_ += ".txt";
}


void MainInterface::setReadMe(Readme r)
{
	readme_ = r;
}

void MainInterface::setCurrentOption(MenuOptions m)
{
	currentOption_ = m;
}
///////////////////////////
//
//		FACILITATORS
//
///////////////////////////	

void MainInterface::clearStream(istream & is)
{
	is.sync();
}

void MainInterface::play(ostream & os, istream & is)
{
	savedFile_ = true; //you technically saved a file that you never loaded
	os << endl << introduction();
	os << endl << endl;

	mainMenu(os, is);
}

void MainInterface::mainMenu(ostream & os, istream & is)
{
	string input;
	clearStream(is);
	while (true)
	{
		currentOption_ = MAIN_MENU;
		os << "Please pick a menu option from the list. Please pick a number or type HELP for help" << endl << endl;

		int j = 0;
		for (unsigned int i = 0; i < currentOption_.maxSize(); i++)
		{
			if (i != currentOption_)
			{
				os << setw(2) << ++j << ") " << MenuOptions(i) << endl;
			}
		}
		os << endl;

		string input = requestInput(os, is);

		if (input == MenuOptions(SAVE_FILE).indexToString() || input == lower(MenuOptions(SAVE_FILE).toString()))
		{
			savedFile_ = save(os, is);
		}
		else if (input == MenuOptions(LOAD_FILE).indexToString() || input == lower(MenuOptions(LOAD_FILE).toString()))
		{
			loadedFile_ = load(os, is);
		}
		else if (input == MenuOptions(CREATE_FILE).indexToString() || input == lower(MenuOptions(CREATE_FILE).toString()))
		{
			_mkdir("projects");
			loadedFile_ = create(os, is);
		}
		else if (input == MenuOptions(ADD_ITEM).indexToString() || input == lower(MenuOptions(ADD_ITEM).toString()))
		{
			addItem(os, is);
		}
		else if (input == MenuOptions(PUBLISH_FILE).indexToString() || input == lower(MenuOptions(PUBLISH_FILE).toString()))
		{
			_mkdir("publishedFiles");
			savedFile_ = publish(os, is);
		}
		else if (input == MenuOptions(HELP).indexToString() || input == lower(MenuOptions(HELP).toString()))
		{
			help(os, input);
		}
		else if (input == MenuOptions(QUIT).indexToString() || input == lower(MenuOptions(QUIT).toString()))
		{
			if (quit(os, is)) return;
		}
		else if (input == MenuOptions(DISPLAY_CONTENT).indexToString() || input == lower(MenuOptions(DISPLAY_CONTENT).toString()))
		{
			viewReadme(os, is);
		}
		else if (input == MenuOptions(VIEW_README).indexToString() || input == lower(MenuOptions(VIEW_README).toString()))
		{
			viewReadme(os, is);
		}
	}
}

void MainInterface::addItem(ostream & os, istream & is)
{
	currentOption_ = ADD_ITEM;
	if (!loadedFile_)
	{
		os << "Sorry but you have not loaded a file. Please load a file and try again." << endl;
		return;
	}
	do
	{
		os << "Welcome to the adding process. This is where you get to add either a section or a description to your readme." << endl << endl;
		string input;

		os << "What would you like to add: " << endl;
		os << "1) Section" << endl;
		os << "2) Chapter" << endl;
		os << "3) Help" << endl;

		os << endl;

		is >> input;

		while (true)
		{
			if (lower(input) == "quit")
			{
				return;
			}
			else if (lower(input) == "section" || input == "1") addSection(os, is);
			else if (lower(input) == "chapter" || input == "2") addChapter(os, is);
			else if (lower(input) == "help" || input == "3")
			{
				//TODO: EXPAND HELP SECTION
				os << "This is for adding parts of of the section for you." << endl;
			}
			else
				os << "Invalid choice. Please try again." << endl;

			os << "What would you like to add: " << endl;
			os << "1) Section" << endl;
			os << "2) Chapter" << endl;
			os << "3) Help" << endl;
			os << "Quit" << endl;
			is >> input;
		}
	}while (true);
}

void MainInterface::addChapter(ostream & os, istream & is)
{
	string title;
	os << "Please give a title for this chapter: " << endl;
	is >> title;
	if (lower(title) == "quit") return;
	
	string contents; //the current paragraph of contents
	ostringstream ostr; //for parsing the entire chapter in the readme
	do
	{
		os << "Please give your paragraph of text. If you are done adding chapters, simply type \"++++\":" << endl;
		getline(is, contents);
		if (contents != "++++")
		{
			ostr << contents << endl;
		}
	} while (contents != "++++");
	readme_.addChapter(title, ostr.str());
	savedFile_ = false;
}

void MainInterface::addSection(ostream & os, istream &is)
{
	string content;
	os << "Please give the content name: ";
	is >> content;

	if (lower(content) == "quit") return;

	string location;
	os << "Please give the loation name: ";
	is >> location;
	if (lower(location) == "quit") return;

	string section;
	os << "Please give the section name: ";
	is >> section;
	if (lower(section) == "quit") return;

	if (readme_.findSection(content) != -1)
	{
		os << "Error: section already found: " << endl;
		os << readme_.getSectionAt(readme_.findSection(content));
	}
	else
	{
		readme_.addSection(content, location, section);
		os << "Success! Your file was added!" << endl;
		if (readme_.findSection(content) == -1)
		{
			os << "Wait.... take that back. something went wrong" << endl;
			os << "The size is: " << readme_.getTable().size() << endl;
		}
		savedFile_ = false;
		changedFile_ = true;
	}
}

void MainInterface::viewReadme(ostream & os, istream & is)
{
	os << readme_ << endl;
}
bool MainInterface::load(ostream & os, istream & is)
{
	currentOption_ = LOAD_FILE;

	string fileName;
	do
	{
		os << endl;
		os << "Welcome to the loading process. If you already have an existing file, please give the file name for us to load." << endl;
		os << "If you don\'t already have a file and wanted to create one, please say \"QUIT\" to go back to the main menu." << endl;

		fileName = requestInput(os, is, "What is your file\'s name (including extension)?");

		if (fileName == "help")
		{
			help(os, "help");
		}
	} while (fileName == "help");
	if (lower(fileName) == "quit") return loadedFile_;
	if (fileName.find('.') == -1) fileName.append(".txt");

	os << endl;

	os << endl << "Loading " << fileName << "..." << endl;
	string s = PROJECT_DIR + fileName;
	bool check = readme_.load(s);
	if (check)
	{
		os << "Congratulations! Your file was loaded!" << endl;
		fileName_ = fileName;
	}
	else
	{
		os << "There was something wrong with loading the file." << endl;
		os << "Maybe you've misspelled the file name or gave the wrong section." << endl;
		os << "Or maybe the file doesn't exist in the first place." << endl;
		os << "Please check your file name and try again from the main menu. " << endl;
	}
	return check;
}

bool MainInterface::create(ostream & os, istream & is)
{
	currentOption_ = CREATE_FILE;
	string fileName;
	os << endl;
	os << "Welcome to the file creating process. If you haven\'t created a file already, please give the file name for us to crate." << endl;
	os << "If you already have a file and wanted to load it, or you went to the wrong section, please say \"QUIT\" when prompted." << endl;

	fileName = requestInput(os, is, "What is your file\'s name (including extension)?");

	if (fileName == "quit") return loadedFile_;

	if (fileName.find('.') == -1) fileName += ".txt";

	if (readme_.fexists(PROJECT_DIR + fileName))
	{
		os << "Sorry, " << fileName << " is unavailable to create right now. It seems to be already created at an earlier time." << endl;
		os << "Please try again, or use " << MenuOptions(LOAD_FILE) << " to load in the file." << endl;
		return loadedFile_;
	}
	readme_.setFileName(fileName);
	if (readme_.create(PROJECT_DIR + fileName))
	{
		os << "Congratulations." << endl;
		os << "Your file, " << fileName << " was saved and loaded for future use." << endl;
		fileName_ = fileName;
		savedFile_ = true;
		loadedFile_ = true;
		return true;
	}
	else
	{
		os << "There was an error with creating your file." << endl;
		os << "Maybe we tried to create a file that exists and that\'s read-only?" << endl;
		os << "I don't know. Try again later I guess." << endl;
		return false;
	}
}

bool MainInterface::save(ostream & os, istream & is)
{
	currentOption_ = SAVE_FILE;
	os << endl;

	if (!loadedFile_)
	{
		os << "You have not loaded nor created a file. Please load/create a file before saving." << endl;
		return false;
	}

	string s;
	do
	{
		os << endl << "Are you sure you want to save? " << endl;
		os << "Say \"y\" for yes or \"n\" for no: ";
		is >> s;
		os << endl << endl;
	} while (!validateInput(s));

	if (s == "n" || s == "quit") return savedFile_;
	os << endl;
	os << endl << "Saving " << fileName_ << endl;
	bool check = readme_.save(PROJECT_DIR + fileName_);
	if (check)
	{
		os << "Congratulations! Your file was saved!" << endl;
	}
	else
	{
		os << "There was something wrong with saving the file." << endl;
		os << "Maybe you've misplaced the file or turned it read-only." << endl;
		os << "Please check your file and try again from the main menu. " << endl;
	}
	return check;
}

bool MainInterface::publish(ostream & os, istream & is)
{
	currentOption_ = PUBLISH_FILE;
	os << endl;

	if (!loadedFile_)
	{
		os << "You have not loaded nor created a file. Please load/create a file before publishing." << endl;
		return false;
	}

	string s;
	os << endl << "Welcome to the file publishing process. If you want your file completely published for use, please give the file name for us to publish." << endl;
	if (!savedFile_)
	{
		os << "We've noticed that you haven\'t saved your file since your last set of changes." << endl;
		os << endl << "Would you like to save your changes now? " << endl;
		s = requestInput(os, is, "saving");
		if (s == "y")
		{
			if (!save(os, is))
				return false;
		}
		else if (s == "quit") return loadedFile_;
	} 
	os << endl;
	string fileName = requestInput(os, is, "What is the name of the file that you woule like to publish?");

	if (fileName.find('.') == -1) fileName += ".txt";
	if (readme_.publish(PUBLISH_DIR + fileName))
	{
		os << endl << "Congratulations! Your file has been published for reading!" << endl;
		os << endl << "Please note that files created this way will not be able to go back to their old project files." << endl;
		os << endl << "Please get your new file at " << fileName << "." << endl;
	}

	return false;
}

void MainInterface::help(ostream & os, string s)
{
	if (currentOption_ == MAIN_MENU)
	{
		currentOption_ = HELP;
		os << endl << "This program is for creating and editing a readme file for your convenience." << endl;
		os << "For help on specific secitons, please say \"help\" inside that section." << endl;
	}
	else if (currentOption_ == LOAD_FILE)
	{
		os << endl << "This is the loading process. If you already created a file prior and haven\'t loaded it in yet, you may do so here." << endl;
		os << "Just simply give us the file name and we will load it up for you." << endl;
		os << "NOTE: If you haven\'t created a file prior, please do so in the \"CREATE FILE\" option in the main menu." << endl;
	}
}

bool MainInterface::quit(ostream & os, istream & is)
{
	currentOption_ = QUIT;

	char op;
	if (!savedFile_)
	{
		os << "Would you like to save your file first? 'y' or 'n': " << endl;
		is >> op;
		while (op != 'y' && op != 'n' && op != 'Y' && op != 'N')
		{
			os << "invalid option. try again." << endl;
			os << "Would you like to save your file first? 'y' or 'n': " << endl;
			is >> op;
		}
		if (op == 'y' || op == 'Y')
		{
			save(os, is);
		}
	}
	string s;
	do
	{
		os << endl << "Are you sure you want to quit? " << endl;
		os << "Say \"y\" for yes or \"n\" for no: ";
		is >> s;
		os << endl << endl;
	} while (!validateInput(s));

	if (s == "y") return true;
	return false;
}

//request the input from the user
string MainInterface::requestInput(ostream & os, istream & is, string question)
{
	string s;
	bool validated = false;
	while (true)
	{
		if (question == "")
			os << "What would you like to do? ";
		else if (question == "saving")
			os << ' ';
		else
			os << question << ' ';
		getline(is, s);
		s = s.substr(0, s.find(' '));
		validated = question == "saving" ? validateInput(s) : validateInput(s, question);
		clearStream(is);
		if (!validated)
			os << "Invalid choice. Pick another option. " << endl;
		else return lower(s);
	}
}

//turns the input to lowercase
string MainInterface::lower(string s) const
{
	const char LOWER = 'A' - 'a';
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z') s[i] -= LOWER;
	}
	return s;
}


//checks if the input is valid
bool MainInterface::validateInput(string & s, string process)
{
	s = lower(s);
	if (s == "quit") return true;

	if (currentOption_ == MAIN_MENU)
	{
		if (s[0] >= '1' && static_cast<unsigned int>(s[0]) <= '1' + (currentOption_.maxSize() - 1))
			return true;
		
		if (s == "help") 
			return true;
		
		if (s == "quit") 
			return true;

		if (s == "load" || s == "save" || s == "create" || s == "publish")
		{
			s += " file";
			return true;
		}
		if (s == "view")
		{
			s += " readme";
			return true;
		}

		if (s == "add")
		{
			s += " item";
			return true;
		}
	}
	if (currentOption_ == QUIT || currentOption_ == SAVE_FILE)
	{
		if (s == "y" || s == "n") return true;
	}
	if (currentOption_ == LOAD_FILE || currentOption_ == CREATE_FILE)
	{
		if (isAlpha(s, { '.', '\\'})) return true;
	}
	if (currentOption_ == PUBLISH_FILE)
	{
		if (process == "saving")
		{
			if (s == "y" || s == "n") return true;
		}
		else return true;
	}
	return false;
}

bool MainInterface::isAlpha(string s, vector<char> exceptions) const
{
	s = lower(s);
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s[i] < 'a' || s[i] > 'z')
		{
			bool isOkay = false;
			for (unsigned int j = 0; j < exceptions.size(); j++)
			{
				if (s[i] == exceptions[j]) isOkay = true;
			}
			if (!isOkay) return false;
		}
	}
	return true;
}