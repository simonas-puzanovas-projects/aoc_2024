#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"

typedef struct {
    int x;
    int y;
} Point;

int solve(FILE *fptr){
    char line[2048];

    static char matrix[1024][1024];
    bool is_valid[1024][1024];

    int y_move[6] = {1, 0, -1, -1, 0, 1};
    int x_move[6] = {-1, 0, 1, 1, 0, -1};
    int x_modifier[2] = {1, -1};

    char mas_c[] = "MAS";
    int mas_size = 3;
    int mas_index_buffer = 0;

    int result = 0;

    //count colums, line lengths
    int column_count = 0;
    int line_length = 0;

    while (fgets(line, sizeof(line), fptr)){
        for (int i = 0; i < strlen(line); i++){
            matrix[column_count][i] = line[i];
            if (column_count == 0) line_length += 1;
        }
        column_count += 1; 
    }

    Point valid_stack[mas_size*4];

    for (int y = 0; y < column_count; y++){
        for (int x = 0; x < line_length; x++){

            int good_count = 0;

            for (int i = 0; i < 2; i++){

                int buffer = 0;

                for (int mas_index = 0; mas_index < mas_size*2; mas_index++){

                    int y_coord = y + y_move[mas_index];
                    int x_coord = x + x_move[mas_index] * x_modifier[i];

                    valid_stack[i * mas_size + mas_index] = (Point){x_coord, y_coord};

                    if (y_coord < 0
                            || y_coord > column_count
                            || x_coord < 0
                            || x_coord > line_length
                            || matrix[y_coord][x_coord] != mas_c[buffer])
                    {
                        buffer = 0;
                    }

                    if (buffer == mas_size-1){
                        good_count += 1;
                        buffer = 0;
                        continue;
                    }

                    if (matrix[y_coord][x_coord] == mas_c[buffer]){
                        buffer += 1;
                    }
                }

            }
            if (good_count == 2){
                result += 1;
                for (int valid_index = 0; valid_index < mas_size*2; valid_index++){
                    is_valid[valid_stack[valid_index].y][valid_stack[valid_index].x] = true;
                }
            };
        }
    }

    for (int y = 0; y < column_count; y++){
        for (int x = 0; x < line_length; x++){
            if (is_valid[y][x]){
                printf("%s%c",KGRN, matrix[y][x]);
            }
            else{
                printf("%s%c",KWHT, matrix[y][x]);
            }
        }
    }

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
