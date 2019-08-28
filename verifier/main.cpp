#include <QCoreApplication>
#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include "settings.h"
#include "inspector.h"
#include "point.h"
#include "pointmanager.h"




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

	if (Settings::instance().load(argc, argv) != ErrorCode::SUCCESS || Settings::instance().grabFilePaths() != ErrorCode::SUCCESS){
		exit(1);
	}

	int filesCount = Settings::instance().filesCount();

	for(auto i = 0; i < filesCount; i++){
		Point* groundTruth = PointManager::instance().loadPoint(Settings::instance().groundTruthPaths(i));
		Point* point = nullptr;

		ifstream ifs(Settings::instance().streamPaths(i));

		if (ifs.is_open()) {
			string line;

			while (filesCount <= Settings::instance().filesCount()) {
				while (getline(ifs, line)) {
					if (Inspector::instance().hasCoordinates(line, groundTruth->label())) {
						point = PointManager::instance().extract(line);
						point->setLatitude(groundTruth->latitude());
						point->setLongitude(groundTruth->longitude());

						points.emplace_back(point);
					}
				}
				Settings::instance().grabFilePaths();

				if (ifs.eof() && i < filesCount - 1) {
					break;
				}
				else{
					PointManager::instance().exportSeriesToJsonFile(Settings::instance().jsonDir(), groundTruth->label(), points, 300, Settings::instance().threasholdN(), Settings::instance().threasholdE(), Settings::instance().threasholdU());
					PointManager::instance().exportLastCheckToJsonFile(Settings::instance().jsonDir(), groundTruth->label(), *point, Settings::instance().threasholdN(), Settings::instance().threasholdE(), Settings::instance().threasholdU());
					this_thread::sleep_for(chrono::seconds(5));
				}
			}
			ifs.close();
		}

		delete groundTruth;
		groundTruth = nullptr;
	}







	return app.exec();
}
