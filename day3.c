#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct rucksack_t {
    char *com1;
    char *com2;
    int line_length;
} typedef rucksack;

rucksack rucksack_create(char *line) {
    rucksack new_rucksack;
    int line_length = strlen(line) / 2;

    //printf("%d\n", line_length);

    new_rucksack.com1 = (char*) malloc(line_length + 1);
    memset(new_rucksack.com1, 0, line_length + 1);
    new_rucksack.com2 = (char*) malloc(line_length + 1);
    memset(new_rucksack.com2, 0, line_length + 1);

    new_rucksack.line_length = line_length;

    memcpy(new_rucksack.com1, line, line_length);
    memcpy(new_rucksack.com2, line + line_length, line_length);

    //printf("%s%s",new_rucksack.com1,new_rucksack.com2);

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

    for (int i = 0; i < 52; i++) {
        if (map[i]) {
            if (i > 25) {
                printf("%c", i + 71, i + 71);
            } else {
                printf("%c", i + 'A', i + 'A');
            }
        }
    }

    printf("\n");

    for (int i = 0; i < r.line_length; i++) {
        if (r.com2[i] >= 'a') {
            if (map[r.com2[i] - 71]) {
                printf("%c %d\n", r.com2[i], r.com2[i] - 71);
                return r.com2[i];
            }
        } else if (map[r.com2[i] - 'A']) {
            printf("%c %d\n", r.com2[i], r.com2[i] - 'A');
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

        printf("%s%s %s\n%c %d\n", buffer, new.com1, new.com2, error, priority);
        priority_sum += priority;
        //printf("%s%s\n", new.com1, new.com2);

        rucksack_destroy(new);
    }

    return priority_sum;
}

int main(int argc, char **argv) {
    int priority_sums;
    FILE *fp;

    fp = fopen("day3.txt", "r");
    priority_sums = get_priority_sums(fp);

    printf("sum of priorities is %d\n", priority_sums);

    //rucksack r = rucksack_create("PENIADOGGA");
    //char common = rucksack_get_error(r);
    //int prio = error_to_priority(common);
    //printf("%c\n", common);
    //printf("%d\n", (int)common);
    //printf("%d\n", prio);

    return 0;
}