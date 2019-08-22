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
	} else {
		for (auto i = 1; i < argc; i++) {
			string option(argv[i]);
			if (option.compare("-h") == 0 || option.compare("--help") == 0) {
				cout << helpMenu();
			} else if (option.compare("-i") == 0 || option.compare("--input-settings") == 0) {
				m_settingFilePath =  string(argv[++i]);
			}
		}
		return handle();
	}
}





Settings::Settings() {
	std::locale::global(std::locale("en_US.UTF8"));
}





Settings::~Settings() {
}



ErrorCode Settings::handle() {
	std::ifstream input(m_settingFilePath);

	if(input.is_open()){
		getline(input, m_aprioriDir);
		getline(input, m_streamDir);

		std::string label;
		while(getline(input, label)){
			m_pointLabels.push_back(label);
		}
		input.close();

		m_streamFilePaths.clear();
		QDir streamDir(QString(m_streamDir.c_str()));
		QStringList streamFilePaths = streamDir.entryList(QStringList() << "*.ppp", QDir::Files);
		foreach(QString filePath, streamFilePaths) {
			m_streamFilePaths.push_back(m_streamDir + "/" + filePath.toStdString());
//			std::cout << filePath.toStdString() << "\n";
		}

		m_aprioriFilePaths.clear();
		QDir aprioriDir(QString(m_aprioriDir.c_str()));
		QStringList aprioriFilePaths = aprioriDir.entryList(QStringList() << "*.apr", QDir::Files);
		foreach(QString filePath, aprioriFilePaths) {
			m_aprioriFilePaths.push_back(m_aprioriDir + "/" + filePath.toStdString());
//			std::cout << filePath.toStdString() << "\n";
		}

		if(m_aprioriFilePaths.size() != m_streamFilePaths.size()) {
			return ErrorCode::ERR_APRIORI_X_STREAM;
		}
		return ErrorCode::SUCCESS;
	}

	return ErrorCode::ERR_SETTINGS_FILE;
}




int Settings::pointCount() const {
	return m_aprioriFilePaths.size();
}





std::string Settings::aprioriPath(int index) const {
	return m_aprioriFilePaths[index];
}


string Settings::helpMenu() const {
}




std::string Settings::streamPath(int index) const {
	return m_streamFilePaths[index];
}
