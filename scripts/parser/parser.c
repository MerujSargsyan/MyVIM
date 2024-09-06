#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector.h>

#define MAXLEN 25
#define FILE_ERROR "ERROR: reading file\n"
#define TYPEDEF_LEN 7

vector tokens;
vector structs;
int err_status = 0;

int is_valid_char(char c) {
    if(c == '{' || c == '}') return 1;
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

void print_structs() {
    for(int i = 0; i < structs.size; i++) {
        printf("struct %d: %s\n", i, (char *)structs.arr[i]);
    }
}

void parse_tokens(char* file_name) {
    FILE* fp = fopen(file_name, "r");
    if(!fp) {
        err_status = 1;
        return;
    }

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
}

int find_closing_bracket(int idx) {
    int count = 0;
    char* str = (char *)tokens.arr[idx];
    while(idx < tokens.size && !strncmp(str, "}", 1)) {
        count++;
        idx++;
    }
    printf("found at offset: %d\n", count);
    return count;
}

void find_structs() {
    structs = init_vector(5);
    for(int i = 0; i < tokens.size; i++) {
        char* str = (char *)tokens.arr[i];
        if(!strncmp(str, "typedef", TYPEDEF_LEN)) {
            char* struct_name = (char *)tokens.arr[i+2];
            if(!strncmp(struct_name, "{", 0)) {
                struct_name = (char *)tokens.arr[i+find_closing_bracket(i) + 1];
            }
            char* allocator = MY_ALLOC(strnlen(str, MAXLEN) + 1); // excludes '\0'
            strncpy(allocator, tokens.arr[i+2], MAXLEN); 
            vector_add(&structs, allocator);
        }
    }
}

int main(int argc, char** argv) {
    if(argc != 2) exit(1);

    parse_tokens(argv[1]);
    find_structs();


    if(err_status) {
        perror(FILE_ERROR);   
        exit(2);
    } 

    print_structs();
    print_tokens();
    free_vector(&structs);
    free_vector(&tokens);
    return 0;
}
