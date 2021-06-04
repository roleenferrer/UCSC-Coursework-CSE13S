#include "io.h"
#include "stdio.h"

uint64_t total_syms;
uint64_t total_bits;
//
// Wrapper for the read() syscall.
// Loops to read the specified number of bytes, or until input is exhausted.
// Returns the number of bytes read.
//
// infile:  File descriptor of the input file to read from.
// buf:     Buffer to store read bytes into.
// to_read: Number of bytes to read.
// returns: Number of bytes read.
// Oly Lab Section 12/7 and Euguen Lab Section 12/9
//
int read_bytes(int infile, uint8_t *buf, int to_read) {
  // Declare variables to store readbytes and total bytes
  int rbytes = 0;
  int total = 0;

  do { // Set rbytes to number of bytes using write() and add to total
    rbytes = read(infile, buf + total, to_read - total);
    total += rbytes;
  } while (rbytes > 0); // Condition will run until rbytes < 0

  total_bits += total; // FOR STATISTICS, add total to extern variable
  return total;
}

//
// Wrapper for the write() syscall.
// Loops to write the specified number of bytes, or until nothing is written.
// Returns the number of bytes written.
//
// outfile:   File descriptor of the output file to write to.
// buf:       Buffer that stores the bytes to write out.
// to_write:  Number of bytes to write.
// returns:   Number of bytes written.
// Eugene Lab Section 12/9
//
int write_bytes(int outfile, uint8_t *buf, int to_write) {
  // Declare variables to store writebytes and total bytes
  int wbytes = 0;
  int total = 0;

  do { // Set wbytes to number of bytes using write() and add to total
    wbytes = write(outfile, buf + total, to_write - total);
    total += wbytes;
  } while (wbytes > 0); // Condition will run until wbytes < 0

  total_syms += total; // FOR STATISTICS, add total to extern variable
  return total;
}

//
// Reads in sizeof(FileHeader) bytes from the input file.
// These bytes are read into the supplied FileHeader, header.
//
// infile:  File descriptor of input file to read header from.
// header:  Pointer to memory where the bytes of the read header should go.
// returns: Void.
//
void read_header(int infile, FileHeader *header) {
  // Call read_bytes() to read bytes into FileHeader
  read_bytes(infile, (uint8_t *)header, sizeof(FileHeader));
  return;
}

//
// Writes sizeof(FileHeader) bytes to the output file.
// These bytes are from the supplied FileHeader, header.
//
// outfile: File descriptor of output file to write header to.
// header:  Pointer to the header to write out.
// returns: Void.
//
void write_header(int outfile, FileHeader *header) {
  // Call write_bytes() to write bytes into FileHeader
  write_bytes(outfile, (uint8_t *)header, sizeof(FileHeader));
  return;
}

//
// "Reads" a symbol from the input file.
// The "read" symbol is placed into the pointer to sym. (e.g. * sym = val )
// In reality, a block of symbols is read into a buffer.
// An index keeps track of the currently read symbol in the buffer.
// Once all symbols are processed, another block is read.
// If less than a block is read, the end of the buffer is updated.
// Returns true if there are symbols to be read, false otherwise.
//
// infile : File descriptor of input file to read symbols from .
// sym: Pointer to memory which stores the read symbol .
// returns : True if there are symbols to be read , false otherwise
// Eugene Lab Section 12/9
//
bool read_sym(int infile, uint8_t *sym) {
  static int end = 0; // Declare variable to signal end

  if (bytebuffindex == 0) { // Check if index is 0
    end = read_bytes(infile, bytebuff, 4096);
  }

  // Set sym to the current index of bytebuff
  *sym = bytebuff[bytebuffindex++];

  if (bytebuffindex == 4096) { // Check if index is 4096 (BLOCK)
    bytebuffindex = 0;
  }

  if (end == 4096) { // Return true if end is 4096 (BLOCK)
    return true;
  } else {
    if (bytebuffindex == end + 1) { // Return false if index is end + 1
      return false;
    } else {
      return true;
    }
  }
}

//
// Buffers a pair. A pair is comprised of a code and a symbol.
// The bits of the code are buffered first, starting from the LSB.
// The bits of the symbol are buffered next, also starting from the LSB.
// The code buffered has a bit-length of bitlen.
// The buffer is written out whenever it is filled.
//
// outfile: File descriptor of the output file to write to.
// code:    Code of the pair to buffer.
// sym:     Symbol of the pair to buffer.
// bitlen:  Number of bits of the code to buffer.
// returns: Void.
//
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {
  for (int i = 0; i < bitlen; i++) { // Iterate through code from 0 - bitlen
    if ((code & 1) == 1) { // if bit is 1 (set)
      // Set bit
      pairbuff[pairbuffindex / 8] |= (1 << (pairbuffindex) % 8);
    } else {
      // Clear bit
      pairbuff[pairbuffindex / 8] &= ~(1 << (pairbuffindex) % 8);
    }

    pairbuffindex += 1;
    code = code >> 1; // Shift code right by 1

    if (pairbuffindex == 4096 * 8) { // Check if index is BLOCK * 8
      write_bytes(outfile, pairbuff, 4096); // Write to outfile if full
      pairbuffindex = 0; // Reset index
    }
  }

  for (int i = 0; i < 8; i++) { // Iterate through sym from 0 - 8
    if ((sym & 1) == 1) { // if sym is 1 (set)
      // Set bit
      pairbuff[pairbuffindex / 8] |= (1 << (pairbuffindex) % 8);
    } else {
      // Clear bit
      pairbuff[pairbuffindex / 8] &= ~(1 << (pairbuffindex) % 8);
    }

    pairbuffindex += 1;
    sym = sym >> 1; // Shift sym right by 1

    if (pairbuffindex == 4096 * 8) { // Check if index is BLOCK * 8
      write_bytes(outfile, pairbuff, 4096); // Write to outfile if full
      pairbuffindex = 0; // Reset index
    }
  }
  return;
}

