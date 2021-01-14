#pragma once
#ifndef _SIExporter_H_
#define _SIExporter_H_

#include <fstream>

#include "SIStorage.h"
#include "define_file.h"

using std::fstream;
using std::endl;

/**
 * @brief SIMPLE - Smart INI Manager and Parser Lite Edition
*/
namespace SIMPLE {

	/**
	 * @brief SIExporter exports the current loaded ini setting that is stored inside the SIStorage class into an standard ini file
	*/
	class SIMPLE_API SIExporter {
	private:

		fstream iniFile;
		SIStorage& iniSettings;

	public:

		/**
		 * @brief Initialise the exporter, given the destination of the ini and the ini settings
		 * @param path - The location where the ini will be stored
		 * @param storage - The SIStorage class where all ini settings are stored
		*/
		SIExporter(const SIString&, SIStorage&);

		~SIExporter();

		/**
		 * @brief Export the ini file to the local file system
		*/
		const bool WriteINI();

	};
}
#endif//_SIExporter_H_
