#include "vect2.hpp"

vect2::vect2(){
	this->x = 0;
	this->y = 0;
}

vect2::vect2(int num1, int num2){
	this->x = num1;
	this->y = num2;
}

vect2::vect2(const vect2& other){
	*this = other;
}

vect2& vect2::operator=(const vect2& other){
	if(this != &other){
		this->x = other.x;
		this->y = other.y;
	}
	return (*this);
}

int vect2::operator[](int index) const{
	if(index == 0)
		return(this->x);
	return(this->y);
}

int& vect2::operator[](int index){
	if(index == 0)
		return(this->x);
	return(this->y);
}

vect2::~vect2(){} // Importante!!!

std::ostream& operator<<(std::ostream& os, const vect2& obj){
	std::cout << "{" << obj[0] << ", " << obj[1] << "}";
	return(os);
}

// PART 2

// Hacerlos negativos
vect2 vect2::operator-() const{
	return vect2(-x, -y);
}


// Tipo 1: -, +, 
vect2 vect2::operator-(const vect2& other) const{
	vect2 temp = *this;
	temp -=  other;
	return(temp);
}

vect2 vect2::operator+(const vect2& other) const{
	vect2 temp = *this;
	temp +=  other;
	return(temp);
}

vect2 vect2::operator*(const vect2& other) const {
	vect2 temp = *this;
	temp *= other;
	return temp;
}

vect2 vect2::operator*(int num) const {
	vect2 temp = *this;
	temp *= num;
	return temp;
}

vect2 vect2::operator++(int) {
	vect2 temp = *this;
	++(*this);
	return temp;
}

vect2 vect2::operator--(int) {
	vect2 temp = *this;
	--(*this);
	return temp;
}

// TIPO 2: +=, -=, *=, *=vect2, ++, --
vect2& vect2::operator+=(const vect2& other){
	x += other.x;
	y += other.y;
	return (*this);
}

vect2& vect2::operator-=(const vect2& other){
	x -= other.x;
	y -= other.y;
	return (*this);
}

vect2& vect2::operator*=(int num) {
	x *= num;
	y *= num;
	return (*this);
}

vect2& vect2::operator*=(const vect2& other) {
	x *= other.x;
	y *= other.y;
	return (*this);
}

vect2& vect2::operator++() {
	x += 1;
	y += 1;
	return *this;
}

vect2& vect2::operator--() {
	x -= 1;
	y -= 1;
	return *this;
}

// TIPO 3: ==, !==
bool vect2::operator==(const vect2& other) const {
	return (x == other.x) && (y == other.y);
}

bool vect2::operator!=(const vect2& other) const {
	return !(*this == other);
}

vect2 operator*(int num, const vect2& obj)
{
	vect2 temp(obj);
	temp *= num;
	return(temp);
}