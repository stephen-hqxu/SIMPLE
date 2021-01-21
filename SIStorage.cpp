#include "SIStorage.h"

using namespace SIMPLE;

SIStorage::SIStorage() {

}

SIStorage::SIStorage(SISectionTable sections) {
	this->sections = SISectionTable(sections);
}

SIStorage::~SIStorage() {
	this->sections.clear();
}

SIString& SIStorage::operator()(const SIString key, const SIString section) {
	try {
		return (*this)[section](key);
	}
	catch (const SINullKeyException& e) {
		//re throw the exception since the section itself does not have section and we need to tell user the section name
		throw SINullKeyException(e.what(), section, e.getKeyErr());
	}
}

SISection& SIStorage::operator[](const SIString section) {
	auto sec = this->sections.find(section);
	if (sec == this->sections.end()) {//if iterator is end(), key is not found
		throw SINullKeyException("SectionNotFoundException", section);
	}
	return sec->second;
}

SISection& SIStorage::operator+=(const SIString section) {
	return this->sections[section];
}

bool SIStorage::operator-=(const SIString section) {
	return this->sections.erase(section) == 1;
}

SIString& SIStorage::insertProperty(const SIString key, const SIString section) {
	//we are using insert function instead of operator[]
	//since operator[] will insert a new section(if does not exist) with no initialisation
	//but insert function can let us initialise it
	//then we call .first to get the new section(or existing section) (.second is a bool value), and use ->second to get the section in the hash table
	SISection& currentSec = (this->sections.insert(std::pair<SIString, SISection>(section, SISection())).first)->second;
	return currentSec += key;
}

bool SIStorage::removeProperty(const SIString key, const SIString section) {
	return this->sections[section] -= key;
}

SISize SIStorage::getNumSection() const {
	return this->sections.size();
}

SISize SIStorage::getNumProperty(const SIString section) const {
	return const_cast<SIStorage&>((*this))[section].getNumProperty();
}

bool SIStorage::hasDefault() const {
	auto sec = this->sections.find(SIMPLE::DEFAULT_SECTION);
	if (sec == this->sections.end()) {//if iterator is end(), key is not found
		return false;
	}
	return true;
}

SISectionTable::iterator SIStorage::begin() {
	return this->sections.begin();
}

SISectionTable::iterator SIStorage::end() {
	return this->sections.end();
}

