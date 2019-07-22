#ifndef POINTMANAGER_H
#define POINTMANAGER_H

#include <string>
#include "point.h"


class PointManager {
public:
	static PointManager& instance();

	Point* loadPoint(std::string filePath) const;

	Point* buildPoint(double x, double y, double z, std::string label, int year, int month, int day) const;

	double calcDeltaEpoch(const Point& aprioriPoint, const Point& point) const;

	void updateEpoch(const Point& aprioriPoint, Point* point) const;


private:
	PointManager();

	~PointManager();
};



#endif    // POINTCALCULATOR_H
