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

bool pair_has_contain(char *line) {
    int alow, blow, ahigh, bhigh;

    int first_dash, comma, second_dash;
}