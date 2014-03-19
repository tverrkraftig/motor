#ifndef SERVER_COMMUNICATION

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
/*
int connect();

int disconnect();

map <int,string> server_get_client_list();

void server_send_status(map<string,string> status);

map<string,string> server_get_status(int id);

*/


// --------------- send data ----------------
//sending a map of data with a string key, and a double value
// use this to send all your sensor data, with the map syntax [sensor_name,sensor_value]
void server_send_data(map<string,double> data);

// ----------------- get data -----------------
// Request sensor data from a specific device id
map <string,double> server_get_data(int id);

// ----------------- send command --------------
// Send a command to a specific device id. Commands are sent as strings
void server_send_command(string command,int id);


//------------------ get command -----------------
// get a vector of all the commands the server has for your device
vector<string> server_get_commands(int id);


// ----------------- Set id---------------
// Set your id manually. 
void server_set_myID(int id);


// ------------------- get id -----------------------
// get your id from the server framework
int server_get_myID();



class connectException;
class disconnectException;
class sendException;
class getException;
class jsonException;

#endif
