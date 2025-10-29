/*  
    Purpose: The standard library function calloc(n, size) return s apointer to n objects of size size, with storage initialized to zero. Write calloc, by calling malloc or by modifying it
*/

/*
    How are we going to store these in one array?
    - Use an array of pointers since each time you call malloc you get a pointer to the free memory space
    - Since we don't know what the type is that the user wants we just return void * array
*/

void *calloc(int n, int size) {
    if (size != 0 && n > SIZE_MAX / size) // Check for overflow
        return NULL;    
    size_t total = n * size;
    void *p = malloc(total);
    if (p != NULL)
        memset(p, 0, total);
    return p;
}
