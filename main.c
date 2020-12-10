#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "db.h"

database_t db;

void handle_sigint(int sig) 
{ 
    printf("\nWaiting for requests to terminate...\n");
    printf("Comitting database changes to the disk...\n");
    db_save(&db, "tests/data/out_db.bin");
    printf("Done.\n");
    exit(0);
} 

void set(student_t* s, char* champ, char* valeur)
{
    if(strcmp(champ, "id") == 0)
    {
        s->id = (unsigned int)atoi(valeur);   
    }
    if(strcmp(champ, "fname") == 0)
    {
        strcpy(s->fname, valeur);   
    }
    if(strcmp(champ, "lname") == 0)
    {
        strcpy(s->lname, valeur);
    }
    if(strcmp(champ, "section") == 0)
    {
        strcpy(s->section, valeur);
    }
    if(strcmp(champ, "birthdate") == 0)
    {
        char* save2;
        s->birthdate.tm_mday = atoi(strtok_r(valeur, "/", &save2));
        s->birthdate.tm_mon = atoi(strtok_r(NULL, "/", &save2)) - 1;
        s->birthdate.tm_year = atoi(strtok_r(NULL, "/", &save2)) - 1900;
    }
}

int main(int argc, char* argv[])
{
    signal(SIGINT, handle_sigint); 

    db.lsize = 9;
    db.psize = 100;
    db_init(&db);
    db_load(&db, "tests/data/test_db.bin");

    printf("Welcome to the Tiny Database!\n");
    if(isatty(0))
    {
        printf("Loading the database...\n");
    }
    printf("Please enter your requests.\n");
    if(isatty(0))
    {
        printf("> ");
    }
    char phrase[256];

    while(fgets(phrase, 256, stdin) != NULL)
    {

        clock_t c0 = clock();

        phrase[strcspn(phrase, "\n")] = 0;
        char pl[256];
        strcpy(pl, phrase);

        if(!isatty(0))
            printf("Running query '%s'\n", pl);
            
        char* save;
        char* command = strtok_r(phrase, " ", &save);
        
        

        char path[256];
        sprintf(path, "logs/%ld-%s.txt", time(0), command);
        

        if(isatty(0))
        {
            printf("%s\n", path);
        }
        
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
            memset(result, 0, sizeof result);
            char* rest = strtok_r(NULL, " ", &save);
            char* save1;
            char* champ = strtok_r(rest, "=", &save1);
            char* valeur = strtok_r(NULL, "=", &save1);
            if(strcmp(champ, "id") == 0)
            {
                for(int i = 0; i < db.lsize; i++)
                {
                    if((int)(db.data[i].id) == atoi(valeur))
                    {
                        numResults++;
                        char pl[256];
                        sprintf(pl, "%u: %s %s in section %s, born on the %d/%d/%d\n", db.data[i].id, db.data[i].fname, db.data[i].lname, db.data[i].section, db.data[i].birthdate.tm_mday, db.data[i].birthdate.tm_mon + 1, db.data[i].birthdate.tm_year + 1900);
                        strcat(result, pl);
                    }
                }
            }
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
            if(strcmp(champ, "lname") == 0)
            {
                for(int i = 0; i < db.lsize; i++)
                {
                    if(strcmp(db.data[i].lname, valeur) == 0)
                    {
                        numResults++;
                        char pl[256];
                        sprintf(pl, "%u: %s %s in section %s, born on the %d/%d/%d\n", db.data[i].id, db.data[i].fname, db.data[i].lname, db.data[i].section, db.data[i].birthdate.tm_mday, db.data[i].birthdate.tm_mon + 1, db.data[i].birthdate.tm_year + 1900);
                        strcat(result, pl);
                    }
                }
            }
            if(strcmp(champ, "section") == 0)
            {
                for(int i = 0; i < db.lsize; i++)
                {
                    if(strcmp(db.data[i].section, valeur) == 0)
                    {
                        numResults++;
                        char pl[256];
                        sprintf(pl, "%u: %s %s in section %s, born on the %d/%d/%d\n", db.data[i].id, db.data[i].fname, db.data[i].lname, db.data[i].section, db.data[i].birthdate.tm_mday, db.data[i].birthdate.tm_mon + 1, db.data[i].birthdate.tm_year + 1900);
                        strcat(result, pl);
                    }
                }
            }
            if(strcmp(champ, "birthdate") == 0)
            {
                char* save2;
                int day = atoi(strtok_r(valeur, "/", &save2));
                int month = atoi(strtok_r(NULL, "/", &save2));
                int year = atoi(strtok_r(NULL, "/", &save2));
                for(int i = 0; i < db.lsize; i++)
                {
                    if(db.data[i].birthdate.tm_mday == day && db.data[i].birthdate.tm_mon == (month-1) && db.data[i].birthdate.tm_year == (year-1900) )
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
        else if(strcmp(command, "update") == 0)
        {
            int numResults = 0;
            char result[1024];
            memset(result, 0, sizeof result);
            char* rest = strtok_r(NULL, " ", &save);
            char* save1;
            char* filtre = strtok_r(rest, "=", &save1);
            char* valeur = strtok_r(NULL, "=", &save1);

            strtok_r(NULL, " ", &save);
            rest = strtok_r(NULL, " ", &save);
            char* save2;
            char* champ_modifie = strtok_r(rest, "=", &save2);
            char* valeur_modifie = strtok_r(NULL, "=", &save2);
            
            if(strcmp(filtre, "id") == 0)
            {
                for(int i = 0; i < db.lsize; i++)
                {
                    if((int)(db.data[i].id) == atoi(valeur))
                    {
                        char plvaleur[256];
                        strcpy(plvaleur, valeur_modifie);
                        set(&(db.data[i]), champ_modifie, plvaleur);
                        numResults++;
                        char pl[256];
                        sprintf(pl, "%u: %s %s in section %s, born on the %d/%d/%d\n", db.data[i].id, db.data[i].fname, db.data[i].lname, db.data[i].section, db.data[i].birthdate.tm_mday, db.data[i].birthdate.tm_mon + 1, db.data[i].birthdate.tm_year + 1900);
                        strcat(result, pl);
                    }
                }
            }
            if(strcmp(filtre, "fname") == 0)
            {
                for(int i = 0; i < db.lsize; i++)
                {
                    if(strcmp(db.data[i].fname, valeur) == 0)
                    {
                        char plvaleur[256];
                        strcpy(plvaleur, valeur_modifie);
                        set(&(db.data[i]), champ_modifie, plvaleur);
                        numResults++;
                        char pl[256];
                        sprintf(pl, "%u: %s %s in section %s, born on the %d/%d/%d\n", db.data[i].id, db.data[i].fname, db.data[i].lname, db.data[i].section, db.data[i].birthdate.tm_mday, db.data[i].birthdate.tm_mon + 1, db.data[i].birthdate.tm_year + 1900);
                        strcat(result, pl);
                    }
                }
            }
            if(strcmp(filtre, "lname") == 0)
            {
                for(int i = 0; i < db.lsize; i++)
                {
                    if(strcmp(db.data[i].lname, valeur) == 0)
                    {
                        char plvaleur[256];
                        strcpy(plvaleur, valeur_modifie);
                        set(&(db.data[i]), champ_modifie, plvaleur);
                        numResults++;
                        char pl[256];
                        sprintf(pl, "%u: %s %s in section %s, born on the %d/%d/%d\n", db.data[i].id, db.data[i].fname, db.data[i].lname, db.data[i].section, db.data[i].birthdate.tm_mday, db.data[i].birthdate.tm_mon + 1, db.data[i].birthdate.tm_year + 1900);
                        strcat(result, pl);
                    }
                }
            }
            if(strcmp(filtre, "section") == 0)
            {
                for(int i = 0; i < db.lsize; i++)
                {
                    if(strcmp(db.data[i].section, valeur) == 0)
                    {
                        char plvaleur[256];
                        strcpy(plvaleur, valeur_modifie);
                        set(&(db.data[i]), champ_modifie, plvaleur);
                        numResults++;
                        char pl[256];
                        sprintf(pl, "%u: %s %s in section %s, born on the %d/%d/%d\n", db.data[i].id, db.data[i].fname, db.data[i].lname, db.data[i].section, db.data[i].birthdate.tm_mday, db.data[i].birthdate.tm_mon + 1, db.data[i].birthdate.tm_year + 1900);
                        strcat(result, pl);
                    }
                }
            }
            if(strcmp(filtre, "birthdate") == 0)
            {
                char* save3;
                int day = atoi(strtok_r(valeur, "/", &save3));
                int month = atoi(strtok_r(NULL, "/", &save3));
                int year = atoi(strtok_r(NULL, "/", &save3));
                
                
                for(int i = 0; i < db.lsize; i++)
                {
                    if(db.data[i].birthdate.tm_mday == day && db.data[i].birthdate.tm_mon == (month-1) && db.data[i].birthdate.tm_year == (year-1900) )
                    {
                        char plvaleur[256];
                        strcpy(plvaleur, valeur_modifie);
                        set(&(db.data[i]), champ_modifie, plvaleur);
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
        else if(strcmp(command, "insert") == 0)
        {
            int numResults = 1;
            char result[1024];
            memset(result, 0, sizeof result);

            student_t spl;
            strcpy(spl.fname, strtok_r(NULL, " ", &save));
            strcpy(spl.lname, strtok_r(NULL, " ", &save));
            spl.id = (unsigned int)atoi(strtok_r(NULL, " ", &save));
            strcpy(spl.section, strtok_r(NULL, " ", &save));
            char* birthdate = strtok_r(NULL, " ", &save);

            char* save2;
            spl.birthdate.tm_mday = atoi(strtok_r(birthdate, "/", &save2));
            spl.birthdate.tm_mon = atoi(strtok_r(NULL, "/", &save2)) - 1;
            spl.birthdate.tm_year = atoi(strtok_r(NULL, "/", &save2)) - 1900;
            
            db_add(&db, spl);
            
            char pl[256];
            sprintf(pl, "%u: %s %s in section %s, born on the %d/%d/%d\n", spl.id, spl.fname, spl.lname, spl.section, spl.birthdate.tm_mday, spl.birthdate.tm_mon + 1, spl.birthdate.tm_year + 1900);
            strcat(result, pl);
            
            double diff_ms = (clock() - c0) * 1000. / CLOCKS_PER_SEC;
            fprintf(fptr, " %f ms with %d results.\n%s\n", diff_ms, numResults, result);
        }
        else if(strcmp(command, "delete") == 0)
        {
            int numResults = 0;
            char result[1024];
            memset(result, 0, sizeof result);
            char* rest = strtok_r(NULL, " ", &save);
            char* save1;
            char* champ = strtok_r(rest, "=", &save1);
            char* valeur = strtok_r(NULL, "=", &save1);

            int deleted = 1;
            while(deleted == 1)
            {
                deleted = 0;
                
                if(strcmp(champ, "id") == 0)
                {
                    for(int i = 0; i < db.lsize; i++)
                    {
                        if((int)(db.data[i].id) == atoi(valeur))
                        {
                            numResults++;
                            char pl[256];
                            sprintf(pl, "%u: %s %s in section %s, born on the %d/%d/%d\n", db.data[i].id, db.data[i].fname, db.data[i].lname, db.data[i].section, db.data[i].birthdate.tm_mday, db.data[i].birthdate.tm_mon + 1, db.data[i].birthdate.tm_year + 1900);
                            strcat(result, pl);
                            db_delete(&db, &(db.data[i]));
                            deleted = 1;
                        }
                    }
                }
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
                            db_delete(&db, &(db.data[i]));
                            deleted = 1;
                        }
                    }
                }
                if(strcmp(champ, "lname") == 0)
                {
                    for(int i = 0; i < db.lsize; i++)
                    {
                        if(strcmp(db.data[i].lname, valeur) == 0)
                        {
                            numResults++;
                            char pl[256];
                            sprintf(pl, "%u: %s %s in section %s, born on the %d/%d/%d\n", db.data[i].id, db.data[i].fname, db.data[i].lname, db.data[i].section, db.data[i].birthdate.tm_mday, db.data[i].birthdate.tm_mon + 1, db.data[i].birthdate.tm_year + 1900);
                            strcat(result, pl);
                            db_delete(&db, &(db.data[i]));
                            deleted = 1;
                        }
                    }
                }
                if(strcmp(champ, "section") == 0)
                {
                    for(int i = 0; i < db.lsize; i++)
                    {
                        if(strcmp(db.data[i].section, valeur) == 0)
                        {
                            numResults++;
                            char pl[256];
                            sprintf(pl, "%u: %s %s in section %s, born on the %d/%d/%d\n", db.data[i].id, db.data[i].fname, db.data[i].lname, db.data[i].section, db.data[i].birthdate.tm_mday, db.data[i].birthdate.tm_mon + 1, db.data[i].birthdate.tm_year + 1900);
                            strcat(result, pl);
                            db_delete(&db, &(db.data[i]));
                            deleted = 1;
                        }
                    }
                }
                if(strcmp(champ, "birthdate") == 0)
                {
                    char plvaleur[256];
                    strcpy(plvaleur, valeur);
                    char* save2;
                    int day = atoi(strtok_r(plvaleur, "/", &save2));
                    int month = atoi(strtok_r(NULL, "/", &save2));
                    int year = atoi(strtok_r(NULL, "/", &save2));
                    
                    for(int i = 0; i < db.lsize; i++)
                    {
                        if(db.data[i].birthdate.tm_mday == day && db.data[i].birthdate.tm_mon == (month-1) && db.data[i].birthdate.tm_year == (year-1900) )
                        {
                            numResults++;
                            char pl[256];
                            sprintf(pl, "%u: %s %s in section %s, born on the %d/%d/%d\n", db.data[i].id, db.data[i].fname, db.data[i].lname, db.data[i].section, db.data[i].birthdate.tm_mday, db.data[i].birthdate.tm_mon + 1, db.data[i].birthdate.tm_year + 1900);
                            strcat(result, pl);
                            db_delete(&db, &(db.data[i]));
                            deleted = 1;
                        }
                    }
                }
            }
            double diff_ms = (clock() - c0) * 1000. / CLOCKS_PER_SEC;
            fprintf(fptr, " %f ms with %d results.\n%s\n", diff_ms, numResults, result);
        }

        fclose(fptr);
        
        if(isatty(0))
            printf("> ");
        
    }
    db_save(&db, "tests/data/out_db.bin");

    printf("\nWaiting for requests to terminate...\n");
    printf("Comitting database changes to the disk...\n");
    printf("Done.\n");
    return 0;
}