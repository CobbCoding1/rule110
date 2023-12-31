#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum {
  OFF = 0,
  ON = 1,
} Cell;

char cell[2] = " *";
#define SIZE 128 
Cell grid[SIZE] = {0};

#define ITERATIONS 128 

typedef struct {
  char pattern[3];
  Cell output;
} Pattern;

#define PATTERNS 8
Pattern patterns[PATTERNS] = {
  {"111", OFF},
  {"110", ON},
  {"101", ON},
  {"100", OFF},
  {"011", ON},
  {"010", ON},
  {"001", ON},
  {"000", OFF},
};

void init_grid() {
  for(size_t i = 0; i < SIZE; i++) {
    grid[i] = rand() % 2;
  }
}

void print_grid() {
  for(size_t i = 0; i < SIZE; i++) {
	  putc(cell[grid[i]], stdout);
  }
  printf("\n");
}

void print_grid_twin() {
  size_t first_index = 0;
  for(size_t i = 0; i < SIZE; i++) {
	  if(grid[i] == 1) {
		first_index = i;
		break;
	  }
  }

  for(size_t i = first_index / 2; i < SIZE; i++) {
	printf("%c", cell[grid[i]]);
  }

  printf("\n");
}

void gen_next() {
  Cell next_grid[SIZE] = {0};
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
  grid[SIZE-1] = ON;
  srand(time(NULL));
  for(size_t i = 0; i < ITERATIONS; i++) {
    print_grid();
    gen_next();
  }
}
