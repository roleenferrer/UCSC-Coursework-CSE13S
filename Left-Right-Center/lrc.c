#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t left(uint32_t pos, uint32_t players);
uint32_t right(uint32_t pos, uint32_t players);

int main(void) {
  typedef enum faciem { LEFT, RIGHT, CENTER, PASS } faces;
  faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

  const char *names[] = { "Happy", "Sleepy", "Sneezy", "Dopey", "Bashful",
    "Grumpy", "Doc", "Mirror Mirror", "Snow White", "Wicked Queen" };

  // Get random seed from user and save it to "int seed"
  uint32_t seed;
  printf("Random seed: ");
  scanf("%d", &seed);
  srand(seed);

  // Get number of players and save it to "int players"
  int players;
  printf("How many players? ");
  scanf("%d", &players);

  // Check if number the user input (k) is between 1<k<=10, else exit
  if (players <= 0 || players > 10) {
    exit(0);
  }

  // Declare pot and pos as an integer
  //
  // pot: The amount of money that is currently in the pot
  // pos: The current position in names[] array
  int pot;
  int pos;
  pot = 0;
  pos = 0;

  // Tracking money
  //
  // money[] has 10 "$3" for k players from 1 < k <= 10.
  // Values change during the while loop to correspond
  // to losing or gaining money.
  int money[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
  int i, roll;

  // While loop for the left, right center game.
  //
  // while(1) is declared in order to have the game run
  // indefinitely. Will only break if the current player's
  // money (money[pos]) plus the pot is equal to the amount
  // of players multiplied by 3 (the total amount of money
  // in the game)
  //
  // Roll algorithm
  //
  // if the current player's money is >= 3, roll 3 times
  // if the current player's money is == 2, roll 2 times
  // if the current player's money is == 1, roll 1 time
  // if the current player's money is == 0, print nothing
  //
  // Current position algorithm
  //
  // if the current player's position is equal to the amount
  // of players - 1, reset the position to the begninning (0)
  // else: add 1 to the current position to go to the next
  // person

  while (1) {
    // Exit loop condition must be met to exit
    if (money[pos] + pot == players * 3) {
      printf("%s wins the $%d pot with $%d left in the bank!\n", names[pos],
          pot, money[pos]);
      break;
    }
    // if current player's money is >= 3
    if (money[pos] >= 3) {
      printf("%s rolls... ", names[pos]);

      for (i = 1; i < 4; ++i) {
        roll = rand() % 6;

        if (die[roll] == LEFT) {
          if (i == 3) {
            printf("gives $1 to %s", names[left(pos, players)]);
          } else {
            printf("gives $1 to %s ", names[left(pos, players)]);
          }
          --money[pos];
          ++money[left(pos, players)];

        } else if (die[roll] == RIGHT) {
          if (i == 3) {
            printf("gives $1 to %s", names[right(pos, players)]);
          } else {
            printf("gives $1 to %s ", names[right(pos, players)]);
          }
          --money[pos];
          ++money[right(pos, players)];

        } else if (die[roll] == CENTER) {
          if (i == 3) {
            printf("puts $1 in the pot");
          } else {
            printf("puts $1 in the pot ");
          }
          --money[pos];
          ++pot;

        } else if (die[roll] == PASS) {
          if (i == 3) {
            printf("gets a pass");
          } else {
            printf("gets a pass ");
          }
        }
      }
      printf("\n");

      // if current player's money is 2
    } else if (money[pos] == 2) {
      printf("%s rolls... ", names[pos]);

      for (i = 1; i < 3; ++i) {
        roll = rand() % 6;
        if (die[roll] == LEFT) {
          if (i == 2) {
            printf("gives $1 to %s", names[left(pos, players)]);
          } else {
            printf("gives $1 to %s ", names[left(pos, players)]);
          }
          --money[pos];
          ++money[left(pos, players)];

        } else if (die[roll] == RIGHT) {
          if (i == 2) {
            printf("gives $1 to %s", names[right(pos, players)]);
          } else {
            printf("gives $1 to %s ", names[right(pos, players)]);
          }
          --money[pos];
          ++money[right(pos, players)];

        } else if (die[roll] == CENTER) {
          if (i == 2) {
            printf("puts $1 in the pot");
          } else {
            printf("puts $1 in the pot ");
          }
          --money[pos];
          ++pot;

        } else if (die[roll] == PASS) {
          if (i == 2) {
            printf("gets a pass");
          } else {
            printf("gets a pass ");
          }
        }
      }
      printf("\n");

      // if current player's money is 1
    } else if (money[pos] == 1) {
      printf("%s rolls... ", names[pos]);

      for (i = 1; i < 2; ++i) {
        roll = rand() % 6;
        if (die[roll] == LEFT) {
          if (i == 1) {
            printf("gives $1 to %s", names[left(pos, players)]);
          } else {
            printf("gives $1 to %s ", names[left(pos, players)]);
          }
          --money[pos];
          ++money[left(pos, players)];

        } else if (die[roll] == RIGHT) {
          if (i == 1) {
            printf("gives $1 to %s", names[right(pos, players)]);
          } else {
            printf("gives $1 to %s ", names[right(pos, players)]);
          }
          --money[pos];
          ++money[right(pos, players)];

        } else if (die[roll] == CENTER) {
          if (i == 1) {
            printf("puts $1 in the pot");
          } else {
            printf("puts $1 in the pot ");
          }
          --money[pos];
          ++pot;

        } else if (die[roll] == PASS) {
          if (i == 1) {
            printf("gets a pass");
          } else {
            printf("gets a pass ");
          }
        }
      }
      printf("\n");

      // Check if the amount of players are in the game
    }
    if (pos == players - 1) {
      pos = 0;
    } else {
      ++pos;
    }
  }
  return 0;
}

// Returns the position of the player to the left
//
// pos: The position of the current player.
// players: The number of players in the game.

uint32_t left(uint32_t pos, uint32_t players) {
  return ((pos + players - 1) % players);
}

// Returns the position of the player to the right
//
// pos: The position of the current player.
// players: The number of players in the game.

uint32_t right(uint32_t pos, uint32_t players) {
  return ((pos + 1) % players);
}
