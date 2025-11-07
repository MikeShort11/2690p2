// CS 2690 Program 1 
// Simple Windows Sockets Echo Client (IPv6)
// Last update: 2/12/19
// <Your name here> <Your section here> <Date>
// <Your Windows version and Visual Studio version>
//
// Usage: WSEchoClientv6 <server IPv6 address> <server port> <"message to echo">
// Companion server is WSEchoServerv6
// Server usage: WSEchoServerv6 <server port>
//
// This program is coded in conventional C programming style, with the 
// exception of the C++ style comments.
//
// I declare that the following source code was written by me or provided
// by the instructor. I understand that copying source code from any other 
// source or posting solutions to programming assignments (code) on public
// Internet sites constitutes cheating, and that I will receive a zero 
// on this project if I violate this policy.
// ----------------------------------------------------------------------------

// Minimum required header files for C Winsock program
#include <netinet/in.h>
#include <stdio.h>       // for print functions
#include <stdlib.h>      // for exit() 
#include <string.h>
#include <sys/socket.h>
#include "winsockwrapper.h"

// #define ALL required constants HERE, not inline 
// #define is a macro, don't terminate with ';'  For example...
#define RCVBUFSIZ 50

// declare any functions located in other .c files here
void DisplayFatalErr(char *errMsg)
{
	fprintf(stderr, "%s: %d\n", errMsg, WSAGetLastError());  // Returns error code from current task or thread
	WSACleanup();
	exit(1);
}


int main(int argc, char *argv[])   // argc is # of strings following command, argv[] is array of ptrs to the strings
{
	// Declare ALL variables and structures for main() HERE, NOT INLINE (including the following...)
	WSADATA wsaData;                // contains details about WinSock DLL implementation
	
   //check for command line arguments
   if (argc != 2) {
      fprintf(stderr, "Usage: program <port number>");
      exit(1);
   }

   //convert port number to int
   int port = atoi(argv[1]);

   struct sockaddr_in6 serverInfo; //server address
   memset(&serverInfo, 0, sizeof(serverInfo)); //zero out the structure
   serverInfo.sin6_family = AF_INET6; //address family = IPv6
   serverInfo.sin6_port = htons(port); //convert int port to network order
   serverInfo.sin6_addr = in6addr_any; //any IPv6 address

   int listenSocket;
   listenSocket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP); //create a listen socket
   if (listenSocket == INVALID_SOCKET) {
      DisplayFatalErr("socket() failed");
   }
   printf("listen socket made sucsessfully\n");

   //bind the listen socket to the server address
   bind(listenSocket, (struct sockaddr *) &serverInfo, sizeof(serverInfo)); //bind the listen socket to the server address

   //listen for incoming connections
   listen(listenSocket, SOMAXCONN); //listen for incoming connections
   printf("listening for incoming connections\n");

   for (;;) {
      struct sockaddr_in6 clientInfo; //client address
      socklen_t clientAddrLen = sizeof(clientInfo);
      int clientSocket = accept(listenSocket, (struct sockaddr *) &clientInfo, &clientAddrLen); //accept an incoming connection
      if (clientSocket == INVALID_SOCKET) {
         DisplayFatalErr("accept() failed");
      }
      printf("Processing client request on socket %d\n", clientSocket);

      //read the client request
      char request[RCVBUFSIZ + 1];
      int bytesRead = recv(clientSocket, request, RCVBUFSIZ, 0);
      if (bytesRead > 0) {
         request[bytesRead] = '\0';
         printf("Received request: %s\n", request);
         //send the response to the client
         send(clientSocket, request, bytesRead, 0);
      }
      else {
         DisplayFatalErr("recv() failed");
      }

      //close the client socket
      closesocket(clientSocket);
   }

   WSACleanup();
   printf("winsock dll cleanup ran sucsessfully\n");
   exit(0);
   return 0;
}
