1. 先说一下gcc, gcc是GNU编译器套件，可以简单的理解成为是编译器，可以编译很多种编程语言（C,C++，java等），当程序只有一个源文件（很少的时候），就可以直接用gcc去编译它。
2. 如果当项目出现了很多源文件，这时候就出现了make工具，make工具可以看成一个智能批处理工具，本身并没有编译和链接的功能，而是用类似于批处理的方式通过调用makefile文件中用户指定的命令来进行编译和链接的。
3. makefile 是什么呢？ makefile 命令中就包含了调用gcc，去编译某个源文件的命令。后面接着依赖项，makefile还是需要掌握基本的命令操作的。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210226230817480.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

4. 当项目变得大了后，makefile通常是自动生成的。
5. 此时就出现了Cmake，cmake可以更加简单的生成makefile文件给上面的那个make用，当然cmake还有其他的功能，就是可以跨平台生成对应平台能用makefile，不用自己手动的修改。
6. 那么cmake通过什么去生成makefile？ 这时cmakelists.txt 文件就出来了，通过cmakelists.txt文件生成makefile。（）**cmakelist.txt 文件是需要手动写**，这时候就需要掌握里面的语法内容了。
7. 如果是在windows或者是在ide平台上，可以直接用图形化界面去完成上面的一系列操作。
