#include "code.h"
#include "io.h"
#include "trie.h"
#include "word.h"
#include <fcntl.h>
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

//
// Function for decompressing a file
//
// infile   : a file stream to decompress
// outfile  : the destination of the decompressed file
// Psuedo-code provided in the lab document
//
void decompress(int infile, int outfile) {
  WordTable *table = wt_create();
  if (!table) {
    return;
  }

  uint8_t curr_sym = 0;
  uint16_t curr_code = 0;
  uint16_t next_code = START_CODE;
  while (read_pair(infile, &curr_code, &curr_sym, (uint16_t)log2(next_code) + 1)
         == true) {
    table[next_code] = word_append_sym(table[curr_code], curr_sym);
    buffer_word(outfile, table[next_code]);
    next_code += 1;
    if (next_code == MAX_CODE) {
      wt_reset(table);
      next_code = START_CODE;
    }
  }
  flush_words(outfile);
  for (uint32_t i = 0; i < MAX_CODE; i++) {
    if (table[i] != NULL) {
      word_delete(table[i]);
    }
  }
  free(table);
  return;
}

int main(int argc, char **argv) {
  int opt = 0;
  bool display_stats = false; // Boolean value to print statistics

  int infile = STDIN_FILENO; // Default infile to stdin
  int outfile = STDOUT_FILENO; // Default outfile to stdout

  while ((opt = getopt(argc, argv, "vi:o:")) != -1) {
    switch (opt) {
    case 'v': // Display decompression statistics
      display_stats = true;
      break;
    case 'i': // Specify input to decompress
      close(infile);
      infile = open(optarg, O_RDONLY);
      break;
    case 'o': // Specify output of decompressed input
      close(outfile);
      outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
      break;
    }
  }

  FileHeader header = { 0, 0 };
  read_header(infile, &header); // Read header from infile

  if (header.magic != MAGIC) { // Stop program if protection isn't magic number
    printf("ERROR!\n"); // Error message
    return 0;
  }

  fchmod(outfile, header.protection); // Change mode (protection) of outfile

  decompress(infile, outfile);

  if (display_stats == true) { // Print statistics if boolean value is true
    printf("Compressed file size: %lu bytes\n", total_bits);
    printf("Uncompressed file size: %lu bytes\n", total_syms);
    float float_total_syms = (float)total_syms;
    float float_total_bits = (float)total_bits;
    printf("Compression ratio: %.2f%%\n",
        100 * (1 - (float_total_bits / float_total_syms)));
  }

  // Close both file streams
  close(infile);
  close(outfile);

  return 0;
}
