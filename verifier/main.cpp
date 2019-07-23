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
	QCoreApplication a(argc, argv);

	Settings::instance().handleOptions(argc, argv);


	Point* refPoint = PointManager::instance().loadPoint(Settings::instance().refPointFilePath());


	ifstream ifs(Settings::instance().streamFilePath());
	if (ifs.is_open()) {
		string line;

		while (true) {
			while (getline(ifs, line)) {
				if (Inspector::instance().hasCoordinates(line, refPoint->label())) {
					Point* p = PointManager::instance().extract(line);
					cout << refPoint->toString() << " REF 2000.4\n";
					cout << p->toString() << " BNC\n";
					PointManager::instance().updateEpoch(*refPoint, p);
					cout << p->toString() << " BNC 2000.4\n\n";

					delete p;
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


	delete refPoint;
	refPoint = nullptr;

	return a.exec();
}
