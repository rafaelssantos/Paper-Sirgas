#include "datetime.h"
#include <iostream>


using namespace std;



DateTime::DateTime() {
	m_tm = new struct tm;
	m_tm->tm_year = 0;
	m_tm->tm_mon = 0;
	m_tm->tm_mday = 0;
	m_tm->tm_hour = 0;
	m_tm->tm_min = 0;
	m_tm->tm_sec = 0;
}




DateTime::DateTime(int year, int month, int day) {
	m_tm = new struct tm;
	m_tm->tm_year = year - 1900;
	m_tm->tm_mon = month - 1;
	m_tm->tm_mday = day;
	m_tm->tm_hour = 0;
	m_tm->tm_min = 0;
	m_tm->tm_sec = 0;
}





DateTime::DateTime(int year, int month, int day, int hour, int min, int sec) {
	m_tm = new struct tm;
	m_tm->tm_year = year - 1900;
	m_tm->tm_mon = month - 1;
	m_tm->tm_mday = day;
	m_tm->tm_hour = hour;
	m_tm->tm_min = min;
	m_tm->tm_sec = sec;
}



DateTime::DateTime(const DateTime& dateTime) {
	m_tm = new struct tm;
	m_tm->tm_year = dateTime.m_tm->tm_year;
	m_tm->tm_mon = dateTime.m_tm->tm_mon;
	m_tm->tm_mday = dateTime.m_tm->tm_mday;
	m_tm->tm_hour = dateTime.m_tm->tm_hour;
	m_tm->tm_min = dateTime.m_tm->tm_min;
	m_tm->tm_sec = dateTime.m_tm->tm_sec;
}





DateTime::~DateTime() {
	delete m_tm;
	m_tm = nullptr;
}





std::string DateTime::toString() const {
	string month = to_string(m_tm->tm_mon + 1);
	string day = to_string(m_tm->tm_mday);
	string hour = to_string(m_tm->tm_hour);
	string min = to_string(m_tm->tm_min);
	string sec = to_string(m_tm->tm_sec);

	month = string(2 - month.length(), '0') + month;
	day = string(2 - day.length(), '0') + day;
	hour = string(2 - hour.length(), '0') + hour;
	min = string(2 - min.length(), '0') + min;
	sec = string(2 - sec.length(), '0') + sec;

	string output = "";
	output += to_string(m_tm->tm_year + 1900) + "-" + month + "-" + day + " ";
	output += hour + ":" + min + ":" + sec;

	return output;
}


string DateTime::timeToString() const {
	string hour = to_string(m_tm->tm_hour);
	string min = to_string(m_tm->tm_min);
	string sec = to_string(m_tm->tm_sec);

	hour = string(2 - hour.length(), '0') + hour;
	min = string(2 - min.length(), '0') + min;
	sec = string(2 - sec.length(), '0') + sec;

	string output = hour + ":" + min + ":" + sec;

	return output;
}

string DateTime::dateToString() const {
	string month = to_string(m_tm->tm_mon + 1);
	string day = to_string(m_tm->tm_mday);

	month = string(2 - month.length(), '0') + month;
	day = string(2 - day.length(), '0') + day;


	string output = to_string(m_tm->tm_year + 1900) + "-" + month + "-" + day;


	return output;
}





int DateTime::year() const {
	return m_tm->tm_year + 1900;
}

void DateTime::setYear(int year) {
	m_tm->tm_year = year - 1900;
}




int DateTime::month() const {
	return m_tm->tm_mon + 1;
}




void DateTime::setMonth(int month) {
	m_tm->tm_mon = month - 1;
}




int DateTime::day() const {
	return m_tm->tm_mday;
}





void DateTime::setDay(int day) {
	m_tm->tm_mday = day;
}




int DateTime::hour() const {
	return m_tm->tm_hour;
}

void DateTime::setHour(int hour) {
	m_tm->tm_hour = hour;
}

int DateTime::min() const {
	return m_tm->tm_min;
}

void DateTime::setMin(int min) {
	m_tm->tm_min = min;
}

int DateTime::sec() const {
	return m_tm->tm_sec;
}

void DateTime::setSec(int sec) {
	m_tm->tm_sec = sec;
}

std::tm* DateTime::tm() const {
	return m_tm;
}
