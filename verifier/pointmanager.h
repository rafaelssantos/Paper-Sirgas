#ifndef POINTMANAGER_H
#define POINTMANAGER_H

#include <QString>
#include <vector>
#include <string>

#include "point.h"


class PointManager {
public:
	static PointManager& instance();

	Point* loadPoint(std::string filePath) const;

	Point* buildPoint(std::string label, int year, int month, int day, double x, double y, double z) const;

	Point* extract(std::string line) const;

	double calcDeltaEpoch(const Point& point, const Point& groundTruth) const;

	void updateRefEpoch(const Point& point, Point* groundTruth) const;

	bool checkIntegrityNEU(const Point& point, double thresholdNorth, double threasholdEast, double threasholdUp) const;

	void exportSeriesToJsonFile(std::string dirPath, std::string label, const std::vector<Point*>& points, int count, double thresholdNorth, double threasholdEast, double threasholdUp) const;

	void exportLastCheckToJsonFile(std::string dirPath, std::string label, const Point& point, double thresholdNorth, double threasholdEast, double threasholdUp) const;


private:
	PointManager();

	~PointManager();

	void extractDateTime(const QString& dateTime, Point* point) const;

	void extractCoordinates(const QString& data, Point* point) const;

	void extractNEU(const QString& data, Point* point) const;

};



#endif    // POINTCALCULATOR_H
