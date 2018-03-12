#ifndef _U_TIMERD_H_
#define _U_TIMERD_H_

#include "u_common.h"
#include "u_handle.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

typedef enum
{
    X_TIMER_FLAG_ONCE   = 1,
    X_TIMER_FLAG_REPEAT
}   TIMER_FLAG_E;


typedef struct
{
	HANDLE_T h_timer;
	UINT32 ui4_delay;
	TIMER_FLAG_E e_flags;	
}TIMER_TYPE_T;

extern INT32 u_timer_start( HANDLE_T h_app, TIMER_TYPE_T *p_timer, void * ptimer_msg,size_t msg_size);
extern INT32 u_timer_create (HANDLE_T *ph_timer);
extern INT32 u_timer_stop (HANDLE_T  h_timer);
extern INT32 u_timer_delete (HANDLE_T	h_timer);
#endif /* _U_TIMERD_H_ */
