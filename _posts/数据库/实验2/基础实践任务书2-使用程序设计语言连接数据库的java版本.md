# 数据库基础实践任务书

## 实践任务二：使用程序设计语言连接数据库篇（4h）

## 【任务描述】

依托标准API，使用程序设计语言连接数据库和操作数据库。同时，编写数据库连接池，连接数据库。

## 【任务目的】

1. 掌握标准API操作数据库的流程和基本方法

学习Java连接数据库的标准API，掌握使用Java连接数据库的步骤和常用方法。

2. 运用使用标准API连接和操作目标数据库

能够根据业务需要，使用标准API连接数据库，并编写执行执行相关业务SQL语句、获取查询结果的程序。

3. 使用标准数据库工具表实现具有连接池的数据库访问程序

学习数据库连接池工具包，运用数据库连接池工具包改造现有数据库操作程序，实现基于数据库连接池的数据库访问程序。

## 【任务内容】

在给定的关系表上，根据实践任务中需要，运用程序设计语言连接和使用数据库。

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

|课程号|课程号|学分数|学时数|任课教师|
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

### 1. 学习Java操作数据库的标准API

* 阅读Java操作数据库的官方文档
* 学习Java操作数据库的标准API
* 总结Java操作数据库的基本步骤

### 2. 使用java操纵SQL Server

* 学习jdbc的安装和使用方法
* 学习jdbc案例
* 编写满足实践任务需求的程序

### 3. 使用数据库连接池工具包实现数据库连接池

* 学习连接池工具包提供的4中连接池模式
* 学习连接池工具包配置连接池和获取连接的方法
* 使用连接池优化已有实践任务程序

## 【实验步骤】

### 1. 数据库标准API的使用学习

#### 1.1 学习使用Java连接数据库的方法

* 通过“Java访问数据库.ppt”，学时用Java语言访问数据库的方法。
* 相关驱动的下载和加载方法
* JDBC是Java数据库连接技术的简称，提供连接各种常用数据库的能力
* java.sql包中，如：DriverManager类、Connection接口、Statement接口、ResultSet接口

```Java
String URL="jdbc:sqlserver://ip:1433; DatabaseName=education";
try{
    Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
    Connection con = DriverManager.getConnection(URL,"sa","sa");
}catch (Exception ex){
        ex.printStackTrace();
}

```



#### 1.2 使用标准API连接和操作数据库的例子

Statement中提供的执行SQL语句的三种常用方法
* ResultSet executeQuery(String sql):可以执行SQL查询并获取到ResultSet对象
* Int executeUpdate(String sql)：可以执行插入，删除，更新等操作，返回值是执行该操作所影响的行数
* Boolean  execute(String sql):可以执行任何SQL语句，然后获得一个布尔值，表示是否返ResultSet。


```Java
public static void main(String[] args) {
    Connection con = null;
    Statement statement = null;
    try {
        String strSql = "************";
        String url = "jdbc:sqlserver://ip:1433; DatabaseName=education;user=stu;password=123";
        try {
            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
        } catch (ClassNotFoundException e) {
            System.out.println("无法找到驱动类");
        }
        conn = DriverManager.getConnection(url);
		statement = conn.createStatement();
        statement.executeUpdate(strSql);
    } catch (SQLException sqlE) {
        sqlE.printStackTrace();
    } finally {
        if(conn != null){
            conn.close();
        }
        
    }
}


```

```Java
public class ConnectionManagement{
    public static Connection getConnection(){
        Connection conn = null;
        try {
            String url = "jdbc:sqlserver://ip:1433; DatabaseName=education;user=stu;password=123";
            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
            conn = DriverManager.getConnection(url);
        } catch (ClassNotFoundException e) {
            System.out.println("无法找到驱动类");
        }
        
    } catch (SQLException sqlE) {
        sqlE.printStackTrace();
    }

    return conn 
        
}



```

使用PreparedStatement执行SQL语句
* PreparedStatement 接口继承 Statement接口
* PreparedStatement比普通的Statement对象使用起来更加灵活，更有效率

```Java
public class NewsFirstTitleDB2 {
    public static void main(String[] args) {
        Connection con = null;
        PreparedStatement pStatement = null;
        try {
        SimpleDateFormat hmFromat = 
                           new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
        con = ConnectionManager.getConnection();
        String strSql = "insert into FirstLevelTitle values(?,?,?,?)";
        pStatement = con.prepareStatement(strSql);
        pStatement.setInt(1, 1);
        pStatement.setString(2, "军事");
        pStatement.setString(3, "管理员");
        pStatement.setString(4, hmFromat.format(new Date()));
        pStatement.executeUpdate();
        } catch (SQLException sqlE) {
            sqlE.printStackTrace();
        } finally {
            ConnectionManager.closeStatement(pStatement);
            ConnectionManager.closeConnection(con);
        }
    }
}

```

