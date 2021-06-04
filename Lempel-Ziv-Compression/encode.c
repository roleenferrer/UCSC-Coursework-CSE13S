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
// Function for compressing a file
//
// infile   : a file stream to compress
// outfile  : the destination of the compressed file
// Psuedo-code provided in the lab document
//
void compress(int infile, int outfile) {
  TrieNode *root = trie_create();
  if (!root) {
    return;
  }

  TrieNode *curr_node = root;
  TrieNode *prev_node = NULL;
  uint8_t curr_sym = 0, prev_sym = 0;
  uint16_t next_code = START_CODE;
  while (read_sym(infile, &curr_sym) == true) {
    TrieNode *next_node = trie_step(curr_node, curr_sym);
    if (next_node != NULL) {
      prev_node = curr_node;
      curr_node = next_node;
    } else {
      buffer_pair(
          outfile, curr_node->code, curr_sym, (uint16_t)log2(next_code) + 1);
      curr_node->children[curr_sym] = trie_node_create(next_code);
      curr_node = root;
      next_code += 1;
    }
    if (next_code == MAX_CODE) {
      trie_reset(root);
      curr_node = root;
      next_code = START_CODE;
    }
    prev_sym = curr_sym;
  }
  if (curr_node != root) {
    buffer_pair(
        outfile, prev_node->code, prev_sym, (uint16_t)log2(next_code) + 1);
    next_code = (next_code + 1) % MAX_CODE;
  }
  buffer_pair(outfile, STOP_CODE, 0, (uint16_t)log2(next_code) + 1);
  flush_pairs(outfile);
  trie_delete(root);

  return;
}

int main(int argc, char **argv) {
  int opt = 0;
  bool display_stats = false; // Boolean value to print statistics

  int infile = STDIN_FILENO; // Default infile to stdin
  int outfile = STDOUT_FILENO; // Default outfile to stdout

  while ((opt = getopt(argc, argv, "vi:o:")) != -1) {
    switch (opt) {
    case 'v': // Display compression statistics
      display_stats = true;
      break;
    case 'i': // Specify input to compress
      close(infile);
      infile = open(optarg, O_RDONLY);
      break;
    case 'o': // Specify output of compressed input
      close(outfile);
      outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
      break;
    }
  }

  FileHeader header = { 0, 0 };
  header.magic = MAGIC; // Set header magic number to MAGIC

  struct stat header_protection; // Create stat struct for protection

  fstat(infile, &header_protection); // Get file status of infile
  header.protection = header_protection.st_mode; // Set protection to header
  fchmod(outfile, header.protection); // Change mode (protection) of outfile

  write_header(outfile, &header); // Write header to outfile

  compress(infile, outfile);

  if (display_stats == true) { // Print statistics if boolean value is true
    printf("Compressed file size: %lu bytes\n", total_syms);
    printf("Uncompressed file size: %lu bytes\n", total_bits);
    float float_total_syms = (float)total_syms;
    float float_total_bits = (float)total_bits;
    printf("Compression ratio: %.2f%%\n",
        100 * (1 - (float_total_syms / float_total_bits)));
  }

  // Close both file streams
  close(infile);
  close(outfile);

  return 0;
}
