#ifndef _U_PLAYBACK_URI_H_
#define _U_PLAYBACK_URI_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_assistant_stub.h"

#define PB_URI_OK                            ((INT32)0)
#define PB_URI_FAIL                          ((INT32)-1) /* abnormal return must < 0 */
#define PB_URI_INV_ARG                       ((INT32)-2)
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*the struct of playback mic in application's message*/
typedef struct _PB_URI_MSG_T
{
    UINT32          ui4_msg_id;
    UINT32          ui4_data1;
    UINT32          ui4_data2;
    UINT32          ui4_data3;
} PB_URI_MSG_T;

typedef enum
{
    URI_STOP = 0,
    URI_START,
    URI_PAUSE,
    URI_RESUME,
} URI_CONTROL_MSG_T;

extern INT32 u_playback_uri_send_msg(const PB_URI_MSG_T* pt_event);
extern VOID  u_playback_uri_get_player_status(ASSISTANT_STUB_PLAYER_STATUS_CHANGE_T *pt_status);
extern BOOL  u_playback_uri_get_running_flag(VOID);
#endif
