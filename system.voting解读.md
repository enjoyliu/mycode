# system合约

## voting.cpp







下面介绍该cpp文件中的函数

### regproducer()

**功能：** 注册生产者帐号

**参数：** 

~~~cpp
const account_name producer, 
const eosio::public_key& producer_key,
const std::string& url, 
uint16_t location
~~~

**过程：** 

1.首先验证输入格式的正确性，并进行验证

2.检查该生产者是否已经注册，如果已经注册就更新信息，如果没有就注册并复制。



### upproducer()

**功能： ** 注销生产者

**参数：** 

```cpp
const account_name producer, 
```

**过程：** 

1.首先验证输入格式的正确性，并进行验证

2.如果找到该生产者，就把它的状态变为未激活



### update_elected_producers()

**功能：** 更新被选中的生产者结点，即BP结点

**参数：** 

```cpp
block_timestamp block_time
```

**过程：** 

1.首先更新gstate中的bp结点列表为输入的时间

2.然后根据规则更新BP结点列表

### stake2vote()

**功能： ** 投票权重衰减的计算公式

**参数：** 

```cpp
int64_t staked
```

**过程：** 

```cpp
double weight = int64_t( (now() - (block_timestamp::block_timestamp_epoch /1000)) / (seconds_per_day * 7) )  / double( 52 );
 return double(staked) * std::pow( 2, weight );
```



### voteproducer()

**功能： **  更新被选中的生产者结点，即BP结点

**参数：** 

```cpp
const account_name voter_name, 
const account_name proxy, 
const std::vector<account_name>& producers
```

**过程：** 

1.进行验证

2.更新投票信息



### update_votes()

**功能： **  voteproducer函数中更新票数的具体过程

**参数：** 

```cpp
const account_name voter_name, 
const account_name proxy, 
const std::vector<account_name>& producers
```

**过程：** 

1.检查是否为代理账户投票，之后分别检测相关信息是否符合要求：投票总数小于30，代理账户不能再使用代理，自己不能交给自己代理，必须先抵押然后才能投票等等）

2.如果投票者第一次投票，我们要把它的抵押额更新/添加到EOS总的抵押额度上

3.根据该投票者抵押的数额，计算他的投票权重

4.计算之前投票的权重是否丢失，如果丢失则在总的投票权重中减去这一部分

5.将增加的投票更新到系统上





### regproxy()

**功能：**   注册一个账户为代理账户

**参数：** 

```cpp
const account_name proxy,
bool isproxy
```

**过程：** 





### propagate_weight_change()

**功能： **   更新投票的权重

**参数：** 

```cpp
const voter_info& voter
```

**过程：** 

