
/*

    FULL-DUPLEX CHAT APPLICATION (Using TCP/IP Protocol):

    - Name: Siddharth M
    - University: MIT, Manipal (India)
    - Branch: Computer & Communication Engg.
    - Course: Network Programming & Advanced Communication Networks

*/

// TCP_CLIENT:

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

    printf("\n TCP-CLIENT \n");

    char sendBuffer[SIZE];
    char recvBuffer[SIZE];

    struct sockaddr_in serverAddress;

    pid_t fork_return;

    // Create client tcp-socket:
    int client_socket = 0;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // bzero() clears data from start to end of the structure
    bzero(&serverAddress, sizeof(serverAddress));

    // Define tcp-server's address:
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Connect to server:
    int connection_status = 0;
    connection_status = connect(client_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (connection_status < 0) {
        printf("\n>> Connection to server failed! \n");
        return 1;
    }
    printf("\n>> Connection established! \n\n");

    // Fork the process after successful connection:
    fork_return = fork();

    if (fork_return == 0) {     // Child process

        while(1) {
            
            // Clear the send buffer:
            bzero(&sendBuffer,sizeof(sendBuffer));

            // Read the message to send:
            fgets(sendBuffer, SIZE, stdin);

            // Send data to server:
            send(client_socket, sendBuffer, strlen(sendBuffer) + 1, 0);

        }

    } else {                    // Parent process

        while(1) {
            
            // Clear the receiving buffer:
            bzero(&recvBuffer, sizeof(recvBuffer));
            
            // Receive message from server:
            recv(client_socket, recvBuffer, sizeof(recvBuffer), 0);

            // Print server data:
            printf("SERVER : %s\n", recvBuffer);

        }

    }

    // Close the socket:
    close(client_socket);

    return 0;
}