#ifndef SETTINGS_H
#define SETTINGS_H


#include <string>
#include <vector>


class Settings {
public:
	static Settings& instance();

	void handleOptions(int argc, char* argv[]);

	std::string streamDataPath(int index) const;

	void setStreamDataPath(int index, const std::string& streamDataPath);

	void addStreamDataPath(const std::string& streamDataPath);

	std::string refDataPath(int index) const;

	void setDataFilePath(int index, const std::string& refDataPath);

	void addDataFilePath(const std::string& refDataPath);

	std::string helpMenu() const;

	int StationCount() const;



private:
	Settings();

	~Settings();

	std::vector<std::string> m_sDataFilePaths;

	std::vector<std::string> m_refFilePaths;
};


#endif    // SETTINGS_H
