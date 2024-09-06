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

void add_to_vim_file() {
    char* filename = "test_file.vim";
    FILE* vim_fp = fopen(filename, "w");

    for(int i = 0; i < structs.size; i++) {
        char* text_to_write = MY_ALLOC(2*MAXLEN);
        sprintf(text_to_write, "syntax keyword cType %s\n", (char *)structs.arr[i]);
        fwrite(text_to_write, 1, strnlen(text_to_write, 2*MAXLEN), vim_fp);
        free(text_to_write);
    }

    // TODO: fix sizes
    char linking_text[] = "highlight link cType Type";
    fwrite(linking_text, 1, strnlen(linking_text, 2*MAXLEN), vim_fp);
}

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

    fclose(fp);
}

int find_closing_bracket(int idx) {
    int count = 0;
    char* str = (char *)tokens.arr[idx];
    while(idx < tokens.size && strncmp(str, "}", 1)) {
        str = (char *)tokens.arr[idx+1];
        count++;
        idx++;
    }
    return count;
}

void find_structs() {
    structs = init_vector(5);
    for(int i = 0; i < tokens.size; i++) {
        char* str = (char *)tokens.arr[i];
        if(!strncmp(str, "typedef", TYPEDEF_LEN)) {
            char* struct_name = (char *)tokens.arr[i+2];
            if(!strncmp(struct_name, "{", 1)) {
                struct_name = (char *)tokens.arr[i+find_closing_bracket(i) + 1];
                struct_name[strnlen(struct_name, MAXLEN)-2] = '\0';
            }
            char* allocator = MY_ALLOC(strnlen(str, MAXLEN) + 1); // excludes '\0'
            strncpy(allocator, struct_name, MAXLEN); 
            vector_add(&structs, allocator);
            add_to_vim_file();
        }
    }
}

int main(int argc, char** argv) {
    if(argc != 2) exit(1);

    parse_tokens(argv[1]);
    find_structs();

    free_vector(&tokens);

    if(err_status) {
        perror(FILE_ERROR);   
        exit(2);
    } 

    free_vector(&structs);
    return 0;
}
