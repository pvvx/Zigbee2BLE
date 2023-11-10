/********************************************************************************************************
 * @file     config_uECC.h
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

// Configuration of micro-ecc for use with BTstack
//
// We only need/use SECP256R1 for LE Secure Connections
#define uECC_CURVE uECC_secp256r1

// optimization: size vs. speed: uECC_asm_none - uECC_asm_small - uECC_asm_fast
#ifndef uECC_ASM
#define uECC_ASM uECC_asm_none
#endif

// don't use special square functions
#ifndef uECC_SQUARE_FUNC
#define uECC_SQUARE_FUNC 0
#endif
