#pragma once
#ifndef _SIParser_H_
#define _SIParser_H_

#include <fstream>

#include "SIStorage.h"
#include "SIDefineFile.h"

using std::fstream;
using std::getline;

//Determine whether the comment (line that starts with # or ;) will be igonre, otherwise comment will be treated as regular ini settings
//If the comment line is set to be parsed but the properties do not obey the ini syntax then this line will be skipped
#ifdef SIMPLE_PARSE_COMMENT
#undef SIMPLE_PARSE_COMMENT
#define SIMPLE_PARSE_COMMENT true
#else
#define SIMPLE_PARSE_COMMENT false
#endif

//Determine if the user input key needs to be matched with case sensitivity, by Windows specification ini files are case-insensitive
#ifdef SIMPLE_CASE_SENSITIVE
#undef SIMPLE_CASE_SENSITIVE
#define SIMPLE_CASE_SENSITIVE true
#else
#define SIMPLE_CASE_SENSITIVE false
#endif

/**
 * @brief SIMPLE - Smart INI Manager and Parser Lite Edition
*/
namespace SIMPLE {

	/**
	 * @brief SIParser loads the ini file from the file system, process it and store it using hash table.
	 *
	*/
	class SIMPLE_API SIParser {
	private:

		//flag
		//try to make it looks complicated so we won't get parse from the ini file
		inline const static SIString SYNTAX_ERROR = "S_Y_N_T_A_X_E_R_R_O_R";

		//the file stream that opens the ini file in read only mode
		fstream iniFile;
		SIStorage iniSettings;

		/**
		 * @brief Load the ini file from the file system and store into SIParser
		 * The ini file can be retreive as SIStorage format using get()
		*/
		void loadINI();

		/**
		 * @brief Parse the current line into property class
		 * @param line - The current line of the ini file stream
		 * @return The property of the current line
		*/
		SIProperty parseProperty(const SIString);

		/**
		 * @brief Parse the line that contain section name
		 * @param line - The current line of the ini file stream
		 * @return The name of that section
		*/
		const SIString parseSection(const SIString);

	public:

		/**
		 * @brief Initialise the SIMPLE Parser. User provide a file path which should be an ini file.
		 * Then ini file will be loaded into SIParser, stored in SIStorage
		 * If the file is not an ini file or it is invalid, exception will be thrown.
		 * @param filename - The path that leads to the ini file
		*/
		SIParser(const SIString&);

		~SIParser();

		/**
		 * @brief Return the internally stored SIStorage
		 * @return The reference to the location where all ini settings that are stored
		*/
		SIStorage& get();
	};
}
#endif//_SIParser_H_