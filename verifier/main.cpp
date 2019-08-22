#include <QCoreApplication>
#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>
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

	if (Settings::instance().load(argc, argv) != ErrorCode::SUCCESS || Settings::instance().grabFilePaths() != ErrorCode::SUCCESS){
		exit(1);
	}

	int filesCount = Settings::instance().filesCount();

	for(auto i = 0; i < filesCount; i++){
		Point* groundTruth = PointManager::instance().loadPoint(Settings::instance().groundTruthPaths(i));
		Point* groundTruthCurTime = PointManager::instance().loadPoint(Settings::instance().groundTruthPaths(i));

		ifstream ifs(Settings::instance().streamPaths(i));

		if (ifs.is_open()) {
			string line;

			while (filesCount <= Settings::instance().filesCount()) {
				while (getline(ifs, line)) {
					if (Inspector::instance().hasCoordinates(line, groundTruth->label())) {
						Point* stream = PointManager::instance().extract(line);
						PointManager::instance().updateRefEpoch(*stream, groundTruthCurTime);

						cout << groundTruth->toString() << " GROUND TRUTH\n";
						cout << groundTruthCurTime->toString() << " GROUND TRUTH CUR TIME\n";
						cout << stream->toString() << " PPP POINT\n\n";

						delete stream;
					}
				}
				Settings::instance().grabFilePaths();

				if (ifs.eof() && i < filesCount - 1) {
					break;
				}
				else{
					this_thread::sleep_for(chrono::seconds(5));
				}
			}
			ifs.close();
		}

		delete groundTruthCurTime;
		groundTruthCurTime = nullptr;

		delete groundTruth;
		groundTruth = nullptr;
	}







	return app.exec();
}
