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
/*-----------------------------------------------------------------------------
 * $RCSfile: u_aee.h,v $
 * $Revision: #1 $
 * $Date: 2016/03/07 $
 * $Author: bdbm01 $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/3 $
 * $SWAuthor: Iolo Tsai $
 * $MD5HEX: 7073777ef840de31d560641fd88f5e7f $
 *
 * Description: 
 *         This header file contains AEE specific definitions, which are
 *         exported.
 *---------------------------------------------------------------------------*/

#ifndef _U_AEE_H_
#define _U_AEE_H_


/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "u_common.h"
#include "u_handle.h"
#include "u_os.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/* AEE API return values */

#define AEER_OK                    ((INT32)  0)
#define AEER_FAIL                  ((INT32) -1)
#define AEER_INV_ARG               ((INT32) -2)
#define AEER_INV_HANDLE            ((INT32) -3)
#define AEER_INV_NAME              ((INT32) -4)
#define AEER_OUT_OF_HANDLES        ((INT32) -5)
#define AEER_OUT_OF_MEMORY         ((INT32) -6)
#define AEER_OUT_OF_RESOURCES      ((INT32) -7)
#define AEER_NOT_AUTHORIZED        ((INT32) -8)
#define AEER_AEE_NO_RIGHTS         ((INT32) -9)
#define AEER_AEE_OUT_OF_RESOURCES  ((INT32) -10)

/* AEE authorization flags */
#define AEE_FLAG               ((UINT64) 0)
#define AEE_FLAG_WRITE_SVL     MAKE_BIT_MASK_64(0)
#define AEE_FLAG_WRITE_TSL     MAKE_BIT_MASK_64(1)
#define AEE_FLAG_WRITE_FLM     MAKE_BIT_MASK_64(2)
#define AEE_FLAG_WRITE_CONFIG  MAKE_BIT_MASK_64(3)


typedef VOID (* u_aee_app_main_fct) (HANDLE_T  h_app,
                                     VOID*     pv_arg);

typedef INT32 (* u_aee_app_receive_data_fct) (HANDLE_T  h_app,
                                              UINT32    ui4_type,
                                              VOID*     pv_data,
                                              SIZE_T    z_data_len);
#if AEE_RES_CONTROL_SUPPORT

typedef struct
{
    SIZE_T  z_min_memory;
    SIZE_T  z_max_memory;
    UINT64  ui8_max_files_size;
    UINT16  ui2_max_files;
    UINT16  ui2_max_handles;
    UINT16  ui2_max_threads;
    UINT16  ui2_max_semaphores;
    UINT16  ui2_max_msg_queues;
    UINT16  ui2_max_nb_msgs;
    UINT16  ui2_max_msg_size;
}   AEE_MAX_RESOURCES_T;

typedef struct
{
    SIZE_T  z_memory;
    UINT64  ui8_files_size;
    UINT16  ui2_files;
    UINT16  ui2_handles;
    UINT16  ui2_threads;
    UINT16  ui2_semaphores;
    UINT16  ui2_msg_queues;
}   AEE_RESOURCES_T;
#endif

typedef struct
{
    UINT64                      ui8_flags;	
    UINT32                      ui4_app_id;
    THREAD_DESCR_T              t_thread_desc;
    SIZE_T                      z_arg_size;
    u_aee_app_receive_data_fct  pf_receive_data;
    u_aee_app_main_fct          pf_main;
    VOID*                       pv_arg;
    UINT32                      ui4_app_group_id;
#if AEE_RES_CONTROL_SUPPORT
    AEE_MAX_RESOURCES_T         t_max_res;
#endif
}   AEE_APP_DESC_T;

#if AEE_RES_CONTROL_SUPPORT
typedef enum
{
    AEE_RES_MIN_MEMORY_ID,
    AEE_RES_MAX_MEMORY_ID,
    AEE_RES_MAX_FILES_SIZE_ID,
    AEE_RES_MAX_FILES_ID,
    AEE_RES_MAX_HANDLES_ID,
    AEE_RES_MAX_THREADS_ID,
    AEE_RES_MAX_SEMAPHORES_ID,
    AEE_RES_MAX_MSG_QUEUES_ID,
    AEE_RES_MAX_NB_MSGS_ID,
    AEE_RES_MAX_MSG_SIZE_ID,
    AEE_RES_MEMORY_ID,
    AEE_RES_FILES_SIZE_ID,
    AEE_RES_FILES_ID,
    AEE_RES_HANDLES_ID,
    AEE_RES_THREADS_ID,
    AEE_RES_SEMAPHORES_ID,
    AEE_RES_MSG_QUEUES_ID
}   AEE_RESOURCE_ID_T;
#endif


/**
\f u_aee_get_handle:
	allocate an handle for an app who's name is ps_name.
*/
extern INT32 u_aee_get_handle (const CHAR*  ps_name, HANDLE_T*    ph_app);
extern INT32 u_aee_free_handle (HANDLE_T*	  ph_app);



#endif /* _U_AEE_H_ */
