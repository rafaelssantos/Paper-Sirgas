#ifndef SETTINGS_H
#define SETTINGS_H


#include <string>
#include <vector>
#include "errorcode.h"


class Settings {
public:
	static Settings& instance();

	ErrorCode load(int argc, char* argv[]);

	std::string streamPath(int index) const;

	std::string aprioriPath(int index) const;

	std::string helpMenu() const;

	int pointCount() const;



private:
	Settings();

	~Settings();

	ErrorCode handle();

	std::vector<std::string> m_streamFilePaths;
	std::vector<std::string> m_aprioriFilePaths;
	std::vector<std::string> m_pointLabels;

	std::string m_settingFilePath;

	std::string m_aprioriDir;
	std::string m_streamDir;
};


#endif    // SETTINGS_H
