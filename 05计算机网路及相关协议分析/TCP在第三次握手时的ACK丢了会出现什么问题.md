当Client 端 三次握手是收到Server 的SYN + ACK 应答后， 其状态变为established，并发送ACK包给Server

**此时ACK在网络中丢失，会怎么样？** 
> Server端该TCP连接的状态为SYN_RECV, 并且依次等待3s,6s,12s后**重新发送SYN+ACK
> 包，以便Client 重新发送ACK包**，Server重发SYN+ACK的次数，可以通过修改配置文件修改（/proc/sys/net/ipv4/tcp_synack_retries），默认是5；
> 如果指定的次数后，仍然未收到ACK应答， 那么一段时间后，Server会自动关闭这个连接

>但是Client，认为这个连接已经建立，如果Client向Server继续发送数据，Server端将以RST包（用于强制关闭tcp连接）响应，方能感知到Server出现错误。

### 拓展
如果是故意不发ACK，就是大量连接只发送握手信号SYN，不发第三个SYN+ACK，也不发数据，那这个就是简单直接的SYN洪水攻击了，属于安全问题。
