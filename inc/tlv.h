/*
 *  COPYRIGHT NOTICE  
 *  Copyright (C) 2015, Jhuster, All Rights Reserved
 *  Author: Jhuster(lujun.hust@gmail.com)
 *  
 *  https://github.com/Jhuster/TLV
 *   
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published
 *  by the Free Software Foundation; either version 2.1 of the License, 
 *  or (at your option) any later version.
 */
#ifndef __TLV_BOX_H__
#define __TLV_BOX_H__

#include "key_list.h"
#include "tlv_types.h"

#ifdef __cplusplus
extern "C" {
#endif
	
#define EMV_TAGS_LENTH 	146

typedef struct _tlv_base 
{
    tlv_uint16_t tag;
    tlv_uint16_t length;
    tlv_uint8_t *value;
} tlv_base_t;

typedef enum _tlv_error 
{
    NO_ERROR = 0,
    NOT_INITIALIZED = -1,
    TAG_BAD_VAL = -2,
    TAG_IS_INSUFF = -3,
    LEN_IS_INSUFF = -4,
    VAL_IS_INSUFF = -5,
    VAL_IS_OVERFLOW = -6,
    BUF_IS_NULL = -7,
	ALLOC_MEMORY_ERROR = -8,
    LIST_OPERATION_ERR = -9,
    SER_BUFF_NOT_NULL = -10,
    CROSS_REF_DATA = -11,
    PARAMS_ERROR = -12,
} tlv_error_t;

typedef void (* tlv_parse_callback)(tlv_uint32_t tlv,
                                    tlv_error_t error_num, 
									tlv_uint8_t *original_data, 
									tlv_uint32_t original_data_len, 
									tlv_uint32_t parse_positon);

typedef struct _tlv_box 
{
    key_list_t *m_list;
    tlv_uint8_t *m_serialized_buffer;
    tlv_uint32_t m_serialized_bytes;
    tlv_uint16_t *m_tags_buffer;
    tlv_uint16_t m_tags_number;
    tlv_uint32_t m_parse_positon;
	tlv_parse_callback m_parse_cb;
} tlv_box_t;

extern tlv_uint16_t emv_tags[EMV_TAGS_LENTH];

tlv_box_t *tlv_box_create(void);
tlv_error_t tlv_parse(tlv_box_t *box, tlv_uint8_t *buffer, tlv_uint32_t buffersize, tlv_uint8_t byteorder);
tlv_error_t tlv_box_destroy(tlv_box_t *box);
tlv_uint8_t *tlv_box_get_buffer(tlv_box_t *box);
tlv_int32_t tlv_box_get_size(tlv_box_t *box);
tlv_error_t tlv_set_tags(tlv_box_t *box, tlv_uint16_t * tags_buff, tlv_uint16_t tags_num);
tlv_base_t *tlv_box_get_value(tlv_box_t *box);
void tlv_box_dest_value(tlv_box_t *box);
tlv_int16_t tlv_box_get_length(tlv_box_t *box, tlv_uint16_t tag);
tlv_error_t tlv_set_value(tlv_box_t *box, tlv_uint16_t tag, void *value, tlv_uint16_t length);
tlv_error_t tlv_box_serialize(tlv_box_t *box, tlv_uint8_t byteorder);

#ifdef __cplusplus
}
#endif

#endif
