
#define CSTAR_DLLEXPORT
#include ".\CSFunctionValidator.h"
namespace CSTAR
{

CSFunctionValidator::CSFunctionValidator(void)
{
};

CSFunctionValidator::~CSFunctionValidator(void)
{
};

bool CSFunctionValidator::ValidateExpression(const std::vector<CSToken> & arrObjTokenCollection)
{
	int intTemp;
	bool blnTemp = true;
	bool blnReturn = true;//set opptimistic
	size_t i, intNumTokens;
	CSTokenType objCurrToken;
	intNumTokens = arrObjTokenCollection.size();
	//safety check on size
	if(intNumTokens <= 0){/*No tokens*/return false;};

	for(i = 0; i < intNumTokens;i++)
	{
		objCurrToken = arrObjTokenCollection.at(i).m_objTokenType;
		switch(objCurrToken)
		{
		case NUMBER:
			{
				intTemp = this->ValidateNumber(arrObjTokenCollection,blnTemp,i);
				break;
			};//end NEG description
		case VAR:
			{
				intTemp = this->ValidateVariable(arrObjTokenCollection,blnTemp,i);
				break;
			};//end NEG description
		//case ASSIGN:
		//	{
		//		intTemp = this->ValidateAssign(arrObjTokenCollection,blnTemp,i);
		//		break;
		//	};//end NEG description


		};//end switch
		if(blnTemp == false)
		{//then failed
			blnReturn = false;
		};
	};//end for loop through tokens
	return blnReturn;
};

int CSFunctionValidator::ValidateOperator(const std::vector<CSToken> & arrObjTokenCollection, bool & blnValidFunction, int intCurrPos)
{
	int intReturn = -1;
	size_t intNumTokens;
	intNumTokens = arrObjTokenCollection.size();
	//safety check on size
	if(intNumTokens <= 0){/*No tokens*/return -1;};
	//depending on where we are look for invalid neighbor tokens
	blnValidFunction = false;//set pessimistic
	if(intCurrPos == intNumTokens - 1)
	{		
		//then at end
		blnValidFunction = false;
		return -1;
	}else{
		//then at beginning or somewhere inbetween
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == NUMBER){blnValidFunction = true; return 1;};
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == VAR){blnValidFunction = true; return 1;};
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == OPENPAREN){blnValidFunction = true; return 1;};
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == OPENBRACKET){blnValidFunction = true; return 1;};
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == OPENBLOCK){blnValidFunction = true; return 1;};
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == FUNC){blnValidFunction = true; return 1;};
		
	};
	return 1;
};

int CSFunctionValidator::ValidateFunction(const std::vector<CSToken> & arrObjTokenCollection, bool & blnValidFunction, int intCurrPos,int intNumArgs)
{
	int intFoundArgs = 0;
	int intNestLevel = 0;
	blnValidFunction = true;//set optimistic
	bool blnCloseFound;
	CSTokenType objFuncToken,objCurrToken, objNextToken;
	size_t i, intNumTokens;
	intNumTokens = arrObjTokenCollection.size();
	objFuncToken = arrObjTokenCollection.at(intCurrPos).m_objTokenType;

	if((intCurrPos + 2) > (int)(intNumTokens - 1))
	{
		blnValidFunction = false;
		return -1;
	};
	//check for valid opening functions have to start with OPEN Parenthesis
	if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType != OPENPAREN)
	{
		blnValidFunction = false;
		return -1;
	};
	blnCloseFound = false;
	//now scan for the number of arguments and the close parenthesis for this function
	i = intCurrPos + 2;
	objCurrToken = arrObjTokenCollection.at(i).m_objTokenType;
	//check the first argument manually
	if((objCurrToken != CLOSEPAREN)&&(objCurrToken != CLOSEPAREN)&&(objCurrToken != CLOSEPAREN) )
	{
		//then valid first argument
		++intFoundArgs;
	};
	do//cycle through the rest delimiting on commas
	{
		objCurrToken = arrObjTokenCollection.at(i).m_objTokenType;
		if((objCurrToken ==  OPENPAREN)||(objCurrToken ==  OPENBRACKET)||(objCurrToken ==  OPENBLOCK))
		{
			//increment nest level
			//need to make sure this only counts once for a multiply nested arg
			++intNestLevel;
		};
		if( (intNestLevel > 0)
			&&((objCurrToken ==  CLOSEPAREN)||(objCurrToken ==  CLOSEBRACKET)||(objCurrToken ==  CLOSEBLOCK)) )
		{
			//increment nest level
			--intNestLevel;
		};
		//otherwise need to scan on delimiting with commas
		if((intNestLevel <= 0)&&(objCurrToken == COMMA))
		{
			//then delimiter for new argument found
			//check next token
			if((i + 1) > (intNumTokens - 1))
			{//then can't analyze next token, comma is the last thing bad function footprint
				blnValidFunction = false;
				return -1;
			}
			objNextToken = arrObjTokenCollection.at(i+1).m_objTokenType;
			if((objNextToken != CLOSEPAREN)&&(objNextToken != CLOSEPAREN)&&(objNextToken != CLOSEPAREN) )
			{
				//then valid next argument, increment the number of arguments
				++intFoundArgs;
			};
		}

		//scan until close parenthesis
		if((intNestLevel <= 0)&& (objCurrToken ==  CLOSEPAREN))
		{
			blnCloseFound = true;
		};
		//increment the current position
		i++;
	}while((blnCloseFound == false)&&(i < intNumTokens));

	if(intNumArgs == intFoundArgs)
	{
		blnValidFunction = true;
		return 1;
	}else{
		blnValidFunction = false;
		return -1;
	};
	return 0;
};

