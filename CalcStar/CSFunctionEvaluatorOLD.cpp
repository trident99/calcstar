//#include "LpsTktMDO_StdAfx.h"
#include ".\ClsFunctionEvaluator.h"
#include ".\ClsFunctionValidator.h"



ClsFunctionEvaluator::ClsFunctionEvaluator(void)
{
}

ClsFunctionEvaluator::~ClsFunctionEvaluator(void)
{
}

//STRING EXPRESSION ACCESS FUNCTIONS
//Gets the string expression
std::string ClsFunctionEvaluator::Get_strExpression(void)
{
	return m_strExpression;	
};

int ClsFunctionEvaluator::Set_strExpression(std::string strInput)
{
	this->m_strExpression = strInput;
	return 1;	
};

//DOUBLE CURRENT VALUE ACCESS FUNCTION
//!Gets the current value of the expression
double ClsFunctionEvaluator::Get_dblCurrValue(void)
{
	return this->m_dblCurrValue;
}
//VARIABLE COLLECTION MANIPULATION;
int ClsFunctionEvaluator::AddVariable(structVariable objNewVar)
{
	this->m_arrObjVarCollection.push_back(objNewVar);
	return 1;
};
//!Delete a variable by its string variable name
int ClsFunctionEvaluator::DeleteVariable(std::string strVarName)
{
	int i, intUboundI;
	try{
		intUboundI = this->m_arrObjVarCollection.size();
		for(i = 0; i < intUboundI; i++)
		{
			if(strVarName == this->m_arrObjVarCollection.at(i).m_strVarName)
			{
				//then match found, delete it
				this->m_arrObjVarCollection.erase(m_arrObjVarCollection.begin() + i);
				return 1;
			}

		}
		//if we get here no match found, return NULL
		return 0;
	}catch(...){
		//return error
		return -1;
	}
};
//!Delete a variable by index number
int ClsFunctionEvaluator::DeleteVariable(int intIndex)
{
	try{

		//then match found, delete it
		this->m_arrObjVarCollection.erase(m_arrObjVarCollection.begin() + intIndex);
		return 1;

	}catch(...){
		//return error
		return -1;
	}
};
//!Deletes All Variables
int ClsFunctionEvaluator::DeleteAllVariables(void)
{
	this->m_arrObjVarCollection.clear();
	return 1;
};

//! Get variable by its name, returns NULL if not found
structVariable * ClsFunctionEvaluator::Get_Variable(std::string strVarName)
{
	int i, intUboundI;
	try{
		intUboundI = this->m_arrObjVarCollection.size();
		for(i = 0; i < intUboundI; i++)
		{
			if(strVarName == this->m_arrObjVarCollection.at(i).m_strVarName)
			{
				//then match found, return the pointer to it
				return &(this->m_arrObjVarCollection.at(i));
			}
		}
		//if we get here no match found, return NULL
		return 0;
	}catch(...){
		//return error
		return NULL;
	}
};
//!Get variable by its index, returns NULL if not found
structVariable *  ClsFunctionEvaluator::Get_Variable(int intIndex)
{
	try{
		if((intIndex >= 0)&&(intIndex < (int)(this->m_arrObjVarCollection.size())))
		{
			//then match found, return the pointer to it
			return &(this->m_arrObjVarCollection.at(intIndex));
		}else{
			return NULL;
		}
	}catch(...){
		//return error, bad index
		return NULL;
	}

};
//gets the number of variables in the collection
unsigned int ClsFunctionEvaluator::Get_VariableCount(void)
{
	return (this->m_arrObjVarCollection.size());
};
//VARIABLE LINKING AND INTEGRITY CHECK FUNCTIONS
//!Link RPN Variable tokens to their appropriate variables in the variable collection
int ClsFunctionEvaluator::LinkRPNVariables(void)
{
	int i, intUboundI, j, intUboundJ;
	structRPNUnit * ptrUnitTemp = NULL;
	structVariable * ptrVarTemp = NULL;
	int intReturn = 1;
	bool blnMatchFound;
	//cycle through the RPN Stack and set the links for the tokens that are VAR
	intUboundI = this->m_arrObjRPNQueue.size();
	intUboundJ = this->m_arrObjVarCollection.size();
	for(i = 0; i < intUboundI; i++)
	{
		ptrUnitTemp = &(this->m_arrObjRPNQueue.at(i));
		if((!ptrUnitTemp->m_blnExternal) && (ptrUnitTemp->m_objTokenType == VAR))
		{//then it is an internally linked variable, need to find the pointer within the current variable collection
			//externally linked variables must be manually kept track of for initialization
			blnMatchFound = false;
			for(j = 0; j < intUboundJ; j++)
			{
				ptrVarTemp = &(this->m_arrObjVarCollection.at(j));
				if(ptrVarTemp->m_strVarName == ptrUnitTemp->m_strToken)
				{
					//then we found a match, set the pointer
					blnMatchFound = true;
					ptrUnitTemp->m_ptrDblVarData = &(ptrVarTemp->m_dblCurrVal);
				}

			}//end for loop j
			if(!blnMatchFound)
			{
				//did not find a match, return false
				intReturn = -1;
			}
		}//end if block external check
	}//end for loop i
	return intReturn;
};

//!	Sets a variable link for the RPN Unit, ASSUMED EXTERNAL LINK
int ClsFunctionEvaluator::Set_VariableLink(std::string strVarName, double * ptrDblVar, bool blnExternal)
{//ASSUMES THAT THE LINK BEING PROPOSED IS AN EXTERNAL LINK
	int i, intUboundI, intUboundJ;
	structRPNUnit * ptrUnitTemp = NULL;
	structVariable * ptrVarTemp = NULL;
	int intReturn = 1;
	bool blnMatchFound = false;
	//cycle through the RPN Stack and set the links for the tokens that are VAR
	intUboundI = this->m_arrObjRPNQueue.size();
	intUboundJ = this->m_arrObjVarCollection.size();

	//cycle throug the RPN stack and substitute for each matching VAR, setting the pointer link
	blnMatchFound = false;
	for(i = 0; i < intUboundI;i++)
	{
		ptrUnitTemp = &(this->m_arrObjRPNQueue.at(i));
		if(ptrUnitTemp->m_objTokenType == VAR)
		{
			if(ptrUnitTemp->m_strToken == strVarName)
			{
				ptrUnitTemp->m_ptrDblVarData = ptrDblVar;
				if(blnExternal)
				{
					ptrUnitTemp->m_blnExternal = true;
				}else{
					ptrUnitTemp->m_blnExternal = false; 
				}
				blnMatchFound = true;
			}//end match check

		}//end if Variable check

	}//end loop through 
	//if a match was found return 1, otherwise return 0
	if(blnMatchFound)
	{
		return 1;
	}else{
		return 0;
	}

}; 

//! Sets the data to the matching variable name
int ClsFunctionEvaluator::Set_VariableData(std::string strVarName, double dblData)
{
	int i, intUboundI;
	structVariable * ptrVarTemp = NULL;

	intUboundI = this->m_arrObjVarCollection.size();
	//cycle through the RPN stack units and make sure all VAR types do not have a NULL pointer for their data.
	for(i = 0; i < intUboundI; i++)
	{
		ptrVarTemp = &(this->m_arrObjVarCollection.at(i) );
		if(ptrVarTemp->m_strVarName == strVarName)
		{
			//then have a match, set the data and return successful
			ptrVarTemp->m_dblCurrVal = dblData;
			return 1;
		}

	}//end for loop i
	return 0;
}

//!Checks the RPN queue to make sure all variables are linked properly
bool ClsFunctionEvaluator::CheckVariablesLinked(void)
{
	int i, intUboundI;
	structRPNUnit * ptrUnitTemp = NULL;
	intUboundI = this->m_arrObjRPNQueue.size();
	//cycle through the RPN stack units and make sure all VAR types do not have a NULL pointer for their data.
	for(i = 0; i < intUboundI; i++)
	{
		ptrUnitTemp = &(this->m_arrObjRPNQueue.at(i) );
		if((ptrUnitTemp->m_objTokenType == VAR) &&(ptrUnitTemp->m_ptrDblVarData == NULL))
		{
			return false;
		}

	}//end for loop i
	return true;
};


//TOKEN COLLECTION MANIPULATION
//!Gets the number of tokens in the collection
unsigned int ClsFunctionEvaluator::Get_TokenCount(void)
{
	return (this->m_arrObjTokenCollection.size());
};
//!get the token by index number, returns NULL if not found
structToken * ClsFunctionEvaluator::Get_Token(int intIndex)
{
	try{
		if((intIndex >= 0)&&(intIndex < (int)(this->m_arrObjTokenCollection.size())))
		{
			//then match found, return the pointer to it
			return &(this->m_arrObjTokenCollection.at(intIndex));
		}else{
			return NULL;
		}
	}catch(...){
		//return error
		return NULL;
	}
};
//!	Clears the token collection
int ClsFunctionEvaluator::ClearTokenCollection(void)
{
	this->m_arrObjTokenCollection.clear();
	return 1;
};

//RPN QUEUE MANIPULATION
//!Gets the number of tokens in the collection
unsigned int ClsFunctionEvaluator::Get_RPNCount(void)
{
	return (this->m_arrObjRPNQueue.size());
};
//!get the token by index number, returns NULL if not found
structRPNUnit * ClsFunctionEvaluator::Get_RPNUnit(int intIndex)
{
	try{
		if((intIndex >= 0)&&(intIndex < (int)(this->m_arrObjRPNQueue.size())))
		{
			//then match found, return the pointer to it
			return &(this->m_arrObjRPNQueue.at(intIndex));
		}else{
			return NULL;
		}

	}catch(...){
		//return error
		return NULL;
	}
};
//!	Clears the RPN Queue
int ClsFunctionEvaluator::ClearRPNQueue(void)
{
	this->m_arrObjRPNQueue.clear();
	return 1;
};
//!Checks the RPN stack to make sure it is a valid RPN stack
int ClsFunctionEvaluator::CheckRPNIntegrity(void)
{
	return 1;
};

