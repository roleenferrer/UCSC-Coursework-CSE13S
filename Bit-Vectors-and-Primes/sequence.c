#include "bv.h"
#include "sieve.h"
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// LucasNumbersCheck Helper Function
// This function will check if the prime number is a Lucas number.
//
// Parameters:
// prime_number - a prime number to be compared
bool lucasNumbersCheck(double prime_number) {
  double first = 2, second = 1, next;
  for (double n = 0; n <= 42; n++) { // n <= 42 which is less than uint32_t
    if (prime_number == first) {
      return true;
    }
    next = first + second;
    first = second;
    second = next;
  }
  return false;
}

// fibNumbersCheck Helper Function
// This function will check if the prime number is a Fibonacci number.
//
// Parameters:
// prime_number - a prime nubmer to be compared
bool fibNumbersCheck(double prime_number) {
  double first = 0, second = 1, next;
  for (double n = 0; n <= 47; n++) { // n <= 47 which is less than unint32_t
    if (prime_number == first) {
      return true;
    }
    next = first + second;
    first = second;
    second = next;
  }
  return false;
}

// mersenneNumbersCheck Helper Function
// This funciton will check if the prime nubmer is a Mersenne number.
//
// Parameters:
// prime_number - a prime number to be compared
bool mersenneNumbersCheck(double prime_number) {
  for (double n = 0; n <= 32; n++) { // n <= 32 which is less than unint32_t
    double mersenne_number = pow(2, n) - 1;
    if (prime_number == mersenne_number) {
      return true;
    }
  }
  return false;
}

// printPrimes
// This function will print the primes from the Bit Vector, which was
// passed a the Sieve of Erastothenes
//
// Parameters:
// BitVector *primes - a Bit Vector
// numbers - The amount of numbers for the Bit Vector to parse through
void printPrimes(struct BitVector *primes, uint32_t numbers) {
  for (uint32_t i = 0; i <= numbers; i++) {
    if (bv_get_bit(primes, i) == 0) { // if bit is cleared, continue
      continue;
    }
    printf("%d: prime", i); // print the prime number

    bool is_mer_number = mersenneNumbersCheck(i);
    if (is_mer_number == true) { // check if prime number is Mersenne
      printf(", mersenne");
    }
    bool is_lucas_number = lucasNumbersCheck(i);
    if (is_lucas_number == true) { // check if prime number is Lucas
      printf(", lucas");
    }
    bool is_fib_number = fibNumbersCheck(i);
    if (is_fib_number == true) { // check if prime number is Fibonacci
      printf(", fibonacci");
    }
    printf("\n");
  }
  return;
}

// isPalindrome Helper Function
// This function will check if the given array is a palindrome.
//
// Parameters:
// *array - An array of of the translated prime number to some base
// top_of_array - The top of the array, or highest index
bool isPalindrome(uint8_t *array, int top_of_array) {
  for (uint8_t i = 0; i <= (top_of_array / 2); i += 1) {
    if (array[i] != array[((top_of_array - 1) - i)]) {
      // check if current index is equal to the opposite index
      return false;
    }
  }
  return true;
}

// base2 Function
// This function will convert each prime number to base 2 and check
// if it is a palindome at base 2.
//
// Parameters:
// *primes - A Bit Vector that has been run through a sieve
// numbers - The amount of numbers for the Bit Vector to parse through
void base2(struct BitVector *primes, uint32_t numbers) {
  printf("Base   2\n");
  printf("----  --\n");

  for (uint32_t i = 0; i <= numbers; i++) {
    if (bv_get_bit(primes, i) == 0) {
      continue;
    }

    uint8_t array[32]; // allocate 32 bits, which is equal to uint32_t

    uint32_t prime = i;
    int index = 0;
    while (prime > 0) { // run loop until quotient (prime) is < 0
      array[index] = prime % 2; // set current index of array to remainder
      prime = prime / 2; // set prime to quotient
      index += 1; // increment index by 1
    }
    bool is_palindrome = isPalindrome(array, index);
    if (is_palindrome) { // Check if array is a palindrome and print
      printf("%d = ", i);
      for (int x = 0; x < index; x++) {
        printf("%d", array[x]);
      }
      printf("\n");
    }
  }
  printf("\n");
  return;
}

