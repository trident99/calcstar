#define CSTAR_DLLEXPORT

#include "HtlBasicMath.h"
#include ".\CSFunctionEvaluator.h"
#include ".\CSFunctionValidator.h"
#include ".\CSOpBaseFactory.h"


namespace CSTAR
{

	CSFunctionEvaluator::CSFunctionEvaluator(void)
	{
	}

	CSFunctionEvaluator::~CSFunctionEvaluator(void)
	{
	}

	//STRING EXPRESSION ACCESS FUNCTIONS
	//Gets the string expression
	std::string CSFunctionEvaluator::Get_strExpression(void)
	{
		return m_strExpression;	
	};

	int CSFunctionEvaluator::Set_strExpression(std::string strInput)
	{
		this->m_strExpression = strInput;
		return 1;	
	};

	//DOUBLE CURRENT VALUE ACCESS FUNCTION
	//!Gets the current value of the expression
	double CSFunctionEvaluator::Get_dblCurrValue(void)
	{
		return this->m_dblCurrValue;
	}
	//VARIABLE COLLECTION MANIPULATION;
	int CSFunctionEvaluator::AddVariable(CSVariable objNewVar)
	{
		this->m_arrObjVarCollection.push_back(objNewVar);
		return 1;
	};
	//!Delete a variable by its string variable name
	int CSFunctionEvaluator::DeleteVariable(std::string strVarName)
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
	int CSFunctionEvaluator::DeleteVariable(int intIndex)
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
	int CSFunctionEvaluator::DeleteAllVariables(void)
	{
		this->m_arrObjVarCollection.clear();
		return 1;
	};

