#include "header.h"
#define NUM_ITEMS 100

char lines[NUM_ITEMS][256];
 
void readFile(){

    FILE *f;
    f = fopen("items.txt", "r");

    // for storing each line of items.txt 
    
    int nums[NUM_ITEMS];
    char items[NUM_ITEMS][256];
    char details[NUM_ITEMS][256];
    char prices[NUM_ITEMS][256];
    char locations[NUM_ITEMS][256];

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

        // assigns items to array
        strtok(temp2, "$");
        char *sep_at = strchr(temp2, '.');
        strcpy(&items[index][0], (sep_at + 1));

        // assigns details to array
        char *sep_at2 = strchr(temp3, '$');
        strcpy(&details[index][0], (sep_at2 + 1));

        // printf("NUM: %d ", nums[index]);
        // printf("ITEM: %s\n", items[index]);
        // printf("DETAILS: %s\n", details[index]);

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

char * trimwhitespace(char *str){
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}