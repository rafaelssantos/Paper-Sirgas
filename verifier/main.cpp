#include <iostream>

#include "point.h"
#include "pointmanager.h"



using namespace std;





int main(int argc, char* argv[]) {
	string pointFilepath = "";

	if (argc < 3) {
		cout << "Incorrect number of parameters.\n";
		cout << "Type: -h or --help for help menu.\n\n";

		return 0;
	}

	for (int i = 0; i < argc; i++) {
		string param(argv[i]);

		if (param.compare("--input") == 0 || param.compare("-i") == 0) {
			string input(argv[++i]);

			pointFilepath = input;
		}
	}



	Point* aprioriPoint = PointManager::instance().loadPoint(pointFilepath);
	std::cout << aprioriPoint->toString() << "\n";



	//	std::ifstream ifs("/home/rafaelssantos/workspaces/bnc-sirgas/PPTE00BRA_U_20192030000_01D_01S.ppp");

	//	if (ifs.is_open()) {
	//		std::string line;
	//		while (true) {
	//			while (std::getline(ifs, line)) {
	//				std::cout << line << "\n";
	//			}
	//			if (!ifs.eof()) {
	//				break;    // Ensure end of read was EOF.
	//			}

	//			ifs.clear();

	//			// You may want a sleep in here to avoid
	//			// being a CPU hog.
	//		}

	//		std::this_thread::sleep_for(std::chrono::seconds(5));
	//	}

	return 0;
}
