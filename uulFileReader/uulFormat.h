#pragma once
#include "readURL.h"

struct node {
	node* next;
	node* prev;
	node* head;
	node* tail;
};

class uulFormatTextBox {

private: 
	std::string text;
	std::string labelName;
	int size;

};

class uulUncastedDataField {

 private:
	 std::string fieldName;
	 double uncastedField;

	 short castToShort(double uncastedField);
	 int castToInt(double uncastedField);
	 long castToLong(double uncastedField);
	 float castToFloat(double uncastedField);
 
 public:
	 uulUncastedDataField castToAppropriateField();
};

template<typename T>
class uulCastedDataField {

 private:
	 T field;
	 std::string fieldName;
};

//parent class that takes in a subtype eg uultextbox, uuldatafield
template <class T>
class uulFormatContainer {

private:
	std::string url;
	std::vector <T> data;
	std::vector<T> urlContents;

public:

};