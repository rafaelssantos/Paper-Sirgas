#ifndef POINTMANAGER_H
#define POINTMANAGER_H

#include <QString>
#include <string>

#include "point.h"


class PointManager {
public:
	static PointManager& instance();

	Point* loadPoint(std::string filePath) const;

	Point* buildPoint(double x, double y, double z, std::string label, int year, int month, int day) const;

	Point* extract(std::string line) const;

	double calcDeltaEpoch(const Point& refPoint, const Point& point) const;

	void updateEpoch(const Point& refPoint, Point* point) const;

	bool checkIntegrity(const Point& refPoint, const Point& point, double threshold) const;


private:
	PointManager();

	~PointManager();

	void extractDateTime(const QString& dateTime, Point* point) const;

	void extractCoordinates(const QString& coordinates, Point* point) const;
};



#endif    // POINTCALCULATOR_H
