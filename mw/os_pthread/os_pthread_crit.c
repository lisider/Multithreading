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


#include <pthread.h>
#include "u_assert.h"
#include "u_dbg.h"
#include "u_os.h"


#define INVALID_PTHREAD_T ((pthread_t)(-1))


static struct
{
    pthread_mutex_t mutex;
    pthread_t thread;
    INT16 i2_selfcount;
} s_crit =
{
    PTHREAD_MUTEX_INITIALIZER,
    INVALID_PTHREAD_T,
    (INT16)(0)
};


CRIT_STATE_T
u_crit_start(VOID)
{
    pthread_t thread = pthread_self();
    if (!pthread_equal(s_crit.thread, thread))
    {
        VERIFY(pthread_mutex_lock(&s_crit.mutex) == 0);
        s_crit.thread = thread;
		
    }
    s_crit.i2_selfcount++;
    return (CRIT_STATE_T)(s_crit.i2_selfcount);
}


VOID
u_crit_end(CRIT_STATE_T t_old_level)
{
    ASSERT(pthread_equal(s_crit.thread, pthread_self()));
    ASSERT((CRIT_STATE_T)(s_crit.i2_selfcount) == t_old_level);
    s_crit.i2_selfcount--;
    if (s_crit.i2_selfcount == 0)
    {
        s_crit.thread = INVALID_PTHREAD_T;
        VERIFY(pthread_mutex_unlock(&s_crit.mutex) == 0);
    }
}

