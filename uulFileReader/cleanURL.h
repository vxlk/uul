#pragma once
#include "readURL.h"

enum errorType {
	emptyFile,
	invalidFormat,
	notHTML
};

class cleanURL {

	std::string errorReader(errorType type);
 
 public:
	std::string stripHeaderInfo(const std::string& buffer);
};
