#ifndef HTTP_FUNCTIONS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// make HTTP request to url
char* http_request(char *url);

//post to server
void http_post(char* url, char* json_string);
#endif
