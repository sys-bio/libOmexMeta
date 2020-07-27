Incrementing Version
=====================

I've put a mechanism in place so that the only place you
ever need to touch, with regards to incrementing the
version is at the top of the top level cmake file.
CMake will write this to a file and Python will read the file.
Please stick to this strategy of only ever updating the
version inside the cmake script. 

