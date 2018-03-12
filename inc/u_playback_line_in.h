#ifndef _U_PLAYBACK_LINE_IN_H_
#define _U_PLAYBACK_LINE_IN_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

#define PB_LINE_IN_OK                            ((INT32)0)
#define PB_LINE_IN_FAIL                          ((INT32)-1) /* abnormal return must < 0 */
#define PB_LINE_IN_INV_ARG                       ((INT32)-2)
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*the struct of playback mic in application's message*/
typedef struct _PB_LINE_IN_MSG_T
{
    UINT32          ui4_msg_id;
    UINT32          ui4_data1;
    UINT32          ui4_data2;
    UINT32          ui4_data3;
} PB_LINE_IN_MSG_T;

typedef enum
{
    LINE_IN_REQUEST_PLAY = ((UINT32)0),
    LINE_IN_CREATE_THREAD,
    LINE_IN_PLAY_PAUSE,
    LINE_IN_STOP,
    LINE_IN_MAX_MSG
} LINE_IN_CONTROL_MSG_T;

extern INT32 u_playback_line_in_send_msg(const PB_LINE_IN_MSG_T* pt_event);
#endif