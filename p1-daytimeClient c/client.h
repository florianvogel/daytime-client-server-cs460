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

#define NIST_IP "129.6.15.28" //NIST daytime server IP
#define NIST_PORT "13" //NIST daytime server PORT
#define OTM '*' //NIST daytime server OTM

char* read_line(int socket); //Read from the socket
int socket_connect(char* ip, char* port); //Connect to socket
void socket_disconnect(int socket); //Disconnect the socket

#endif
