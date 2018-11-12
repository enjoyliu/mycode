# system合约

## producer_pay.cpp



```cpp
const int64_t  min_pervote_daily_pay = 100'0000;
const int64_t  min_activated_stake   = 150'000'000'0000;  //15%激活
const double   continuous_rate       = 0.04879;          // 5% annual rate
const double   perblock_rate         = 0.0025;           // 0.25%
const double   standby_rate          = 0.0075;           // 0.75%
const uint32_t blocks_per_year       = 52*7*24*2*3600;   // the number of half seconds per year  --half seconds a block
const uint32_t seconds_per_year      = 52*7*24*3600;
const uint32_t blocks_per_day        = 2 * 24 * 3600;
const uint32_t blocks_per_hour       = 2 * 3600;
const uint64_t useconds_per_day      = 24 * 3600 * uint64_t(1000000);
const uint64_t useconds_per_year     = seconds_per_year*1000000ll;
```





 Producer_pay　主要是负责支付各种节点的goc奖励，goc每年增值5%，其中分配比例如下

```cpp
   const double   goc_bp_rate = 0.2;   // 1% for BP 

   const double   goc_vote_rate = 0.1; // 0.5% for BP votes

   const double   goc_gn_rate = 0.15;  // 0.75% for GN

   const double   goc_wps_rate = 0.55; // 2.75% for WPS
```

cpp文件中的以上常量规定了各种节点的收益比例。

下面对该文件中的一些函数进行介绍

### onblock()

**功能：**  启动区块

**参数：**

~~~cpp
onblock( block_timestamp timestamp,
    account_name producer )
~~~

**过程：**

1.进行验证后，判断当前的抵押数额是否小于最小数目，若小于则返回。（EOS有15%以上的投票活跃度时，主网才会激活）

2.如果还没有开始产生收益，则初始化。

3.检查该生产者是否创建了对应的对象，如果没有则创建一个

4.每分钟更新一次生产者，每0.5秒更新一次区块的时间戳



### claimreward()

**功能：**按之前规定的比例，新生区块后分配奖励，生成奖励每天一次，提案的奖励每周一次

**参数：**

```cpp
claimrewards( const account_name& owner )
```



**过程：** 

1.验证身份后，检查生产者是否为激活状态，然后检查是否激活；

2.首先进行出块奖励的分配，检查距离上次分配是否已经过去一天(规定的间隔时间)；

3.然后开始声明，声明完成后更新gstate的参数

4.之后进行goc独有的投票奖励的分配，检查距离上次分配是否间隔一周

5.将所有投票结束的提案以及还没有执行的提案添加到容器中

6.将奖励进行声明，之后更新gstate的参数

7.然后GOC对已经声明但还未支付的奖励进行支付





