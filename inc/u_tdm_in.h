#ifndef _U_TDM_IN_H_
#define _U_TDM_IN_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

#define TDM_IN_OK                            ((INT32)0)
#define TDM_IN_FAIL                          ((INT32)-1) /* abnormal return must < 0 */
#define TDM_IN_INV_ARG                       ((INT32)-2)
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*the struct of playback mic in application's message*/
typedef struct _TDM_IN_MSG_T
{
    UINT32          ui4_msg_id;
    UINT32          ui4_data1;
    UINT32          ui4_data2;
    UINT32          ui4_data3;
} TDM_IN_MSG_T;

typedef enum
{
    TDM_IN_CREATE_THREAD = ((UINT32)0),
    TDM_IN_PLAY_PAUSE,
    TDM_IN_STOP,
    TDM_IN_MAX_MSG
} TDM_IN_CONTROL_MSG_T;

extern INT32 u_tdm_in_send_msg(const TDM_IN_MSG_T* pt_event);
#endif