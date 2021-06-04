## DESCRIPTION

In this lab assignment, the user will be able to compress and decompress files using Lempel-Ziv Compression. The program uses the Abstract Data Types **Tries** and **WordTables** in order to parse through data from files. The program also uses efficient **File I/O** in order to parse through certain files and compress/decompress their sizes. Compressing the data will reduce the number of bits that is needed to represent it, thus making it faster to transfer and also more storage efficient. The purpose of this lab is to do as follows:

- *encode* can compress any file, text, or binary
- *decode* can decompress any file, text, or binary, that was compressed with *encode*
- Both will use variable bit-length codes
- Both will perform read and writes in efficient blocks of 4KB

The user is able to input commands in the command prompt to achieve the following:

*encode* supports the following:

- **-v :** Display compression statistics
- **-i + input :** Specify input to compress (stdin by default)
- -**o + output :** Specify output of compressed input (stdout by default)

*decode* supports the following:

- **-v :** Display decompression statistics
- **-i + input :** Specify input to decompress (stdin by default)
- **-o + output :** Specify output of decompressed input (stdout by default)

## FILES

**encode.c**

This file contains main() for the encode program and the encode algorithm to compress a file

***decode.c***

This file contains main() for the decode program and the decode algorithm to decompress an encoded file

**trie.c**

This file contains the source code for the **Trie ADT**

***trie.h***

This file specifies the interface to trie.c

**word.c**

This file contains the source code for the **WordTable ADT**

***word.h***

This file specifies the interface to word.c

***io.c***

This file contains the source code for the **I/O module** used to manipulate files

***io.h***

This file specifies the interface to io.c

***code.h***

This header file contains macros for special codes

***DESIGN.pdf***

This file includes the implementation used to create the Abstract Data Types and main(). It also contains the design behind each function. 

## INSTRUCTIONS

**Compiling**

This program is intended to be compiled using the makefile associated with the assignment folder. Running make on the command will create both file executables *encode* and *decode*. Typing make encode or make decode will create the executable *encode* or *decode* respectfully.

**Execution**

Typing ./encode followed by commands specifying which file to compress (infile) and a target output (outfile) will compress the infile and output the outfile. If no command was specified, it will default to stdin and stdout respectfully.

Typing ./decode followed by commands specifying which file to decompress (infile) and a target output (outfile) will decompress the infile and output the outfile. If not command was specified, it will default to stdin and stdout respectfully.

**Known Issues**

- ~~NULL Dereference errors in Trie and WordTable ADT's~~
- ~~Memory leak when creating a WordTabl~~



