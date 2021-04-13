
## 引言

Qt 是一个用标准 C++ 编写的跨平台开发类库，它对标准 C++ 进行了扩展，引入了元对象系统、信号与槽、属性等特性，使应用程序的开发变得更高效。

## Qt的核心机制
 Qt本身不是一种编程语言，它就是一个**跨平台的C++开发库**，是用标准C++编写的类库，为开发GUI程序提供了很好的接口。Qt是对标准C++进行的扩展，引入了一些新的概念和功能（在某些方面Qt直接调用接口是真的方便），例如**信号与槽**、**对象属性**等；Qt的元对象编译器（Meta-ObjectCompiler，**MOC**）是一个预处理器，在源程序被编译前，先将这些Qt特性的程序转换称为标准C++兼容的形式。然后再由标准的C++编译器进行编译。这也是为什么在使用信号与槽机制的类中，**必须要在类中添加一个Q_OBJECT宏**的原因，添加了这个宏，moc才能对类中里的信号槽的代码进行预处理。（构建项目时，MOC 工具读取 C++ 源文件，当它发现类的定义里有 Q_OBJECT 宏时，它就会为这个类生成另外一个包含有元对象支持代码的 C++ 源文件，这个生成的源文件连同类的实现文件一起被编译和连接。）

**QtCore模块** 是Qt类库的核心，所有其他模块都依赖于此模块，如果使用qmake来构建项目，QtCore模块则是被自动加入的。Qt为C++语言增加的特性就是在QtCore模块里实现的,这些扩展特性由Qt的元对象系统实现，包括信号与槽机制、属性系统、动态类型转换等。

## Qt的元对象系统
学习Qt有一段时间了，这个概念还不是很清楚，今天看到面试题，正好做个总结。

Qt的元对象系统（Meta-Object System）提供了对象之间通信的**信号与槽机制**、**运行时类型信息**和**动态属性系统**。
元对象系统由以下三个基础组成：
1. QObject 类是所有使用元对象系统的类的基类，
2. 在一个类的private 部分声明Q_OBJECT 宏，是的类可以使用元对象的特性，如动态属性、信号与槽。
3. MOC （元对象编译器）为每个QObject 的类提供必要的代码来实现元对象系统的特性。

除了信号与槽机制外，元对象还提供了一些功能：

 - QObject::metaObject() 函数返回类关联的元对象，元对象类 QMetaObject 包含了访问元对象的一些接口函数，例如 QMetaObject::className() 函数可在运行时返回类的名称字符串。

```cpp
QObject *obj = new QPushButton;
obj->metaObject()->className (); //返回"QPushButton"
```
- QMetaObject::newInstance() 函数创建类的一个新的实例。
- QObject::inherits(const char *className) 函数判断一个对象实例是否是名称为 className 的类或 QObject 的子类的实例。例如：

```cpp
QTimer *timer = new QTimer; // QTimer 是 QObject 的子类
timer->inherits ("QTimer"); // 返回 true
timer->inherits ("QObject");  // 返回 true
timer->inherits ("QAbstractButton");//返回 false,不是 QAbstractButton 的子类
```
- QObject::tr() 和 QObject::trUtf8() 函数可翻译字符串，用于多语言界面设计，后续章会专门介绍多语言界面设计。
- QObject::setProperty() 和 QObject::property() 函数用于通过属性名称动态设置和获取属性值。

对于 QObject 及其子类，还可以使用 qobject_cast() 函数进行动态投射（dynamic cast）。例如，假设 QMyWidget 是 QWidget 的子类并且在类定义中声明了 Q_OBJECT 宏。创建实例使用下面的语句：

```cpp
QObject *obj = new QMyWidget;
```
变量 obj 定义为 QObject 指针，但它实际指向 QMyWidget 类，所以可以正确投射为 QWidget，即：

```cpp
QWidget *widget = qobject_cast<QWidget *>(obj);
```
从 QObject 到 QWidget 的投射是成功的，因为 obj 实际是 QMyWidget 类，是 QWidget 的子类。也可以将其成功投射为 QMyWidget，即：

```cpp
QMyWidget *myWidget = qobject_cast<QMyWidget *>(obj);
```
投射为 QMyWidget 是成功的，因为 qobject_cast() 并不区分 Qt 内建的类型和用户自定义类型。但是，若要将 obj 投射为 QLabel 则是失败的，即：

```cpp
QLabel * label - qobject_cast<QLabel *>(obj);
```

这样投射是失败的，返回指针 label 为 NULL，因为 **QMyWidget 不是 QLabel 的子类**。
使用动态投射，使得程序可以在运行时对不同的对象做不同的处理。

## 元对象特性例子
MOC 演示Qt元对象系统的一些功能，MCO 是主窗口基于QWiget 的应用程序，这个设计界面不多，主要是C++代码，设计元对象特性。

