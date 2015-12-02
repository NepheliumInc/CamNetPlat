#include "systemdata.h"

SystemData::SystemData()
{

}

SystemData::~SystemData()
{

}

void SystemData::logSystemStartingTime()
{
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "root");

	stmt = con->createStatement();
	stmt->execute("USE camera");

	QTime currentTime = QTime::currentTime();
	string init_second = to_string(currentTime.second());
	string init_minute = to_string(currentTime.minute());
	string init_hour = to_string(currentTime.hour());
	string queryInserTime = "INSERT INTO system_initiate values( " + init_second + ", " + init_minute + ", " + init_hour + ")";
	stmt->execute(queryInserTime);

}

void SystemData::resetSystemStartTime()
{
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "root");

	stmt = con->createStatement();
	stmt->execute("USE camera");
	stmt->execute("DELETE FROM system_initiate");
	

}

QTime SystemData::getSystemStartTime()
{
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "root");

	stmt = con->createStatement();
	stmt->execute("USE camera");
	ResultSet *getSytemInitTime = stmt->executeQuery("select * from system_initiate");

	int init_second;
	int init_minute; 
	int init_hour;
	if (getSytemInitTime->next())
	{
		init_second = getSytemInitTime->getInt("init_seconds");
		init_minute = getSytemInitTime->getInt("init_minutes");
		init_hour	= getSytemInitTime->getInt("init_hour");
	}

	QTime systemStartTime(init_hour, init_minute, init_second);

	return systemStartTime;
}

int SystemData::getElapsedTimeInMilliseconds(QTime startingTime)
{
	QTime currentTime = QTime::currentTime();
	int timeinmilli = (currentTime.hour() - startingTime.hour()) * 60 * 60 * 1000
				+ (currentTime.minute() - startingTime.minute()) * 60 * 1000
				+ (currentTime.second() - startingTime.second()) * 1000;

	return timeinmilli;
}