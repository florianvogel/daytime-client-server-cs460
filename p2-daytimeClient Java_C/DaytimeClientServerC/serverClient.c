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

#include "serverClient.h"

pthread_mutex_t lock;
pthread_t thread;

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
int socket_connect(char* ip, int port, int doBind){

	int server_socket;                 // descriptor of server socket
    struct sockaddr_in server_address; // for naming the server's listening socket
    
    //error checking
    if(ip == NULL){
        fprintf(stderr, "Error: given IP is null\n");
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
    server_address.sin_port        = htons(port); // port to connect to

	if(doBind == TRUE){
		 // binding unnamed socket to a particular port
		if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
		    perror("Error binding socket");
		    exit(1);
		}
	}
	else{
		 // connecting unnamed socket to a particular port
		if (connect(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
			perror("Error binding socket");
			exit(1);
		}
	}
    return server_socket;
}

//Closes the given socket
void socket_disconnect(int socket){
    if (close(socket) == -1) {
        perror("Error closing socket");
        exit(EXIT_FAILURE); 
    }
}

//Y = year; M = month; D = day; h = hour; m = minute; s = second
char* parse_time(char* time, char identifier){
	int loop = 0;
	char* output;
	switch(identifier){
		case 'Y':
			loop = 2;
			break;
		case 'M':
			loop = 3;
			break;
		case 'D':
			loop = 4;
			break;
		case 'h':
			loop = 5;
			break;
		case 'm':
			loop = 6;
			break;
		case 's':
			loop = 7;
			break;
		default:
			fprintf(stderr, "Error: Identifier not recognised\n");
			exit(1);
	}
	
	int i;
	for(i=0; i<loop; i++){
		output = strsep(&time, " -:");
	}
	return output;
}

void* handle_client(void *client_socket){
	//Create a local variable for the client socket to save the value
	int local_client_socket = *(int *)client_socket;
	pthread_mutex_unlock(&lock);
    char input;
    
    // read char from client
    switch (read(local_client_socket, &input, sizeof(char))) {
        case 0:
            printf("\nEnd of stream, returning ...\n");
            break;
        case -1:
            perror("Error reading from network!\n");
            break;
    }
    printf("%c\n", input);

	int nist_socket = socket_connect(NIST_IP, NIST_PORT, FALSE);
	char* reply = read_line(nist_socket);

    reply = parse_time(reply, input);
    //send back to client
    int f = write(local_client_socket, reply, strlen(reply));
    if(reply != NULL){
        printf("\"%s\" written back to socket \n", reply);
    }
    else{
        fprintf(stderr, "Error: No reply found\n");
        exit(1);
    }

    socket_disconnect(nist_socket); //disconnecting the socket
    socket_disconnect(local_client_socket);
	//puts("returning");
    return NULL;
}

//Main function connects to the server, gets the reply,
//inserts '\0' into the reply at the position before the
//OTM, prints the reply then disconnects.
int main(int argc, char** argv){
	int server_socket = socket_connect(SERVER_IP, SERVER_PORT, TRUE);
	int client_socket;

	// listen for client connections (pending connections get put into a queue)
    if (listen(server_socket, NUM_CONNECTIONS) == -1) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }

	//Initialising the mutex
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		fprintf(stderr, "Error: Cannot initalise mutex\n");
		return 1;
	}
    // server loop
    while (TRUE) {
    	//Lock the mutex to prevent race condition
		pthread_mutex_lock(&lock);
		// accept connection to client
		if ((client_socket = accept(server_socket, NULL, NULL)) == -1) {
			perror("Error accepting client");
		} else {
			printf("\nAccepted client\n"); 
			pthread_create(&(thread), NULL, handle_client, (void *) &client_socket);  
		}
    }

    return 0;
}
