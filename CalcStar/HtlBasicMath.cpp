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
#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define CSTAR_DLLEXPORT
#pragma warning(pop)

#include ".\HtlBasicMath.h"
#include <string>
#include <stdio.h>//need the printf, scanf series of functions
using namespace std;

namespace CMATH
{

	double round(double value, unsigned int numdecimals){
		long lngTemp, lngDecShift;
		double dblTemp;

		//Shift the Decimal Places by the number desired and
		//then round that value to an integer. Then shift the decimals
		//back to the original position and return the double.
		lngDecShift = (long)pow(10.0, static_cast<int>(numdecimals));
		if(value > 0.0){
			lngTemp = (long)((value * lngDecShift) + 0.5);
			dblTemp = ((double)lngTemp / (double)lngDecShift);
			return dblTemp;
		}else{
			lngTemp = (long)((value * lngDecShift) - 0.5);
			dblTemp = ((double)lngTemp / (double)lngDecShift);
			return dblTemp;
		};
	};

	double trunc(double value, unsigned int numdecimals){

		double dblTemp, dblCalc, dblNewVal, dblShift;
		//Shift the Decimal Places by the number desired and
		//then truncate that value to an integer. Then shift the decimals
		//back to the original position and return the double.
		if(numdecimals < 1){
			return floor(value);
		}else{
			dblShift = pow(10.0,static_cast<int>(numdecimals));
			dblCalc = value * dblShift;
			dblNewVal = floor(dblCalc);
			dblTemp =  (dblNewVal / dblShift);
			return dblTemp;
		};
	};

	//
	double floor(double value, unsigned int numdecimals)
	{
		long lngTemp, lngDecShift;
		double dblTemp;

		//Shift the Decimal Places by the number desired and
		//then round that value to an integer. Then shift the decimals
		//back to the original position and return the double.
		lngDecShift = (long)pow(10.0, static_cast<int>(numdecimals));
		if(value > 0.0){
			lngTemp = (long)((value * lngDecShift));
			dblTemp = ((double)lngTemp / (double)lngDecShift);
			return dblTemp;
		}else{
			lngTemp = (long)((value * lngDecShift));
			dblTemp = ((double)lngTemp / (double)lngDecShift);
			return dblTemp;
		};
	};
	double ceil(double value, unsigned int numdecimals)
	{
		long lngDecShift;
		double dblTemp, dblCalc, dblBaseline;
		//THIS NEEDS TO BE MODIFIED
		//Shift the Decimal Places by the number desired and
		//then round that value to an integer. Then shift the decimals
		//back to the original position and return the double.
		lngDecShift = (long)pow(10.0, (static_cast<int>(numdecimals)));
		if(value > 0.0){
			dblCalc = (value * (double)lngDecShift);
			dblBaseline = (round(value,numdecimals) * (double)lngDecShift);
			if(dblCalc > dblBaseline){ dblCalc += 1;};
			dblTemp = (dblCalc / (double)lngDecShift);
			return round(dblTemp,numdecimals);
		}else{
			dblCalc = (value * (double)lngDecShift);
			dblBaseline = (round(value,numdecimals) * (double)lngDecShift);
			if(dblCalc < dblBaseline){ dblCalc -= 1.0f;};
			dblTemp = (dblCalc / (double)lngDecShift);
			return round(dblTemp,numdecimals);
		};
	};

	char * itoa(char * buf, int intValue)
	{
		sprintf_s(buf, 256, "%d",intValue);
		return buf;
	};

	char * uitoa(char * buf, unsigned int uintValue)
	{
		sprintf_s(buf, 256, "%u",uintValue);
		return buf;
	};

	char* ltoa(char * buf, long lngValue)
	{
		sprintf_s(buf, 256, "%d",lngValue);
		return buf;
	};

	char * ultoa(char * buf, unsigned long ulngValue)
	{
		sprintf_s(buf, 256, "%u",ulngValue);
		return buf;
	};

	char * ftoa(char * buf, float sngValue)
	{
		sprintf_s(buf, 256, "%3.6f",sngValue);
		return buf;
	};

	char * dtoa(char * buf, double dblValue)
	{
		sprintf_s(buf, 256, "%3.12f",dblValue);
		return buf;
	};

	char * ftoa(char * buf, float sngValue, unsigned int numdecimals)
	{	char chrDec[50];
	std::string strFormat = "%6.";
	strFormat += itoa(chrDec, numdecimals);
	strFormat += "f";
	sprintf_s(buf, 256, strFormat.c_str(), sngValue);
	return buf;
	};

	char * dtoa(char * buf, double dblValue, unsigned int numdecimals)
	{
		char chrDec[50];
		std::string strFormat = "%6.";
		strFormat += itoa(chrDec, numdecimals);
		strFormat += "f";
		sprintf_s(buf, 256, strFormat.c_str(),dblValue);
		return buf;
	};

	double factorial(int intX)
	{
		double dblFact;
		int intCursor;
		if(intX < 0){return 0.0f;};
		intCursor = intX;
		dblFact = 1.0f;
		while(intCursor >= 1)
		{
			dblFact = dblFact*intCursor;
			intCursor--;
		};
		return dblFact;
	};

};//end namespace math
