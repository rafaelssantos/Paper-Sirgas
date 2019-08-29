#include "timedaemon.h"
#include "pointmanager.h"
#include <iostream>

using namespace std;



TimeDaemon& TimeDaemon::intance() {
	static TimeDaemon instance;
	return instance;
}



double TimeDaemon::deltaMin(const DateTime& dateTime1, const DateTime& dateTime2) {
	long deltaSeconds = difftime(mktime(dateTime1.tm()), mktime(dateTime2.tm()));

	float t = deltaSeconds / 60.0;

	return deltaSeconds / 60.0;
}


bool TimeDaemon::isOld(){
	time_t now = time(0);
	tm* nowUtc= gmtime(&now);

	DateTime curTime(nowUtc->tm_year, nowUtc->tm_mon, nowUtc->tm_mday, nowUtc->tm_hour, nowUtc->tm_min, nowUtc->tm_sec);

	if(abs(deltaMin(curTime, *m_last120min)) > 120){
		return true;
	}
	return false;
}


void TimeDaemon::count(bool ok, const DateTime& instance) {
	updateReferences(ok, instance);

	m_valuesIn30min++;
	m_valuesIn60min++;
	m_valuesIn120min++;

	if(ok){
		m_okValuesIn30min++;
		m_okValuesIn60min++;
		m_okValuesIn120min++;
	}
}



float TimeDaemon::percent30min() {
	if(m_valuesIn30min > 0 ){
		return static_cast<float> (m_okValuesIn30min) / static_cast<float>(m_valuesIn30min);
	}
	else{
		return -1;
	}
}



float TimeDaemon::percent60min() {
	if(m_valuesIn60min > 0){
		return static_cast<float> (m_okValuesIn60min) / static_cast<float>(m_valuesIn60min);
	}
	else{
		return 0;
	}
}


float TimeDaemon::percent120min() {
	if(m_valuesIn120min > 0){
		return static_cast<float> (m_okValuesIn120min) / static_cast<float>(m_valuesIn120min);
	}
	else {
		return 0;
	}
}






TimeDaemon::TimeDaemon() {
	m_valuesIn120min = m_okValuesIn120min = 0;
	m_valuesIn60min = m_okValuesIn60min = 0;
	m_valuesIn30min = m_okValuesIn30min = 0;
	m_last120min = new DateTime();
	m_last60min = new DateTime();
	m_last30min = new DateTime();
}




TimeDaemon::~TimeDaemon(){
	delete m_last120min;
	delete m_last60min;
	delete m_last30min;
}




void TimeDaemon::updateReferences(bool ok, const DateTime& instance){
	if(abs(deltaMin(instance, *m_last120min)) > 120){
		m_last120min->setYear(instance.year());
		m_last120min->setMonth(instance.month());
		m_last120min->setDay(instance.day());

		m_last120min->setHour(static_cast<int>(instance.hour() / 2) * 2);
		m_last120min->setMin(0);
		m_last120min->setSec(0);

		if(ok){
			m_valuesIn120min = 0;
			m_okValuesIn120min = 0;
		}
		else{
			m_valuesIn120min = -1;
			m_okValuesIn120min = -1;
		}
	}
	if(abs(deltaMin(instance, *m_last60min)) > 60){
		m_last60min->setYear(instance.year());
		m_last60min->setMonth(instance.month());
		m_last60min->setDay(instance.day());

		m_last60min->setHour(instance.hour());
		m_last60min->setMin(0);
		m_last60min->setSec(0);

		if(ok){
			m_valuesIn60min = 0;
			m_okValuesIn60min = 0;
		}
		else{
			m_valuesIn60min = -1;
			m_okValuesIn60min = -1;
		}
	}
	if(abs(deltaMin(instance, *m_last30min)) > 30){
		m_last30min->setYear(instance.year());
		m_last30min->setMonth(instance.month());
		m_last30min->setDay(instance.day());

		m_last30min->setHour(instance.hour());
		m_last30min->setMin(static_cast<int>(instance.min() / 30) * 30);
		m_last30min->setSec(0);

		if(ok){
			m_valuesIn30min = 0;
			m_okValuesIn30min = 0;
		}
		else{
			m_valuesIn30min = -1;
			m_okValuesIn30min = -1;
		}
	}
}
