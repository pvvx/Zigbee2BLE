/********************************************************************************************************
 * @file     smp_ms_storage.h
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

#ifndef SMP_MS_STORAGE_H_
#define SMP_MS_STORAGE_H_

#include <stack/ble/ble_8258/llms/llms.h>
#include <stack/ble/ble_8258/smp/smp.h>
#include <stack/ble/ble_8258/smp/smp_storage.h>

#define 	SMP_MS_BONDING_DEVICE_MAX_NUM				12 //support 12 bonding devices


#define 	SMP_MS_PARAM_NV_UNIT						112// 108

#define 	SMP_MS_PARAM_INIT_CLEAR_MAGIN_ADDR 			3360  //112 * 30
#define 	SMP_MS_PARAM_LOOP_CLEAR_MAGIN_ADDR 			4032  //112 * 36 (36 device most)



#define		SMP_MS_PARAM_NV_MAX_LEN						4096


//extern 		int	 SMP_MS_PARAM_NV_ADDR_START;

#define		SMP_MS_PARAM_NV_SEC_ADDR_START				(SMP_MS_PARAM_NV_ADDR_START + SMP_MS_PARAM_NV_MAX_LEN)
#define		SMP_MS_PARAM_NV_SEC_ADDR_END				(SMP_MS_PARAM_NV_SEC_ADDR_START + SMP_MS_PARAM_NV_MAX_LEN - 1)



#define		FLAG_SMP_MS_PARAM_SAVE_OLD					0x5A  // 0101 1010  old storage

														  // 10xx 1010  new storage,  xx: see "paring_sts_t" definition
#define		FLAG_SMP_MS_PARAM_SAVE_BASE					0x8A  // 1000 1010
#define		FLAG_SMP_MS_PARAM_SAVE_UNANTHEN				0x9A  // 1001 1010  new storage Unauthenticated_LTK
#define		FLAG_SMP_MS_PARAM_SAVE_AUTHEN				0xAA  // 1010 1010  new storage Authenticated_LTK_Legacy_Paring
#define		FLAG_SMP_MS_PARAM_SAVE_AUTHEN_SC			0xBA  // 1011 1010  new storage Authenticated_LTK_Secure_Connection

#define		FLAG_SMP_MS_PARAM_SAVE_PENDING				0xBF  // 1011 1111
#define		FLAG_SMP_MS_PARAM_SAVE_ERASE				0x00  //

#define 	FLAG_SMP_MS_PARAM_MASK						0x0F  // 0000 1111
#define     FLAG_SMP_MS_PARAM_VALID						0x0A  // 0000 1010
#define 	FLAG_SMP_MS_PARING_STATUS_MASK				0x30  // 0011 1000


#define		FLAG_SMP_MS_SECTOR_USE						0x3C
#define		FLAG_SMP_MS_SECTOR_CLEAR					0x00

#define     FLASH_SECTOR_OFFSET							4080  //0xFF0


extern	int smp_ms_bond_device_flash_cfg_idx;


typedef struct {

	u8 paring_status[BLMS_MAX_CONN_NUM];

	u8 rsvd;
	u8 addrIndex;
	u8 keyIndex;
	u8 cur_bondNum;

	#if (SMP_DATABASE_INFO_SOURCE == SMP_INFO_STORAGE_IN_FLASH)
		u32 bond_flash_idx[SMP_BONDING_DEVICE_MAX_NUM];  //mark paired slave mac address in flash
		u8	bond_flag[SMP_BONDING_DEVICE_MAX_NUM];
		u32  index_update_method;
	#else
		//may be sram address if use other mcu store smp info
	#endif

} smp_ms_bond_device_t;


extern smp_ms_bond_device_t  smpMStblBondDevice;


/*
 * smp parameter need save to flash.
 * */
typedef struct {  //106+6
	u8		smp_save_flag;
	u8		peer_addr_type;  //address used in link layer connection
	u8		peer_addr[6];

	u8      conn_handle;     //handle: 00 xx(high omit)
	u8		peer_id_adrType; //peer identity address information in key distribution, used to identify
	u8		peer_id_addr[6];

	u8 		own_ltk[16];
	u8		own_irk[16];
	u8		own_csrk[16];
	u8		peer_irk[16];
	u8		peer_csrk[16];

	u8      random[8]; //master role may be used

	u16     ediv;      //master role may be used
	u8      rsvd[6];
}smp_ms_param_save_t;





/******************************* User Interface  *****************************************/


u8			blms_smp_param_getCurrentBondingDeviceNumber(void);



void 		blms_smp_configParingSecurityInfoStorageAddr (int addr);


u32 		blms_smp_param_loadByIndex(u8 index, smp_ms_param_save_t* smp_param_load);

u32			blms_smp_param_loadByAddr(u8 addr_type, u8* addr, smp_ms_param_save_t* smp_param_load);


void		blms_smp_setIndexUpdateMethod(index_updateMethod_t method);


void		blms_smp_eraseAllParingInformation(void);


/************************* Stack Interface, user can not use!!! ***************************/
int     	blms_smp_param_saveBondingInfo (smp_ms_param_save_t*);
void 		blms_smp_param_initFromFlash(void);
void		blms_smp_param_Cleanflash (void);
u32 		blms_smp_loadParamVsRand (u16 ediv, u8* random);
int     	blms_smp_loadParamVsAddr (u16 addr_type, u8* addr);
u8			blms_smp_param_getIndexByFLashAddr(u32 flash_addr);

int			blms_smp_param_delete_by_Address(u8 addr_type, u8* addr );
int			blms_smp_param_deleteByIndex(u8 index);
u8			blms_smp_param_getBondFlag_by_flashAddress(u32 flash_addr);

u32			blms_smp_searchBondingDevice_in_Flash_by_Address(u8 addr_type, u8* addr );
u32 		blms_smp_param_updateToNearestByIndex(u8 index);



#endif /* SMP_STORAGE_H_ */
