#include "settings.h"

#include <locale>
#include <iostream>
#include <fstream>
#include <QString>
#include <QDir>


using namespace std;





Settings& Settings::instance() {
	static Settings instance;

	return instance;
}




ErrorCode Settings::load(int argc, char* argv[]) {
	if (argc < 3) {
		cout << "Incorrect number of parameters.\n";
		cout << "Type: -h or --help for help menu.\n\n";
		return ErrorCode::ERR_PARAMS;
	}
	else {
		for (auto i = 1; i < argc; i++) {
			string option(argv[i]);
			if (option.compare("-h") == 0 || option.compare("--help") == 0) {
				cout << helpMenu();
			} else if (option.compare("-i") == 0 || option.compare("--input-settings") == 0) {
				m_settingsFilePath =  string(argv[++i]);
			}
		}
		std::ifstream input(m_settingsFilePath);

		if(input.is_open()){
			getline(input, m_label);
			getline(input, m_groundTruthDir);
			getline(input, m_streamDir);

			input.close();

			return ErrorCode::SUCCESS;
		}

		return ErrorCode::ERR_SETTINGS_FILE;
	}
}





Settings::Settings() {
	std::locale::global(std::locale("en_US.UTF8"));
}





Settings::~Settings() {
}





int Settings::filesCount() const {
	return m_groundTruthFilePaths.size();
}




string Settings::label() const {
	return m_label;
}





std::string Settings::groundTruthPaths(int index) const {
	return m_groundTruthFilePaths[index];
}


string Settings::helpMenu() const {
}


ErrorCode Settings::grabFilePaths() {
	QDir streamDir(QString(m_streamDir.c_str()));
	QStringList streamFileNames = streamDir.entryList(QStringList() << "*.ppp", QDir::Files);
	m_streamFilePaths.clear();
	foreach(QString fileName, streamFileNames) {
		if(fileName.startsWith(QString(m_label.c_str()))){
			m_streamFilePaths.push_back(m_streamDir + "/" + fileName.toStdString());
		}
	}



	QDir groundTruthDir(QString(m_groundTruthDir.c_str()));
	QStringList gdThDFileNames = groundTruthDir.entryList(QStringList() << "*.gdth", QDir::Files);
	m_groundTruthFilePaths.clear();
	foreach(QString fileName, gdThDFileNames) {
		if(fileName.startsWith(QString(m_label.c_str()))){
			m_groundTruthFilePaths.push_back(m_groundTruthDir + "/" + fileName.toStdString());
		}
	}


	if(m_groundTruthFilePaths.size() != m_streamFilePaths.size()) {
		return ErrorCode::ERR_APRIORI_X_STREAM;
	}

	return ErrorCode::SUCCESS;
}




string Settings::streamPaths(int index) const {
	return m_streamFilePaths[index];
}
