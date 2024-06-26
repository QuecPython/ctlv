/*
 * Copyright (c) Quectel Wireless Solution, Co., Ltd.All Rights Reserved.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */
#include <string.h>
#include "tlv_types.h"
#include "tlv_iostream.h"
#include "timer.h"
#include "logging.h"


#define TEST_TAG_0 0x00
#define TEST_TAG_1 0x01
#define TEST_TAG_2 0x02
#define TEST_TAG_3 0x03
#define TEST_TAG_4 0x04
#define TEST_TAG_5 0x05
#define TEST_TAG_6 0x06
#define TEST_TAG_7 0x07
#define TEST_TAG_8 0x08
#define TEST_TAG_9 0x09


tlv_uint16_t test_tag[] = {
    TEST_TAG_0,
    TEST_TAG_1,
    TEST_TAG_2,
    TEST_TAG_3,
    TEST_TAG_4,
    TEST_TAG_5,
    TEST_TAG_6,
    TEST_TAG_7,
    TEST_TAG_8,
    TEST_TAG_9,
};


char hex_mapping[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};


void bytes_to_hexstring(char *dest, tlv_uint8_t *src, tlv_uint32_t size) {
    int hv, lv;
    char hex_string[4] = {0x00, 0x00, 0x20, 0x00};
    for (int i = 0; i < size; i++) {
        memset(hex_string, 0, 2);
        hex_string[0] = hex_mapping[(src[i] >> 4) & 0x0F];
        hex_string[1] = hex_mapping[src[i] & 0x0F];
        strcat(dest, hex_string);
    }
}


/*
* TLV test case
*/

static void tlv_parse_cb(
    tlv_uint32_t tlv, 
    tlv_error_t errno, 
    tlv_uint8_t *original_data, 
    tlv_uint32_t original_data_len, 
    tlv_uint32_t parse_positon
) {
    tlv_base_t *tlv_base;
    
    TLV_LOG("errno: %d", errno);
    char hex_string[(original_data_len * 3) + 1];
    memset(hex_string, 0, (original_data_len * 3) + 1);

    if(errno) {
        TLV_LOG("original_data_len: %d", original_data_len);
        TLV_LOG("parse_positon: %d", parse_positon);
        TLV_LOG("original_data: ");
        bytes_to_hexstring(hex_string, original_data, original_data_len);
        TLV_LOG("%s", hex_string);
    } else {
        while(tlv_base = tlv_get_value(tlv)) {
            TLV_LOG("tlv->tag: %04X", tlv_base->tag);
            TLV_LOG("tlv->len: %04X", tlv_base->length);
            for(tlv_uint32_t i = 0; i < tlv_base->length; i++) {
                TLV_LOG("tlv->val: %02X", tlv_base->value[i]);
            }
            tlv_dest_value(tlv);
            TLV_LOG("------------------------");
        }
    }
}


void main() {
    uart_cfg_t uart_cfg = {
        .baud_rate = 115200,
        .word_length = UART_WORDLENGTH_8,
        .stop_bits = 1,
        .parity = UART_PARITY_NO,
        .mode = UART_MODE_RX_TX,
        .hardware_flowcontrol = UART_HWFC_None,
        .rx_buffer_size = 1024
    };

    tlv_uint32_t tlv = tlv_init(UART_PORT2, &uart_cfg, tlv_parse_cb, test_tag, sizeof(test_tag)/sizeof(tlv_uint16_t));
    
    while (1)
    {   
        send_data_type send_data[6] = {0};
        
        tlv_chr_t test1 = 'x'; 
        send_data[0].pdata = (tlv_uint8_t *)&test1;
        send_data[0].data_len = sizeof(test1);
        send_data[0].tage = TEST_TAG_1;
        
        tlv_int16_t test2 = 2; 
        send_data[1].pdata = (tlv_uint8_t *)&test2;
        send_data[1].data_len = sizeof(test2);
        send_data[1].tage = TEST_TAG_2;
        
        tlv_int32_t test3 = 3; 
        send_data[2].pdata = (tlv_uint8_t *)&test3;
        send_data[2].data_len = sizeof(test3);
        send_data[2].tage = TEST_TAG_3;
        
        tlv_float_t test4 = 5.67;  
        send_data[3].pdata = (tlv_uint8_t *)&test4;
        send_data[3].data_len = sizeof(test4);
        send_data[3].tage = TEST_TAG_4;
        
        tlv_str_t test5 = "hello world !";
        send_data[4].pdata = (tlv_uint8_t *)test5;
        send_data[4].data_len = strlen(test5);
        send_data[4].tage = TEST_TAG_5;
        
        tlv_uint8_t test6[6] = {1, 2, 3, 4, 5, 6};
        send_data[5].pdata = test6;
        send_data[5].data_len = sizeof(test6);
        send_data[5].tage = TEST_TAG_6;

        // send tlv data
        tlv_send(tlv, send_data, sizeof(send_data)/sizeof(send_data_type));

        timer_msleep(1000);
    }
}