//STRING TOKENIZATION FUNCTIONS
//! Creates the tokenized collection which is used to generate the RPN stack
int ClsFunctionEvaluator::TokenizeExpression(void)
{
	//make a local copy of the string
	bool blnWhiteSpace, blnReturn;
	int pos, intNumChars, intLength;
	std::string strInput;
	structToken objTokenTemp;
	strInput = this->m_strExpression;
	pos = 0;
	this->m_arrObjTokenCollection.clear();
	std::vector<structToken> tokens;
	intNumChars = strInput.size();
	while(!strInput.empty())
	{
		//safety check
		if(strInput.size() <= 0)
		{
			break;
		}
		//get the next token off of the string
		blnReturn = this->GetNextToken(strInput,pos,intLength,objTokenTemp,blnWhiteSpace);
		if(blnReturn)
		{
			if(blnWhiteSpace)
			{
				//erase the whitespace and continue
				strInput.erase(pos,intLength);
			}else{
				//push the token onto the back of the vector
				tokens.push_back (objTokenTemp);
				//this->m_arrObjTokenCollection.push_back(objTokenTemp);
				//remove the token from the string
				strInput.erase(pos,intLength);
			}
		}else{
			//error in getting next token, or error in string
			//clear the stack and quit,return error
			tokens.clear ();
			//this->m_arrObjTokenCollection.clear();
			return -1;	
		}//
	}
	m_arrObjTokenCollection = tokens;
	return 1;	
};


bool ClsFunctionEvaluator::GetNextToken(std::string strInput, int posStart, int & intLength, structToken &objReturn, bool & blnWhiteSpace)
{
	//check
	char chrCurrent = '\0';
	structToken objControlToken, objOpToken, objMathToken, objNumberToken, objVarToken;
	int intTestLength;

	//read the first character to see what kind of token we are dealing with
	//Check for operators and control block characters first. if it is one of them, check the necessary characters
	//Then make the token and returns the correct ending position of the 
	chrCurrent = strInput.at(posStart);
	//CHECK FOR WHITESPACE FIRST, IGNORE IF IT IS WHITESPACE
	if(chrCurrent == ' ')
	{//then it is whitespace, ignore
		blnWhiteSpace = true;
		intLength = 1;
		return true;
	}else{
		blnWhiteSpace = false;
	}

	//CHECK FOR CONTROL / PRECEDENCE CHARACTERS FIRST
	if(this->GetNextControl(strInput,posStart,intTestLength,objControlToken) )
	{//then the next token is an operator
		objReturn = objControlToken;
		intLength = intTestLength;
		return true;
	}
	//NOT A CONTROL CHARACTER, NOW CHECK FOR OPERATORS

	if(this->GetNextOperator(strInput,posStart,intTestLength,objOpToken) )
	{//then the next token is an operator
		objReturn = objOpToken;
		intLength = intTestLength;
		return true;
	}
	//NOT A FUNCTION, NOW CHECK FOR MATH FUNCTIONS
	if(this->GetNextFunction(strInput,posStart,intTestLength,objMathToken) )
	{//then the next token is an operator
		objReturn = objMathToken;
		intLength = intTestLength;
		return true;
	}
	//NOT A FUNCTION, NOW CHECK TO SEE IF IT IS A NUMBER
	if(this->GetNextNumber(strInput,posStart,intTestLength,objNumberToken) )
	{//then the next token is an operator
		objReturn = objNumberToken;
		intLength = intTestLength;
		return true;
	}
	//NOT A NUMBER, NOW CHECK TO SEE IF IT IS A VARIABLE
	if(this->GetNextVariable(strInput,posStart,intTestLength,objVarToken) )
	{//then the next token is an operator
		objReturn = objVarToken;
		intLength = intTestLength;
		return true;
	}
	//UNKNOWN TOKEN, RETURN ERROR.
	return false;	
};

bool ClsFunctionEvaluator::GetNextControl(std::string strInput, int posStart, int & intLength, structToken & objReturn)
{
	//check
	char chrCurrent = '\0';
	structToken objOpToken, objMathToken,objNumberToken;
	chrCurrent = strInput.at(posStart);
	//ALL CONTROL CHARACTERS ARE NON ASSOCIATIVE UNLESS OTHERWISE NOTED
	objReturn.m_objAssociativity = NON_ASSOCIATIVE;
	//BLOCK CONTROLS
	if(chrCurrent == '{')
	{
		objReturn.m_objTokenType = OPENBLOCK;
		objReturn.m_strToken = '{';
		intLength = 1;
		return true;
	};
	if(chrCurrent == '}')
	{
		objReturn.m_objTokenType = CLOSEBLOCK;
		objReturn.m_strToken = '}';
		intLength = 1;
		return true;
	};
	//BRACKET CONTROLS
	if(chrCurrent == '[')
	{
		objReturn.m_objTokenType = OPENBRACKET;
		objReturn.m_strToken = '[';
		intLength = 1;
		return true;
	};
	if(chrCurrent == ']')
	{
		objReturn.m_objTokenType = CLOSEBRACKET;
		objReturn.m_strToken = ']';
		intLength = 1;
		return true;
	};
	//PARENTHESES PRESCEDENCE CONTROLS
	if(chrCurrent == '(')
	{
		objReturn.m_objTokenType = OPENPAREN;
		objReturn.m_strToken = '(';
		intLength = 1;
		return true;
	};
	if(chrCurrent == ')')
	{
		objReturn.m_objTokenType = CLOSEPAREN;
		objReturn.m_strToken = ')';
		intLength = 1;
		return true;
	};
	//FUNCTION ARGUMENT DELIMITER
	if(chrCurrent == ',')
	{
		objReturn.m_objTokenType = COMMA;
		objReturn.m_strToken = ',';
		intLength = 1;
		return true;
	};
	return false;
};

bool ClsFunctionEvaluator::GetNextOperator(std::string strInput, int posStart, int & intLength, structToken & objReturn)
{
	char chrCurrent = '\0';
	char charTest = '\0';
	std::string strTest;
	//read the first characr and based on that character test the other possible scenarios
	chrCurrent = strInput.at(posStart);
	int intSize = strInput.size();
	//safety check string size
	if((intSize < 1)||strInput.empty())
	{
		//error string not big enough to be an operator
		return false;
	}
	//ALL OPERATORS ARE LEFT ASSOCIATIVE UNLESS OTHERWISE NOTED
	objReturn.m_objAssociativity = LEFT_ASSOCIATIVE;

	if(chrCurrent == '>')
	{//could be > or >= or ><
		//could be >=
		//GREATER THAN OR EQUAL TO OPERATOR
		strTest = strInput.substr(posStart,2);
		if(strTest == ">=")
		{//then function is cos()
			objReturn.m_objTokenType = GTE;
			objReturn.m_strToken = ">=";
			intLength = 2;
			return true;
		}

		//SYNONYM FOR NOT EQUAL TO OPERATOR
		strTest = strInput.substr(posStart,2);
		if(strTest == "><")
		{//then function is cos()
			objReturn.m_objTokenType = NEQ;
			objReturn.m_strToken = "!=";
			intLength = 2;
			return true;
		}

		//then GT
		objReturn.m_objTokenType = GT;
		objReturn.m_strToken = ">";
		intLength = 1;
		return true;
	}//end GT check

	if(chrCurrent == '<')
	{//could be < or <= or <>
		//could be <=
		//LESS THAN OR EQUAL TO OPERATOR
		strTest = strInput.substr(posStart,2);
		if(strTest == "<=")
		{//then function is cos()
			objReturn.m_objTokenType = LTE;
			objReturn.m_strToken = "<=";
			intLength = 2;
			return true;
		}
		//SYNONYM FOR NOT EQUAL TO OPERATOR
		strTest = strInput.substr(posStart,2);
		if(strTest == "<>")
		{//then function is cos()
			objReturn.m_objTokenType = NEQ;
			objReturn.m_strToken = "!=";
			intLength = 2;
			return true;
		}

		//then LT
		objReturn.m_objTokenType = LT;
		objReturn.m_strToken = "<";
		intLength = 1;
		return true;
	}//end GT check

	if(chrCurrent == '!')
	{//could be < or <= or <>
		//NOT EQUAL TO OPERATOR
		strTest = strInput.substr(posStart,2);
		if(strTest == "!=")
		{//then function is cos()
			objReturn.m_objTokenType = NEQ;
			objReturn.m_strToken = "!=";
			intLength = 2;
			return true;
		}
		//NOT an operator
		return false;
	}//end GT check

	if(chrCurrent == '=')
	{//could be < or <= or <>
		//EQUAL TO OPERATOR
		strTest = strInput.substr(posStart,2);
		if(strTest == "==")
		{//then function is cos()
			objReturn.m_objTokenType = EQ;
			objReturn.m_strToken = "==";
			intLength = 2;
			return true;
		}
		//ASSIGNMENT OPERATOR
		{//then function is cos()
			objReturn.m_objTokenType = ASSIGN;
			objReturn.m_strToken = "=";
			intLength = 1;
			return true;
		};
		//NOT an operator
		return false;
	}//end GT check

	if(chrCurrent == '&')
	{//could be < or <= or <>
		//AND OPERATOR
		strTest = strInput.substr(posStart,2);
		if(strTest == "&&")
		{//then function is cos()
			objReturn.m_objTokenType = AND;
			objReturn.m_strToken = "&&";
			intLength = 2;
			return true;
		}
		//NOT an operator
		return false;
	}//end GT check

	if(chrCurrent == '|')
	{//could be < or <= or <>
		//OR OPERATOR
		strTest = strInput.substr(posStart,2);
		if(strTest == "||")
		{//then function is cos()
			objReturn.m_objTokenType = OR;
			objReturn.m_strToken = "||";
			intLength = 2;
			return true;
		}
		//NOT an operator
		return false;
	}//end GT check

	if(chrCurrent == '+')
	{//could be < or <= or <>

		objReturn.m_objTokenType = ADD;
		objReturn.m_strToken = "+";
		intLength = 1;
		return true;
		//NOT an operator
		return false;
	}//end GT check

	if(chrCurrent == '-')
	{//could be subtraction
		//OR OPERATOR
		strTest = strInput.substr(posStart,2);
		if(strTest == "- ")
		{//then function is cos()
			objReturn.m_objTokenType = SUB;
			objReturn.m_strToken = "-";
			intLength = 1;
			return true;
		}else{
			//THEN NEGATIVE OPERATOR
			objReturn.m_objTokenType = NEG;
			objReturn.m_strToken = "-";
			intLength = 1;
			return true;
		};
	}//end GT check

	if(chrCurrent == '*')
	{//could be < or <= or <>

		objReturn.m_objTokenType = MULT;
		objReturn.m_strToken = "*";
		intLength = 1;
		return true;
	}//end GT check

	if(chrCurrent == '/')
	{//could be < or <= or <>

		objReturn.m_objTokenType = DIV;
		objReturn.m_strToken = "/";
		intLength = 1;
		return true;
	}//end GT check


	//NOT an operator
	return false;
};

