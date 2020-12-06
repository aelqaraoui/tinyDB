#include "db.h"
#include <stdlib.h> 

void db_add(database_t *db, student_t s)
{
    db->data[db->lsize] = s;
    (db->lsize)++;
}

void db_delete(database_t *db, student_t *s)
{
    int last;
    for(int i = 0; i < db->lsize; i++)
    {
        if(student_equals(&(db->data[i]), s))
            last = i;
    }
    for(int i = last; i < db->lsize; i++)
        db->data[i] = db->data[i+1];
    (db->lsize)--;
}

void db_save(database_t *db, const char *path)
{
    int n;
    FILE *fptr;

    if ((fptr = fopen(path,"wb")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    for(n = 1; n < db->lsize+1; ++n)
    {
        fwrite(&(db->data[n-1]), sizeof(student_t), 1, fptr);
    }
    fclose(fptr);
}

void db_load(database_t *db, const char *path)
{
    int n;
    FILE *fptr;

    if ((fptr = fopen(path,"rb")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    for(n = 1; n < db->lsize+1; ++n)
    {
        fread(&(db->data[n-1]), sizeof(student_t), 1, fptr);
    }
    fclose(fptr);
}

void db_init(database_t *db)
{
    db->data = (student_t *)malloc(db->psize*sizeof(student_t));
}