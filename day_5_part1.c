#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"

typedef struct {
    int num1;
    int num2;
} before_after;

int solve(FILE *fptr){
    bool in_before_after = true;

    int number_buffer_count = 0;
    char number_buffer[256];

    before_after b_a_nums[1024];
    int b_a_size = 0;

    char line[2048];

    int result = 0;
    int column_count = 0;

    while (fgets(line, sizeof(line), fptr)){
        int first_num = 0;
        int second_num = 0;

        int normal_number_array[1024];
        int normal_number_count = 0;

        for (int i = 0; i < strlen(line); i++){

            if (in_before_after){

                if (i == 0 && line[i] == '\r'){
                    in_before_after = false;
                    number_buffer_count = 0;
                    memset(number_buffer, 0, 256);
                    continue;
                }
                else if (line[i] == '|'){
                    first_num = atoi(number_buffer);
                    number_buffer_count = 0;
                    memset(number_buffer, 0, 256);
                }
                else if (line[i] == '\n'){
                    second_num = atoi(number_buffer);
                    number_buffer_count = 0;
                    memset(number_buffer, 0, 256);

                    before_after first_sec;
                    first_sec.num1 = first_num;
                    first_sec.num2 = second_num;
                    b_a_nums[b_a_size] = first_sec;
                    b_a_size += 1;
                }
                else if (isdigit(line[i])){
                    number_buffer[number_buffer_count] = line[i];
                    number_buffer_count += 1;
                }

            }
            else if (!in_before_after){
                if (line[i] == ',' || line[i] == '\r' || line[i] == '\n'){
                    if (number_buffer_count != 0){
                        normal_number_array[normal_number_count] = atoi(number_buffer);
                        normal_number_count += 1;
                    }
                    number_buffer_count = 0;
                    memset(number_buffer, 0, 256);
                }
                else if (isdigit(line[i])){
                    number_buffer[number_buffer_count] = line[i];
                    number_buffer_count += 1;
                }
            }
        }

        if (normal_number_count == 0){
            continue; 
        }

        bool correct = true;
        for (int i = 0; i < normal_number_count; i++){
            for (int ii = 0; ii < b_a_size; ii++){
                if (normal_number_array[i] == b_a_nums[ii].num1){
                    for (int y = 0; y < i; y++){
                        if (normal_number_array[y] == b_a_nums[ii].num2){
                            printf("negeras before_after to right: %d %d\n", b_a_nums[ii].num1, b_a_nums[ii].num2);
                            correct = false;
                        }
                    }
                }
                else if (normal_number_array[i] == b_a_nums[ii].num2){
                    for (int y = i; y < normal_number_count; y++){
                        if (normal_number_array[y] == b_a_nums[ii].num1){
                            printf("negeras before_after to left: %d %d\n", b_a_nums[ii].num1, b_a_nums[ii].num2);
                            correct = false;
                        }
                    }
                }
            }
        }
        if (correct && !in_before_after){
            printf("correct: ");
            for (int i = 0; i < normal_number_count; i++){
                printf("%d ", normal_number_array[i]);
            }
            printf("\n");
            result += normal_number_array[normal_number_count / 2];
        }
        column_count += 1; 
    }

    printf("\n");
    for (int i = 0; i < b_a_size; i++){
        printf("%d|%d\n", b_a_nums[i].num1, b_a_nums[i].num2);
    }
    printf("\n");

    return result;
}

int main(){

    FILE *fptr;
    fptr = fopen("input", "r");

    int line_length;
    fseek(fptr, 0, SEEK_END);
    fseek(fptr, 0, SEEK_SET);

    printf("\n%sanswer: %d\n",KWHT, solve(fptr));

    return 0;

}
