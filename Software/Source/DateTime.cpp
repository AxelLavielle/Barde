/*
  ==============================================================================

    Date.cpp
    Created: 4 May 2018 4:26:10pm
    Author:  Anthony

  ==============================================================================
*/

#include "DateTime.hh"

DateTime::DateTime()
{
}

DateTime::DateTime(const DateTime & other)
{
	*this = other;
}

DateTime::~DateTime()
{
}

DateTime & DateTime::operator=(const DateTime & other)
{
	_isoDate = other.getIsoDate();
	_day = other.getDay();
	_month = other.getMonth();
	_year = other.getYear();
	_hours = other.getHours();
	_minutes = other.getMinutes();
	_secondes = other.getSecondes();
	return *this;
}

bool DateTime::setISODate(const std::string & date)
{
	int			day;
	int			month;
	int			year;
	int			hours;
	int			minutes;
	float		secondes;

	_isoDate = date;
	sscanf(date.c_str(), "%d-%d-%dT%d:%d:%fZ", &year, &month, &day, &hours, &minutes, &secondes);
	_day = std::to_string(day);
	_month = std::to_string(month);
	_year = std::to_string(year);
	_hours = std::to_string(hours);
	_minutes = std::to_string(minutes);
	_secondes = std::to_string(secondes);
	return false;
}

std::string DateTime::getDay() const
{
	return _day;
}

std::string DateTime::getMonth() const
{
	return _month;
}

std::string DateTime::getYear() const
{
	return _year;
}

std::string DateTime::getHours() const
{
	return _hours;
}

std::string DateTime::getMinutes() const
{
	return _minutes;
}

std::string DateTime::getSecondes() const
{
	return _secondes;
}

std::string DateTime::getIsoDate() const
{
	return _isoDate;
}

void DateTime::setDay(const std::string & day)
{
	_day = day;
}

void DateTime::setMonth(const std::string & month)
{
	_month = month;
}

void DateTime::setYear(const std::string & year)
{
	_year = year;
}

void DateTime::setHours(const std::string & hours)
{
	_hours = hours;
}

void DateTime::setMinutes(const std::string & minutes)
{
	_minutes = minutes;
}

void DateTime::setSecondes(const std::string & secondes)
{
	_secondes = secondes;
}
