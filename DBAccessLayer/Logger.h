#ifndef CAVIAR_HITS_H
#define CAVIAR_HITS_H

#include "dbaccesslayer_global.h"

#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <QtCore\qdiriterator.h>
#include <QtCore\qstring.h>
#include <QtCore\qstring.h>
#include <QtCore\qdebug.h>
#include <QtCore\qmath.h>

#include "momentstructures2.h"

#include <stdio.h>
#include <set>
using namespace std;
using namespace sql;
using namespace mysql;

class DBACCESSLAYER_EXPORT ProfileHits
{
public:
	ProfileHits();
	ProfileHits(Connection *con);
	~ProfileHits();
	void profileLog(string Video_ID , string Profile_ID , string TimeStamp);
	
	void ProfileHits::multiProfileLog(string Video_ID, vector<string>* Profile_IDs, string TimeStamp);
	void initDB();


private:
	MySQL_Driver *driver;
	Connection *con;
	Statement *stmt;
	map<string, string> dbLinkMap;
	map<string, int> dbIdMap;
};

#endif 
