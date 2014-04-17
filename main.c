/*
 *
 *
 *
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const char* file_name = "record.txt";

/* 信息结构体 */
struct Information {
    long int id;
    char name[200];
    char type[200];
    double price;
    unsigned int number;
    char company[200];
    char comment[400];
};

/* 链表结构体 */
struct Info_list {
    struct Information * node;
    struct Info_list * next;
};

/* 结构体字段枚举值 */
enum InfoType{
    NONE = 0,
    ID = 1,
    NAME = 2,
    TYPE = 3,
    PRICE = 4,
    NUMBER = 5,
    COMPANY = 6,
    COMMENT = 7,
    ALL = 8
};

/* 去掉字符串两端的空白字符 */
char* trimmed(char * c)
{
    char* end = NULL;
    if (NULL == c)
        return c;
    
    end = c + strlen(c) - 1;
    
    while (*c && isspace(*c)) {
        c++;
    }
    while (*end && end >= c && isspace(*end)) {
        *end-- = '\0';
    }
    return c;
}

/* 显示所有支持的命令 */
void show_help()
{
    printf("This is Help Page!\n");
    printf("Type \"q\", Quit \n");
    printf("Type \"i\", Insert Data of Device \n");
    printf("Type \"d\", Delete Data \n");
    printf("Type \"m\", Modify Data \n");
    printf("\n");
    
    printf("Type \"l\", Show All Data, default order by time\n");
    printf("Type \"lid\", Show Data order by Id\n");
    printf("Type \"lname\", Show Data order by Name\n");
    printf("Type \"ltype\", Show Data order by Type\n");
    printf("Type \"lprice\", Show Data order by Price\n");
    printf("Type \"lnumber\", Show Data order by Number\n");
    printf("Type \"lcompany\", Show Data order by Company\n");
    printf("Type \"lcomment\", Show Data order by Comment\n");
    printf("\n");
    
    printf("Type \"s\", Search Data, default support fuzzy search\n");
    printf("Type \"sid\", Search Data by Id\n");
    printf("Type \"sname\", Search Data by Name\n");
    printf("Type \"stype\", Search Data by Type\n");
    printf("Type \"sprice\", Search Data by Price\n");
    printf("Type \"snumber\", Search Data by Number\n");
    printf("Type \"scompany\", Search Data by Company\n");
    printf("Type \"scomment\", Search Data by Comment\n");
    
    printf("\n");
    
}

/* 向文件末尾添加结构体信息 */
int write_info_to_file(struct Information* info)
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

/* 将整个链表重新保存文件 */
int write_list_to_file(struct Info_list* list_head)
{
    struct Info_list * list_iter = list_head->next;
    
    /* 删除文件所有内容 */
    FILE *file;
    file = fopen(file_name, "w");
    if(!file) {
        printf("\nError!    Cannot Open File %s\n", file_name);
        return 0;
    }
    fclose(file);

    /* 循环保存链表中得每一个结构体到文件 */
    while (list_iter && list_iter->node) {
        write_info_to_file(list_iter->node);
        list_iter = list_iter->next;
    }
    
    return 1;
}

/* 读取文件所有数据，并保存到链表当中 */
struct Info_list* read_from_file(struct Info_list* list_first)
{
    FILE *file;
    struct Information *info = NULL;
    struct Info_list *list_next = NULL;
    struct Info_list *list_temp = NULL;
    
    char str[400];
    int flag = 0;
    
