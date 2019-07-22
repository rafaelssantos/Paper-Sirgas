#include "point.h"





using namespace std;





Point::Point() {
	m_x = m_y = m_z = 0.0f;
	m_label = "";
	m_datetime = new DateTime();
	m_velocX = 0;
	m_velocY = 0;
	m_velocZ = 0;
}





Point::Point(double x, double y, double z) : Point() {
	m_x = x;
	m_y = y;
	m_z = z;
}




Point::Point(double x, double y, double z, string label) : Point(x, y, z) {
	m_label = label;
}



Point::~Point() {
	delete m_datetime;
	m_datetime = nullptr;
}




void Point::setX(double x) {
	m_x = x;
}




double Point::x() const {
	return m_x;
}





void Point::setY(double y) {
	m_y = y;
}




double Point::y() const {
	return m_y;
}





void Point::setZ(double z) {
	m_z = z;
}





double Point::z() const {
	return m_z;
}





void Point::setLabel(string label) {
	m_label = label;
}





const string& Point::label() const {
	return m_label;
}




string Point::toString() const {
	string output = "";

	output += m_label + "(" + to_string(m_x) + ", " + to_string(m_y) + ", " + to_string(m_z) + ", ";
	output += m_datetime->toString();
	output += ")";

	return output;
}

DateTime* Point::dateTime() const {
	return m_datetime;
}

double Point::velocX() const {
	return m_velocX;
}

void Point::setVelocX(double velocX) {
	m_velocX = velocX;
}

double Point::velocY() const {
	return m_velocY;
}

void Point::setVelocY(double velocY) {
	m_velocY = velocY;
}

double Point::velocZ() const {
	return m_velocZ;
}

void Point::setVelocZ(double velocZ) {
	m_velocZ = velocZ;
}
