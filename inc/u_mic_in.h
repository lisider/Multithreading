#ifndef _U_MIC_IN_H_
#define _U_MIC_IN_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

#define MIC_IN_OK                            ((INT32)0)
#define MIC_IN_FAIL                          ((INT32)-1) /* abnormal return must < 0 */
#define MIC_IN_INV_ARG                       ((INT32)-2)
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*the struct of playback mic in application's message*/
typedef struct _MIC_IN_MSG_T
{
    UINT32          ui4_msg_id;
    UINT32          ui4_data1;
    UINT32          ui4_data2;
    UINT32          ui4_data3;
} MIC_IN_MSG_T;

typedef enum
{
    MIC_IN_REQUEST_PLAY = ((UINT32)0),
    MIC_IN_CREATE_THREAD,
    MIC_IN_PLAY_PAUSE,
    MIC_IN_STOP,
    MIC_IN_MAX_MSG
} MIC_IN_CONTROL_MSG_T;

extern INT32 u_mic_in_send_msg(const MIC_IN_MSG_T* pt_event);
#endif