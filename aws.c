#include "aws.h"
#include "servers.h"

void error(char *msg)
{
	perror(msg);
	exit(0);
}

int main()
{
		//TCP
	int sockfd, newsockfd, clilen;
	char buffer[9000];
	char bufA[3000], bufB[3000], bufC[3000];
	int dataA[400], dataB[400], dataC[400],data[1200];
	struct sockaddr_in serv_addr, cli_addr;
	struct addrinfo hints, *res;
	int n, i, j;
	int sock, length;
	struct sockaddr_in serverA;
	struct sockaddr_in serverB;
	struct sockaddr_in serverC;
	struct sockaddr_in fromA, fromB, fromC;
	struct hostent *hpA, *hpB, *hpC;
	
	
    
	bzero ((char *)&serv_addr, sizeof(serv_addr));
    // Establish TCP socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		error("ERROR opening socket");
	}

	bzero ((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = 25205;
    
    //Bind TCP socket with IP address and port number
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		error("ERROR on binding");
	}

	//Listen the connection from client
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	length = sizeof (struct sockaddr_in);


	//Creat UDP socket in aws
	serverA.sin_family = AF_INET;
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (sock < 0)
	{
		error("socket");
	}

	memset(&hints, '\0', sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = 0;
	getaddrinfo(NULL, "24205", &hints, &res);

	//Bind UDP socket with its IP addrss and port number
	bind(sock, res->ai_addr, res->ai_addrlen);

	hpA = gethostbyname("localhost");

	if (hpA == 0)
	{
		error("Unknown host");
	}

	bcopy((char *)hpA -> h_addr, (char *)&serverA.sin_addr, hpA->h_length);
	
	serverA.sin_port = 21205;


	serverB.sin_family = AF_INET;
	
    hpB = gethostbyname("localhost");

	if (hpB == 0)
	{
		error("Unknown host");
	}


	bcopy((char *)hpB -> h_addr, (char *)&serverB.sin_addr, hpB->h_length);
	
	serverB.sin_port = 22205;


	serverC.sin_family = AF_INET;
	
	hpC = gethostbyname("localhost");

	if (hpC == 0)
	{
		error("Unknown host");
	}

	bcopy((char *)hpC -> h_addr, (char *)&serverC.sin_addr, hpC->h_length);
	
	serverC.sin_port = 23205;

	printf("%s\n", "The AWS is up and running.");

	
    while (1){

    	//Accept the connection and creat chile socket of TCP
    	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

		if (newsockfd < 0)
		{
			error ("ERROR on accept");
		}

    	memset(buffer, '\0', sizeof(buffer));
    	
    	//receving char array data from client and store them in buffer
		n = recv(newsockfd, buffer, 9000, 0);

		if (n < 0)
		{
			error ("ERROR reading from the socket");
		}

		int indexA = 0, indexB = 0, indexC = 0, index = 0, count = 2;
		long long int finalres = 0;
		memset(&data, 0, sizeof(data));
		memset(&dataA, 0, sizeof(dataA));
		memset(&dataB, 0, sizeof(dataB));
		memset(&dataC, 0, sizeof(dataC));
		bzero(bufA, 3000);
		bzero(bufB, 3000);
		bzero(bufC, 3000);

		//transform num_fun to Integer and distinguish function type
		int num_fun = atoi(buffer);
		char fun[10];
		bufA[0] = buffer[0];
		bufB[0] = buffer[0];
		bufC[0] = buffer[0];
		bufA[1] = 'n';
		bufB[1] = 'n';
		bufC[1] = 'n';

		//Transform receiving data from char type to int type
		while (count < strlen(buffer))
		{
			data[index] = atoi(buffer + count);
			index++;
			while (buffer[count] != 'n' && count < strlen(buffer))
			{
				count++;
			}
			count++;
		}

		printf("%s%d%s\n", "The AWS has received ",index," numbers from the client using TCP over port 25205");
		
		//Divide the receiving data into three groups and stored in different groups
		for (i = 0; i < index / 3; i++)
		{
			dataA[indexA] = data[i];
			indexA++;
		}
		for (i = index/3; i < 2 * index/3; i++)
		{
			dataB[indexB] = data[i];
			indexB++;
		}
		for (i = 2 * index/3; i < index; i++)
		{
			dataC[indexC] = data[i];
			indexC++;
		}

		//Transform three groups data from type integer to char and stored into three groups
		for (j = 0; j < indexA; j++)
		{
			int lenA = strlen(bufA);
			_itoa(dataA[j], bufA + lenA, 10);
			bufA[strlen(bufA)] = 'n';
		}
		for (j = 0; j < indexB; j++)
		{
			int lenB = strlen(bufB);
			_itoa(dataB[j], bufB + lenB, 10);
			bufB[strlen(bufB)] = 'n';
		}
		for (j = 0; j < indexC; j++)
		{
			int lenC = strlen(bufC);
			_itoa(dataC[j], bufC + lenC, 10);
			bufC[strlen(bufC)] = 'n';
		}

		//get the function type from function number
		switch(num_fun)
		{
			case 1 :
			strcpy(fun, "SUM");
			break;

			case 2 :
			strcpy(fun, "MAX");
			break;

			case 3 :
			strcpy(fun, "MIN");
			break;

			case 4 :
			strcpy(fun, "SOS");
			break;

			default:
			error("ERROR function number");
		}


		//send the first group char data to serverA
		n = sendto(sock, bufA, strlen(bufA), 0, &serverA, length);

		if (n < 0)
		{
			error("Sendto");
		}

		printf("%s%d%s\n", "The AWS has sent ",indexA," numbers to Backend-Server A");

		//receive the first group result from serverA
		n = recvfrom(sock, bufA, 400, 0, &fromA, &length);
		if (n < 0)
		{
			error("recvfrom");
		}

		printf("%s%s%s%s\n", "The AWS received reduction result of ",fun," from Backend-Server A using UDP over port 21205 and it is ",bufA);

		//send the second group char data to serverB
		n = sendto(sock, bufB, strlen(bufB), 0, &serverB, length);
		if (n < 0)
		{
			error("Sendto");
		}
		printf("%s%d%s\n", "The AWS has sent ",indexB," numbers to Backend-Server B");

		//receive the second group result from serverB
		n = recvfrom(sock, bufB, 400, 0, &fromB, &length);


		if (n < 0)
		{
			error("recvfrom");
		}

		printf("%s%s%s%s\n", "The AWS received reduction result of ",fun," from Backend-Server B using UDP over port 22205 and it is ",bufB);

		//send the third group char data to serverC
		n = sendto(sock, bufC, strlen(bufC), 0, &serverC, length);
		if (n < 0)
		{
			error("Sendto");
		}

		printf("%s%d%s\n", "The AWS has sent ",indexC," numbers to Backend-Server C");

		//receive the third group result from serverC
		n = recvfrom(sock, bufC, 400, 0, &fromC, &length);
		if (n < 0)
		{
			error("recvfrom");
		}

		printf("%s%s%s%s\n", "The AWS received reduction result of ",fun," from Backend-Server C using UDP over port 23205 and it is ",bufC);

		//transform three results from char array to integer
		long long int res[3];
		res[0] = atoll(bufA);
		res[1] = atoll(bufB);
		res[2] = atoll(bufC);

		//calculate the final result according to the three number from three servers
		if (num_fun == 1)
		{
			finalres = res[0] + res[1] + res[2];
		}
		else if (num_fun == 2)
		{
			finalres = res[0];
			if (res[1] > finalres)
			{
				finalres = res[1];
			}
			if (res[2] > finalres)
			{
				finalres = res[2];
			}
		}
		else if (num_fun == 3)
		{
			finalres = res[0];
			if (res[1] < finalres)
			{
				finalres = res[1];
			}
			if (res[2] < finalres)
			{
				finalres = res[2];
			}
		}
		else if (num_fun == 4)
		{
			finalres = res[0] + res[1] + res[2];
		}
		else
		{
			error("ERROR, function number");
		}

		printf("%s%s%s%lld\n", "The AWS has successfully finished the reduction ",fun,":", finalres);

		memset(&res, '\0', sizeof(res));

		char finalmes[30];
		_itoa(finalres, finalmes, 10);

		//send the final result to client
		n = send(newsockfd, finalmes, strlen(finalmes), 0);

		if (n < 0)
		{
			error("ERROR writing to socket");
		}

		printf("%s\n\n", "The AWS has successfully finished sending the reduction to client");

	}
}
