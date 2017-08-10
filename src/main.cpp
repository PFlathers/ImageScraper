#include <string.h>
#include <tidy.h>
#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include "main.hpp"
#include "typeCheck.hpp"

using namespace std;

//TODO: this doesnt really need to be static.
static const char html_folder[] = "temp/";
static const char html_ext[] = ".html";

int main(int argc, char *argv[])
{
	//TODO: change to <= 2 and make a while loop to take in multiple urls.
	//TODO: add --help option to print out things.
	//TODO: add input for how pages are structured for infinite scrolling
	//pages.
	//TODO: add function for checking flags and inputs.
	if ( argc != 2 )
		cout << "usage: " << argv[0] << " <url>\n";

	char *seedUrl = (argv[1]);
	gatherWebPages(seedUrl);
	return 0;
}

void gatherWebPages(char *seedUrl)
{
	CURL *curl;
	curl = curl_easy_init();
	int result = 0;
	int page_count = 0;
	char *pagename = NULL;

	while(!result){
		pagename = incPage(pagename, &page_count);
		result = getPage(seedUrl, pagename, curl);
	}
	curl_easy_cleanup(curl);
}


char* incPage(char *pagename, int *page_count)
{
	int count_size = numPlaces(*page_count);
	int namelen = strlen(html_folder) + strlen(html_ext) + count_size + 1;
	if(pagename)
		free(pagename);

	pagename = (char*) malloc(namelen * sizeof(char));
	sprintf(pagename, "%s%d%s", html_folder, *page_count, html_ext);
	*page_count += 1;
	return pagename;
}

//TODO: add the url in the error msg.
int getPage(char *url, const char* pagename, CURL *curl)
{
	CURLcode res;
	FILE *page = fopen(pagename, "w+");
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, page);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			cout << "curl_easy_perform() failed: " <<
				curl_easy_strerror(res) <<
				"\nOn url: " << url << "\n";
			return 1;
		}

		curl_easy_reset(curl);
	}

	fclose(page);
	return 0;
}
