#include "SISection.h"

using namespace SIMPLE;

SISection::SISection() {

}

SISection::SISection(SIPropertyTable properties) {
	this->properties = SIPropertyTable(properties);
}

SISection::~SISection() {
	this->properties.clear();
}

SIString& SISection::operator()(const SIString key) {
	auto prop = this->properties.find(key);
	if (prop == this->properties.end()) {//if iterator is end(), key is not found
		throw SINullKeyException("KeyNotFoundException", SIMPLE::GENRIC_SECTION, key);
	}
	return prop->second;
}

SIString& SISection::operator+=(const SIString key) {
	return this->properties[key];
}

bool SISection::operator-=(const SIString key) {
	return this->properties.erase(key) == 1;//we have unique key so the number of erase must be either 1 or 0
}

SISize SISection::getNumProperty() const {
	return this->properties.size();
}

SIPropertyTable::iterator SISection::begin() {
	return this->properties.begin();
}

SIPropertyTable::iterator SISection::end() {
	return this->properties.end();
}