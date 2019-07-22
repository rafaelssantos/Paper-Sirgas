#include "pointmanager.h"


#include <ctime>
#include <fstream>
#include <iostream>





using namespace std;





PointManager& PointManager::instance() {
	static PointManager instance;

	return instance;
}





Point* PointManager::loadPoint(string filePath) const {
	ifstream file(filePath);

	Point* point = nullptr;

	if (file.is_open()) {
		string label;
		double x, y, z;
		double velocX, velocY, velocZ;
		int year, month, day;

		std::getline(file, label);
		file >> x;
		file >> y;
		file >> z;

		file >> year;
		file >> month;
		file >> day;

		file >> velocX;
		file >> velocY;
		file >> velocZ;

		point = new Point(x, y, z, label);

		point->dateTime()->setYear(year);
		point->dateTime()->setMonth(month);
		point->dateTime()->setDay(day);

		file.close();
	}

	return point;
}





Point* PointManager::buildPoint(double x, double y, double z, std::string label, int year, int month, int day) const {
	Point* point = new Point(x, y, z, label);


	point->dateTime()->setYear(year);
	point->dateTime()->setMonth(month);
	point->dateTime()->setDay(day);

	return point;
}





double PointManager::calcDeltaEpoch(const Point& aprioriPoint, const Point& point) const {
	long deltaSeconds = difftime(mktime(aprioriPoint.dateTime()->tm()), mktime(point.dateTime()->tm()));

	return (deltaSeconds / 86400.0) / 365.0;
}





void PointManager::updateEpoch(const Point& aprioriPoint, Point* point) const {
	double delta = calcDeltaEpoch(aprioriPoint, *point);

	point->setX(point->x() + delta * aprioriPoint.velocX());
	point->setX(point->y() + delta * aprioriPoint.velocY());
	point->setX(point->z() + delta * aprioriPoint.velocZ());
}





PointManager::PointManager() {
}





PointManager::~PointManager() {
}
