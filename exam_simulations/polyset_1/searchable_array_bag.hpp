#pragma once
#include "searchable_bag.hpp"
#include "array_bag.hpp"

class searchable_array_bag : public searchable_bag, public array_bag {

public:
	searchable_array_bag() : array_bag() {}
	searchable_array_bag(const searchable_array_bag &other) : array_bag(other) {}
	searchable_array_bag &operator=(const searchable_array_bag &other) {
		if (this != &other)
			array_bag::operator=(other);
		return *this;
	}

	~searchable_array_bag() {}

	bool has(int item) const {
		int i = 0;
		while(i < size){
			if (data[i] == item)
				return true;
			i++;
		}
		return false;
	}

};