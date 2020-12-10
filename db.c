#include "db.h"
#include <stdlib.h> 
#include <string.h>

void db_add(database_t *db, student_t s)
{
    strcpy(db->data[db->lsize].fname, s.fname);
    strcpy(db->data[db->lsize].lname, s.lname);
    strcpy(db->data[db->lsize].section, s.section);
    db->data[db->lsize].id = s.id;
    db->data[db->lsize].birthdate.tm_mday = s.birthdate.tm_mday;
    db->data[db->lsize].birthdate.tm_mon = s.birthdate.tm_mon;
    db->data[db->lsize].birthdate.tm_year = s.birthdate.tm_year;

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
    for(int i = last; i < db->lsize; i++){
        strcpy(db->data[i].fname, db->data[i+1].fname);
        strcpy(db->data[i].fname, db->data[i+1].fname);
        strcpy(db->data[i].fname, db->data[i+1].fname);
        db->data[i].id = db->data[i+1].id;
        db->data[i].birthdate.tm_mday = db->data[i+1].birthdate.tm_mday;
        db->data[i].birthdate.tm_mon = db->data[i+1].birthdate.tm_mon;
        db->data[i].birthdate.tm_year = db->data[i+1].birthdate.tm_year;
    }
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