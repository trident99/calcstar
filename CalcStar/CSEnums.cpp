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
#define CSTAR_DLLEXPORT

#include "CSEnums.h"

namespace CSTAR
{

	std::string TokenTypeToString(CSTokenType objInput)
	{
		std::string strRet;

		if( objInput == NOOP){return "NOOP";};
		if( objInput == OPENPAREN){return "OPENPAREN";};
		if( objInput == OPENBRACKET){return "OPENBRACKET";};
		if( objInput == OPENBLOCK){return "OPENBLOCK";};
		if( objInput == CLOSEPAREN){return "CLOSEPAREN";};
		if( objInput == CLOSEBRACKET){return "CLOSEBRACKET";};
		if( objInput == CLOSEBLOCK){return "CLOSEBLOCK";};
		if( objInput == COMMA){return "COMMA";};
		if( objInput == NUMBER){return "NUMBER";};
		if( objInput == VAR){return "VAR";};
		if( objInput == ASSIGN){return "ASSIGN";};
		if( objInput == NEG){return "NEG";};
		if( objInput == ADD){return "ADD";};
		if( objInput == SUB){return "SUB";};
		if( objInput == MULT){return "MULT";};
		if( objInput == DIV){return "DIV";};
		if( objInput == LT){return "LT";};
		if( objInput == GT){return "GT";};
		if( objInput == LTE){return "LTE";};
		if( objInput == GTE){return "GTE";};
		if( objInput == NEQ){return "NEQ";};
		if( objInput == EQ){return "EQ";};
		if( objInput == AND){return "AND";};
		if( objInput == OR){return "OR";};
		if( objInput == NOT){return "NOT";};
		if( objInput == FUNC){return "FUNC";};

		return("nil");

	}

}//end namespace CSTAR