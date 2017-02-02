#include "aws.h"
#include "servers.h"

void error(char *msg)
{
	perror(msg);
	exit(0);
}

int main()
{
	int sock, length, fromlen, n;
	struct sockaddr_in server;
	struct sockaddr_in from;
	char buf[3000];

	//establish UDP socket in serverA
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		error("Opening socket");
	}
	
	length = sizeof(server);
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = 21205;

	//bind socket with IP address and port number
	if (bind (sock, (struct sockaddr *)&server, length) < 0)
	{
		error("binding");
	}
	fromlen = sizeof(struct sockaddr_in);
	printf("%s\n", "The Server A is up and running using UDP on port <21205>");

	while (1)
	{
		
		memset(buf, '\0', sizeof(buf));

		//receive data from aws in the form of char array
		n = recvfrom(sock, buf, 3000, 0, (struct sockaddr *)&from, &fromlen);


		if (n < 0)
		{
			error("recvfrom");
		}

		int count = 2;
		int index = 0;
		int num_fun = atoi(buf);
		int result[400];
	    memset(&result, 0, sizeof(result));

	    //transform the receving data from char to integer
		while (count < strlen(buf) - 1)
		{

			result[index] = atoi(buf + count);
			index++;
			while (buf[count] != 'n' && count < sizeof (buf))
			{
				count++;
			}
			count++;

		}

		printf("%s%d%s\n", "The Server A has received ",index," numbers");
	

		long long int Res;
		char fun[10];

		//realize the four functions according to the function number
		switch (num_fun)
		{
			case 1 :
			Res = Sum(result, index);
			strcpy(fun, "SUM");
			break;

			case 2 :
			Res = Max(result, index);
			strcpy(fun, "MAX");
			break;

			case 3 :
			Res = Min(result, index);
			strcpy(fun, "MIN");
			break;

			case 4 :
			Res = Sos(result, index);
			strcpy(fun, "SOS");
			break;

			default:
			error("ERROR function number");

		}

		printf("%s%s%s%lld\n", "The Server A has successfully finished the reduction ",fun,": ",Res);
		
		//transform the final result to integer form
		memset(&result, 0, sizeof(result));
		char sendmessage[400];
		memset(&sendmessage, 0, sizeof(sendmessage));
		_itoa(Res, sendmessage, 10);
		printf("%s\n", sendmessage);
		char *sendmes = sendmessage;

		//send the data to aws
		n = sendto(sock, sendmes, strlen(sendmessage) + 1, 0, (struct sockaddr *)&from, fromlen);
		if (n < 0)
		{
			error("sendto");
		}

		printf("%s\n\n", "The Server A has successfully finished sending the reduction value to AWS");
	}
}
