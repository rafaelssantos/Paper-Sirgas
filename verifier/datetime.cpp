#include "datetime.h"



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




DateTime::DateTime(int year, int month, int day) : DateTime() {
	m_tm->tm_year = year;
	m_tm->tm_mon = month;
	m_tm->tm_mday = day;
}





DateTime::DateTime(int year, int month, int day, int hour, int min, int sec) : DateTime(year, month, day) {
	m_tm->tm_hour = hour;
	m_tm->tm_min = min;
	m_tm->tm_sec = sec;
}





DateTime::~DateTime() {
	delete m_tm;
	m_tm = nullptr;
}





std::string DateTime::toString() const {
	string output = "(";
	output += to_string(m_tm->tm_year) + "-" + to_string(m_tm->tm_mon) + "-" + to_string(m_tm->tm_mday) + ", ";
	output += to_string(m_tm->tm_hour) + ":" + to_string(m_tm->tm_min) + ":" + to_string(m_tm->tm_sec) + ")";

	return output;
}





int DateTime::year() const {
	return m_tm->tm_year;
}

void DateTime::setYear(int year) {
	m_tm->tm_year = year;
}




int DateTime::month() const {
	return m_tm->tm_mon;
}




void DateTime::setMonth(int month) {
	m_tm->tm_mon = month;
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
