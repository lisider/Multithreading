/********************************************************************************************
 *     LEGAL DISCLAIMER 
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES 
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED 
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS 
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED, 
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR 
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY 
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, 
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK 
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION 
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *     
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH 
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, 
 *     TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE 
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
 *     
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS 
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.  
 ************************************************************************************************/
#ifndef _TIMERD_H_
#define _TIMERD_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_dbg.h"

#undef   DBG_LEVEL_MODULE
#define  DBG_LEVEL_MODULE       timed_get_dbg_level()

#define TIMERD_TAG "<timerd> "
typedef struct _TIMERD_MSG_T
{
    UINT32          ui4_msg_id;    
    UINT32          ui4_data1;
    UINT32          ui4_data2;
    UINT32          ui4_data3;
} TIMERD_MSG_T;

/* application structure */
typedef struct _TIMERD_OBJ_T
{
    HANDLE_T        h_app;    
    BOOL            b_app_init_ok;
}TIMERD_OBJ_T;

/*app private  msg*/
enum
{
    TIMERD_PRI_KEY_MSG,
    TIMERD_PRI_DM_MSG,
    
    TIMERD_PRI_MAX_MSG
};

struct _TIMER_CBFCT_ARGS{
	HANDLE_T h_app;
	void *ptimer_msg;
	UINT32 msg_size;
};


/*------------------------------------------------------------------------------
                                            funcitons declarations
------------------------------------------------------------------------------*/
typedef VOID (*u_os_timer_cb_fct) (HANDLE_T  pt_tm_handle,
                                   struct _TIMER_CBFCT_ARGS *     pv_tag);
extern INT32 os_timer_init (VOID);  

                                 
extern UINT16 timerd_get_dbg_level(VOID);
extern VOID timerd_set_dbg_level(UINT16 ui2_db_level);
                                                                                                 
#endif /* _HELLOTEST_H_ */
