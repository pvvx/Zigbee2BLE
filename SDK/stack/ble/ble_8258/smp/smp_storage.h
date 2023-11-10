/********************************************************************************************************
 * @file     smp_storage.h
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
 * smp_storage.h
 *
 *  Created on: 2018-12-4
 *      Author: Administrator
 */

#ifndef SMP_STORAGE_H_
#define SMP_STORAGE_H_



#if (SIMPLE_MULTI_MAC_EN)
	#include "smp.h"
	extern u8 device_mac_index;
#endif


#define 	SMP_PARAM_NV_UNIT						64

#define 	SMP_PARAM_INIT_CLEAR_MAGIN_ADDR 		3072  //64 * 48
#define 	SMP_PARAM_LOOP_CLEAR_MAGIN_ADDR 		3520  //64 * 55 (56 device most)



#define		SMP_PARAM_NV_MAX_LEN					4096


extern 		int	 SMP_PARAM_NV_ADDR_START;

#define		SMP_PARAM_NV_SEC_ADDR_START				(SMP_PARAM_NV_ADDR_START + SMP_PARAM_NV_MAX_LEN)
#define		SMP_PARAM_NV_SEC_ADDR_END				(SMP_PARAM_NV_SEC_ADDR_START + SMP_PARAM_NV_MAX_LEN - 1)




#define		NEW_FLASH_STORAGE_KEY_ENABLE			0   //be compatible with old flash storage methods


#define		FLAG_SMP_PARAM_SAVE_OLD					0x5A  // 0101 1010  old storage

#if (SIMPLE_MULTI_MAC_EN)
														  // 10xx 1YYY  new storage,  xx: see "paring_sts_t" definition YYY:device_mac_index default
#define		FLAG_SMP_PARAM_SAVE_BASE				(0x88+(device_mac_index&0x07))//0x8A  // 1000 1010
#else
														  // 10xx 1010  new storage,  xx: see "paring_sts_t" definition
#define		FLAG_SMP_PARAM_SAVE_BASE				0x8A  // 1000 1010
#endif
#define		FLAG_SMP_PARAM_SAVE_UNANTHEN			0x9A  // 1001 1010  new storage Unauthenticated_LTK
#define		FLAG_SMP_PARAM_SAVE_AUTHEN				0xAA  // 1010 1010  new storage Authenticated_LTK_Legacy_Paring
#define		FLAG_SMP_PARAM_SAVE_AUTHEN_SC			0xBA  // 1011 1010  new storage Authenticated_LTK_Secure_Connection

#define		FLAG_SMP_PARAM_SAVE_PENDING				0xBF  // 1011 1111
#define		FLAG_SMP_PARAM_SAVE_ERASE				0x00  //

#if (SIMPLE_MULTI_MAC_EN)
#define 	FLAG_SMP_PARAM_MASK						0xC8
#define     FLAG_SMP_PARAM_VALID					0x88
#else
#define 	FLAG_SMP_PARAM_MASK						0x0F  // 0000 1111
#define     FLAG_SMP_PARAM_VALID					0x0A  // 0000 1010
#endif
#define 	FLAG_SMP_PARING_STATUS_MASK				0x30  // 0011 1000


#define		FLAG_SMP_SECTOR_USE						0x3C
#define		FLAG_SMP_SECTOR_CLEAR					0x00

#define     FLASH_SECTOR_OFFSET						4080  //0xFF0


extern int		bond_device_flash_cfg_idx;



typedef enum {
	Index_Update_by_Pairing_Order = 0,     //default value
	Index_Update_by_Connect_Order = 1,
} index_updateMethod_t;



/*
 * smp parameter need save to flash.
 * */
typedef struct {  //82
	u8		flag;
	u8		peer_addr_type;  //address used in link layer connection
	u8		peer_addr[6];

	u8 		peer_key_size;
	u8		peer_id_adrType; //peer identity address information in key distribution, used to identify
	u8		peer_id_addr[6];


	u8 		own_ltk[16];      //own_ltk[16]
	u8		peer_irk[16];
	u8		peer_csrk[16];

}smp_param_save_t;





/******************************* User Interface  *****************************************/


u8			blc_smp_param_getCurrentBondingDeviceNumber(void);



void 		bls_smp_configParingSecurityInfoStorageAddr (int addr);


u32 		bls_smp_param_loadByIndex(u8 index, smp_param_save_t* smp_param_load);

u32			bls_smp_param_loadByAddr(u8 addr_type, u8* addr, smp_param_save_t* smp_param_load);


void		bls_smp_setIndexUpdateMethod(index_updateMethod_t method);


void		bls_smp_eraseAllParingInformation(void);


/************************* Stack Interface, user can not use!!! ***************************/
int     bls_smp_param_saveBondingInfo (smp_param_save_t*);
void 	bls_smp_param_initFromFlash(void);
void	bls_smp_param_Cleanflash (void);
u32 	bls_smp_loadParamVsRand (u16 ediv, u8* random);
int     bls_smp_loadParamVsAddr (u16 addr_type, u8* addr);
u8		bls_smp_param_getIndexByFLashAddr(u32 flash_addr);


int		bls_smp_param_deleteByIndex(u8 index);
u8		bls_smp_param_getBondFlag_by_flashAddress(u32 flash_addr);

u32		bls_smp_searchBondingDevice_in_Flash_by_Address(u8 addr_type, u8* addr );
u32 	blc_smp_param_updateToNearestByIndex(u8 index);



#endif /* SMP_STORAGE_H_ */
