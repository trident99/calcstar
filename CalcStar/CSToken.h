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

#ifndef CSTAR_TOKEN_H
#define CSTAR_TOKEN_H

#include "CSStructs.h"

namespace CSTAR
{

	struct CSTAR_DLLAPI CSToken
	{
	public:
		//!Default Constructor
		CSToken();
		//!Copy Constructor
		CSToken(const CSToken& rhs);
		//!Assignment Operator
		CSToken& operator= (const CSToken& rhs);
		//!Destructor
		~CSToken();
	public:  
		//This is a thin class, so member variables are public like in a typical struct
		//!The token type of this RPN Unit
		CSTokenType m_objTokenType;
		//!The string representation of the token
		std::string m_strToken;
		//!token's associativity
		CSAssociativity m_objAssociativity;
		//!numeric version of token if applicable
		double m_dblToken;

	};
	
}//end namespace CSTAR
#endif