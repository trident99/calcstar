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
#ifndef CSTAR_OPBASEFACTORY_H
#define CSTAR_OPBASEFACTORY_H

#include ".\HtlObjectFactory.h"
#include ".\CSOpBase.h"
using namespace HTL;
using namespace std;

namespace CSTAR {

	class CSTAR_DLLAPI CSOpBaseFactory : 
		public HtlObjectFactory<CSOpBase> 
		{
		public:

			//retrieves a string vector of all of the classes in the factory
			std::vector<std::string> GetAllOperNames(void);
			//retrieves a subset of the classes in factory that contain strName in the class name
			std::vector<std::string> SearchOperNames(std::string strName);

		};//end ORSDBObjectFactory class definition


	CSTAR_DLLAPI CSOpBaseFactory * GetOpBaseFactoryPtr(void);

	CSTAR_DLLAPI CSOpBase * CreateOpBase(std::string strName);

	CSTAR_DLLAPI CSOpBase * CreateOpBase(const char * ptrName);

};//end namespace CSTAR

#endif//CSTAR_OPBASEFACTORY_H
