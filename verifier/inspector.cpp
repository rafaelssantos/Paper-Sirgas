#include "inspector.h"



using namespace std;





Inspector& Inspector::instance() {
	static Inspector instance;

	return instance;
}




bool Inspector::hasCoordinates(std::string line, std::string label) {
	if (line.find(label) != string::npos) {
		return true;
	}

	return false;
}



Inspector::Inspector() {
}



Inspector::~Inspector() {
}
