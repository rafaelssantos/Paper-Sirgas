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

		ifstream ifs(Settings::instance().streamPaths(i));

		if (ifs.is_open()) {
			string line;

			while (filesCount <= Settings::instance().filesCount()) {
				while (getline(ifs, line)) {
					if (Inspector::instance().hasCoordinates(line, groundTruth->label())) {
						Point* p = PointManager::instance().extract(line);
						p->setLatitude(groundTruth->latitude());
						p->setLongitude(groundTruth->longitude());

						points.emplace_back(p);
					}
				}
				Settings::instance().grabFilePaths();

				if (ifs.eof() && i < filesCount - 1) {
					break;
				}
				else{
					PointManager::instance().exportToJsonFile(Settings::instance().jsonDir(), groundTruth->label(), points, 0.05, 0.05, 0.10);
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
