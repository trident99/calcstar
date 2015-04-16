/*
**	This file is part of the CalcStar Function Evaluator library.
**  License information is in the CSLicense.h file.
**	This software was developed by:
**	
**  Anthony Daniels (copyright 2014)
** <http://www.pyramidsolutions.com>
**
**  CalcStar is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**
**  CalcStar is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with CalcStar.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#ifndef CSTAR_ENUMS_H
#define CSTAR_ENUMS_H

#include "CSLibRefs.h"

namespace CSTAR
{

	enum CSTAR_DLLAPI CSAssociativity
	{
		NON_ASSOCIATIVE = 0,
		LEFT_ASSOCIATIVE = 1,
		RIGHT_ASSOCIATIVE = 2
	};

	enum CSTAR_DLLAPI CSTrigType
	{
		REG,
		ARC,
		HYP,
		AHYP
	};

	enum CSTAR_DLLAPI CSTokenType
	{	//IMPORTANT NOTE!!! these operators are in order of operation prescedence
		//THE LOWER THE NUMBER THE HIGHER THE PRESCEDENCE
		//DO NOT CHANGE THIS ORDERING, HARDCODING IS USED BASED ON ENUMERATED TYPES
		//
		NOOP = -1,
		OPENPAREN = 0,
		OPENBRACKET,
		OPENBLOCK,
		CLOSEPAREN,
		CLOSEBRACKET,
		CLOSEBLOCK,
		COMMA,
		NUMBER,
		VAR,
		ASSIGN,
		NEG,
		ADD,
		SUB,
		MULT,
		DIV,
		LT,
		GT,
		LTE,
		GTE,
		NEQ,
		EQ,
		AND,
		OR,
		NOT,
		FUNC
	};
	//MISCELLANEOUS PUBLIC DATA FUNCTIONS
	//Converts the token type to a string for output
	CSTAR_DLLAPI std::string TokenTypeToString(CSTokenType objInput);

}//end namespace CSTAR

#endif // CSTAR_ENUMS_H


