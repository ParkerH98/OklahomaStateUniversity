#include <stdio.h>
#include <string.h>

int main() {

    FILE *fp;
    char buff[255];
    fp = fopen("inputTxtFiles/Name.txt", "r");

    
    while (fgets(buff, sizeof(buff), fp)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        // printf("%s", buff);
        char * token = strtok(buff, "\t");
        printf("%s\n", token);
        char * token1 = strtok(NULL, "");
        printf("%s\n", token1);
    }
    
    fclose(fp);

    return 0;
}