//!NEG Function
int CSFunctionValidator::ValidateNumber(const std::vector<CSToken> & arrObjTokenCollection, bool & blnValidFunction, int intCurrPos)
{
	size_t intNumTokens;
	intNumTokens = arrObjTokenCollection.size();
	//safety check on size
	blnValidFunction = true;
	if(intNumTokens <= 0){blnValidFunction = true;/*No tokens*/return -1;};

	//depending on where we are look for invalid neighbor tokens
	if((intNumTokens <= 1)&&(intCurrPos == 0))
	{
		//then var is only token
		blnValidFunction = true;
		return 1;
	};

	if(intCurrPos == 0)
	{//then at beginning
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == NUMBER){blnValidFunction = false; return -1;};
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == VAR){blnValidFunction = false; return -1;};
	}else if(intCurrPos == intNumTokens - 1){
		//then at end
		if(arrObjTokenCollection.at(intCurrPos - 1).m_objTokenType == NUMBER){blnValidFunction = false; return -1;};
		if(arrObjTokenCollection.at(intCurrPos - 1).m_objTokenType == VAR){blnValidFunction = false; return -1;};
	}else{
		//somewhere inbetween the ends
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == NUMBER){blnValidFunction = false; return -1;};
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == VAR){blnValidFunction = false; return -1;};
		if(arrObjTokenCollection.at(intCurrPos - 1).m_objTokenType == NUMBER){blnValidFunction = false; return -1;};
		if(arrObjTokenCollection.at(intCurrPos - 1).m_objTokenType == VAR){blnValidFunction = false; return -1;};
	};
	return 1;
};
//!NEG Function
int CSFunctionValidator::ValidateVariable(const std::vector<CSToken> & arrObjTokenCollection, bool & blnValidFunction, int intCurrPos)
{
	size_t intNumTokens;
	intNumTokens = arrObjTokenCollection.size();
	//safety check on size
	//safety check on size
	blnValidFunction = true;
	if(intNumTokens <= 0){blnValidFunction = false;/*No tokens*/return -1;};

	//depending on where we are look for invalid neighbor tokens
	if((intNumTokens <= 1)&&(intCurrPos == 0))
	{
		//then var is only token
		blnValidFunction = true;
		return 1;
	};

	if(intCurrPos == 0)
	{//then at beginning
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == NUMBER){blnValidFunction = false; return -1;};
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == VAR){blnValidFunction = false; return -1;};
	}else if(intCurrPos == intNumTokens - 1){
		//then at end
		if(arrObjTokenCollection.at(intCurrPos - 1).m_objTokenType == NUMBER){blnValidFunction = false; return -1;};
		if(arrObjTokenCollection.at(intCurrPos - 1).m_objTokenType == VAR){blnValidFunction = false; return -1;};
	}else{
		//somewhere inbetween the ends
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == NUMBER){blnValidFunction = false; return -1;};
		if(arrObjTokenCollection.at(intCurrPos + 1).m_objTokenType == VAR){blnValidFunction = false; return -1;};
		if(arrObjTokenCollection.at(intCurrPos - 1).m_objTokenType == NUMBER){blnValidFunction = false; return -1;};
		if(arrObjTokenCollection.at(intCurrPos - 1).m_objTokenType == VAR){blnValidFunction = false; return -1;};
	};
	return 1;
};
//!NEG Function



}//end namespace CSTAR