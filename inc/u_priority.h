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
/*! \file u_priority.h
*
* \par Project
*    MT8520
*
* \par Description
*    Definition for thread priority.
*
* \par Author_Name
*    mtk00874
*
* \par Last_Changed
* $Author: bdbm01 $
* $Modtime: $
* $Revision: #2 $
*
*/


#ifndef U_PRIORITY_H
#define U_PRIORITY_H

/*
* ===========
*  GUIDELINE
* ===========
*
* 1. This header file is used by each layer to define thread priority.
*
* 2. A thread priority is defined by three parts, namely [class], [layer], and [offset].
*
* 3. You can add a new class or layer or modify the value if necessary.
*
* 4. Do not assume what the value is, because it may be changed when porting to other OS.
*
* 5. [offset] should be in the range of [-5, 5]. The larger [offset] value, the lower priority.
*
* 5. Define your thread priority like this:
*
*    #define XXX_THREAD_PRIORITY PRIORITY(PRIORITY_CLASS_NORMAL, PRIORITY_LAYER_DRIVER, 0)
*
* 6. You can use an assertion macro to check the priority relationship between two threads.
*
*/


//
// priority class definition
//

#define PRIORITY_CLASS_REALTIME         50    ///< for hard real-time
#define PRIORITY_CLASS_HIGH             100   ///< for streaming
#define PRIORITY_CLASS_NORMAL           150   ///< for normal application
#define PRIORITY_CLASS_IDLE             200   ///< for background

//
// priority layer definition
//

#define PRIORITY_LAYER_TIME_CRITICAL    0
#define PRIORITY_LAYER_DRIVER           10
#define PRIORITY_LAYER_MIDDLEWARE       20
#define PRIORITY_LAYER_UI               30

//
// priority macro definition
//

#define PRIORITY(CLASS, LAYER, OFFSET)  ((CLASS) + (LAYER) + (OFFSET))


#endif // U_PRIORITY_H
