#pragma once
#ifndef _SINullKeyException_H_
#define _SINullKeyException_H_

#include "SIDefineFile.h"

using std::exception;

/**
 * @brief SIMPLE - Smart INI Manager and Parser Lite Edition
*/
namespace SIMPLE {
	/**
	 * @brief SINullKeyException class, throws when the section name does not exist, or the key cannot be found in that section
	*/
	class SIMPLE_API SINullKeyException : public exception {
	private:

		const SIException msg;
		const SIString key, section;//the key in the section that user provided has caused the problem

	public:

		//If the user did not specify the key (when the user wants to get the section only), use NULL_KEY instead
		inline const static SIString NULL_KEY = "N_U_L_L_K_E_Y";

		/**
		 * @brief Setup the exception with message of the detail of this exception
		 * @param message - The message of thie exception
		 * @param section - The section where this key has caused the problem, or the section itself caused problem
		 * @param key - The key is that caused this exception
		*/
		SINullKeyException(const SIException, const SIString, const SIString = SIMPLE::SINullKeyException::NULL_KEY);

		~SINullKeyException();

		/**
		 * @brief Get the detail of the exception message
		 * @return detail of the exception message
		*/
		virtual const char* what() const noexcept override;

		/**
		 * @brief Return the key is that caused this exception.
		 * If the user did not specify the key (when the user wants to get the section only), NULL_KEY will be returned instead
		 * @return The key is that caused this exception
		*/
		const SIString getKeyErr() const noexcept(true);

		/**
		 * @brief Return the section is that caused this exception
		 * @return The section is that caused this exception
		*/
		const SIString getSectionErr() const noexcept(true);
	};
}
#endif//_SINullKeyException_H_