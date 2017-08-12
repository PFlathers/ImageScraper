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
 *
 *
 * This File acts as the driver for Image Scraper. While it does not
 * currently contain much, it allows to easy follow the flow of the
 * program incase other features are later added.
 *
 */

#include <string.h>
#include <iostream>
#include "scrapehtml.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	//TODO: change to <= 2 and make a while loop to take in multiple urls.
	//TODO: allow for urls to be read in from a plain text file.
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

