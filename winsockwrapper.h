// CS 2690 Winsock Wrapper for *nix
// Last update: 12/14/17
// Patrick Felt
//
// This header file *must* not be submitted with your assignment.
// Programs must compile and run in Visual Studio/Windows.
// This wrapper file is provided *only* to allow you to
// write and debug your code under other compilers/platforms
// ----------------------------------------------------------------------------
#ifndef WINSOCKH
#define WINSOCKH
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#define WSACleanup()
#define INVALID_SOCKET -1
#define WSADATA int
#define MAKEWORD(x, y) 0
#define WSAStartup(x, y) 0
#define closesocket(x) shutdown(x, SHUT_WR)
#define WSAGetLastError() errno
#endif

