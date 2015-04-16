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

#include "CSOpBase.h"
#include "CSRpnUnit.h"

namespace CSTAR
{
	//!Default Constructor
	CSOpBase::CSOpBase()
	{
		m_intNumInputs = 1;
	};
	//!Default Destructor
	CSOpBase::~CSOpBase()
	{
		return;
	}
	//!This function determines if the required preceeding operations are valid numbers or variables
	int CSOpBase::ValidOpInputs(std::vector<CSRpnUnit> & arrObjCalcStack, bool & blnValidInputs,int intCurrPos ,int intNumInputs)
	{
		int i;
		blnValidInputs = true;
		CSRpnUnit * ptrUnit = NULL;
		try{
			//start at the current position - 1 and go back
			for(i = intCurrPos - 1 ; i >= intCurrPos - intNumInputs;i--)
			{
				ptrUnit = &(arrObjCalcStack.at(i));
				if((ptrUnit->m_objTokenType == NUMBER) || (ptrUnit->m_objTokenType == VAR) )
				{
					//valid input do nothing
				}else{
					//invalid input
					blnValidInputs = false;
				}
			}
			return 1;
		}catch(...){
			//encountered an error probably
			blnValidInputs = false;
			return -1;
		}
	};

	int CSOpBase::ReplaceOp(std::vector<CSRpnUnit> & arrObjCalcStack,int intStartPos, int intEndPos, CSRpnUnit objNumberUnit)
	{
		try{
			////erase the calculation tokens
			//arrObjCalcStack.erase(arrObjCalcStack.begin() + intStartPos,arrObjCalcStack.begin() + intEndPos);
			////write the replacement number token
			//arrObjCalcStack.insert(arrObjCalcStack.begin() + intStartPos,objNumberUnit);
			////the above method should have worked but erase has lost its mind in the STL
			
			//CLEAN SLATE REPLACE METHOD
			std::vector<CSRpnUnit>::iterator iter;

			std::vector<CSRpnUnit> arrObjNewStack;

			//copy up to the current operation
			for(size_t i = 0; i < (intStartPos); i++)
			{
				arrObjNewStack.push_back(arrObjCalcStack.at(i));
			};
			//put in the replacement for the operation
			arrObjNewStack.push_back(objNumberUnit);
			//put in the remainder of the unyet used stack
			if( (intEndPos + 1) < arrObjCalcStack.size())
			{
				for( (iter = arrObjCalcStack.begin() + intEndPos + 1) ; iter != arrObjCalcStack.end() ; ++iter)
				{
					arrObjNewStack.push_back( (*iter) );
				}
			};
			//assign new stack
			arrObjCalcStack.clear();
			arrObjCalcStack = arrObjNewStack;

			return 1;
		}catch(...){
			return -1;
		}
	};
	//!This function takes in an RPN Unit and returns the numeric value for the unit if it is a NUMBER OR VAR, 
	//return's NULL if it doesn't recognize the operation type
	int CSOpBase::GetOpNumber(const CSRpnUnit * ptrUnit, double & dblReturn)
	{
		if(ptrUnit->m_objTokenType == NUMBER)
		{
			//return the numeric value of the token
			dblReturn =  ptrUnit->m_dblToken;
			return 1;
		}else if(ptrUnit->m_objTokenType == VAR){
			//check to see if the pointer has been set
			if(ptrUnit->m_ptrDblVarData != NULL)
			{
				dblReturn = *(ptrUnit->m_ptrDblVarData);
				return 1;
			}else{
				dblReturn = 0;
				return -1;
			}
		}else{
			//unknown token type for numeric output
			dblReturn = 0;
			return -1;
		}
	};
	//return's NULL if it doesn't recognize the operation type
	int CSOpBase::SetOpNumber(CSRpnUnit * ptrUnit, double & dblReturn)
	{
		if(ptrUnit->m_objTokenType == NUMBER)
		{
			//return the numeric value of the token
			ptrUnit->m_dblToken = dblReturn;
			return 1;
		}else if(ptrUnit->m_objTokenType == VAR){
			//check to see if the pointer has been set
			if(ptrUnit->m_ptrDblVarData != NULL)
			{
				*(ptrUnit->m_ptrDblVarData) = dblReturn;
				return 1;
			}else{
				return -1;
			}
		}else{
			//unknown token type for numeric output
			dblReturn = 0;
			return -1;
		}
	};

}//end namespace CSTAR