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
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LASAMPLE 
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LASAMPLE PRINCIPLES.  
 ************************************************************************************************/
#ifndef _SAMPLE_H_
#define _SAMPLE_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_dbg.h"
#include "u_timerd.h"

#undef   DBG_LEVEL_MODULE
#define  DBG_LEVEL_MODULE       ht_get_dbg_level()

#define HT_TAG "<HELLO> "
typedef struct _SAMPLE_MSG_T
{
    UINT32          ui4_msg_id;    
    UINT32          ui4_data1;
    UINT32          ui4_data2;
    UINT32          ui4_data3;
} SAMPLE_MSG_T;

/* application structure */
typedef struct _SAMPLE_OBJ_T
{
    HANDLE_T        h_app;    
    HANDLE_T        h_iom;
    BOOL            b_app_init_ok;
    BOOL            b_recv_iom_msg;

	
	TIMER_TYPE_T my_timer_rep;
	TIMER_TYPE_T my_timer_once;
}SAMPLE_OBJ_T;

/*app private  msg*/
enum
{
    SAMPLE_PRI_KEY_MSG,
    SAMPLE_PRI_DM_MSG,
    
    SAMPLE_PRI_MAX_MSG
};

//------------------------------------------------------------------------------
//msg between ht and misc
#define MAX_USR_MSG_LEN     20
typedef struct
{
    UINT32      ui4_sender_id;      //in order to imitate APPMSG_T, the first two data just like it.
    UINT32      ui4_msg_type;

    BYTE        uc_usr_msg[MAX_USR_MSG_LEN + 1];

}HT_MISC_MSG_T;

typedef enum
{
    HT_TO_MISC_KEY_MSG,
    HT_TO_MISC_USER_MSG,

    MISC_TO_HT_KEY_MSG,

    HT_MISC_MAX_MSG
}HT_MISC_MSG_TYPE_T;

//------------------------------------------------------------------------------
//key info
typedef struct _IRRC_KEY_MAP
{
    char     *cName;
    UINT32   ui2_crystalkey;
    BOOL     b_support_repeat;
}   IRRC_KEY_MAP; 
extern const IRRC_KEY_MAP irrc_key_map[];

/*------------------------------------------------------------------------------
                                            funcitons declarations
------------------------------------------------------------------------------*/
extern UINT16 ht_get_dbg_level(VOID);
extern VOID ht_set_dbg_level(UINT16 ui2_db_level);
extern VOID ht_enable_recv_iom_msg(VOID);
extern VOID ht_disable_recv_iom_msg(VOID);
                                                                                                 
#endif /* _SAMPLE_H_ */
