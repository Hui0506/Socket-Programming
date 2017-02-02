#include "servers.h"
#include "hui_fun.h"


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
	char buf[1024];

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		error("Opening socket");
	}
	
	length = sizeof(server);
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = 23205;
	if (bind (sock,(struct sockaddr *)&server, length) < 0)
	{
		error("binding");
	}
	fromlen = sizeof(struct sockaddr_in);

	while (1)
	{
		n = recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&from, &fromlen);

		int count = 2;
		int index = 0;
		int num_fun = atoi(buf);
		int result[300];
	    memset(&result, 0, sizeof(result));

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
		for (int i = 0; i < index; i++){
			printf("%d    ", result[i]);
		}
		
		if (n < 0)
		{
			error("recvfrom");
		}

		int Res;

		switch (num_fun)
		{
			case 1 :
			Res = Sum(result, index);
			break;

			case 2 :
			Res = Max(result, index);
			break;

			case 3 :
			Res = Min(result, index);
			break;

			case 4 :
			Res = Sos(result, index);
			break;

			default:
			printf("%s\n", "error");

		}
		printf("\n%d\n", Res);

		memset(&result, 0, sizeof(result));
		index = 0;
		write(1, "Received a datagram : ", 21);
		write(1, buf, n);
		char sendmessage[300];
		memset(&sendmessage, 0, sizeof(sendmessage));
		_itoa(Res, sendmessage, 10);
		printf("%s\n", sendmessage);
		char *sendmes = sendmessage;

		
		n = sendto(sock, sendmes, strlen(sendmessage) + 1, 0, (struct sockaddr *)&from, fromlen);
		if (n < 0)
		{
			error("sendto");
		}
	}
}
