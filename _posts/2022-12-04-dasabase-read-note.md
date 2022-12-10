---
layout: post
title:《数据库系统概念》（第6版）阅读笔记
categories: [Life]
---

## 写在前面的话

由于课程匆忙，故只细看1-7章 + （应对课设）。

并且，为了当作提前预习，先在[蓝桥网](https://www.lanqiao.cn/courses/9)上练习mysql基本操作，相关笔记放在第0章。

## 第 0 章——蓝桥网练习

#### lab1 SQL介绍及安装

MySQL目前属于Oracle公司，由于其体积小、速度快、源码开放，逐渐成为中小型网站主流。

> 以下命令均在Ubuntu20.04 上运行

打开MySQL：`sudo service mysql start`

安装MySQL：

```sql
# 安装 MySQL 服务端、核心程序
sudo apt-get install mysql-server

# 安装 MySQL 客户端
sudo apt-get install mysql-client

# 测试
sudo netstat -tap | grep mysql
```

打开MySQL：

```sql
# 启动mysql服务
sudo service mysql start

# 使用root用户进行登录
sudo mysql -u root
```

查看数据库：`show dasabase;`

#### lab2 创建数据库并插入数据

连接数据库：`use <数据库名>u;`

连接数据库后查看表：`show tables;`

创建db并插入数据：

```sql
create database mysql_shiyan;
show databases;
use mysql_shiyan;
show tables; 
```

db只是一个框架，表才是实质内容。创建表例子如下：

```sql
create table employee (
	id int(10),
    name char(20),
    phone int(12)
);
create table department (
	dpt_name char(20);
    dpt_phone int(12);
);
show tables;
```

mysql常用数据类型如下：

![image-20221206121159504](/home/hhm/.config/Typora/typora-user-images/image-20221206121159504.png)

char和varchar区别：char长度固定，varchar长度不固定。

插入数据：

```sql
insert into employee(id, name, phone) values(01, 'Tom', 110110110); # 完整形态
insert into employee values (02, 'Jack', 119119119);
insert into employee(id, name) values(03, 'Rose');
```

#### lab3 SQL的约束

约束是一种限制，通过对表中行或者列的数据作出限制，确保表中数据的完整性和唯一性。

mysql中通常有以下几种约束：

* 主键 primary key，一行数据的唯一标识符，不能重复也不能为空。

```sql
dpt_name char(20) primary key, # 定义主键的一种方式
constraint dpt_pk primary key(dpt_name), # 定义主键的另一种方式，其中dpt_pk是自定义的名字
constraint proj_pk primary key(proj_num, proj_name), # 定义复合主键
```

* 默认值 default，插入为空时使用default。

```sql
people_num int(10) default 10;
```

* 唯一 unique，规定某列的每个值都是唯一的。

```sql
unique (phone), # 保证phone这列的每个值都是不相同的，否则会报错
```

* 外键 foreign key，外键确保数据完整性且表现表之间关系。

```sql
constraint emp_fk foreign key(in_dpt) references department(dpt_name);
```



![image-20221207122535401](./2022-12-04-%E3%80%8A%E6%95%B0%E6%8D%AE%E5%BA%93%E7%B3%BB%E7%BB%9F%E6%A6%82%E5%BF%B5%E3%80%8B%EF%BC%88%E7%AC%AC6%E7%89%88%EF%BC%89%E9%98%85%E8%AF%BB%E7%AC%94%E8%AE%B0.assets/image-20221207122535401.png)

* 非空 not null

删除数据库：`drop database mysql_shiyan;`

新建一个初始库，`vim MySQL-03-01.sql `

```sql
create database mysql_shiyan;

use mysql_shiyan;

create table department
(
	dpt_name char(20) not null,
    people_num int(10) default '10',
    constraint dpt_pk primary key(dpt_name)
);

create table employee
(
	id int(10) primary key,
    name char(20),
    age int(10),
    salary int(10) not null,
    phone int(12) not null,
    in_dpt char(20) not null,
    unique (phone),
    constraint emp_fk foreign key (in_dpt) references department(dpt_name)
);

create table project
(
	proj_num int(10) not null,
    proj_name char(20) not null,
    start_date date not null,
    end_date date default '2015-04-01',
    of_dpt char(20) references department(dpt_name),
   	constraint proj_pk primary key (proj_num, proj_name)
);
```

加载上面的sql文件：`source  /home/hhm/Code/lanqiaoTmp/MySQL-03-01.sql;`

即可得到一个新建的数据库。

#### 挑战1 搭建简易成绩管理系统数据库

`vim createStudent.sql`

```sql
```







## 第 1 章——引言

数据库管理系统（database management system DBMS），由数据集合和程序组成，简称数据库。

在DBMS出现之前，多采用永久记录的文件处理系统，手工进行更新和同步。

使用以下几个层次来对用户屏蔽复杂性：

* 物理层physical level：实际且负责的底层数据结构。
* 逻辑层logical level：描述存储什么数据及关系。
* 视图层view level：只描述db的某个部分。

实例instance：特定时刻的db，类比为某一时刻变量的值。

模式schema：db的总体设计，类比为变量声明。

数据库语言通常分为以下两种，通常语言两者兼具。

* 数据定义语言data-definition language。
* 数据操纵语言data-manipulation language。













## [下载链接]()

提前声明：不能用于商业用途，仅供学习。