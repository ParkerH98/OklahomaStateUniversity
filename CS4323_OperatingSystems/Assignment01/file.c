// move assert

// delte copy of struct array


#include "header.h" // header file containing function prototypes and includes statements
#include "stringOps.c" // link to file containing functions for string manipulations

#define MEMORY_NAME "SharedMemory"

/*
---------------------------------------------------------
Takes in 4 input arrays and stores the data from each array
index into a struct array where each index is the information
for one gift item.

Params: int and 3 char arrays containing the items.txt info
Return: void
*/
void initializeStructure(int serialNums[NUM_ITEMS], char items[NUM_ITEMS][256], char prices[NUM_ITEMS][16], char stores[NUM_ITEMS][256]){

  // struct Item // struct to hold the contents of the items.txt file
  // {
  //   int serialNum;
  //   char item[256];
  //   char price[16];
  //   char store[64];
  // };

  int shmfd = shm_open (MEMORY_NAME, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR); // creates file descriptor for shared memory
  assert (shmfd != -1);   // throws error if it fails

  assert (ftruncate (shmfd, sizeof (struct Item) * 100) != -1); // Resize the region to store 100 struct instances

  struct Item *shm_struct = mmap (NULL, sizeof (struct Item) * 100, // creates shared memory object
                            PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);

  assert (shm_struct != MAP_FAILED);

  pid_t child_pid = fork(); // creates child process
  if (child_pid == 0) // child process executes 
  {
    int i;
    
    for (int i = 0; i < 100; i++) // loops 100 times and stores arrays into their respective fields of the Item struct
    {
      shm_struct->serialNum = serialNums[i];
      strcpy(shm_struct->item, items[i]);
      strcpy(shm_struct->store, stores[i]);
      strcpy(shm_struct->price, prices[i]);

      shm_struct++;
    }

    munmap (shm_struct, sizeof (struct Item) * 100); // Unmap and close the child's shared memory access
    close (shmfd); // closes file descriptor
    exit(0); // child exits
  }

  wait (NULL); // Make the parent wait until the child has exited

  process(shm_struct); // calls the function to execute the processes and passes the shared memory object

  munmap (shm_struct, sizeof (struct Item) * 100); // Unmap and close the child's shared memory access
  close (shmfd); // closes file descriptor
  shm_unlink (MEMORY_NAME); // deletes shared memory space
}


/*
---------------------------------------------------------
Reads in the items.txt file line by line and extracts the 
data and stores into proper arrays.

Params: none
Return: void
*/
void readFile(){

  FILE *f; // file pointer
  f = fopen("items.txt", "r"); // opens file for reading

  char lines[NUM_ITEMS][256]; // for storing each line of items.txt 

  // arrays to store serial number, item, price, and location
  int serialNums[NUM_ITEMS];
  char items[NUM_ITEMS][256];
  char details[NUM_ITEMS][256];
  char prices[NUM_ITEMS][16];
  char stores[NUM_ITEMS][256];

  char temp[256]; // temp strings for string manipulation

  int index = 0;

  while(fgets(lines[index], 256, f)) // reads items.txt line by line and stores string into lines[]
  {
    lines[index][strlen(lines[index]) - 1] = '\0'; // get rid of ending \n from fgets

    // SERIAL NUMBERS
    // =============================================================================================
    strcpy(temp, lines[index]); // creates copies of the original line for string manipulation

    serialNums[index] = atoi(strtok(temp, ".")); // splits whole line by '.' and assigns the serial number to serialNums[]


    // ITEMS
    // =============================================================================================
    strcpy(temp, lines[index]); // resets the temp string to the original copied string ~ lines[index]

    strtok(temp, "$"); // splits line by the $

    char *sep_at = strchr(temp, '.'); // gets substring after the serial number ~ after the '.'

    strcpy(&items[index][0], (sep_at + 1)); // copies items to the items[]

    // variables used when stripping white space from items[]
    char test_buffer[256];
    char comparison_buffer[256];
    int compare_pos;

    // Fill buffer with known value to verify we do not write past the end of the string.
    memset(test_buffer, 0xCC, sizeof(test_buffer));
    strcpy(test_buffer, items[index]);
    memcpy(comparison_buffer, test_buffer, sizeof(comparison_buffer));

    strcpy(&items[index][0], trim(test_buffer)); // copies final versions of stripped item strings into items[]


    // PRICES
    // =============================================================================================
    strcpy(temp, lines[index]); // resets the temp string to the original copied string ~ lines[index]

    char *sep_at2 = strchr(temp, '$'); // seprates main line by $

    strcpy(&details[index][0], (sep_at2)); // stores separation into details[]

    strcpy(temp, details[index]); // stores details into temp3

    // splits the price and store by 'on' or 'at' --- used to extract the price
    if (index == 46) {strtok(temp, "on");}
    else {strtok(temp, "at");}

    strcpy(prices[index], temp); // copies price from split into prices[]


    // STORES
    // =============================================================================================
    char* store;

    // removes the hanging t or n in the second token from the strtok() call
    if (index == 46) {
      store = strtok(NULL, "");
      removeFirst(store, 'n');
      removeFirst(store, ' ');
    }
    else {
      store = strtok(NULL, "");
      removeFirst(store, 't');
      removeFirst(store, ' ');
    }
    strcpy(stores[index], store); // stores the result of the strtok split into the stores[]

    index++;
  }

  initializeStructure(serialNums, items, prices, stores); // passes in arrays to initialize the Item struct
}