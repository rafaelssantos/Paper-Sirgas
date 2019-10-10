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

	return deltaSeconds / 60.0;
}


void TimeDaemon::setOld(const DateTime& instance){
	std::time_t now= std::time(0);
	std::tm* nowUtc= std::gmtime(&now);

	DateTime nowDateTime(1900 + nowUtc->tm_year, nowUtc->tm_mon + 1, nowUtc->tm_mday, nowUtc->tm_hour, nowUtc->tm_min, nowUtc->tm_sec);

	if(deltaMin(nowDateTime, instance) > 5){
		m_old = true;
	}
	else{
		m_old = false;
	}
}




void TimeDaemon::count(bool ok, const DateTime& instance) {

	updateReferences(instance);

	m_valuesIn30min++;
	m_valuesIn60min++;
	m_valuesIn120min++;
	m_valuesInAllmin++;
	m_valuesDaily[instance.dateToString()] = m_valuesDaily[instance.dateToString()] + 1;

	if(ok){
		m_okValuesIn30min++;
		m_okValuesIn60min++;
		m_okValuesIn120min++;
		m_okValuesInAllmin++;
		m_okValuesDaily[instance.dateToString()] = m_okValuesDaily[instance.dateToString()] + 1;
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




float TimeDaemon::percentAllmin() {
	if(m_valuesInAllmin > 0){
		return static_cast<float> (m_okValuesInAllmin) / static_cast<float>(m_valuesInAllmin);
	}
	else {
		return 0;
	}
}






bool TimeDaemon::isOld() const {
	return m_old;
}




std::vector<int> TimeDaemon::dailyOkValues() const {
	vector<int> list;

	for(auto d = m_okValuesDaily.begin(); d != m_okValuesDaily.end(); d++){
		list.emplace_back(d->second);
	}

	return list;
}





std::vector<int> TimeDaemon::dailyValues() const {
	vector<int> list;

	for(auto d = m_valuesDaily.begin(); d != m_valuesDaily.end(); d++){
		list.emplace_back(d->second);
	}

	return list;
}





std::vector<float> TimeDaemon::dailyPercent() const {
	vector<int> values = dailyValues();
	vector<int> okValues = dailyOkValues();
	vector<float> percent;

	for(auto i = 0u; i < values.size(); i++) {
		percent.emplace_back(static_cast<float>(okValues[i]) / static_cast<float>(values[i]));
	}

	return percent;
}




std::vector<string> TimeDaemon::dailyLabels() const {
	vector<string> list;

	for(auto d = m_labelDaily.begin(); d != m_labelDaily.end(); d++){
		list.emplace_back(d->first);
	}

	return list;
}






TimeDaemon::TimeDaemon() {
	m_valuesInAllmin = m_okValuesInAllmin = 0;
	m_valuesIn120min = m_okValuesIn120min = 0;
	m_valuesIn60min = m_okValuesIn60min = 0;
	m_valuesIn30min = m_okValuesIn30min = 0;
	m_lastAllmin = new DateTime();
	m_last120min = new DateTime();
	m_last60min = new DateTime();
	m_last30min = new DateTime();
	m_last5min = new DateTime();
}




TimeDaemon::~TimeDaemon(){
	delete m_lastAllmin;
	delete m_last120min;
	delete m_last60min;
	delete m_last30min;
}




void TimeDaemon::updateReferences(const DateTime& instance){
	if(m_valuesInAllmin == 0){
		m_lastAllmin->setYear(instance.year());
		m_lastAllmin->setMonth(instance.month());
		m_lastAllmin->setDay(instance.day());

		m_lastAllmin->setHour(instance.hour());
		m_lastAllmin->setMin(instance.min());
		m_lastAllmin->setSec(instance.sec());

		m_valuesInAllmin = 0;
		m_okValuesInAllmin = 0;
	}

	if(abs(deltaMin(instance, *m_last120min)) > 120){
		m_last120min->setYear(instance.year());
		m_last120min->setMonth(instance.month());
		m_last120min->setDay(instance.day());

		m_last120min->setHour(static_cast<int>(instance.hour() / 2) * 2);
		m_last120min->setMin(0);
		m_last120min->setSec(0);

		m_valuesIn120min = 0;
		m_okValuesIn120min = 0;
	}

	if(abs(deltaMin(instance, *m_last60min)) > 60){
		m_last60min->setYear(instance.year());
		m_last60min->setMonth(instance.month());
		m_last60min->setDay(instance.day());

		m_last60min->setHour(instance.hour());
		m_last60min->setMin(0);
		m_last60min->setSec(0);

		m_valuesIn60min = 0;
		m_okValuesIn60min = 0;
	}

	if(abs(deltaMin(instance, *m_last30min)) > 30){

		m_last30min->setYear(instance.year());
		m_last30min->setMonth(instance.month());
		m_last30min->setDay(instance.day());

		m_last30min->setHour(instance.hour());
		m_last30min->setMin(static_cast<int>(instance.min() / 30) * 30);
		m_last30min->setSec(0);

		m_valuesIn30min = 0;
		m_okValuesIn30min = 0;
	}

	if (m_labelDaily.find(instance.dateToString()) == m_labelDaily.end() ) {
		m_valuesDaily[instance.dateToString()] = 0;
		m_okValuesDaily[instance.dateToString()] = 0;
		m_labelDaily[instance.dateToString()] = new DateTime(instance.year(), instance.month(), instance.day());
	}
}
