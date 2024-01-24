# Bug 1

## A) How is your program acting differently than you expect it to?
- In the InsertContent function, when word_start is initialized to content, it fails to correctly parse the content and identify word boundaries. This results in incorrect word boundaries and potentially a segmentation fault.

## B) Brainstorm a few possible causes of the bug
- The word_start pointer is initialized to content, meaning it never changes, preventing the correct identification of word boundaries.
- All characters are treated as part of a single word, and the code may not identify word boundaries correctly.
- The if (isalpha(*cur_ptr)) condition may not work as intended because word_start is never updated.

## C) How you fixed the bug and why the fix was necessary
- I ensure that word_start is updated when the code detects the start of a word. As it stands, the initialization of word_start to content causes the code to treat the entire content as a single word, which is not the intended behavior. To resolve this issue, I assign the value of word_start to NULL update it when a word is encountered.

# Bug 2

## A) How is your program acting differently than you expect it to?
In the MemIndex_Search function, when handling the first query word (index 0), it fails to allocate memory for a SearchResult and append it to ret_list. As a result, the search results for the first query word are not being added to the result list.

## B) Brainstorm a few possible causes of the bug
- Memory allocation for SearchResult structure might fail.
- The code for appending SearchResult to ret_list might not be executed.

## C) How you fixed the bug and why the fix was necessary
- I add a check for successful memory allocation and handle the case where memory allocation fails. If malloc fails to allocate memory for a SearchResult, you should free any previously allocated resources and return an appropriate error code or value. Additionally, make sure that the code for appending the SearchResult to ret_list is correctly executed when the allocation is successful.


# Bug 3

## A) How is your program acting differently than you expect it to?
- In the ReadFileToString function, there is a bug related to how the code handles reading from the file. The code does not correctly handle situations where read returns fewer bytes than requested. This can result in incorrect data being read into the buffer and an incorrect value of the left_to_read variable.

## B) Brainstorm a few possible causes of the bug
- The code does not correctly update the left_to_read variable inside the loop. 
- It only checks if read returns -1 or 0 and doesn't account for cases where read returns a value less than left_to_read.

## C) How you fixed the bug and why the fix was necessary
- I fixed the issue by checking left_to_read variable is correctly decremented based on the number of bytes read by the read system call. This will ensure that the loop continues until the entire file is read, even if read returns fewer bytes than expected.
