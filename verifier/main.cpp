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



	Point* refPoint = PointManager::instance().loadPoint(Settings::instance().refDataPath(0));
	Point* refPointCur = PointManager::instance().loadPoint(Settings::instance().refDataPath(0));
	int countTotal = 0;
	int countOk = 0;
	double percent;

	ifstream ifs(Settings::instance().streamDataPath(0));
	if (ifs.is_open()) {
		string line;

		while (true) {
			while (getline(ifs, line)) {
				if (Inspector::instance().hasCoordinates(line, refPoint->label())) {
					Point* p = PointManager::instance().extract(line);

					cout << refPoint->toString() << " REFERENCE POINT\n";
					PointManager::instance().updateRefEpoch(*p, refPointCur);
					cout << refPointCur->toString() << " REFERENCE POINT UPDATED\n";
					cout << p->toString() << " BNC POINT PPP\n\n";

					countTotal++;
					if(PointManager::instance().checkIntegrity(*refPointCur, *p, 0.30)){
						countOk++;
					}
					percent = ((1.0 * countOk ) / countTotal) * 100.0;

					cout << "Percentage: " << percent << "%\n\n";

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
