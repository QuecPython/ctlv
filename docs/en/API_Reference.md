# TLV Serialization Format - C Language Implementation (ctlv)

TLV (Type Length Value) is a data encoding format composed of the type of data (Tag), length of data (Length), and value of data (Value). This format is widely used in fields such as data communication and protocol design because it is simple, efficient, and has good scalability.

`ctlv` is a TLV structure codec written in C language, which is commonly used in serial port, Bluetooth, and even network data transmission.

## Error No.

header file：`tlv.h`

enum tyle：`tlv_error_t`

enum value：

- `NO_ERROR`
- `NOT_INITIALIZED`
- `TAG_BAD_VAL`
- `TAG_IS_INSUFF`
- `LEN_IS_INSUFF`
- `VAL_IS_INSUFF`
- `VAL_IS_OVERFLOW`
- `BUF_IS_NULL`
- `ALLOC_MEMORY_ERROR`
- `LIST_OPERATION_ERR`

## TLV IOSTREAM

header file：`io_stream.h`

### TVL IOSTREAM INIT

function define：`tlv_uint32_t tlv_init(uart_port_e port, uart_cfg_t *config, tlv_parse_callback parse_cb, tlv_uint16_t * tags_buff, tlv_uint16_t tags_num);`

args：

- `port`：serial port number
- `config`：serial port configure
- `parser_cb`
- `tags_buff`

return：`tlv_ios_t`

### get tlv value

function define：`tlv_base_t *tlv_get_value(tlv_uint32_t tlv);`

args：

- `tlv`：`tlv_ios_t`

return：`tlv_base_t`

### del tlv value

function define：`void tlv_dest_value(tlv_uint32_t tlv);`

args：

- `tlv`：`tlv_ios_t`

return：无

### send TLV value

function define：`tlv_error_t tlv_send(tlv_uint32_t tlv, send_data_type *send_data_array, tlv_uint16_t array_len);`

args：

- `tlv`：`tlv_ios_t`
- `send_data_array`
- `array_len`：data length

## Parse TLV

header file：`tlv.h`

### create TLV parse box

function define：`tlv_box_t *tlv_box_create(void);`

args：None

return：`tlv_box_t`

### parse buffer

function define：`tlv_error_t tlv_parse(tlv_box_t *box, tlv_uint8_t *buffer, tlv_uint32_t buffersize, tlv_uint8_t byteorder);`

args：

- `box`：box pointer
- `buffer`：data buffer
- `buffersize`：buffer length
- `byteorder`：bytes order（`LITTLE_ENDIAN_PLATFORM` or `BIG_ENDIAN_PLATFORM`）

return：error no.

### del box

function define：`tlv_error_t tlv_box_destroy(tlv_box_t *box);`

args：

- `box`：box pointer

return：error no.

### get box buffer

function define：`tlv_uint8_t *tlv_box_get_buffer(tlv_box_t *box);`

args：

- `box`：box pointer

return:  box buffer pointer

### get box buffer length

function define：`tlv_int32_t tlv_box_get_size(tlv_box_t *box);`

args：

- `box`：box pointer

return: length

### set TAGs

function define：`tlv_error_t tlv_set_tags(tlv_box_t *box, tlv_uint16_t *tags_buff, tlv_uint16_t tags_num);`

args：

- `box`：box pointer
- `tags_buff`：TAGs
- `tags_num`：TAG numbers

return: `tlv_error_t`

### read tlv value

function define：`tlv_base_t *tlv_box_get_value(tlv_box_t *box);`

args：

- `box`：box pointer

return: `tlv_base_t`

### del tlv value

function define：`void tlv_box_dest_value(tlv_box_t *box);`

args：

- `box`：box pointer

return: NULL

### get tlv value length

function define：`tlv_int16_t tlv_box_get_length(tlv_box_t *box, tlv_uint16_t tag);`

args：

- `box`：box pointer
- `tag`：TAG

return: length

### set TLV value

function define：`tlv_error_t tlv_set_value(tlv_box_t *box, tlv_uint16_t tag, void *value, tlv_uint16_t length);`

args：

- `box`：box pointer
- `tag`: TAG
- `value`：value data pointer
- `length`：value data length

return: `tlv_error_t`

### serialize tlv value

function define：`tlv_error_t tlv_box_serialize(tlv_box_t *box, tlv_uint8_t byteorder);`

args：

- `box`：box pointer
- `byteorder`：byte order mode

return: `tlv_error_t`

