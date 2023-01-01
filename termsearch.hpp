template <typename T, typename N>
const T *termsearch(const T bucket[], const T term[], const N bucketlen, const N termlen)
{
    if(termlen > bucketlen) // prevents a waste of time
        return nullptr;
    
    // if searching for the first occurence of a specific character
    if(termlen == 1)
    {
        for(int k = 0; k < bucketlen; k++)
        {
            if(bucket[k] == term[0])
                return &bucket[k];
        }
    }
    
    const T *termstart = nullptr;
    N i = 0, j;
    
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
    // also returns nullptr if term not found
    if(i >= bucketlen - termlen)
        return nullptr;
    
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
