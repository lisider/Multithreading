#ifndef _U_AISPEECH_APP_
#define _U_AISPEECH_APP_

typedef struct _AISPEECH_APP_MSG_T
{
    UINT32          ui4_msg_id;    
    UINT32          ui4_data1;
    UINT32          ui4_data2;
    VOID *			v_ptr;
} AISPEECH_APP_MSG_T;

typedef enum
{
	AISPEECH_APP_MESSAGE_START_NATIVE_TTS = ((unsigned int)0),
	AISPEECH_APP_MESSAGE_START_CLOUD_TTS,
	AISPEECH_APP_MESSAGE_MAX
}AISPEECH_APP_MESSAGE;

extern int u_ai_app_send_message(AISPEECH_APP_MSG_T* pt_event);
#endif
