#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct elf_range_t {
    int low;
    int high;
} typedef elf_range;

elf_range larger_elf_range(elf_range a, elf_range b) {
    return (a.high - a.low > b.high - b.low) ? a : b;
}

bool elf_range_contains(elf_range a, elf_range b) {
    if (a.high - a.low > b.high - b.low) {
        return (a.low <= b.low && b.high <= a.high);
    } else {
        return (b.low <= a.low && a.high <= b.high);
    }
}

void get_pair_from_line(char *line, elf_range *a, elf_range *b) {
    int alow, blow, ahigh, bhigh;

    char *buffer;

    int first_dash, comma, second_dash;

    for (int i = 0; i < strlen(line); i++) { // getting first dash allows us to get alow
        if (line[i] == '-') {
            first_dash = i;
            buffer = (char*)calloc(i, sizeof(char)); // start = 0, end = i
            memcpy(buffer, line + 0, i);
            printf("alow_buffer: %s\n", buffer);
            alow = atoi(buffer);
            free(buffer);
            break;
        }
    }

    for (int i = first_dash + 1; i < strlen(line); i++) { // getting comma gets ahigh
        if (line[i] == ',') {
            comma = i;
            buffer = (char*) calloc(comma - (first_dash + 1), sizeof(char));
            memcpy(buffer, line + first_dash + 1, i - (first_dash + 1));
            printf("ahigh_buffer: %s\n", buffer);
            ahigh = atoi(buffer);
            free(buffer);
            break;
        }
    }

    for (int i = comma + 1; i < strlen(line); i++) { // getting second dash gets blow
        if (line[i] == '-') {
            second_dash = i;
            buffer = (char*) calloc(second_dash - (comma + 1), sizeof(char));
            memcpy(buffer, line + comma + 1, i - (comma + 1));
            printf("blow_buffer: %s\n", buffer);
            blow = atoi(buffer);
            free(buffer);
            break;
        }
    }

    // it also gets bhigh

    for (int i = second_dash + 1; i < strlen(line); i++) { // getting second dash gets blow
        if (line[i] == '\n' || line[i] == 0) {
            buffer = (char*) calloc(i - (second_dash + 1), sizeof(char));
            memcpy(buffer, line + second_dash + 1, i - (second_dash + 1));
            printf("bhigh_buffer: %s\n", buffer);
            bhigh = atoi(buffer);
            free(buffer);
            break;
        }
    }

    a->low = alow;
    a->high = ahigh;
    b->low = blow;
    b->high = bhigh;
}

void part1() {
    elf_range a;
    elf_range b;
    char buffer[32];

    FILE *fp;

    fp = fopen("day4.txt", "r");

    while (!feof) {
        fgets(buffer, 32, fp);

        get_pair_from_line(buffer, &a, &b);
    }

    fclose(fp);
}
    

int main() {
    get_pair_from_line("71-87,70-88\n", NULL, NULL);

    part1();

    return 0;
}