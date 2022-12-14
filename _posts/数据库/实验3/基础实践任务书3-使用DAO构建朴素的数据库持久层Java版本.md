# 数据库基础实践任务书

## 实践任务三：使用DAO构建朴素的数据库持久层篇（4h）

## 【任务描述】

通过DAO技术，针对给定的数据库，构建满足可扩展性要求且具有面向对象特点的数据库持久层。

## 【任务目的】

1. 理解关系型数据库与面向对象程序之间的转换方法

学习关系型数据库操作时转换为面向对象程序之间的必要性和方法。

2. 掌握使用DAO技术构建朴素数据库持久层的方法

结合提供的学习资料，编写指定数据库的持久层框架。


## 【任务内容】

在给定的关系表上，根据实践任务中需要，运用程序设计语言构建朴素的数据库持久层。

表3.1 学生表（表中联系电话***处自拟）

|学号|姓名|性别|专业班级|出生日期|联系电话|
|:----:|:----:|:----:|:----:|:----:|:----:|
|0433|张艳|女|生物04|1986-9-13||
|0496|李越|男|电子04|1984-2-23|1381290****|
|0529|赵欣|男|会计05|1984-1-27|1350222****|
|0531|张志国|男|生物05|1986-9-10|1331256****|
|0538|于兰兰|女|生物05|1984-2-20|1331200****|
|0591|王丽丽|女|电子05|1984-3-20|1332080****|
|0592|王海强|男|电子05|1986-11-1||

表3.2 课程表

|课程号|课程名|学分数|学时数|任课教师|
|:----:|:----:|:----:|:----:|:----:|
|K001|计算机图形学|2.5|40|胡晶晶|
|K002|计算机应用基础|3|48|任泉|
|K006|数据结构|4|64|马跃先|
|M001|政治经济学|4|64|孔繁新|
|S001|高等数学|3|48|赵晓尘|

表3.3 学生作业表

|课程号|学号|作业1成绩|作业2成绩|作业3成绩|
|:----:|:----:|:----:|:----:|:----:|
|K001|0433|60|75|75|
|K001|0529|70|70|60|
|K001|0531|70|80|80|
|K001|0591|80|90|90|
|K002|0496|80|80|90|
|K002|0529|70|70|85|
|K002|0531|80|80|80|
|K002|0592|75|85|85|
|K006|0531|80|80|90|
|K006|0591|80|80|80|
|M001|0496|70|70|80|
|M001|0591|65|75|75|
|S001|0531|80|80|80|
|S001|0538|60||80|

### 1. 理解关系型数据库与面向对象程序之间的转换方法

* 阅读提供的Java持久层资料，学习关系型数据库与面向对象程序之间的转换方法
* 运用Java语言，对给定的关系型数据库进行对象封装
* 思考主码和外码的实现方式

### 2. 掌握使用DAO技术构建朴素数据库持久层的方法

* 阅读提供的Java持久层资料，学习DAO可扩展连接类的编写方法，开展可扩展连接类的编写工作
* 阅读提供的Java持久层资料，学习实体对象调用DAO的编写方法，开展DAO实体的编写工作
* 阅读提供的Java持久层资料，学习DAO工厂的方法，开展DAO工厂的生成代码编写工作

## 【实验步骤】

### 1. 理解关系型数据库与面向对象程序之间的转换方法

#### 1.1 阅读提供的Java持久层资料，学习关系型数据库与面向对象程序之间的转换方法：

* ⼀条记录对应⼀个对象。

* ⼀张关系表可以看作是记录的集合，也可以看作是对象的集合。

* 表的表头，即关系的模式，可以看作是⼀类对象的模板，即对象对应的类。

* 通过以上关系的转换，对数据库的操作可以转换为对对象的操作：

* 插入⼀条记录，可以看作是创建⼀个对象，然后将对象持久的保存在硬盘上的过程；

* 删除⼀条记录，可以看作是将已经创建的对象从硬盘上进⾏删除或者从内存中释放的过程；

* 修改⼀条记录，可以看作是将已有对象从硬盘中读取后，然后修改相关信息，再保存到硬盘中的过程；

