#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char cell[2] = " *";
#define SIZE 64 
int grid[SIZE] = {0};

#define ITERATIONS 64 

typedef struct {
  char pattern[3];
  int output;
} Pattern;

#define PATTERNS 8
Pattern patterns[PATTERNS] = {
  {"111", 0},
  {"110", 1},
  {"101", 1},
  {"100", 0},
  {"011", 1},
  {"010", 1},
  {"001", 1},
  {"000", 0},
};

void init_grid() {
  for(size_t i = 0; i < SIZE; i++) {
    grid[i] = rand() % 2;
  }
}

void print_grid() {
  for(size_t i = 0; i < SIZE; i++) {
    printf("%c", cell[grid[i]]);
  }
  printf("\n");
}

void gen_next() {
  int next_grid[SIZE] = {0};
  for(size_t i = 0; i < SIZE; i++) {
    size_t prev_in = (i - 1 + SIZE) % SIZE;
    size_t cur_in = (i + SIZE) % SIZE;
    size_t next_in = (i + 1 + SIZE) % SIZE;
    char pattern[3] = {grid[prev_in] + '0', grid[cur_in] + '0', grid[next_in] + '0'};

    for(size_t j = 0; j < PATTERNS; j++) {
	if(strncmp(pattern, patterns[j].pattern, 3) == 0) {
            next_grid[i] = patterns[j].output;
        }
    }

  }
  memcpy(grid, next_grid, sizeof(int) * SIZE);
}

int main() {
  grid[SIZE-1] = 1;
  srand(time(NULL));
  for(size_t i = 0; i < ITERATIONS; i++) {
    print_grid();
    gen_next();
  }
}
