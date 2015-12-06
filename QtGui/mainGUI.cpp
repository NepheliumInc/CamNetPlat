
#include "qttesting.h"
#include "QtWidgets\qapplication.h"

int mainGH(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QtTesting w;
	w.show();
	return a.exec();
}