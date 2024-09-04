#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector.h>

#define MAXLEN 25

vector tokens;

int is_valid_char(char c) {
    if(c < 48 || c > 122) return 0;
    if(c >= 58 && c <= 64) return 0;
    if(c >= 91 && c <= 94) return 0;
    if(c == 96) return 0;
    return 1;
}

void print_tokens() {
    for(int i = 0; i < tokens.size; i++) {
        printf("token %d: %s\n", i, (char *)tokens.arr[i]);
    }
}

int main(int argc, char** argv) {
    if(argc != 2) return 1;

    FILE* fp = fopen(argv[1], "r");
    char buff[MAXLEN] = {0};

    tokens = init_vector(MAXLEN);

    int i = 0;
    int nbytes = 1;
    while((nbytes = fread(buff + i, sizeof(char), 1, fp) > 0)) {
        if(buff[i] == ' ' || buff[i] == '\n') {
            if(is_valid_char(buff[0]))  {
                char* allocator = MY_ALLOC(strnlen(buff, MAXLEN) + 1); // excludes '\0'
                strncpy(allocator, buff, MAXLEN); 
                vector_add(&tokens, allocator);
            }

            memset(buff, 0, MAXLEN);
            i = -1;
        }
        i++;
    }

    print_tokens();
    free_vector(&tokens);
    return 0;
}
