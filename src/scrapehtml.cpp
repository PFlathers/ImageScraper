/* This file is part of ImageScraper
 *
 * ImageScraper is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation either version 3 of the License, or
 * (at your option) any later version.
 *
 * ImageScraper is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warrenty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ImageScraper. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Author:	Patrick J. Flathers
 * Created:	August 7, 2017
 * Last edited:	August 14, 2017
 *
 *
 * This file exists for the purpose of downloading the html for
 * webpages and finding the <img> tags and then downloading the images
 * associated with that page. It also works to grab images from pages
 * with infinite scolling.
 *
 *
 * TODO: Allow the page append string to be user input, incase that
 * the site the user is trying to uses a different format.
 *
 * TODO: Allow user to change image save folder destination.
 *
 * TODO: Dont save the html as a file, that limits speed by reading
 * and writing to disk.
 *
 * TODO: Switch from easy_curl to multi_curl so that images of the
 * same page may be downloaded at the same time.
 *
 * TODO: Create a function for curl to save the images asynchronously
 * so that disk speed is not a limiting factor.
 *
 */


#include <curl/curl.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <regex>
#include "scrapehtml.hpp"
#include "typeCheck.hpp"

using namespace std;
static const char html_folder[] = "temp/";
static const char html_ext[] = ".html";
static const char img_folder[] = "img/";
static const char img_ext[] = ".jpg";
static const char page_app[] = "/page/";

/* from the seed url, scrape the html for links to images.
 * if the page has infinite scroll, continue on until the page
 * reaches the bottom.
 */
void gatherWebPages(char *seed_url)
{
	CURL *curl;
	curl = curl_easy_init();
	char *page_name = NULL;
	char *url = seed_url;
	int page_result = 0;
	int page_count = 1;
	int img_result = 0;

	std::cout << "Starting with url: " << seed_url << "\n";

	while(!page_result){
		//std::cout << url << "\n";
		page_name = incPage(page_name, &page_count);
		page_result = getPage(url, page_name, curl);
		img_result = getImages(curl, page_name);
		if(img_result == 0){
			std::cout << "Page: " << page_name << "\n" <<
				"Has no images, assuming its a page without" << 
				" images or a prototype, terminating\n";
			break;
		}
		url = nextSeedUrl(seed_url, url, page_count);
	}

	std::cout << "Finished!\n";
	if(page_name)
		free(page_name);
	if(strcmp(url, seed_url))
		free(url);
	curl_easy_cleanup(curl);
}

// Appends the page and its number to the seed url.
char* nextSeedUrl(char* seed_url, char *url, int page_count)
{
	int count_size = numPlaces(page_count);
	int name_len = strlen(url) + strlen(page_app) + count_size + 1;
	if (url)
		if (strcmp(seed_url, url) != 0)
			free(url);
	url = (char*) malloc(name_len * sizeof(char));
	sprintf(url, "%s%s%d", seed_url, page_app, page_count);
	return url;
}

// Creates the file name for html to be saved
char* incPage(char *page_name, int *page_count)
{
	int count_size = numPlaces(*page_count);
	int name_len = strlen(html_folder) + strlen(html_ext) + count_size + 1;
	if(page_name)
		free(page_name);

	page_name = (char*) malloc(name_len * sizeof(char));
	sprintf(page_name, "%s%d%s", html_folder, *page_count, html_ext);
	*page_count += 1;
	return page_name;
}

// Grabs the html and saves it.
int getPage(char *url, const char* page_name, CURL *curl)
{
	CURLcode res;
	FILE *page = fopen(page_name, "w+");

	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, page);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			std::cout << "curl_easy_perform() failed: " <<
				curl_easy_strerror(res) <<
				"\nOn url: " << url << "\n";
			return 1;
		}
		std::cout << "Sucessfully saved: " << page_name << "\n";
		curl_easy_reset(curl);
	}
	fclose(page);
	return 0;
}

// Grabs all images on a page and saves them.
int getImages(CURL *curl, char* page_name)
{
	std::ifstream infile(page_name);
	std::string line;
	std::regex rgx("<img[^>]+src=\"([^\"]+.jpg)\"");
	std::smatch match;
	CURLcode res;
	char *image_url = NULL;
	char *image_name = NULL;
	FILE *image;
	int count_size = 0;
	int name_len = 0;
	int image_page_count = 0;
	static int img_count = 0;

	// Loads html and checks each line for images.
	while(getline(infile, line)){
		if(std::regex_search(line, match, rgx)){
			count_size = numPlaces(img_count);
			name_len = strlen(img_folder) + count_size + strlen(img_ext);
			if (image_name)
				free(image_name);
			image_name = (char*) malloc(name_len * sizeof(char));
			sprintf(image_name, "%s%d%s",img_folder, img_count, img_ext);
			img_count ++;
			std::cout << img_count << "\n";

			image = fopen(image_name, "w+");

			string asdf = (string) match[1];

			image_url =  (char*) malloc(strlen(asdf.c_str()) +1);
			strcpy(image_url, asdf.c_str());

			// Downloads and saves the images.
			curl_easy_setopt(curl, CURLOPT_URL, image_url);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, image);
			res = curl_easy_perform(curl);
			if(res != CURLE_OK){
				std::cout << "curl_easy_perform() failed: " <<
					curl_easy_strerror(res) <<
					"\nOn url: " << image_url << "\n";
			}
			else{
				image_page_count += 1;
			}
			fclose(image);
			free(image_url);
			curl_easy_reset(curl);
		}
	}
	return image_page_count;
}
