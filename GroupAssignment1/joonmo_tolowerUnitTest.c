#include <stdio.h>
#include <ctype.h>

int main () {
   int i = 0;
   char c;
   char str[] = "JOONMO KOO";
   
   while(str[i]) {
      // putchar (toupper(str[i]));
      str[i] = tolower(str[i]);
      i++;
   }
   printf("%s",str);

   
   return(0);
}