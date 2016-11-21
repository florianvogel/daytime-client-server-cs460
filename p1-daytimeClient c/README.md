# Part 1
This assignment concentrates on protocol development. Semantically, you are asked to work with daytime servers that are provided by the US government, with a catch: you will refine their service, based on the information that they serve.

What to do

In this first step you are going to write a simple client that can connect to a daytime server, retrieve the server's response and just print it out. The server sends an OTM (on-time marker), that you need to be able to recognize and, once the marker was received, your client will take this as a sign to tear down the connection to the server. The client needs to be written in C.

You are not allowed to hard-code server addresses into your program, instead I ask you to provide a header file which, possibly among other things, contains symbolic constants for the server name, the server port number and also the OTM character.

I ask you to clearly delineate the code that is concerned with the raw networking and the code that receives the time information. By raw code I mean setting up the connection and tearing it down - everything that happens "in between" is depending on the daytime service. That said, I ask you to write a function that can read a line from a given file descriptor and that returns a character pointer, which points to the string received. In this context, a "line" is a bunch of characters delimited by the OTM. The string returned by the function needs to be ASCII zero terminated at the position that is exactly one character before the OTM. The function has to have this signature:

char* read_line(int socket);

What to submit

Submit the well-commented source code of you both your program and the header file.

Hint

Information about the daytime service and the list of servers you will find here.

The space for putting characters needs to be dynamically created by and within the above function (with malloc()), as local variables are destroyed after the function returns and using global variables is bad programming practice. You may assume that the string the daytime service returns is no longer than 80 characters - which you are allowed to hard-code.