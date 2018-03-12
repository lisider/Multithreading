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
/*----------------------------------------------------------------------------*
 * $RCSfile: rwl_handle_cb.c,v $
 * $Revision: #1 $
 * $Date: 2016/07/22 $
 * $Author: bdbm01 $
 *
 * Description: 
 *         This file contains all implementations for the Read-Write lock
 *         handle free callbacks.
 *         
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
  include files
  ----------------------------------------------------------------------------*/

#include "u_common.h"
#include "u_dbg.h"
#include "u_handle.h"
#include "rwl.h"

/*-----------------------------------------------------------------------------
 * Name: rwl_handle_cb
 *
 * Description: This API is called whenever a read-write lock handle
 *              is being freed. If the read-write lock object has been
 *              marked for deleted, then this API return TRUE so the
 *              handle library can detach the handle from this read-write
 *              lock object.  Note: the read-write lock is not deleted
 *              until the last client has complete.
 *
 * Inputs:  h_obj         Contains the handle to read-write lock.
 *          e_type        Contains the read-write lock handle type and must be 
 *                        set to READ_WRITE_LOCK.
 *          pv_obj        References the read-write lock object structure.
 *          pv_tag        Ignored.
 *          b_req_handle  Is set to TRUE if the handle free was initiated with
 *                        this handle else FALSE.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
BOOL rwl_handle_cb (HANDLE_T       h_obj, 
                    HANDLE_TYPE_T  e_type,
                    VOID*          pv_obj,
                    VOID*          pv_tag, 
                    BOOL           b_req_handle)
{
    MRSW_LOCK_T* pt_rw_lock ;
    
    /* If no read-write lock object has been pass into this
       simply return . */
    if ( ( pt_rw_lock = ( (MRSW_LOCK_T*) pv_obj ) ) != NULL ) 
    {
        /* Abort if this is not the correct type. */
        if (e_type == READ_WRITE_LOCK )
        {
            /* Return TRUE  only if this rwlock has been marked
               for deletion.
            */
            if ( pt_rw_lock->b_del_flag != FALSE )
            {
                return TRUE;
            }
        }
        else
        {
            ABORT (DBG_CAT_HANDLE, DBG_ABRT_INVALID_HANDLE_TYPE);
        }
    }
    return FALSE;
}
