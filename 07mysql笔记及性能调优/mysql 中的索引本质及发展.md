###  mysql 中的索引本质及发展
　　mysql中为什么有索引，在大学中，我记得老师将的数据库就是说索引就类似课本前面的目录，当然这也不能算是错的，只是现在回过头来重新学习，觉得还是太浅了。
　　**索引**是帮助MySQL高效获取数据的**排好序**的**数据结构**。
  　　说到数据结构，我们必定会想起二叉树，红黑树，Btree等等。是的，我们今天讲的mysql索引从最初的发展开始一步一步讲为什么最后决定用**B+tree**这种数据结构。
  　　 ·最开始数据库的索引就是用二叉树（这里的二叉排序树）当做索引的，从下图左边看如果不用索引技术，从数据库中查找Col2 = 89这条数据，需要遍历前面6条数据，要知道数据库里面的数据是存储在磁盘中的，每次遍历就从磁盘中寻址，这个寻址操作是**非常耗时**的。（查找Col2 = 89操作，首先在计算机中先找到Col2 =89 这列，然后将Col2=89 这列前面的地址返回给计算机，最后计算机按照返回的地址获取查找的这一条数据，因为数据库中的数据可能不是同一时间插入进去的，所以在数据库中即使相邻的数据在计算机的硬盘中也是不在一起的）
  　　 后来有人提出索引的方式进行优化，按照下面右边的二叉树，将Col2列数据作为索引，如果还是查找Col2=89 这条数据，在二叉树中只需要遍历两次，就找到89这个节点，然后将地址返回给计算机，比一种方法节省了大量时间。（这里的存储的节点信息就是**按照索引数据值和地址**，以**key-value方式**进行存储的）。
  　　 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20210122150205179.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
  　　 为什么弃用了二叉排序树，原因很简单，如果插入的数据是从小到大的顺序插入的，这里的二叉树就会**退化成一个链表**，下面是将数据2,3,4,5,6依次插入到二叉排序树中。
  　　 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20210122153649186.png)
  　　 因此这里就有人想到用红黑树来代替上面的二叉排序树做索引了，避免了上面退化为链表的情况，这里用红黑树作为数据结构依次插入2,3,4,5,6,7,8。如下图所示。
  　　 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20210122154045278.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
  　　 那为什么数据库中的数据结构我不选择红黑树作为内部的数据结构呢，原因是当数据量很大师，比如：500百万条数据时，这时候用红黑树作为索引的数据结构，树的高度大概是20-25左右，也就是说有500百万条数据时，平均查询的次数就是12次左右，这在计算机和磁盘中来回寻址是非常慢的。这时就有人提出用Btree和B+tree，现在的数据库中用B+tree,是Btree的升级版。
  　　 这里新增数据库中hash算法的特点（不用）
  　　 1. 对索引的key进行一次hash计算就可以定位出数据存储的位置
  　　 2. 很多时候hash索引要比B+ 树更高效
  　　 3. 仅能满足“= ”， “IN”, **不支持范围查询**
  　　 4. 有hash冲突

