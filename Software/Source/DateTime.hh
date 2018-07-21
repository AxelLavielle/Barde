/*
  ==============================================================================

    Date.h
    Created: 4 May 2018 4:26:20pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include <string>
#include <stdio.h>

class DateTime
{
public:
	DateTime();
	DateTime(const DateTime &other);
	~DateTime();
	DateTime	&operator=(const DateTime &other);
	bool setISODate(const std::string &date);
	std::string		getDay() const;
	std::string		getMonth() const;
	std::string		getYear() const;
	std::string		getHours() const;
	std::string		getMinutes() const;
	std::string		getSecondes() const;
	std::string		getIsoDate() const;
	void			setDay(const std::string &day);
	void			setMonth(const std::string &month);
	void			setYear(const std::string &year);
	void			setHours(const std::string &hours);
	void			setMinutes(const std::string &minutes);
	void			setSecondes(const std::string &secondes);

private:
	std::string	_isoDate;
	std::string _day;
	std::string _month;
	std::string _year;
	std::string _hours;
	std::string _minutes;
	std::string _secondes;
};