bool ClsFunctionEvaluator::GetNextFunction(std::string strInput, int posStart, int & intLength, structToken & objReturn)
{
	char chrCurrent = '\0';
	char charTest = '\0';
	std::string strTest;
	//read the first characr and based on that character test the other possible scenarios
	chrCurrent = strInput.at(posStart);
	int intFuncSizeLimit = strInput.size() - posStart - 1;
	//ALL FUNCTIONS ARE RIGHT ASSOCIATIVE UNLESS OTHERWISE NOTED
	objReturn.m_objAssociativity = RIGHT_ASSOCIATIVE;
	if(intFuncSizeLimit < 1)
	{//then can't be a function, not enough characters
		intLength = 0;
		return false;
	}
	//otherwise test every function possible
	//SINE FUNCTION
	strTest = strInput.substr(posStart,4);
	if(strTest == "sin(")
	{//then function is sin()
		objReturn.m_objTokenType = SIN;
		objReturn.m_strToken = "sin";
		intLength = 3;
		return true;
	}

	//COSINE FUNCTION
	strTest = strInput.substr(posStart,4);
	if(strTest == "cos(")
	{//then function is cos()
		objReturn.m_objTokenType = COS;
		objReturn.m_strToken = "cos";
		intLength = 3;
		return true;
	}

	//TANGENT FUNCTION
	strTest = strInput.substr(posStart,4);
	if(strTest == "tan(")
	{//then function is tan()
		objReturn.m_objTokenType = TAN;
		objReturn.m_strToken = "tan";
		intLength = 3;
		return true;
	}

	//ARC SINE FUNCTION
	strTest = strInput.substr(posStart,5);
	if(strTest == "asin(")
	{//then function is asin()
		objReturn.m_objTokenType = ASIN;
		objReturn.m_strToken = "asin";
		intLength = 4;
		return true;
	}

	//ARC COSINE FUNCTION
	strTest = strInput.substr(posStart,5);
	if(strTest == "acos(")
	{//then function is acos()
		objReturn.m_objTokenType = ACOS;
		objReturn.m_strToken = "acos";
		intLength = 4;
		return true;
	}

	//ARC TANGENT FUNCTION
	strTest = strInput.substr(posStart,5);
	if(strTest == "atan(")
	{//then function is atan()
		objReturn.m_objTokenType = ATAN;
		objReturn.m_strToken = "atan";
		intLength = 4;
		return true;
	}

	//	HSINE FUNCTION
	strTest = strInput.substr(posStart,5);
	if(strTest == "sinh(")
	{//then function is sinh()
		objReturn.m_objTokenType = SINH;
		objReturn.m_strToken = "sinh";
		intLength = 4;
		return true;
	}

	// HCOSINE FUNCTION
	strTest = strInput.substr(posStart,5);
	if(strTest == "cosh(")
	{//then function is cos()
		objReturn.m_objTokenType = COSH;
		objReturn.m_strToken = "cosh";
		intLength = 4;
		return true;
	}

	// HTANGENT FUNCTION
	strTest = strInput.substr(posStart,5);
	if(strTest == "tanh(")
	{//then function is tanh()
		objReturn.m_objTokenType = TANH;
		objReturn.m_strToken = "tanh";
		intLength = 4;
		return true;
	}

	//ARC HSINE FUNCTION
	strTest = strInput.substr(posStart,6);
	if(strTest == "asinh(")
	{//then function is asinh()
		objReturn.m_objTokenType = ASINH;
		objReturn.m_strToken = "asinh";
		intLength = 5;
		return true;
	}

	//ARC HCOSINE FUNCTION
	strTest = strInput.substr(posStart,6);
	if(strTest == "acosh(")
	{//then function is acosh()
		objReturn.m_objTokenType = ACOSH;
		objReturn.m_strToken = "acosh";
		intLength = 5;
		return true;
	}

	//ARC HTANGENT FUNCTION
	strTest = strInput.substr(posStart,6);
	if(strTest == "atanh(")
	{//then function is atanh()
		objReturn.m_objTokenType = ATANH;
		objReturn.m_strToken = "atanh";
		intLength = 5;
		return true;
	}
	//TO BE ADDED LATER
	//SIGN
	//END TO BE ADDED LATER

	//LOG BASE 2 FUNCTION
	strTest = strInput.substr(posStart,5);
	if(strTest == "log2(")
	{//then function is log2()
		objReturn.m_objTokenType = LOG2;
		objReturn.m_strToken = "log2";
		intLength = 4;
		return true;
	}

	//LOG FUNCTION
	strTest = strInput.substr(posStart,4);
	if(strTest == "log(")
	{//then function is log()
		objReturn.m_objTokenType = LOG;
		objReturn.m_strToken = "log";
		intLength = 3;
		return true;
	}

	//NATURAL LOG FUNCTION
	strTest = strInput.substr(posStart,3);
	if(strTest == "ln(")
	{//then function is ln()
		objReturn.m_objTokenType = LN;
		objReturn.m_strToken = "ln";
		intLength = 2;
		return true;
	}

	//NATRURAL EXPONENTIAL FUNCTION
	strTest = strInput.substr(posStart,4);
	if(strTest == "exp(")
	{//then function is exp()
		objReturn.m_objTokenType = EXP;
		objReturn.m_strToken = "exp";
		intLength = 3;
		return true;
	}

	//POWER EXPONENTIAL FUNCTION
	strTest = strInput.substr(posStart,4);
	if(strTest == "pow(")
	{//then function is pow()
		objReturn.m_objTokenType = POW;
		objReturn.m_strToken = "pow";
		intLength = 3;
		return true;
	}

	//SQUARE ROOT FUNCTION
	strTest = strInput.substr(posStart,5);
	if(strTest == "sqrt(")
	{//then function is sqrt()
		objReturn.m_objTokenType = SQRT;
		objReturn.m_strToken = "sqrt";
		intLength = 4;
		return true;
	}

	//ROUND FUNCTION
	strTest = strInput.substr(posStart,6);
	if(strTest == "round(")
	{//then function is round()
		objReturn.m_objTokenType = ROUND;
		objReturn.m_strToken = "round";
		intLength = 5;
		return true;
	}

	//TRUNC FUNCTION
	strTest = strInput.substr(posStart,6);
	if(strTest == "trunc(")
	{//then function is trunc()
		objReturn.m_objTokenType = TRUNC;
		objReturn.m_strToken = "trunc";
		intLength = 5;
		return true;
	}

	//ABSOLUTE VALUE FUNCTION
	strTest = strInput.substr(posStart,4);
	if(strTest == "abs(")
	{//then function is abs()
		objReturn.m_objTokenType = ABS;
		objReturn.m_strToken = "abs";
		intLength = 3;
		return true;
	}

	//CEILING FUNCTION
	strTest = strInput.substr(posStart,5);
	if(strTest == "ceil(")
	{//then function is ceil()
		objReturn.m_objTokenType = CEIL;
		objReturn.m_strToken = "ceil";
		intLength = 4;
		return true;
	}

	//FLOOR FUNCTION
	strTest = strInput.substr(posStart,6);
	if(strTest == "floor(")
	{//then function is floor()
		objReturn.m_objTokenType = FLOOR;
		objReturn.m_strToken = "floor";
		intLength = 5;
		return true;
	}

	//NOT A FUNCTION
	return false;
};


