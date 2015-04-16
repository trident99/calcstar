#include "CalcStarApp.h"
#include <sstream>

CalcStarApp::CalcStarApp(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	this->m_ptrApplication = NULL;

	this->OnIntializeDialog();
}

CalcStarApp::~CalcStarApp()
{

}

int CalcStarApp::SetApplicationPointer( QApplication * ptrToApp)
{
	this->m_ptrApplication = ptrToApp;
	return 1;
};


//!Calls STANDARD PUBLIC FUNCTIONS THAT EVERY MAIN DIALOG SHOULD HAVE
void CalcStarApp::OnIntializeDialog(void)
{
	QString strTemp;
	QVariant varTemp;
	QStringList arrStrHorizHeaders;
	int i,j;
	//initialize the grid views
	//variables
	ui.grd_Variables->setRowCount(20);
	ui.grd_Variables->setColumnCount(2);
	//get the values of the lower and upper bounds for P1 and P2
	arrStrHorizHeaders.clear();
	strTemp = "Variable Name";
	arrStrHorizHeaders.append(strTemp);
	strTemp = "Value";
	arrStrHorizHeaders.append(strTemp);
	//set the column width while looping through
	ui.grd_Variables->setColumnWidth( 0,200);
	//set the column width while looping through
	ui.grd_Variables->setColumnWidth( 1,100);
	ui.grd_Variables->setHorizontalHeaderLabels(arrStrHorizHeaders);

	//Tokens
	ui.grd_Tokens->setRowCount(30);
	ui.grd_Tokens->setColumnCount(2);
	arrStrHorizHeaders.clear();
	strTemp = "Token Type";
	arrStrHorizHeaders.append(strTemp);
	strTemp = "Token String";
	arrStrHorizHeaders.append(strTemp);
	//set the column width while looping through
	ui.grd_Tokens->setColumnWidth( 0,200);
	//set the column width while looping through
	ui.grd_Tokens->setColumnWidth( 1,100);
	ui.grd_Tokens->setHorizontalHeaderLabels(arrStrHorizHeaders);


	//RPN Stack
	ui.grd_RPNStack->setRowCount(50);
	ui.grd_RPNStack->setColumnCount(2);
	arrStrHorizHeaders.clear();
	strTemp = "Token Type";
	arrStrHorizHeaders.append(strTemp);
	strTemp = "Value";
	arrStrHorizHeaders.append(strTemp);
	//set the column width while looping through
	ui.grd_RPNStack->setColumnWidth( 0,200);
	//set the column width while looping through
	ui.grd_RPNStack->setColumnWidth( 1,100);
	ui.grd_RPNStack->setHorizontalHeaderLabels(arrStrHorizHeaders);

	//initialize all of the menus, actions, etc.
	this->CreateActions();
	this->CreateMenus();
	this->CreateContextMenus();
	this->CreateToolBars();
	this->CreateStatusBar();
	return;
};

//!This SLOT Reads in and Sets the Variables
void CalcStarApp::OnResetVariables(void)
{
	return;	
};

//!Create the Main Menu Actions and connect them to the slots code for handling their events
void CalcStarApp::CreateActions(void)
{
	////Link the actions for Apply and Cancel
	//Link Apply Changes
	connect(ui.cmd_SaveVariables,SIGNAL(clicked() ),this,SLOT(OnCmdSaveVariables_Click() ) );

	return;
};
//!Create the Main Menu or modify the main menu programmatically
void CalcStarApp::CreateMenus(void)
{

	//Menu already created using the QT Form Designer
	//Do not need to create Menu Items programmatically.
	QAction * ptrActionTemp = NULL;

	//Editing some of the settings
	//FILE MENU ACTION CONNECTIONS
	ptrActionTemp = ui.actionExit;
	//ptrActionTemp->setIcon(QIcon(":/images/new.png"));
	ptrActionTemp->setShortcut(QKeySequence::Close);
	connect(ui.actionExit,SIGNAL(triggered() ), this, SLOT(OnFileExit() ) );

	//Connect the Tokenize Menu
	connect(ui.actionTokenize,SIGNAL(triggered() ), this, SLOT(OnTokenize() ) );
	//Connect the Tokenize Menu
	connect(ui.actionCompile,SIGNAL(triggered() ), this, SLOT(OnCompile() ) );
	//Connect the Tokenize Menu
	connect(ui.actionEvaluate,SIGNAL(triggered() ), this, SLOT(OnEvaluate() ) );

	//Connect the Tokenize Menu
	connect(ui.actionRunAllTests,SIGNAL(triggered() ), this, SLOT(OnRunAllTests() ) );
	return;
};
//!Create any popup menus for the main application GUI
void CalcStarApp::CreateContextMenus(void)
{	
	//TO BE ADDED LATER
	return;
};
//!Create any tool bars needed for the main application GUI
void CalcStarApp::CreateToolBars(void)
{	
	//TO BE ADDED LATER
	return;
};
//!Initialize the status bar for the main application GUI
void CalcStarApp::CreateStatusBar(void)
{
	//TO BE ADDED LATER
	return;
};


