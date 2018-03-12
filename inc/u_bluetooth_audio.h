#ifndef _BLUETOOTH_AUDIO_H_
#define _BLUETOOTH_AUDIO_H_

#include "u_common.h"
#include "u_amb.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/* return value */
#define APPUTILR_OK                              ((INT32)0)
#define APPUTILR_FAIL                            ((INT32)-1) /* abnormal return must < 0 */
#define APPUTILR_INV_ARG                         ((INT32)-2)
#define APPUTILR_LACK_BUFFER                     ((INT32)-3)
#define APPUTILR_NOT_EXIST                       ((INT32)-4)

#define BT_VOLUME_STEP     10
#define CONFIG_APP_SUPPORT_BT_STICKY_PAIRING     1
#define CONFIG_APP_SUPPORT_BLE_GATT_CLIENT		 0
#define CONFIG_APP_SUPPORT_CUSTOM_BT_NAME        0
#define CONFIG_APP_SUPPORT_BLE_GATT_SERVER       0
#define CONFIG_APP_SUPPORT_BT_KEEP_CONNECT                0
#define CONFIG_APP_SUPPORT_BLUETOOTH_EXHAUST_PAIR_LIST    0
#define CONFIG_APP_SUPPORT_BT_SRC_MODE           1
#define CONFIG_SUPPORT_BT_SRC_AVRCP                       1
#ifdef EXTER_WIFI_CHIP
#define CONFIG_SUPPORT_BT_HFP                             1
#define CONFIG_SUPPORT_AUDIO_CONNECT                      1
#define CONFIG_SUPPORT_PHONE_BOOK                         1
#else
#define CONFIG_SUPPORT_BT_HFP                             1
#define CONFIG_SUPPORT_AUDIO_CONNECT                      1
#define CONFIG_SUPPORT_PHONE_BOOK                         1
#endif
#define CONFIG_APP_SUPPORT_ALWAYS_CON_DIS        1

#define BT_AUDIO_NAME_MAX_LENGTH    (256)
#define BT_AUDIO_ANCHOR_MAX_LENGTH  (256)
#define BT_AUDIO_SOURCE_MAX_LENGTH  (32)
#define BT_AUDIO_ALBUM_MAX_LENGTH   (256)
#define SOURCE_MAX_LENGTH        (16)



//#if (CONFIG_APP_SUPPORT_BLUETOOTH_UI || CONFIG_APP_SUPPORT_BLUETOOTH_AUDIO)
enum BLUETOOTH_ENABLE_T
{
    BLUETOOTH_ENABLE = 0,
    BLUETOOTH_DISABLE,
};
//#endif
//net connection
enum NETWORK_CONNETION_T
{
    NETCONNECTION_ON,
    NETCONNECTION_OFF,
};

//#if (CONFIG_APP_SUPPORT_BLUETOOTH_UI || CONFIG_APP_SUPPORT_BLUETOOTH_AUDIO)
typedef enum _CFG_RECID_BLUETOOTH_T
{
    CFG_RECID_BLUETOOTH_ENABLE,
}CFG_RECID_BLUETOOTH_T;
//#endif

typedef struct
{
    char audioName[BT_AUDIO_NAME_MAX_LENGTH+1];
    char audioAnchor[BT_AUDIO_ANCHOR_MAX_LENGTH+1];
    char audioAlbum[BT_AUDIO_ALBUM_MAX_LENGTH+1];
    char audioSource[BT_AUDIO_SOURCE_MAX_LENGTH+1];
    char source[SOURCE_MAX_LENGTH+1];
    UINT32 song_length;
    int  progress;
}BT_SRC_PLAYER_STATUS_T;



extern VOID a_bluetooth_audio_init(AMB_REGISTER_INFO_T* pt_reg);
extern INT32 a_bt_plug_out(VOID);
extern INT32 a_bt_plug_in(VOID);
extern INT32 a_bt_aud_bt_key_handle(UINT32 ui4_keysta, UINT32 ui4_keyval);
extern INT32 a_bt_aud_volume_sync(UINT8 ui1_value);
extern INT32 a_bt_aud_clear_bluetooth_data(VOID);
extern INT32 a_bt_aud_get_local_mac_addr(CHAR* pc_mac);
extern INT32 u_bluetooth_set_absolute_volume(UINT8 ui1_value);
extern BOOL u_bt_hfp_is_audio_connect(VOID);
#if CONFIG_SUPPORT_BT_SRC_AVRCP
extern INT32 u_bt_aud_src_request_mediaInfo_from_url(BT_SRC_PLAYER_STATUS_T *medialnfo);
#endif


#if CONFIG_APP_SUPPORT_CUSTOM_BT_NAME
extern INT32 a_bt_aud_get_custom_bt_name(CHAR *pc_name);
#endif/* CONFIG_APP_SUPPORT_CUSTOM_BT_NAME */

#if CONFIG_APP_SUPPORT_BT_STICKY_PAIRING
extern INT32 a_bt_aud_get_custom_sticky_pairing_time(UINT32 *pui4_time);
#endif/* CONFIG_APP_SUPPORT_BT_STICKY_PAIRING */

#endif  /* _BLUETOOTH_AUDIO_H_ */
