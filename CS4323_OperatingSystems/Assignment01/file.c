#include "header.h"
#define NUM_ITEMS 100

char lines[NUM_ITEMS][256];
char items[NUM_ITEMS][256];

char *trim(char *str);
// void test(char *sample_strings[]);

void readFile(){

  FILE *f;
  f = fopen("items.txt", "r");

  // for storing each line of items.txt 
  
  int nums[NUM_ITEMS];
  // char items[NUM_ITEMS][256];
  char details[NUM_ITEMS][256];
  char prices[NUM_ITEMS][256];
  char stores[NUM_ITEMS][256];

  // temp strings for string manipulation
  char temp1[256];
  char temp2[256];
  char temp3[256];

  int index = 0;

  while(fgets(lines[index], 256, f)) {

    /* get rid of ending \n from fgets */
    lines[index][strlen(lines[index]) - 1] = '\0';

    // creates copies of the original line for string manipulation
    strcpy(temp1, lines[index]);
    strcpy(temp2, lines[index]);
    strcpy(temp3, lines[index]);

    // assigns serial numbers to array
    nums[index] = atoi(strtok(temp1, "."));


    // HANDLES ITEMS & STRIPPING
    // assigns items to array
    strtok(temp2, "$");
    char *sep_at = strchr(temp2, '.');
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



    // HANDLES PRICE & STORE
    // assigns details to array
    char *sep_at2 = strchr(temp3, '$');
    strcpy(&details[index][0], (sep_at2));
    strcpy(temp3, details[index]);

    

    // separates price from store
    strtok(temp3, "at");

    strcpy(prices[index], temp3);




    // printf("NUM: %d ", nums[index]);
    // printf("%s\n", items[index]);
    // printf("DETAILS: %s\n", details[index]);
    printf("PRICE: %s\n", prices[index]);


    // printf("TEMP1: %s\n", temp1);
    // printf("TEMP2: %s\n", temp2);
    // printf("TEMP3: %s\n", temp3);

    index++;
  }
}


void print(){

  int i;
  for (i = 0; i < NUM_ITEMS; ++i){

    printf("%s\n", lines[i]);
  }
}

char *trim(char *str){

  int len = 0;
  char *frontp = str;
  char *endp = NULL;

  if( str == NULL ) { return NULL; }
  if( str[0] == '\0' ) { return str; }

  len = strlen(str);
  endp = str + len;

  /* Move the front and back pointers to address the first non-whitespace
    * characters from each end.
    */
  while( isspace((unsigned char) *frontp) ) { ++frontp; }

  if( endp != frontp ){

    while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
  }

  if( frontp != str && endp == frontp ){*str = '\0';}
          
  else if( str + len - 1 != endp ){*(endp + 1) = '\0';}
          

  /* Shift the string so that it starts at str so that if it's dynamically
    * allocated, we can still free it on the returned pointer.  Note the reuse
    * of endp to mean the front of the string buffer now.
    */
  endp = str;
  if( frontp != str ){
    
    while( *frontp ) { *endp++ = *frontp++; }
    *endp = '\0';
  }

  return str;
}