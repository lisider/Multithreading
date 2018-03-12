#ifndef _U_PLAYBACK_TTS_H_
#define _U_PLAYBACK_TTS_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

#define PB_TTS_OK                            ((INT32)0)
#define PB_TTS_FAIL                          ((INT32)-1) /* abnormal return must < 0 */
#define PB_TTS_INV_ARG                       ((INT32)-2)

#define PLAYBACK_TTS_SAMPLERATE     44100
#define PLAYBACK_TTS_CHANNLE        2
#define PLAYBACK_TTS_BITWIDTH       16
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*the struct of playback mic in application's message*/
typedef struct _PB_TTS_MSG_T
{
    UINT32          ui4_msg_id;
    UINT32          ui4_data1;
    UINT32          ui4_data2;
    UINT32          ui4_data3;
} PB_TTS_MSG_T;

typedef enum
{
    TTS_STOP = 0,
    TTS_START,
    TTS_PAUSE,
    TTS_RESUME,
} TTS_CONTROL_MSG_T;

extern INT32 u_playback_tts_send_msg(const PB_TTS_MSG_T* pt_event);
#endif