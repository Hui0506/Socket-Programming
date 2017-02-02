#include "servers.h"
#include "hui_fun.h"

void error(char *msg)
{
	perror(msg);
	exit(0);
}

int main()
{
	int sockfd, n, in;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int input[300];
	char buffer[1500];
	buffer[0] = '4';
	buffer[1] = 'n';

	FILE *fp;
	fp = fopen("/Users/macbook/Desktop/pro_450/nums.csv", "r");
	for (in = 0; fscanf(fp, "%d", input + in) != EOF; in++);
	for (int k = 0; k < in; k++)
	{
		int lenBuf = strlen(buffer);
		_itoa(input[k], buffer + lenBuf, 10);
		buffer[strlen(buffer)] = 'n';
	}
	printf("%s\n", buffer);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		error("ERROR opening socket");
	}

	server = gethostbyname("localhost");
	if (server == NULL)
	{
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

	serv_addr.sin_port = 25205;

	if (connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0)
	{
		error("ERROR connecting");
	}
	
	n = write(sockfd, buffer, strlen(buffer));
	if (n < 0)
	{
		error("ERROR writing to socket");
	}
	bzero(buffer, 1500);
	n = read(sockfd, buffer, 1499);
	if (n < 0)
	{
		error("ERROR reading from socket");
	}
	printf("%s\n", buffer);

	return 0;
}
