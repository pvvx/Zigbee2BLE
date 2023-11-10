/*
 * bthome_beacon.c
 *
 *  Created on: 17.10.23
 *      Author: pvvx
 */

#include "tl_common.h"
#include <stack/ble/ble.h>
#include "bthome_beacon.h"

extern void bls_set_advertise_prepare(void *p); // add ll_adv.h

adv_buf_t adv_buf;
measured_data_t measured_data;

const u8	def_devName[] = {"Z2B_"};

__attribute__((optimize("-Os")))
void bthome_data_beacon(void) {
	padv_bthome_ns1_t p = (padv_bthome_ns1_t)&adv_buf.data;
	p->head.type = GAP_ADTYPE_SERVICE_DATA_UUID_16BIT; // 16-bit UUID
	p->head.UUID = ADV_BTHOME_UUID16;
	p->info = BtHomeID_Info;
	p->p_id = BtHomeID_PacketId;
	p->pid = (u8)adv_buf.send_count;
	p->data.b_id = BtHomeID_battery;
	p->data.battery_level = measured_data.battery_level;
	p->data.t_id = BtHomeID_temperature;
	p->data.temperature = measured_data.temp; // x0.01 C
	p->data.h_id = BtHomeID_humidity;
	p->data.humidity = measured_data.humi; // x0.01 %
	p->head.size = sizeof(adv_bthome_ns1_t) - sizeof(p->head.size);
}

static const u8* hex_ascii = { "0123456789ABCDEF" };
u8 * str_bin2hex(u8 *d, u8 *s, int len) {
	while(len--) {
		*d++ = hex_ascii[(*s >> 4) & 0xf];
		*d++ = hex_ascii[(*s++ >> 0) & 0xf];
	}
	return d;
}

void load_adv_data(void) {
	adv_buf.data_size = adv_buf.data[0] + 1 + sizeof(adv_buf.flag);
	bls_ll_setAdvData(adv_buf.flag, adv_buf.data_size);
}

void set_adv_data(void) {
	bthome_data_beacon();
	load_adv_data();
}

/*
 * use bls_set_advertise_prepare(app_advertise_prepare_handler)
 * TODO: not work if EXTENDED_ADVERTISING
 */
int app_advertise_prepare_handler(rf_packet_adv_t * p)	{
	(void) p;
#if USE_ADV_EVENT
	if (!blta.adv_duraton_en)
#endif
	{
		if (adv_buf.old_measured_count != measured_data.count) { // new measured_data ?
			adv_buf.old_measured_count = measured_data.count; // save measured count
			adv_buf.call_count = 1; // count 1..cfg.measure_interval
			adv_buf.send_count++; // count & id advertise, = beacon_nonce.cnt32
			adv_buf.update_count = 0;
			set_adv_data();
		} else {
#if USE_ADV_EVENT
			if (!adv_buf.data_size) // flag
				adv_buf.send_count++; // count & id advertise, = beacon_nonce.cnt32
#endif
			if (++adv_buf.call_count > adv_buf.update_count) // refresh adv_buf.data ?
				set_adv_data();
		}
#if USE_ADV_EVENT
//		if(ext_key.rest_adv_int_tad) {
//			ext_key.rest_adv_int_tad--;
//		}
#endif
	}
#if USE_ADV_EVENT
	else {
		// restore next adv. interval
		blta.adv_interval = ADV_EVENT_INTERVAL*625*CLOCK_16M_SYS_TIMER_CLK_1US; // system tick
	}
#endif
	return 1;		// = 1 ready to send ADV packet, = 0 not send ADV
}

extern u8  mac_public[6];
extern void app_switch_to_indirect_adv(u8 e, u8 *p, int n);
void adv_init(void) {
	// 0x02, 0x01, 0x05
	adv_buf.flag[0] = 0x02; // size
	adv_buf.flag[1] = GAP_ADTYPE_FLAGS; // type
	/*	Flags:
	 	bit0: LE Limited Discoverable Mode
		bit1: LE General Discoverable Mode
		bit2: BR/EDR Not Supported
		bit3: Simultaneous LE and BR/EDR to Same Device Capable (Controller)
		bit4: Simultaneous LE and BR/EDR to Same Device Capable (Host)
		bit5..7: Reserved
	 */
	// Flags: BLE limited discoverable mode and BR/EDR not supported
	adv_buf.flag[2] = 0x04 | GAP_ADTYPE_LE_LIMITED_DISCOVERABLE_MODE_BIT;

	adv_buf.scanRsp[0] = sizeof(def_devName) + 6;
	adv_buf.scanRsp[1] = GAP_ADTYPE_LOCAL_NAME_COMPLETE;
	memcpy(adv_buf.devName, def_devName, sizeof(def_devName)-1);
	u8 *p = str_bin2hex(&adv_buf.devName[sizeof(def_devName)-1], &mac_public[2], 1);
	p = str_bin2hex(p, &mac_public[1], 1);
	p = str_bin2hex(p, &mac_public[0], 1);
	// TODO: not work if EXTENDED_ADVERTISING
	bls_set_advertise_prepare(app_advertise_prepare_handler);
	bls_ll_setScanRspData( adv_buf.scanRsp, adv_buf.scanRsp[0] + 1);
	set_adv_data();
#if APP_SECURITY_ENABLE//(BLE_REMOTE_SECURITY_ENABLE)
	u8 bond_number = blc_smp_param_getCurrentBondingDeviceNumber();  //get bonded device number
	smp_param_save_t  bondInfo;
	if(bond_number)   //at least 1 bonding device exist
		bls_smp_param_loadByIndex( bond_number - 1, &bondInfo);  //get the latest bonding device (index: bond_number-1 )
	if(bond_number)   //set direct adv
	{
		//set direct adv
		u8 status = bls_ll_setAdvParam( DEF_ADV_INTERVAL_MIN, DEF_ADV_INTERVAL_MAX,
										ADV_TYPE_CONNECTABLE_DIRECTED_LOW_DUTY, app_own_address_type,
										bondInfo.peer_addr_type,  bondInfo.peer_addr,
										DEF_APP_ADV_CHANNEL,
										ADV_FP_NONE);
		extern void sampleGwSysException(void);
		if(status != BLE_SUCCESS) { sampleGwSysException(); }  //debug: adv setting err

		//it is recommended that direct adv only last for several seconds, then switch to indirect adv
		bls_ll_setAdvDuration(DEF_DIRECT_ADV_TMIE, 1);
		bls_app_registerEventCallback (BLT_EV_FLAG_ADV_DURATION_TIMEOUT, &app_switch_to_indirect_adv);

		bls_ll_setAdvEnable(1);  //adv enable

	}
	else   //set indirect adv
#endif
	{
		app_switch_to_indirect_adv(0,0,0);
	}
}
