/********************************************************************************************************
 * @file     device_information.h
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

#pragma once

#include "tl_common.h"
//#include <stack/ble/ble_8258/att.h>
#include "../ble_common.h"
//#include <stack/ble/ble_8258/gap.h>

/** @addtogroup  TELINK_BLE_STACK TELINK BLE Stack
 *  @{
 */

/** @addtogroup  SERVICE_MODULE Service
 *  @{
 */


/** @addtogroup  DEVICE_INFO_Module Device Information
 *  @{
 */
 
/** @addtogroup  DEVICE_INFO_Constant Device Information Constants
 *  @{
 */

/**
 *  @brief  Definition for Characteristics UUID
 */

/** @addtogroup device_char_uuid Device Information Characteristc UUID
 * @{
 */

#define CHARACTERISTIC_UUID_MANU_NAME_STRING                    0x2A29
#define CHARACTERISTIC_UUID_MODEL_NUM_STRING                    0x2A24
#define CHARACTERISTIC_UUID_SERIAL_NUM_STRING                   0x2A25
#define CHARACTERISTIC_UUID_HW_REVISION_STRING                  0x2A27
#define CHARACTERISTIC_UUID_FW_REVISION_STRING                  0x2A26
#define CHARACTERISTIC_UUID_SW_REVISION_STRING                  0x2A28
#define CHARACTERISTIC_UUID_SYSTEM_ID                           0x2A23
#define CHARACTERISTIC_UUID_IEEE_11073_CERT_LIST                0x2A2A
#define CHARACTERISTIC_UUID_PNP_ID                              0x2A50

/** @} end of group device_char_uuid */


/** @addtogroup  IEEE_AUTHORITATIVE_BODY_VALUES IEEE Authoritative Body Values
 *  @{
 */

/**
 *  @brief  IEEE 11073 authoritative body values
 */
#define IEEE_11073_BODY_EMPTY                                   0
#define IEEE_11073_BODY_IEEE                                    1
#define IEEE_11073_BODY_CONTINUA                                2
#define IEEE_11073_BODY_EXP                                     254

/** @} end of group IEEE_AUTHORITATIVE_BODY_VALUES */




/** @addtogroup  SYSTEM_ID_LEN System Id Len
 *  @{
 */

/**
 *  @brief  Definition for System ID length
 */
#define SYSTEM_ID_LEN                                           8

/** @} end of group SYSTEM_ID_LEN */



/** @addtogroup  PNP_ID_LEN PnP ID Len
 *  @{
 */

/**
 *  @brief  Definition for PnP ID length
 */
#define DEVINFO_PNP_ID_LEN                                      7

/** @} end of group PNP_ID_LEN */

/** @} end of group DEVICE_INFO_Constant */



 /** @addtogroup  DEVICE_INFORMATION_Variables Device Information Variables
 *  @{
 */

/**
 *  @brief  External variable for device information Attribute tables
 */

extern  attribute_t devInfo_attrTbl[];

/**
 *  @brief  External variable for device information attribute size
 */
extern u16         devInfo_attrSize;

/** @} end of group DEVICE_INFORMATION_Variables */




 /** @addtogroup  PUBLIC_FUNCTION Device Information APIs
 *  @{
 */



/** @} end of group PUBLIC_FUNCTION */

/** @} end of group DEVICE_INFO_Module */

/** @} end of group SERVICE_MODULE */

/** @} end of group TELINK_BLE_STACK */
