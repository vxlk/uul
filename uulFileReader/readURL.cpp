/*
Author: Tyler Small 2/28/18

This class scrapes hero stats from the playoverwatch website and puts them into player profiles.

Because of the potential negatives scraping poses on a website, this code is not licensed under M.I.T.
And therefore not open to the general public.
Database is kept at <INSERT URL>

* Copyright (C) Tyler Small - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

///TODO FIX TIME PLAYED READIN
///A FLOAT IS USED IF THE TIME IS IN SECONDS. POTENTIAL FOR ERROR

#include "readURL.h"
#include <iostream>

#define CURL_LIB_LOCATION "curl/libcurl-vc14-x86-release-static-ipv6-sspi-winssl/lib/libcurl_a"
#pragma comment(lib, CURL_LIB_LOCATION)

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}


float convertFromScientificNotation(std::string statNum) {
	std::string tempBuffer;
	int index = 0;
	int coefficient = 0;
	float toBeReturned = 0;

	while (statNum[index] != 'e') {
		tempBuffer += statNum[index];
		++index;
	}

	while (statNum[index] != '\0') {
		if (statNum[index] == 'e' || statNum[index] == ' ')
			continue;
		if (statNum[index] == '+') {
			++index; //read past the exponent operator and get the power n
			coefficient = statNum[index];
			++index; //go to the next number that is not the power n

					 //deal with form 0n -> n
			if (coefficient == 0) {
				++index;
				coefficient = statNum[index];
				++index;
				continue;
			}
		}
		tempBuffer += statNum[index];
		++index;

		//convert to float
		toBeReturned = stof(tempBuffer);
		//convert the number to scientific notation
		toBeReturned *= pow(10, coefficient);

		return toBeReturned;
	}

	//do the conversion
}


/*
Scrape the data, and read it into a string buffer
*/
void readURL::standardReadFromString(char* URL) {

	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	std::string URLtoString(URL);
	std::string urlRawFileName = "uulRawFile-" + URLtoString;

	//format file name
	std::replace(urlRawFileName.begin(), urlRawFileName.end(), '.', '-');
	std::replace(urlRawFileName.begin(), urlRawFileName.end(), '/', '-');
	urlRawFileName.erase(std::remove(urlRawFileName.begin(), urlRawFileName.end(), ':'), urlRawFileName.end());
	urlRawFileName += ".txt";

	curl = curl_easy_init();
	if (curl) {
	
		curl_easy_setopt(curl, CURLOPT_URL, URL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);


		///LIST OF USEFUL COMMANDS
		/*

		competitive-rank    - comp rank image

		div id=\"competitive\"    -> get to comp

		*/

		///TESTING
		std::ofstream out;
		out.open(urlRawFileName.c_str());

		//convert char buffer to string
		std::string bufferString(readBuffer);

		//call subroutines

		///TESTING
		out << URL << std::endl;
		out << bufferString << std::endl;


	}
}