    file = fopen(file_name, "r");
    if(!file) {
        printf("\nError!    Cannot Open File %s\n", file_name);
        return NULL;
    }
    list_temp = list_first;
    while ((fgets(str, 400, file))!=NULL)
    {
        if (strlen(str) > 1 )
            ++flag;
        else
            continue;
        
        if (flag > 7) {
            flag = 1;
        }
        
        switch(flag)
        {
            case 0:
                break;
            case 1:
                list_next = (struct Info_list*)malloc(sizeof(struct Info_list));
                info = (struct Information*)malloc(sizeof(struct Information));
                if (NULL == info || NULL == list_first) {
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
                trimmed(info->name);    /* 这里的trimmed函数没有返回值，意味着只能去掉末尾的空白 */
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
    return list_first;
}

/* 执行插入数据命令 */
void insert_information(struct Info_list *list_head)
{
    char id_char[200];
    char price_char[200];
    char number_char[200];
    struct Information *info = NULL;
    struct Info_list* list_next = NULL;
    struct Info_list* list_temp = NULL;
/*
    if (!list_head) {
        list_head = (struct Info_list*)malloc(sizeof(struct Info_list));
        if (NULL == list_head) {
            printf("\nError!    Cannot malloc memory\n");
            return ;
        }
        list_head->next = NULL;
        list_head->node = NULL;
    }
*/
    list_temp = list_head->next;
    while (list_temp != NULL && list_temp->node != NULL)
        list_temp = list_temp->next;
    
    list_next = (struct Info_list*)malloc(sizeof(struct Info_list));
    info = (struct Information*)malloc(sizeof(struct Information));
    if (NULL == info || NULL == list_next) {
        printf("\nError!    Cannot malloc memory\n");
        return ;
    }
    list_next->next = NULL;
    list_next->node = NULL;
    list_temp->next = list_next;
    list_temp->node = info;
    printf("\nNow Insert a New Data of Devcie.\n");
    
    printf("Plase Enter ID, only numeral support, for example: \"123456\"\n");
    printf(">>>> ");
    fgets(id_char, 200, stdin);
    info->id = atol(id_char);
    printf("You Typed %ld\n", info->id);
    
    printf("Plase Enter Name, for example: \"Kobe Bryant\"\n");
    printf(">>>> ");
    fgets(info->name, 200, stdin);
    trimmed(info->name);
    printf("You Typed %s\n", info->name);
    
    printf("Plase Enter Type, for example: \"A\"\n");
    printf(">>>> ");
    fgets(info->type, 200, stdin);
    trimmed(info->type);
    printf("You Typed %s\n", info->type);
    
    printf("Plase Enter Price, only numeral support, example: \"123.456\"\n");
    printf(">>>> ");
    fgets(price_char, 200, stdin);
    info->price = atof(price_char);
    printf("You Typed %f\n", info->price);
    
    printf("Plase Enter Number, only numeral support, example: \"543210\"\n");
    printf(">>>> ");
    fgets(number_char, 200, stdin);
    info->number = atoi(number_char);
    printf("You Typed %u\n", info->number);
    
    printf("Plase Enter Company, for example: \"Red Had\"\n");
    printf(">>>> ");
    fgets(info->company, 200, stdin);
    trimmed(info->company);
    printf("You Typed %s\n", info->company);
    
    printf("Plase Enter Comment, for example: \"This is Comment\"\n");
    printf(">>>> ");
    fgets(info->comment, 400, stdin);
    printf("You Typed %s\n", info->comment);
    trimmed(info->comment);
    write_info_to_file(info);
}

/* 按插入的日期显示所有数据 */
void list_information(struct Info_list * list_head)
{
    struct Info_list *list_temp = list_head->next;
    struct Information *temp = NULL;
    while (list_temp != NULL && list_temp->node != NULL) {
        temp = list_temp->node;
        printf("\n ID: %ld", temp->id);
        printf("\t Name: %s", temp->name);
        printf("\t Type %s", temp->type);
        printf("\t Price: %.2f", temp->price);
        printf("\t Number: %u", temp->number);
        printf("\t Company: %s", temp->company);
        printf("\t Comment: %s\n", temp->comment);
        
        list_temp = list_temp->next;
    }
}

/* 按相应的排序方法显示数据 */
void list_information_order(struct Info_list * list_head, const char* which)
{
    struct Info_list * list_temp = list_head->next;
    struct Info_list * swap_temp = NULL;
    struct SortHelp
    {
        struct Info_list* node;
        int flag;
        struct SortHelp *next;
    };
    struct SortHelp *sort_head = NULL;
    struct SortHelp *sort_iter = NULL;
    struct SortHelp *sort_one = NULL;
    struct SortHelp *sort_min = NULL;
    struct SortHelp *sort_temp = NULL;
    
    struct Information * info_temp = NULL;
    int sort_num = 0;
    int i = 0;
    int j = 0;
    
    /* 新建链表保存原链表的信息 */
    /* copy Info_list to SortHelp */
    while(list_temp && list_temp->node != NULL ) {
        
        sort_one = (struct SortHelp *)malloc(sizeof(struct SortHelp));
        if (NULL == sort_one) {
            printf("\nError!    Cannot malloc memory\n");
            /* 如果申请内存失败，在函数返回前需要释放已申请的内存，防止内存泄露 */
            sort_iter = sort_head;
            while (sort_iter) {
                sort_temp = sort_iter;
                sort_iter = sort_iter->next;
                free(sort_temp);
            }
            return ;
        }
        sort_one->node = list_temp;
        sort_one->flag = 0;    /* 0 meaning nothing*/
        sort_one->next = NULL;
        
        if (NULL == sort_head) {
            sort_head = sort_one;
            sort_iter = sort_head;
        } else {
            sort_iter->next = sort_one;
            sort_iter = sort_iter->next;
        }
        
        list_temp = list_temp->next;
        ++sort_num;
    }
    
    /* 冒泡排序 */
    for (i = sort_num; i > 0; --i) {
        sort_iter = sort_head;
        
        /* 跳过前面的已经排过序的结点 */
        /* jump have sort node */
        for (j = 0; j < sort_num - i; ++j) {
            sort_iter = sort_iter->next;
        }
        sort_temp = sort_iter;
        
        /* 按照一定规则，找到数值最小的结点 */
        /* selet min node, and move to head in linked list */
        sort_min = sort_iter;
        while(sort_iter) {
            if (0 == sort_iter->flag) {
                if (0 == strcmp(which, "id")) {
                    if (sort_iter->node->node->id < sort_min->node->node->id)
                        sort_min = sort_iter;
                } else if (0 == strcmp(which, "name")) {
                    if (strcmp(sort_iter->node->node->name , sort_min->node->node->name) < 0)
                        sort_min = sort_iter;
                } else if (0 == strcmp(which, "price")) {
                    if (sort_iter->node->node->price < sort_min->node->node->price)
                        sort_min = sort_iter;
                } else if (0 == strcmp(which, "type")) {
                    if (strcmp(sort_iter->node->node->type , sort_min->node->node->type) < 0)
                        sort_min = sort_iter;
                } else if (0 == strcmp(which, "company")) {
                    if (strcmp(sort_iter->node->node->company , sort_min->node->node->company) < 0)
                        sort_min = sort_iter;
                } else if (0 == strcmp(which, "comment")) {
                    if (strcmp(sort_iter->node->node->comment , sort_min->node->node->comment) < 0)
                        sort_min = sort_iter;
                } else if (0 == strcmp(which, "number")) {
                    if (sort_iter->node->node->number < sort_min->node->node->number)
                        sort_min = sort_iter;
                }

            }
            sort_iter = sort_iter->next;
        }
        (sort_min->flag)++;
        
        /* 将找到的最小结点与第一个无序的结点交换位置 */
        swap_temp = sort_min->node;
        sort_min->node = sort_temp->node;
        sort_temp->node = swap_temp;
    }

    /* 将排序后的链表中得数据输出，并释放内存，防止内存泄露 */
    sort_iter = sort_head;
    while(sort_iter) {
        info_temp = sort_iter->node->node;
        printf("\n id: %ld", info_temp->id);
        printf("\t name: %s", info_temp->name);
        printf("\t type: %s", info_temp->type);
        printf("\t price: %.2f", info_temp->price);
        printf("\t Number: %u", info_temp->number);
        printf("\n  Company: %s", info_temp->company);
        printf("  Comment: %s\n", info_temp->comment);
        sort_temp = sort_iter;
        sort_iter = sort_iter->next;
        free(sort_temp);
    }
    
}

/* 从链表中删除指定ID的记录 */
void delete_id_in_list(struct Info_list * list_head, long int id)
{
    struct Info_list * list_iter = list_head->next;
    struct Info_list * list_pre = list_head;
    struct Information * info = NULL;
    
    while (list_iter && list_iter->node) {
        
        info = list_iter->node;
        if (info->id == id) {
            free(info);
            list_iter->node = NULL;
            
            /* 释放当前内存，指针回退 */
            list_pre->next = list_iter->next;
            free(list_iter);
            list_iter = list_pre;
        }
        list_pre = list_iter;
        list_iter = list_iter->next;
    }
    
}

/* 删除指定的记录 */
void delete_information(struct Info_list * list_head)
{
    char condition[100];
    char * trimmed_condition = NULL;
    long int id;
    printf("Enter ID which you want delete. \n>>>> ");
    fgets(condition, 100, stdin);
    trimmed_condition = trimmed(condition);
    id = atol(trimmed_condition);
    
    delete_id_in_list(list_head, id);
    
    /* 保存 */
    write_list_to_file(list_head);
}


/* 查找数据 */
void search_information(struct Info_list * list_head, enum InfoType type)
{
    enum HaveInfo {
        HAVE = 1,
        UNHAVE = 2
    };
    struct Info_list * list_iter = list_head->next;
    char condition[100];
    char char_id[100];
    char char_price[100];
    char char_number[100];
    char * trimmed_condition = NULL;
    struct Information * info = NULL;
    enum HaveInfo is_have = UNHAVE;
    if (ALL == type) {
        printf("Enter your condition below. (support fuzzy search) \n>>>> ");
    } else
        printf("Enter your condition below. \n>>>> ");
    fgets(condition, 100, stdin);
    trimmed_condition = trimmed(condition);
    while (list_iter && list_iter->node) {
        info = list_iter->node;
        is_have = UNHAVE;
        sprintf(char_id, "%ld", info->id);
        sprintf(char_price, "%f", info->price);
        sprintf(char_number, "%u", info->number);
        switch (type) {
            case ALL:
                if( strstr(char_id, trimmed_condition)
                   || strstr(info->name, trimmed_condition)
                   || strstr(info->type, trimmed_condition)
                   || strstr(char_price, trimmed_condition)
                   || strstr(char_number, trimmed_condition)
                   || strstr(info->company, trimmed_condition)
                   || strstr(info->comment, trimmed_condition)
                   )
                    is_have = HAVE;
                break;
            case ID:
                if( strstr(char_id, trimmed_condition))
                    is_have = HAVE;
                break;
            case NAME:
                if( strstr(info->name, trimmed_condition))
                    is_have = HAVE;
                break;
            case TYPE:
                if( strstr(info->type, trimmed_condition))
                    is_have = HAVE;
                break;
            case PRICE:
                if( strstr(char_price, trimmed_condition))
                    is_have = HAVE;
                break;
            case NUMBER:
                if( strstr(char_number, trimmed_condition))
                    is_have = HAVE;
                break;
            case COMPANY:
                if( strstr(info->company, trimmed_condition))
                    is_have = HAVE;
                break;
            case COMMENT:
                if( strstr(info->comment, trimmed_condition))
                    is_have = HAVE;
                break;
                
            default:
                is_have = UNHAVE;
                break;
        }
        if( HAVE == is_have) {
            printf("\n ID: %ld", info->id);
            printf("\t Name: %s", info->name);
            printf("\t Type %s", info->type);
            printf("\t Price: %.2f", info->price);
            printf("\t Number: %u", info->number);
            printf("\t Company: %s", info->company);
            printf("\t Comment: %s\n", info->comment);
        }
        list_iter = list_iter->next;
    }
    
}


void modify_information(struct Info_list * list_head)
{
    struct Info_list * list_iter = list_head->next;
    char condition[100];
    char * trimmed_condition = NULL;
    long int id;
    struct Information * info_temp = NULL;
    struct Information * info = NULL;
    char id_char[200];
    char price_char[200];
    char number_char[200];
    
    printf("Enter ID which you want modify. \n>>>> ");
    fgets(condition, 100, stdin);
    trimmed_condition = trimmed(condition);
    id = atol(trimmed_condition);
    
    while (list_iter && list_iter->node) {
        if (list_iter->node->id == id)
            break;
        list_iter = list_iter->next;
    }
    info_temp = list_iter->node;
    printf("\n id: %ld", info_temp->id);
    printf("\t name: %s", info_temp->name);
    printf("\t type: %s", info_temp->type);
    printf("\t price: %.2f", info_temp->price);
    printf("\t Number: %u", info_temp->number);
    printf("\n  Company: %s", info_temp->company);
    printf("  Comment: %s\n", info_temp->comment);
    
    info = info_temp;
    printf("\nNow Enter New Data of This Information.\n");
    printf("Plase Enter ID, only numeral support, for example: \"123456\"\n");
    printf(">>>> ");
    fgets(id_char, 200, stdin);
    info->id = atol(id_char);
    printf("You Typed %ld\n", info->id);
    
    printf("Plase Enter Name, for example: \"Kobe Bryant\"\n");
    printf(">>>> ");
    fgets(info->name, 200, stdin);
    trimmed(info->name);
    printf("You Typed %s\n", info->name);
    
    printf("Plase Enter Type, for example: \"A\"\n");
    printf(">>>> ");
    fgets(info->type, 200, stdin);
    trimmed(info->type);
    printf("You Typed %s\n", info->type);
    
    printf("Plase Enter Price, only numeral support, example: \"123.456\"\n");
    printf(">>>> ");
    fgets(price_char, 200, stdin);
    info->price = atof(price_char);
    printf("You Typed %f\n", info->price);
    
    printf("Plase Enter Number, only numeral support, example: \"543210\"\n");
    printf(">>>> ");
    fgets(number_char, 200, stdin);
    info->number = atoi(number_char);
    printf("You Typed %u\n", info->number);
    
    printf("Plase Enter Company, for example: \"Red Had\"\n");
    printf(">>>> ");
    fgets(info->company, 200, stdin);
    trimmed(info->company);
    printf("You Typed %s\n", info->company);
    
    printf("Plase Enter Comment, for example: \"This is Comment\"\n");
    printf(">>>> ");
    fgets(info->comment, 400, stdin);
    printf("You Typed %s\n", info->comment);
    trimmed(info->comment);

    /* 保存 */
    write_list_to_file(list_head);

}

/* 分配命令，并执行 */
void select_operator(char operator[100], struct Info_list * list_head)
{
    /* 显示帮助页面 */
    if (0 == strcmp(operator,"help"))
        show_help();
    
    /* 插入新数据 */
    else if (0 == strcmp(operator, "i"))
        insert_information(list_head);
    
    /* 显示数据，按插入时间输出，或按某个字段排序后输出 */
    else if (0 == strcmp(operator, "l"))
        list_information(list_head);
    else if (0 == strcmp(operator, "lid"))
        list_information_order(list_head, "id");
    else if (0 == strcmp(operator, "lname"))
        list_information_order(list_head, "name");
    else if (0 == strcmp(operator, "lprice"))
        list_information_order(list_head, "price");
    else if (0 == strcmp(operator, "lnumber"))
        list_information_order(list_head, "number");
    else if (0 == strcmp(operator, "ltype"))
        list_information_order(list_head, "type");
    else if (0 == strcmp(operator, "lcompany"))
        list_information_order(list_head, "company");
    else if (0 == strcmp(operator, "lcomment"))
        list_information_order(list_head, "comment");
    /* 删除 */
    else if (0 == strcmp(operator, "d"))
        delete_information(list_head);
    
    /* 查找数据，全文模糊查找或按字段模糊查找*/
    else if (0 == strcmp(operator, "s"))
        search_information(list_head , ALL);
    else if (0 ==  strcmp(operator, "sid"))
        search_information(list_head, ID);
    else if (0 ==  strcmp(operator, "sname"))
        search_information(list_head, NAME);
    else if (0 ==  strcmp(operator, "sprice"))
        search_information(list_head, PRICE);
    else if (0 ==  strcmp(operator, "stype"))
        search_information(list_head, TYPE);
    else if (0 ==  strcmp(operator, "snumber"))
        search_information(list_head, NUMBER);
    else if (0 ==  strcmp(operator, "scompany"))
        search_information(list_head, COMPANY);
    else if (0 ==  strcmp(operator, "scomment"))
        search_information(list_head, COMMENT);
    
    /* 修改 */
    else if (0 == strcmp(operator, "m"))
        modify_information(list_head);
}

/* 释放链表申请的内存 */
void freeMem(struct Info_list* list_head)
{
    struct Info_list * list_temp = list_head;
    struct Info_list * list_next = NULL;
    while (list_temp) {
        if (list_temp->node) {
            free(list_temp->node);
        }
        if (list_temp->next) {
            list_next = list_temp->next;
            free(list_temp);
            list_temp = list_next;
        } else {
            break;
        }
    }
}

int main(int argc, char** argv)
{
    char operator[100];
    char * trimmed_operator = NULL;
    struct Info_list * list_first = NULL;
    /* 给链表的头结点分配内存，并初始化数据为NULL*/
    struct Info_list * list_head = (struct Info_list*)malloc(sizeof(struct Info_list));
    if (NULL == list_head) {
        printf("\nError!    Cannot malloc memory\n");
        return 0;
    }
    list_head->next = NULL;
    list_head->node = NULL;
    
    /* 给链表的第一个结点分配内存，并初始化数据为NULL*/
    list_first = (struct Info_list*)malloc(sizeof(struct Info_list));
    if (NULL == list_first) {
        printf("\nError!    Cannot malloc memory\n");
        return 0;
    }
    list_first->next = NULL;
    list_first->node = NULL;
    list_head->next = list_first;
    /* 从保存的文件读取数据，并将数据保存到链表当中 */
    read_from_file(list_first);
    
    /* 循环执行用户输入的指令，直到输入退出指令 "q" */
    do{
        printf("\n________________________________________________________________________\n");
        printf("Plese Select Your Operator!    ");
        printf("Type \"help\", for More Information.\n");
        printf("------------------------------------------------------------------------\n");
        printf(">>>> ");
        fgets(operator, 100, stdin);
        trimmed_operator = trimmed(operator);
        select_operator(trimmed_operator, list_head);
        
    } while (strcmp(operator, "q") != 0);
    
    /* 释放链表所申请的内存，防止内存泄露 */
    freeMem(list_head);
    return 0;
}

