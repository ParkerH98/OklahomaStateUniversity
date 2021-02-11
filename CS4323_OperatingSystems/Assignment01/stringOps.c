


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

void removeFirst(char * str, const char toRemove){

  int i = 0;
  int len = strlen(str);

  /* Run loop till the first occurrence of the character is not found */
  while(i<len && str[i]!=toRemove)
      i++;

  /* Shift all characters right to the position found above, to one place left */
  while(i < len)
  {
      str[i] = str[i+1];
      i++;
  }
}