bool ClsFunctionEvaluator::GetNextNumber(std::string strInput, int posStart, int & intLength, structToken & objReturn)
{
	char buf[256], output[256];
	for (int i = 0; i < 256; buf[i++] = '\0');
	for (int i = 0; i < 256; output[i++] = '\0');
	int pos = 0;

	//if it's not a number, return false
	if (!isdigit(strInput.at(pos)) && strInput.at(pos) != '-' && strInput.at(pos) != '.')
		return false;

	//if the - don't follow by number, then it's not a number
	if (strInput.at(pos) == '-')
		if (!isdigit(strInput.at(1)))
			return false;
	buf[0] = strInput.at(0);
	//if only one character long short circuit and quit out
	if(strInput.size() <= 1)
	{
		objReturn.m_objTokenType = NUMBER;
		objReturn.m_dblToken = atof(buf);
		sprintf_s(output,"%f",objReturn.m_dblToken);
		objReturn.m_strToken = output;
		objReturn.m_objAssociativity = NON_ASSOCIATIVE;
		intLength = 1;
		return true;
	}
	//more than one character in the array
	for (pos = 1; pos < (int)strInput.size(); pos++)
	{

		if (isdigit(strInput.at(pos)) || strInput.at(pos) == '.')
		{
			buf[pos] = strInput.at(pos);
		}else{
			break;
		}

	}

	objReturn.m_objTokenType = NUMBER;
	objReturn.m_dblToken = atof(buf);
	sprintf_s(output,"%f",objReturn.m_dblToken);
	objReturn.m_strToken = output;
	objReturn.m_objAssociativity = NON_ASSOCIATIVE;
	intLength = pos;
	return true;	
};


bool ClsFunctionEvaluator::GetNextVariable(std::string strInput, int posStart, int & intLength, structToken & objReturn)
{

	char buf[256];
	for (int i = 0; i < 256; buf[i++] = '\0');
	int pos = 0;

	//if it's not a alphanumeric, return false
	if (!isdigit(strInput.at(pos)) && !isalpha(strInput.at(pos)))
		return false;

	buf[0] = strInput.at(0);
	if(strInput.size() <= 1)
	{
		if (isdigit(strInput.at(0)) || isalpha(strInput.at(0)))
		{
			objReturn.m_objTokenType = VAR;
			objReturn.m_strToken = buf;
			objReturn.m_dblToken = atof(buf);
			objReturn.m_objAssociativity = NON_ASSOCIATIVE;
		}else{
			return false;
		}
	}

	for (pos = 1; pos < (int)strInput.size(); pos++)
	{
		if(strInput.at(pos) == ' ')
		{
			break;
		}else if(isdigit(strInput.at(pos) ) || isalpha(strInput.at(pos) ) || (strInput.at(pos) == '_') ){

			buf[pos] = strInput.at(pos);
		}else{
			break;
		}
	}
	if(pos < 256)
	{
		buf[pos] = 0;
	}
	intLength = pos;
	objReturn.m_objTokenType = VAR;
	objReturn.m_strToken = buf;
	objReturn.m_dblToken = atof(buf);
	objReturn.m_objAssociativity = NON_ASSOCIATIVE;
	return true;	
};

//STRING COMPILATION FUNCTIONS
//! Compiles from scratch the existing string, First it Tokenizes it, then it compiles the RPN
int ClsFunctionEvaluator::Compile(void)
{
	int intRetToken,intRetCompile;

	intRetToken = this->TokenizeExpression();
	intRetCompile = this->CompileExistingTokens();
	if( (intRetToken == 1) && (intRetCompile == 1) )
	{	//then successful
		return 1;
	}else{
		//then return error
		return -1;
	};
};
//! Compiles the existing token stack
int ClsFunctionEvaluator::CompileExistingTokens(void)
{
	ClsFunctionValidator objValidator;
	int i, intUboundI;
	structToken objCurrToken, objTempToken;
	//first check to see if expression balanced.
	bool blnParenBalanced,blnBlockBalanced,blnBracketBalanced, blnValidExpression;

	blnParenBalanced = this->CheckParenthesisBalanced();
	blnBlockBalanced = this->CheckBlockBalanced();
	blnBracketBalanced = this->CheckBracketBalanced();
	blnValidExpression = objValidator.ValidateExpression(this->m_arrObjTokenCollection);

	if(blnParenBalanced && blnBlockBalanced && blnBracketBalanced && blnValidExpression)
	{
		//safe to continue to compilation
	}else{
		//mismatched control characters, QUIT OUT and return error
		return -1;
	}

	try{
		/*
		The remainder of the algorithm uses the SHUNTING YARD ALGORITHM	on the existing calculation token collection.
		It makes use of an output stack, and an operator stack to re-organize the numbers, variables, and operations into
		postfix notation, which makes it easier for the computer to do calculations by sweeping through the vector of operations.
		Operator precedence is also preserved. The listed operators are enumerated in order of operation precedence, to simplify calculations
		and stack manipulation.

		The shunting yard algorithm (from Wikipedia)

		While there are tokens to be read: 
		-Read a token. 
		-If the token is a number, then add it to the output queue. 
		-If the token is a function token, then push it onto the stack. 
		-If the token is a function argument separator (e.g., a comma): 
		-Until the token at the top of the stack is a left parenthesis, pop operators off the stack onto the output queue.
		If no left parentheses are encountered, either the separator was misplaced or parentheses were mismatched. 
		-If the token is an operator, o1, then: 
		-while there is an operator, o2, at the top of the stack (this excludes left parenthesis), and either 
		-o1 is left-associative and its precedence is less than (lower precedence) or equal to that of o2, or 
		-o1 is right-associative and its precedence is less than (lower precedence) that of o2, 
		-pop o2 off the stack, onto the output queue; 
		-push o1 onto the stack. 
		-If the token is a left parenthesis, then push it onto the stack. 
		-If the token is a right parenthesis: 
		-Until the token at the top of the stack is a left parenthesis, pop operators off the stack onto the output queue. 
		-Pop the left parenthesis from the stack, but not onto the output queue. 
		-If the token at the top of the stack is a function token, pop it onto the output queue. 
		-If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. 
		-When there are no more tokens to read: 
		-While there are still operator tokens in the stack: 
		-If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. 
		-Pop the operator onto the output queue. 
		-Exit. 
		*/
		//clear the stacks
		this->m_arrObjOpStack.clear();
		this->m_arrObjOutputStack.clear();
		//if no tokens then quit out
		if(this->m_arrObjTokenCollection.empty()){return 0;}

		intUboundI = this->m_arrObjTokenCollection.size();
		for(i = 0; i < intUboundI; i++)
		{
			//get the current operator
			objCurrToken = this->m_arrObjTokenCollection.at(i);

			switch(objCurrToken.m_objTokenType)
			{
				//FIRST CHECK TO SEE IF IT IS A NUMBER OR A VARIABLE
				//-If the token is a number, then add it to the output queue.
			case NUMBER:
			case VAR :
				{
					//then it is a number or variable, push it directly onto the output stack
					this->m_arrObjOutputStack.push_back(objCurrToken);
					break;
				}
				//NEXT CHECK TO SEE IF IT IS A CONTROL CHARACTER, THEN HANDLE ACCORDINGLY
				//all open control characters are handled the same 
			case OPENPAREN :
			case OPENBLOCK :
			case OPENBRACKET :
				{
					//for Open characters, just push it onto the op stack
					this->m_arrObjOpStack.push_back(objCurrToken);
					break;
				}//end case
			case CLOSEPAREN :
				{
					bool blnOpenParenFound = false;
					//pop operators off the OP STACK and put them onto the OUTPUT STACK, until the OPENPAREN is found
					if(m_arrObjOpStack.size() <= 0 )
					{//error illegal stack size to begin with.
						return -1;
					}
					//loop through the op stack tokens
					do
					{
						objTempToken = this->m_arrObjOpStack.back();
						if(objTempToken.m_objTokenType != OPENPAREN)
						{
							//then not open parenthesis, make a copy and push it onto the output queue, then remove it from the op stack
							this->m_arrObjOutputStack.push_back(objTempToken);
							this->m_arrObjOpStack.pop_back();

						}else if(objTempToken.m_objTokenType == OPENPAREN){
							//we found the next open parenthesis, pop it off the op stack and then exit the loop
							this->m_arrObjOpStack.pop_back();
							blnOpenParenFound = true;
						}
					}while((!this->m_arrObjOpStack.empty()) && (!blnOpenParenFound));

					break;
				}//end case

			case CLOSEBLOCK:
				{
					bool blnOpenBlockFound = false;
					//pop operators off the OP STACK and put them onto the OUTPUT STACK, until the OPENBLOCK is found
					if(m_arrObjOpStack.size() <= 0 )
					{//error illegal stack size to begin with.
						return -1;
					}
					//loop through the op stack tokens
					do
					{
						objTempToken = this->m_arrObjOpStack.back();
						if(objTempToken.m_objTokenType != OPENBLOCK)
						{
							//then not open parenthesis, make a copy and push it onto the output queue, then remove it from the op stack
							this->m_arrObjOutputStack.push_back(objTempToken);
							this->m_arrObjOpStack.pop_back();

						}else if(objTempToken.m_objTokenType == OPENBLOCK){
							//we found the next open parenthesis, pop it off the op stack and then exit the loop
							this->m_arrObjOpStack.pop_back();
							blnOpenBlockFound = true;
						}
					}while((!this->m_arrObjOpStack.empty()) && (!blnOpenBlockFound));

					break;
				}//end case
			case CLOSEBRACKET:
				{
					bool blnOpenBracketFound = false;
					//pop operators off the OP STACK and put them onto the OUTPUT STACK, until the OPENBRACKET is found
					if(m_arrObjOpStack.size() <= 0 )
					{//error illegal stack size to begin with.
						return -1;
					}
					//loop through the op stack tokens
					do
					{
						objTempToken = this->m_arrObjOpStack.back();
						if(objTempToken.m_objTokenType != OPENBRACKET)
						{
							//then not open parenthesis, make a copy and push it onto the output queue, then remove it from the op stack
							this->m_arrObjOutputStack.push_back(objTempToken);
							this->m_arrObjOpStack.pop_back();

						}else if(objTempToken.m_objTokenType == OPENBRACKET){
							//we found the next open parenthesis, pop it off the op stack and then exit the loop
							this->m_arrObjOpStack.pop_back();
							blnOpenBracketFound = true;
						}
					}while((!this->m_arrObjOpStack.empty()) && (!blnOpenBracketFound));

					break;
				}//end case
			case COMMA:
				{
					bool blnOpenParenFound = false;
					//pop operators off the OP STACK and put them onto the OUTPUT STACK, until the OPENPAREN is found
					if(m_arrObjOpStack.size() <= 0 )
					{//error illegal stack size to begin with.
						return -1;
					}
					//loop through the op stack tokens
					do
					{
						objTempToken = this->m_arrObjOpStack.back();
						if(objTempToken.m_objTokenType != OPENPAREN)
						{
							//then not open parenthesis, make a copy and push it onto the output queue, then remove it from the op stack
							this->m_arrObjOutputStack.push_back(objTempToken);
							this->m_arrObjOpStack.pop_back();

						}else if(objTempToken.m_objTokenType == OPENPAREN){
							//LEAVE OPEN PARENTHESIS ON THE OP STACK
							blnOpenParenFound = true;
						}
					}while((!this->m_arrObjOpStack.empty()) && (!blnOpenParenFound));

					break;
				}//end case

				//NEXT CHECK TO SEE IF IT IS A FUNCTION 
				//-If the token is a function token, then push it onto the stack.
			default:
				{
					//then it is a function or another type of operator, check associativity and precedence with those in the stack first
					//then push it onto the stack.

					if(objCurrToken.m_objAssociativity == NON_ASSOCIATIVE)
					{
						//then the operator is non-associative, push it onto the OP STACK
						this->m_arrObjOpStack.push_back(objCurrToken);
					}else if(objCurrToken.m_objAssociativity == LEFT_ASSOCIATIVE){
						//if the operator is of LESS THAN OR EQUAL TO precedence than the operator on the top of the stack
						//then pop the operator on the OP STACK until an operator of higher precedence is found
						if(this->m_arrObjOpStack.empty())
						{
							m_arrObjOpStack.push_back(objCurrToken);
						}else{
							//loop through the op stack tokens
							bool blnHigherFound = false;
							do
							{
								objTempToken = this->m_arrObjOpStack.back();
								if(objCurrToken.m_objTokenType <= objTempToken.m_objTokenType)
								{
									//then not open parenthesis, make a copy and push it onto the output queue, then remove it from the op stack
									this->m_arrObjOutputStack.push_back(objTempToken);
									this->m_arrObjOpStack.pop_back();
								}else{
									//precedence is HIGHER
									blnHigherFound = true;
								}
							}while((!this->m_arrObjOpStack.empty()) && (!blnHigherFound));
							//now that a higher precedence operator was found
							m_arrObjOpStack.push_back(objCurrToken);
						}

					}else if(objCurrToken.m_objAssociativity == RIGHT_ASSOCIATIVE){
						//if the operator is of LESS THAN  precedence than the operator on the top of the stack
						//then pop the operator on the OP STACK until an operator of higher precedence is found
						//loop through the op stack tokens
						if(this->m_arrObjOpStack.empty() )
						{
							m_arrObjOpStack.push_back(objCurrToken);
						}else{

							bool blnHigherFound = false;
							do
							{
								objTempToken = this->m_arrObjOpStack.back();
								if(objCurrToken.m_objTokenType < objTempToken.m_objTokenType)
								{
									//then not open parenthesis, make a copy and push it onto the output queue, then remove it from the op stack
									this->m_arrObjOutputStack.push_back(objTempToken);
									this->m_arrObjOpStack.pop_back();
								}else{
									//precedence is HIGHER
									blnHigherFound = true;
								}
							}while((!this->m_arrObjOpStack.empty()) && (!blnHigherFound));
							//now that a higher precedence operator was found
							m_arrObjOpStack.push_back(objCurrToken);
						}

					}else{
						//unknown associativity
						return -1;
					}
				}//end case
			}//end switch
		}//end for loop through token collection
		/*-When there are no more tokens to read: 
		-While there are still operator tokens in the stack: 
		-If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. 
		-Pop the operator onto the output queue.
		*/
		if( (!m_arrObjOpStack.empty()) &&
			(!m_arrObjOutputStack.empty()) )
		{
			do
			{
				objTempToken = this->m_arrObjOpStack.back();
				//then not open parenthesis, make a copy and push it onto the output queue, then remove it from the op stack
				this->m_arrObjOutputStack.push_back(objTempToken);
				this->m_arrObjOpStack.pop_back();
			}while(!this->m_arrObjOpStack.empty() );
		};

		if(m_arrObjOutputStack.empty())
		{
			//no operations in final stack return error
			return -1;
		};

		//now that the output queue is finished copy it to the actual RPN Calculation stack
		structRPNUnit objRPNTemp;
		this->m_arrObjRPNQueue.clear();
		for(i = 0; i < (int)(m_arrObjOutputStack.size());i++)
		{
			objRPNTemp.m_objTokenType = this->m_arrObjOutputStack.at(i).m_objTokenType;
			objRPNTemp.m_objAssociativity = this->m_arrObjOutputStack.at(i).m_objAssociativity;
			objRPNTemp.m_strToken = this->m_arrObjOutputStack.at(i).m_strToken;
			objRPNTemp.m_dblToken = this->m_arrObjOutputStack.at(i).m_dblToken;
			this->m_arrObjRPNQueue.push_back(objRPNTemp);
		}
		return 1;
	}catch(...){

		return -1;
	}//end try catch

};

