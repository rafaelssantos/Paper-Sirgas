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

	Point(double x, double y, double z, std::string label, double north, double east, double up);

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

	double latitude() const;

	void setLatitude(double latitude);

	double longitude() const;

	void setLongitude(double longitude);

	double north() const;

	void setNorth(double north);

	double east() const;

	void setEast(double east);

	double up() const;

	void setUp(double up);

	double sigmaNorth() const;

	void setSigmaNorth(double sigmaNorth);

	double sigmaEast() const;

	void setSigmaEast(double sigmaEast);

	double sigmaUp() const;

	void setSigmaUp(double sigmaUp);



private:
	double m_x;
	double m_y;
	double m_z;

	double m_sigmaX;
	double m_sigmaY;
	double m_sigmaZ;

	double m_velocX;
	double m_velocY;
	double m_velocZ;

	double m_north;
	double m_east;
	double m_up;

	double m_sigmaNorth;
	double m_sigmaEast;
	double m_sigmaUp;

	double m_latitude;
	double m_longitude;

	std::string m_label;
	DateTime* m_datetime;
};

#endif    // POINT_H
