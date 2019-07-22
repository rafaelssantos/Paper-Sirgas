#ifndef POINTMANAGER_H
#define POINTMANAGER_H

#include <string>
#include "point.h"


class PointManager {
public:
	static PointManager& instance();

	Point* loadPoint(std::string filePath) const;

	Point* buildPoint(float x, float y, float z, std::string label, int year, int month, int day) const;

	void updateCoordByEpoch(const Point& referencePoint, float velX, float velY, float velZ, Point* point) const;


private:
	PointManager();

	~PointManager();
};

#endif    // POINTCALCULATOR_H
