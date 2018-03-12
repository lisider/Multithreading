#ifndef _U_PLAYBACK_MIC_IN_H_
#define _U_PLAYBACK_MIC_IN_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

#define PB_MIC_IN_OK                            ((INT32)0)
#define PB_MIC_IN_FAIL                          ((INT32)-1) /* abnormal return must < 0 */
#define PB_MIC_IN_INV_ARG                       ((INT32)-2)
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*the struct of playback mic in application's message*/
typedef struct _PB_MIC_IN_MSG_T
{
    UINT32          ui4_msg_id;
    UINT32          ui4_data1;
    UINT32          ui4_data2;
    UINT32          ui4_data3;
} PB_MIC_IN_MSG_T;

typedef enum{
    ALSA_MIC_PB_START = ((UINT32)0),
    ALSA_MIC_IN_PB_SET_HW_PARAMS,
    ALSA_MIC_IN_PB_CREATE_PB_THREAD,
    ALSA_MIC_IN_PB_PLAY,
    ALSA_MIC_IN_PB_PAUSE,
    ALSA_MIC_IN_PB_STOP,         /*5*/
    ALSA_MIC_IN_PB_PCM_STATE_CHECK, /*6*/
    ALSA_MIC_IN_PB_DM_MSG,          /*7*/
    ALSA_MIC_IN_PB_MAX_MSG
} ALSA_MIC_IN_PB_CONTROL_MSG_T;

INT32 u_playback_mic_in_send_msg(const PB_MIC_IN_MSG_T* pt_event);
#endif