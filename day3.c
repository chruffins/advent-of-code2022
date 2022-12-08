#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// part 1

struct rucksack_t {
    char *com1;
    char *com2;
    int line_length;
} typedef rucksack;

rucksack rucksack_create(char *line) {
    rucksack new_rucksack;
    int line_length = strlen(line) / 2;

    new_rucksack.com1 = (char*) malloc(line_length + 1);
    memset(new_rucksack.com1, 0, line_length + 1);
    new_rucksack.com2 = (char*) malloc(line_length + 1);
    memset(new_rucksack.com2, 0, line_length + 1);

    new_rucksack.line_length = line_length;

    memcpy(new_rucksack.com1, line, line_length);
    memcpy(new_rucksack.com2, line + line_length, line_length);

    return new_rucksack;
}

void rucksack_destroy(rucksack trash) {
    free(trash.com1);
    free(trash.com2);
}

char rucksack_get_error(rucksack r) {
    char map[52];
    memset(map, 0, 52);

    for (int i = 0; i < r.line_length; i++) {
        if (r.com1[i] >= 'a') {
            map[r.com1[i] - 71] = 1;
        } else {
            map[r.com1[i] - 'A'] = 1;
        }
    }

    for (int i = 0; i < r.line_length; i++) {
        if (r.com2[i] >= 'a') {
            if (map[r.com2[i] - 71]) {
                return r.com2[i];
            }
        } else if (map[r.com2[i] - 'A']) {
            return r.com2[i];
        }
    }

    return 0; // what the fuck
}

int error_to_priority(char error) {
    int priority;

    if (error > 0x60) { // for lowercase
        priority = error - 0x60;
    } else {
        priority = error - 0x26;
    }

    return priority;
}

int get_priority_sums(FILE *fp) {
    int priority_sum = 0;
    int priority = 0;
    char *buffer = (char*)malloc(60*sizeof(char));

    while (!feof(fp)) { 
        fgets(buffer, 60, fp);
        
        rucksack new = rucksack_create(buffer);
        char error = rucksack_get_error(new);
        int priority = error_to_priority(error);

        priority_sum += priority;

        rucksack_destroy(new);
    }

    free(buffer);
    return priority_sum;
}

// part 2

void fill_map_from_line(char *line, char *map) {
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == '\n') continue;
        if (line[i] >= 'a') {
            map[line[i] - 71] = 1; // lowercase 26-51
        } else {
            map[line[i] - 'A'] = 1;  // uppercase 0-25
        }
    }
}

char get_common_char(char *line1, char *line2, char *line3) {
    char map1[52];
    char map2[52];
    char map3[52];
    memset(map1, 0, 52);
    memset(map2, 0, 52);
    memset(map3, 0, 52);

    fill_map_from_line(line1, map1);
    fill_map_from_line(line2, map2);
    fill_map_from_line(line3, map3);

    for (int i = 0; i < 26; i++) {
        if (map1[i] && map2[i] && map3[i]) {
            return i + 'A';
        }
    }

    for (int i = 26; i < 52; i++) {
        if (map1[i] && map2[i] && map3[i]) {
            return i - 26 + 'a';
        }
    }

    return 0;
}

int get_priority_sums_p2(FILE *fp) {
    int priority_sum = 0;
    int priority = 0;
    char buffer1[60];
    char buffer2[60];
    char buffer3[60];

    while (!feof(fp)) {
        fgets(buffer1, 60, fp);
        fgets(buffer2, 60, fp);
        fgets(buffer3, 60, fp);

        char common = get_common_char(buffer1, buffer2, buffer3);
        int priority = error_to_priority(common);

        priority_sum += priority;
    }

    return priority_sum;
}

int main(int argc, char **argv) {
    int priority_sums;
    FILE *fp;

    fp = fopen("day3.txt", "r");
    priority_sums = get_priority_sums_p2(fp);

    printf("sum of priorities is %d\n", priority_sums);

    //rucksack r = rucksack_create("PENIADOGGA");
    //char common = rucksack_get_error(r);
    //int prio = error_to_priority(common);
    return 0;
}