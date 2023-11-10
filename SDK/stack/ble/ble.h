/********************************************************************************************************
 * @file     ble.h 
 *
 * @brief    for TLSR chips
 *
 * @author	 public@telink-semi.com;
 * @date     Sep. 18, 2015
 *
 * @par      Copyright (c) Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *           
 *			 The information contained herein is confidential and proprietary property of Telink 
 * 		     Semiconductor (Shanghai) Co., Ltd. and is available under the terms 
 *			 of Commercial License Agreement between Telink Semiconductor (Shanghai) 
 *			 Co., Ltd. and the licensee in separate contract or the terms described here-in. 
 *           This heading MUST NOT be removed from this file.
 *
 * 			 Licensees are granted free, non-transferable use of the information in this 
 *			 file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided. 
 *           
 *******************************************************************************************************/

#ifndef BLE_H__
#define BLE_H__

#if defined (MCU_CORE_8258)
#include "ble_8258/ble.h"
#define BLE_BLT_STATE_GET()    blt_state

#elif defined (MCU_CORE_B91)
#include "ble_b91/ble.h"
#define BLE_BLT_STATE_GET()    bltParam.blt_state

#endif


#endif /* BLE_H_H_ */
