#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
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
	string refFilePath = "";
	string streamFilePath = "";
	Point* refPoint = nullptr;



	checkNumberOfParams(argc);


	for (int i = 0; i < argc; i++) {
		string param(argv[i]);

		if (param.compare("--reference-file") == 0 || param.compare("-r") == 0) {
			string input(argv[++i]);
			refFilePath = input;
		} else if (param.compare("--stream-file") == 0 || param.compare("-s") == 0) {
			string input(argv[++i]);
			streamFilePath = input;
		}
	}


	refPoint = PointManager::instance().loadPoint(refFilePath);

	std::ifstream ifs(streamFilePath);

	if (ifs.is_open()) {
		std::string line;

		while (true) {
			while (std::getline(ifs, line)) {
				if (Inspector::instance().hasCoordinates(line, refPoint->label())) {
					Point* p = PointManager::instance().extract(line);
					std::cout << p->toString() << "\n";
				}
			}
			if (!ifs.eof()) {
				break;
			}
			std::this_thread::sleep_for(std::chrono::seconds(5));
			ifs.clear();
		}
		ifs.close();
	}

	return 0;
}
