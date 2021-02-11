#include "header.h"
#include "stringOps.c"

#define NUM_ITEMS 100

void removeFirst(char *str, const char toRemove);

void readFile(){

  FILE *f;
  f = fopen("items.txt", "r");

  // for storing each line of items.txt 
  char lines[NUM_ITEMS][256];

  // arrays to store serial number, item, price, and location
  int nums[NUM_ITEMS];
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

    // splits whole line by '.' and assigns the serial number to nums[]
    nums[index] = atoi(strtok(temp, "."));


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
    printf("%d %s %s %s\n", nums[index], items[index], prices[index], stores[index]);

    // printf("%d ", nums[index]);
    // printf("%s ", items[index]);
    // printf("%s ", details[index]);
    // printf("%s ", prices[index]);
    // printf("%s\n", stores[index]);
    // printf("\n");
    index++;
  }
}