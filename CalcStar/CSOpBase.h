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

#ifndef CSTAR_OPBASE_H
#define CSTAR_OPBASE_H

#include "CSRpnUnit.h"

namespace CSTAR
{

	class CSOpBase
	{
	public:
		//!Default Constructor
		CSOpBase();
		//!Default Destructor
		~CSOpBase();
	public:
		//!Perform the operation on the stack
		virtual int OpEval(std::vector<CSRpnUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos) = 0;
		//!Makes sure the inputs to the Calculation Operation are Valid
		int ValidOpInputs(std::vector<CSRpnUnit> & arrObjCalcStack, bool & blnValidInputs,int intCurrPos,int intNumInputs);
		//!Replace the operation and input tokens with the output NUMBER token
		int ReplaceOp(std::vector<CSRpnUnit> & arrObjCalcStack,int intStartPos, int intEndPos, CSRpnUnit objNumberUnit);
		//!Gets the number for the current operational unit
		int GetOpNumber(const CSRpnUnit * ptrUnit, double & dblReturn);
		//!Sets the number for the current operational unit
		int SetOpNumber(CSRpnUnit * ptrUnit, double & dblReturn);
	public:
        int m_intNumInputs;
	};

}//end namespace
#endif