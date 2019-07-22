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
		float x, y, z;
		int year, month, day;

		std::getline(file, label);
		file >> x;
		file >> y;
		file >> z;

		file >> year;
		file >> month;
		file >> day;

		point = new Point(x, y, z, label);


		//		point->setTime(year, month, day);


		file.close();
	}

	return point;
}





Point* PointManager::buildPoint(float x, float y, float z, string label, int year, int month, int day) const {
	Point* point = new Point(x, y, z, label);

	point->setTime(year, month, day);

	return point;
}





void PointManager::updateCoordByEpoch(const Point& referencePoint, float velX, float velY, float velZ, Point* point) const {
	double deltaSeconds;

	deltaSeconds = difftime(mktime(referencePoint.getTime()), mktime(point->getTime()));

	std::cout << "[Teste] Remover: " << deltaSeconds << "\n";
}





PointManager::PointManager() {
}





PointManager::~PointManager() {
}