//SIGNALS AND SLOTS FUNCTIONS
//! This SLOT Exits the Application without saving anything
void CalcStarApp::OnFileExit(void)
{
	try{
		if(this->m_ptrApplication)
		{
			this->m_ptrApplication->exit();
		}
	}catch(...){
		//quit out gracefully
		return;
	}
	return;
};
//!This SLOT Tokenizes the expression in the m_strExpression
void CalcStarApp::OnTokenize(void)
{
	QString strTemp;
	QVariant varTemp;
	QStringList arrStrHorizHeaders;
	int i,intUboundI, intReturn;
	QTableWidgetItem * ptrCurrCell = NULL;
	CSToken * ptrTokenTemp = NULL;
	//clear the grid first
	ui.grd_Tokens->clearContents();
	arrStrHorizHeaders.clear();
	strTemp = "Token Type";
	arrStrHorizHeaders.append(strTemp);
	strTemp = "Token String";
	arrStrHorizHeaders.append(strTemp);
	////set the column width while looping through
	//ui.grd_Tokens->setColumnWidth( 0,200);
	////set the column width while looping through
	//ui.grd_Tokens->setColumnWidth( 1,100);
	ui.grd_Tokens->setHorizontalHeaderLabels(arrStrHorizHeaders);


	//Get the string to tokenize
	varTemp = ui.txt_Expression->toPlainText();
	strTemp = varTemp.toString();
	this->m_objFuncEvaluator.Set_strExpression(strTemp.toStdString());
	//tokenize the expression
	intReturn = this->m_objFuncEvaluator.TokenizeExpression();

	if( intReturn == 1)
	{
	//then successful tokenization, write it out to the grid
		intUboundI = this->m_objFuncEvaluator.Get_TokenCount();
		ui.grd_Tokens->setRowCount(intUboundI);
		for(i = 0; i < intUboundI; i++)
		{
			ptrTokenTemp = this->m_objFuncEvaluator.Get_Token(i);
			strTemp = CSTAR::TokenTypeToString(ptrTokenTemp->m_objTokenType).c_str();
			ptrCurrCell = new QTableWidgetItem();
			ui.grd_Tokens->setItem(i,0,ptrCurrCell);
			ptrCurrCell->setText(strTemp);

			strTemp = ptrTokenTemp->m_strToken.c_str();
			ptrCurrCell = new QTableWidgetItem();
			ui.grd_Tokens->setItem(i,1,ptrCurrCell);
			ptrCurrCell->setText(strTemp);
		}
		
	};


};
//!This SLOT Compile the expression in the m_strExpression
void CalcStarApp::OnCompile(void)
{
	QString strTemp;
	QVariant varTemp;
	QStringList arrStrHorizHeaders;
	int i,intUboundI, intReturn;
	QTableWidgetItem * ptrCurrCell = NULL;
	CSRpnUnit * ptrRPNUnitTemp = NULL;

	//clear the grid first
	ui.grd_RPNStack->clearContents();
	arrStrHorizHeaders.clear();
	strTemp = "RPN Token Type";
	arrStrHorizHeaders.append(strTemp);
	strTemp = "RPN Token String";
	arrStrHorizHeaders.append(strTemp);
	////set the column width while looping through
	//ui.grd_Tokens->setColumnWidth( 0,200);
	////set the column width while looping through
	//ui.grd_Tokens->setColumnWidth( 1,100);
	ui.grd_RPNStack->setHorizontalHeaderLabels(arrStrHorizHeaders);

	this->OnTokenize();
	intReturn = this->m_objFuncEvaluator.CompileExistingTokens();

	if( intReturn == 1)
	{
	//then successful tokenization, write it out to the grid


		intUboundI = this->m_objFuncEvaluator.Get_RPNCount();
		ui.grd_RPNStack->setRowCount(intUboundI);
		for(i = 0; i < intUboundI; i++)
		{
			ptrRPNUnitTemp = this->m_objFuncEvaluator.Get_RPNUnit(i);
			strTemp = CSTAR::TokenTypeToString(ptrRPNUnitTemp->m_objTokenType).c_str();
			ptrCurrCell = new QTableWidgetItem();
			ui.grd_RPNStack->setItem(i,0,ptrCurrCell);
			ptrCurrCell->setText(strTemp);

			strTemp = ptrRPNUnitTemp->m_strToken.c_str();
			ptrCurrCell = new QTableWidgetItem();
			ui.grd_RPNStack->setItem(i,1,ptrCurrCell);
			ptrCurrCell->setText(strTemp);
		}
		
	};
	return;

};
//!This SLOT Evaluate the expression in the m_strExpression
void CalcStarApp::OnEvaluate(void)
{
	QString strTemp;
	QVariant varTemp;
	QStringList arrStrHorizHeaders;
	int i,intUboundI, intReturn;
	QTableWidgetItem * ptrCurrCell = NULL;


	//clear the grid first
	ui.txt_Output->clear();
	this->OnCompile();
	this->m_objFuncEvaluator.LinkRPNVariables();
	intReturn = this->m_objFuncEvaluator.Evaluate();

	if( intReturn == 1)
	{
	//then successful tokenization, write it out to the grid
		varTemp = this->m_objFuncEvaluator.Get_dblCurrValue();
		ui.txt_Output->setText(varTemp.toString());
		OnUpdateVariables();
	};
	return;
};
//!This Slot Applys the changes made to a variable
void CalcStarApp::OnCmdSaveVariables_Click(void)
{
	CSVariable objVarTemp;
	QTableWidgetItem * ptrCurrCell = NULL;
	int i, intRowCount, intVarCount;
	QString strTemp;
	QVariant varName, varValue;
	intRowCount = ui.grd_Variables->rowCount();
	intVarCount = 0;
	this->m_objFuncEvaluator.DeleteAllVariables();
	for(i = 0; i < intRowCount; i++)
	{
		ptrCurrCell = ui.grd_Variables->item(i,0);
		if(ptrCurrCell != NULL)
		{//then there is something in the cell
			varName = ptrCurrCell->text();
			if(varName.toString() != "")
			{//then there is a variable, need to save it
				strTemp = varName.toString();
				objVarTemp.m_strVarName = strTemp.toStdString();
				ptrCurrCell = ui.grd_Variables->item(i,1);
				try{
					varValue = ptrCurrCell->text();
					if(varValue.toString() != "")
					{
						objVarTemp.m_dblCurrVal = varValue.toDouble();
					}else{
						objVarTemp.m_dblCurrVal = 0;
					}
				}catch(...){
					objVarTemp.m_dblCurrVal = 0;
				}
				//push the newly saved variable onto the collection
				this->m_objFuncEvaluator.AddVariable(objVarTemp);
			}//end if block for has string value in it
		}//end if block for valid cell

	}//end for loop 
	return;
};

