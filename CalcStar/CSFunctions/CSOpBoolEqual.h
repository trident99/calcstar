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

#ifndef CSTAR_OP_BoolEqual_H
#define CSTAR_OP_BoolEqual_H

#include "..\CSOpBase.h"
#include "..\CSOpBaseFactory.h"

namespace CSTAR
{

	class CSOpBoolEqual: public CSOpBase
	{
	public:
		//!Default Constructor
		CSOpBoolEqual();
		//!Default Destructor
		~CSOpBoolEqual();

		//!Perform the operation on the stack
		virtual int OpEval(std::vector<CSRpnUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos);

	};

	//OBJECT FACTORY REGISTRATION CODE
	static bool blnCSOpBoolEqual_Registered = CSTAR::GetOpBaseFactoryPtr()->Register<CSOpBoolEqual>("==");
	static bool blnCSOpBoolEqual2_Registered = CSTAR::GetOpBaseFactoryPtr()->Register<CSOpBoolEqual>("EQ");
	static bool blnCSOpBoolEqual3_Registered = CSTAR::GetOpBaseFactoryPtr()->Register<CSOpBoolEqual>("CSOpBoolEqual");
}//end namespace
#endif