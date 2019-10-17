#canal 



Canal，有水渠管道的意思，主要用于基于MySQL数据库的增量日志信息解析，提供增量数据订阅和消费。

例如在bilibili的网站中，用户在视频下的评论，也需要在up主的创作中心显示，此时就需要用到canal通过对数据库日志的解析来实时获取更新。canal对数据库进行解析后交由kafka,hbase,RocketMQ等进行消费

## 工作原理

canal的工作原理依赖于数据库的主从复制原理

###MySQL主从复制原理

 ![mysql-master-slave](https://raw.githubusercontent.com/weixiao619/mycode/master/image/canal.png) 



- MySQL master 将数据变更写入二进制日志( binary log, 其中记录叫做二进制日志事件binary log events，可以通过 show binlog events 进行查看)
- MySQL slave 将 master 的 binary log events 拷贝到它的中继日志(relay log)
- MySQL slave 重放 relay log 中事件，将数据变更反映它自己的数据



### canal工作原理

- canal 模拟 MySQL slave 的交互协议，伪装自己为 MySQL slave ，向 MySQL master 发送dump 协议
- MySQL master 收到 dump 请求，开始推送 binary log 给 slave (即 canal )
- canal 解析 binary log 对象(原始为 byte 流)