//!This displayes the stored variables
void CalcStarApp::OnUpdateVariables(void)
{
	char chrBuf[256];
	CSVariable * ptrVarTemp = NULL;
	QTableWidgetItem * ptrCurrCell = NULL;
	int i, intRowCount, intVarCount;

	intRowCount = ui.grd_Variables->rowCount();
	intVarCount = 0;
	intVarCount = this->m_objFuncEvaluator.Get_VariableCount();
	//ui.grd_Variables->clear();
	
	for(i = 0; i < intVarCount; i++)
	{
		ptrVarTemp = this->m_objFuncEvaluator.Get_Variable(i);
		if(ptrVarTemp)
		{
			ptrCurrCell = ui.grd_Variables->item(i,0);
			if(ptrCurrCell != NULL)
			{//then there is something in the cell
				ptrCurrCell->setText(ptrVarTemp->m_strVarName.c_str());	
			}//end if block for valid cell
			ptrCurrCell = ui.grd_Variables->item(i,1);
			if(ptrCurrCell != NULL)
			{//then there is something in the cell
				sprintf(chrBuf,"%3.6f",ptrVarTemp->m_dblCurrVal);
				ptrCurrCell->setText(chrBuf);	
			}//end if block for valid cell
		};
	}//end for loop 
	return;
	
};

bool PassTest(double dblCalc, double dblAnswer, double dblError)
{
	return (abs(dblCalc - dblAnswer) < dblError);
}


