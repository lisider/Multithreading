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
#include <string.h>
/* application level */
#include "u_amb.h"
#include "u_common.h"
#include "u_app_thread.h"
#include "u_cli.h"
#include "u_os.h"
#include "u_assert.h"
/* private */
#include "ws.h"
#include "ws_cli.h"

static WS_OBJ_T t_g_ht               = {0};
static UINT16 ui2_g_ws_dbg_level = DBG_INIT_LEVEL_APP_WS;

typedef enum
{
	E_EHLO_TIMER_MSG_DEMO_REPATER,
	E_EHLO_TIMER_MSG_DEMO_ONCE,
	E_EHLO_TIMER_MSG_MAX
}E_HELO_TIMER_MSG;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _ws_start (
                    const CHAR*                 ps_name,
                    HANDLE_T                    h_app
                    );
static INT32 _ws_exit (
                    HANDLE_T                    h_app,
                    APP_EXIT_MODE_T             e_exit_mode
                    );
static INT32 _ws_process_msg (
                    HANDLE_T                    h_app,
                    UINT32                      ui4_type,
                    const VOID*                 pv_msg,
                    SIZE_T                      z_msg_len,
                    BOOL                        b_paused
                    );
/*---------------------------------------------------------------------------
 * Name
 *      a_app_set_registration
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
VOID a_ws_register(
                AMB_REGISTER_INFO_T*            pt_reg
                )
{
    if (t_g_ht.b_app_init_ok == TRUE) {
        return;
    }
	DBG_API_IN;
    /* Application can only use middleware's c_ API */
    memset(pt_reg->s_name, 0, sizeof(CHAR)*(APP_NAME_MAX_LEN + 1));
    strncpy(pt_reg->s_name, WS_THREAD_NAME, APP_NAME_MAX_LEN);
    pt_reg->t_fct_tbl.pf_init                   = _ws_start;
    pt_reg->t_fct_tbl.pf_exit                   = _ws_exit;
    pt_reg->t_fct_tbl.pf_process_msg            = _ws_process_msg;

    pt_reg->t_desc.ui8_flags                    = ~((UINT64)0);
    pt_reg->t_desc.t_thread_desc.z_stack_size   = 4096;
    pt_reg->t_desc.t_thread_desc.ui1_priority   = 200;
    pt_reg->t_desc.t_thread_desc.ui2_num_msgs   = 20;

    pt_reg->t_desc.ui2_msg_count                = 20;
    pt_reg->t_desc.ui2_max_msg_size             = 64;
    return;
}

UINT16 ht_get_dbg_level(VOID)
{
    return (ui2_g_ws_dbg_level | DBG_LAYER_APP);
}

VOID ht_set_dbg_level(UINT16 ui2_db_level)
{
    ui2_g_ws_dbg_level = ui2_db_level;
}


static INT32 _ws_start (
                    const CHAR*                 ps_name,
                    HANDLE_T                    h_app
                    )
{
    INT32 i4_ret;
    DBG_API_IN;
    memset(&t_g_ht, 0, sizeof(WS_OBJ_T));
    t_g_ht.h_app = h_app;


    if (t_g_ht.b_app_init_ok)
    {
        return AEER_OK;
    }
#ifdef CLI_SUPPORT
    i4_ret = ht_cli_attach_cmd_tbl();
    if ((i4_ret != CLIR_NOT_INIT) && (i4_ret != CLIR_OK))
    {
        DBG_ERROR((HT_TAG"Err: ht_cli_attach_cmd_tbl() failed, ret=%ld\r\n",
            i4_ret ));
        return AEER_FAIL;
    }
    ht_set_dbg_level(DBG_INIT_LEVEL_APP_WS);
#endif/* CLI_SUPPORT */

    t_g_ht.b_app_init_ok = TRUE;


#if 0
	t_g_ht.my_timer_rep.e_flags = X_TIMER_FLAG_REPEAT;
	t_g_ht.my_timer_rep.ui4_delay = 1500;
	E_HELO_TIMER_MSG msg_rep = E_EHLO_TIMER_MSG_DEMO_REPATER;
	t_g_ht.my_timer_once.e_flags = X_TIMER_FLAG_ONCE;
	t_g_ht.my_timer_once.ui4_delay = 1000;
	E_HELO_TIMER_MSG msg_one = E_EHLO_TIMER_MSG_DEMO_ONCE;

	CHECK_ASSERT(u_timer_create(&t_g_ht.my_timer_rep.h_timer));
	CHECK_ASSERT(u_timer_start(t_g_ht.h_app,&t_g_ht.my_timer_rep, (void *)&msg_rep,sizeof(E_HELO_TIMER_MSG)));

	CHECK_ASSERT(u_timer_create(&t_g_ht.my_timer_once.h_timer));
	CHECK_ASSERT(u_timer_start(t_g_ht.h_app,&t_g_ht.my_timer_once, (void *)&msg_one,sizeof(E_HELO_TIMER_MSG)));
#endif
    DBG_API_OUT;


    return AEER_OK;
}

static INT32 _ws_exit (
                    HANDLE_T                    h_app,
                    APP_EXIT_MODE_T             e_exit_mode
                    )
{
    INT32 i4_ret;
    DBG_API_IN;

    t_g_ht.b_app_init_ok = FALSE;

    DBG_API_OUT;
    return AEER_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _ws_process_msg
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _ws_process_msg (
                    HANDLE_T                    h_app,
                    UINT32                      ui4_type,
                    const VOID*                 pv_msg,
                    SIZE_T                      z_msg_len,
                    BOOL                        b_paused
                    )
{
    UCHAR* pc_name;
    UINT32             i4_ret;
    const CHAR *pc_keysta, *pc_keyval;
    DBG_API_IN;

    if (t_g_ht.b_app_init_ok == FALSE) {
        return AEER_FAIL;
    }

    if (ui4_type < AMB_BROADCAST_OFFSET)
    {
    	switch(ui4_type){
			case E_APP_MSG_TYPE_TIMER:
				{
					static int count = 0;
					E_HELO_TIMER_MSG msg = *(E_HELO_TIMER_MSG*)pv_msg;
					DBG_INFO(("------receive timer %d\n",msg));
					if(msg==E_EHLO_TIMER_MSG_DEMO_ONCE)
					{
						if(count < 3)
						{
							E_HELO_TIMER_MSG msg_one = E_EHLO_TIMER_MSG_DEMO_ONCE;
							CHECK_ASSERT(u_timer_start(t_g_ht.h_app,&t_g_ht.my_timer_once, (void *)&msg_one,sizeof(E_HELO_TIMER_MSG)));
							count++;
						}else
							u_timer_delete(t_g_ht.my_timer_once.h_timer);
					}
				}
				break;
			default:
				break;
		}
    }
    else
    {
    	switch(ui4_type){
			case E_APP_MSG_TYPE_DUT_STATE:
				{
					// should get power on/off msg here
				}
				break;
			case E_APP_MSG_TYPE_USB_DEV:
				{
					// should get usb plug in /out, file system mount/unmount msg.
				}
				break;
		}
        DBG_INFO(("am broadcast message\n"));
    }
    DBG_API_OUT;
    return AEER_OK;
}

