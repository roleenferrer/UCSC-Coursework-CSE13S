## DESCRIPTION

In this lab assignment, the user will be able to input commands to modify the creation of several Abstract Data Types: A Bloom Filter, a Hash Table, and a Linked List. These different ADT's will help translate words that were taking through I/O redirection using a regular expression to "HatterSpeak". There are three scenarios given a stream of words: 

1. **Guilty of NonTalk**

   A person guilty of NonTalk only used OldSpeak words with no HatterSpeak translations. A 

   person guilty of NonTalk will be sent to the dungeon.

2. **HatterSpeak Translation**

   A person who uses OldSpeak words but has a HatterSpeak translation will not receive a 

   harsher punishment than someone guilty of NonTalk. The person will then be told of their 

   errors by translation to HatterSpeak.

3. **Both OldSpeak and HatterSpeak**

   A person who uses OldSpeak words with no translations and words with translations will be 

   guilty of both. The person will be told of their OldSpeak errors and proper HatterSpeak 

   translations for OldSpeak words. 

The user is able to input commands in the command prompt to achieve the following:

1. **-s** will print statistics of each ADT instead of a message at the end of the parse through. These statistics include:

   Seeks: Number of seeks performed

   Average Seek Length: The links searched / total seeks

   Averaged Linked List Length: The average length of non-zero linked lists in the hash table

   Hash Table Load: The percentage of loading for the hash table

   Bloom Filter Load: The percentage of loading for the bloom filter

2. **-h** will specify the hash table size of entries (default is 10000)

3. **-f** will specify the bloom filter size of entries (default is 2^20)

4. -**m** will use the move-to-front rule (for Linked Lists)

5. **-b** will not use the move-to-front rule (for Linked Lists)

## FILES

***hatterspeak.c***

This file contains main(), which takes in commands from the user using getopt(), creates ADT's using other source files, parses through a stream of words through I/O redirection, and frees memory that was used by the ADT's

***hash.c***

This file contains the source code for the Hash Table ADT

***hash.h***

This file specifies the interface to hash.c

***ll.c***

This file contains the source code for the Linked List ADT

***ll.h***

This file specifies the interface to ll.c

***bf.f***

This file contains the source code for the Bloom Filter ADT

***bf.h***

This file specifies the interface to bf.c

***bv.c***

This file contains the source code for the Bit Vector ADT

***bv.h***

This file specifies the interface to bv.c

***parser.c***

This file contains the source code to parse through a stream of words using I/O redirection

***parser.h***

This file specifies the interface to parser.c

***speck.c***

This file contains the source code for the hash function using the SPECK cipher

***speck.h***

This file specifies the interface to speck.c

***Makefile***

This file includes instructions when building, compiling, and running the source code using make

***DESIGN.pdf***

This file includes the description of the implementation used to create the Abstract Data Types. It also contains the design behind each function

***WRITEUP.pdf***

This file contains the lab write-up after post-lab analysis. It includes topics such as the effects of a varying size of the Hash Table, Bloom Filter, and the effectiveness of the move-to-front rule

## INSTRUCTIONS

**Compiling**

This program is intended to be compiled using the makefile associated with the assignment folder. Running make on the command prompt will create a file executable *hatterspeak*.

**Execution**

Typing ./hatterspeak followed by any other commands (see Description) will then direct the user in inputting a stream of words to be check for HatterSpeak translation. In order to end this I/O redirection, hit CTRL + D to stop the program and display either a message or statistics if the (-s) command is raised.

**Known Issues**

- ~~NULL dereference error in hs_create function in hatterspeak.c is causing a make infer error.~~
- ~~Memory leak when using ht_create.~~
- If the user inputs a size of 0 for either Hash Table or Bloom Filter, the program closes.
  - No ADT is created



