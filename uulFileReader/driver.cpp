#include <iostream>
#include "uul.h"
#include <fstream>

int main(void)
{
	readURL readURLObj;
	readURLObj.standardReadFromString("https://playoverwatch.com/en-us/career/pc/ZerG-11720");

	std::ofstream out;
	out.open("testOutput.txt");
	
	return 0;
}
