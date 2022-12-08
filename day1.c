#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INPUT_FILE "day1.txt"

void get_three_highest_calories(FILE *fp) {
    int highest_calorie_elves[3];
    int current_elf_calories = 0;

    memset(&highest_calorie_elves, 0, 3*sizeof(int));

    char *buffer = (char*) malloc(10*sizeof(char));

    while (!feof(fp)) {
        int calories = 0;

        fgets(buffer, 10, fp);

        if (strlen(buffer) > 1) {
            calories = atoi(buffer);
            current_elf_calories += calories;
        } else {
            if (current_elf_calories >= highest_calorie_elves[2]) {
                int temp = highest_calorie_elves[2];
                int temp2 = highest_calorie_elves[1];
                highest_calorie_elves[2] = current_elf_calories;
                highest_calorie_elves[1] = temp;
                highest_calorie_elves[0] = temp2;
            } else if (current_elf_calories >= highest_calorie_elves[1]) {
                int temp = highest_calorie_elves[1];
                highest_calorie_elves[1] = current_elf_calories;
                highest_calorie_elves[0] = temp;
            } else if (current_elf_calories >= highest_calorie_elves[0]) {
                highest_calorie_elves[0] = current_elf_calories;
            }

            current_elf_calories = 0;
        }
    }

    free(buffer);

    printf("sum of three highest calories is %d\n", highest_calorie_elves[0] + highest_calorie_elves[1] + highest_calorie_elves[2]);
}

int get_highest_calories(FILE* fp) {
    int current_elf_calories = 0;
    int highest_elf_calories = 0;

    char *buffer = (char*) malloc(20*sizeof(char));

    while (!feof(fp)) {
        int calories = 0;
        
        fgets(buffer, 20, fp);
        
        if (strlen(buffer) > 1) {
            calories = atoi(buffer);
            current_elf_calories += calories;
        } else {
            if (highest_elf_calories < current_elf_calories) {
                highest_elf_calories = current_elf_calories;
            }
            current_elf_calories = 0;
        }
    }

    return highest_elf_calories;
}

int main(int argc, char **argv) {
    FILE* fp = NULL;
    int highest_calories = -1;

    if (argc >= 1) {
        fp = fopen(argv[1], "r");
    } else {
        fp = fopen(INPUT_FILE, "r");
    }

    get_three_highest_calories(fp); // part 2
    fseek(fp, 0, SEEK_SET);
    highest_calories = get_highest_calories(fp); // part 1

    if (fp != NULL) {
        fclose(fp);
    }

    printf("highest calories is %d", highest_calories);
}