下面是一个简单的类

```cpp
class QPerson : public Q0bject
{ 
	Q OBJECT
	/// 使用宏 Q_CLASSINFO 增加了3个信息， Q_PROPERTY3个属性
	Q_CLASSINFO("author", "Wang")
	Q_CLASSINFO("company", "UPC")
	Q_CLASSINFO("version", "1.0.0")
	Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
	Q_PROPERTY(QString name MEMBER m_ name)
	Q_PROPERTY(int score MEMBER m_ score)
private :
	int m_ age=10;
	QString	m_ name ;
	int m score=79;
public:
	explicit QPerson (QString fName， Qobject *parent = nullptr) ;
	int age () ;
	void setAge (int value) ;
	void incAge () ;
signals:
	ageChanged(int value) ;   // QT 5 有返回值，但只是鸡肋
public slots:
};
```
QPerson 是 QObject 的子类，在类定义部分使用了宏Q_OBJECT， 这样QPerson就获得了元对象系统的支持，能使用信号与槽、属性等功能。
QPerson 使用的Q_CLASSINFO 宏定义了3个附加信息，使用Q_PROPERTY 宏定义了3个属性，还定义了一个信号。下面是QPerson类的实现代码。

```cpp
QPerson::QPerson (QString fName, Qobject *parent):QObject(parent)
{ //构造函数
	m_ name= fName ;
}

int QPerson::age ()
{
	//返回age
	return	m_ age;
}

void QPerson::setAge(int value)  //设置age
{ 
	m_ age=value;
	emit ageChanged(m_ age);  //发射信号
}

void QPerson::incAge ()
{ 
	m_ age++;
	emit ageChanged(m_ age) ; //发射信号
}
```
元对象特性的使用用法


```cpp
class QmyWidget : public QWidget
{
	Q_ OBJECT .
private:
	QPerson *boy;
	QPerson *girl;
public:
	explicit QmyWidget (QWidget *parent = 0) ;
	~ QmyWidget() ;
private:
	Ui::QmyWidget *ui;
private slots :
//自定义槽函数
void on_ageChanged(int value) ;
void on_ spin_ valueChanged(int arg1) ;
//界面按钮的槽函数
void on_ btnClear_ clicked() ;
void on_ btnBoyInc_ clicked() ;
void on btnGirlInc clicked() ;
void on_ btnClassInfo_ clicked() ;
}
```
QMyWidget 类里面定义了两个QPerson 类型的指针变量，定义了两个自定义槽函数，构造函数的代码如下：

```cpp
QmyWidget::QmyWidget (QWidget *parent) : Qwidget (parent), ui (new Ui::Qmywidget)
{ 
	//构造 函数
	ui ->setupUi (this) ;
	boy=new QPerson("王小明"); .
	boy->setProperty("score",95) ;
	boy->setProperty("age", 10) ;
	boy->setProperty("sex" , "Boy");//动态属性
	connect(boy, &QPerson:: ageChanged, this, &QmyWidget::on_ ageChanged);
	
	girl=new QPerson("张小丽");
	girl->setProperty("score",81) ;
	girl->setProperty("age",20) ;
	girl->setProperty("sex", "Girl");//动态属性
	connect(girl, &QPerson:: ageChanged, this, &QmyWidget::on_ ageChanged);
	ui->spinBoy->setProperty("isBoy", true); //动态 属性
	ui->spinGirl->setProperty ("isBoy", false);
	
	connect(ui->spinGirl, SIGNAL (valueChanged(int)),
	this, SLOT(on_spin_valueChanged(int)));
	connect (ui->spinBoy, SIGNAL (valueChanged(int)),
	this, SLOT(on_spin_valueChanged(int)));
	
}
```
  创建QPerson类型对象boy后，使用setProperty()函数设置了score、 age属性的值，这两个属性是QPerson类里定义的。还设置了一个属性sex的值。

```cpp
boy->setProperty("sex", "Boy") ;
```
sex属性在QPerson类里没有定义，所以这个属性是个**动态属性**。

创建对象boy和girl后，它们的ageChanged()信号都与槽函数`on_ ageChanged()` 关联，设置信号与槽关联时使用了函数指针的形式，因为QPerson只有一个`ageChanged()`信 号，具有缺省函数参数，这样设置关联是可以的。

  为界面上的组件spinBoy和spinGirl也设置了–个逻辑型动态属性 isBoy ,分别赋值为true和false，并且这两个 spinBox 的信号 valueChanged(int) 都与槽函数on_ spin_ valueChanged(int) 相关联 。但是，这里使用 connect() 函数设置关联时必须使用SIGNAL和SLOT宏的形式，而不能使用函数指针的形式，因为QSpinBox有两个valueChanged()信号，只是参数不同。

  自定义槽函数on_ ageChanged() 用于响应QPerson的ageChanged() 信号，其实现代码如下:
  

