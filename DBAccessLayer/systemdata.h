#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H

#include "dbaccesslayer_global.h"
#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <QtCore\qdiriterator.h>
#include <QtCore\qstring.h>
#include <QtCore\qdebug.h>
#include <QtCore\qmath.h>
#include <QtCore\qdatetime.h>


using namespace sql;
using namespace mysql;
using namespace std;

class DBACCESSLAYER_EXPORT SystemData
{
public:
	SystemData();
	~SystemData();
	void logSystemStartingTime();
	void resetSystemStartTime();
	QTime getSystemStartTime();
	int getElapsedTimeInMilliseconds(QTime currentTime);


private:
	MySQL_Driver *driver;
	Connection *con;
	Statement *stmt;
};

#endif // SYSTEMDATA_H
