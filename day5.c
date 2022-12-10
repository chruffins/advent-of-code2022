#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack_t {
    char data[80];
    int pointer;
} typedef stack;

stack stack_create() {
    stack new_stack;

    memset(&new_stack, 0, sizeof(stack));
    new_stack.pointer = -1;

    return new_stack;
}

void stack_push(stack *stacker, char data) {
    stacker->pointer += 1;
    stacker->data[stacker->pointer] = data;
}

char stack_pop(stack *stacker) {
    char data = stacker->data[stacker->pointer];
    stacker->data[stacker->pointer] = 0;
    stacker->pointer -= 1;

    return data;
}

char stack_peek(stack *stacker) {
    return stacker->data[stacker->pointer];
}

// part 2 function
void stack_grab(stack *stacker, char *buffer, int to_move) {
    int start = stacker->pointer - (to_move - 1);
    memcpy(buffer, &(stacker->data[start]), to_move);
    memset(&(stacker->data[start]), 0, to_move);

    stacker->pointer -= to_move;
} // abcdef -> pointer = 5, d = txt[3], abc -> pointer = 2

void get_move_command(char *line, int *to_move, int *from, int *to) {
    sscanf(line, "move %d from %d to %d", to_move, from, to);
}

// this just goes through the file to grab the stack contents
void construct_stacks(stack *stacks, FILE *fp) {
    for (int i = 0; i < 9; i++) {
        stacks[i] = stack_create();
    }

    char buffer[40];
    memset(buffer, 0 , 40);

    while(1) {
        fgets(buffer, 40, fp);
        if (buffer[1] == '1') break;
        //printf("%s", buffer);

        for (int i = 0; i < 9; i++) {
            if (buffer[1+(i*4)] != ' ') {
                stack_push(&stacks[i], buffer[1+(i*4)]);
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        char temp;
        for (int j = 0, k = strlen(stacks[i].data) - 1; j < k; j++, k--) {
            temp = stacks[i].data[j];
            stacks[i].data[j] = stacks[i].data[k];
            stacks[i].data[k] = temp;
        }
        //printf("%c", stack_peek(&stacks[i]));
    }

    // prepare to start moving things
    fgets(buffer, 40, fp); // get the empty line (line 10) out of the way
} 

void part1() {
    stack stacks[9];
    FILE *fp = fopen("day5.txt", "r");
    char buffer[40];
    memset(buffer, 0, 40);

    // fill the stacks

    construct_stacks(stacks, fp);

    while (!feof(fp)) {
        int to_move, from, to;
        fgets(buffer, 40, fp);

        get_move_command(buffer, &to_move, &from, &to);

        for (int i = 0; i < to_move; i++) {
            char temp = stack_pop(&stacks[from-1]);
            //printf("%c %d %d %d\n", temp, i, from, to);

            stack_push(&stacks[to-1], temp);
        }
    }

    fclose(fp);

    for (int i = 0; i < 9; i++) {
        printf("%c", stack_peek(&stacks[i]));
    }
}

void part2() {
    stack stacks[9];
    FILE *fp = fopen("day5.txt", "r");
    char movebuffer[40];
    char buffer[40];
    memset(movebuffer, 0, 40);
    memset(buffer, 0, 40);

    // fill the stacks

    construct_stacks(stacks, fp);

    while (!feof(fp)) {
        int to_move, from, to;
        fgets(buffer, 40, fp);

        get_move_command(buffer, &to_move, &from, &to);

        stack_grab(&stacks[from-1], movebuffer, to_move);

        for (int i = 0; i < to_move; i++) {
            stack_push(&stacks[to-1], movebuffer[i]);
        }
    }

    fclose(fp);

    for (int i = 0; i < 9; i++) {
        //printf("%c", stack_peek(&stacks[i]));
        printf("%s\n", stacks[i].data);
    }
}

int main() {
    part1();
    printf("\n");
    part2();

    return 0;
}