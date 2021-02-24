
/*
---------------------------------------------------------
Takes an input string and trims the whitespace off of the
front and end.

Params: pointer to string to trim
Return: returns pointer to trimmed string
*/
char * trim(char *string){

  int length = 0;
  char *frontPointer = string; // ptr to the front of the string
  char *endPointer = NULL; // initializes the end pointer

  if( string == NULL ) { return NULL; }
  if( string[0] == '\0' ) { return string; } // got to the end of the string

  length = strlen(string); // length equals the length of the string
  endPointer = string + length;
    
  while( isspace((unsigned char) *frontPointer) ) { ++frontPointer; } // Move the front and back pointers to address the first non-whitespace characters from each end.

  if( endPointer != frontPointer ) // loop while a space exists
  {
    while( isspace((unsigned char) *(--endPointer)) && endPointer != frontPointer ) {}
  }

  if( frontPointer != string && endPointer == frontPointer ){*string = '\0';} // handle if empty
          
  else if( string + length - 1 != endPointer ){*(endPointer + 1) = '\0';} // handle the ending white space

  endPointer = string; // shifts the string so it starts at the string 
  if( frontPointer != string )
  {
    while( *frontPointer ) { *endPointer++ = *frontPointer++; } // moves the pointer until end is detected
    *endPointer = '\0';
  }
  return string;
}


/*
---------------------------------------------------------
Removes the first occurrence of a specified character

Params: pointer to string to manipulate and the char to remove
Return: void
*/
void removeFirst(char * string, const char toRemove){

  int i = 0;
  int length = strlen(string);

  /* Run loop till the first occurrence of the character is not found */
  while(i<length && string[i]!=toRemove)
    i++;

  /* Shift all characters right to the position found above, to one place left */
  while(i < length)
  {
    string[i] = string[i+1];
    i++;
  }
}