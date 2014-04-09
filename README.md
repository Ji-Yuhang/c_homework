c_homework
==========
![Mou icon](http://mouapp.com/Mou_128.png)
#实验设备管理系统

**这是我表弟的同学的一个C语言作业，包括基本的输入输出，文件操作，等......**

作者：<742654192@qq.com>, <yuhang.silence@gmail.com>

个人网站：<http://jiyuhang.sinaapp.com>

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
struct information{
    long id;
    char name[200];
    char type[200];
    double price;
    unsigned int number;
    char company[200];
    char comment[400];
};
```
    
	
####需满足基本功能
* 设备信息录入功能		`insert_information`
* 设备信息浏览功能     `list_information`
* 查询功能、排序功能：按编号、名称查询，按价格、名称排序 `search_information` 
* 设备信息删除功能     `delete_information`
* 设备信息修改功能     `modify_information`
