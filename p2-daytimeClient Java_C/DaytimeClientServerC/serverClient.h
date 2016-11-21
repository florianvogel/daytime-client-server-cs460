/**
 * Author: Jayden Urch
 * Student No: 5388406
 * Email: jsu22@nau.edu
 *
 * Author: Florian Vogel
 * Student No: 5373720
 * Email: fv69@nau.edu
 *
 * Date: 11/03/2016
 */

#ifndef URCH_VOGEL_DAYTIME_CLIENT
#define URCH_VOGEL_DAYTIME_CLIENT

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>

#define NIST_IP "129.6.15.28" //NIST daytime server IP
#define NIST_PORT 13 //NIST daytime server PORT
#define OTM '*' //NIST daytime server OTM
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 23657

#define FALSE 0
#define TRUE !FALSE

#define NUM_CONNECTIONS 1       // number of pending connections in the connection queue
#define MAX_CONCURRENT 128		// maximum number of concurrent threads

char* read_line(int socket); //Read from the socket
int socket_connect(char* ip, int port, int doBind); //Connect to socket
void socket_disconnect(int socket); //Disconnect the socket
void* handle_client(void *client_socket);
char* parse_time(char* time, char identifier); //Y = year; M = month; D = day; h = hour; m = minute; s = second

#endif
