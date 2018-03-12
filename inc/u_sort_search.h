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
 * $RCSfile: u_sort_search.h,v $
 * $Revision: #1 $
 * $Date: 2016/03/07 $
 * $Author: bdbm01 $
 *
 * Description: 
 *         This header file contains shared typedef and return codes for
 *         sorting and searching function API.
 *         
 *---------------------------------------------------------------------------*/

#ifndef _U_SORT_SEARCH_H_
#define _U_SORT_SEARCH_H_

/*---------------------------------------------------------------------------
                    include files
----------------------------------------------------------------------------*/

#include "u_common.h"

/*--------------------------------------------------------------------------
 Constants, enumerations, and macros
---------------------------------------------------------------------------*/
    
#define SSR_OK           ((INT32)   0)
#define SSR_INV_ARG      ((INT32)  -1)
#define SSR_OUT_OF_MEM   ((INT32)  -2)
#define SSR_NOT_FOUND    ((INT32)  -3)
#define SSR_FAIL         ((INT32)  -4)


/*
  return code for the sorting comparison function and for searching
  comparison function.
*/
#define  RC_CMP_FCT_T  INT32

#define   RC_SMALLER  ((INT32)-1)
#define   RC_EQUAL    ((INT32)0)
#define   RC_GREATER  ((INT32)1)
#define   RC_ERROR    ((INT32)-100)

/*---------------------------------------------------------------------------
 Type definition
----------------------------------------------------------------------------*/

/* 
  Typedef for the sort compare function. This function is passed
  to the x_qsort function.
   
*/
typedef INT32 (*x_sort_cmp_fct)
(
    const VOID*  pv_elem_a,
    const VOID*  pv_elem_b,
    VOID*        pv_opt_param
);

/* Typedef for the search compare function. This function is to be passed
   to the binary search function to compare the search parameters and search
   field in the element in the sorted array.
*/ 
typedef INT32 (*x_search_cmp_fct) 
(
    const VOID*  pv_elem_a,
    const VOID*  pv_search_param,
    VOID*        pv_opt_param
);

#endif /* _U_SORT_SEARCH_H_ */
