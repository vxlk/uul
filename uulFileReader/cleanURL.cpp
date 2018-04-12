#include "cleanURL.h"
#include <iostream>

std::string cleanURL::errorReader(errorType type) {
	if (type == emptyFile) std::cout << "\nempty file\n";
	if (type == notHTML) std::cout << "\nnot HTML\n";
	return ""; //temp
}

std::string cleanURL::stripHeaderInfo(const std::string& buffer) {
	std::string returnBuffer;
	std::string startingHeader = "<!";
	int loopIndex = 0;
	int start = buffer.find(startingHeader);
	if (start == buffer.npos) { errorReader(emptyFile); return ""; }

	for (;  returnBuffer.find('>') == returnBuffer.npos; ++loopIndex)
		returnBuffer += buffer[loopIndex];

	//remove spaces/caps, make sure it reads <!doctypehtml> -> document is formatted correctly
	//now read until <title>

	returnBuffer.erase(std::remove_if(returnBuffer.begin(), returnBuffer.end(), isspace), returnBuffer.end());
	std::transform(returnBuffer.begin(), returnBuffer.end(), returnBuffer.begin(), ::tolower);

	if (returnBuffer != "<!doctypehtml>") { errorReader(notHTML); return returnBuffer; }

	int rememberIndex = loopIndex;

	//need to check there is a title
	//inc index past the header info that is irrelevant to us
	for (; returnBuffer.find("<title>") == returnBuffer.npos; ++loopIndex) {}

	///Contains no title
	if (loopIndex == buffer.size())
		loopIndex = rememberIndex;

	return returnBuffer;
}

