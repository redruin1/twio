// testdata_generator.c
// Generates a bunch of data conformat to twio.c's specifications

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_ENTRIES 1000

int randrange(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

void rand_str(char* dest, size_t len) {
    char charset[] = "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while(len-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}

void main() {
    FILE* file;
    if((file = fopen("randomdata.txt", "w"))==NULL){
        fprintf(stderr, "Error opening file");
        return;
    }
    
    for(int i = 0; i < NUM_ENTRIES; i++){
        // The maximum number of characters for each string entry within twio.c 
        // is 64, so book titles and their authors cannot exceed this length.
        char title[64];
        char author[64];
        char date[64];

        rand_str(title, 1);
        rand_str(author, 1);
        sprintf(date, "%04d.%02d.%02d.%02d:%02d", 
            randrange(0, 9999), 
            randrange(1, 12), 
            randrange(0, 23), 
            randrange(0, 23), 
            randrange(0, 59));

        fprintf(file, "%s/%s/%s\n", title, author, date);
    }

    fclose(file);
}