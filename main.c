/*
 *
 *
 *
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct information{
    long id;
    char name[200];
    char type[200];
    double price;
    unsigned int number;
    char company[200];
    char comment[400];
};

void show_help()
{
    printf("This is Help Page!\n");
    printf("Type \"q\", Quit \n");
    printf("Type \"v\", Insert Data of Device \n");
    printf("Type \"l\", Show All Data, default order by ID\n");
    printf("Type \"lid\", Show Data order by Id\n");
    printf("Type \"lname\", Show Data order by Name\n");
    printf("Type \"lprice\", Show Data order by Price\n");
    printf("\n");

}

void insert_information()
{
    printf("\nNow Insert a New Data of Devcie.\n");
    printf("Plase Enter ID, only numeral support, example: \"123456\"\n");
    printf(">>>>");
    long id = 0;
    char id_char[200];
    fgets(id_char, 200, stdin);
    id = atol(id_char);
    printf("You Typed %ld\n", id);
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
void select_operator(char operator[100])
{
    int compare_help = strcmp(operator,"help\n");
    if (0 == compare_help)
        show_help();
    int compare_insert = strcmp(operator, "v\n");
    if (0 == compare_insert)
        insert_information();
    int compare_list = strcmp(operator, "l\n");
    if (0 == compare_list)
        list_information();
    int compare_delete = strcmp(operator, "d\n");
    if (0 == compare_delete)
        delete_information();      
    int compare_search = strcmp(operator, "s\n");
    if (0 == compare_search)
        search_information();
    int compare_modify = strcmp(operator, "m\n");
    if (0 == compare_modify)
        modify_information();
}
int main(int argc, char** argv)
{
    char operator[100];
    do{
        printf("\n________________________________________________________________________\n");
        printf("Plese Select Your Operator!    ");
        printf("Type \"help\", for More Information.\n");
        printf("------------------------------------------------------------------------\n");
        printf(">>>>");
        fgets(operator, 100, stdin);
        select_operator(operator);
        
    } while (strcmp(operator, "q\n") != 0);

    return 0;
}
