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

//CS Dynamic Link Library definitions
#ifndef CSTAR_LIB_REFS_H
#define CSTAR_LIB_REFS_H

#ifdef CSTAR_DLLEXPORT
	//configure for dll export
	#define CSTAR_DLLAPI __declspec(dllexport)
#else
	//configure for dll import
	#define CSTAR_DLLAPI __declspec(dllimport)
#endif

#ifndef CSTAR_EXPORT
#define CSTAR_EXPORT __declspec(dllexport)
#endif

#ifndef CSTAR_IMPORT
#define CSTAR_IMPORT __declspec(dllimport)
#endif

#define CSTAR_VERSION_STR "0.1.0"
/*
   CS_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define CSTAR_VERSION 0x000100

#ifndef CSTAR_CPP_TYPEDEFS
#define CSTAR_CPP_TYPEDEFS
//!Unsigned 
	typedef unsigned int uint;
	typedef unsigned int size_t;
	typedef unsigned short ushort;
	typedef unsigned long ulong;
	typedef unsigned char uchar;
#endif

//Standard Template Library Includes
#ifndef CSTAR_STD_LIB_INCLUDES
	#define CSTAR_STD_LIB_INCLUDES
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctype.h>
#include <math.h>
#endif

#endif
