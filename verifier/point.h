#ifndef POINT_H
#define POINT_H


#include <ctime>
#include <ostream>
#include <string>



class Point {
public:
	Point();

	Point(float x, float y, float z);

	Point(float x, float y, float z, std::string label);

	virtual ~Point();

	void setX(float x);

	float getX() const;

	void setY(float y);

	float getY() const;

	void setZ(float z);

	float getZ() const;

	void setLabel(std::string label);

	const std::string& getLabel() const;

	void setTime(int year, int month, int day);

	void setTime(int year, int month, int day, int hour, int min, int sec);

	tm* getTime() const;

private:
	float m_x;
	float m_y;
	float m_z;

	std::string m_label;
	std::tm* m_time;
};


std::ostream& operator<<(std::ostream& os, const Point& point);



#endif    // POINT_H
