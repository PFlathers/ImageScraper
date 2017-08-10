#ifndef __MAIN_H__
#define __MAIN_H__
#include <curl/curl.h>

void gatherWebPages(char*);

int getPage(char*, const char*, CURL *);

char* incPage(char*, int*);

#endif
