#include "aws.h"
#include "servers.h"

void error(char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, const char *argv[])
{
	int sockfd, n, in;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	//establish socket of TCP connected with aws
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		error("ERROR opening socket");
	}

	server = gethostbyname("localhost");

	if (server == 0)
	{
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

	serv_addr.sin_port = 25205;

	//connect socket with TCP socket
	n = connect(sockfd, &serv_addr, sizeof(serv_addr));

	if (n < 0)
	{
		error("ERROR connecting");
	}

	int input[1200];
	char buffer[9000] = {"0"};
	char fun[10];

	//compare the input information to function number
	if (strcmp(argv[1], "sum") == 0)
	{
		buffer[0] = '1';
		strcpy(fun, "SUM");
	}
	else if (strcmp(argv[1], "max") == 0)
	{
		buffer[0] = '2'; 
		strcpy(fun, "MAX");
	}
	else if (strcmp(argv[1], "min") == 0)
	{
		buffer[0] = '3';
		strcpy(fun, "MIN");
	}
	else if (strcmp(argv[1], "sos") == 0)
	{
		buffer[0] = '4';
		strcpy(fun, "SOS");
	}
	else
	{
		error("ERROR function number");
	}

	buffer[1] = 'n';

	//read data from number file nums.csv and store them into the int array input
	//this piece of code is referenced from online instance of BaiduBaike
	FILE *fp;
	fp = fopen("nums.csv", "r");

	for (in = 0; fscanf(fp, "%d", input + in) != EOF; in++);

	int k;
	for (k = 0; k < in; k++)
	{
		int lenBuf = strlen(buffer);
		_itoa(input[k], buffer + lenBuf, 10);
		buffer[strlen(buffer)] = 'n';
	}

	printf("%s\n", "The client is up and running.");
	
	//send the information to aws
	n = send(sockfd, buffer, strlen(buffer), 0);
	if (n < 0)
	{
		error("ERROR writing to socket");
	}

	printf("%s%s%s\n", "The client has sent reduction type ",fun," to AWS");
	printf("%s%d%s\n", "The client has sent ",in," numbers to AWS");

	bzero(buffer, 9000);

	//receive the final result from aws.
	n = recv(sockfd, buffer, 8999, 0);

	if (n < 0)
	{
		error("ERROR reading from socket");
	}
	
	printf("%s%s%s%s\n\n", "The client has received ",fun," :",buffer);

}