//
// Writes out any remaining pairs of symbols and codes to the output file.
//
// outfile: File descriptor of the output file to write to.
// returns: Void.
// Eugnene Lab Section 12/11
//
void flush_pairs(int outfile) {
  int bytes = 0; // Declare varaible to store to_write bytes
  if (pairbuffindex != 0) { // Conditional will convert index to correct byte
    if ((pairbuffindex % 8) == 0) {
      bytes = pairbuffindex / 8;
    } else {
      bytes = (pairbuffindex / 8) + 1;
    }
    write_bytes(outfile, pairbuff, bytes);
    pairbuffindex = 0;
  }
}

//
// "Reads" a pair (code and symbol) from the input file.
// The "read" code is placed in the pointer to code (e.g. *code = val)
// The "read" symbol is placed in the pointer to sym (e.g. *sym = val).
// In reality, a block of pairs is read into a buffer.
// An index keeps track of the current bit in the buffer.
// Once all bits have been processed, another block is read.
// The first bitlen bits are the code, starting from the LSB.
// The last 8 bits of the pair are the symbol, starting from the LSB.
// Returns true if there are pairs left to read in the buffer, else false.
// There are pairs left to read if the read code is not STOP_CODE.
//
// infile:  File descriptor of the input file to read from.
// code:    Pointer to memory which stores the read code.
// sym:     Pointer to memory which stores the read symbol.
// bitlen:  Length in bits of the code to read.
// returns: True if there are pairs left to read, false otherwise.
// Eugene Lab Section 12/9
//
bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {
  *code = 0; // Reset code to 0
  for (uint32_t i = 0; i < bitlen;
       i++) { // Iterate through code from i - bitlen
    if (pairbuffindex == 0) { // Check if index is 0 and call read_bytes()
      read_bytes(infile, pairbuff, 4096);
    }

    // Get the bit at the current pairbuff index
    if (pairbuff[pairbuffindex / 8] & (1 << (pairbuffindex % 8))) {
      // Set bit
      *code |= (1 << (i % 16));
    } else {
      // Clear bit
      *code &= ~(1 << (i % 16));
    }

    pairbuffindex += 1;

    if (pairbuffindex == 4096 * 8) { // Check if index is BLOCK * 8
      pairbuffindex = 0; // Reset index
    }
  }

  *sym = 0; // Reset sym to 0

  for (uint8_t i = 0; i < 8; i++) { // Iterate through code from i - 8
    if (pairbuffindex == 0) { // Check if index is 0 and call read_bytes()
      read_bytes(infile, pairbuff, 4096);
    }

    // Get the bit at the current pairbuff index
    if (pairbuff[pairbuffindex / 8] & (1 << (pairbuffindex % 8))) {
      // Set bit
      *sym |= (1 << (i % 8));
    } else {
      // Clear bit
      *sym &= ~(1 << (i % 8));
    }

    pairbuffindex += 1;

    if (pairbuffindex == 4096 * 8) { // Check if index is BLOCK * 8
      pairbuffindex = 0; // Reset index
    }
  }
  return *code != STOP_CODE; // Return boolean value
}

//
// Buffers a Word, or more specifically, the symbols of a Word.
// Each symbol of the Word is placed into a buffer.
// The buffer is written out when it is filled.
//
// outfile: File descriptor of the output file to write to.
// w:       Word to buffer.
// returns: Void.
// Euguene Lab Section 12/9
//
void buffer_word(int outfile, Word *w) {
  for (uint32_t i = 1; i < w->len + 1; i++) { // Iterate through 1 - w->len + 1

    // Set bytebuff at index to symbol of word at index i
    bytebuff[bytebuffindex] = w->syms[i];
    bytebuffindex += 1;

    if (bytebuffindex == 4096) { // Check if index is BLOCK
      write_bytes(outfile, bytebuff, 4096); // Call write_bytes() if full
      bytebuffindex = 0;
    }
  }
  return;
}

//
// Writes out any remaining symbols in the buffer.
//
// outfile: File descriptor of the outpute file to write to.
// returns: Void.
// Euguene Lab Section 12/9
void flush_words(int outfile) {
  if (bytebuffindex != 0) { // Check if index != 0
    // Write all bytes in bytebuff to outfile
    write_bytes(outfile, bytebuff, bytebuffindex);
  }
  return;
}
