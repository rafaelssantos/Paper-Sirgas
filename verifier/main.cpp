#include <QCoreApplication>
#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include "settings.h"
#include "point.h"
#include "pointmanager.h"
#include "timedaemon.h"



using namespace std;



void checkNumberOfParams(int argc) {
	if (argc < 3) {
		cout << "Incorrect number of parameters.\n";
		cout << "Type: -h or --help for help menu.\n\n";

		exit(0);
	}
}





int main(int argc, char* argv[]) {
	QCoreApplication app(argc, argv);
	vector<Point*> points;

	if (Settings::instance().load(argc, argv) != ErrorCode::SUCCESS){
		exit(1);
	}

	Settings::instance().grabFilePaths();

	Point* groundTruth = PointManager::instance().loadPoint(Settings::instance().groundTruthPaths(0));

	cout << "Starting check for " << Settings::instance().label() << "\n";

	for(auto i = 0; i < Settings::instance().filesCount(); i++){
		Point* point = nullptr;

		ifstream ifs(Settings::instance().streamPaths(i));

		if (ifs.is_open()) {
			string line;

			while (true) {

				while (getline(ifs, line)) {
					if (PointManager::instance().hasCoordinates(line, groundTruth->label())) {
						point = PointManager::instance().extract(line);
						point->setLatitude(groundTruth->latitude());
						point->setLongitude(groundTruth->longitude());


						if(points.size() > 500){
							size_t n = points.size() - 500;
							for(auto i = 0; i < n; i++){
								delete points[i];
								points[i] = nullptr;
								points.erase(points.begin(), points.begin());
							}
						}

						points.emplace_back(point);
						TimeDaemon::intance().count(PointManager::instance().checkIntegrityNEU(*point, Settings::instance().threasholdN(), Settings::instance().threasholdE(), Settings::instance().threasholdU()), *(point->dateTime()));
					}
				}

				Settings::instance().grabFilePaths();

				if (ifs.eof() && i < Settings::instance().filesCount() - 1) {
					PointManager::instance().exportSeriesToJsonFile(Settings::instance().jsonDir(), groundTruth->label(), points, 300, Settings::instance().threasholdN(), Settings::instance().threasholdE(), Settings::instance().threasholdU());
					PointManager::instance().exportLastCheckToJsonFile(Settings::instance().jsonDir(), groundTruth->label(), *point, Settings::instance().threasholdN(), Settings::instance().threasholdE(), Settings::instance().threasholdU());
					cout << "Reading next File ["<< Settings::instance().streamPaths(i+1) <<"]...\n";
					break;
				}
				else{
					PointManager::instance().exportSeriesToJsonFile(Settings::instance().jsonDir(), groundTruth->label(), points, 300, Settings::instance().threasholdN(), Settings::instance().threasholdE(), Settings::instance().threasholdU());
					PointManager::instance().exportLastCheckToJsonFile(Settings::instance().jsonDir(), groundTruth->label(), *point, Settings::instance().threasholdN(), Settings::instance().threasholdE(), Settings::instance().threasholdU());
					this_thread::sleep_for(chrono::seconds(5));
					cout << "Trying lasf file ["<< Settings::instance().streamPaths(i) << "]...\n";
				}
			}
			ifs.close();
		}
	}


	delete groundTruth;
	groundTruth = nullptr;





	return app.exec();
}
