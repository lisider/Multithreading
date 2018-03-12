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

#include "u_dbg.h"

#include "u_aee.h"

#include "timerd_cli.h"

#ifdef CLI_SUPPORT
#include "u_cli.h"
#include "u_app_thread.h"
#include "u_timerd.h"
#include "u_assert.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32  _timerd_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _timerd_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _timerd_cli_echo(INT32 i4_argc, const CHAR** pps_argv);

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/

/* wifi test command table */
static CLI_EXEC_T at_timerd_wifi_cmd_tbl[] =
{

    END_OF_CLI_CMD_TBL
};

/* main command table */
static CLI_EXEC_T at_timerd_cmd_tbl[] =
{
 	{
        CLI_GET_DBG_LVL_STR,
        NULL,
        _timerd_cli_get_dbg_level,
        NULL,
        CLI_GET_DBG_LVL_HELP_STR,
        CLI_GUEST
    },
	{
        CLI_SET_DBG_LVL_STR,
        NULL,
        _timerd_cli_set_dbg_level,
        NULL,
        CLI_SET_DBG_LVL_HELP_STR,
        CLI_GUEST
    },
    {
        "echo",
        "e",
        _timerd_cli_echo,
        NULL,
        "repeat the input string",
        CLI_GUEST
    },

 	END_OF_CLI_CMD_TBL
};
/* SVL Builder root command table */
static CLI_EXEC_T at_timerd_root_cmd_tbl[] =
{
	{
	    "timerd",
	    "td",
	    NULL,
	    at_timerd_cmd_tbl,
	    "timerd commands",
	    CLI_GUEST
	},
	END_OF_CLI_CMD_TBL
};
/*-----------------------------------------------------------------------------
 * export methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name:    ht_cli_attach_cmd_tbl
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
INT32 timerd_cli_attach_cmd_tbl(VOID)
{
    return (u_cli_attach_cmd_tbl(at_timerd_root_cmd_tbl, CLI_CAT_APP, CLI_GRP_GUI));
}


/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: _ht_cli_get_dbg_level
 *
 * Description: This API gets the current debug level.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _timerd_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_ret;

    i4_ret = u_cli_show_dbg_level(timerd_get_dbg_level());

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _ht_cli_set_dbg_level
 *
 * Description: This API sets the debug level.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _timerd_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    UINT16 ui2_dbg_level;
    INT32  i4_ret;

    i4_ret = u_cli_parse_dbg_level(i4_argc, pps_argv, &ui2_dbg_level);

    if (i4_ret == CLIR_OK){
        timerd_set_dbg_level(ui2_dbg_level);
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _ht_cli_echo
 *
 * Description: This API is only for test purpose.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _timerd_cli_echo (INT32 i4_argc, const CHAR** pps_argv)
{

    return CLIR_OK;
}


#endif