// base9 Function
// This function will convert each prime number to base 9 and check
// if it is a palindome at base 9.
//
// Parameters:
// *primes - A Bit Vector that has been run through a sieve
// numbers - The amount of numbers for the Bit Vector to parse through
void base9(struct BitVector *primes, uint32_t numbers) {
  printf("Base   9\n");
  printf("----  --\n");

  for (uint32_t i = 0; i <= numbers; i++) {
    if (bv_get_bit(primes, i) == 0) {
      continue;
    }

    uint8_t array[32]; // allocate 32 bits, which is equal to uint32_t

    uint32_t prime = i;
    int index = 0;
    while (prime > 0) { // run loop until quotient (prime) is < 0
      array[index] = prime % 9; // set current index of array to remainder
      prime = prime / 9; // set prime to quotient
      index += 1; // increment index by 1
    }
    bool is_palindrome = isPalindrome(array, index);
    if (is_palindrome) { // Check if array is a palindrome and print
      printf("%d = ", i);
      for (int x = 0; x < index; x++) {
        printf("%d", array[x]);
      }
      printf("\n");
    }
  }
  printf("\n");
  return;
}

// base10 Function
// This function will convert each prime number to base 10 and check
// if it is a palindome at base 10.
//
// Parameters:
// *primes - A Bit Vector that has been run through a sieve
// numbers - The amount of numbers for the Bit Vector to parse through
void base10(struct BitVector *primes, uint32_t numbers) {
  printf("Base  10\n");
  printf("----  --\n");

  for (uint32_t i = 0; i <= numbers; i++) {
    if (bv_get_bit(primes, i) == 0) {
      continue;
    }

    uint8_t array[32]; // allocate 32 bits, which is equal to uint32_t

    uint32_t prime = i;
    int index = 0;
    while (prime > 0) { // run loop until quotient (prime) is < 0
      array[index] = prime % 10; // set current index of array to remainder
      prime = prime / 10; // set prime to quotient
      index += 1; // increment index by 1
    }
    bool is_palindrome = isPalindrome(array, index);
    if (is_palindrome) { // Check if array is a palindrome and print
      printf("%d = ", i);
      for (int x = 0; x < index; x++) {
        printf("%d", array[x]);
      }
      printf("\n");
    }
  }
  printf("\n");
  return;
}

// base16 Function
// This function will convert each prime number to base 16 and check
// if it is a palindome at base 16.
//
// Parameters:
// *primes - A Bit Vector that has been run through a sieve
// numbers - The amount of numbers for the Bit Vector to parse through
void base16(struct BitVector *primes, uint32_t numbers) {
  printf("Base  16\n");
  printf("----  --\n");

  for (uint32_t i = 0; i <= numbers; i++) {
    if (bv_get_bit(primes, i) == 0) {
      continue;
    }

    uint8_t array[32]; // allocate 32 bits, which is equal to uint32_t

    uint32_t prime = i;
    int index = 0;
    while (prime > 0) { // run loop until quotient (prime) is < 0
      array[index] = prime % 16; // set current index of array to remainder
      prime = prime / 16; // set prime to quotient
      index += 1; // increment index by 1
    }
    bool is_palindrome = isPalindrome(array, index);
    if (is_palindrome) { // Check if array is a palindrome and print
      printf("%d = ", i);
      for (int x = 0; x < index; x++) {
        if (array[x] >= 10) { // Convert to ASCII character if > 10
          printf("%x", array[x]);
        } else {
          printf("%d", array[x]);
        }
      }
      printf("\n");
    }
  }
  return;
}

// Main Function
// This function will take in a command from the user using getopt().
// Will also call functions depending on the command to print output.
int main(int argc, char **argv) {
  int opt = 0;
  int n = 1000; // default value of n to 1000 is user does not specify n

  bool print_primes = false;
  bool print_palindromes = false;
  while ((opt = getopt(argc, argv, "n:sp")) != -1) {
    switch (opt) {
    case 'n': // 'n' set amount of numbers to iterate through
      n = atoi(optarg);
      break;
    case 's': // 's' print primes and special primes
      print_primes = true;
      break;
    case 'p': // 'p' print palindromes of a given base from prime numbers
      print_palindromes = true;
      break;
    }
  }
  if (print_primes == true) {
    if (n > 0) { // Check if n > 0 and not NULL or negative
      struct BitVector *primes = bv_create(n);
      sieve(primes);
      printPrimes(primes, n);
      bv_delete(primes);
    }
  }
  if (print_palindromes == true) {
    if (n > 0) { // Check if n > 0 and not NULL or negative
      struct BitVector *primes = bv_create(n);
      sieve(primes);
      base2(primes, n);
      base9(primes, n);
      base10(primes, n);
      base16(primes, n);
      bv_delete(primes);
    }
  }
  return 0;
}
