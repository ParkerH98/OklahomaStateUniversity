# OS-Group_B
Operating Systems Spring 2021 Group B Repository


### About
-----
Repo for the group B OS assignment. This is a client/server program that uses socket connections, IPC via pipes, and multithreaded file searching to search a database for a query
and send it back to the client.


### Usage
-------------
#### SERVER

* `gcc driver_server.c -lpthread -o server`
* `./server`

#### CLIENT
* `gcc driver_client.c -lpthread -o client`
* `./client [server IP address]`


### Important Notes
-------------
* Must specify an IP address when running the client program
* The client will create a new terminal each time the client program is ran. User must have 
    multiple iterations on a single program execution in order to see multiple queries on the same terminal
* If the program prematurely exits and the sockets aren't able to close, sometimes this will create a bind error on a
   future execution of the program. If this happens, change the `#define PORT` constant located in the header.h file
* Both the client and server require 'Control + C' in order to stop the program
* `landen.c` is not connected to the program. We were having issues with his functions on the day of submission so Michael wrote his own versions of `writeFile()` and `searchFile()`. Landen's code is commented out so it is not confused with implemented code.


### Contents
--------
#### PROGRAM FILES
* driver_client.c - main() for client
* driver_server.c - main() for server
* parker.c - client, manager, terminal printing, client socket connection, IPC via pipes
* joonmo.c - server socket connection, searching database with threads
* michael.c - searching database with threads, writing to history file, and searching history file
* landon.c
* header.h - includes, global function, and struct definitions


#### INPUT FILES
* Name.txt - file containing IDs, and names

* Satisfaction.txt - file containing IDs, satisfaction levels, average monthly hours, time spent in company in years, work accidents, and promotions in the last 5 years

* Salary.txt - file containing IDs, job titles, base pay, overtime pay, benefits, and status


### Group Members
-------------
1. Parker Hague
2. Joonmo Koo
3. Michael Oliver
4. Landen Thornton