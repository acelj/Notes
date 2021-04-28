
>deque（双端队列）是由一段一段的定量连续空间构成，可以向两端发展，因此不论在尾部或头部安插元素都十分迅速。 在中间部分安插元素则比较费时，因为必须移动其它元素。

## 初始化

```cpp
#include<deque>  // 需使用 using std::deque;

定义的实现代码
deque<int> a; // 定义一个int类型的双端队列a
deque<int> a(10); // 定义一个int类型的双端队列a，并设置初始大小为10
deque<int> a(10, 1); // 定义一个int类型的双端队列a，并设置初始大小为10且初始值都为1
deque<int> b(a); // 定义并用双端队列a初始化双端队列b
deque<int> b(a.begin(), a.begin()+3); // 将双端队列a中从第0个到第2个(共3个)作为双
// 端队列b的初始值

// 除此之外，还可以直接使用数组来初始化向量：
int n[] = { 1, 2, 3, 4, 5 };
// 将数组n的前5个元素作为双端队列a的初值
// 说明：当然不包括arr[4]元素，末尾指针都是指结束元素的下一个元素，
// 这个主要是为了和deque.end()指针统一。
deque<int> a(n, n + 5); 
deque<int> a(&n[1], &n[4]); // 将n[1]、n[2]、n[3]作为双端队列a的初值
```
## 操作函数
#### 容量函数
- 容器大小：deq.size();
- 容器最大容量：deq.max_size();
- 更改容器大小：deq.resize();
- 容器判空：deq.empty();
- 减少容器大小到满足元素所占存储空间的大小：deq.shrink_to_fit();
#### 添加函数
- 头部添加元素：deq.push_front(const T& x);
- 末尾添加元素：deq.push_back(const T& x);
- 任意位置插入一个元素：deq.insert(iterator it, const T& x);
- 任意位置插入 n 个相同元素：deq.insert(iterator it, int n, const T& x);
- 插入另一个向量的 [forst,last] 间的数据：deq.insert(iterator it, iterator first, iterator last);
#### 删除函数
- 头部删除元素：deq.pop_front();
- 末尾删除元素：deq.pop_back();
- 任意位置删除一个元素：deq.erase(iterator it);
- 删除 [first,last] 之间的元素：deq.erase(iterator first, iterator last);
- 清空所有元素：deq.clear();
#### 访问函数
- 下标访问：deq[1]; // 并不会检查是否越界
- at 方法访问：deq.at(1); // 以上两者的区别就是 at 会检查是否越界，是则抛出 out of range 异常
- 访问第一个元素：deq.front();
- 访问最后一个元素：deq.back();
#### 其他函数
- 多个元素赋值：deq.assign(int nSize, const T& x); // 类似于初始化时用数组进行赋值
- 交换两个同类型容器的元素：swap(deque&);
## 迭代器算法
#### 迭代器
- 开始迭代器指针：deq.begin();
- 末尾迭代器指针：deq.end(); // 指向最后一个元素的下一个位置
- 指向常量的开始迭代器指针：deq.cbegin(); // 意思就是不能通过这个指针来修改所指的内容，但还是可以通过其他方式修改的，而且指针也是可以移动的。
- 指向常量的末尾迭代器指针：deq.cend();
- 反向迭代器指针，指向最后一个元素：deq.rbegin();
- 反向迭代器指针，指向第一个元素的前一个元素：deq.rend();
##### 算法
- 遍历元素

```cpp
deque<int>::iterator it;
for (it = deq.begin(); it != deq.end(); it++)
    cout << *it << endl;
// 或者
for (int i = 0; i < deq.size(); i++) {
    cout << deq.at(i) << endl;
}
```

- 元素翻转

```cpp
#include <algorithm>
reverse(deq.begin(), deq.end());
```

- 元素排序

```cpp
#include <algorithm>
sort(deq.begin(), deq.end()); // 采用的是从小到大的排序

// 如果想从大到小排序，可以采用先排序后反转的方式，也可以采用下面方法:
// 自定义从大到小的比较器，用来改变排序方式
bool Comp(const int& a, const int& b) {
    return a > b;
}

sort(deq.begin(), deq.end(), Comp);
```
## 总结
可以看到，deque 与 vector 的用法基本一致，除了以下几处不同：

- deque 没有 capacity() 函数，而 vector 有；
- deque 有 push_front() 和 pop_front() 函数，而 vector 没有；
- deque 没有 data() 函数，而 vector 有。
