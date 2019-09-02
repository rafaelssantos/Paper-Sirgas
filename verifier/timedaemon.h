#ifndef TIMEDAEMON_H
#define TIMEDAEMON_H

#include <ctime>
#include "datetime.h"


class TimeDaemon {
public:
	static TimeDaemon& intance();

	double deltaMin(const DateTime& dateTime1, const DateTime& dateTime2);

	void count(bool ok, const DateTime& instance);

	float percent30min();

	float percent60min();

	float percent120min();

	bool isOld();


private:
	TimeDaemon();

	~TimeDaemon();

	void updateReferences(const DateTime& instance);

	int m_valuesIn120min;
	int m_okValuesIn120min;

	int m_valuesIn60min;
	int m_okValuesIn60min;

	int m_valuesIn30min;
	int m_okValuesIn30min;

	DateTime* m_last120min;
	DateTime* m_last60min;
	DateTime* m_last30min;
};

#endif // TIMEDAEMON_H
