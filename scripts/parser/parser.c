#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 25

int main(int argc, char** argv) {
    if(argc != 2) return 1;

    FILE* fp = fopen(argv[1], "r");
    char buff[MAXLEN] = {0};

    int i = 0;
    int nbytes = 1;
    while((nbytes = fread(buff + i, sizeof(char), 1, fp) > 0)) {
        if(buff[i] == ' ') {
            printf("%s\n", buff);
            memset(buff, 0, MAXLEN);
            i = -1;
        }
        i++;
    }

    return 0;
}
