#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const bool DEBUG = true;

enum { nb_of_columns = 140 };
// enum { nb_of_columns = 10 };

bool found_needle(uint8_t *counter, char *needle, unsigned long needle_len,
                  char current_char) {
  if (*counter != 0 && needle[0] == current_char) {
    // found start of needle, throw previous and init new needle
    *counter = 1;
  } else if (needle[*counter] == current_char) {
    if (*counter == needle_len - 1) {
      // found the needle, reset for next iteration
      *counter = 0;

      return true;
    } else {
      // still trying to read the entire needle
      *counter += 1;
    }
  } else {
    // needle is invalid, reset for next iteration
    *counter = 0;
  }

  return false;
}

uint64_t count_needle(FILE *input) {
  char *line = NULL;
  size_t line_len = 0;

  uint64_t count = 0;

  char *needle = "XMAS";
  char *rneedle = "SAMX";
  unsigned long needle_len = strlen(needle);
  // because the needle `XMAS` doesn't overlap it self in the same direction

  // init counters for diagonal direction
  uint8_t counters_tl[nb_of_columns] = {0};
  uint8_t counters_tr[nb_of_columns] = {0};
  uint8_t counters_bl[nb_of_columns] = {0};
  uint8_t counters_br[nb_of_columns] = {0};

  // init counters for top-down directions
  uint8_t counters_tb[nb_of_columns] = {0};
  uint8_t counters_bt[nb_of_columns] = {0};

  uint32_t lines_offset = 0;

  while (getline(&line, &line_len, input) - 1 == nb_of_columns) {
    uint32_t index = 0;

    // init counters for left-right directions
    uint8_t counter_lr = 0;
    uint8_t counter_rl = 0;

    // remove extremities of diagonal counters
    counters_tr[nb_of_columns - lines_offset] = 0;
    counters_tl[(nb_of_columns - 1 + lines_offset) % nb_of_columns] = 0;
    counters_br[(nb_of_columns - 1 + lines_offset) % nb_of_columns] = 0;
    counters_bl[nb_of_columns - lines_offset] = 0;

    // ignore final newline
    while (index < nb_of_columns) {
      char current = line[index];

      if (DEBUG)
        printf("%d%c.", index, current);

      // check left-right counters
      if (found_needle(&counter_lr, needle, needle_len, current))
        count += 1;

      if (found_needle(&counter_rl, rneedle, needle_len, current))
        count += 1;

      // check top-down counters
      if (found_needle(&counters_tb[index], needle, needle_len, current))
        count += 1;

      if (found_needle(&counters_bt[index], rneedle, needle_len, current))
        count += 1;

      // check top-diagnal
      if (found_needle(&counters_tr[(nb_of_columns - lines_offset + index) %
                                    nb_of_columns],
                       needle, needle_len, current))
        count += 1;

      if (found_needle(&counters_tl[(lines_offset + index) % nb_of_columns],
                       needle, needle_len, current))
        count += 1;

      // check bottom-diagnal
      if (found_needle(&counters_br[(lines_offset + index) % nb_of_columns],
                       rneedle, needle_len, current))
        count += 1;

      if (found_needle(&counters_bl[(nb_of_columns - lines_offset + index) %
                                    nb_of_columns],
                       rneedle, needle_len, current))
        count += 1;

      index += 1;
    }

    if (DEBUG)
      printf("\n");

    lines_offset += 1;
  }

  if (line)
    free(line);

  fclose(input);

  return count;
}

uint64_t x_mas(FILE *input) {
  char *pline = NULL;
  // size_t pline_len = 0;
  char *cline = NULL;
  // size_t cline_len = 0;
  char *nline = NULL;
  size_t nline_len = 0;

  uint64_t count = 0;

  char pre_computed_position[][4] = {
      {'M', 'M', 'S', 'S'},
      {'M', 'S', 'M', 'S'},
      {'S', 'M', 'S', 'M'},
      {'S', 'S', 'M', 'M'},
  };

  while (getline(&nline, &nline_len, input) - 1 == nb_of_columns) {
    if (pline != NULL && cline != NULL) {
      // iterate with a margin of one to avoid out of bounds
      uint32_t index = 1;
      while (index < nb_of_columns - 1) {
        char current = cline[index];

        if (current == 'A') {
          for (int precomp_index = 0; precomp_index < 4; precomp_index += 1) {
            if (pline[index - 1] == pre_computed_position[precomp_index][0] &&
                pline[index + 1] == pre_computed_position[precomp_index][1] &&
                nline[index - 1] == pre_computed_position[precomp_index][2] &&
                nline[index + 1] == pre_computed_position[precomp_index][3]) {
              count += 1;
              break;
            }
          }
        }

        index += 1;
      }

      if (DEBUG)
        printf("\n");
    }

    pline = cline;
    cline = nline;
    nline = NULL;
  }

  if (pline)
    free(pline);
  if (cline)
    free(cline);
  if (nline)
    free(nline);

  fclose(input);

  return count;
}

int main() {
  FILE *input;

  // silver
  input = fopen("day4.txt", "r");
  // input = fopen("day4.sample.txt", "r");
  assert(input != NULL && "day4.txt is not accessible");

  uint64_t silver = count_needle(input);

  // golden
  input = fopen("day4.txt", "r");
  // input = fopen("day4.sample.txt", "r");
  assert(input != NULL && "day4.txt is not accessible");

  uint64_t golden = x_mas(input);

  printf("silver: %zu, gold: %zu\n", silver, golden);

  return EXIT_SUCCESS;
}
