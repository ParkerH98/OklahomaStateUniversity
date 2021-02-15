#include "header.h"
#include "stringOps.c"

// void initializeStructure(int *serialNums, char **items, char **prices, char **stores);

// void removeFirst(char *str, const char toRemove);



void initializeStructure(int *serialNums, char **items, char **prices, char **stores){

  struct Item itemsList[100];

  int i;
  for (int i = 0; i < 100; i++){


    itemsList[i].serialNum = serialNums[i];
    strcpy(itemsList[i].item, items[i]);
    strcpy(itemsList[i].price, prices[i]);
    strcpy(itemsList[i].store, stores[i]);
  }

  printf("%d %s %s %s", itemsList[67].serialNum, itemsList[67].item, itemsList[67].price, itemsList[67].store);
}

int* initializeSerial(){

  // double pointers to arrays
  int *serialNumsPtr;

  // allocates an array for each row of the data
  serialNumsPtr = malloc(sizeof(int *) * NUM_ITEMS);


  return serialNumsPtr;
}

char** initializeItems(){

  // double pointers to arrays
  char **itemsPtr;


  // allocates an array for each row of the data
  itemsPtr = malloc(sizeof(char *) * NUM_ITEMS);

  int i;
  for (i = 0; i < NUM_ITEMS; i++){

    // allocates column elements for each row array
    itemsPtr[i] = malloc(sizeof(char) * 256);
  }
  return itemsPtr;
}

char** initializePrices(){

  // double pointers to arrays
  char **pricesPtr;

  // allocates an array for each row of the data
  pricesPtr = malloc(sizeof(char *) * NUM_ITEMS);

  int i;
  for (i = 0; i < NUM_ITEMS; i++){

    // allocates column elements for each row array
    pricesPtr[i] = malloc(sizeof(char) * 256);
  }
  return pricesPtr;
}

char** initializeStores(){

  // double pointers to arrays
  char **storesPtr;

  // allocates an array for each row of the data
  storesPtr = malloc(sizeof(char *) * NUM_ITEMS);

  int i;
  for (i = 0; i < NUM_ITEMS; i++){

    // allocates column elements for each row array
    storesPtr[i] = malloc(sizeof(char) * 256);
  }
  return storesPtr;
}



void readFile(){

  FILE *f;
  f = fopen("items.txt", "r");

  // for storing each line of items.txt 
  char lines[NUM_ITEMS][256];

  // arrays to store serial number, item, price, and location
  int serialNums[NUM_ITEMS];
  char items[NUM_ITEMS][256];
  char details[NUM_ITEMS][256];
  char prices[NUM_ITEMS][256];
  char stores[NUM_ITEMS][256];

  // temp strings for string manipulation
  char temp[256];

  int index = 0;

  // reads items.txt line by line and stores string into lines[]
  while(fgets(lines[index], 256, f)) {

    /* get rid of ending \n from fgets */
    lines[index][strlen(lines[index]) - 1] = '\0';

    // SERIAL NUMBERS
    // =============================================================================================
    // creates copies of the original line for string manipulation
    strcpy(temp, lines[index]);

    // splits whole line by '.' and assigns the serial number to serialNums[]
    serialNums[index] = atoi(strtok(temp, "."));


    // ITEMS
    // =============================================================================================
    // resets the temp string to the original copied string ~ lines[index]
    strcpy(temp, lines[index]);

    // splits line by the $
    strtok(temp, "$");

    // gets substring after the serial number ~ after the '.'
    char *sep_at = strchr(temp, '.');

    // copies items to the items[]
    strcpy(&items[index][0], (sep_at + 1));

    // variables used when stripping white space from items[]
    char test_buffer[256];
    char comparison_buffer[256];
    int compare_pos;

    // Fill buffer with known value to verify we do not write past the end of the string.
    memset(test_buffer, 0xCC, sizeof(test_buffer));
    strcpy(test_buffer, items[index]);
    memcpy(comparison_buffer, test_buffer, sizeof(comparison_buffer));

    // copies final versions of stripped item strings into items[]
    strcpy(&items[index][0], trim(test_buffer));


    // PRICES
    // =============================================================================================
    // resets the temp string to the original copied string ~ lines[index]
    strcpy(temp, lines[index]);

    // seprates main line by $
    char *sep_at2 = strchr(temp, '$');

    // stores separation into details[]
    strcpy(&details[index][0], (sep_at2));

    // stores details into temp3
    strcpy(temp, details[index]);

    // splits the price and store by 'on' or 'at' --- used to extract the price
    if (index == 46) {strtok(temp, "on");}
    else {strtok(temp, "at");}

    // copies price from split into prices[]
    strcpy(prices[index], temp);


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

    // stores the result of the strtok split into the stores[]
    strcpy(stores[index], store);

    // DEBUG
    // printf("%d %s %s %s\n", serialNums[index], items[index], prices[index], stores[index]);

    // printf("%d ", serialNums[index]);
    // printf("%s ", items[index]);
    // printf("%s ", details[index]);
    // printf("%s ", prices[index]);
    // printf("%s\n", stores[index]);
    // printf("\n");
    index++;
  }

  // dynamically allocates arrays
  int * serialNumsPtr = initializeSerial();
  char ** itemsPtr = initializeItems();
  char ** pricesPtr = initializePrices();
  char ** storesPtr = initializeStores();

  initializeStructure(serialNumsPtr, itemsPtr, pricesPtr, storesPtr);
}