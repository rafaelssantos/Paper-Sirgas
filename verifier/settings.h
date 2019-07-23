#ifndef SETTINGS_H
#define SETTINGS_H


#include <string>


class Settings {
public:
	static Settings& instance();

	void handleOptions(int argc, char* argv[]);

	std::string streamFilePath() const;

	void setStreamFilePath(const std::string& streamFilePath);

	std::string refPointFilePath() const;

	void setRefPointFilePath(const std::string& refPointFilePath);

	std::string helpMenu() const;

private:
	Settings();

	~Settings();

	std::string m_streamFilePath;

	std::string m_refPointFilePath;
};


#endif    // SETTINGS_H
