/********************************************************************************************************
 * @file     ll_encrypt.h
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

/*
 * ble_ll_encrypt.h
 *
 *  Created on: 2016-9-22
 *      Author: Telink
 */

#ifndef BLE_LL_ENCRYPT_H_
#define BLE_LL_ENCRYPT_H_





typedef struct {
	u32		pkt;
	u8		dir;
	u8		iv[8];
} ble_cyrpt_nonce_t;


typedef struct {
	u32					enc_pno;
	u32					dec_pno;
	u8					sk[16];			//session key
	ble_cyrpt_nonce_t	nonce;
	u8					st;
	u8					enable;			//1: slave enable; 2: master enable
	u8					mic_fail;
} ble_crypt_para_t;

#endif /* BLE_LL_ENCRYPT_H_ */
