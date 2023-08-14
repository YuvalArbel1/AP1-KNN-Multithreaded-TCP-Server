<h1 align="center">
  <br>
  <a href="https://github.com/TalMizrahii/AP1Project"><img src="https://img.icons8.com/color/344/c-plus-plus-logo.png" alt="C++" width="200"></a>
  <br>
  Advanced-Programming-1
  <br>
</h1>

<h4 align="center">This github repository is for the final assignment given in Advanced Programming 1 course, Bar Ilan University.


<p align="center">
  <a href="#description">Description</a> •
  <a href="#implementation">Implementation</a> •
  <a href="#installing-and-executing">Installing And Executing</a> •
  <a href="#authors">Authors</a> 
</p>

## Description

*The final project seats in the "main" branch!*

This program has two components, a Server and a client. The Server is a TCP server, which can receive two CSV files. One of the files contains vectors of doubles and a specific classification, and the other file contain vectors of doubles with no classification. The Client can connect to the server, enter a path to the files, and ask the server to calculate the classification of each vector from the unclassified file using [KNN algorithm](https://en.wikipedia.org/wiki/K-nearest_neighbors_algorithm). The server can send to the client the result, and if the client wishes to, it can can send it to a file in the client's computer.

![adfbh](https://user-images.githubusercontent.com/103560553/213933559-65033ac1-ab25-4200-9162-e51c7295ee2c.png)


The client receives two system arguments. The IP address of the server, and his port number. The server gets only a port number to bind to his main socket.
  
 After initiation, the client connects to the server. The server sends the client a menu, and from it, the client can choose a command for the server. 

  
The menu looks like this:
  
  <img width="368" alt="1" src="https://user-images.githubusercontent.com/103560553/213907301-233a977c-a5b1-49f8-b42c-97fd3f332baa.PNG">


The user can choose any option from the menu. If he enters a choice outside of the menu, the server will reply "invalid input" message and will send the menu again.
  
In the first option, the user will be asked to upload files to the server. He will be asked to enter a path to a classified CSV file, and a path to an unclassified CSV file. The client will automatically send the content of the files to the server. This option will look like that:


  <img width="368" alt="3" src="https://user-images.githubusercontent.com/103560553/213906933-1b0cd068-c3dc-4808-a286-e36b1b564603.PNG">

  
If the user asks for the algorithm settings, the server will send him the current settings of the KNN algorithm. The message with the default settings looks like that:

<img width="370" alt="2" src="https://user-images.githubusercontent.com/103560553/213906987-efa9ee9f-1935-4b0d-860b-9d322b0b5018.PNG">
  
If he wants no changes to be made, he can press ENTER and the server will send the menu again. If the user wants to change the settings, he can enter a new K element, and a metric of his choice from these options:
  
  
  * MAN - [Taxicab geometry](https://en.wikipedia.org/wiki/Taxicab_geometry)
  
  ![image](https://user-images.githubusercontent.com/103560553/202403477-4c2885df-8eee-4721-897b-dee4e95c4ed0.png)
  
  * AUC - [Euclidean distance](https://en.wikipedia.org/wiki/Euclidean_distance)
  
  ![image](https://user-images.githubusercontent.com/103560553/202403137-049e516b-ac15-4e21-abbc-bf4f465a83bf.png)

  * CHB - [Chebyshev distance](https://en.wikipedia.org/wiki/Chebyshev_distance)
  
  ![image](https://user-images.githubusercontent.com/103560553/202403736-3438755a-f128-46a9-8f55-4b1cf69a215f.png)

  * CAN - [Canberra distance](https://en.wikipedia.org/wiki/Canberra_distance)

  ![image](https://user-images.githubusercontent.com/103560553/202403909-432f6285-c7cb-4a78-b9e7-a0b6b837c455.png)

  * MIN - [Minkowski distance](https://en.wikipedia.org/wiki/Minkowski_distance)
  
  ![image](https://user-images.githubusercontent.com/103560553/202404050-595c6cba-1b98-42ba-868c-c2c28586d6e4.png)


 In the third option, the client can just classify the data in the server. If no files were uploaded, the server will reply with an error message, and send the menu again. This part will look like this:
  
  
<img width="285" alt="4" src="https://user-images.githubusercontent.com/103560553/213907466-b97fdb4d-20e7-4e9c-8049-776ea83f8145.PNG">


  In option number 4, the client can request the result of the classification. The server will send the client the result of each vector in the order he received it. If no classification command is performed or no files were uploaded, the server will send an error message. The result will be displayed like that:
  
<img width="288" alt="5" src="https://user-images.githubusercontent.com/103560553/213907770-2840113a-7d60-48f5-8dd0-2fcc5e75d638.PNG">

The last operational option is to download the results to the client's computer. If the user asks for it, the user will be asked to enter a path to store the file. After that, the server will send the results and the client will write them to the file. A message of validation will be presented to the client when the download will complete. If no data or results exist within the server, an error message will be sent. The communication looks like this:
  
  <img width="292" alt="6" src="https://user-images.githubusercontent.com/103560553/213908062-e6346e50-af08-4001-9d2a-4f1e06781048.PNG">

 And the content of the file will look like that:
  
  <img width="547" alt="7" src="https://user-images.githubusercontent.com/103560553/213908097-36d254be-85bc-41bb-a6b0-a1b891a1a6d5.PNG">

The last option (8) is to close the connection. all data will be released and the client socket will be closed. The server will move to the next connection.
  


## Implementation
  
  Both server and client share the IO directory. This directory's purpose is to allow them to communicate threw different IO ways, such as sockets, keyboard io, etc. They use the AbstractDefaultIO to polymorphism the IO tool they use. In this program, we use the TCP socket IO. We implemented a self-protocol to transfer data using the SocketIO read and write.  The protocol adds the char "$" to the end of the message we want to send.  When we read the message in the read method, the protocol concatenates the data (because of the [TCP](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) segmentation mechanism), to ensure all data will be received as one message.
### client
  
The Clients implementation is relatively basic. It uses "operations" to fulfill the user requests, such as printing the results of the classification or entering a path to a file. The communication with the server is performed as a "ping pong" talk. If the client sends a message to the server, it can't send a repetitive message until the server replies with a message of its own. All client operations are made sequentially, except the "download results". in this option, the client opens a new thread, which gives him the ability to concurrently make new commends while he downloads the results to his computer.
  
<img width="300" alt="image" src="https://user-images.githubusercontent.com/112869076/210267297-323a511d-25c7-42ab-9493-fa0617a78b81.png">
  
### Server
  
The server's implementation is based on a CLI with the client. After the server accepts a new client, it opens a thread for this client, which gives him the ability to concurrently accept new clients and handle them. The server implements the [Command](https://en.wikipedia.org/wiki/Command_pattern) design pattern, giving him the modular option to add and remove new features from the menu. The server uses the RelativeDatabase class to store all information from the client. This class is allocated on the heap to assure data modularity and safe data sharing between the different commands.
  
A standard UML of this design pattern is:
  
  <img width="471" alt="11" src="https://user-images.githubusercontent.com/103560553/213909239-9831578a-e806-4657-a483-57a9ff2b14e2.PNG">


  

## Installing And Executing

To clone and run this application, you'll need [Git](https://git-scm.com) installed on your computer. From your command line (running on localhost and port number 12345 - change if necessary):

```bash
# Clone this repository.
$ git clone https://github.com/TalMizrahii/AP1-KNN-Multithreaded-TCP-Server

# Go into the repository.
$ cd AP1-KNN-Multithreaded-TCP-Server

# Compile using makefile.
$ make
```
  This command will create two .out files; server.out and client.out.
  
```bash
# To run the server with default port:
$ make run-server
```
To run the client with the default connection settings:
  
```bash
$ make run-client
```

To clean the .out files:

```bash
$ make clean
```



## Authors
* [@Yuval Arbel](https://github.com/YuvalArbel1)
* [@Tal Mizrahi](https://github.com/TalMizrahii)

