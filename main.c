/*
 *
 *
 *
 * */

#include <stdio.h>
#include <string.h>
struct information{
    int id;
    char name[200];
    char type[200];
    double price;
    unsigned int number;
    char company[200];
    char comment[400];
};

void insert_information()
{
}
void list_information()
{
}
void delete_information()
{
}
void search_information()
{
}
void modify_information()
{
}
int main(int argc, char** argv)
{
    char select[100];
    do{
        printf("Plese Select Your Operator!\n");
        fgets(select, 100, stdin);
        int compare_insert = strcmp(select, "v\n");
        if (0 == compare_insert)
            insert_information();
        int compare_list = strcmp(select, "l\n");
        if (0 == compare_list)
            list_information();
        int compare_delete = strcmp(select, "d\n");
        if (0 == compare_delete)
            delete_information();      
        int compare_search = strcmp(select, "s\n");
        if (0 == compare_search)
            search_information();
        int compare_modify = strcmp(select, "m\n");
        if (0 == compare_modify)
            modify_information();
        
    } while (strcmp(select, "q\n") != 0);

    return 0;
}
