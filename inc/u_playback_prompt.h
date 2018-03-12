#ifndef _U_PLAYBACK_PROMPT_H_
#define _U_PLAYBACK_PROMPT_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_assistant_stub.h"

#define PB_PROMPT_OK                            ((INT32)0)
#define PB_PROMPT_FAIL                          ((INT32)-1) /* abnormal return must < 0 */
#define PB_PROMPT_INV_ARG                       ((INT32)-2)
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*the struct of playback mic in application's message*/
typedef struct _PB_PROMPT_MSG_T
{
    UINT32          ui4_msg_id;
    UINT32          ui4_data1;
    UINT32          ui4_data2;
    UINT32          ui4_data3;
} PB_PROMPT_MSG_T;

typedef enum
{
    PROMPT_STOP = 0,
    PROMPT_START,
    PROMPT_PAUSE,
    PROMPT_RESUME,
} PROMPT_CONTROL_MSG_T;

extern INT32 u_playback_prompt_send_msg(const PB_PROMPT_MSG_T* pt_event);
extern VOID  u_playback_prompt_get_player_status(ASSISTANT_STUB_PLAYER_STATUS_CHANGE_T *pt_status);

#endif
