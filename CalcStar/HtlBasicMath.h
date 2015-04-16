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


#ifndef HTL_BASICMATH_H
#define HTL_BASICMATH_H

#include "CSLibRefs.h"
//SUPERSET OF STL MATH
#include <math.h>

namespace CMATH{
	CSTAR_DLLAPI double round(double value, unsigned int numdecimals = 0);
	CSTAR_DLLAPI double trunc(double value, unsigned int numdecimals = 0);

	CSTAR_DLLAPI double floor(double value, unsigned int numdecimals = 0);
	CSTAR_DLLAPI double ceil(double value, unsigned int numdecimals = 0);

	CSTAR_DLLAPI char * itoa(char * buf, int intValue);
	CSTAR_DLLAPI char * uitoa(char * buf, unsigned int uintValue);
	CSTAR_DLLAPI char * ltoa(char * buf, long lngValue);
	CSTAR_DLLAPI char * ultoa(char * buf, unsigned long lngValue);
	CSTAR_DLLAPI char * ftoa(char * buf, float sngValue);
	CSTAR_DLLAPI char * dtoa(char * buf, double dblValue);
	CSTAR_DLLAPI char * ftoa(char * buf, float sngValue,unsigned int numdecimals);
	CSTAR_DLLAPI char * dtoa(char * buf, double dblValue,unsigned int numdecimals);


	CSTAR_DLLAPI double factorial(int intX);
};//end namespace Math

#endif //HTL_BASICMATH_H