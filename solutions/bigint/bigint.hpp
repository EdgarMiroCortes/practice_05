#include <iostream>
#include <sstream>

#pragma once

class bigint{
	private:
		std::string str;
	public:
		// Part 1: Inicialization
		bigint();
		bigint(unsigned int num);
		bigint(const bigint& source);
		bigint& operator=(const bigint& source);
		std::string getStr()const;

		//Part 2: Additions
		bigint operator+(const bigint& other) const;
		bigint& operator +=(const bigint& other);
		bigint operator++();
		bigint operator++(int);

		//Part 3: Shifts
		bigint operator<<(unsigned int n) const;
		bigint operator>>(unsigned int n) const;
		bigint& operator<<=(unsigned int n);
		bigint& operator>>=(unsigned int n);

		bigint operator<<(const bigint& other) const;
		bigint operator>>(const bigint& other) const;
		bigint& operator<<=(const bigint& other);
		bigint& operator>>=(const bigint& other);

		// Part 4: Comparisions
		bool operator==(const bigint& other) const;
		bool operator!=(const bigint& other) const;
		bool operator<(const bigint& other) const;
		bool operator>(const bigint& other) const;
		bool operator<=(const bigint& other) const;
		bool operator>=(const bigint& other) const;
	
};

std::ostream& operator <<(std::ostream& output, const bigint& obj);
