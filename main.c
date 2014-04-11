/*
 *
 *
 *
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* file_name = "record.txt";

struct information {
    long int id;
    char name[200];
    char type[200];
    double price;
    unsigned int number;
    char company[200];
    char comment[400];
};

struct info_list {
    struct information * node;
    struct info_list * next;
};

void trimmed(char c[])
{
    if (c[strlen(c) - 1] == '\n')
        c[strlen(c) - 1] = '\0';
}
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

int write_to_file(struct information* info)
{
    FILE *file;
    file = fopen(file_name, "a");
    if(!file) {
        printf("\nError!    Cannot Open File %s\n", file_name);
        return 0;
    }
    fputs("\n",file);
    fprintf(file, "%ld\n", info->id);
    fprintf(file, "%s\n", info->name);
    fprintf(file, "%s\n", info->type);
    fprintf(file, "%f\n", info->price);
    fprintf(file, "%d\n", info->number);
    fprintf(file, "%s\n", info->company);
    fprintf(file, "%s\n", info->comment);
    fputs("\n",file);

    fclose(file);
    return 1;
}

struct info_list* read_from_file(struct info_list* list_head)
{
    FILE *file;
    struct information *info = NULL;
    struct info_list *list_next = NULL;
    struct info_list *list_temp = NULL;

    char str[400];
    int flag = 0;
    
    
    file = fopen(file_name, "r");
    if(!file) {
        printf("\nError!    Cannot Open File %s\n", file_name);
        return NULL;
    }
    list_temp = list_head;
    while ((fgets(str, 400, file))!=NULL)
    {
        if (strlen(str) > 1 )
            ++flag;
        else
            continue;

        if (flag > 7)
            flag = 0;
        
        switch(flag)
        {
            case 0:
                break;
            case 1:
                list_next = (struct info_list*)malloc(sizeof(struct info_list));
                info = (struct information*)malloc(sizeof(struct information));
                if (NULL == info || NULL == list_head) {
                    printf("\nError!    Cannot malloc memory\n");
                    return NULL;
                }
                list_next->next = NULL;
                list_next->node = NULL;

                list_temp->node = info;
                list_temp->next = list_next; 
                list_temp = list_next;
                info->id = atol(str);
                break;
            case 2:
                strncpy(info->name, str, 200);
                trimmed(info->name);
                break;
            case 3:
                strncpy(info->type, str, 200);
                trimmed(info->type);
                break;
            case 4:
                info->price = atof(str);
                break;
            case 5:
                info->number = atoi(str);
                break;
            case 6:
                strncpy(info->company, str, 200);
                trimmed(info->company);
                break;
            case 7:
                strncpy(info->comment ,str, 400);
                trimmed(info->comment);
                break;
            default:
                break;
        }
    }

    fclose(file);
    return list_head;

}

void insert_information(struct info_list *list_head)
{
    char id_char[200];
    char price_char[200];
    char number_char[200];
    struct information *info = NULL;
    struct info_list* list_next = NULL;
    struct info_list* list_temp = NULL;

    if (!list_head) {
        list_head = (struct info_list*)malloc(sizeof(struct info_list));
        if (NULL == list_head) {
            printf("\nError!    Cannot malloc memory\n");
            return ;
        }
        list_head->next = NULL;
        list_head->node = NULL;
    }
    list_temp = list_head;
    while (list_temp != NULL && list_temp->node != NULL)
        list_temp = list_temp->next;

    list_next = (struct info_list*)malloc(sizeof(struct info_list));
    info = (struct information*)malloc(sizeof(struct information));
    if (NULL == info || NULL == list_next) {
        printf("\nError!    Cannot malloc memory\n");
        return ;
    }
    list_next->next = NULL;
    list_next->node = info;
    list_temp->next = list_next;
    printf("\nNow Insert a New Data of Devcie.\n");

    printf("Plase Enter ID, only numeral support, for example: \"123456\"\n");
    printf(">>>>");
    fgets(id_char, 200, stdin);
    info->id = atol(id_char);
    printf("You Typed %ld\n", info->id);

    printf("Plase Enter Name, for example: \"Kobe Bryant\"\n");
    printf(">>>>");
    fgets(info->name, 200, stdin);
    trimmed(info->name);
    printf("You Typed %s\n", info->name);
    
    printf("Plase Enter Type, for example: \"A\"\n");
    printf(">>>>");
    fgets(info->type, 200, stdin);
    trimmed(info->type);
    printf("You Typed %s\n", info->type);


    printf("Plase Enter Price, only numeral support, example: \"123.456\"\n");
    printf(">>>>");
    fgets(price_char, 200, stdin);
    info->price = atof(price_char);
    printf("You Typed %f\n", info->price);

    printf("Plase Enter Number, only numeral support, example: \"543210\"\n");
    printf(">>>>");
    fgets(number_char, 200, stdin);
    info->number = atoi(number_char);
    printf("You Typed %u\n", info->number);

    printf("Plase Enter Company, for example: \"Red Had\"\n");
    printf(">>>>");
    fgets(info->company, 200, stdin);
    trimmed(info->company);
    printf("You Typed %s\n", info->company);

    printf("Plase Enter Comment, for example: \"This is Comment\"\n");
    printf(">>>>");
    fgets(info->comment, 400, stdin);
    printf("You Typed %s\n", info->comment);
    trimmed(info->comment);
    write_to_file(info);
}
void list_information(struct info_list * list_head)
{
    struct info_list *list_temp = list_head;
    struct information *temp = NULL;
    while (list_temp != NULL && list_temp->node != NULL) {
        temp = list_temp->node;
        printf("\n ID: %ld", temp->id);
        printf("\t Name: %s", temp->name);
        printf("\t Type %s", temp->type);
        printf("\t Price: %f", temp->price);
        printf("\t Number: %u", temp->number);
        printf("\t Company: %s", temp->company);
        printf("\t Comment: %s", temp->comment);
        
        list_temp = list_temp->next;
    }
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
void select_operator(char operator[100], struct info_list * list_head)
{
    int compare_help = -1;
    int compare_insert = -1;
    int compare_list = -1;
    int compare_delete = -1;
    int compare_search = -1;
    int compare_modify = -1;

/*1.*/
    compare_help = strcmp(operator,"help\n");
    if (0 == compare_help)
        show_help();
/*2.*/
    compare_insert = strcmp(operator, "v\n");
    if (0 == compare_insert)
        insert_information(list_head);
/*3.*/
    compare_list = strcmp(operator, "l\n");
    if (0 == compare_list)
        list_information(list_head);
/*4.*/
    compare_delete = strcmp(operator, "d\n");
    if (0 == compare_delete)
        delete_information();
/*5.*/
    compare_search = strcmp(operator, "s\n");
    if (0 == compare_search)
        search_information();
/*6.*/
    compare_modify = strcmp(operator, "m\n");
    if (0 == compare_modify)
        modify_information();
}
int main(int argc, char** argv)
{
    char operator[100];
    struct info_list * list_head = (struct info_list*)malloc(sizeof(struct info_list));
    if (NULL == list_head) {
        printf("\nError!    Cannot malloc memory\n");
        return ;
    }
    list_head->next = NULL;
    list_head->node = NULL;;
    read_from_file(list_head);
    do{
        printf("\n________________________________________________________________________\n");
        printf("Plese Select Your Operator!    ");
        printf("Type \"help\", for More Information.\n");
        printf("------------------------------------------------------------------------\n");
        printf(">>>>");
        fgets(operator, 100, stdin);
        select_operator(operator, list_head);
        
    } while (strcmp(operator, "q\n") != 0);

    return 0;
}
