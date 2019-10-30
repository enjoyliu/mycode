# Kafka简介

Kafka 是由 LinkedIn 开发的一个分布式的消息系统，使用 Scala 编写，它以可水平扩展和高吞吐率而被广泛使用。

## 背景介绍

### Kafka创建背景

Kafka 是一个消息系统，原本开发自 LinkedIn，用作 LinkedIn 的活动流（Activity Stream）和运营数据处理管道（Pipeline）的基础。现在它已被多家不同类型的公司作为多种类型的数据管道和消息系统使用。

活动流数据是几乎所有站点在对其网站使用情况做报表时都要用到的数据中最常规的部分。活动数据包括页面访问量（Page View）、被查看内容方面的信息以及搜索情况等内容。这种数据通常的处理方式是先把各种活动以日志的形式写入某种文件，然后周期性地对这些文件进行统计分析。运营数据指的是服务器的性能数据（CPU、IO 使用率、请求时间、服务日志等等数据)。运营数据的统计方法种类繁多。

近年来，活动和运营数据处理已经成为了网站软件产品特性中一个至关重要的组成部分，这就需要一套稍微更加复杂的基础设施对其提供支持。

### Kafka 简介

Kafka 是一种分布式的，基于发布 / 订阅的消息系统。主要设计目标如下：

- 以时间复杂度为 O(1) 的方式提供消息持久化能力，即使对 TB 级以上数据也能保证常数时间复杂度的访问性能。
- 高吞吐率。即使在非常廉价的商用机器上也能做到单机支持每秒 100K 条以上消息的传输。
- 支持 Kafka Server 间的消息分区，及分布式消费，同时保证每个 Partition 内的消息顺序传输。
- 同时支持离线数据处理和实时数据处理。
- Scale out：支持在线水平扩展。

### 为何使用消息系统

- **解耦**在项目启动之初来预测将来项目会碰到什么需求，是极其困难的。消息系统在处理过程中间插入了一个隐含的、基于数据的接口层，两边的处理过程都要实现这一接口。这允许你独立的扩展或修改两边的处理过程，只要确保它们遵守同样的接口约束。
- **冗余**有些情况下，处理数据的过程会失败。除非数据被持久化，否则将造成丢失。消息队列把数据进行持久化直到它们已经被完全处理，通过这一方式规避了数据丢失风险。许多消息队列所采用的 " 插入 - 获取 - 删除 " 范式中，在把一个消息从队列中删除之前，需要你的处理系统明确的指出该消息已经被处理完毕，从而确保你的数据被安全的保存直到你使用完毕。
- **扩展性**因为消息队列解耦了你的处理过程，所以增大消息入队和处理的频率是很容易的，只要另外增加处理过程即可。不需要改变代码、不需要调节参数。扩展就像调大电力按钮一样简单。
- **灵活性 & 峰值处理能力**在访问量剧增的情况下，应用仍然需要继续发挥作用，但是这样的突发流量并不常见；如果为以能处理这类峰值访问为标准来投入资源随时待命无疑是巨大的浪费。使用消息队列能够使关键组件顶住突发的访问压力，而不会因为突发的超负荷的请求而完全崩溃。
- **可恢复性**系统的一部分组件失效时，不会影响到整个系统。消息队列降低了进程间的耦合度，所以即使一个处理消息的进程挂掉，加入队列中的消息仍然可以在系统恢复后被处理。
- **顺序保证**在大多使用场景下，数据处理的顺序都很重要。大部分消息队列本来就是排序的，并且能保证数据会按照特定的顺序来处理。Kafka 保证一个 Partition 内的消息的有序性。
- **缓冲**在任何重要的系统中，都会有需要不同的处理时间的元素。例如，加载一张图片比应用过滤器花费更少的时间。消息队列通过一个缓冲层来帮助任务最高效率的执行———写入队列的处理会尽可能的快速。该缓冲有助于控制和优化数据流经过系统的速度。
- **异步通信**很多时候，用户不想也不需要立即处理消息。消息队列提供了异步处理机制，允许用户把一个消息放入队列，但并不立即处理它。想向队列中放入多少消息就放多少，然后在需要的时候再去处理它们。



## Kafka系统介绍

### Kafka 是什么

- Apache Kafka是一个开源消息系统，由Scala写成。是由Apache软件基金会开发的一个开源消息系统项目，该项目的目标是为处理实时数据提供一个统一、高通量、低等待的平台。
- Kafka是一个分布式消息队列：生产者、消费者的功能。它提供了类似于JMS的特性，但是在设计实现上完全不同，此外它并不是JMS规范的实现。
- Kafka对消息保存时根据Topic进行归类，发送消息者称为Producer,消息接受者称为Consumer,此外kafka集群有多个kafka实例组成，每个实例(server)成为broker。无论是kafka集群，还是producer和consumer都依赖于zookeeper集群保存一些meta信息，来保证系统可用性

### Kafka 核心组件

- **Producer**：消息生产者，产生的消息将会被发送到某个topic

- **Consumer**：消息消费者，消费的消息内容来自某个topic

- **Consumer Group**每个 Consumer 属于一个特定的 Consumer Group（可为每个 Consumer 指定 group name，若不指定 group name 则属于默认的 group）。一个group联合订阅一组特定的topic

- **Topic**：消息根据topic进行归类，topic其本质是一个目录，即将同一主题消息归类到同一个目录,一个消费着可以订阅来自brokers的一个或多个topic，并通过pulling操作来消费来自brokers的数据

- A stream of messages of a particular type is defined by a topic. 

- **Partition**：Parition 是物理上的概念，每个 Topic 包含一个或多个 Partition.一个consumer通常会连续的从一个特定的partition消费数据.partition是最小的并行单元，即一个partition任一时间只能由一个消费者进行消费，一般情况一个topic的partition比group中的consumer的个数要多。0

