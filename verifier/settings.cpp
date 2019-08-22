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
				m_sDataFilePaths.push_back(string(argv[++i]));
			} else if (option.compare("-r") == 0 || option.compare("--reference-point-file") == 0) {
				m_refFilePaths.push_back(string(argv[++i]));
			}
		}
	}
}





Settings::Settings() {
	std::locale::global(std::locale("en_US.UTF8"));
}





Settings::~Settings() {
}




int Settings::StationCount() const {
	return m_refFilePaths.size();
}





std::string Settings::refDataPath(int index) const {
	return m_refFilePaths[index];
}





void Settings::setDataFilePath(int index, const std::string& refPointFilePath) {
	m_refFilePaths[index] = refPointFilePath;
}




void Settings::addDataFilePath(const string& refPointFilePath) {
	m_refFilePaths.push_back(refPointFilePath);
}





string Settings::helpMenu() const {
}




std::string Settings::streamDataPath(int index) const {
	return m_sDataFilePaths[index];
}





void Settings::setStreamDataPath(int index, const std::string& streamFilePath) {
	m_sDataFilePaths[index] = streamFilePath;
}



void Settings::addStreamDataPath(const string& streamFilePath) {
	m_sDataFilePaths.push_back(streamFilePath);
}
