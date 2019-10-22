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

	bool checkIntegrityNEU(const Point& point, double thresholdNorth, double threasholdEast, double threasholdUp) const;

	void exportSeriesToJsonFile(std::string dirPath, std::string label, const std::vector<Point*>& points, int count) const;

	void exportLastCheckToJsonFile(std::string dirPath, std::string label, const Point& point, double thresholdNorth, double threasholdEast, double threasholdUp) const;

	void exportDailyToCsv(std::string dirPath, std::string label, const std::vector<std::string>& labels, const std::vector<float>& percent, const std::vector<int>& okValues, const std::vector<int>& values);

	bool hasCoordinates(std::string line, std::string label);


private:
	PointManager();

	~PointManager();

	void extractDateTime(const QString& dateTime, Point* point) const;

	void extractXYZCoord(const QString& data, Point* point) const;

	void extractNEUCoord(const QString& data, Point* point) const;

};



#endif    // POINTCALCULATOR_H