- **Broker**：Kafka 集群包含一个或多个服务器，这种服务器被称为 broker，一个broker可以有多个Broker

- The published messages are then stored at a set of servers called brokers.

  **Zookeeper**：zookeeper集群不属于kafka内的组件，但kafka依赖zookeeper集群保存meta信息，所以在此做声明其重要性。

### Kafka 整体架构以及解析

![Kafka设计解析（一）：Kafka背景及架构介绍](https://static001.infoq.cn/resource/image/bc/c8/bc99c2a3176ee1695a3d4f1f4f08a5c8.png)







![image-20191029155504291](https://raw.githubusercontent.com/weixiao619/mycode/master/image/kafka_Arch.png)

##### Kafka数据处理步骤

- 1、Producer产生消息，发送到Broker中
- 2、Leader状态的Broker接收消息，写入到相应topic中
- 3、Leader状态的Broker接收完毕以后，传给Follow状态的Broker作为副本备份
- 4、Consumer消费Broker中的消息

##### Kafka名词解释和工作方式

- Producer

  消息生产者，就是向kafka broker发消息的客户端。

- Consumer

  消息消费者，向kafka broker取消息的客户端

- Topic

  可以理解为一个队列。

- Consumer Group （CG）

  这是kafka用来实现一个topic消息的广播（发给所有的consumer）和单播（发给任意一个consumer）的手段。一个topic可以有多个CG。topic的消息会复制（不是真的复制，是概念上的）到所有的CG，但每个partion只会把消息发给该CG中的一个consumer。如果需要实现广播，只要每个consumer有一个独立的CG就可以了。要实现单播只要所有的consumer在同一个CG。用CG还可以将consumer进行自由的分组而不需要多次发送消息到不同的topic。

- Broker

  一台kafka服务器就是一个broker。一个集群由多个broker组成。一个broker可以容纳多个topic。

- Partition

  为了实现扩展性，一个非常大的topic可以分布到多个broker（即服务器）上，一个topic可以分为多个partition，每个partition是一个有序的队列。partition中的每条消息都会被分配一个有序的id（offset）。kafka只保证按一个partition中的顺序将消息发给consumer，不保证一个topic的整体（多个partition间）的顺序。一个Partition只能同时被一个Consumer消费。

##### Consumer与topic关系

kafka只支持Topic

- 每个group中可以有多个consumer，每个consumer属于一个consumer group；通常情况下，一个group中会包含多个consumer，这样不仅可以提高topic中消息的并发消费能力，而且还能提高"故障容错"性，如果group中的某个consumer失效那么其消费的partitions将会有其他consumer自动接管。
- 对于Topic中的一条特定的消息，只会被订阅此Topic的每个group中的其中一个consumer消费，此消息不会发送给一个group的多个consumer；那么一个group中所有的consumer将会交错的消费整个Topic，每个group中consumer消息消费互相独立，我们可以认为一个group是一个"订阅"者。
- 在kafka中,一个partition中的消息只会被group中的一个consumer消费(同一时刻)；
  一个Topic中的每个partions，只会被一个"订阅者"中的一个consumer消费，不过一个consumer可以同时消费多个partitions中的消息。
- kafka的设计原理决定,对于一个topic，同一个group中不能有多于partitions个数的consumer同时消费，否则将意味着某些consumer将无法得到消息。

*kafka只能保证一个partition中的消息被某个consumer消费时是顺序的；事实上，从Topic角度来说,当有多个partitions时,消息仍不是全局有序的。*

##### Kafka消息的分发

- Producer客户端负责消息的分发

- kafka集群中的任何一个broker都可以向producer提供metadata信息,这些metadata中包含*"集群中存活的servers列表"*、*"partitions leader列表"*等信息；

- 当producer获取到metadata信息之后, producer将会和Topic下所有partition leader保持socket连接；

- 消息由producer直接通过socket发送到broker，中间不会经过任何"路由层"。事实上，消息被路由到哪个partition上由producer客户端决定，比如可以采用"random""key-hash""轮询"等。

  *如果一个topic中有多个partitions,那么在producer端实现"消息均衡分发"是必要的。*

- 在producer端的配置文件中,开发者可以指定partition路由的方式。

- Producer消息发送的应答机制

  设置发送数据是否需要服务端的反馈,有三个值0,1,-1

  0: producer不会等待broker发送ack

  1: 当leader接收到消息之后发送ack

  -1: 当所有的follower都同步消息成功后发送ack

  *request.required.acks=0*

![image-20191029160412230](https://raw.githubusercontent.com/weixiao619/mycode/master/image/kafka_log.png)

如图所示为分发的模式，内存索引中并不直接存放messageId,而是存放offset

**Consumer的负载均衡**

当一个group中,有consumer加入或者离开时,会触发partitions均衡.均衡的最终目的,是提升topic的并发消费能力，步骤如下：

- 1、假如topic1,具有如下partitions: P0,P1,P2,P3
- 2、加入group A 中,有如下consumer: C0,C1
- 3、首先根据partition索引号对partitions排序: P0,P1,P2,P3
- 4、根据consumer.id排序: C0,C1
- 5、计算倍数: M = [P0,P1,P2,P3].size / [C0,C1].size,本例值M=2(向上取整)
- 6、然后依次分配partitions: C0 = [P0,P1],C1=[P2,P3],即Ci = [P(i * M),P((i + 1) * M -1)]



**Tips**

- kafka中并不存放精确的messageId
- 生产者可以一次提交多个message的集合，虽然消费者会多次消费
- 仅仅依赖系统循环，避免了double buffering
- kafka中的数据可以被多次消费，保留特定时间（可以配置）后可以删除，便于数据的同步和回滚

-