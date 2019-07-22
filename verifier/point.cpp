#include "point.h"





using namespace std;





Point::Point() {
	m_x = m_y = m_z = 0.0f;    // Coordenada 0, 0, 0
	m_label = nullptr;         // Sem rótulo

	time_t rawTime;

	time(&rawTime);

	m_time = gmtime(&rawTime);    // Hora e minuto atual
}





Point::Point(float x, float y, float z) {
	m_x = x;
	m_y = y;
	m_z = z;
}




Point::Point(float x, float y, float z, string label) {
	m_x = x;
	m_y = y;
	m_z = z;
	m_label = label;
}



Point::~Point() {
	delete m_time;
}




void Point::setX(float x) {
	m_x = x;
}




float Point::getX() const {
	return m_x;
}





void Point::setY(float y) {
	m_y = y;
}




float Point::getY() const {
	return m_y;
}





void Point::setZ(float z) {
	m_z = z;
}





float Point::getZ() const {
	return m_z;
}





void Point::setLabel(string label) {
	m_label = label;
}





const string& Point::getLabel() const {
	return m_label;
}




void Point::setTime(int year, int month, int day) {
	time_t rawTime;

	delete m_time;

	m_time = localtime(&rawTime);
	m_time->tm_year = year;
	m_time->tm_mon = month;
	m_time->tm_mday = day;
}




void Point::setTime(int year, int month, int day, int hour, int min, int sec) {
	Point::setTime(year, month, day);

	m_time->tm_hour = hour;
	m_time->tm_min = min;
	m_time->tm_sec = sec;
}




tm* Point::getTime() const {
	return m_time;
}




ostream& operator<<(ostream& os, const Point& point) {
	return os << "Point(" << point.getX() << ", " << point.getY() << ", " << point.getX() << ")";
}