void CalcStarApp::OnRunAllTests(void)
{	
	char chrCalc[64];
	char chrAnswer[64];
	std::string strFunc;
	std::stringstream strTestLog;
	double dblTestVal,dblAnswer, dblError;
	dblError = 0.00001f;
	//TEST 001 DEFINITION////////////////////////////////
	strTestLog << "CALCSTAR BASELINE FUNCTION TESTS#####################>>>\n";
	strTestLog << "TEST 001: common sense, add\n";
	strFunc = "2 + 2";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 4.0f;//hand calc
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 001: PASSED\n\n";
	}else{
		strTestLog << "TEST 001: FAILED!!!\n\n";
	}

	//TEST 002 DEFINITION////////////////////////////////
	strTestLog << "TEST 002: order ops test one, add, multiply\n";
	strFunc = "2 + 2 * 3";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 8.0f;//hand calc
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 002: PASSED\n\n";
	}else{
		strTestLog << "TEST 002: FAILED!!!\n\n";
	}

	//TEST 003 DEFINITION////////////////////////////////
	strTestLog << "TEST 003: order test two, ADD, DIV, MULT, SUB \n";
	strFunc = "(2 + 2)/3 * 2 - 2";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 0.66666666666667f;//TI-Voyager200
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 003: PASSED\n\n";
	}else{
		strTestLog << "TEST 003: FAILED!!!\n\n";
	}

	//TEST 004 DEFINITION////////////////////////////////
	strTestLog << "TEST 004:negative operator\n";
	strFunc = "(-10) + 5";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = -5.0f;//hand calc
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 004: PASSED\n\n";
	}else{
		strTestLog << "TEST 004: FAILED!!!\n\n";
	}

	//TEST 005 DEFINITION////////////////////////////////
	strTestLog << "TEST 005:bool and, GT, LT\n";
	strFunc = "((2 < 5)&&(6 > 3))";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 1.0f;//hand calc
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 005: PASSED\n\n";
	}else{
		strTestLog << "TEST 005: FAILED!!!\n\n";
	}

	//TEST 006 DEFINITION////////////////////////////////
	strTestLog << "TEST 006:bool or, GTE, LTE\n";
	strFunc = "((2 >= 5)||(6 <= 3))";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 0.0f;//hand calc
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 006: PASSED\n\n";
	}else{
		strTestLog << "TEST 006: FAILED!!!\n\n";
	}

	//TEST 007 DEFINITION////////////////////////////////
	strTestLog << "TEST 007:bool NOT, GTE, LTE\n";
	strFunc = "(!(3 <= 1)) + 2";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 3.0f;//hand calc
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 007: PASSED\n\n";
	}else{
		strTestLog << "TEST 007: FAILED!!!\n\n";
	}

	//TEST 008 DEFINITION////////////////////////////////
	strTestLog << "TEST 008:bool NEQ, NOT, ADD\n";
	strFunc = "(!(3 != 1)) - 5";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = -5.0f;//hand calc
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 008: PASSED\n\n";
	}else{
		strTestLog << "TEST 008: FAILED!!!\n\n";
	}


	//TEST 009 DEFINITION////////////////////////////////
	strTestLog << "TEST 009:ceiling, ADD\n";
	strFunc = "ceil(2.2) + 3.0";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 6.0f;//hand calc
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 009: PASSED\n\n";
	}else{
		strTestLog << "TEST 009: FAILED!!!\n\n";
	}


	//TEST 010 DEFINITION////////////////////////////////
	strTestLog << "TEST 010:floor, ADD\n";
	strFunc = "floor(2.75) + 3.0";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 5.0f;//hand calc
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 010: PASSED\n\n";
	}else{
		strTestLog << "TEST 010: FAILED!!!\n\n";
	}

	//TEST 011 DEFINITION////////////////////////////////
	strTestLog << "TEST 011:truncate, ADD\n";
	strFunc = "trunc(2.7558934,4)";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 2.75580f;//hand calc
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 011: PASSED\n\n";
	}else{
		strTestLog << "TEST 011: FAILED!!!\n\n";
	}

	//TEST 012 DEFINITION////////////////////////////////
	strTestLog << "TEST 012:power, ADD\n";
	strFunc = "pow(2,3) + 7.0";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 15.0f;//hand calc
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 012: PASSED\n\n";
	}else{
		strTestLog << "TEST 012: FAILED!!!\n\n";
	}

	//TEST 013 DEFINITION////////////////////////////////
	strTestLog << "TEST 013:exp, ADD, decimal number\n";
	strFunc = "(3 + 3) - exp(5.5)";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = -238.691932264f;//TI-Voyager200
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 013: PASSED\n\n";
	}else{
		strTestLog << "TEST 013: FAILED!!!\n\n";
	}

	//TEST 013 DEFINITION////////////////////////////////
	strTestLog << "TEST 013:exp, ADD, decimal number\n";
	strFunc = "4 * (10 - 3) + ln(5.5)";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 29.7047480922f;//TI-Voyager200
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 013: PASSED\n\n";
	}else{
		strTestLog << "TEST 013: FAILED!!!\n\n";
	}
	strTestLog << "CALCSTAR TRIG FUNCTION TESTS#####################>>>\n";

	//TEST 014 DEFINITION////////////////////////////////
	strTestLog << "TEST 014:sin\n";
	strFunc = "sin(2.50) * ln(5.5)";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 1.02024424592f;//TI-Voyager200
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 014: PASSED\n\n";
	}else{
		strTestLog << "TEST 014: FAILED!!!\n\n";
	}

	//TEST 015 DEFINITION////////////////////////////////
	strTestLog << "TEST 015:cos\n";
	strFunc = "6.0 - cos(2.50) * 2.0";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 7.60228723109f;//TI-Voyager200
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 015: PASSED\n\n";
	}else{
		strTestLog << "TEST 015: FAILED!!!\n\n";
	}

	//TEST 016 DEFINITION////////////////////////////////
	strTestLog << "TEST 016:cos\n";
	strFunc = "(tan((-2)) + 3.0) * 2.0";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 10.3700797265f;//TI-Voyager200
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 016: PASSED\n\n";
	}else{
		strTestLog << "TEST 016: FAILED!!!\n\n";
	}

	//TEST 017 DEFINITION////////////////////////////////
	strTestLog << "TEST 017:asin\n";
	strFunc = "asin((0.5)) * 3.0 - 2.0";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = -0.429203673205f;//TI-Voyager200
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 017: PASSED\n\n";
	}else{
		strTestLog << "TEST 017: FAILED!!!\n\n";
	}

	//TEST 018 DEFINITION////////////////////////////////
	strTestLog << "TEST 018:acos, log10\n";
	strFunc = "acos((-0.5)) + log10(5.5)";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 2.83475779189f;//TI-Voyager200
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 018: PASSED\n\n";
	}else{
		strTestLog << "TEST 018: FAILED!!!\n\n";
	}

	//TEST 019 DEFINITION////////////////////////////////
	strTestLog << "TEST 019:atan, pow\n";
	strFunc = "atan(0.5) - 2 * 4";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = -7.536352391f;//TI-Voyager200
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 019: PASSED\n\n";
	}else{
		strTestLog << "TEST 019: FAILED!!!\n\n";
	}

	//TEST 020 DEFINITION////////////////////////////////
	strTestLog << "TEST 020:sinh, exp\n";
	strFunc = "sinh(0.5) * exp(2.005) + 1";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 4.86970266776f;//TI-Voyager200
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 020: PASSED\n\n";
	}else{
		strTestLog << "TEST 020: FAILED!!!\n\n";
	}

	//TEST 021 DEFINITION////////////////////////////////
	strTestLog << "TEST 021:cosh, pow\n";
	strFunc = "cosh(0.5) * pow(2,4) - 5.5";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = 12.5420154433f;//TI-Voyager200
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 021: PASSED\n\n";
	}else{
		strTestLog << "TEST 021: FAILED!!!\n\n";
	}

	//TEST 022 DEFINITION////////////////////////////////
	strTestLog << "TEST 022:tanh, sinh\n";
	strFunc = "tanh(0.5) / sinh((-0.5))";
	strTestLog << "Eqtn: " << strFunc.c_str() << "\n";
	//evaluate
	this->m_objFuncEvaluator.Set_strExpression(strFunc);
	m_objFuncEvaluator.Evaluate();
	dblTestVal = m_objFuncEvaluator.Get_dblCurrValue();
	sprintf(chrCalc,"%6.8f",dblTestVal);
	dblAnswer = -0.88681888397f;//TI-Voyager200
	sprintf(chrAnswer,"%6.8f",dblAnswer);
	strTestLog << "Calc: " << chrCalc << " Ans: " <<  chrAnswer << "\n";
	//check to see if passed
	if(PassTest(dblTestVal,dblAnswer,dblError))
	{
		strTestLog << "TEST 022: PASSED\n\n";
	}else{
		strTestLog << "TEST 022: FAILED!!!\n\n";
	}


	///////////////////////////////////////////////////////
	//REPORT THE RESULTS///////////////////////////////////
	///////////////////////////////////////////////////////
	ui.txtTestResults->setText(strTestLog.str().c_str());

	return;

}