#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> /* for atoi */

#define MAX_LINE_LENGTH 256
#define DEFAULT_DISPLAY_WIDTH 31 /* WIDTH 80 (8+31 +2 8+31) = 31 */
#define LINE_NUMBER_WIDTH 4
#define MAX_LOOKAHEAD 10

void read_file(FILE* file, char* line, int* line_number) {
  if (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    line[strcspn(line, "\n")] = 0;
    (*line_number)++;
  } else {
    line[0] = '\0';
  }
}

void print_truncated(const char* line, int width) {
  int len = (int)strlen(line);
  if (len <= width) {
    printf("%-*s", width, line);
  } else {
    printf("%.*s...", width - 3, line);
  }
}

void print_diff_line(const char* left, const char* right, int left_num, int right_num, char left_marker, char right_marker, int display_width) {
  if (left_num == 0) {
    printf("     %c ", left_marker);
  } else {
    printf("%4d %c ", left_num % 10000, left_marker);
  }
  print_truncated(left, display_width);
  printf(" | ");
  if (right_num == 0) {
    printf("     %c ", right_marker);
  } else {
    printf("%4d %c ", right_num % 10000, right_marker);
  }
  print_truncated(right, display_width);
  printf("\n");
}

int find_match(char lines[MAX_LOOKAHEAD][MAX_LINE_LENGTH], int count, const char* target) {
  for (int i = 0; i < count; i++) {
    if (strcmp(lines[i], target) == 0) {
      return i;
    }
  }
  return -1;
}

void remove_first_line(char lines[MAX_LOOKAHEAD][MAX_LINE_LENGTH], int line_nums[MAX_LOOKAHEAD], int* count) {
  for (int i = 0; i < *count - 1; i++) {
    strcpy(lines[i], lines[i + 1]);
    line_nums[i] = line_nums[i + 1];
  }
  if (*count > 0) {
    (*count)--;
  }
}

void print_diff(FILE* file1, FILE* file2, int display_width) {
  char lines1[MAX_LOOKAHEAD][MAX_LINE_LENGTH], lines2[MAX_LOOKAHEAD][MAX_LINE_LENGTH];
  int line_nums1[MAX_LOOKAHEAD], line_nums2[MAX_LOOKAHEAD];
  int count1 = 0, count2 = 0;
  int line_num1 = 0, line_num2 = 0;
  bool in_diff_section = false;
  int identical_count = 0;

  while (1) {
    /* Fill buffers */
    while (count1 < MAX_LOOKAHEAD && !feof(file1)) {
      read_file(file1, lines1[count1], &line_num1);
      line_nums1[count1] = line_num1;
      if (lines1[count1][0] == '\0') break;
      count1++;
    }
    while (count2 < MAX_LOOKAHEAD && !feof(file2)) {
      read_file(file2, lines2[count2], &line_num2);
      line_nums2[count2] = line_num2;
      if (lines2[count2][0] == '\0') break;
      count2++;
    }

    if (count1 == 0 && count2 == 0) break;

    int match1 = find_match(lines2, count2, lines1[0]);
    int match2 = find_match(lines1, count1, lines2[0]);

    if (match1 == 0 && match2 == 0) {
      /* Lines are identical */
      identical_count++;
      if (in_diff_section) {
        print_diff_line(lines1[0], lines2[0], line_nums1[0], line_nums2[0], ' ', ' ', display_width);
        in_diff_section = false;
      } else if (identical_count == 1) {
        print_diff_line(lines1[0], lines2[0], line_nums1[0], line_nums2[0], ' ', ' ', display_width);
      } else if (identical_count == 2) {
        printf("...\n");
      }
      remove_first_line(lines1, line_nums1, &count1);
      remove_first_line(lines2, line_nums2, &count2);
    } else {
      /* Lines are different */
      in_diff_section = true;
      identical_count = 0;
      if (match1 > 0) {
        /* Print any lines from file2 before the match */
        for (int i = 0; i < match1; i++) {
          print_diff_line("", lines2[0], 0, line_nums2[0], ' ', '+', display_width);
          remove_first_line(lines2, line_nums2, &count2);
        }
      } else if (match2 > 0) {
        /* Print any lines from file1 before the match */
        for (int i = 0; i < match2; i++) {
          print_diff_line(lines1[0], "", line_nums1[0], 0, '-', ' ', display_width);
          remove_first_line(lines1, line_nums1, &count1);
        }
      } else {
        /* No match found, print the first line from each file */
        print_diff_line(lines1[0], lines2[0], line_nums1[0], line_nums2[0], '!', '!', display_width);
        remove_first_line(lines1, line_nums1, &count1);
        remove_first_line(lines2, line_nums2, &count2);
      }
    }
  }
}

int main(int argc, char* argv[]) {
  int display_width = DEFAULT_DISPLAY_WIDTH;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--width") == 0 || strcmp(argv[i], "-w") == 0) {
      if (i + 1 < argc) {
        display_width = (atoi(argv[i + 1]) -18) / 2; /* WIDTH 80 (8+31 +2 8+31) = 31 */
        i++; /* Skip the width value */
      } else {
        fprintf(stderr, "Error: --width option requires a numeric value\n");
        return 1;
      }
    }
  }

  if (argc < 3) {
    printf("Usage: %s <file1> <file2> [--width <number>]\n", argv[0]);
    return 1;
  }

  FILE* file1 = fopen(argv[1], "r");
  FILE* file2 = fopen(argv[2], "r");

  if (file1 == NULL || file2 == NULL) {
    printf("Error opening files\n");
    return 1;
  }

  print_diff(file1, file2, display_width);

  fclose(file1);
  fclose(file2);

  return 0;
}