* 查找记录，可以看作是从已有的对象中，选择满⾜条件的对象。

根据上述操作，关系数据库和⾯向对象程序的分⼯为：

* 关系数据库负责维护数据的安全性、完整性和⼀致性。
* 关系数据库负责复杂的查询操作。
* ⾯向对象程序设计负责根据关系数据库中存储的内容在内存中，按照指定类型，创建对象，并进⼀步根据业务流程对对象执⾏相关操作。
* ⾯向对象除了提供有关数据的模板外，还可以封装更加具体的数据操作⽅法，进⽽保证数据操作的安全性，同时，上层业务⼈员⽆需编写SQL代码，可以直接通过⾯相对象的⽅法，对数据
库进⾏操作。



#### 1.2 运用Java语言，对给定的关系型数据库进行对象封装

#### 1.3 思考主码和外码的实现方式

```Java
package edu.db.dao;

public class Student {
    private String student_no;
    private String student_name;
    private String student_sex;
    private String student_class;
    private String student_birthday;
    private String student_phone;

    public Student(String student_no, String student_name, String student_sex, String student_class, String student_birthday, String student_phone) {
        this.student_no = student_no;
        this.student_name = student_name;
        this.student_sex = student_sex;
        this.student_class = student_class;
        this.student_birthday = student_birthday;
        this.student_phone = student_phone;
    }

    public String getStudent_no() {
        return student_no;
    }

    public void setStudent_no(String student_no) {
        this.student_no = student_no;
    }

    public String getStudent_name() {
        return student_name;
    }

    public void setStudent_name(String student_name) {
        this.student_name = student_name;
    }

    public String getStudent_sex() {
        return student_sex;
    }

    public void setStudent_sex(String student_sex) {
        this.student_sex = student_sex;
    }

    public String getStudent_class() {
        return student_class;
    }

    public void setStudent_class(String student_class) {
        this.student_class = student_class;
    }

    public String getStudent_birthday() {
        return student_birthday;
    }

    public void setStudent_birthday(String student_birthday) {
        this.student_birthday = student_birthday;
    }

    public String getStudent_phone() {
        return student_phone;
    }

    public void setStudent_phone(String student_phone) {
        this.student_phone = student_phone;
    }

    @Override
    public String toString() {
        return "Student{" +
                "student_no='" + student_no + '\'' +
                ", student_name='" + student_name + '\'' +
                '}';
    }
}

```

```Java
import java.sql.Connection;

public interface DAO {
    Connection getConnection();
}
```

```Java
import java.sql.Connection;
import java.sql.DriverManager;

public class DAOBase implements DAO {
    @Override
    public Connection getConnection() {
        String URL="jdbc:sqlserver://39.98.232.53:1433; DatabaseName=education";
        Connection con = null;
        try{
            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
             con = DriverManager.getConnection(URL,"teacher","teacher");

        }catch (Exception ex){
            ex.printStackTrace();
        }
        return con;
    }
}

```

```Java
import java.util.List;

public interface StudentDAO {
    void addStudent(Student student);
    void updateStudent(Student student);
    void deleteStudent(String student_no);
    Student getStudent(String student_no);
    List<Student> findStudents(SearchCriteria searchCriteria);
}
```

