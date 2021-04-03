虽然经常做的C++,Web 写的少，但是这个知识在面试中经常遇到，现在就记录一下。

Web的三个概念： Session 、 cookie、 application。

Session 和 Cookie 功能效果是差不多的，区别就是session 是记录在服务端的，Cookie是记录在客户端的。都是记录一系列状态的。
1. session是服务端存储，cookie是浏览器端存储
2. Cookie是把用户的数据写给用户的浏览器。
3. Session技术把用户的数据写到用户独占的session中。
4. Session对象由服务器创建，开发人员可以调用request对象的getSession方法得到session对象。

**Session解释**： 当访问服务某个网页的时候，会在服务器端的内存开辟一块内存，这块内存就叫做session，而这个内存是跟浏览器关联在一起的。这个浏览器指的是浏览器窗口，或者是浏览器的子窗口，意思就是，只允许当前这个Session对应的浏览器访问，就算是在同一个机器上新启动的浏览器也是无法访问的。而另外一个浏览器也需要记录session的话，就会再启动一个属于自己的session。

**另一种解释**：在WEB开发中，服务器可以为每个用户浏览器创建一个会话对象（session对象），注意：一个浏览器独占一个session对象(默认情况下)。因此，在需要保存用户数据时，**服务器程序可以把用户数据写到用户浏览器独占的session中**，当用户使用浏览器访问其它程序时，**其它程序可以从用户的session中取出该用户的数据**，为用户服务。

**原理**：HTTP协议是非连接性的，取完当前浏览器的内容，然后关闭浏览器后，链接就断开了，而没有任何机制去记录取出后的信息。而当需要访问同一个网站的另外一个页面时(**就好比如在第一个页面选择购买的商品后，跳转到第二个页面去进行付款**)这个时候取出来的信息，就读不出来了。所以必须要有一种机制让页面知道之前页面的内容。

**Session实现原理**： 当服务器创建完session对象后，会把session对象的id以**cookie**形式返回给客户端。这样，当用户保持当前浏览器的情况下再去访问服务器时，会把session的id传给服务器，**服务器根据session的id**来为用户提供相应的服务。

**问题**：如何知道浏览器和这个服务器中的session是一一对应的呢？又如何保证不会去访问其它的session呢？

**原理解答**：就是当访问一个页面的时候给浏览器创建一个独一无二的号码，也给同时创建的session赋予同样的号码。这样就可以在打开同一个网站的第二个页面时获取到第一个页面中session保留下来的对应信息（理解：当访问第二个页面时将号码同时传递到第二个页面。找到对应的session。）。这个号码也叫sessionID，session的ID号码，session的独一无二号码。

**session的两种实现方式（也就是传递方式）：第一种通过cookies实现。第二种通过URL重写来实现**

**第一种方式的理解**：就是把session的id 放在cookie里面（为什么是使用cookies存放呢，因为cookie有临时的，也有定时的，临时的就是当前浏览器什么时候关掉即消失，也就是说session本来就是当浏览器关闭即消失的，所以**可以用临时的cookie存放**。保存再cookie里的sessionID一定不会重复，因为是独一无二的。），当允许浏览器使用cookie的时候，session就会依赖于cookies，当浏览器不支持cookie后，就可以通过第二种方式获取session内存中的数据资源。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210403125239528.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

**第二种方式的理解**：在客户端不支持cookie的情况下使用。为了以防万一，也可以同时使用。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210403125624548.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

如果不支持cookie，必须自己编程使用URL重写的方式实现。
如何重写URL：通过response.encodeURL()方法
encodeURL()的两个作用

第一个作用：转码（说明：转中文的编码，或者一些其他特殊的编码。就好比如网页的链接中存在中文字符，就会转换成为一些百分号或者其他的符号代替。）

第二个作用：URL后面加入sessionID，当不支持cookie的时候，可以使用encodeURL()方法，encodeUTL()后面跟上sessionID，这样的话，在禁用cookie的浏览器中同时也可以使用session了。但是需要自己编程，只要链接支持，想用session就必须加上encodeURL()。

提示：**若想程序中永远支持session，那就必须加上encodeURL()，当别人禁用了cookie，一样可以使用session**。

