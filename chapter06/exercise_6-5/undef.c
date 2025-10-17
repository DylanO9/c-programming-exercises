/*
    Purpose: Write a function undef that will remove a name and definition from the table maintained by loopup and install
*/

// What's the method we will use?
// Check if the name/definition pair is inside of the table using lookup()
    // We found the block inside of the lookup table
        // Remove the block
        // Cases to watch out for
            // First node in the linked_list
            // Middle node
            // Last node
    // If it's not return 1 for a bad 


/* 
    What information do we need to pass to it?
        - Name we want to remove
        - Def we want to remove
    Why don't we need to pass the hashtab?
        - Global information
    Why can't we use the lookup function in our solution?
        - Well we want to get rid of the node
        - However, because of the different cases of where the node can be, we will need the previous node sometimes/all the time
    Why don't we add a check for replacement?
        - Well if the person wants to undefine something, then they want to do it regardeless of what the replacement text is assumingly
*/
int undef(char *name) {
    struct nlist *node = NULL;
    struct nlist *prev = NULL;
    if (lookup(name) != NULL) {
        for (prev, node = hashtab[hash(name)]; node != NULL; prev = node, node = node->next) {
            if (strcmp(node->name, name) == 0) {
                if (prev == NULL) {
                    hashtab[hash(name)] = node->next;
                } else {
                    prev->next = node->next;
                }
                free(node->name);
                free(node->defn);
                free(node);
            }
        }
    }
    else {
        printf("We could not find any block with the name %s\n", name);
        return 1;
    }

}
