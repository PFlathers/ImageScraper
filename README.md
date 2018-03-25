# ImageScraper

### Usage:
This program is designed to download all of the images off of a webpage.
Includes feature that will continue to download images of pages with an
infite scroll, even if the images are not yet loaded onto the page.

If you are using a text file, then have the urls sperated by a newline.

### Build:
Run `make` in the directory to build.

### Run:
run `bin/image_scraper.out [url]` to start scraping.

run `bin/image_scraper.out -f [urls.txt]`scrape from multiple sites.

### Dependencies:
* `libcurl`, <curl/curl.h>
