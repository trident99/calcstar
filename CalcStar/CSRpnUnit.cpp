
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

#include "CSRpnUnit.h"
#include "CSOpBase.h"
#include "CSOpBaseFactory.h"

namespace CSTAR
{
	CSRpnUnit::CSRpnUnit() : CSToken()
	{
		//Inherits from structToken
		m_ptrDblVarData = NULL;
		//!The variable is initialized flag
		m_blnVarLinked = false;
		//!The variable is Externally Linked
		m_blnExternal = false;
		//!Pointer to the opbase
		m_ptrOpEval = NULL;
	};

	CSRpnUnit::CSRpnUnit(const CSRpnUnit& rhs)
		: CSToken(rhs) 
	{
		m_ptrDblVarData = rhs.m_ptrDblVarData;
		m_blnVarLinked = rhs.m_blnVarLinked;
		m_blnExternal = rhs.m_blnExternal;
		//DO NOT COPY THE m_ptrOpEval
		//!Pointer to the opbase
		m_ptrOpEval = NULL;
	};

	CSRpnUnit& CSRpnUnit::operator= (const CSRpnUnit& rhs)
	{
		if (this != &rhs)
		{
			m_ptrDblVarData = rhs.m_ptrDblVarData;
			m_blnVarLinked = rhs.m_blnVarLinked;
			m_blnExternal = rhs.m_blnExternal;
			//DO NOT COPY THE m_ptrOpEval
			//!Pointer to the opbase
			m_ptrOpEval = NULL;
		}
		return *this;
	}

	CSRpnUnit::~CSRpnUnit()
	{
		this->DeleteOpBase();
	};

	//Create the OpBase from the factory
	void CSRpnUnit::CreateOpBase(void)
	{
		if(m_ptrOpEval)
		{
			delete m_ptrOpEval;
			m_ptrOpEval = NULL;
		};
		m_ptrOpEval = GetOpBaseFactoryPtr()->Create(m_strToken);
	};
	//!Delete the ObBase
	void CSRpnUnit::DeleteOpBase(void)
	{
		if(m_ptrOpEval)
		{
			delete m_ptrOpEval;
			m_ptrOpEval = NULL;
		};
	};

}