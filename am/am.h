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

#ifndef _AM_H_
#define _AM_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "u_common.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/* Maximum number of applications the system can register */
#define  MAX_APP_NUM             (30)

/* Maximum number of system keys applications can register */
#define  MAX_KEY_NUM             (15)

/* Maximum time delay for system key events */
#define  MAX_KEY_DELAY           (1000) /* in milliseconds *///modify by msz00575 BDP00114973

/* Synchronous operations */
#define  _SYNC_BEGIN(h_sema)     u_sema_lock(h_sema, X_SEMA_OPTION_WAIT)
#define  _SYNC_END(h_sema)       u_sema_unlock(h_sema)
#define  _WAIT(h_sema)           u_sema_lock(h_sema, X_SEMA_OPTION_WAIT)
#define  _CONTINUE(h_sema)       u_sema_unlock(h_sema)

/* Retry message queue */
#define  MSGQ_RETRY_TIMES        (10)  /* retry times */
#define  MSGQ_RETRY_DELAY        (10)  /* retry delay (in milliseconds) */

/* Redefine DBG_LEVEL_MODULE */
#undef   DBG_LEVEL_MODULE
#define  DBG_LEVEL_MODULE        am_get_dbg_level()

/* Defines for time measure module */
#undef   TMS_INIT_LEVEL
#define  TMS_INIT_LEVEL          TMS_LEVEL_NONE

#undef   TMS_MODULE_LEVEL
#define  TMS_MODULE_LEVEL        am_get_tms_level()

#define  TMS_NAME_APP_INIT       "APP_INIT"
#define  TMS_NAME_APP_RESUME     "APP_RESUME"
#define  TMS_NAME_APP_PAUSE      "APP_PAUSE"
#define  TMS_NAME_APP_EXIT       "APP_EXIT"


/*
   AM general variables.
*/
typedef struct
{
    /* Application manager data */
    HANDLE_T              h_am;                           /* application manager handle */
    HANDLE_T              h_mtx_sema;                     /* mutex semaphore */
    HANDLE_T              h_bin_sema;                     /* binary semaphore */
    UINT16                ui2_dbg_level;                  /* debug level */
    UINT16                ui2_tms_level;                  /* time measure level */

    /* Application information */
    HANDLE_T              ah_app[MAX_APP_NUM];            /* application handles */
    UINT32                ui4_app_id;                     /* indicates how many applications has been registered */
    UINT32                ui4_root_app_id;                /* root application's id */
    CHAR                  as_app_name[MAX_APP_NUM][APP_NAME_MAX_LEN+1]; /* application names */

}   AM_T;


#endif /* _AM_H_ */

