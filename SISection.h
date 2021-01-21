#pragma once
#ifndef _SISection_H_
#define _SISection_H_

#include <unordered_map>

using std::unordered_map;

#include "SINullKeyException.h"
#include "SIDefineFile.h"

/**
 * @brief SIMPLE - Smart INI Manager and Parser Lite Edition
*/
namespace SIMPLE {

	typedef unordered_map<SIString, SIString> SIPropertyTable;

	/**
	 * @brief SISection is a storage class for sections in ini file, each section contains multiple properties (or keys)
	 * Keys may (but need not) be grouped into arbitrarily named sections. 
	 * The section name appears on a line by itself, in square brackets ([ and ]). 
	 * All keys after the section declaration are associated with that section. 
	 * There is no explicit "end of section" delimiter; sections end at the next section declaration, or the end of the file. 
	 * Sections may not be nested. 
	 * ----------------------------------------------------------------------------------------------------------------
	 * One section contains properties that store the property of the ini file. 
	 * The basic element contained in an INI file is the key or property. 
	 * Every key has a name and a value, delimited by an equals sign (=). 
	 * The name appears to the left of the equals sign. 
	 * In the Windows implementation the key cannot contain the characters equal sign ( = ) or semicolon ( ; ) as these are reserved characters. 
	 * The value can contain any character. 
	*/
	struct SIMPLE_API SISection {
	private:
		
		//The SISection class holds multiple properties
		SIPropertyTable properties;

	public:

		/**
		 * @brief Initialise the section with a set of properties.
		*/
		SISection();

		/**
		 * @brief Initialise the section with a set of properties.
		 * @param properties - The property table which contain a set of properties
		*/
		SISection(SIPropertyTable);

		~SISection();

		/**
		 * @brief Get the pointer to the property located in this section. If the key cannot be found, exception is thrown
		 * @param key - The key of this property.
		 * @return The refernece to the location of the value of this property. If the key cannot be found, exception is thrown, with the section name given as GENERIC_SECTION since
		 * SISection does not store section name (SIStorage store section name and each name points to a section)
		*/
		SIString& operator()(const SIString);

		/**
		 * @brief Insert a new property into the table by key, then return the reference to the new property value.
		 * If the key has alreay exist, no insertion is done and return the reference to the value which the key belongs to.
		 * @param key - The new key of this property
		 * @return The reference to the new property value. If the key has alreay exist, no insertion is done and return the reference to the value which the key belongs to.
		*/
		SIString& operator+=(const SIString);

		/**
		 * @brief Remove the property whose key is equal to the parameter.
		 * @param key - The property of the key that needs to be removed.
		 * @return True if the key is found and the property is removed, false if not found.
		*/
		bool operator-=(const SIString);

		/**
		 * @brief Get the number of property stored inside of this section
		 * @return The number of property stored inside of this section
		*/
		SISize getNumProperty() const;

		/**
		 * @brief Return the itertor of the container from the beginning
		 * @return The itertor of the container from the beginning
		*/
		SIPropertyTable::iterator begin();

		/**
		 * @brief Return the itertor of the container of the end
		 * @return The itertor of the container of the end
		*/
		SIPropertyTable::iterator end();
	};
}
#endif//_SISection_H_