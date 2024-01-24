# Bug 1

## A) How is your program acting differently than you expect it to?
- My Slice and Linked List Pop function meet the testing issue of malloc(): unaligned tcache chunk detected.

## B) Brainstorm a few possible causes of the bug
- Probably I put free(list); when there is only one element removed from the link list.
- Freeing the entire list would result in freeing the list itself along with its metadata.
- The list becomes unusable and potentially causes memory corruption.

## C) How you fixed the bug and why the fix was necessary
- After removing the free(list); line in this case, I am only freeing the node and updating the list's head and tail pointers correctly.


# Bug 2

## A) How is your program acting differently than you expect it to?
- My program encountered the issue when running Test_LinkedList.TestLLIteratorBasic, there is an error message about the unexpected equality of these values message:
  __null
  Which is: NULL
  llp->head
## B) Brainstorm a few possible causes of the bug
- From the error message, it looks like there is an incorrect iterator of the head.
- Check the remove function in removing head & only one element cases.

## C) How you fixed the bug and why the fix was necessary
- After adding iter->list->head = iter->list->tail = NULL; in only one element case in LLIterator_Remove, because the only node has been removed, it is necessary to assign the null value to head and tail in the link list.


# Bug 3

## A) How is your program acting differently than you expect it to?
- I encountered a memory leak issue in function: HashTable_Find when running valgrind.

## B) Brainstorm a few possible causes of the bug
- Check every functions to see if there is any memory need to be released.
- Because it dynamically allocates memory for the iterator structure. I need to check the every iterators are been released.

## C) How you fixed the bug and why the fix was necessary
- LLIterator need to be free before return to release the memory allocated for the iterator when you are done using it.
