#include "CalcStarApp.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CalcStarApp w;
	w.show();
	return a.exec();
}
