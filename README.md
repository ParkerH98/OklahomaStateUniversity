# OS-Group_B
Operating Systems Spring 2021 Group B Repository


### Usage
-------------

`gcc driver_client.c -lpthread -o client`

`./client [server IP address]`

`gcc driver_server.c -lpthread -o server`

`./server`


### Important Notes
-------------
* Must specify an IP address when running the client program
* The client will create a new terminal each time the client program is ran. User must have 
    multiple iterations on a single program execution in order to see multiple queries on the same terminal


### Group Members
-------------
1. Parker Hague
2. Joonmo Koo
3. Michael Oliver
4. Landen Thornton


### Contents
--------
#### INPUT FILES
* Name.txt - file containing IDs, and names

* Satisfaction.txt - file containing IDs, satisfaction levels, average monthly hours, time spent in company in years, work accidents, and promotions in the last 5 years

* Salary.txt - file containing IDs, job titles, base pay, overtime pay, benefits, and status

#### PROGRAM FILES
* parker.c - TBD
* joonmo.c - TBD
* michael.c - TBD
* landon.c - TBD

### About
-----
Repo for the group B OS assignment. This is a client/server program that uses socket connections, IPC via pipes, and multithreaded file searching to search a database for a query
and send it back to the client.