
//defines
#define BUFFER_SIZE  (256 * 1024)  /* 256 KB */
#define URL_FORMAT   "https://wodinaz.com/%s"
#define URL_SIZE     256

//includes
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

//functions
void json_post(char* url, char* json_string);
void json_test_function();

void debug_print_map(map<string,double> mymap);
void debug_print_vector(vector<string> myvector);


void json_send_data(map<string,double> mymap);
map<string,double> json_get_data(int id);
void json_send_command(string cmd,int id);
vector<string> json_get_commands(int id);

//void json_set_myID(int id);
//int json_get_myID();