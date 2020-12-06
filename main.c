#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>

#include "db.h"


void handle_sigint(int sig) 
{ 
    printf("\nWaiting for requests to terminate...\n");
    printf("Comitting database changes to the disk...\n");
    printf("Done.\n");
    exit(0);
} 

int main()
{
    signal(SIGINT, handle_sigint); 
    printf("Welcome to the Tiny Database!\n");
    printf("Loading the database...\n");
    database_t db;
    db.lsize = 9;
    db.psize = 10;
    db_init(&db);
    db_load(&db, "tests/data/test_db.bin");

    printf("Done!\n");
    printf("Please enter your requests.\n");
    
    while(1)
    {
        printf("> ");
        char phrase[256];
        fgets(phrase, 256, stdin); 

        clock_t c0 = clock();

        phrase[strcspn(phrase, "\n")] = 0;
        char pl[256];
        strcpy(pl, phrase);
        char* save;
        char* command = strtok_r(phrase, " ", &save);

        char path[256];
        sprintf(path, "logs/%ld-%s.txt", time(0), command);
        

        FILE* fptr;
        if ((fptr = fopen(path,"a")) == NULL){
            printf("Error! opening file");

            // Program exits if the file pointer returns NULL.
            exit(1);
        }
        fprintf(fptr, "Query '%s' completed in ", pl);
        
        
        if(strcmp(command, "select") == 0)
        {
            int numResults = 0;
            char result[1024];
            char* rest = strtok_r(NULL, " ", &save);
            char* save1;
            char* champ = strtok_r(rest, "=", &save1);
            char* valeur = strtok_r(NULL, "=", &save1);
            if(strcmp(champ, "fname") == 0)
            {
                for(int i = 0; i < db.lsize; i++)
                {
                    if(strcmp(db.data[i].fname, valeur) == 0)
                    {
                        numResults++;
                        char pl[256];
                        sprintf(pl, "%u: %s %s in section %s, born on the %d/%d/%d\n", db.data[i].id, db.data[i].fname, db.data[i].lname, db.data[i].section, db.data[i].birthdate.tm_mday, db.data[i].birthdate.tm_mon + 1, db.data[i].birthdate.tm_year + 1900);
                        strcat(result, pl);
                    }
                }
            }
            double diff_ms = (clock() - c0) * 1000. / CLOCKS_PER_SEC;
            fprintf(fptr, " %f ms with %d results.\n%s\n", diff_ms, numResults, result);
        }
        if(strcmp(command, "update") == 0)
        {
            printf("True\n");
        }
        if(strcmp(command, "insert") == 0)
        {
            printf("True\n");
        }
        if(strcmp(command, "delete") == 0)
        {
            printf("True\n");
        }

        fclose(fptr);
    }
    return 0;
}