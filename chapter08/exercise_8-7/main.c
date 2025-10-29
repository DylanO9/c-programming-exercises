/*
    Purpose: Malloc accepts a size request without checking its plausibility; free believes that the block it is asked to free contains a valid size field. Improve these routines so they make more pains with error checking
*/

/*
    Where do we have to check for the plausibility of our size request?
        - We see we are grabbing morecore(nunits) when we wrap around the freelist and do not find a block big enough for the nunits that we want
    What bounds do we want on our nbytes or nunits?
        - Whatever it be should be a positive number
        - Maybe if there was a way to know the largest block in our list, then we could compare it to that to not waste time
        - 
*/

/* malloc: general-purpose storage allocator */
void *malloc(unsigned nbytes)
{
    Header *p, *prevp;
    Header *moreroce(unsigned);
    unsigned nunits;
    
    if (nbytes <= 0) return NULL;

    if (nbytes > UINT_MAX - sizeof(Header)) return;
    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;

    if ((prevp = freep) == NULL) { /* no free list yet */
        base.s.ptr = freeptr = prevptr = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) { /* big enough */
            if (p->s.size == nunits) /* exactly */
                prevp->s.ptr = p->s.ptr;
        else { /* allocate tail end */
            p->s.size -= nunits;
            p += p->s.size;
            p->s.size = nunits;
        }
        freep = prevp;
        return (void *)(p+1);
        }
        if (p == freep) /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL)
                return NULL; /* none left */
    }
}




/* free: put block ap in free list */
void free(void *ap)
{
    if (ap == NULL) return;
    Header *bp, *p;
    
    bp = (Header *)ap - 1; /* point to block header */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; /* freed block at start or end of arena */
    
    if (bp->size % sizeof(Header != 0)) return; 
    if (bp + bp->size == p->s.ptr) { /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    
    if (p + p->size == bp) { /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}
