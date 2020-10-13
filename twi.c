// twi.c
// Library Organizer
// Organizes data based on
// Title, Date published, or Author in ascending or descending order.

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#define MAX_ENTRY_SIZE 64
#define err(...) fprintf(stderr, __VA_ARGS__)

enum SortType {
    Title,
    Author,
    Date_Published
};

typedef struct {
    char title[MAX_ENTRY_SIZE];
    char author[MAX_ENTRY_SIZE];
    char date[MAX_ENTRY_SIZE];
} Entry;
size_t toff = offsetof(Entry, title);
size_t aoff = offsetof(Entry, author);
size_t doff = offsetof(Entry, date);

Entry* Entries;

// least important <-> most important
// date_published + descending, author + ascending, title + ascending
// 010 101 001
int organizer = 0;
int no = 0;


int cmpfunc(const void* a, const void* b) {
    Entry* e1 = (Entry*)a;
    Entry* e2 = (Entry*)b;
    for(int i = 0; i < no; i++) {
        //printf("%d\n", i);
        int shifted_org = organizer >> (3*i);
        enum SortType curSort = (enum SortType)((shifted_org >> 1) & 3);
        bool curAscending = shifted_org & 1;
        //printf("%d\n", curSort);
        //printf("testing\n");
        //printf("%d\n", curSort);
        //printf("%d\n", curAscending);
        int c;
        int d = (curAscending)?1:-1;
        switch(curSort) {
            case Title:
                //printf("title");
                c = strcmp(e1->title, e2->title); break;
            case Author:
                //printf("author");
                c = strcmp(e1->author, e2->author); break;
            case Date_Published:
                //printf("date");
                c = strcmp(e1->date, e2->date); break;
            //default:
                //printf("what");
        }
        //printf(" %d\n", c);
        if (c != 0) return c * d;
    }
    return 0;
}

bool parseArgs(int argc, char* argv[]) {
    bool tp=false, dp=false, ap=false;
    for(int i = 2; i < argc; i++){
        int entry = 0;
        //printf("%s\n", argv[i]);
        if (argv[i][0] != '-') continue;
        //printf("%c\n", tolower(argv[i][1]));
        switch(tolower(argv[i][1]))
        {
            case 't':
                if (tp) {
                    err("Duplicate categorization");
                    return false;
                }
                tp=true;
                entry = (int)Title;
                break;
            case 'a':
                if (ap) {
                    err("Duplicate categorization");
                    return false;
                }
                ap=true;
                entry = (int)Author;
                break;
            case 'd':
                if (dp) {
                    err("Duplicate categorization");
                    return false;
                }
                dp=true;
                entry = (int)Date_Published;
                break;
            default:
                err("Unknown classifier '%c'", tolower(argv[i][1]));
                return false;
        }
        bool ascending = islower(argv[i][1]); // or
        //int ascending = islower(argv[i][1])&1;
        //printf("%d\n", ascending);
        organizer |= ((entry << 1) | ascending) << (i-2)*3;
        //if(i!=argc-1) organizer <<= 3;
        no++;
    }
    return true;
}

void main(int argc, char* argv[]) {
    if (argc < 3) {
        err("Not enough arguments\n"); 
        return;
    }
    // Load file
    char* filename = argv[1];
    FILE *file;
    if((file = fopen(filename, "r")) == NULL){
        err("Error opening file\n");
        return;
    }
    char* line = NULL;
    int len = 0;
    int num_entries = 0;
    for (char c = getc(file); c != EOF; c = getc(file)) 
        if (c == '\n') // Increment count if this character is newline 
            num_entries++;

    Entries = malloc(sizeof(Entry) * num_entries);

    fseek(file, 0, SEEK_SET); 

    int i = 0;
    while(getline(&line, &len, file) != -1) {
        //printf("line: %s", line);
        sscanf(line, "%[^/]/%[^/]/%[^/]", Entries[i].title, Entries[i].author, Entries[i].date);
        Entries[i].date[strlen(Entries[i].date)-1] = 0; // strip the newline
        //printf("%s\n", Entries[i].title);
        //printf("%s\n", Entries[i].author);
        //printf("%s\n", Entries[i].date);
        i++;
    }

    fclose(file);

    // Parse args -> organizer, no
    if (!parseArgs(argc, argv))
        return;
    
    for (int c = 31; c >= 0; c--)
    {
        int k = organizer >> c;
        if (k & 1)
            printf("1");
        else
            printf("0");
    }
    printf("\n%d\n", no);

    // Sort the data
    qsort(Entries, num_entries, sizeof(Entry), cmpfunc);

    // Output to stdout for now
    for(int i = 0; i < num_entries; i++) {
        printf("%s/%s/%s\n", Entries[i].title, Entries[i].author, Entries[i].date);
    }
}