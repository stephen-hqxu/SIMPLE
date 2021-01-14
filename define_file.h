#pragma once
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)//The warning tells us the client need to have access to allocator, unordered_map, etc. functions that have been used
//We know what we are doing, so tell the compiler to shut up
#include <string>

#ifdef SIMPLE_EXPORTS
#define SIMPLE_API __declspec(dllexport)
#else
#define SIMPLE_API __declspec(dllimport)
#endif

typedef std::string SIString;
typedef unsigned long long SISize;
typedef const char* SIException;
typedef std::pair<SIString, SIString> SIProperty;

/**
 * @brief SIMPLE - Smart INI Manager and Parser Lite Edition
*/
namespace SIMPLE {
	//Specify the section name as this value will make the storage class return a default section
	const static SIString DEFAULT_SECTION = "D_E_F_A_U_L_T_S_E_C_T_I_O_N";
	//The section name will become generic section when the key not found exception is thrown inside SISection instead of SIStorage since SISection does not store section name
	const static SIString GENRIC_SECTION = "G_E_N_R_I_C_S_E_C_T_I_O_N";
}