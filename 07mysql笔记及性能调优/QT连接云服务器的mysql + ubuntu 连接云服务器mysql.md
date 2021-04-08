环境： QT5.9 + windows10 + ubuntu-mysql5.7

如果需要编译数据驱动的可以参考这篇文章：[编译mysql驱动](http://shouce.jb51.net/qt-beginning/27.html)

QT 连接测试Code:
新建一个Qt 项目（有无界面都ok）

pro 上面需要加上这个
```cpp
QT       += core gui sql
```

main 文件：

```cpp
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Available drivers: ";
    QStringList drivers =QSqlDatabase::drivers();
//    foreach (QString d, drivers) {
//        qDebug() << d;
//    }

    QSqlDatabase db =  QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("x.xxx.147.218");  // 这里换成你自己的云服务器ip
    db.setPort(3306);
    db.setDatabaseName("mydata");   // 需要安装64位的驱动 对应编译器64位
    db.setUserName("root");
    db.setPassword("123456");
    if(!db.open())
        qDebug() << "Failed!";
    else
        qDebug() << "open";

    QSqlQuery query(db);
    //注意这里varchar一定要指定长度，不然会出错
    query.exec("create table student(id int primary key,name varchar(20))");

    query.exec("insert into student values(1,'xiaoliu')");
    query.exec("insert into student values(2,'xiaogao')");
    query.exec("insert into student values(3,'xiaoli')");
    query.exec("insert into student values(4,'xiaoma')");

    query.exec("select id,name from student where id >= 2");

    while(query.next())
    {
        int value0 = query.value(0).toInt();
        QString value1 = query.value(1).toString();
        qDebug() << value0 << value1 ;
    }
    return a.exec();
}
```

**自己遇到的错误：**
1. 刚开始打印qt自带驱动的时候，发现有mysql驱动，就不没有管它，就一直报这个错误。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210408144355865.png)
解决办法，编译mysql驱动，或者在网上找一下windows下的32位或者是64位的驱动，这里的位数是根据自己编译器来决定的，不是根据你安装qt 的位数决定的（这里网上有些文章弄混淆了）
需要的可以留言，我私发给你。
然后放在bin 目录就行，如下图，在按照上面的代码连接就ok了。结果如下。
![在这里插入图片描述](https://img-blog.csdnimg.cn/2021040814465753.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210408144756261.png)
需要注意的点： 云数据库需要修改权限，我貌似之前就修改过了，这里就不讲了。（设置% 是允许所有机器登陆root账号）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210408145007227.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

另外的修改权限大家可以看下这个文章：[https://blog.csdn.net/weixin_39955142/article/details/113385754](https://blog.csdn.net/weixin_39955142/article/details/113385754)

## 在ubuntu 中qt 连接云服务器数据库
**出现问题：**   Qt访问mysql还是报Driver not loaded 
还是上面的代码，直接运行的时候会出现**驱动问题**。
这时候需要在安装qt 的目录下查询一下是否有mysql驱动
刚开始我的ubuntu中是出现这样的libmysqlclient.so.18  --> not found （这个是解决问题的根本原因）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210408161803304.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

解决办法：  下载驱动，直接点击[这里](https://launchpad.net/ubuntu/+source/mysql-5.6/5.6.25-0ubuntu1/+build/7676744)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210408162107188.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
下载上面的驱动后，直接放在之前查询驱动的目录中，然后安装，`sudo dpkg -i libmysqlclient18_5.6.25-0ubuntu1_amd64.deb`
安装完后，在查询会显示全部正常。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210408162309576.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
然后再去ubuntu 中的qt 连接mysql 就正常了。
