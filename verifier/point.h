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

	Point(const Point &point);


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

	double sigmaX() const;

	void setSigmaX(double sigmaX);

	double sigmaY() const;

	void setSigmaY(double sigmaY);

	double sigmaZ() const;

	void setSigmaZ(double sigmaZ);



private:
	double m_x;
	double m_y;
	double m_z;
	double m_velocX;
	double m_velocY;
	double m_velocZ;

	double m_sigmaX;
	double m_sigmaY;
	double m_sigmaZ;

	std::string m_label;
	DateTime* m_datetime;
};

#endif    // POINT_H
