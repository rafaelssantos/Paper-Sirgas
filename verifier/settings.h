#ifndef SETTINGS_H
#define SETTINGS_H


#include <string>
#include <vector>
#include <map>
#include "errorcode.h"


class Settings {
public:
	static Settings& instance();

	ErrorCode load(int argc, char* argv[]);

	std::string streamPaths(int index) const;

	std::string groundTruthPaths(int index) const;

	std::string helpMenu() const;

	void grabFilePaths();

	int filesCount() const;

	std::string label() const;

	std::string jsonDir() const;


	double threasholdN() const;

	void setThreasholdN(double threasholdN);

	double threasholdE() const;

	void setThreasholdE(double threasholdE);

	double threasholdU() const;

	void setThreasholdU(double threasholdU);

private:
	Settings();

	~Settings();

	std::vector<std::string> m_streamFilePaths;
	std::vector<std::string> m_groundTruthFilePaths;
	std::string m_label;

	std::string m_settingsFilePath;

	std::string m_jsonDir;
	std::string m_groundTruthDir;
	std::string m_streamDir;

	double m_threasholdN;
	double m_threasholdE;
	double m_threasholdU;


	void extractThresholds(std::string threshold);
};


#endif    // SETTINGS_H
