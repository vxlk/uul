#include <iostream>
#include "uul.h"
#include <fstream>

int main(void)
{
	char* input = "https://www.google.com/search?source=hp&ei=6ILLWvaiHZKO5wK_pIy4BA&q=something&oq=something&gs_l=psy-ab.3..0l2j0i131k1l2j0j0i3k1j0l4.646.1660.0.1788.10.6.0.3.3.0.112.542.4j2.6.0....0...1c.1.64.psy-ab..1.9.584.0..46j0i46k1.0.TVPct1KKKYU";
	readURL readURLObj;
	readURLObj.standardReadFromString(input);

	std::ofstream out;
	out.open("testOutput.txt");
	

	int x;
	std::cin >> x;

	return 0;
}
