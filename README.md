# WillRio
My implementation of the CS:APP RIO library. 
Credit to Computer Systems: A Programmer's Perspective, 2nd Edition, by Bryant and O'Hallaron.

## About
This library is part of my networking knowledge journey. 
It makes handling *short reads* (reading in fewer bytes than expected), a common occurance in network programming, easy.

### How it works
In short, data is read into a buffer until the requested amount of data is read.
These functions may repeatedly perform blocking I/O calls, conveniently preventing unacceptable short reads.

Te rio_t type also enables several functions, such as rio_readlineb and rio_readnb, to maintain their own internal buffers of read content,
allowing you to repeatedly "read" a small quantity of bytes without performing expensive system calls.

## Requirements
Gcc is just about it!

## Usage
include the compiled object file (visible in out dir) and header file in your project.
