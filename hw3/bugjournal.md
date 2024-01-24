# Bug 1

## A) How is your program acting differently than you expect it to?
- The issue involves obtaining an incorrect header value for "connection" in htreq3 within test_httpconnection.cc. Instead of the expected "keep-alive," the received value is "s."

## B) Brainstorm a few possible causes of the bug
- The program appears to read random values from WrappedRead, indicating a possible issue with the setup for WrappedRead.
- Concatenating strings using "+=" might introduce unintended random values during the process.
- The removal of bytes from buffer_ after parsing the top request may be incorrect, leading to the combination of residual data from the previous request with the next one.

## C) How you fixed the bug and why the fix was necessary
- I addressed the bug by specifying the number of bytes from buf to append to buffer_. Previously, this was not set, causing random values in buf outside the allocated elements to be appended to buffer_. The fix ensures a controlled and accurate appending process, preventing the inclusion of unwanted data in buffer_.


# Bug 2

## A) How is your program acting differently than you expect it to?
- When attempting to retrieve static files using telnet by manually crafting a GET request, no information is displayed on the command line as expected.

## B) Brainstorm a few possible causes of the bug
- There might be an issue with the implementation of the ProcessFileRequest function in HttpServer.cc, which is responsible for returning static files.
- Closing the client file descriptor when the "connection" header value is "close" could be unnecessary and affecting the expected output.
- The order of if statements in HttpServer_ThrFn might be incorrect. It could be beneficial to process the request before checking if the "connection" header value is "close."

## C) How you fixed the bug and why the fix was necessary
- To address the bug, I rearranged the if statements in HttpServer_ThrFn so that the request is processed before checking if the "connection" header value is "close." This adjustment led to the successful display of static files on the command line. The fix ensures that the processing order aligns with the intended logic, allowing for the proper handling of requests and avoiding premature closure of the client file descriptor, ultimately resolving the issue.


# Bug 3

## A) How is your program acting differently than you expect it to?
- The issue revolves around obtaining an incorrect return value when calling IsPathSafe in the ProcessFileRequest function of HttpServer. Even with a file located within the root directory, the return value of IsPathSafe remains false.

## B) Brainstorm a few possible causes of the bug
- It is possible that appending base_dir to file_name in the ProcessFileRequest function is necessary for IsPathSafe to accurately determine whether the file_name is within the base_dir.
- Another potential cause could be the need for an additional check in the IsPathSafe function of HttpUtil.cc, beyond verifying the length and containment of paths, to ensure accurate results.
- The bug might also stem from incorrect parsing of file_name, leading to the submission of an improperly formatted file_name to IsPathSafe.

## C) How you fixed the bug and why the fix was necessary
- To address the bug, I appended base_dir to file_name. This adjustment allowed the logic implemented in IsPathSafe to correctly assess whether the file_name contains the root directory path, resulting in accurate return values. The fix ensures that IsPathSafe receives the necessary information to make a precise determination regarding the safety of the file path
