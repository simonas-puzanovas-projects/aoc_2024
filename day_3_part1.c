#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"
#define KRED  "\x1B[31m"
#define MUL_SIZE 3

int solve(FILE *fptr, int size){
    char line[1024];

    char mul_chars[] = "mul(";
    int mul_index_buffer = 0;

    bool in_argument = false;
    char argument_buffer[1024];
    int argument_buffer_index = 0;

    int arguments[2] = {0, 0};


    int result = 0;

    if (fptr != NULL){

        while (fgets(line, sizeof(line), fptr)){


            for (int i = 0; i < strlen(line); i++){

                if (in_argument){

                    if (isdigit(line[i])){
                        argument_buffer[argument_buffer_index] = line[i];
                        argument_buffer_index += 1;
                        printf("%s%c",KGRN, line[i]);
                    }

                    else if (line[i] == ',' && argument_buffer_index != 0){
                        argument_buffer[argument_buffer_index] = '\0';
                        arguments[0] = atoi(argument_buffer);
                        argument_buffer_index = 0;
                        memset(argument_buffer, 0, sizeof(argument_buffer));
                        printf("%s%c",KGRN, line[i]);

                    }

                    else if (line[i] == ')' && argument_buffer_index != 0){
                        argument_buffer[argument_buffer_index] = '\0';
                        arguments[1] = atoi(argument_buffer);

                        result += arguments[0]*arguments[1];
                        memset(argument_buffer, 0, sizeof(argument_buffer));
                        argument_buffer_index = 0;
                        in_argument = false;
                        printf(")=%d\n", arguments[0]*arguments[1]);

                    }

                    else{
                        memset(argument_buffer, 0, sizeof(argument_buffer));
                        argument_buffer_index = 0;
                        in_argument = false;
                        printf("%s%c: BAD ONE\n",KRED, line[i]);
                    }
                }

                else{

                    if (line[i] == mul_chars[mul_index_buffer]){
                        mul_index_buffer += 1;
                        printf("%s%c",KGRN, line[i]);
                    }

                    else{
                        mul_index_buffer = 0;
                    }

                    if (mul_index_buffer == 4){
                        mul_index_buffer = 0;
                        in_argument = true;
                    }

                }
            }
        }
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

    printf("\n%sanswer: %d\n",KWHT, solve(fptr, size));

    return 0;

}
