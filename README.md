# blob
simple manipulation of raw memory

This was a cute little project testing type-driven manipulation of data at the byte level using C++11.  The main reason this was created was to really test my (somewhat intermediate, at the time) understanding of what was going on at a very low level in memory.  The Blob class template represents a block of raw data which can be read from or written to simply by specifying the position to read from / write to as well as the type of data being manipulated.

I developed a greater appreciation for pointers, pointer arithmetic, and references, as well as how to freely - and admittedly, unsafely - convert between pointer and reference types.  Thankfully, the unsafe operations are done somewhat safely behind the guise of the Blob class.

The main thing I learned is that memory management is something best left to the compiler to figure out.  Doing this sort of thing by hand is an easy way to end up with corrupt data or unexpected program crashes should you try to read or write invalid data.  It was a success in that it does exactly what I wanted it to do, but what I wanted it to do was nothing more than a fun exercise.
