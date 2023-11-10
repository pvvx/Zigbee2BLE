/********************************************************************************************************
 * @file     ll_scan.h
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
 * ll_scan.h
 *
 *  Created on: 2017-3-7
 *      Author: Administrator
 */

#ifndef LL_SCAN_H_
#define LL_SCAN_H_


#include "ll_whitelist.h"



#define			BLS_FLAG_SCAN_ENABLE					BIT(0)


#define			BLS_FLAG_SCAN_IN_ADV_MODE				BIT(5)
#define			BLS_FLAG_SCAN_IN_SLAVE_MODE				BIT(6)



//scan_enable_t
typedef enum {
	BLC_SCAN_DISABLE = 0x00,
	BLC_SCAN_ENABLE  = 0x01,
} scan_en_t;


//duplicate_filter_enable_t
typedef enum {
	DUP_FILTER_DISABLE = 0x00,
	DUP_FILTER_ENABLE  = 0x01,
} dupFilter_en_t;


typedef enum {
	SCAN_TYPE_PASSIVE = 0x00,
	SCAN_TYPE_ACTIVE  = 0x01,
} scan_type_t;



// Advertise report event type
typedef enum {
	ADV_REPORT_EVENT_TYPE_ADV_IND = 0x00,
	ADV_REPORT_EVENT_TYPE_DIRECT_IND = 0x01,
	ADV_REPORT_EVENT_TYPE_SCAN_IND = 0x02,
	ADV_REPORT_EVENT_TYPE_NONCONN_IND = 0x03,
	ADV_REPORT_EVENT_TYPE_SCAN_RSP = 0x04,
} advReportEventType_t;



typedef struct {
	u8		scan_en;
	u8		scan_type;
	u8		scan_filterPolicy;
	u8		filter_dup;

	u8		scanDevice_num;
	u8		scanRspDevice_num;
	u8		scan_extension_mask;
	u8 		rsvd;
//	s8		T_SCAN_REQ_INTVL;



	//u32		scan_interval;
}st_ll_scan_t;

_attribute_aligned_(4) st_ll_scan_t  blts;

u32		blts_scan_interval;

extern 			rf_packet_scan_req_t	pkt_scan_req;


typedef int (*ll_procScanPkt_callback_t)(u8 *, u8 *, u32);
typedef int (*ll_procScanDat_callback_t)(u8 *);

extern ll_procScanDat_callback_t  blc_ll_procScanDatCb;
extern ll_procScanPkt_callback_t  blc_ll_procScanPktCb;





/******************************* User Interface  ************************************/
void 		blc_ll_initScanning_module(u8 *public_adr);


ble_sts_t 	blc_ll_setScanParameter (scan_type_t scan_type, u16 scan_interval, u16 scan_window, own_addr_type_t  ownAddrType, scan_fp_type_t scanFilter_policy);
ble_sts_t 	blc_ll_setScanEnable (scan_en_t scan_enable, dupFilter_en_t filter_duplicate);



ble_sts_t    blc_ll_addScanningInAdvState(void);
ble_sts_t    blc_ll_removeScanningFromAdvState(void);
ble_sts_t    blc_ll_addScanningInConnSlaveRole(void);
ble_sts_t    blc_ll_removeScanningFromConnSLaveRole(void);

u8 blc_scan_busy(u8 index);


/************************* Stack Interface, user can not use!!! ***************************/
int			blc_ll_filterAdvDevice (u8 type, u8 * mac);
int 		blc_ll_addScanRspDevice(u8 type, u8 *mac);
bool 		blc_ll_isScanRspReceived(u8 type, u8 *mac);
void 		blc_ll_clearScanRspDevice(void);


int  		blc_ll_procScanPkt(u8 *raw_pkt, u8 *new_pkt, u32 tick_now);
int  		blc_ll_procScanData(u8 *raw_pkt);

void 		blc_ll_switchScanChannel (int, int);


#endif /* LL_SCAN_H_ */
