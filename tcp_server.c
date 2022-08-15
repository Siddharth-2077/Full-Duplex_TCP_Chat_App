
/*

    FULL-DUPLEX CHAT APPLICATION (Using TCP/IP Protocol):

    - Name: Siddharth M
    - University: MIT, Manipal (India)
    - Branch: Computer & Communication Engg.
    - Course: Network Programming & Advanced Communication Networks

*/

// TCP_SERVER:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SIZE 1000
#define PORT 5555

int main() {

    printf("\n TCP-SERVER \n");

    char recvBuffer[SIZE];
    char sendBuffer[SIZE];

    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    socklen_t clientLength;

    pid_t fork_return;

    int server_socket = 0;
    int client_socket = 0;
    
    // Create server tcp-socket:
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // bzero() clears data from start to end of the structure
    bzero(&serverAddress,sizeof(serverAddress));

    // Define this server's address:
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    // Bind server-socket to it's address:
    int bind_status = 0;
    bind_status = bind(server_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (bind_status < 0) {
        printf("\n>> Bind failed! Try different port number. \n");
        return 1;
    } 
    printf("\n>> Bind successful! \n");

    // Listen for client connections:
    listen(server_socket,5);
    printf("\n>> Listening for client connections... \n\n");

    // Accept client connections:
    client_socket = accept(server_socket, (struct sockaddr*)&clientAddress, &clientLength);

    // Fork the process after accepting:
    fork_return = fork();
    
    if (fork_return == 0) {     // Child process

        while(1) {

            // Clear the receiving buffer:
            bzero(&recvBuffer,sizeof(recvBuffer));

            // Receive data from client:
            recv(client_socket, recvBuffer, sizeof(recvBuffer), 0);            

            // Print client data:
            printf("CLIENT : %s\n", recvBuffer);

        }
    
    } else {                    // Parent process

        while(1) {
            
            // Clear the send buffer:
            bzero(&sendBuffer, sizeof(sendBuffer));

            // Read the message to send:
            fgets(sendBuffer, SIZE, stdin);

            // Send data to client:
            send(client_socket, sendBuffer, strlen(sendBuffer) + 1, 0);

        }

    }

    // Close the socket:
    close(server_socket);

    return 0;
}