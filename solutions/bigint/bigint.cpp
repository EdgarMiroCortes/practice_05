#include "bigint.hpp"

// Part 1: Inicialization
bigint::bigint(){
	this->str = "0";
}

bigint::bigint(unsigned int num){
	std::stringstream ss;
	ss << num;
	this->str = ss.str();
}

bigint::bigint(const bigint& source){
	(*this) = source;
}

bigint& bigint::operator=(const bigint& source){
	if(this == &source)
		return(*this);
	this->str = source.getStr();
	return(*this);
}

std::string bigint::getStr() const{
	return(this->str);
}

//Part 2: Additions
bigint bigint::operator+(const bigint& other) const{
	std::string a = this->getStr();
	std::string b = other.getStr();
	std::string result = "";
	int carry = 0;
	int i = a.size() - 1;
	int j = b.size() - 1;

	while(i >=0 || j >= 0 || carry){
		int d1 = (i>=0) ? a[i--] - '0' : 0;
		int d2 = (j>=0) ? b[j--] - '0' : 0;
		int sum = d1 + d2 + carry;
		carry = sum/10;
		result.insert(result.begin(), (sum%10 + '0'));
	}
	bigint res;
	res.str = result;
	return res;
}

bigint& bigint::operator+=(const bigint& other){
	return *this = *this + other;
}

bigint bigint::operator++(){
	return *this += bigint(1);
}

bigint bigint::operator++(int){
	bigint tmp = *this;
	++(*this);
	return tmp;
}

//Part 3: Shifts
static unsigned int strUnit(const std::string& str){
        return static_cast<unsigned int>(std::stoul(str));
}

bigint bigint::operator<<(unsigned int n) const{
	bigint temp (*this);
	temp.str.append(n, '0');
	return temp;
}
bigint bigint::operator>>(unsigned int n) const{
	bigint temp(*this);
	if(n >= temp.str.size())
		temp.str = "0";
	else
		temp.str.erase(temp.str.size() -n);
	return temp;
}

bigint& bigint::operator<<=(unsigned int n){
	return *this = *this << n; // igualamos a this el resultado del shift
}
bigint& bigint::operator>>=(unsigned int n){
	return *this = *this >> n;
}

bigint bigint::operator<<(const bigint& other) const{
	return *this << strUnit(other.getStr());
}
bigint bigint::operator>>(const bigint& other) const{
	return *this >> strUnit(other.getStr());
}
bigint& bigint::operator<<=(const bigint& other){
	return *this = *this << strUnit(other.getStr());
}

bigint& bigint::operator>>=(const bigint& other){
	return *this = *this >> strUnit(other.getStr());
}

// Part 4: Comparisions
bool bigint::operator==(const bigint& other) const{
	return this->getStr() == other.getStr();
}

bool bigint::operator!=(const bigint& other) const{
	return !(*this == other); // contrario de operator==
}

bool bigint::operator<(const bigint& other) const{
	const std::string& a = this-> getStr();
	const std::string& b = other.getStr();
	if(a.size() != b.size())
		return a.size() < b.size();
	return a<b;
}

bool bigint::operator>(const bigint& other) const{
	return other < *this; // contrario de operador<
}

bool bigint::operator<=(const bigint& other) const{
	return !(other < *this);
}

bool bigint::operator>=(const bigint& other) const{
	return !(*this < other);
}

// Important!!! Print
std::ostream& operator<<(std::ostream& output, const bigint& obj){
	output<<obj.getStr();
	return (output);

}
