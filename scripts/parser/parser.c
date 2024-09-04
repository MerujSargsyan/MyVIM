#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define WORDSIZE 25

int main(int argc, char** argv) {
    if(argc != 2) return 1;
    char* file_name1 = argv[1];
    char buffer[WORDSIZE] = {0};

    FILE* fp = fopen(file_name1, "r");
    if(!fp) {
        perror("fopen failed");
        return 2;
    }

    int i = 0;
    int numbytes = 0;
    do {
        while((numbytes = fread(buffer + i, sizeof(char), 1, fp)) > 0 && buffer[i] != ' ') {
            i++;
        }
        printf("%s", buffer);
        memset(buffer, 0, WORDSIZE);
        i = 0;
    } while(numbytes != 0);

    printf("\n");
    return 0;
}
