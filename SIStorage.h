#pragma once
#ifndef _SIStorage_H_
#define _SIStorage_H_

#include <unordered_map>

#include "SISection.h"
#include "SIDefineFile.h"

using std::unordered_map;

/**
 * @brief SIMPLE - Smart INI Manager and Parser Lite Edition
*/
namespace SIMPLE {

	typedef unordered_map<SIString, SIMPLE::SISection> SISectionTable;

	/**
	 * @brief SIStorage loads the sections and keys or properties from SIParser and store them in hash table.
	 * User can read the value of a specific key in a given section with a general run time of O(1)
	 * Note that native ini file does not support same key located at the same section, behaviour may be undefined if so do.
	*/
	class SIMPLE_API SIStorage {
	private:

		//The SIStorage class contains sections
		SISectionTable sections;

	public:

		/**
		 * @brief Initialise the storage class with a set of sections.
		*/
		SIStorage();

		/**
		 * @brief Initialise the storage class with a set of sections.
		 * @param sections - The section table which contain a set of sections
		*/
		SIStorage(SISectionTable);

		~SIStorage();

		/**
		 * @brief Get the value of the property with a give name under a give section. If the key does not exist in that section does not exist in that section then exception will be thrown.
		 * If section name is not sepcified then the property will be searched in default section, which mean the property isn't defined under a section.
		 * @param key - The key of the property
		 * @param section - The section name of which the property is located. If section name is specified as DEFAULT_SECTION or empty then the property will be searched in default section.
		 * @return The reference to the location where the value of this property. If the key does not exist in that section then exception will be thrown.
		*/
		SIString& operator()(const SIString, const SIString = SIMPLE::DEFAULT_SECTION);

		/**
		 * @brief Get the section with the given section name. If the section does not exist exception will be thrown.
		 * If section name is not sepcified then the property will be searched in default section, where all properties with no specified section will be defined.
		 * @param section - The section name of which the property is located. If section name is specified as DEFAULT_SECTION then the default section will be returned.
		 * @return The reference to the location where the value of this section. If the section does not exist exception will be thrown.
		*/
		SISection& operator[](const SIString);

		/**
		 * @brief Insert a new section into the ini file, given the name of this section.
		 * If the name has already exist in the section then no insertion will be done and the section with corresponding name will be returned.
		 * @param section - The name for the new section.
		 * @return The reference to the location where the new section or the section with this key is stored.
		*/
		SISection& operator+=(const SIString);

		/**
		 * @brief Remove the section with that key
		 * @param section - The name of the section that needs to be removed
		 * @return True if the section name is found and the section is removed
		*/
		const bool operator-=(const SIString);

		/**
		 * @brief Insert a new property into a section, given the key of the property and the section name.
		 * If the section does not exist, a new section will be inserted, then the new property will be inserted into that new section.
		 * If the key has already exist in the section then no insertion will be done and the property with corresponding key will be returned.
		 * @param key - The key of the new property
		 * @param section - The name of the section that the new property is going to be inserted.
		 * If section name is specified as DEFAULT_SECTION or empty then the property will be searched in default section.
		 * If the section name is not found then a  new section will be created.
		 * @return The reference to the value of the new property, or the property with existing key.
		*/
		SIString& insertProperty(const SIString, const SIString = SIMPLE::DEFAULT_SECTION);

		/**
		 * @brief Remove the property with the given key.
		 * @param key - The key of the property
		 * @param section - The name of the section.
		 * If section name is specified as DEFAULT_SECTION or empty then the property will be searched in default section.
		 * @return True if the name of the section AND the key is valid and the property is removed.
		*/
		const bool removeProperty(const SIString, const SIString = SIMPLE::DEFAULT_SECTION);

		/**
		 * @brief Get the number of section in this ini file
		 * @return The number of section in this ini file
		*/
		const SISize getNumSection();

		/**
		 * @brief Get the number of property in a specific section.
		 * @param section - The section name of which the property is located. If section name is not sepcified or specified as DEFAULT_SECTION then the default section will be returned.
		 * @return The number of property in that section.
		*/
		const SISize getNumProperty(const SIString = SIMPLE::DEFAULT_SECTION);

		/**
		 * @brief Check if the current ini file has default section.
		 * Sometimes property may not be written inside a section, the program will parse those properties and put them inside a default section
		 * @return True if contains default section
		*/
		const bool hasDefault();

		/**
		 * @brief Return the iterator of the container from the beginning
		 * @return The iterator of the container from the beginning
		*/
		SISectionTable::iterator begin();

		/**
		 * @brief Return the iterator of the container of the end
		 * @return The iterator of the container of the end
		*/
		SISectionTable::iterator end();
	};
}
#endif//_SIStorage_H_
