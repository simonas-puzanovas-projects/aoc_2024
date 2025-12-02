#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"
#define MOVE_COUNT 8

typedef struct {
    int x;
    int y;
} Point;

int solve(FILE *fptr){
    char line[2048];

    static char matrix[1024][1024];
    bool is_valid[1024][1024];

    int y_move[8] = {0, 0, 1, -1, 1, -1, 1, -1};
    int x_move[8] = {1, -1, 0, 0, 1, 1, -1, -1};

    char xmas_c[] = "XMAS";
    int xmas_size = 4;
    int xmas_index_buffer = 0;

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

    Point valid_stack[xmas_size];

    for (int y = 0; y < column_count; y++){
        for (int x = 0; x < line_length; x++){


            for (int i = 0; i < MOVE_COUNT; i++){
                bool good = false;

                for (int xmas_index = 0; xmas_index < xmas_size; xmas_index++){

                    int y_coord = y + (xmas_index * y_move[i]);
                    int x_coord = x + (xmas_index * x_move[i]);

                    valid_stack[xmas_index] = (Point){x_coord, y_coord};

                    if (y_coord < 0
                            || y_coord > column_count
                            || x_coord < 0
                            || x_coord > line_length
                            || matrix[y_coord][x_coord] != xmas_c[xmas_index])
                    {
                        break;
                    }

                    if (xmas_index == xmas_size-1){
                        good = true;
                        result += 1;
                    }
                }

                if (good){
                    for (int valid_index = 0; valid_index < xmas_size; valid_index++){
                        is_valid[valid_stack[valid_index].y][valid_stack[valid_index].x] = true;
                    }
                };
            }
        }
    }

    for (int y = 0; y < column_count; y++){
        for (int x = 0; x < line_length; x++){
            if (is_valid[y][x] == true){
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
