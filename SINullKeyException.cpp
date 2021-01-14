#include "SINullKeyException.h"

using namespace SIMPLE;

SINullKeyException::SINullKeyException(const SIException message, const SIString section, const SIString key) : msg(message), key(key), section(section) {

}

SINullKeyException::~SINullKeyException() {

}

const char* SINullKeyException::what() const noexcept {
	return this->msg;
}

const SIString SINullKeyException::getKeyErr() const noexcept(true) {
	return this->key;
}

const SIString SINullKeyException::getSectionErr() const noexcept(true) {
	return this->section;
}