```Java
import java.sql.PreparedStatement;
import java.sql.Connection;
import java.sql.ResultSet;
import java.util.List;

public class StudentDAOImpl extends DAOBase implements StudentDAO {
    private static final String STUDENT_INSERT_SQL = "INSERT INTO student(sno,sn,sex,class,birthday,phone) VALUES(?,?,?,?,?,?) ";
    @Override
    public void addStudent(Student student) {
        Connection con = null;
        try{
            con = getConnection();
            PreparedStatement psmt = con.prepareStatement(STUDENT_INSERT_SQL);
            psmt.setString(1, student.getStudent_no());
            psmt.setString(2, student.getStudent_name());
            psmt.setString(3, student.getStudent_sex());
            psmt.setString(4, student.getStudent_class());
            psmt.setString(5, student.getStudent_birthday());
            psmt.setString(6, student.getStudent_phone());
            psmt.executeUpdate();
            psmt.close();
        }catch(Exception e){
            e.printStackTrace();
        }finally {
            try{
                con.close();
            }catch (Exception e){
                e.printStackTrace();
            }
        }


    }

    @Override
    public void updateStudent(Student student) {

    }

    @Override
    public void deleteStudent(String student_no) {

    }

    private static final String STUDENT_SELECT_SQL = "SELECT sno,sn,sex,class,birthday,phone FROM student WHERE sno=?";
    @Override
    public Student getStudent(String student_no) {
        Connection con = null;
        Student student = new Student();
        try{
            con = getConnection();
            PreparedStatement psmt = con.prepareStatement(STUDENT_SELECT_SQL);
            psmt.setString(1, student_no);
            ResultSet rs = psmt.executeQuery();
            while (rs.next()){
                student.setStudent_no(rs.getString("sno"));
                student.setStudent_name(rs.getString("sn"));
                student.setStudent_sex(rs.getString("sex"));
                student.setStudent_class(rs.getString("class"));
                student.setStudent_birthday(rs.getString("birthday"));
                student.setStudent_phone(rs.getString("phone"));
            }
            psmt.close();

        }catch(Exception e){
            e.printStackTrace();
        }finally {
            try{
                con.close();
            }catch (Exception e){
                e.printStackTrace();
            }
        }
        return student;
    }

    @Override
    public List<Student> findStudents(SearchCriteria searchCriteria) {
        return null;
    }
}
```

```Java
public class DAOFactory {
    private static DAOFactory daoFactory;
    static {
        daoFactory = new DAOFactory();
    }
    private DAOFactory(){

    }

    public static DAOFactory getInstance(){
        return daoFactory;
    }

    public StudentDAO getStudengDAO(){
        return new StudentDAOImpl();
    }
}
```
```Java
public class Main {
    public static void main(String[] args){
        Student student = new Student();
        student.setStudent_no("S0010");
        student.setStudent_name("张三");
        student.setStudent_sex("男");
        student.setStudent_class("信息05");
        student.setStudent_birthday("2001-1-1");
        student.setStudent_phone("1777777777");

        DAOFactory.getInstance().getStudengDAO().addStudent(student);

    }
}
```

### 2. 掌握使用DAO技术构建朴素数据库持久层的方法

#### 2.1 阅读提供的Java持久层资料，学习DAO可扩展连接类的编写方法，开展可扩展连接类的编写工作

* 学习提供的资料，分析可扩展的DAO连接类的编写注意事项。
* 结合给定案例，设计并编写DAO连接类。

#### 2.2 阅读提供的Java持久层资料，学习实体对象调用DAO的编写方法，开展DAO实体的编写工作

* 学习提供的资料，分析DAO调用类的编写注意事项。
* 结合给定案例，设计并编写DAO调用类。

#### 2.3 阅读提供的Java持久层资料，学习DAO类的编写方法，开展DAO类的编写工作

* 学习提供的资料，分析DAO工厂类的编写注意事项。
* 结合给定案例，设计并编写DAO工厂类。

### 3. 优化数据库

* 思考现有查询构建方式是否存在安全隐患
* 思考是否有必要创建多个DAO调用类和工厂类，如何实现系统生命周期内，单一调用类和工厂类实例。
* 使用连接池优化已有的连接类程序


## 【实验注意】

### 1. 关系型数据库与面向对象程序之间的转换方法

* 关系型数据库类型与面向对象程序类型转化的注意事项。
* 是否有必要将实体的操作方法放入实体中？
* 外码实现过程中，如何通过程序的方式实现外码的强制性。。
  
### 2. 使用DAO技术构建朴素数据库持久层

* 使用单例构建DAO调用类和工厂类的方法。

## 【实验相关教程】

### 1. DAO类相关教程

* 参考给定的参照资料。

## 【编著信息】

* 北京林业大学 信息学院 数据库课程教学组
* 主要编写人员：崔晓晖
* 版本：V0.1
* 2022-11-25在
