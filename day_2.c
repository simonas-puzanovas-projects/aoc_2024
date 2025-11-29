#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int solve(FILE *fptr, int size){
    char line[256];

    int safe_count = 0;

    if (fptr != NULL){

        while (fgets(line, sizeof(line), fptr)){

            int number_buffer_count = 0;
            int number_count = 0;
            char number_buffer[256];
            int number_array[256];

            for (int i = 0; i < sizeof(line); i++){

                if (isdigit(line[i])){
                    number_buffer[number_buffer_count] = line[i]; 
                    number_buffer_count += 1;
                }

                else if (line[i] == '\n' || line[i] == '\0' || line[i] == '\r'){
                    number_buffer[number_buffer_count] = '\0';  
                    number_array[number_count] = atoi(number_buffer);
                    number_count += 1;
                    break;
                }

                else if (line[i] == ' '){
                    number_buffer[number_buffer_count] = '\0';  
                    number_array[number_count] = atoi(number_buffer);
                    number_count += 1;
                    number_buffer_count = 0;
                    memset(number_buffer, 0, sizeof(number_buffer));
                }
            }

            bool increasing = false;
            bool is_safe = true;

            if (number_array[1] > number_array[0]){
                increasing = true;
            }

            for (int i = 1; i < number_count; i++){

                if (number_array[i] == number_array[i - 1]){
                    is_safe = false;
                    break;
                }

                else if (number_array[i] > number_array[i - 1] && !increasing){
                    is_safe = false;
                    break;
                }
                else if (number_array[i] < number_array[i - 1] && increasing){
                    is_safe = false;
                    break;
                }
                
                else if (abs(number_array[i] - number_array[i - 1]) > 3){
                    is_safe = false;
                    break;
                }
            } 
            if (!is_safe) continue;

            safe_count += 1; 
        }
    }
    return safe_count;
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
