#include "pointmanager.h"


#include <QStringList>
#include <cstring>
#include <ctime>
#include <fstream>




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
		double sigmaX, sigmaY, sigmaZ;
		int year, month, day;


		std::getline(file, label);
		file >> x;
		file >> y;
		file >> z;

		file >> sigmaX;
		file >> sigmaY;
		file >> sigmaZ;

		file >> velocX;
		file >> velocY;
		file >> velocZ;

		file >> year;
		file >> month;
		file >> day;

		point = new Point(x, y, z, label);

		point->dateTime()->setYear(year);
		point->dateTime()->setMonth(month);
		point->dateTime()->setDay(day);

		point->setVelocX(velocX);
		point->setVelocY(velocY);
		point->setVelocZ(velocZ);

		point->setSigmaX(sigmaX);
		point->setSigmaY(sigmaY);
		point->setSigmaZ(sigmaZ);

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
	QString data(line.c_str());
	QStringList tokens = data.split(" ");

	Point* point = new Point();

	extractDateTime(tokens.at(0), point);
	point->setLabel(tokens.at(1).toStdString());
	tokens = data.split(QString(point->label().c_str()));
	extractCoordinates(tokens.at(1), point);

	return point;
}





double PointManager::calcDeltaEpoch(const Point& point, const Point& aprioriPoint) const {
	long deltaSeconds = difftime(mktime(point.dateTime()->tm()), mktime(aprioriPoint.dateTime()->tm()));

	return (deltaSeconds / 86400.0) / 365.0;
}





void PointManager::updateRefEpoch(const Point& point, Point* aprioriPoint) const {
	double delta = calcDeltaEpoch(point, *aprioriPoint);

//	cout <<"\nDelta: "<< delta << "\n";
//	cout <<"Vx: "<< refPoint->velocX() << "\n";
//	cout <<"Vy: "<< refPoint->velocY() << "\n";
//	cout <<"Vz: "<< refPoint->velocZ() << "\n";

	aprioriPoint->setX(aprioriPoint->x() + delta * aprioriPoint->velocX());
	aprioriPoint->setY(aprioriPoint->y() + delta * aprioriPoint->velocY());
	aprioriPoint->setZ(aprioriPoint->z() + delta * aprioriPoint->velocZ());

	aprioriPoint->dateTime()->setDay(point.dateTime()->day());
	aprioriPoint->dateTime()->setMonth(point.dateTime()->month());
	aprioriPoint->dateTime()->setYear(point.dateTime()->year());
	aprioriPoint->dateTime()->setHour(point.dateTime()->hour());
	aprioriPoint->dateTime()->setMin(point.dateTime()->min());
	aprioriPoint->dateTime()->setSec(point.dateTime()->sec());
}





bool PointManager::checkIntegrity(const Point& aprioriPoint, const Point& point, double threshold) const{
	if(abs(aprioriPoint.x() - point.x()) > threshold || abs(aprioriPoint.y() - point.y()) > threshold || abs(aprioriPoint.z() - point.z()) > threshold){
		return false;
	}
	return true;
}





PointManager::PointManager() {
}





PointManager::~PointManager() {
}



void PointManager::extractDateTime(const QString& dateTime, Point* point) const {
	QStringList tokens = dateTime.split("_");
	QStringList dateTokens = tokens.at(0).split("-");
	QStringList timeTokens = tokens.at(1).split(":");

	point->dateTime()->setYear(dateTokens.at(0).toInt());
	point->dateTime()->setMonth(dateTokens.at(1).toInt());
	point->dateTime()->setDay(dateTokens.at(2).toInt());

	point->dateTime()->setHour(timeTokens.at(0).toInt());
	point->dateTime()->setMin(timeTokens.at(1).toInt());
	point->dateTime()->setSec(static_cast<int>(timeTokens.at(2).toDouble()));
}





void PointManager::extractCoordinates(const QString& coordinates, Point* point) const {
	QStringList tokens = coordinates.split(" ");

	for (int i = 0; i < tokens.length(); i++) {
		if (tokens.at(i).contains("x", Qt::CaseInsensitive)) {
			i = i + 2;
			point->setX(tokens.at(i).toDouble());
			i = i + 2;
			point->setSigmaX(tokens.at(i).toDouble());
		} else if (tokens.at(i).contains("y", Qt::CaseInsensitive)) {
			i = i + 2;
			point->setY(tokens.at(i).toDouble());
			i = i + 2;
			point->setSigmaY(tokens.at(i).toDouble());
		} else if (tokens.at(i).contains("z", Qt::CaseInsensitive)) {
			i = i + 2;
			point->setZ(tokens.at(i).toDouble());
			i = i + 2;
			point->setSigmaZ(tokens.at(i).toDouble());
		}
	}
}
