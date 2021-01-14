#include "SIParser.h"

using namespace SIMPLE;

SIParser::SIParser(const SIString& filename) {
	try {
		this->iniFile.open(filename, std::ios::in);

		this->loadINI();
	}
	catch (const fstream::failure& fail) {
		throw(fail);//throw the exception out to let the user handle it, to let them know what good thing they have done...
	}

}

SIParser::~SIParser() {
	//clear up and close the file stream
	if (this->iniFile.is_open()) {
		this->iniFile.close();
	}
}

SIStorage& SIParser::get() {
	return this->iniSettings;
}

void SIParser::loadINI() {
	//storage variable
	SISection currentSec;
	SIString line, sectionName = SIMPLE::DEFAULT_SECTION, nextSecName;//since default section must be at the first line

	//read line by line
	while (getline(this->iniFile, line)) {
		//if this is an empty line, we skip
		if (line == "") {
			continue;
		}

		//otherwise we check the starting point of the line to determine what we are going to do
		switch (*line.begin()) {
		case '['://section line
			//check if the section has any syntax error
			nextSecName = this->parseSection(line);
			if (nextSecName == SIParser::SYNTAX_ERROR) {
				break;//we skip the section line, all following properties will be stored in previous section
			}
			//we store the previous section into the storage
			//if the section has already exist, the previous old section will be discarded
			(this->iniSettings += sectionName) = currentSec;
			//and clear the old section buffer, starting a new one
			sectionName = nextSecName;
			currentSec = SISection();
			break;

		case ';' || '#'://comment line
			if (!SIMPLE_PARSE_COMMENT) {
				break;
			}

		default://property line
			SIProperty currentProp = this->parseProperty(line);
			//syntax error checker
			if (currentProp.first == SIParser::SYNTAX_ERROR && currentProp.second == SIParser::SYNTAX_ERROR) {
				break;//we skip this line if there is syntax error
			}
			//note that if the key is duplicated, a new value will be written in anyway, such that the old value is discarded
			(currentSec += currentProp.first) = currentProp.second;
			break;
		}
	}
	//save the last section
	(this->iniSettings += sectionName) = currentSec;
	//clear up, if there is no default section we don't need to keep it
	if (this->iniSettings[SIMPLE::DEFAULT_SECTION].getNumProperty() == 0) {
		this->iniSettings -= SIMPLE::DEFAULT_SECTION;
	}
}

SIProperty SIParser::parseProperty(const SIString line) {
	//key=value
	//such that we only need to find the location where (=) is located
	const auto Loc = line.find_first_of('=');
	if (Loc == std::string::npos) {
		//= not found, the ini has some syntax error
		return SIProperty(SIParser::SYNTAX_ERROR, SIParser::SYNTAX_ERROR);
	}
	//substring to get the key and value
	const SIString key = line.substr(0, Loc);
	const SIString value = line.substr(Loc + 1);

	return SIProperty(key, value);
}

const SIString SIParser::parseSection(const SIString line) {
	//[section]
	//so we only need to remove the surrounded square bracket
	if (*line.begin() != '[' || *(line.end() - 1) != ']') {
		//syntax error, square bracket is not complete
		return SIParser::SYNTAX_ERROR;
	}

	const auto size = line.length();
	return line.substr(1, size - 2);
}