//! Check to make sure there is a balanced set of parenthesis
bool ClsFunctionEvaluator::CheckParenthesisBalanced(void)
{
	int i, intUboundI;
	int intParenCount = 0;
	intUboundI = this->m_arrObjTokenCollection.size();
	for(i = 0; i < intUboundI ; i++)
	{
		if(this->m_arrObjTokenCollection.at(i).m_objTokenType == OPENPAREN)
		{
			intParenCount += 1;
		}else if(this->m_arrObjTokenCollection.at(i).m_objTokenType == CLOSEPAREN){
			intParenCount -= 1;
		}else{
			//do nothing
		}
	}

	if(intParenCount == 0)
	{
		return true;
	}else{
		return false;
	}

};
//! Check to make sure there is a balanced set of parenthesis
bool ClsFunctionEvaluator::CheckBracketBalanced(void)
{
	int i, intUboundI;
	int intBracketCount = 0;
	intUboundI = this->m_arrObjTokenCollection.size();
	for(i = 0; i < intUboundI ; i++)
	{
		if(this->m_arrObjTokenCollection.at(i).m_objTokenType == OPENBRACKET)
		{
			intBracketCount += 1;
		}else if(this->m_arrObjTokenCollection.at(i).m_objTokenType == CLOSEBRACKET){
			intBracketCount -= 1;
		}else{
			//do nothing
		}
	}

	if(intBracketCount == 0)
	{
		return true;
	}else{
		return false;
	}
}; 
//! Check to make sure there is a balanced set of parenthesis
bool ClsFunctionEvaluator::CheckBlockBalanced(void)
{
	int i, intUboundI;
	int intBlockCount = 0;
	intUboundI = this->m_arrObjTokenCollection.size();
	for(i = 0; i < intUboundI ; i++)
	{
		if(this->m_arrObjTokenCollection.at(i).m_objTokenType == OPENBLOCK)
		{
			intBlockCount += 1;
		}else if(this->m_arrObjTokenCollection.at(i).m_objTokenType == CLOSEBLOCK){
			intBlockCount -= 1;
		}else{
			//do nothing
		}
	}

	if(intBlockCount == 0)
	{
		return true;
	}else{
		return false;
	}
};

//STRING EVALUATION FUNCTIONS

//!Evaluates from scratch the existing string, first it Tokenizes, then Compiles, then Evaluates
int ClsFunctionEvaluator::Evaluate(void)
{
	int intRetEval,intRetCompile;
	//first compile, then evaluate existing RPN stack
	intRetCompile = this->Compile();
	intRetEval = this->LinkRPNVariables();
	intRetEval = this->EvaluateExistingRPN();
	if( (intRetCompile == 1) && (intRetEval == 1) )
	{	//then successful
		return 1;
	}else{
		//then return error
		return -1;
	};
};
//!
int ClsFunctionEvaluator::EvaluateExistingRPN(void)
{
	std::vector<structRPNUnit> arrObjCalcStack;
	int intPosInsert = 0;
	int intCurrPos;
	structRPNUnit objRPNTemp;
	bool blnLinked = false;
	bool blnCalcFinished = false;
	bool blnCalcSuccessful;

	//safety check to make sure variables linked
	blnLinked = this->CheckVariablesLinked();
	if(!blnLinked){return -1;}
	//variables linked, safe to proceed
	//make a by value copy of the RPN calculation stack
	arrObjCalcStack = this->m_arrObjRPNQueue;
	intCurrPos = 0;
	do{
		//if the stack is emp
		if(arrObjCalcStack.empty()){return -1;};//stack should never get emplty

		if((arrObjCalcStack.size() == 1)&&(arrObjCalcStack.at(0).m_objTokenType == NUMBER))
		{
			//final token is a number, this is our answer
			this->m_dblCurrValue = arrObjCalcStack.at(0).m_dblToken;
			blnCalcFinished = true;
			return 1;
		}else if((arrObjCalcStack.size() == 1)&&(arrObjCalcStack.at(0).m_objTokenType == VAR)){
			//final token is a number, this is our answer
			this->m_dblCurrValue = *(arrObjCalcStack.at(0).m_ptrDblVarData);
			blnCalcFinished = true;
			return 1;
		}else if((arrObjCalcStack.size() == 1)&&(arrObjCalcStack.at(0).m_objTokenType != NUMBER)){
			//final token is not a number, quit out with an error
			this->m_dblCurrValue = -1;
			return -1;
		}else{
			this->FindNextOp(arrObjCalcStack, blnCalcSuccessful);
			if(!blnCalcSuccessful)
			{
				return -1;
			};//no successful next operation was found
		}
	}while(!blnCalcFinished);
	return 1;
};