	//!Updates the variable value
	int CSFunctionEvaluator::UpdateVariable(std::string strVarName, double dblNewVal)
	{
		int i, intUboundI;
		try{
			intUboundI = this->m_arrObjVarCollection.size();
			for(i = 0; i < intUboundI; i++)
			{
				if(strVarName == this->m_arrObjVarCollection.at(i).m_strVarName)
				{
					this->m_arrObjVarCollection.at(i).m_dblCurrVal = dblNewVal;
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


	//! Get variable by its name, returns NULL if not found
	CSVariable * CSFunctionEvaluator::Get_Variable(std::string strVarName)
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
	CSVariable *  CSFunctionEvaluator::Get_Variable(int intIndex)
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
	unsigned int CSFunctionEvaluator::Get_VariableCount(void)
	{
		return (this->m_arrObjVarCollection.size());
	};
	//VARIABLE LINKING AND INTEGRITY CHECK FUNCTIONS
	//!Link RPN Variable tokens to their appropriate variables in the variable collection
	int CSFunctionEvaluator::LinkRPNVariables(void)
	{
		int i, intUboundI, j, intUboundJ;
		CSRpnUnit * ptrUnitTemp = NULL;
		CSVariable * ptrVarTemp = NULL;
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
	int CSFunctionEvaluator::Set_VariableLink(std::string strVarName, double * ptrDblVar, bool blnExternal)
	{//ASSUMES THAT THE LINK BEING PROPOSED IS AN EXTERNAL LINK
		int i, intUboundI, intUboundJ;
		CSRpnUnit * ptrUnitTemp = NULL;
		CSVariable * ptrVarTemp = NULL;
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
	int CSFunctionEvaluator::Set_VariableData(std::string strVarName, double dblData)
	{
		int i, intUboundI;
		CSVariable * ptrVarTemp = NULL;

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
	bool CSFunctionEvaluator::CheckVariablesLinked(void)
	{
		int i, intUboundI;
		CSRpnUnit * ptrUnitTemp = NULL;
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
	unsigned int CSFunctionEvaluator::Get_TokenCount(void)
	{
		return (this->m_arrObjTokenCollection.size());
	};
	//!get the token by index number, returns NULL if not found
	CSToken * CSFunctionEvaluator::Get_Token(int intIndex)
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
	int CSFunctionEvaluator::ClearTokenCollection(void)
	{
		this->m_arrObjTokenCollection.clear();
		return 1;
	};

	//RPN QUEUE MANIPULATION
	//!Gets the number of tokens in the collection
	unsigned int CSFunctionEvaluator::Get_RPNCount(void)
	{
		return (this->m_arrObjRPNQueue.size());
	};
	//!get the token by index number, returns NULL if not found
	CSRpnUnit * CSFunctionEvaluator::Get_RPNUnit(int intIndex)
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
	int CSFunctionEvaluator::ClearRPNQueue(void)
	{
		this->m_arrObjRPNQueue.clear();
		return 1;
	};
	//!Checks the RPN stack to make sure it is a valid RPN stack
	int CSFunctionEvaluator::CheckRPNIntegrity(void)
	{
		return 1;
	};

	//STRING TOKENIZATION FUNCTIONS
	//! Creates the tokenized collection which is used to generate the RPN stack
	int CSFunctionEvaluator::TokenizeExpression(void)
	{
		//make a local copy of the string
		bool blnWhiteSpace, blnReturn;
		int pos, intNumChars, intLength;
		std::string strInput;
		CSToken objTokenTemp;
		strInput = this->m_strExpression;
		pos = 0;
		this->m_arrObjTokenCollection.clear();
		std::vector<CSToken> tokens;
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


	bool CSFunctionEvaluator::GetNextToken(std::string strInput, int posStart, int & intLength, CSToken &objReturn, bool & blnWhiteSpace)
	{
		//check
		char chrCurrent = '\0';
		CSToken objControlToken, objOpToken, objMathToken, objNumberToken, objVarToken;
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

	bool CSFunctionEvaluator::GetNextControl(std::string strInput, int posStart, int & intLength, CSToken & objReturn)
	{
		//check
		char chrCurrent = '\0';
		CSToken objOpToken, objMathToken,objNumberToken;
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

	bool CSFunctionEvaluator::GetNextOperator(std::string strInput, int posStart, int & intLength, CSToken & objReturn)
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
				objReturn.m_strToken = " - ";
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

	bool CSFunctionEvaluator::GetNextFunction(std::string strInput, int posStart, int & intLength, CSToken & objReturn)
	{
		int posTest, intSigLength;
		bool blnOpenParenDetected = false;
		char chrCurrent = '\0';
		char charTest = '\0';
		std::string strTest, strSignature;
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
		//scan until a '(' char is detected
		//check the
		posTest = posStart;
		do
		{
			if(strInput[posTest] == ' ')
			{
				//whitespace detected, before paren, NOT a function
				intLength = 0;
				return false;
			}
			if(strInput[posTest] == '(')
			{
				//function detected! get the length of the signature
				intSigLength = posTest - posStart;
				strSignature = strInput.substr(posStart,intSigLength);
				blnOpenParenDetected = true;
			}else{
				//no open paren detected yet, advance the counter
				posTest++;
			}

		}while((!blnOpenParenDetected)&& (posTest < strInput.size()));

		if(!blnOpenParenDetected)
		{
			//then can't be a function, not enough characters
			intLength = 0;
			return false;
		}

		//check the function library
		bool blnExists = GetOpBaseFactoryPtr()->DoesClassExist(strSignature);
		if(blnExists)
		{
			objReturn.m_objTokenType = FUNC;
			objReturn.m_strToken = strSignature;
			intLength = intSigLength;
			return true;
		}else{
			//then can't be a function, not in library
			intLength = 0;
			return false;
		}

		//NOT A FUNCTION
		intLength = 0;
		return false;
	};


	bool CSFunctionEvaluator::GetNextNumber(std::string strInput, int posStart, int & intLength, CSToken & objReturn)
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


	bool CSFunctionEvaluator::GetNextVariable(std::string strInput, int posStart, int & intLength, CSToken & objReturn)
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
	int CSFunctionEvaluator::Compile(void)
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
	int CSFunctionEvaluator::CompileExistingTokens(void)
	{
		CSFunctionValidator objValidator;
		int i, intUboundI;
		CSToken objCurrToken, objTempToken;
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
			CSRpnUnit objRPNTemp;
			this->m_arrObjRPNQueue.clear();
			for(i = 0; i < (int)(m_arrObjOutputStack.size());i++)
			{
				objRPNTemp.m_objTokenType = this->m_arrObjOutputStack.at(i).m_objTokenType;
				objRPNTemp.m_objAssociativity = this->m_arrObjOutputStack.at(i).m_objAssociativity;
				objRPNTemp.m_strToken = this->m_arrObjOutputStack.at(i).m_strToken;
				objRPNTemp.m_dblToken = this->m_arrObjOutputStack.at(i).m_dblToken;
				objRPNTemp.m_ptrOpEval = GetOpBaseFactoryPtr()->Create(objRPNTemp.m_strToken);
				this->m_arrObjRPNQueue.push_back(objRPNTemp);
			}
			return 1;
		}catch(...){

			return -1;
		}//end try catch

	};

	//! Check to make sure there is a balanced set of parenthesis
	bool CSFunctionEvaluator::CheckParenthesisBalanced(void)
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
	bool CSFunctionEvaluator::CheckBracketBalanced(void)
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
	bool CSFunctionEvaluator::CheckBlockBalanced(void)
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
	int CSFunctionEvaluator::Evaluate(void)
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
	int CSFunctionEvaluator::EvaluateExistingRPN(void)
	{
		std::vector<CSRpnUnit> arrObjCalcStack;
		int intPosInsert = 0;
		int intCurrPos;
		CSRpnUnit objRPNTemp;
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

	int CSFunctionEvaluator::FindNextOp(std::vector<CSRpnUnit> & arrObjCalcStack, bool & blnFindSuccessful)
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
		CSRpnUnit * ptrCurrUnit = NULL;
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

	int CSFunctionEvaluator::CalcNextOp(std::vector<CSRpnUnit> & arrObjCalcStack, bool & blnOpSuccessful,int intOpPos)
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
		CSRpnUnit * ptrCurrUnit = NULL;
		CSRpnUnit objOutput;
		if(intOpPos >= (int)(arrObjCalcStack.size()))
		{//then we have reached the end of the stack without finding an operator to perform
			blnOpSuccessful = false;
			return -1;
		}//
		//safe to proceed scan forward until an operation has been found
		ptrCurrUnit = &(arrObjCalcStack.at(intOpPos));
		
		if(!ptrCurrUnit->m_ptrOpEval)
		{
			ptrCurrUnit->CreateOpBase();
		}
		if(!ptrCurrUnit->m_ptrOpEval)
		{
			blnOpSuccessful = false;
			return 0;
		}
		ptrCurrUnit->m_ptrOpEval->OpEval(arrObjCalcStack,blnTemp,intOpPos);
		
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

}//end namespace CSTAR