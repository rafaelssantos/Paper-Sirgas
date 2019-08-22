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

	if (Settings::instance().load(argc, argv) != ErrorCode::SUCCESS){
		exit(1);
	}

	std::cout << Settings::instance().aprioriPath(0) << "\n";
	std::cout << Settings::instance().streamPath(0) << "\n";

	Point* apriori = PointManager::instance().loadPoint(Settings::instance().aprioriPath(0));
	Point* aprioriUpdated = PointManager::instance().loadPoint(Settings::instance().aprioriPath(0));

	ifstream ifs(Settings::instance().streamPath(0));

	if (ifs.is_open()) {
		string line;

		while (true) {
			while (getline(ifs, line)) {
				if (Inspector::instance().hasCoordinates(line, apriori->label())) {
					Point* stream = PointManager::instance().extract(line);
					PointManager::instance().updateRefEpoch(*stream, aprioriUpdated);

					cout << apriori->toString() << " APRIORI POINT\n";
					cout << aprioriUpdated->toString() << " APRIORI POINT UPDATED\n";
					cout << stream->toString() << " PPP POINT\n\n";

					delete stream;
				}
			}

			if (!ifs.eof()) {
				break;
			}
			this_thread::sleep_for(chrono::seconds(5));
			ifs.clear();
		}
		ifs.close();
	}


	delete aprioriUpdated;
	aprioriUpdated = nullptr;

	delete apriori;
	apriori = nullptr;



	return app.exec();
}
