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

#ifndef CLS_FUNCTION_EVALUATOR_H
#define CLS_FUNCTION_EVALUATOR_H

#include "CSStructs.h"
#include "CSRpnUnit.h"

namespace CSTAR
{
	

	class CSTAR_DLLAPI CSFunctionEvaluator
	{
	public:
		CSFunctionEvaluator(void);
		~CSFunctionEvaluator(void);

		//PUBLIC MEMBER VARIABLES AND FUNCTIONS/////////////////////////////////////////////////////////////

		//STRING EXPRESSION ACCESS FUNCTIONS
		//!Sets the expression string
		int Set_strExpression(std::string strInput);
		//Gets the string expression
		std::string Get_strExpression(void);

		//DOUBLE CURRENT VALUE ACCESS FUNCTION
		//!Gets the current value of the expression
		double Get_dblCurrValue(void);

		//!Evaluates the existing RPN stack.
		int EvaluateExistingRPN(void);
		//!Link RPN Variable tokens to their appropriate variables in the variable collection
		int LinkRPNVariables(void);

		//! Creates the tokenized collection which is used to generate the RPN stack
		int TokenizeExpression(void);
		//! Compiles the existing token stack
		int CompileExistingTokens(void);

		//!Gets the number of tokens in the collection
		unsigned int Get_TokenCount(void);
		//!get the token by index number, returns NULL if not found
		CSToken * Get_Token(int intIndex);

	public:
		//VARIABLE COLLECTION MANIPULATION;
		//!Add a Variable
		int AddVariable(CSVariable objNewVar);
		//!Delete a variable by its string variable name
		int DeleteVariable(std::string strVarName);
		//!Delete a variable by index number
		int DeleteVariable(int intIndex);
		//!Deletes All Variables
		int DeleteAllVariables(void);
		//! Get variable by its name, returns NULL if not found
		CSVariable * Get_Variable(std::string strVarName);
		//!Get variable by its index, returns NULL if not found
		CSVariable *  Get_Variable(int intIndex);
		//!Updates the variable value
		int UpdateVariable(std::string strVarName, double dblNewVal);
		//gets the number of variables in the collection
		unsigned int Get_VariableCount(void);

		//VARIABLE LINKING AND INTEGRITY CHECK FUNCTIONS
		//!	Sets a variable link for the RPN Unit, ASSUMED EXTERNAL LINK
		int Set_VariableLink(std::string strVarName, double * ptrDblVar, bool blnExternal);
		//! Sets the data to the matching variable name
		int Set_VariableData(std::string strVarName, double dblData);
		//!Checks the RPN queue to make sure all variables are linked properly
		bool CheckVariablesLinked(void);

		//TOKEN COLLECTION MANIPULATION
		//!	Clears the token collection
		int ClearTokenCollection(void);

		//RPN QUEUE MANIPULATION
		//!Gets the number of tokens in the collection
		unsigned int Get_RPNCount(void);
		//!get the token by index number, returns NULL if not found
		CSRpnUnit * Get_RPNUnit(int intIndex);
		//!	Clears the RPN Queue
		int ClearRPNQueue(void);
		//!Checks the RPN stack to make sure it is a valid RPN stack
		int CheckRPNIntegrity(void);

		//STRING TOKENIZATION FUNCTIONS
		//! Gets the next Token 
		bool GetNextToken(std::string strInput, int posStart, int & intLength, CSToken & objReturn, bool & blnWhiteSpace);
		//!Checks to see if the Next Token is a Control character
		virtual bool GetNextControl(std::string strInput, int posStart, int & intLength, CSToken & objReturn);
		//!Checks to see if the Next Token is an Operator
		virtual bool GetNextOperator(std::string strInput, int posStart, int & intLength, CSToken & objReturn);
		//!Checks to see if the Next Token is a Function from the predefined List
		virtual bool GetNextFunction(std::string strInput, int posStart, int & intLength, CSToken & objReturn);
		//!Checks to see if the Next Token is a Number
		virtual bool GetNextNumber(std::string strInput, int posStart, int & intLength, CSToken & objReturn);
		//!Checks to see if the Next Toke is a Variable
		virtual bool GetNextVariable(std::string strInput, int posStart, int & intLength, CSToken & objReturn);

		//STRING COMPILATION FUNCTIONS
		//! Compiles from scratch the existing string, First it Tokenizes it, then it compiles the RPN
		int Compile(void);
		//! Check to make sure there is a balanced set of parenthesis
		bool CheckParenthesisBalanced(void);
		//! Check to make sure there is a balanced set of parenthesis
		bool CheckBracketBalanced(void);
		//! Check to make sure there is a balanced set of parenthesis
		bool CheckBlockBalanced(void);

		//STRING EVALUATION FUNCTIONS
		//!Evaluates from scratch the existing string, first it Tokenizes, then Compiles, then Evaluates
		int Evaluate(void);
		//!Finds the next available Operation token in the stack to calculate
		int FindNextOp(std::vector<CSRpnUnit> & arrObjCalcStack, bool & blnFindSuccessful);
		//!Calculate the operation at intOpPos by calling the specific math function for that operation
		virtual int CalcNextOp(std::vector<CSRpnUnit> & arrObjCalcStack, bool & blnOpSuccessful,int intOpPos);

		//PROTECTED MEMBER VARIABLES AND FUNCTIONS//////////////////////////////////////////////////////////////
	protected:
		//!The function to be Expression to be Evaluated by the Function Evaluator
		std::string m_strExpression;

		//!The current resultant expression value
		double m_dblCurrValue;

		//!The internal vector collection of Variables
		std::vector<CSVariable> m_arrObjVarCollection;

		//! The tokenized version of the string expression
		std::vector<CSToken> m_arrObjTokenCollection;

		//!The vector of RPN units for the RPN queue
		std::vector<CSRpnUnit> m_arrObjRPNQueue;

		//PRIVATE MEMBER VARIABLES AND FUNCTIONS//////////////////////////////////////////////////////////////
	private:
		//These two vectors are used in compilation only
		//! The tokenized version of the string expression
		std::vector<CSToken> m_arrObjOpStack;
		//! The tokenized version of the string expression
		std::vector<CSToken> m_arrObjOutputStack;

		//!The active calculation stack used for internal calculation / updateing the m_dblCurrValue
		std::vector<CSRpnUnit> m_arrObjCalcStack;
		//!Clears the calculation stack.
		int ClearCalcStack(void);
	};

}//end namespace CSTAR


#endif