```cpp
void QmyWidget: :on_ ageChanged( int value)
{
	//响应QPerson的ageChanged()信号
	Q_ UNUSED (value) ;
	QPerson *aPerson = qobject_ cast<QPerson *>(sender()); //类 型投射
	QString hisName=aPerson->property ("name").toString(); //姓名
	QString hisSex=aPerson->property("sex").toString();   //动态属性
	int hisAge=aPerson->age() ; //通过接口函数获取年龄
	// int hisAge=aPerson->property("age").toInt() ; / /通过属性获得年龄
	ui ->textEdit->appendPlainText (hisName+","+hisSex+
	QString::asprintf(",年龄=%d",hisAge)) ;
}
```
  这里使用了QObject::sender() 函数**获取信号发射者**。因为信号发射者是QPerson类型对象boy或girl,所以可以用qobject_ cast() 将发射者投射为具体的类型。

```cpp
QPerson * aPerson = qobject_ cast<QPerson *> (sender () ) ;
```
这样得到信号发射者QPerson类型的对象指针aPerson，它指向boy或girl。

使用aPerson指针，通过property()函数获取name属性的值，也可以获取动态属性sex的值。

因为在QPerson中，name 属性只用MEMBER关键字定义了一个私有变量表示这个属性，所以只能用property()读取此属性的值，也只能用setProperty()设 置此属性的值。

读取年龄时，直接用了接口函数，即:

```cpp
int hisAge=aPerson->age() ;
```
当然也可以采用property()函数获取年龄，即:
```cpp
int hisAge=aPerson->property ("age") . toInt() ;
```

因为定义age属性时用READ和WRITE指定了公共的接口函数，既可以通过property() 和setProperty() 进行属性读写，也可以直接使用接口函数进行读写。当然，直接使用接口函数速度更快。

界面上两个分别用于设置boy和girl年龄的spinBox 的valueChanged(int)信号与槽函数on_ spin_valueChanged(int) 关联，槽函数代码如下:

```cpp
void QmyWidget: :on_spin_valueChanged(int arg1)
{
	//响应界面上spinBox的valueChanged(int)信号
	Q_ UNUSED(arg1) ;
	QSpinBox *spinBox = qobject_ cast<QSpinBox *> (sender()) ;
	if (spinBox->property ("isBoy").toBool())
		boy->setAge (spinBox->value());
	else
		girl->setAge (spinBox->value());
}
```
这里也使用了**信号发射者的类型投射**，投射为QSpinBox类型指针spinBox,然后根据spinBox的动态属性isBoy的值，确定调用boy或girl的setAge() 函数。
  
这种编写代码的方式一般用于为多个同类型组件的同一信号编写-一个槽函数，在槽函数里区分信号来源分别做处理，避免为每个组件分别编写槽函数形成的代码冗余。

界面上 类的元对象信息 按钮的响应代码如下:
```cpp
void QmyWidget::on_btnClassInfo_clicked()
{
	//"类的元对象信息"按钮
	const QMetaObject * meta=boy->meta0bject();
	ui->textEdit->clear () ;
	ui->textEdit->appendPlainText("==元对象信息==\n");
	ui->textEdit->appendPlainText(
			QString("类名称: %1\n") .arg (meta->className()));
	ui->textEdit->appendPlainText ("property") ;
	for (int i=meta->propertyOffset() ; i<meta->propertyCount() ;i++)
	{
		QMetaProperty prop=meta->property(i);
		const char* propName=prop.name();
		QString propValue=boy->property(propName).toString();
		ui->textEdit->appendPlainText(QString("属性名称=%1，属性值=%2").arg(propName)
				.arg(propValue));
	}
	ui->textEdit->appendPlainText("");
	ui->textEdi t->appendPlainText("classInfo");
	for (int i=meta->classInfo0ffset(); i <meta->classInfoCount(); ++i)
	{
		QMetaClassInfo classInfo=meta->classInfo(i);
		ui->textEdit->appendPlainText(QString("Name=81; Value=82")
			.arg(classInfo.name()).arg(classInfo.value());
	}
}
```
代码里通过boy->metaObject() 获得对象boy的元对象。元对象类QMetaObject封装了访问类的元对象的各种接口函数，例如，QMetaObject:: className() 返回类的名称。

QMetaObject用于属性操作的函数有以下几种：
- propertyOffset(): 返回类的第-一个属性的序号，第-一个属性的序号不一-定是0。
- propertyCount(): 返回类的属性个数。
- QMetaProperty property(int index): 返回序号为index的属性对象,返回值是QMetaProperty 类型，它封装了对属性的更多特征查询功能，以及属性值的读写功能。

 QMetaClassInfo类封装了类的 classInfo 的访问接口函数,只有 name()和value() 两个接口函数。

元对象就介绍到这里。
