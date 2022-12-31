#include "termsearch.c"
#include <stdio.h>

int main()
{
    const char
        *bucket = "0123456789ABCDEF", 
        *query = "ABC";
    char
        *location;
    
    location = (char *)termsearch((unsigned char *)bucket, 
        (unsigned char *)query, 16, 3);

    printf("%s\n", location);
}
