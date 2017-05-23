#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int s;
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	struct addrinfo hints, *result;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; /* IPv4 only */
	hints.ai_socktype = SOCK_STREAM; /* TCP */

	s = getaddrinfo("www.illinois.edu", "80", &hints, &result);
	if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    	exit(1);
	}

	if(connect(sock_fd, result->ai_addr, result->ai_addrlen) == -1){
        perror("connect");
        exit(2);
    }

	char *buffer = "GET / HTTP/1.0\r\n\r\n";
	printf("SENDING: %s", buffer);
	printf("===\n");

    // For this trivial demo just assume write() sends all bytes in one go and is not interrupted

	write(sock_fd, buffer, strlen(buffer));

	char resp[1000];
	int len = read(sock_fd, resp, 999);
	resp[len] = '\0';
	printf("%s\n", resp);

    return 0;
}
