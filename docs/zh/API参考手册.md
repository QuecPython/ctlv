# TLV序列化格式 —— C语言实现（ctlv）

TLV（Type-Length-Value）是一种数据编码格式，由数据的类型（Tag）、数据的长度（Length）、数据的值（Value）组成。这种格式在数据通信、协议设计等领域广泛应用，因为它简单高效且具有良好的可扩展性。 

`ctlv`是用 C 语言编写的 TLV 结构编解码器，在串口、蓝牙甚至网络数据传输中比较常用。

## 错误码

头文件：`tlv.h`

枚举类型：`tlv_error_t`

枚举值：

- `NO_ERROR`：无错误
- `NOT_INITIALIZED`：未初始化
- `TAG_BAD_VAL`：TAG非法
- `TAG_IS_INSUFF`：TAG域解析错误（输入缓冲数据长度不足）
- `LEN_IS_INSUFF`：长度域解析错误（输入缓冲数据长度不足）
- `VAL_IS_INSUFF`：数据域解析错误（输入缓冲数据长度不足）
- `VAL_IS_OVERFLOW`：数据域解析溢出
- `BUF_IS_NULL`：输入缓冲为空
- `ALLOC_MEMORY_ERROR`：内存申请错误
- `LIST_OPERATION_ERR`：TLV缓冲链表插入失败

## TLV流式IO

头文件：`io_stream.h`

### TVL初始化IO流

函数原型：`tlv_uint32_t tlv_init(uart_port_e port, uart_cfg_t *config, tlv_parse_callback parse_cb, tlv_uint16_t * tags_buff, tlv_uint16_t tags_num);`

参数：

- `port`：串口号
- `config`：串口配置
- `parser_cb`：解析回调函数
- `tags_buff`：合法TAG

返回值：tlv io句柄

### 获取当前TLV帧

函数原型：`tlv_base_t *tlv_get_value(tlv_uint32_t tlv);`

参数：

- `tlv`：`tlv_ios_t`

返回值：`tlv_base_t`

### 删除当前TLV帧

函数原型：`void tlv_dest_value(tlv_uint32_t tlv);`

参数：

- `tlv`：`tlv_ios_t`

返回值：无

### 发送一帧TLV

函数原型：`tlv_error_t tlv_send(tlv_uint32_t tlv, send_data_type *send_data_array, tlv_uint16_t array_len);`

参数：

- `tlv`：`tlv_ios_t`
- `send_data_array`：待发送数据
- `array_len`：数据长度

## TLV解析

头文件：`tlv.h`

### 创建解析暂存区

函数原型：`tlv_box_t *tlv_box_create(void);`

参数：无

返回值：暂存区指针

### buffer解析

函数原型：`tlv_error_t tlv_parse(tlv_box_t *box, tlv_uint8_t *buffer, tlv_uint32_t buffersize, tlv_uint8_t byteorder);`

参数：

- `box`：暂存区指针
- `buffer`：待解析数据指针
- `buffersize`：数据长度
- `byteorder`：字节对齐方式（`LITTLE_ENDIAN_PLATFORM` or `BIG_ENDIAN_PLATFORM`）

返回值：错误码

### 删除暂存区

函数原型：`tlv_error_t tlv_box_destroy(tlv_box_t *box);`

参数：

- `box`：暂存区指针

返回值：错误码

### 获取暂存区buffer

函数原型：`tlv_uint8_t *tlv_box_get_buffer(tlv_box_t *box);`

参数：

- `box`：暂存区指针

返回值：暂存区buffer指针

### 获取暂存区buffer长度

函数原型：`tlv_int32_t tlv_box_get_size(tlv_box_t *box);`

参数：

- `box`：暂存区指针

返回值：长度

### 设置合法TAG

函数原型：`tlv_error_t tlv_set_tags(tlv_box_t *box, tlv_uint16_t *tags_buff, tlv_uint16_t tags_num);`

参数：

- `box`：暂存区指针
- `tags_buff`：TAG数组指针
- `tags_num`：TAG数量

### 读取TLV帧

函数原型：`tlv_base_t *tlv_box_get_value(tlv_box_t *box);`

参数：

- `box`：暂存区指针

返回值：`tlv_base_t`

### 删除TLV帧

函数原型：`void tlv_box_dest_value(tlv_box_t *box);`

参数：

- `box`：暂存区指针

返回值：无

### 获取指定TAG的数据长度

函数原型：`tlv_int16_t tlv_box_get_length(tlv_box_t *box, tlv_uint16_t tag);`

参数：

- `box`：暂存区指针
- `tag`：TAG

返回值：长度

### 设置TLV帧

函数原型：`tlv_error_t tlv_set_value(tlv_box_t *box, tlv_uint16_t tag, void *value, tlv_uint16_t length);`

参数：

- `box`：暂存区指针
- `tag`: TAG
- `value`：数据域指针
- `length`：数据长度

返回值：错误码

### 序列化

函数原型：`tlv_error_t tlv_box_serialize(tlv_box_t *box, tlv_uint8_t byteorder);`

参数：

- `box`：暂存区指针
- `byteorder`：字节对齐方式

返回值：无

