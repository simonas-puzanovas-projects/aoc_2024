#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int solve(FILE *fptr, int size){
    char line[256];
    int line_count = 0;
    
    int array0[9999];
    int array1[9999];

    if (fptr != NULL){

        while (fgets(line, sizeof(line), fptr)){
            int number_buffer_count = 0;
            char number_buffer[256];
            bool in_second = false;

            for (int i = 0; i < sizeof(line); i++){

                if (isdigit(line[i])){
                    number_buffer[number_buffer_count] = line[i]; 
                    number_buffer_count += 1;
                }

                else if (line[i] == '\n' || line[i] == '\0' || line[i] == '\r'){
                    array1[line_count] = atoi(number_buffer);
                    break;
                }

                else if (in_second == false && !isdigit(line[i])){
                    in_second = true;
                    array0[line_count] = atoi(number_buffer);
                    memset(number_buffer, 0, 256);
                    number_buffer_count = 0;
                }
            }
            line_count += 1;
        }
    }

    bool checked0[line_count];
    bool checked1[line_count];

    for (int i = 0; i < line_count; i++){
        checked0[i] = false;
        checked1[i] = false;
    }

    int smallest0 = 0;
    int smallest1 = 0;

    int result = 0;

    for (int j = 0; j < line_count; j++){

        for (int i = 0; i < line_count; i++){
            if (checked0[i] == false){
                smallest0 = i;
                break;
            }
        }

        for (int i = 0; i < line_count; i++){
            if (checked1[i] == false){
                smallest1 = i;
                break;
            }
        }

        for (int i = 0; i < line_count; i++){
            if (array0[i] < array0[smallest0] && !checked0[i]){
                smallest0 = i;  
            }
        }
        for (int i = 0; i < line_count; i++){
            if (array1[i] < array1[smallest1] && !checked1[i]){
                smallest1 = i;  
            }
        }

        checked0[smallest0] = true;
        checked1[smallest1] = true;

        int distance = abs(array1[smallest1] - array0[smallest0]);
        print("")
        result += distance;
    }

    return result;
}

int main(){

    FILE *fptr;
    fptr = fopen("input", "r");

    int size;
    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    printf("answer: %d\n", solve(fptr, size));

    return 0;

}