　　**Btree**是一种什么样的数据结构，简单来说就是一种多叉树的数据结构，多叉来充分降低树的高度。
  　　 **BTree**特点
  　　 1. 叶子节点具有相同的深度，叶子节点的指针为空。
  　　 2. 所有索引元素不重复
  　　 3. 节点中的数据索引从左到右递增排列。
  　　 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20210122182807107.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
  　　 **B+tree**特点（BTree的升级）：多路平衡树
  　　 1. 非叶子节点不存储data（与BTree区别，可以存储更多索引），只存储索引（只含key，也就是冗余索引），这样可以放更多的索引
  　　 2. 叶子节点包含所有索引字段
  　　 3. 叶子节点用指针连接，提高区间访问的性能（**支持区间查询**，因为叶子节点是按照从小到大排列的）
  　　![在这里插入图片描述](https://img-blog.csdnimg.cn/20210122183650353.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
  　　 **B+ tree 中查找元素的思路**:（查找30为例）先将节点放在内存中15， 56  ，77，30 在15,和56之间，找到当中的地址，然后根据上面找的地址，在根据地址载入15,20,49这个节点 找到30在20和49之间（因为这个节点中的索引是排好序的，是可以用二分查找来查找的），然后将20,30的节点载入到内存进行比对，这样就能定位30这个索引，然后将对应的value也就是保存的地址拿出来，找出整行的数据。
  　　 这里有人就会发现一行存储的索引越多，那可以查询的数量级就越多，那么这个上限是多少呢，在mysql中，我们可以用一行命令查看mysql当中的一页数据大小：默认是16KB.
```cpp
show global status like 'Innodb apge size';

// 结果是   16kB
```
  　　 我们假设按照16KB算的话，3层数据全部放满，我们假设数据索引大小是8B, 旁边保存下一个地址的大小按照mysql默认分配的是6B, data数据按照1KB算的话：一个节点放满能保存的多少个索引呢？ 就是 (16KB /(8 + 6B) =1170个索引 ) 总共的话，就是1170 * 1170 * 16 = **2千多万**
  　　 如果mysql版本高的话，mysql内部是将非叶子节点全部放在内存中的（非叶子节点不会占用太多磁盘空间），这样就减少了非叶子节点在磁盘中的寻址过程。
  　　 MYISAM存储引擎和InnoDB存储引擎比较（**存储引擎都是形容表的**）
  　　 1. MYISAM存储引擎在电脑中生成的文件
  　　  xx.frm :   存储表的结构信息
  　　  xx.MYD ： 存储表中所有的数据
  　　  xx.MYI： 存储表中的索引（B+ tree）
  　　  **特点：**
  　　  **它的主键索引就是非聚集索引，它的索引是放在myi文件中，数据是放在myd文件中，数据和索引是分开的，这种索引就叫非聚集索引。**
  　　  看下面的图，如果按照col1索引去查找数据的话（还是以30为例），数据库先到myi文件中的查找30节点对应的value（0xF3）地址，然后根据地址在到MYD文件中查找col1=30一行的数据。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210122193420917.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
  　　 2. Innodb存储引擎在电脑中生成的文件（现在主要的是innodb）
  　　  xx.frm :   存储表的结构信息
  　　  xx.ibd： 存储表中所有的数据和索引（就是将myisam中的两个表合一了）
  　　  **特点：** 
  　　  · 表数据文件本身就是按B+Tree组织的一个索引结构文件
  　　  · 聚集索引- 叶子节点包含了完整的数据记录
  　　  	· 为什么建议InnoDB表**必须建主键**，并且推荐使用**整型**的**自增**主键？
  　　  	· 为什么非主键索引结构叶子节点存储的是主键值？（一致性和节省存储空间）
  　　  	· **它的主键索引是聚集索引，数据和索引放在一起的。聚集索引查询效率高，比myisam好。但是它的非主键索引是非聚集索引，如果按照非主见索引，下面第二张图，最后查询会找到主键，然后根据主键索引找到整行数据。**
  　　  	·为什么DMA必须建一个主键?     如果不建立主键，mysql会找到一个特征列建立主键，如果找不到特征列，mysql内部会自动建立一个隐藏主键，维护唯一性。**一张表有且仅有就一个聚集索引**。不建立主键，也会给mysql增加负担。
  　　 ·用整型自增当作主键，而不是其他，淘汰了uuid（uuid不是整型也不是自增类型）?
  　　  优点： 字符串比较大小 肯定比整型慢;  uuid占用的空间多，整型也能节约资源；如果是非自增的，放进去可能会较大破坏平衡，节点有的会往上提，放的是自增元素话，节点永远是往后后面放，都是重新开辟空间，不会破坏前面树的平衡。
  　　  维护自增方法：　可以用redis 、 一些中间件的组件。
  　　 ![dd](https://img-blog.csdnimg.cn/20210122195435935.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)![在这里插入图片描述](https://img-blog.csdnimg.cn/20210122200331628.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
  　　 **联合索引**：　索引最左前缀原理
  　　 在数据库中联合索引用的比较常见，一些主要的性能优化，在联合索引中更能体现。联合索引字面理解就是多个字段组合形成的索引。联合索引在底层还是以B+tree存储，叶子节点还是排好了序。按照**最左前缀原理进行排序**：先按照第一个字段排序，第一个字段相等，按照第二个排序，以此类推。
  　　 举例：
  　　 按照下面三条sql语句： 那一条会走索引
  ```cpp
select * from table where name = 'Bill' and age = 31;
select * from table where age= 30 and position = 'dev';
select * from table where position = 'manager';
```
  　　 答案是第一条，不能直接说是最左前缀原理就是这样规定回答，这样回答太简单了。因为按照第二条找的话，首先是找age ，这个直接跳过name，在表中就已经不是排好序了，就不能快速进行定位数据，就退化到查询全表；按照第一条先找name字段，找到后在找age字段，就会在name='Bill'中查找age=31的数据，因为找出来的name字段是排好序的，所以第一条才会走索引。  　　![d](https://img-blog.csdnimg.cn/20210122204638954.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
 
