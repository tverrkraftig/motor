
#ifndef JSON_PROCESSING
/* code */


//defines
#define BUFFER_SIZE  (256 * 1024)  /* 256 KB */
#define URL_FORMAT   "https://wodinaz.com/%s"
#define URL_SIZE     256

#define PATH_CONNECT "connect"
#define PATH_DATA "data/"
#define PATH_COMMAND "command/"

//includes
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <jansson.h>
#include "server_communication.h"
#include <string>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

//functions
static char* json_request(const char *url);
static size_t write_response(void *ptr, size_t size, size_t nmemb, void *stream);
void json_post(char* url, char* json_string);

int json_connect();

void json_send_data(map<string,double> mymap);
map<string,double> json_get_data(int id);
void json_send_command(string cmd,int id);
vector<string> json_get_commands(int id);

void json_set_myID(int id);
int json_get_myID();

#endif
