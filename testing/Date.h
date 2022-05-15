#pragma once
#include <iostream>

using namespace std;

class Date {
private:
	unsigned int day;
	unsigned int month;
	unsigned int year;
public:
	Date() : day(0), month(0), year(0) {}
	Date(unsigned day, unsigned month, unsigned year) : day(day), month(month), year(year) {}
	Date(const Date& other);
	Date& operator=(const Date& rhs);

	void setDay(unsigned day) {
		this->day = day;
	}

	void setMonth(unsigned month) {
		this->month = month;
	}

	void setYear(unsigned year) {
		this->year = year;
	}

	unsigned getDay() const {
		return day;
	}

	unsigned getMonth() const {
		return month;
	}

	unsigned getYear() const {
		return year;
	}

	void printDate() const {
		cout << day << "/" << month << "/" << year << endl;
	}

	bool sameDate(const Date& other) const {
		if ((day == other.day) && (month == other.month) && (year == other.year))
			return true;
		else {
			return false;
		}
	}

	friend ostream& operator<<(ostream& os, const Date& obj);
	friend istream& operator>>(istream& is, Date& obj);
};

Date::Date(const Date& other) {
	day = other.day;
	month = other.month;
	year = other.year;
}

Date& Date::operator=(const Date& rhs) {
	if (this != &rhs) {
		day = rhs.day;
		month = rhs.month;
		year = rhs.year;
	}
	return *this;
}

ostream& operator<<(ostream& os, const Date& obj) { // i need to fix this to be write for file
	os << obj.day << "/" << obj.month << "/" << obj.year;

	return os;
}

istream& operator>>(istream& is, Date& obj) {
	is >> obj.day >> obj.month >> obj.year;

	return is;
}
