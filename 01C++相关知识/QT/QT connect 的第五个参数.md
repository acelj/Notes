

> 发送者： 是指当前调用emit 出发信号的线程。 

>1)自动连接(AutoConnection)，默认的连接方式，如果信号与槽，也就是发送者与接受者在同一线程，等同于直接连接；如果发送者与接受者处在不同线程，等同于队列连接。
> 2)直接连接(DirectConnection)，当信号发射时，槽函数立即直接调用。无论槽函数所属对象在哪个线程，槽函数总在发送者所在线程执行，即槽函数和信号发送者在同一线程
> 3)队列连接(QueuedConnection)，当控制权回到接受者所在线程的事件循环时，槽函数被调用。槽函数在接受者所在线程执行，即槽函数与信号接受者在同一线程
> 4)锁定队列连接(QueuedConnection)
> Qt::BlockingQueuedConnection：槽函数的调用时机与Qt::QueuedConnection一致，不过发送完信号后发送者所在线程会阻塞，直到槽函数运行完。接收者和发送者绝对不能在一个线程，否则程序会死锁。在多线程间需要同步的场合可能需要这个。
> 5)单一连接(QueuedConnection)
> Qt::UniqueConnection：这个flag可以通过按位或（|）与以上四个结合在一起使用。当这个flag设置时，当某个信号和槽已经连接时，再进行重复的连接就会失败。也就是避免了重复连接


来源： 
https://blog.csdn.net/peterbig/article/details/99722345