int ClsFunctionEvaluator::FindNextOp(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnFindSuccessful)
{
	/*start scanning for an operator from the current position
	at each position, based on the operator scan the required inputs, 
	If the required inputs exist, then perform the required calculation based
	on the inputs, then replace the inputs and the operator with a single NUMBER token.
	quit out gracefully.
	*/
	//set optimistic
	int intCurrPos = 0;
	blnFindSuccessful = true;
	bool blnOperationFound = false;
	bool blnTemp;
	structRPNUnit * ptrCurrUnit = NULL;
	do
	{
		if(intCurrPos >= (int)(arrObjCalcStack.size()))
		{//then we have reached the end of the stack without finding an operator to perform
			blnFindSuccessful = false;
			return -1;
		}//q
		//safe to proceed scan forward until an operation has been found
		ptrCurrUnit = &(arrObjCalcStack.at(intCurrPos));
		switch(ptrCurrUnit->m_objTokenType)
		{

		case NOOP :
		case OPENPAREN :
		case OPENBRACKET :
		case OPENBLOCK :
		case CLOSEPAREN :
		case CLOSEBRACKET :
		case CLOSEBLOCK :
		case COMMA :
		case NUMBER:
		case VAR:
			{
				//this is not an operation, do nothing and go to the next token
				break;
			}
			//COULD BE A FUNCTION, We have found potentially the next operation, 
			//Test this operation by calling CalcOp(), if it is successful, return successful
		default:
			{
				this->CalcNextOp(arrObjCalcStack,blnTemp,intCurrPos);
				if(blnTemp)
				{
					//then calculation was successfully performed.
					blnFindSuccessful = true;
					return 1;
				}//otherwise the calc was not successful due to inadequate inputs
				//keep searching to the next operation
				break;
			}//end default
		}//end switch case statement on operators

		intCurrPos++;
	}while(!blnOperationFound);

	return 1;	
};

