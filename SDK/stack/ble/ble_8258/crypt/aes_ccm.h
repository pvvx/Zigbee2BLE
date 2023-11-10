/********************************************************************************************************
 * @file     aes_ccm.h
 *
 * @brief    This is the header file for 8258 BLE SDK
 *
 * @author	 BLE GROUP
 * @date         12,2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *******************************************************************************************************/

#pragma  once

#include "../ll/ll.h"

#define AES_BLOCK_SIZE     16


//#define		SUCCESS			0
enum {
    AES_SUCC = SUCCESS,
    AES_NO_BUF,               
    AES_FAIL,
};

#if 0
struct CCM_FLAGS_TAG {
    union {
        struct {
            u8 L : 3;
            u8 M : 3;
            u8 aData :1;
            u8 reserved :1;            
        } bf;
        u8 val;
    };
};

typedef struct CCM_FLAGS_TAG ccm_flags_t;
#endif

typedef struct {
    union {
        u8 A[AES_BLOCK_SIZE];
        u8 B[AES_BLOCK_SIZE];
    } bf;
    
    u8 tmpResult[AES_BLOCK_SIZE];
    u8 newAstr[AES_BLOCK_SIZE];
} aes_enc_t;

u8 ble_aes_ccmAuthTran(u8 micLen, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u16 aStrLen, u8 *result);
u8 ble_aes_ccmDecAuthTran(u8 micLen, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u8 aStrLen, u8 *mic);
u8 aes_initKey(u8 *key);
u8 ble_aes_encrypt(u8 *key, u8 *data, u8 *result);

u8 aes_ccm_encryption(u8 *key, u8 *iv, u8 *aStr, u8 *mic, u8 mStrLen, u8 *mStr, u8 *result);
u8 aes_ccm_decryption(u8 *key, u8 *iv, u8 *aStr, u8 *mic, u8 mStrLen, u8 *mStr, u8 *result);
void aes_ecb_encryption(u8 *key, u8 *plaintext, u8 *encrypted_data);
void aes_ecb_decryption(u8 *key, u8 *encrypted_data, u8 *decrypted_data);
void aes_ll_encryption(u8 *key, u8 *plaintext, u8 *result);
void aes_ll_ccm_encryption_init (u8 *ltk, u8 *skdm, u8 *skds, u8 *ivm, u8 *ivs, ble_crypt_para_t *pd);
void aes_ll_ccm_encryption(u8 *pkt, int master, ble_crypt_para_t *pd);
int aes_ll_ccm_decryption(u8 *pkt, int master, ble_crypt_para_t *pd);		//OK return 0
u8 aes_att_encryption_packet(u8 *key, u8 *iv, u8 *mic, u8 mic_len, u8 *ps, u8 len);
u8 aes_att_decryption_packet(u8 *key, u8 *iv, u8 *mic, u8 mic_len, u8 *ps, u8 len);

void aes_ll_c1(u8 * key, u8 * r, u8 *p1, u8 *p2, u8 * result);
void aes_ll_s1(u8 * key, u8 * r1, u8 * r2, u8 * result);

volatile void  smemset(register char * dest,register int val,register unsigned int len);
volatile void * smemcpy(register char * out, register char * in, register unsigned int len);
