#ifndef TIMEDAEMON_H
#define TIMEDAEMON_H

#include <ctime>
#include <map>
#include <vector>
#include <string>
#include "datetime.h"


class TimeDaemon {
public:
	static TimeDaemon& intance();

	double deltaMin(const DateTime& dateTime1, const DateTime& dateTime2);

	void count(bool ok, const DateTime& instance);

	float percent30min();

	float percent60min();

	float percent120min();

	float percentAllmin();

	bool isOld() const;

	std::vector<int> dailyOkValues() const;

	std::vector<int> dailyValues() const;

	std::vector<float> dailyPercent() const;

	std::vector<std::string> dailyLabels() const;



private:
	TimeDaemon();

	virtual ~TimeDaemon();

	void updateReferences(const DateTime& instance);

	void setOld(const DateTime& instance);


	int m_valuesInAllmin;
	int m_okValuesInAllmin;

	int m_valuesIn120min;
	int m_okValuesIn120min;

	int m_valuesIn60min;
	int m_okValuesIn60min;

	int m_valuesIn30min;
	int m_okValuesIn30min;

	bool m_old;

	DateTime* m_lastAllmin;
	DateTime* m_last120min;
	DateTime* m_last60min;
	DateTime* m_last30min;
	DateTime* m_last5min;

	std::map<std::string, int> m_okValuesDaily;
	std::map<std::string, int> m_valuesDaily;
	std::map<std::string, DateTime*> m_labelDaily;

};

#endif // TIMEDAEMON_H
