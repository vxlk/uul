#include <iostream>
#include "uul.h"
#include <fstream>

int main(void)
{
	char* input = "https://cryptowat.ch/";
	readURL readURLObj;
	readURLObj.standardReadFromString(input);

	std::ofstream out;
	out.open("testOutput.txt");
	
	return 0;
}
