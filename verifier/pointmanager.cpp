#include "pointmanager.h"


#include <QStringList>
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
		double sigmaX, sigmaY, sigmaZ;
		double latitude, longitude;
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

		file >> latitude;
		file >> longitude;

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

		point->setLatitude(latitude);
		point->setLongitude(longitude);

		file.close();
	}

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
	extractNEU(tokens.at(1), point);

	return point;
}




double PointManager::calcDeltaEpoch(const Point& point, const Point& groundTruth) const {
	long deltaSeconds = difftime(mktime(point.dateTime()->tm()), mktime(groundTruth.dateTime()->tm()));

	return (deltaSeconds / 86400.0) / 365.0;
}





void PointManager::updateRefEpoch(const Point& point, Point* groundTruth) const {
	double delta = calcDeltaEpoch(point, *groundTruth);

	groundTruth->setX(groundTruth->x() + delta * groundTruth->velocX());
	groundTruth->setY(groundTruth->y() + delta * groundTruth->velocY());
	groundTruth->setZ(groundTruth->z() + delta * groundTruth->velocZ());

	groundTruth->dateTime()->setDay(point.dateTime()->day());
	groundTruth->dateTime()->setMonth(point.dateTime()->month());
	groundTruth->dateTime()->setYear(point.dateTime()->year());
	groundTruth->dateTime()->setHour(point.dateTime()->hour());
	groundTruth->dateTime()->setMin(point.dateTime()->min());
	groundTruth->dateTime()->setSec(point.dateTime()->sec());
}





bool PointManager::checkIntegrityNEU(const Point& point, double thresholdNorth, double threasholdEast, double threasholdUp) const{
	if(abs(point.north()) > thresholdNorth || abs(point.east()) > threasholdEast || abs(point.up()) > threasholdUp){
		return false;
	}
	return true;
}







void PointManager::exportToJsonFile(string dirPath, string label, const vector<Point*> &points, double thresholdNorth, double threasholdEast, double threasholdUp) const {
	ofstream ofs(dirPath + "/" + label + ".json");

	string jsonString = "[\n";
	if(ofs.is_open()){
		size_t count = 0;
		for(auto point = points.begin(); point != points.end(); point++){
//			jsonSring += "\"" + (*point)->dateTime()->toString() + "\" : {";
			jsonString += "{";

			jsonString += "\"label\":\"" + (*point)->label() + "\", ";

			jsonString += "\"lat\":\"" + to_string((*point)->latitude()) + "\", ";
			jsonString += "\"long\":\"" + to_string((*point)->longitude()) + "\", ";

			jsonString += "\"year\":\"" + to_string((*point)->dateTime()->year()) + "\", ";
			jsonString += "\"month\":\"" + to_string((*point)->dateTime()->month()) + "\", ";
			jsonString += "\"day\":\"" + to_string((*point)->dateTime()->day()) + "\", ";
			jsonString += "\"hour\":\"" + to_string((*point)->dateTime()->hour()) + "\", ";
			jsonString += "\"min\":\"" + to_string((*point)->dateTime()->min()) + "\", ";
			jsonString += "\"sec\":\"" + to_string((*point)->dateTime()->sec()) + "\", ";


			jsonString += "\"north\":\"" + to_string((*point)->north()) + "\", ";
			jsonString += "\"east\":\"" + to_string((*point)->east()) + "\", ";
			jsonString += "\"up\":\"" + to_string((*point)->up()) + "\", ";

			jsonString += "\"sigmaNorth\":\"" + to_string((*point)->sigmaNorth()) + "\", ";
			jsonString += "\"sigmaEast\":\"" + to_string((*point)->sigmaEast()) + "\", ";
			jsonString += "\"sigmaUp\":\"" + to_string((*point)->sigmaUp()) + "\", ";

			jsonString += "\"status\":\"" + to_string(checkIntegrityNEU(**point, thresholdNorth, threasholdEast, threasholdUp)) + "\"";

			count++;
			if(count != points.size()){
				jsonString += "},\n";
			}
			else{
				jsonString += "}\n";

			}
		}
		jsonString += "]";

		ofs << jsonString;
		ofs.close();
	}

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





void PointManager::extractCoordinates(const QString& data, Point* point) const {
	QStringList tokens = data.split(" ");

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



void PointManager::extractNEU(const QString& data, Point* point) const {
	QStringList tokens = data.split(" ");
	for (int i = 0; i < tokens.length(); i++) {
		if (tokens.at(i).contains("dN", Qt::CaseInsensitive)) {
			i = i + 2;
			point->setNorth(tokens.at(i).toDouble());
			i = i + 2;
			point->setSigmaNorth(tokens.at(i).toDouble());
		} else if (tokens.at(i).contains("dE", Qt::CaseInsensitive)) {
			i = i + 2;
			point->setEast(tokens.at(i).toDouble());
			i = i + 2;
			point->setSigmaEast(tokens.at(i).toDouble());
		} else if (tokens.at(i).contains("dU", Qt::CaseInsensitive)) {
			i = i + 2;
			point->setUp(tokens.at(i).toDouble());
			i = i + 2;
			point->setSigmaUp(tokens.at(i).toDouble());
		}
	}
}
