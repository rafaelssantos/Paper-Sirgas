#include "settings.h"

#include <locale>
#include <iostream>


using namespace std;





Settings& Settings::instance() {
	static Settings instance;

	return instance;
}




void Settings::handleOptions(int argc, char* argv[]) {
	if (argc < 3) {
		cout << "Incorrect number of parameters.\n";
		cout << "Type: -h or --help for help menu.\n\n";
		exit(1);
	} else {
		for (auto i = 1; i < argc; i++) {
			string option(argv[i]);
			if (option.compare("-h") == 0 || option.compare("--help") == 0) {
				cout << helpMenu();
			} else if (option.compare("-s") == 0 || option.compare("--stream-file") == 0) {
				m_streamFilePath = string(argv[++i]);
			} else if (option.compare("-r") == 0 || option.compare("--reference-point-file") == 0) {
				m_refPointFilePath = string(argv[++i]);
			}
		}
	}
}





Settings::Settings() {
	std::locale::global(std::locale("en_US.UTF8"));
}





Settings::~Settings() {
}





std::string Settings::refPointFilePath() const {
	return m_refPointFilePath;
}





void Settings::setRefPointFilePath(const std::string& refPointFilePath) {
	m_refPointFilePath = refPointFilePath;
}





string Settings::helpMenu() const {
}





std::string Settings::streamFilePath() const {
	return m_streamFilePath;
}





void Settings::setStreamFilePath(const std::string& streamFilePath) {
	m_streamFilePath = streamFilePath;
}
