#ifndef _NVRAM_UTILS_H__
#define _NVRAM_UTILS_H__

#include <stdbool.h>

struct WIFI_CFG_STRUCT {
    unsigned char mac[6];
};

struct BT_CFG_STRUCT {
    unsigned char mac[6];
};

/* Length serial number, MUST NOT TO MODIFY */
#define SN_LEN 23
/* Length PCB serial number, MUST NOT TO MODIFY */
#define PCBSN_LEN 18


#ifdef __cplusplus
extern "C" {
#endif

/**
* Read WiFi configuration from MTK data NvRAM.
* @param param the WiFi configuration to be read from MTK data NvRAM.
* @return whether the read requested fully succeeded.
*/
bool r_WiFi_CFG(struct WIFI_CFG_STRUCT* param);

/**
* Write WiFi configuration to MTK data NvRAM.
* @param param the WiFi configuration to be written to MTK data NvRAM.
* @return whether the write requested fully succeeded.
*/
bool w_WiFi_CFG(struct WIFI_CFG_STRUCT* param);

/**
* Read Bluetooth configuration from MTK data NvRAM.
* @param param the Bluetooth configuration to be read from MTK data NvRAM.
* @return whether the read requested fully succeeded.
*/
bool r_BT_CFG(struct BT_CFG_STRUCT* param);

/**
* Write Bluetooth configuration to MTK data NvRAM.
* @param param the WiFi configuration to be written to MTK data NvRAM.
* @return whether the write requested fully succeeded.
*/
bool w_BT_CFG(struct BT_CFG_STRUCT* param);

/**
* Backup  MTK data NvRAM (such as WiFi/Bluetooth/SN/PCBSN configuration) to MTK NvRAM raw partition.
* @return whether the backup requested fully succeeded.
*/
bool b_CFG();

bool r_XOCAP();

/**
* Read serial number from MTK data NvRAM.
* @param sn the buffer to store data from MTK data NvRAM,
* expected length not more than SN_LEN ,excluding the terminating null byte ('\0').
* @return whether the read requested fully succeeded.
*/
bool r_SN(char* sn);

/**
* Write serial number to MTK data NvRAM.
* @param sn the buffer to store data want write to  MTK data NvRAM,
* expected length not more than SN_LEN ,excluding the terminating null byte ('\0').
* @return whether the write requested fully succeeded.
*/
bool w_SN(char* sn);

/**
* Read PCB serial number from MTK data NvRAM.
* @param pcbsn the buffer to store data from MTK data NvRAM,
* expected length not more than PCBSN_LEN ,excluding the terminating null byte ('\0').
* @return whether the read requested fully succeeded.
*/
bool r_PCBSN(char* pcbsn);

/**
* Write PCB serial number to MTK data NvRAM.
* @param pcbsn the buffer to store data want write to  MTK data NvRAM,
* expected length not more than PCBSN_LEN ,excluding the terminating null byte ('\0').
* @return whether the write requested fully succeeded.
*/
bool w_PCBSN(char*pcbsn);

#ifdef __cplusplus
}
#endif
#endif /* _NVRAM_UTILS_H__ */
