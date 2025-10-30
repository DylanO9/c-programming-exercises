/*
    Purpose: Write a routine bfree(p, n) that will free any arbitrary block p of n characters into the free list maintained by malloc and free. By using bfree, a user can add a static or external array to the free list at any time
*/

static Header base; /* empty list to get started */
static Header *freep = NULL; /* start of free list */

void bfree(void *p, unsigned n) {
    Header *hp; // This is where we will store the casted p
    
    if (n < sizeof(Header)) // Can't use this memory because we don't have enough to be looked at by our free
        return;
    hp = (Header *) p;
    hp->s.size = n / sizeof(Header);
    
    free((void *)(hp + 1)); 
}
