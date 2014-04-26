c_homework
==========
![Mou icon](http://mouapp.com/Mou_128.png)
#C语言实验设备管理系统

**这是我表弟的同学的一个C语言作业，包括基本的输入输出，文件操作，排序，链表，动态分配内存等......**

作者：<742654192@qq.com>, <yuhang.silence@gmail.com>

====================

####主要内容——开发一个实验设备管理系统，基本设备信息包括：

* 设备编号	`id`
* 设备名称	`name`
* 类型		`type`
* 价格     `price`
* 设备数量  `number`
* 生产公司  `company`
* 备注信息  `comment`

```
/* 信息结构体 */
struct information{
    long id;
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
```
    
	
####五大基本功能
1. 设备信息录入功能		`insert_information`
* 设备信息浏览和排序功能     `list_information`
* 查询功能 `search_information` 
* 设备信息删除功能     `delete_information`
* 设备信息修改功能     `modify_information`

---
####说明

采用单链表在内存中保存设备的信息。在程序开始的时候，读取保存在文件中的内容数据，将其保存到链表当中。用户通过输入各式各样的命令来执行增、删、查、改和搜索等功能。
其中查找是`字符串模糊查找`。
排序采用`冒泡排序`。
尽量避免`内存泄露`。
尽量避免`溢出`。

#####命令

    q 退出
    i 插入
    d 删除
    m 更改
    
    l 按插入时间输出
    lid 按id大小排序后输出
    lname 按名字排序后输出
    ltype 按类型排序后输出
    lprice 按价格排序后输出
    lnumber 按数量排序后输出
    lcompany 按公司排序后输出
    lcomment 按注释排序后输出
    
    s 全文模糊查找
    sid 按id模糊查找
    sname 按姓名模糊查找
    stype 按类型查找
    sprice 按价格模糊查找
    snumber 按数量模糊查找
    scompany 按公司模糊查找
    scomment 按注释模糊查找
    