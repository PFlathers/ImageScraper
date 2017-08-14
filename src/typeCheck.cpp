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
 * This file contains functions for checking properties of primitives.
 *
 */

#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>


// Returns how many places an 32 bit int has.
int numPlaces(int n)
{
	if (n < 0) n = (n == INT_MIN) ? INT_MAX: -n;
	if (n < 10) return 1;
	if (n < 100) return 2;
	if (n < 1000) return 3;
	if (n < 10000) return 4;
	if (n < 100000) return 5;
	if (n < 1000000) return 6;
	if (n < 10000000) return 7;
	if (n < 100000000) return 8;
	if (n < 1000000000) return 9;
	// Since  2^31 - 1 is the cap, this is going to asympotically faster
	// Than any use of for loops, recursion, or logrithms. I know its not
	// pretty, but its fast.

	return 10;
}

// checks if a directory exists, if not then create, if it cant return error.
int dirCheck(char *path)
{
	struct stat s;
	int err = stat(path, &s);
	//Checks for errors
	if (err == -1){
		//path doesnt exists
		if (ENOENT == errno){
			std::cout << "creating: " << path << "\n";
			mkdir(path, 0777);
			return 0;
		//something else
		} else {
			std::cout << "error\n";
			return 1;
		}
	//path does exist
	} else {
		if (S_ISDIR(s.st_mode)){
			std::cout << path << " exists\n";
			return 0;
		}
		//path is not a dir
		 else{
			std::cout << path << " exists but is not a directory";
			return 2;
		 }
	}
}
