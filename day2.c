#include<stdio.h>
#include<stdlib.h>

#define DAY2_FILE "day2.txt"

static int old_game_matrix[3][3] = { // used in part 1
    //r p  s (you choose)
    {4, 8, 3}, // r (they choose)
    {1, 5, 9}, // p
    {7, 2, 6}  // s
};

static int new_game_matrix[3][3] = { // used in part 2
    //l   d    w (you choose)
    {0+3, 3+1, 6+2,}, // r (they choose)
    {0+1, 3+2, 6+3,}, // p
    {0+2, 3+3, 6+1,}  // s
};

int get_old_rps_score(char *rps_line) {
    char opponent = rps_line[0];
    char player = rps_line[2];

    return old_game_matrix[opponent - 0x41][player - 0x58];
}

int get_new_rps_score(char *rps_line) {
    char opponent = rps_line[0];
    char player = rps_line[2];

    return new_game_matrix[opponent - 0x41][player - 0x58];
}

void get_total_score(FILE *fp) {
    int old_score = 0;
    int new_score = 0;

    char *buffer = (char*) malloc(8*sizeof(char));

    while (!feof(fp)) { 
        fgets(buffer, 8, fp);
        //printf("%s", buffer);

        old_score += get_old_rps_score(buffer);
        new_score += get_new_rps_score(buffer);
    }

    printf("part 1 score is %d\n", old_score);
    printf("part 2 score is %d\n", new_score);
}

int main(int argc, char **argv) {
    FILE *fp;
    int result = 0;

    if (argc >= 1) {
        fp = fopen(argv[1], "r");
    } else {
        fp = fopen(DAY2_FILE, "r");
    }

    get_total_score(fp);

    fclose(fp);

    return 0;
}