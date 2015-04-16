#ifndef CalcStarApp_H
#define CalcStarApp_H
#include <QtGui/QMainWindow>
#include "ui_CalcStarApp.h"

#include "..\CalcStar\CalcStar.h"
using namespace CSTAR;

class CalcStarApp : public QMainWindow
{
	Q_OBJECT

public:
	CalcStarApp(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CalcStarApp();

	int SetApplicationPointer( QApplication * ptrToApp);

	//!Calls STANDARD PUBLIC FUNCTIONS THAT EVERY MAIN DIALOG SHOULD HAVE
	void OnIntializeDialog(void);
	//!Create the Main Menu Actions and connect them to the slots code for handling their events
	void CreateActions(void);
	//!Create the Main Menu or modify the main menu programmatically
	void CreateMenus(void);
	//!Create any popup menus for the main application GUI
	void CreateContextMenus(void);
	//!Create any tool bars needed for the main application GUI
	void CreateToolBars(void);
	//!Initialize the status bar for the main application GUI
	void CreateStatusBar(void);

	//Actions Methods
	public slots:
	//SIGNALS AND SLOTS FUNCTIONS
	//! This SLOT Exits the Application without saving anything
	void OnFileExit(void);
	//!This SLOT Tokenizes the expression in the m_strExpression
	void OnTokenize(void);
	//!This SLOT Compile the expression in the m_strExpression
	void OnCompile(void);
	//!This SLOT Evaluate the expression in the m_strExpression
	void OnEvaluate(void);
	//!Run All Function Evaluator Tests
	void OnRunAllTests(void);

	//!This Slot Applys the changes made to a variables and saves them in the function evaluator
	void OnCmdSaveVariables_Click(void);

	//!This SLOT Reads in and Sets the Variables
	void OnResetVariables(void);

	//!This displayes the stored variables
	void OnUpdateVariables(void);

private:

	QApplication * m_ptrApplication;

	Ui::CalcStarAppClass ui;
	//!the main GUI classes function evaluator
	CSFunctionEvaluator m_objFuncEvaluator;
};

#endif // CalcStarApp_H
