/*
Author: Tyler Small 2/28/18

* Copyright (C) Tyler Small - All Rights Reserved
* Github.com/vxlk
* 
*/

///TODO FIX TIME PLAYED READIN
///A FLOAT IS USED IF THE TIME IS IN SECONDS. POTENTIAL FOR ERROR

#include "readURL.h"
#include "cleanURL.h"
#include <experimental/filesystem>
#include <cmath>
#include <iostream>

#ifdef _WIN32
	#define MAX_FILE_SIZE 260
#endif

#ifdef _WIN64
	#define MAX_FILE_SIZE 260
#endif

#ifdef __APPLE__
	#define MAX_FILE_SIZE 260
#endif

#ifdef __MACH__
	#define MAX_FILE_SIZE 260
#endif

#ifdef __linux__
	#define MAX_FILE_SIZE 260
#endif

#define CURL_LIB_LOCATION "curl/libcurl-vc14-x86-release-static-ipv6-sspi-winssl/lib/libcurl_a"
#pragma comment(lib, CURL_LIB_LOCATION)

namespace fs = std::experimental::filesystem;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
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
	urlRawFileName.erase(std::remove(urlRawFileName.begin(), urlRawFileName.end(), '?'), urlRawFileName.end());
	urlRawFileName.erase(std::remove(urlRawFileName.begin(), urlRawFileName.end(), '&'), urlRawFileName.end());
	urlRawFileName.erase(std::remove(urlRawFileName.begin(), urlRawFileName.end(), '='), urlRawFileName.end());

	fs::path p = fs::path("..") / ".." / "uulFileReader";
	std::string cpath = fs::canonical(p).string();
	std::cout << cpath << "\n";

	//check size requirements
	if (urlRawFileName.size() + cpath.size() >= MAX_FILE_SIZE) {
		int destinationSize = (urlRawFileName.size() + cpath.size() - MAX_FILE_SIZE);
		urlRawFileName = urlRawFileName.substr(0, destinationSize);
	}
	urlRawFileName += ".txt";

	curl = curl_easy_init();
	if (curl) {
	
		curl_easy_setopt(curl, CURLOPT_URL, URL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		///TESTING
		std::ofstream out;
		out.open(urlRawFileName.c_str());
		std::cout << urlRawFileName.c_str();
		
		//convert char buffer to string
		std::string bufferString(readBuffer);

		//call subroutines
		cleanURL clean;
		std::string newString = clean.stripHeaderInfo(bufferString);




		///TESTING
		out << URL << std::endl;
		out << bufferString << std::endl;


	}
}
