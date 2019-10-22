#include "pointmanager.h"


#include <QStringList>
#include <cmath>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include "timedaemon.h"


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
	extractXYZCoord(tokens.at(1), point);
	extractNEUCoord(tokens.at(1), point);

	return point;
}




bool PointManager::checkIntegrityNEU(const Point& point, double thresholdNorth, double threasholdEast, double threasholdUp) const{
	if(abs(point.north()) > thresholdNorth || abs(point.east()) > threasholdEast || abs(point.up()) > threasholdUp){
		return false;
	}
	return true;
}







void PointManager::exportSeriesToJsonFile(string dirPath, string label, const vector<Point*> &points, int count) const {
	ofstream ofs(dirPath + "/" + label + ".json");

	string jsonString = "[\n";
	if(ofs.is_open()){
		size_t n = 0;

		for(auto i = static_cast<unsigned>(max(static_cast<int>(points.size() - count), 0)); i < points.size(); i++){
			jsonString += "{";


			jsonString += "\"datetime\":\"" + points[i]->dateTime()->dateToString() + " " + points[i]->dateTime()->timeToString() + "\", ";

			jsonString += "\"north\":" + to_string(points[i]->north()) + ", ";
			jsonString += "\"east\":" + to_string(points[i]->east()) + ", ";
			jsonString += "\"up\":" + to_string(points[i]->up()) + ", ";

			jsonString += "\"sigma-north\": [" + to_string(points[i]->north() - points[i]->sigmaNorth()) +", " + to_string(points[i]->north() + points[i]->sigmaNorth()) + "], ";
			jsonString += "\"sigma-east\": [" + to_string(points[i]->east() - points[i]->sigmaEast()) +", " + to_string(points[i]->east() + points[i]->sigmaEast()) + "], ";
			jsonString += "\"sigma-up\": [" + to_string(points[i]->up() - points[i]->sigmaUp()) +", " + to_string(points[i]->up() + points[i]->sigmaUp()) + "]";


			n++;
			if(n != points.size() && n != static_cast<size_t>(count)){
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




void PointManager::exportLastCheckToJsonFile(string dirPath, string label, const Point& point, double thresholdNorth, double threasholdEast, double threasholdUp) const {
	ofstream ofs(dirPath + "/LAST_" + label + ".json");

	string jsonString = "{\n";
	if(ofs.is_open()){
		jsonString += "\"datetime\":\"" + point.dateTime()->dateToString() + " " + point.dateTime()->timeToString() + "\", ";
		jsonString += "\"lat\":" + to_string(point.latitude()) + ", ";
		jsonString += "\"long\":" + to_string(point.longitude()) + ", ";
		jsonString += "\"north\":" + to_string(point.north()) + ", ";
		jsonString += "\"east\":" + to_string(point.east()) + ", ";
		jsonString += "\"up\":" + to_string(point.up()) + ", ";

		jsonString += "\"min30\":" + to_string(TimeDaemon::intance().percent30min()) + ", ";
		jsonString += "\"min60\":" + to_string(TimeDaemon::intance().percent60min()) + ", ";
		jsonString += "\"min120\":" + to_string(TimeDaemon::intance().percent120min()) + ", ";
		jsonString += "\"minAll\":" + to_string(TimeDaemon::intance().percentAllmin()) + ", ";
		jsonString += "\"old\":" + to_string(TimeDaemon::intance().isOld()) + ", ";

		jsonString += "\"status\":" + to_string(checkIntegrityNEU(point, thresholdNorth, threasholdEast, threasholdUp)) + "";
		jsonString += "}";

		ofs << jsonString;
		ofs.close();
	}
}


void PointManager::exportDailyToCsv(string dirPath, string label, const std::vector<string>& labels, const std::vector<float>& percent, const std::vector<int>& okValues, const std::vector<int>& values) {
	ofstream ofs(dirPath + "/" + label + ".csv");

	string output = "";
	if(ofs.is_open()){
		output += "day, percent, ok, all\n";
		for(auto i = 0u; i < labels.size(); i++){
			output += labels[i] +  ", " + to_string(percent[i])  + ", " + to_string(okValues[i]) + ", " + to_string(values[i]) + "\n";
		}
		ofs << output;
		ofs.close();
	}
}




bool PointManager::hasCoordinates(string line, string label) {
	if(line.find(label) != string::npos){
		return true;
	}
	return false;
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





void PointManager::extractXYZCoord(const QString& data, Point* point) const {
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



void PointManager::extractNEUCoord(const QString& data, Point* point) const {
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
