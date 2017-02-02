1. What have your done?
  a. Learned the functions used in the socket programming such as accept(), bind(), sendto() and so on.
  b. Familiarized conceptions about the socket working mechanism including TCP and UDP.
  c. In the client, realized TCP connection with AWS, and read data from data file and the function type form command line. At the same time, add a separator ’n’ among numbers. Then transformed all data from integer to char array and the function type to a function number. At last sent those chars to AWS server.
  d. In the server of AWS, connected TCP with client, received data at the type of char array. Then transformed them to integers and divided them into three parts. For each part, transformed integers to char array. Established a UDP socket and connected it with Backend-Server A, sent the first part to A. Then connected the socket with B, sent the second part to B. Last connected the socket with C, sent the last part char data to C.
  e. In the server A, established UDP socket and connected with AWS. Received data and transformed them into integer, realized four functions according to the function number, and then transformed the result into char and sent back.
  f. In the server B, the same of server A.
  g. In the server C, the same of server A.

2. What your code files and what each one of them does?
  a. C file: client.c realizes the reading data and TCP connection between client and AWS server. And it transforms the function type to function number. At last it sends the data to AWS.
  b. C file: aws.c realizes the TCP connection with client and receiving data from client. it separates data into three parts and sends each part to corresponding back-end server. After receiving result from 3 servers. It processes three results according to the function and at last sends it back.
  c. C file: serverA.c realizes the UDP connection with AWS and processes data according to the function number. At last it sends the result back. 
  d. C file: serverB.c realizes the UDP connection with AWS and processes data according to the function number. At last it sends the result back. 
  c. C file: serverC.c realizes the UDP connection with AWS and processes data according to the function number. At last it sends the result back. 
  e. Header file: aws.h includes all headers would be used in the routine.
  f. Header file: servers.h includes functions of _itoa and Sum, Mam, Min, Sos. The _itoa is used to transform integer to char array. The Sum is used to realize the function of sum, the Min is used to realizes the function of min, the Max is used to realizes the function of max and the Sos is used to realizes the function of sos.
  
3. What the TA should do to run your programs.
  a. Rename the data file of “nums.csv” in the csv format.
  b. Compile c file and start by the use of Makefile. Type make all to compile and make aws, make serverA, make serverB, make serverC to run the servers file. At last type the ./client + function type in the first terminal. The function is one of “sum”, “max”, “min”, “sos”.

4. The format of all the messages exchanged.
  a. Reading format in client: Integer
  b. Transforming format between client and AWS: Char Array.
  c. Separating format in AWS: Integer.
  d. Transforming format between AWS and server A: Char Array.
  e. Realising function format in server A: Integer.
  f. Sending result back to AWS from A: Char Array.
  g. Transforming format between AWS and server B: Char Array.
  h. Realising function format in server B: Integer.
  i. Sending result back to AWS from B: Char Array.
  j. Transforming format between AWS and server C: Char Array.
  k. Realising function format in server C: Integer.
  l. Sending result back to AWS from C: Char Array.
  m. Realising function format in AWS: Integer.
  n. Sending back to client: Char Array.

5. Idiosyncrasy programs?
  If the number of nums is exceed 1000 and each number is larger 9999, it will over flow. 

6. Reused Code.
  Function _itoa is referenced the source code of C function itoa. And the read function is referenced from online instance from Baidu Baike. Some codes are referenced from Beej’s Programming Tutorial.
    
