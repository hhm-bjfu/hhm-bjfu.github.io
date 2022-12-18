---
layout:	post
title:	Connect to MySQL Database in IntelliJ IDEA with Java in Ubuntu20.04
date:	2022-12-17
categories:	[Skill]
---

## Download JDBC

Download Link:[MySQL :: Download Connector/J](https://dev.mysql.com/downloads/connector/j/)

Select Operating System:`Platform Independent`

Click `No thanks, just start my download.`

![image](https://user-images.githubusercontent.com/88172940/208276041-3e65da44-9c11-4efe-b42b-f2a6a0582b02.png)

Extract files and place files in a memorable location.

## Create new project in IDEA

1、Create new project.

2、Add a directory.

![image](https://user-images.githubusercontent.com/88172940/208238034-cd1e9607-7583-414f-8676-95d1aa786083.png)

3、Select lib -> right click -> Opin in -> files -> Import JDBC

![image](https://user-images.githubusercontent.com/88172940/208276060-60eeac66-3c5a-4cc7-9d40-48395ba6c2b3.png)

## Add it as a module

Select testJDBC -> right click -> Project Structure -> Module -> JAR

![image](https://user-images.githubusercontent.com/88172940/208238807-3e2f3e17-bda4-4f9c-ba28-028dbc204e79.png)

## Create Module in MySQL Workbench

![image](https://user-images.githubusercontent.com/88172940/208275952-20b837eb-ce52-4b05-82e6-d41ddb8baaae.png)



## Editor Java Code

In src/Main.java

```java
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class Main {

    public static void main(String[] args) {
        try {
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/book",
                    "root", "11");
            Statement statement = connection.createStatement();

            ResultSet resultSet = statement.executeQuery("select * from advisor");
            while (resultSet.next()) {
                System.out.println(resultSet.getString("s_ID"));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

![image](https://user-images.githubusercontent.com/88172940/208275957-dd694371-8f71-47ee-8aa2-31e90c04c4a4.png)

## 参考链接

视频参考：[Java JDBC - Connect to MySQL Database in IntelliJ with Java - YouTube](https://www.youtube.com/watch?v=e8g9eNnFpHQ)