int ClsFunctionEvaluator::CalcNextOp(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnOpSuccessful,int intOpPos)
{
	/*start scanning for an operator from the current position
	at each position, based on the operator scan the required inputs, 
	If the required inputs exist, then perform the required calculation based
	on the inputs, then replace the inputs and the operator with a single NUMBER token.
	quit out gracefully.
	*/
	//set optimistic
	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnOpSuccessful = true;
	bool blnOperationFound = false;
	bool blnTemp;
	structRPNUnit * ptrCurrUnit = NULL;
	structRPNUnit objOutput;
	if(intOpPos >= (int)(arrObjCalcStack.size()))
	{//then we have reached the end of the stack without finding an operator to perform
		blnOpSuccessful = false;
		return -1;
	}//
	//safe to proceed scan forward until an operation has been found
	ptrCurrUnit = &(arrObjCalcStack.at(intOpPos));
	switch(ptrCurrUnit->m_objTokenType)
	{
	case ASSIGN:
		{
			this->RPN_ASSIGN(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end NEG description
	case NEG:
		{
			this->RPN_NEG(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end NEG description
	case ADD:
		{
			this->RPN_ADD(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end ADD description
	case SUB:
		{
			this->RPN_SUB(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end SUB description
	case MULT:
		{
			this->RPN_MULT(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end MULT description
	case DIV:
		{
			this->RPN_DIV(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end DIV description
	case LT:
		{
			this->RPN_LT(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end LT description
	case GT:
		{
			this->RPN_GT(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end GT description
	case LTE:
		{
			this->RPN_LTE(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end LTE description
	case GTE:
		{
			this->RPN_GTE(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end GTE description
	case NEQ:
		{
			this->RPN_NEQ(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end NEQ description
	case EQ:
		{
			this->RPN_EQ(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end EQ description
	case AND:
		{
			this->RPN_AND(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end AND description
	case OR:
		{
			this->RPN_OR(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end OR description
	case SQRT:
		{
			this->RPN_SQRT(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end SQRT description
	case POW:
		{
			this->RPN_POW(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end POW description
	case LN:
		{
			this->RPN_LOG(arrObjCalcStack,blnTemp,intOpPos,0);
			break;
		}//end LN description
	case LOG:
		{
			this->RPN_LOG(arrObjCalcStack,blnTemp,intOpPos,10);
			break;
		}//end LOG description
	case LOG2:
		{
			this->RPN_LOG(arrObjCalcStack,blnTemp,intOpPos,2);
			break;
		}//end LOG2 description
	case EXP:
		{
			this->RPN_EXP(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end EXP description
	case ABS:
		{
			this->RPN_ABS(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end ABS description
	case SIGN:
		{
			this->RPN_SIGN(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end SIGN description
	case ROUND:
		{
			this->RPN_ROUND(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end ROUND description
	case TRUNC:
		{
			this->RPN_TRUNC(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end TRUNC description
	case CEIL:
		{
			this->RPN_CEIL(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end CEIL description
	case FLOOR:
		{
			this->RPN_FLOOR(arrObjCalcStack,blnTemp,intOpPos);
			break;
		}//end FLOOR description
	case SIN:
		{
			this->RPN_SIN(arrObjCalcStack,blnTemp,intOpPos,REG);
			break;
		}//end SIN description
	case ASIN:
		{
			this->RPN_SIN(arrObjCalcStack,blnTemp,intOpPos,ARC);
			break;
		}//end ASIN description
	case SINH:
		{
			this->RPN_SIN(arrObjCalcStack,blnTemp,intOpPos,HYP);
			break;
		}//end SINH description
	case ASINH:
		{
			this->RPN_SIN(arrObjCalcStack,blnTemp,intOpPos,AHYP);
			break;
		}//end ASINH description
	case COS:
		{
			this->RPN_COS(arrObjCalcStack,blnTemp,intOpPos,REG);
			break;
		}//end COS description
	case ACOS:
		{
			this->RPN_COS(arrObjCalcStack,blnTemp,intOpPos,ARC);
			break;
		}//end ACOS description
	case COSH:
		{
			this->RPN_COS(arrObjCalcStack,blnTemp,intOpPos,HYP);
			break;
		}//end COSH description
	case ACOSH:
		{
			this->RPN_COS(arrObjCalcStack,blnTemp,intOpPos,AHYP);
			break;
		}//end ACOSH description
	case TAN:
		{
			this->RPN_TAN(arrObjCalcStack,blnTemp,intOpPos,REG);
			break;
		}//end TAN description
	case ATAN:
		{
			this->RPN_TAN(arrObjCalcStack,blnTemp,intOpPos,ARC);
			break;
		}//end ATAN description
	case TANH:
		{
			this->RPN_TAN(arrObjCalcStack,blnTemp,intOpPos,HYP);
			break;
		}//end TANH description
	case ATANH:
		{
			this->RPN_TAN(arrObjCalcStack,blnTemp,intOpPos,AHYP);
			break;
		}//end ATANH description
	default:
		{
			//throw Lps::Error (__FUNCTION__, "Function not defined within Calculator");
			break;
		}//end NOT FOUND 
	}//end switch

	if(blnTemp)
	{
		blnOpSuccessful = true;
		return 1;
	}else{
		blnOpSuccessful = false;
		return 0;
	}

	return 1;
};

//!MATH FUNCTIONS FOR THE RPN CALCULATION STACK

//!SQUARE ROOT Function
int ClsFunctionEvaluator::RPN_SQRT(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos)
{
	//FUNCTION: sqrt(input)
	//first determine if the necessary inputs are valid, if they are,
	//then get the input numbers and perform the calculation, Once the calculation is made
	//then replace the operation and input tokens with the output number token

	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnCalcSuccessful = true;
	bool blnValid;
	double dblOutput;
	structRPNUnit objOutput;

	try{
		this->ValidOpInputs(arrObjCalcStack,blnValid,intCurrPos,1);

		if(blnValid)
		{
			//then valid inputs, perform the sin calculation
			//then replace the sin calculation results with the single number
			double dblInput;
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)),dblInput);
			dblOutput = sqrt(dblInput);


			objOutput.m_objTokenType = NUMBER;
			objOutput.m_dblToken = dblOutput;
			sprintf_s(chrOutput,"%f",dblOutput);
			objOutput.m_strToken = chrOutput;

			this->ReplaceOp(arrObjCalcStack,intCurrPos - 1,intCurrPos,objOutput);
			blnCalcSuccessful = true;
			return 1;

		}else{
			blnCalcSuccessful = false;
			return 0;
		}
	}catch(...){
		blnCalcSuccessful = false;
		return -1;
	}//end try catch
};
//!POWER OR EXPONENTIAL Function
int ClsFunctionEvaluator::RPN_POW(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos)
{
	//FUNCTION: pow(Number, numdecimal)
	//first determine if the necessary inputs are valid, if they are,
	//then get the input numbers and perform the calculation, Once the calculation is made
	//then replace the operation and input tokens with the output number token

	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnCalcSuccessful = true;
	bool blnValid;
	double dblOutput;
	structRPNUnit objOutput;

	try{
		this->ValidOpInputs(arrObjCalcStack,blnValid,intCurrPos,2);

		if(blnValid)
		{
			//then valid inputs, perform the sin calculation
			//then replace the sin calculation results with the single number
			double dblNum, dblPower;
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)),dblPower);
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 2)),dblNum);

			dblOutput = pow(dblNum,dblPower);

			objOutput.m_objTokenType = NUMBER;
			objOutput.m_dblToken = dblOutput;
			sprintf_s(chrOutput,"%f",dblOutput);
			objOutput.m_strToken = chrOutput;

			this->ReplaceOp(arrObjCalcStack,intCurrPos - 2,intCurrPos,objOutput);
			blnCalcSuccessful = true;
			return 1;

		}else{
			blnCalcSuccessful = false;
			return 0;
		}
	}catch(...){
		blnCalcSuccessful = false;
		return -1;
	}//end try catch
};

//!COMMON NATURAL LOGARITHM, BASE 10 AND BASE 2 Function
int ClsFunctionEvaluator::RPN_LOG(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos,int base)
{
	//FUNCTION: log2(input)
	//first determine if the necessary inputs are valid, if they are,
	//then get the input numbers and perform the calculation, Once the calculation is made
	//then replace the operation and input tokens with the output number token

	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnCalcSuccessful = true;
	bool blnValid;
	double dblOutput;
	structRPNUnit objOutput;

	try{
		this->ValidOpInputs(arrObjCalcStack,blnValid,intCurrPos,1);

		if(blnValid)
		{
			//then valid inputs, perform the sin calculation
			//then replace the sin calculation results with the single number
			double dblInput;
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)),dblInput);
			if (base==0)
				dblOutput = log(dblInput);
			else if (base==10)
				dblOutput = log10(dblInput);
			else if (base==2)
				dblOutput = log2(dblInput);
			else
				dblOutput = 0.0;

			objOutput.m_objTokenType = NUMBER;
			objOutput.m_dblToken = dblOutput;
			sprintf_s(chrOutput,"%f",dblOutput);
			objOutput.m_strToken = chrOutput;

			this->ReplaceOp(arrObjCalcStack,intCurrPos - 1,intCurrPos,objOutput);
			blnCalcSuccessful = true;
			return 1;

		}else{
			blnCalcSuccessful = false;
			return 0;
		}
	}catch(...){
		blnCalcSuccessful = false;
		return -1;
	}//end try catch
};

//!NATURAL EXPONENTIAL Function
int ClsFunctionEvaluator::RPN_EXP(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos)
{
	//FUNCTION: exp(input)
	//first determine if the necessary inputs are valid, if they are,
	//then get the input numbers and perform the calculation, Once the calculation is made
	//then replace the operation and input tokens with the output number token

	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnCalcSuccessful = true;
	bool blnValid;
	double dblOutput;
	structRPNUnit objOutput;

	try{
		this->ValidOpInputs(arrObjCalcStack,blnValid,intCurrPos,1);

		if(blnValid)
		{
			//then valid inputs, perform the sin calculation
			//then replace the sin calculation results with the single number
			double dblInput;
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)),dblInput);
			dblOutput = exp(dblInput);


			objOutput.m_objTokenType = NUMBER;
			objOutput.m_dblToken = dblOutput;
			sprintf_s(chrOutput,"%f",dblOutput);
			objOutput.m_strToken = chrOutput;

			this->ReplaceOp(arrObjCalcStack,intCurrPos - 1,intCurrPos,objOutput);
			blnCalcSuccessful = true;
			return 1;

		}else{
			blnCalcSuccessful = false;
			return 0;
		}
	}catch(...){
		blnCalcSuccessful = false;
		return -1;
	}//end try catch
};

//!ABSOLUTE VALUE Function
int ClsFunctionEvaluator::RPN_ABS(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos)
{
	//FUNCTION: abs(input)
	//first determine if the necessary inputs are valid, if they are,
	//then get the input numbers and perform the calculation, Once the calculation is made
	//then replace the operation and input tokens with the output number token

	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnCalcSuccessful = true;
	bool blnValid;
	double dblOutput;
	structRPNUnit objOutput;

	try{
		this->ValidOpInputs(arrObjCalcStack,blnValid,intCurrPos,1);

		if(blnValid)
		{
			//then valid inputs, perform the sin calculation
			//then replace the sin calculation results with the single number
			double dblInput;
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)),dblInput);
			dblOutput = abs(dblInput);


			objOutput.m_objTokenType = NUMBER;
			objOutput.m_dblToken = dblOutput;
			sprintf_s(chrOutput,"%f",dblOutput);
			objOutput.m_strToken = chrOutput;

			this->ReplaceOp(arrObjCalcStack,intCurrPos - 1,intCurrPos,objOutput);
			blnCalcSuccessful = true;
			return 1;

		}else{
			blnCalcSuccessful = false;
			return 0;
		}
	}catch(...){
		blnCalcSuccessful = false;
		return -1;
	}//end try catch
};
//!SIGN Function
int ClsFunctionEvaluator::RPN_SIGN(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos)
{
	//FUNCTION: abs(input)
	//first determine if the necessary inputs are valid, if they are,
	//then get the input numbers and perform the calculation, Once the calculation is made
	//then replace the operation and input tokens with the output number token

	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnCalcSuccessful = true;
	bool blnValid;
	double dblOutput;
	structRPNUnit objOutput;

	try{
		this->ValidOpInputs(arrObjCalcStack,blnValid,intCurrPos,1);

		if(blnValid)
		{
			//then valid inputs, perform the sin calculation
			//then replace the sin calculation results with the single number
			double dblInput;
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)),dblInput);

			if(dblInput >= 0)
			{
				dblOutput = 1;
			}else{
				dblOutput = -1;
			}

			objOutput.m_objTokenType = NUMBER;
			objOutput.m_dblToken = dblOutput;
			sprintf_s(chrOutput,"%f",dblOutput);
			objOutput.m_strToken = chrOutput;

			this->ReplaceOp(arrObjCalcStack,intCurrPos - 1,intCurrPos,objOutput);
			blnCalcSuccessful = true;
			return 1;

		}else{
			blnCalcSuccessful = false;
			return 0;
		}
	}catch(...){
		blnCalcSuccessful = false;
		return -1;
	}//end try catch
};
//!ROUND Function
int ClsFunctionEvaluator::RPN_ROUND(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos)
{
	//FUNCTION: round(Number, numdecimal)
	//first determine if the necessary inputs are valid, if they are,
	//then get the input numbers and perform the calculation, Once the calculation is made
	//then replace the operation and input tokens with the output number token

	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnCalcSuccessful = true;
	bool blnValid;
	double dblOutput;
	structRPNUnit objOutput;

	try{
		this->ValidOpInputs(arrObjCalcStack,blnValid,intCurrPos,2);

		if(blnValid)
		{
			//then valid inputs, perform the sin calculation
			//then replace the sin calculation results with the single number
			double dblNumDecimal, dblNumber;
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)),dblNumDecimal);
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 2)),dblNumber);

			unsigned int intNumDecimal = int(round(dblNumDecimal,0));
			dblOutput = round(dblNumber,intNumDecimal);

			objOutput.m_objTokenType = NUMBER;
			objOutput.m_dblToken = dblOutput;
			sprintf_s(chrOutput,"%f",dblOutput);
			objOutput.m_strToken = chrOutput;

			this->ReplaceOp(arrObjCalcStack,intCurrPos - 2,intCurrPos,objOutput);
			blnCalcSuccessful = true;
			return 1;

		}else{
			blnCalcSuccessful = false;
			return 0;
		}
	}catch(...){
		blnCalcSuccessful = false;
		return -1;
	}//end try catch
};
//!TRUNC Function
int ClsFunctionEvaluator::RPN_TRUNC(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos)
{
	//FUNCTION: trunc(Number, numdecimal)
	//first determine if the necessary inputs are valid, if they are,
	//then get the input numbers and perform the calculation, Once the calculation is made
	//then replace the operation and input tokens with the output number token

	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnCalcSuccessful = true;
	bool blnValid;
	double dblOutput;
	structRPNUnit objOutput;

	try{
		this->ValidOpInputs(arrObjCalcStack,blnValid,intCurrPos,2);

		if(blnValid)
		{
			//then valid inputs, perform the sin calculation
			//then replace the sin calculation results with the single number
			double dblNumDecimal, dblNumber;
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)),dblNumDecimal);
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 2)),dblNumber);

			unsigned int intNumDecimal = int(round(dblNumDecimal,0));
			dblOutput = trunc(dblNumber,intNumDecimal);

			objOutput.m_objTokenType = NUMBER;
			objOutput.m_dblToken = dblOutput;
			sprintf_s(chrOutput,"%f",dblOutput);
			objOutput.m_strToken = chrOutput;

			this->ReplaceOp(arrObjCalcStack,intCurrPos - 2,intCurrPos,objOutput);
			blnCalcSuccessful = true;
			return 1;

		}else{
			blnCalcSuccessful = false;
			return 0;
		}
	}catch(...){
		blnCalcSuccessful = false;
		return -1;
	}//end try catch
};
//!CEIL Function
int ClsFunctionEvaluator::RPN_CEIL(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos)
{
	//FUNCTION:ceil(input)
	//first determine if the necessary inputs are valid, if they are,
	//then get the input numbers and perform the calculation, Once the calculation is made
	//then replace the operation and input tokens with the output number token

	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnCalcSuccessful = true;
	bool blnValid;
	double dblOutput;
	structRPNUnit objOutput;

	try{
		this->ValidOpInputs(arrObjCalcStack,blnValid,intCurrPos,1);

		if(blnValid)
		{
			//then valid inputs, perform the sin calculation
			//then replace the sin calculation results with the single number
			double dblInput1;
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)),dblInput1);
			dblOutput = ceil(dblInput1);

			objOutput.m_objTokenType = NUMBER;
			objOutput.m_dblToken = dblOutput;
			sprintf_s(chrOutput,"%f",dblOutput);
			objOutput.m_strToken = chrOutput;

			this->ReplaceOp(arrObjCalcStack,intCurrPos - 1,intCurrPos,objOutput);
			blnCalcSuccessful = true;
			return 1;

		}else{
			blnCalcSuccessful = false;
			return 0;
		}
	}catch(...){
		blnCalcSuccessful = false;
		return -1;
	}//end try catch
};
//!FLOOR Function
int ClsFunctionEvaluator::RPN_FLOOR(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos)
{
	//FUNCTION:floor(input)

	//first determine if the necessary inputs are valid, if they are,
	//then get the input numbers and perform the calculation, Once the calculation is made
	//then replace the operation and input tokens with the output number token

	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnCalcSuccessful = true;
	bool blnValid;
	double dblOutput;
	structRPNUnit objOutput;

	try{
		this->ValidOpInputs(arrObjCalcStack,blnValid,intCurrPos,1);

		if(blnValid)
		{
			//then valid inputs, perform the sin calculation
			//then replace the sin calculation results with the single number
			double dblInput1;
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)),dblInput1);
			dblOutput = floor(dblInput1);

			objOutput.m_objTokenType = NUMBER;
			objOutput.m_dblToken = dblOutput;
			sprintf_s(chrOutput,"%f",dblOutput);
			objOutput.m_strToken = chrOutput;

			this->ReplaceOp(arrObjCalcStack,intCurrPos - 1,intCurrPos,objOutput);
			blnCalcSuccessful = true;
			return 1;

		}else{
			blnCalcSuccessful = false;
			return 0;
		}
	}catch(...){
		blnCalcSuccessful = false;
		return -1;
	}//end try catch
};
//!SIN/ASIN/SINH/ASINH Function
int ClsFunctionEvaluator::RPN_SIN(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos,TrigType type)
{
	//FUNCTION: sin(input)
	//first determine if the necessary inputs are valid, if they are,
	//then get the input numbers and perform the calculation, Once the calculation is made
	//then replace the operation and input tokens with the output number token

	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnCalcSuccessful = true;
	bool blnValid;
	double dblOutput;
	structRPNUnit objOutput;

	try{
		this->ValidOpInputs(arrObjCalcStack,blnValid,intCurrPos,1);

		if(blnValid)
		{
			//then valid inputs, perform the sin calculation
			//then replace the sin calculation results with the single number
			double dblInput1;
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)),dblInput1);

			if (type == REG)
				dblOutput = sin(dblInput1);
			else if (type==ARC)
				dblOutput = asin(dblInput1);
			else if (type == HYP)
				dblOutput = sinh(dblInput1);
			else if (type==AHYP)
				dblOutput = log(dblInput1+sqrt((dblInput1*dblInput1)+1.0));
			else
				dblOutput = 0.0;

			objOutput.m_objTokenType = NUMBER;
			objOutput.m_dblToken = dblOutput;
			sprintf_s(chrOutput,"%f",dblOutput);
			objOutput.m_strToken = chrOutput;

			this->ReplaceOp(arrObjCalcStack,intCurrPos - 1,intCurrPos,objOutput);
			blnCalcSuccessful = true;
			return 1;

		}else{
			blnCalcSuccessful = false;
			return 0;
		}
	}catch(...){
		blnCalcSuccessful = false;
		return -1;
	}//end try catch
};

//!COS/ACOS/COSH/ACOSH Function
int ClsFunctionEvaluator::RPN_COS(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos,TrigType type)
{
	//FUNCTION: cos(input)
	//first determine if the necessary inputs are valid, if they are,
	//then get the input numbers and perform the calculation, Once the calculation is made
	//then replace the operation and input tokens with the output number token

	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnCalcSuccessful = true;
	bool blnValid;
	double dblOutput;
	structRPNUnit objOutput;

	try{
		this->ValidOpInputs(arrObjCalcStack,blnValid,intCurrPos,1);

		if(blnValid)
		{
			//then valid inputs, perform the sin calculation
			//then replace the sin calculation results with the single number
			double dblInput1;
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)),dblInput1);

			if (type == REG)
				dblOutput = cos(dblInput1);
			else if (type==ARC)
				dblOutput = acos(dblInput1);
			else if (type == HYP)
				dblOutput = cosh(dblInput1);
			else if ((type==AHYP) && ((dblInput1*dblInput1) >= 1.0))
				dblOutput = log(dblInput1+sqrt((dblInput1*dblInput1)-1.0));
			else
				dblOutput = 0.0;

			objOutput.m_objTokenType = NUMBER;
			objOutput.m_dblToken = dblOutput;
			sprintf_s(chrOutput,"%f",dblOutput);
			objOutput.m_strToken = chrOutput;

			this->ReplaceOp(arrObjCalcStack,intCurrPos - 1,intCurrPos,objOutput);
			blnCalcSuccessful = true;
			return 1;

		}else{
			blnCalcSuccessful = false;
			return 0;
		}
	}catch(...){
		blnCalcSuccessful = false;
		return -1;
	}//end try catch
};
//!TAN/ATAN/TANH/ATANH Function
int ClsFunctionEvaluator::RPN_TAN(std::vector<structRPNUnit> & arrObjCalcStack, bool & blnCalcSuccessful,int intCurrPos,TrigType type)
{
	//FUNCTION: tan(input)
	//first determine if the necessary inputs are valid, if they are,
	//then get the input numbers and perform the calculation, Once the calculation is made
	//then replace the operation and input tokens with the output number token

	char chrOutput[256];
	for (int i = 0; i < 256; chrOutput[i++] = '\0');
	blnCalcSuccessful = true;
	bool blnValid;
	double dblOutput;
	structRPNUnit objOutput;

	try{
		this->ValidOpInputs(arrObjCalcStack,blnValid,intCurrPos,1);

		if(blnValid)
		{
			//then valid inputs, perform the sin calculation
			//then replace the sin calculation results with the single number
			double dblInput1;
			this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)),dblInput1);

			if (type == REG)
				dblOutput = tan(dblInput1);
			else if (type==ARC)
				dblOutput = atan(dblInput1);
			else if (type == HYP)
				dblOutput = tanh(dblInput1);
			else if ((type==AHYP) && (fabs(dblInput1-1.0)) >= 0.000001)
				dblOutput = log((1.0+dblInput1)/(1.0-dblInput1))/2.0;
			else
				dblOutput = 0.0;

			objOutput.m_objTokenType = NUMBER;
			objOutput.m_dblToken = dblOutput;
			sprintf_s(chrOutput,"%f",dblOutput);
			objOutput.m_strToken = chrOutput;

			this->ReplaceOp(arrObjCalcStack,intCurrPos - 1,intCurrPos,objOutput);
			blnCalcSuccessful = true;
			return 1;

		}else{
			blnCalcSuccessful = false;
			return 0;
		}
	}catch(...){
		blnCalcSuccessful = false;
		return -1;
	}//end try catch
};