```Java
public class NewsFirstTitleDB3 {
    public static void main(String[] args) {
        Connection con = null;
        PreparedStatement pStatement = null;
        try {
            con = ConnectionManager.getConnection();
            String strSql = "delete from FirstLevelTitle where id=<?";
            pStatement = con.prepareStatement(strSql);
            pStatement.setString(1, 10);
            int row = pStatement.executeUpdate();
            System.out.println("成功删除了"+row+"行数据!");
        } catch (SQLException sqlE) {
            sqlE.printStackTrace();
        } finally {
            ConnectionManager.closeStatement(pStatement);
            ConnectionManager.closeConnection(con);
        }
    }
}

```

```Java
public class NewsFirstTitleDB4 {
    public static void main(String[] args) {
        Connection con = null;
        PreparedStatement pStatement = null;
        try {
            con = ConnectionManager.getConnection();
            String strSql = "update FirstLevelTitle set Creator = ? where Id = ?";
            pStatement = con.prepareStatement(strSql);
            pStatement.setString(1, "编辑");
            pStatement.setInt(2, 1);
            int row = pStatement.executeUpdate();
            System.out.println("成功更新了"+row+"行数据!");
        } catch (SQLException sqlE) {
            sqlE.printStackTrace();
        } finally {
            ConnectionManager.closeStatement(pStatement);
            ConnectionManager.closeConnection(con);
        }
    }
}

```

```Java
public class NewsFirstTitleDB5 {
    public static void main(String[] args) {
        int id = 0;
        Connection con = null;
        PreparedStatement pstmt = null;
        ResultSet resSet = null;
        try {
            con = ConnectionManager.getConnection();
            String sqlStr = "select max(id) from FirstLevelTitle ";
            pstmt = con.prepareStatement(sqlStr);
            resSet = pstmt.executeQuery();
            if (resSet.next()) {
                id = resSet.getInt(1);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            ConnectionManager.closeResultSet(resSet);
            ConnectionManager.closeStatement(pstmt);
            ConnectionManager.closeConnection(con);
        }
        System.out.println("新的一级新闻标题的Id为：" + (id + 1));
    }
}


    public static List getAllFirstLevelTitleList() {
    //省略部分变量声明语句
        ArrayList list = new ArrayList();
        try {
            dbConnection = ConnectionManager.getConnection();
            String strSql = "select * from FirstLevelTitle order by CreateTime desc";
            pStatement = dbConnection.prepareStatement(strSql);
            res = pStatement.executeQuery();
            while (res.next()) {
                int id = res.getInt("id");
                String title = res.getString("TitleName");
                String creator = res.getString("Creator");
                Date time = res.getDate (“CreateTime”); 
                FirstLevelTitle fTitle = new FirstLevelTitle(id, title,creator, time);
                list.add(fTitle);
            }
        }  //省略catch、finally子句
        return list;
    }

```

#### 2 运用标准API连接和操作目标数据库的实践步骤

* 编写程序，连接数据库，遍历学生表，在标准输出中显示学生表中的每条记录。
* 编写程序，连接数据库，遍历学生表、学生选课表和课程表，在标准数据中显示学时数量超过40的学生姓名、课程名称。
* 编写程序，向学生表中插入任意两条记录，在标准输出中显示插入数据后的结果。

#### 3. 使用连接池工具包实现数据库连接池

3.1 Druid学习

* 根据给定的[学习资料](https://zhuanlan.zhihu.com/p/157607448)学习druid的使用

3.2 Druid包编程实践

3.3 使用Druid优化已有程序



## 【实验注意】

### 1. 使用jdbc的注意事项

* 注意jdbc是否已经正确安装并具有数据据库的访问权限。
* 注意sql server端口是否正确开放，开放的端口是否为静态端口。
* 注意jdbc的url是否正确
  
### 2. 使用Druid连接数据库

* 深刻理解使用连接池的意义和作用。
* 理解Druid的主要参数的含义。


## 【编著信息】

* 北京林业大学 信息学院 数据库课程教学组
* 主要编写人员：崔晓晖
* 版本：V0.1
* 2022-11-24
