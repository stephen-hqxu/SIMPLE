#include "SIExporter.h"

using namespace SIMPLE;

SIExporter::SIExporter(const SIString& path, SIStorage& storage) : iniSettings(storage) {
	try {
		//initialise the file stream
		this->iniFile.open(path, std::ios_base::out | std::ios_base::trunc);
	}
	catch (const fstream::failure& fail) {
		throw(fail);
	}
}

SIExporter::~SIExporter() {
	//clear up and close the file stream
	if (this->iniFile.is_open()) {
		this->iniFile.close();
	}
}

const bool SIExporter::WriteINI() {
	//handle the case when the file path is not valid
	if (this->iniFile.fail()) {
		throw exception("FileNotValidException");
	}
	//TODO: output the SIStorage to an ini file
	//output default section first, since default section should start at first line
	if (this->iniSettings.hasDefault()) {
		auto defaultSec = this->iniSettings[SIMPLE::DEFAULT_SECTION];
		for (auto prop = defaultSec.begin(); prop != defaultSec.end(); prop++) {
			this->iniFile << prop->first << "=" << prop->second << endl;
		}
	}
	//iterate over the regular sections
	for (auto sec = this->iniSettings.begin(); sec != this->iniSettings.end(); sec++) {
		if (sec->first == SIMPLE::DEFAULT_SECTION) {//do not out put default section
			continue;
		}
		SISection currentSec = this->iniSettings[sec->first];
		//output section declare line
		this->iniFile << "[" << sec->first << "]" << endl;

		//iterate over the properties
		for (auto prop = currentSec.begin(); prop != currentSec.end(); prop++) {
			this->iniFile << prop->first << "=" << prop->second << endl;
		}
		this->iniFile << endl;//add empty line between each line, makes it looks better
	}

	return true;
}