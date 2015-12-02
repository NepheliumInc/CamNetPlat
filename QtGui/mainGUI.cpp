
#include "qttesting.h"
#include "QtWidgets\qapplication.h"

int mainFGH(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QtTesting w;
	w.show();
	return a.exec();
}