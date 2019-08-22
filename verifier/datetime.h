#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include <string>

class DateTime {
public:
	DateTime();

	DateTime(int year, int month, int day);

	DateTime(int year, int month, int day, int hour, int min, int sec);

	DateTime(const DateTime &dateTime);

	virtual ~DateTime();

	std::string toString() const;

	int year() const;

	void setYear(int year);

	int month() const;

	void setMonth(int month);

	int day() const;

	void setDay(int day);

	int hour() const;

	void setHour(int hour);

	int min() const;

	void setMin(int min);

	int sec() const;

	void setSec(int sec);

	std::tm* tm() const;

private:
	struct tm* m_tm;
};

#endif    // DATETIME_H
