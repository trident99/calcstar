
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

#define CSTAR_DLLEXPORT

#include "CSToken.h"


namespace CSTAR
{
	CSToken::CSToken()
	{
		m_objTokenType = NOOP;
		m_objAssociativity = NON_ASSOCIATIVE;
		m_strToken = "nil";
		m_dblToken = 0.0;
	};

	CSToken::CSToken(const CSToken& rhs)
		: m_objTokenType (rhs.m_objTokenType)
		, m_objAssociativity (rhs.m_objAssociativity)
		, m_strToken (rhs.m_strToken)
		, m_dblToken (rhs.m_dblToken)
	{
	};

	CSToken& CSToken::operator= (const CSToken& rhs)
	{
		if (this != &rhs)
		{
			m_objTokenType = rhs.m_objTokenType;
			m_objAssociativity = rhs.m_objAssociativity;
			m_strToken = rhs.m_strToken;
			m_dblToken = rhs.m_dblToken;
		}
		return *this;
	}

	CSToken::~CSToken()
	{
		m_strToken.clear();
	};


}