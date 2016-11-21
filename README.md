# daytime-client-server-cs460
In this second daytime semantics assignment you will focus on designing and implementing your own proprietary protocol, after you experienced how to comply to a given protocol.  

What to build
I want you to extend your current client, written in C, to (also) become a server that is capable of serving very specific information back to a new client that you will develop also. The information that this server needs to be able to pin-pointedly serve is - either of the - following:
  - The current year
  - The month of the year
  - The day of the month
  - The hour
  - The minute of the hour
  - The second
  
It is totally up to you, which conventions you adopt in order to communicate with your server, so that the server can actually, unambiguously, serve any of the above pieces of information. You need, however, fully disclose/describe those conventions.

You will also need to develop a GUI-based client, written in Java, that lives up to the protocol conventions and can actually talk to your server. Needless to say, your server will need to connect to a daytime server to actually receive the authentic time information, according to the daytime protocol conventions. This latter part is easy, as you already developed it in the last assignment.

From a procedural point of view, your two pieces of software work together like this: your GUI based client takes a request from a user that asks for a specific part of time information and connects to your server. The server turns around and contacts a daytime server, receives the complete time information and parses that information. Then it turns around again, serves the specific part of time information back to the client and closes the connection. The client displays the information in the GUI. 

What to submit

I ask you to submit three parts (which will result in more than three files):
  - Your client code, written in Java
  - Your server code, written in C
  - A memo word document, that precisely describes your protocol conventions 

In addition, I want you to show the proper working of the code by submitting screen shots of the GUI client, which you put into your word document and comment. Specifically, I want to see what the user put in and what gets returned and displayed in response.
