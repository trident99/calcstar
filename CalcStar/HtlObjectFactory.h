/*
**	This file is part of the Hpc Template Library (Htl or HTL).
**  It is based on a merger of QT, STL, and SigSlots along with development of new classes.
**  License information is in the HtlLicense.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT, STL, SigSlots
**
**  HTL is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to HtlStar.
**
**  HTL is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with HTL.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef HTL_OBJECTFACTORY_H
#define HTL_OBJECTFACTORY_H


#include <cstdlib>
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include <iostream> 
using namespace std;

namespace HTL
{
	
	template<typename BaseType, typename ClassType>
	BaseType *CreateObject()
	{

		return new ClassType();//requires that the class type being used Has a void constructor
	}

	//!This is a string registration key based object factory.
	template<typename BaseType>
	class HtlObjectFactory
	{
	protected:
		// Create function pointer
		//typedef BaseType* (__stdcall *CreateObjectFunc)(void);
		typedef BaseType* (__cdecl *CreateObjectFunc)(void);

		std::map<std::string, CreateObjectFunc> m_ptrObjectConstructorMap;

	public:

		typedef typename std::map<std::string, CreateObjectFunc>::const_iterator FactoryConstIter;
		typedef typename std::map<std::string, CreateObjectFunc>::iterator FactoryIter;


		//!Register the class with the object factory
		template<typename ClassType>
		bool Register(std::string unique_id)
		{
			if (m_ptrObjectConstructorMap.find(unique_id) != m_ptrObjectConstructorMap.end())
				return false;

			m_ptrObjectConstructorMap[unique_id] = &CreateObject<BaseType, ClassType>;

			return true;
		}
		//!Unregister the class from the object factory
		bool UnRegister(std::string unique_id)
		{
			return (m_ptrObjectConstructorMap.erase(unique_id) == 1);
		}
		//!Create an object based on its class name unique ID
		BaseType *Create(std::string unique_id)
		{
			if(m_ptrObjectConstructorMap.size() <= 0){return NULL;};//safety check
			FactoryIter iter = m_ptrObjectConstructorMap.find(unique_id);
			//std::cout<< "map size..." << m_ptrObjectConstructorMap.size() << "\n";
			if (iter == m_ptrObjectConstructorMap.end())
			{
				return NULL;
			};

			return ((*iter).second)();
		}
		//!Get the map beginning iterator
		FactoryConstIter GetBegin() const
		{
			return m_ptrObjectConstructorMap.begin();
		}
		//!Get the map beginning iterator
		FactoryIter GetBegin()
		{
			return m_ptrObjectConstructorMap.begin();
		}
		//!Get the map end iterator
		FactoryConstIter GetEnd() const
		{
			return m_ptrObjectConstructorMap.end();
		}
		//!Get the map end iterator
		FactoryIter GetEnd()
		{
			return m_ptrObjectConstructorMap.end();
		}
		//!Does the class name exist
		bool DoesClassExist(std::string type)
		{
			FactoryIter iter;
			iter = m_ptrObjectConstructorMap.find(type);
			if(iter != m_ptrObjectConstructorMap.end())
			{
				return true;
			}else{
				return false;
			};
		};

		//!Get a list of all of the registered classes
		std::vector<std::string> GetAllRegistered(void)
		{
			std::vector<string> arrNames;
			FactoryIter iter;
			iter = m_ptrObjectConstructorMap.begin();
			for(iter = m_ptrObjectConstructorMap.begin();
				iter != m_ptrObjectConstructorMap.end();
				++iter)
			{
				arrNames.push_back((*iter).first);
			};
			return arrNames;
		};



	};

};// end namespace HTL
#endif // HTL_OBJECTFACTORY_H