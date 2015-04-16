
#ifndef FUNCTIONVALIDATOR_H
#define FUNCTIONVALIDATOR_H

#include ".\CSFunctionEvaluator.h"
namespace CSTAR
{
	class CSTAR_DLLAPI CSFunctionValidator
	{
	public:
		CSFunctionValidator(void);
		~CSFunctionValidator(void);

		bool ValidateExpression(const std::vector<CSToken> & arrObjTokenCollection);

		int ValidateOperator(const std::vector<CSToken> & arrObjTokenCollection, bool & blnValidFunction, int intCurrPos);

		int ValidateFunction(const std::vector<CSToken> & arrObjTokenCollection, bool & blnValidFunction, int intCurrPos,int intNumArgs);

		//!NEG Function
		int ValidateNumber(const std::vector<CSToken> & arrObjTokenCollection, bool & blnValidFunction, int intCurrPos);
		//!NEG Function
		int ValidateVariable(const std::vector<CSToken> & arrObjTokenCollection, bool & blnValidFunction, int intCurrPos);

	};
}
#endif