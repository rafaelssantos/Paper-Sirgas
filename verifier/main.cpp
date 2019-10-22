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

#define MAX_INSTANCES_TO_JSON 100


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
	int k = 0;
	for(auto i = 0; i < Settings::instance().streamFilesCount(); i++){
		Point* point = nullptr;

		ifstream ifs(Settings::instance().streamPaths(i));

		if (ifs.is_open()) {
			string line;

			std::streampos gpos = ifs.tellg();


			while (true) {
				while (getline(ifs, line)) {
					if (PointManager::instance().hasCoordinates(line, groundTruth->label())) {
						point = PointManager::instance().extract(line);
						point->setLatitude(groundTruth->latitude());
						point->setLongitude(groundTruth->longitude());


						if(points.size() > MAX_INSTANCES_TO_JSON){
							size_t n = points.size() - MAX_INSTANCES_TO_JSON;
							for(auto j = 0u; j < n; j++){
								delete points[j];
								points[j] = nullptr;
								points.erase(points.begin(), points.begin());
							}
						}
						points.emplace_back(point);

						TimeDaemon::intance().count(PointManager::instance().checkIntegrityNEU(*point, Settings::instance().threasholdN(), Settings::instance().threasholdE(), Settings::instance().threasholdU()), *(point->dateTime()));
					}
					gpos = ifs.tellg();
				}

				Settings::instance().grabFilePaths();
				cout << "*ppp files for station: " << Settings::instance().streamFilesCount() << "\n";

				if (i < Settings::instance().streamFilesCount() - 1) {
					PointManager::instance().exportSeriesToJsonFile(Settings::instance().jsonDir(), groundTruth->label(), points, MAX_INSTANCES_TO_JSON);
					PointManager::instance().exportLastCheckToJsonFile(Settings::instance().jsonDir(), groundTruth->label(), *point, Settings::instance().threasholdN(), Settings::instance().threasholdE(), Settings::instance().threasholdU());
					cout << "Processing file ["<< Settings::instance().streamPaths(i) << "]\n";
					break;
				}
				else{
					ifs.clear();
					ifs.seekg(gpos, ios::beg);

					TimeDaemon::intance().dailyLabels();
					TimeDaemon::intance().dailyOkValues();
					TimeDaemon::intance().dailyValues();
					TimeDaemon::intance().dailyPercent();

					PointManager::instance().exportDailyToCsv(Settings::instance().jsonDir(), Settings::instance().label(), TimeDaemon::intance().dailyLabels(), TimeDaemon::intance().dailyPercent(), TimeDaemon::intance().dailyOkValues(), TimeDaemon::intance().dailyValues());
					PointManager::instance().exportSeriesToJsonFile(Settings::instance().jsonDir(), groundTruth->label(), points, MAX_INSTANCES_TO_JSON);
					PointManager::instance().exportLastCheckToJsonFile(Settings::instance().jsonDir(), groundTruth->label(), *point, Settings::instance().threasholdN(), Settings::instance().threasholdE(), Settings::instance().threasholdU());
					this_thread::sleep_for(chrono::seconds(5));
					cout << "[Pos: " << gpos  <<"] last file ["<< Settings::instance().streamPaths(i) << "]\n";
				}
				k++;
			}
			ifs.close();
		}

	}


	delete groundTruth;
	groundTruth = nullptr;





	return app.exec();
}
