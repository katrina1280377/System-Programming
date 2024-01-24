# Bug 1

## A) How is your program acting differently than you expect it to?
The program is returning an incorrect header value for "connection" in htreq3 of test_httpconnection.cc. Instead of "keep-alive," it is returning "s."

## B) Brainstorm a few possible causes of the bug
- Reading random values from WrappedRead, indicating a potential issue with its setup.
- Concatenating strings using "+=" might introduce unwanted random values.
- Incorrect calculation of bytes to remove from buffer_ after parsing the top request, leading to residual data from the previous request.

## C) How you fixed the bug and why the fix was necessary
- Addressed the bug by setting the precise number of bytes from buf to append to buffer_. Previously, this omission caused random values from buf outside allocated elements to be appended.


# Bug 2

## A) How is your program acting differently than you expect it to?
- Attempting to obtain static files using telnet by manually writing a GET request results in nothing being displayed on the command line.

## B) Brainstorm a few possible causes of the bug
- Flawed implementation of the ProcessFileRequest function in HttpServer.cc.
- Incorrectly closing the client file descriptor when the "connection" header value is "close."
- Potentially incorrect ordering of if statements in HttpServer_ThrFn, with the request processing occurring after checking the "connection" header.

## C) How you fixed the bug and why the fix was necessary
- Resolved the bug by adjusting the ordering of if statements in HttpServer_ThrFn to process the request before checking the "connection" header. This change resulted in the correct display of static files on the command line.


# Bug 3

## A) How is your program acting differently than you expect it to?
- Unable to obtain the correct return value from calling IsPathSafe in the ProcessFileRequest function of HttpServer. Even with a file within the root directory, the return value of IsPathSafe is false.

## B) Brainstorm a few possible causes of the bug
- Failure to append base_dir to file_name for IsPathSafe to determine if the file is within the base directory.
- Need for an additional check in the IsPathSafe function of HttpUtil.cc beyond the comparison of root_dir and test_file paths.
- Possible parsing error in file_name, leading to an incorrect format passed to IsPathSafe.

## C) How you fixed the bug and why the fix was necessary
- Corrected the bug by appending base_dir to file_name, enabling the logic in IsPathSafe to accurately determine if the file_name contains the root directory path, resulting in the correct return values.
