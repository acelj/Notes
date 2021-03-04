> `int main(int argc, char* argv[])`  或者是 `int main(int argc, char** argv)`   里面的参数是什么意义呢？

 - argc 是 `argument count`的缩写，表示传入main函数的**参数个数**；
 - argv 是 `argument vector`的缩写，表示传入main函数的**参数序列或指针**，并且第一个参数`argv[0]`一定是程序的名称（是固定的值），是包含了程序所在的完整路径，因此准确的说我们输入的main函数的参数个数应该是**argc-1个**；
 
下面是代码示例：

```cpp
#include <iostream>
using namespace std;

// 如果在程序后面加入参数， 就会打印多个参数，例如在cmd中加入参数执行，或者在linux中执行的时候加上参数会打印多个。但argc[0] 始终是程序的路径。
int main(int argc, char** argv)
{
	for (int i =0; i<argc; i++)
		cout << "argc [" << i << "] is " << argv[i] << " "; 
	return 0;
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210304192953236.png)

下面放上一个opencv 显示图片的例子：

```cpp
#include <iostream>
#include <core/core.hpp>
#include <highgui/highgui.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat img = imread(argv[1);
	imshow("mypic", img);
	waitKey();
	return 0;
}
```
在linux中执行的时候只需要在执行文件后面加上一个需要打开图片的例子就行了`./xxx  图片路径`.
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210304193621357.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
> ps: 这里的argc和argv只是参数，可以更换名字，只是现在学习的都按照前人的习惯而已。
 
