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
 * Last edited:	August 12, 2017
 */


#ifndef __SCRAPE_HTML_H__
#define __SCRAPE_HTML_H__
#include <curl/curl.h>

// Pass in a char* to the page that you want to scrape for images.
void gatherWebPages(char *seed_url);

// Pass a url, a save file name, and an open CURL. Downloads the html
// for the url.
int getPage(char *url, const char *page_name, CURL *curl);

// Pass a reference to a open CURL and a html file name to download
// all images references in <img> in the html.
int getImages(CURL *curl, char *page_name);

// Pass the char* to a string of the previous file name, which will
// be freed. Returns the next file name. The int numbers the files.
char* incPage(char *page_name, int *page_count);

// Pass the seed_url, the previous url, and the page number for the
// infinite scrolling. Returns the next url_page to scrape.
char* nextSeedUrl(char *seed_url, char *url, int page_count);

#endif