//PRIVATE MATH FUNCTIONS
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
	long lngTemp;
	//Shift the Decimal Places by the number desired and
	//then truncate that value to an integer. Then shift the decimals
	//back to the original position and return the double.
	if(numdecimals < 1){
		return floor(value);
	}else{
		lngTemp = (long)floor(value * (numdecimals *10));
		return (lngTemp/(numdecimals*10));
	};
};

double log2(double value)
{
	double ret = log(value) / log(2.0);
	return ret;
}

/*
double floor(double value, unsigned int numdecimals)
{
	long lngTemp, lngDecShift;
	double dblTemp;

	//Shift the Decimal Places by the number desired and
	//then round that value to an integer. Then shift the decimals
	//back to the original position and return the double.
	lngDecShift = (long)pow(10.0, static_cast<int>(numdecimals));
	if(value > 0.0){
		lngTemp = (long)(floor((value * lngDecShift) - 0.5) );
		dblTemp = ((double)lngTemp / (double)lngDecShift);
		return dblTemp;
	}else{
		lngTemp = (long)(floor((value * lngDecShift) + 0.5) );
		dblTemp = ((double)lngTemp / (double)lngDecShift);
		return dblTemp;
	};
};

double ceil(double value, unsigned int numdecimals)
{
	long lngTemp, lngDecShift;
	double dblTemp;

	//Shift the Decimal Places by the number desired and
	//then round that value to an integer. Then shift the decimals
	//back to the original position and return the double.
	lngDecShift = (long)pow(10.0, static_cast<int>(numdecimals));
	if(value > 0.0){
		lngTemp = (long)(ceil((value * lngDecShift) + 0.5) );
		dblTemp = ((double)lngTemp / (double)lngDecShift);
		return dblTemp;
	}else{
		lngTemp = (long)(ceil((value * lngDecShift) - 0.5) );
		dblTemp = ((double)lngTemp / (double)lngDecShift);
		return dblTemp;
	};
};

double abs(double value)
{
	if(value < 0)
	{
		return (-1) * value;
	}else{
		return value;
	}
};
*/