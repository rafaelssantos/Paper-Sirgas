#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <string>


class Inspector {
public:
	static Inspector& instance();

	bool hasCoordinates(std::string line, std::string label);

private:
	Inspector();

	~Inspector();
};

#endif    // INSPECTOR_H
