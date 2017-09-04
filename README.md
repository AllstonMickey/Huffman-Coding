###### Author: Allston Mickey

## Files:
* bv.h
* code.h
* decode.c
* encode.c
* heap.h
* huffman.c, huffman.h
* queue.c, queue.h
* stack.c, stack.h
* Makefile

## How to compile & run:
Command | Description
--- | ---
make | Compiles the encode and decode programs. 
make all | Compiles the encode and decode programs. 
make encode | Compiles the encode program.
make decode | Compiles the decode program.
make clean | Remove the object files and encode/decode programs
./encode [flags] | Run the encode program.
./decode [flags] | Run the decode program.

## Flags:
Argument(s) | Description | Coding Type
--- | --- | ---
-i [path] | Full path to the input file | Both **_[REQUIRED]_**
-o [path] | Full path to the output file | Both
-A | Sets all flags (-vp, -ch if available) | Both
-v | Enable verbose mode - prints statistics about the program | Both
-p | Prints the Huffman Tree | Both
-c | Prints the codes/bit paths to each leaf in the Huffman Tree | Encoding
-h | (./encode only) Prints the histogram of bytes | Encoding

## Description:
These programs encode/decode any file by using the greedy Huffman Algorithm.
#### [encoding]
1. Construct a histogram of the bytes in a file.
2. Enqueue each histogram entry as a node in the Huffman Tree.
3. Repeatedly dequeue 2X and enqueue until the root of the tree is remaining.
4. Load the codes for each leaf by a post-order traversal of the tree, assigning a 0 when traversing left and a 1 when traversing right.  Store the codes in a bit vector for maximum efficiency.
5. Write the tree and the paths to each leaf to an encoded output file.

#### [decode]
1. Read the encoded file.
2. Reconstruct the Huffman Tree with a stack.
3. For each byte in the original, uncompressed file, look up its code and step through the tree.
4. Write the bytes back to a decoded output file.
---
* Using both programs, any file can be encoded and then decoded back to an exact copy of the original.
* Note that the default permissions to a file are 0744 (-rwxr--r--).
  You may change these on your own if they do not suit what you intended.
