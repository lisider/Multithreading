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
#ifndef _U_PLAYBACK_USB_H_
#define _U_PLAYBACK_USB_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*the struct of playback usb application's message*/
typedef struct _PB_USB_MSG_T
{
    UINT32          ui4_msg_id;
    UINT32          ui4_data1;
    UINT32          ui4_data2;
    UINT32          ui4_data3;
} PB_USB_MSG_T;

/*Alsa playback contorl msg*/
typedef enum{
    ALSA_USB_PB_START = ((UINT32)0),
    ALSA_USB_PB_CREATE_PB_LIST,
    ALSA_USB_PB_PARSER_FILE,
    ALSA_USB_PB_SET_HW_PARAMS,
    ALSA_USB_PB_CREATE_PB_THREAD,
    ALSA_USB_PB_PLAY,
    ALSA_USB_PB_PAUSE,
    ALSA_USB_PB_PLAY_PAUSE,
    ALSA_USB_PB_NEXT,         /*8*/
    ALSA_USB_PB_PREVIOUS,     /*9*/
    ALSA_USB_PB_STOP,         /*10*/
    ALSA_USB_PB_DELET_PB_LIST,
    ALSA_USB_PB_PCM_STATE_CHECK, /*12*/
    ALSA_USB_PB_DM_MSG,          /*13*/
    ALSA_USB_PB_MAX_MSG
} ALSA_USB_PB_CONTROL_MSG_T;

/*-----------------------------------------------------------------------------
                    extern functions declarations
-----------------------------------------------------------------------------*/
extern VOID u_playback_ui_msg_process(const VOID *pv_msg, SIZE_T z_msg_len);
extern INT32 u_playback_usb_send_msg(const PB_USB_MSG_T* pt_event);
#endif /* _U_PLAYBACK_USB_H_ */
