#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include "datetime.h"



class Point {
public:
	Point();

	Point(double x, double y, double z);

	Point(double x, double y, double z, std::string label);

	virtual ~Point();

	void setX(double x);

	double x() const;

	void setY(double y);

	double y() const;

	void setZ(double z);

	double z() const;

	void setLabel(std::string label);

	const std::string& label() const;

	std::string toString() const;

	DateTime* dateTime() const;

	double velocX() const;

	void setVelocX(double velocX);

	double velocY() const;

	void setVelocY(double velocY);

	double velocZ() const;

	void setVelocZ(double velocZ);

private:
	double m_x;
	double m_y;
	double m_z;
	double m_velocX;
	double m_velocY;
	double m_velocZ;

	std::string m_label;
	DateTime* m_datetime;
};

#endif    // POINT_H
