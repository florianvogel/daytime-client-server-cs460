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

#include "client.h"

//Reads data from the given socket, searches for the OTM and
//replaces the characted before it with '\0'
//Then returns the data
char* read_line (int socket){

    char* reply = malloc(sizeof(char)*1000);

    //receiving from socket
    if(recv(socket, reply ,1000 ,0) == -1){
        fprintf(stderr, "recv failed\n");
        exit(1);
    }
     char* OTM_position = strrchr(reply,OTM); //searching for the last occurrence of the OTM character

     if(OTM_position == NULL){
         fprintf(stderr, "Error: On Time Marker not found\n");
         exit(1);
     }

     int i;
     int length = strlen(reply);
     //Loops over the string, searching for the OTM character position
     //Then replaces the character before it with '\0'
     for(i=0; i<length; i++){
         if(&reply[i] == OTM_position){
             reply[i-1] = '\0';
             break;
         }
     }

     return reply;
}

//Creates and connects a socket to the given IP and PORT
int socket_connect(char* ip, char* port){

	int server_socket;                 // descriptor of server socket
    struct sockaddr_in server_address; // for naming the server's listening socket
    
    //error checking
    if(ip == NULL || port == NULL){
        fprintf(stderr, "Error: given IP or PORT is null\n");
        exit(1);
    }
	
    //creating socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(1);
    }

    
    // name the socket (making sure the correct network byte ordering is observed)
    server_address.sin_family      = AF_INET; // accept IP addresses
    server_address.sin_addr.s_addr = inet_addr(ip); // connect to server on given interface
    server_address.sin_port        = htons((int) strtol(port,(char **)NULL,10)); // port to connect to

     // binding unnamed socket to a particular port
    if (connect(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding socket");
        exit(1);
    }

    return server_socket;
}

//Closes the given socket
void socket_disconnect(int socket){
    close(socket);
}

//Main function connects to the server, gets the reply,
//inserts '\0' into the reply at the position before the
//OTM, prints the reply then disconnects.
int main(int argc, char** argv){

    int socket = socket_connect(NIST_IP, NIST_PORT); //connecting to socker
    char* reply = read_line(socket); //reading the line

    //Error checking and line printing
    if(reply != NULL){
        printf("%s\n", reply);
    }
    else{
        fprintf(stderr, "Error: No reply found\n");
        exit(1);
    }

    socket_disconnect(socket); //disconnecting the socket
    free(reply); //freeing memory

    return 0;
}