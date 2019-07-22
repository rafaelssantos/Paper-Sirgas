#include "pointmanager.h"


#include <cstring>
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





Point* PointManager::extract(string line) const {
	Point* point = new Point();
	string label;
	double x, y, z;
	double sigmaX, sigmaY, sigmaZ;
	int year, month, day;


	char* dateTime;
	char cLine[line.length() + 1];

	strcpy(cLine, line.c_str());

	dateTime = strtok(cLine, " ");


	extractDateTime(dateTime, point);


	return point;
}





double PointManager::calcDeltaEpoch(const Point& refPoint, const Point& point) const {
	long deltaSeconds = difftime(mktime(refPoint.dateTime()->tm()), mktime(point.dateTime()->tm()));

	return (deltaSeconds / 86400.0) / 365.0;
}





void PointManager::updateEpoch(const Point& refPoint, Point* point) const {
	double delta = calcDeltaEpoch(refPoint, *point);

	point->setX(point->x() + delta * refPoint.velocX());
	point->setX(point->y() + delta * refPoint.velocY());
	point->setX(point->z() + delta * refPoint.velocZ());
}





PointManager::PointManager() {
}





PointManager::~PointManager() {
}



void PointManager::extractDateTime(char* data, Point* point) const {
	char* date;
	char* time;
	char* token;


	date = strtok(data, "_");
	time = strtok(nullptr, "_");


	token = strtok(date, "-");
	point->dateTime()->setYear(atoi(token));
	token = strtok(nullptr, "-");
	point->dateTime()->setMonth(atoi(token));
	token = strtok(nullptr, "-");
	point->dateTime()->setDay(atoi(token));


	token = strtok(time, ":");
	point->dateTime()->setHour(atoi(token));
	token = strtok(nullptr, ":");
	point->dateTime()->setMin(atoi(token));
	token = strtok(nullptr, ":");
	point->dateTime()->setSec(static_cast<int>(atof(token)));
}
