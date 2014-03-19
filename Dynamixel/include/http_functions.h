#ifndef HTTP_FUNCTIONS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

// ---------- get from server -----------
// make HTTP request to url, receive json string
char* http_request(char *url);


//-----------  post to server --------------------
//Making a http call passing the json string the specified url

void http_post(char* url, char* json_string);

#endif