#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <jansson.h>
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
//#include "server_communication.h"
#include "json_processing.h"


#define ID_ERROR -1
#define RETURN_ERROR -1
using namespace std;

//our files
//#include json_processing.h
//defines
#define CONNECT_ERROR -1

//int i=0;
/*
class connectException: public exception
{
  virtual const char* message() const throw()
  {
    return "Connection error";
  }
} connectException;

class disconnectException: public exception
{
  virtual const char* message() const throw()
  {
    return "Error on disconnect";
  }
} disconnectException;

class sendException: public exception
{
  virtual const char* message() const throw()
  {
    return "Error on sending";
  }
} sendException;

class getException: public exception
{
  virtual const char* message() const throw()
  {
    return "Error on receiving from server";
  }
} getException;

class jsonException: public exception
{
  virtual const char* message() const throw()
  {
    return "Error decoding json string";
  }
} 202;
*/


map<string,double> server_get_data(int id){
    return json_get_data(id);
    //throws getException
}


void server_send_data(map<string,double> data){
    json_send_data(data);
    //throws sendException
}

 void server_send_command(string command, int id){
    json_send_command(command,id);
    //throws sendException
 }

 vector<string> server_get_commands(int id){
    return json_get_commands(id);
    //throws getException
    // put things in vector or return array
}

void server_set_myID(int id){
  json_set_myID(id);
}

int server_get_myID(){
  int temp_id=json_get_myID();
  return temp_id;
}

/*

int server_connect(){
    int id=CONNECT_ERROR; //my ID
    id = json_connect();
    if(id==CONNECT_ERROR){
        //action on connection fail
        throw connectException;
    }
    // connection is successful
    return id;

 }

void server_disconnect(){
    return json_disconnect();
    // throws disconnectException
}


 vector<string> server_get_client_list(){
    return json_get_client_list();
    //throws getException

 }



 int server_send_status(map status){
    return json_send_status(status);
    //throws sendException
 }

 map server_get_status(int id){
    return json_get_status(id);
    //throws getException
 }
 */

