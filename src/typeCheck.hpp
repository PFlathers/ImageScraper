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
 * Author:	Patrick J. Flathers
 * Created:	August 7, 2017
 * Last edited:	August 14, 2017
 *
 */

#ifndef __TYPECHECK_H__
#define __TYPECHECK_H__

// Pass an 32 bit int and get back the number of places the int has.
// Does not work for unsigned ints or 64 bit ints yet.
int numPlaces(int n);

//Checks if a directory exists, returns 0 if it does or if it can be created.
//return >0 otherwise.
int dirCheck(char *path);
#endif
