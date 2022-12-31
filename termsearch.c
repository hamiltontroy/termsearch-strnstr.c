//termsearch

unsigned char *termsearch(unsigned char *bucket, unsigned char *term, 
    const long bucketlen, const long termlen);

/*
    termsearch() will search for a sequence of bytes "term",
    which resides within a larger sequence of bytes "bucket",
    and will search only "bucketlen" number of bytes within bucket,
    for a term that is "termlen" number of bytes.
    
    on success returns a pointer to term.
    on failure returns NULL.
    
    Time complexity:
        Typical: O(n)
        Worst Case: O(n^2)
*/

#include <stddef.h> // <cstddef> // used for NULL and nothing else

unsigned char *termsearch(unsigned char *bucket, unsigned char *term, const long bucketlen, const long termlen)
{
    if(termlen > bucketlen) // prevents a waste of time
        return NULL;
    if(term < bucket)       // prevents an out of bounds search
        return NULL;
    
    unsigned char
        *termstart = NULL;
    long
        i = 0, j;
    
    RESTART:
    
    // stops when the start of term is found
    for(; i < bucketlen - termlen; i++)
    {
        if(bucket[i] == term[0])
        {
            termstart = &bucket[i];
            break;
        }
    }
    
    // prevents an out of bounds search,
    // also returns NULL if term not found
    if(i >= bucketlen - termlen)
        return NULL;
    
    // continues to iterate the bucket until the entire length of term is found
    for(j = 0; j < termlen; j++)
    {
        if(termstart[j] != term[j])
            goto RESTART;
        
        if(j == termlen)
            break;
    }
    
    return termstart;
}

/* NOTES TO FUTURE READERS:
    The above algorithm can be sped up in the following ways:
    
    Instead of searching and comparing 8 bits at a time,
    it can be modified to search either 32 bytes or 64 bytes at a time
    based on what architecture the system is.
    
    The reason why it does not implement that is:
    1. Currently it will only be used on byte buffers.
    
    Look into making:
    termsearch64 used on buffers where bucket and term can be divisible by 8 bytes
    termsearch32 used on buffers where bucket and term can be divisible by 4 bytes
    termsearch16 used on buffers where bucket and term can be divisible by 2 bytes
*/
