#ifndef _U_AISPEECH_MANAGER_H_
#define _U_AISPEECH_MANAGER_H_

typedef struct _AISPEECH_MSG_T
{
    UINT32          ui4_msg_id;    
    UINT32          ui4_data1;
	unsigned char  *data;
	//void  *data1;
} AISPEECH_MSG_T;

typedef struct _AISPEECH_GRAM_MP3_PARAM_LIST_T
{
	int imageSize;
	int id;
	char domain[20];
	char artistImg[120];
	char artist[20];
	char title[40];
	char url[120];
	int size;
	char *output;
}AISPEECH_GRAM_MP3_PARAM_LIST_T;

typedef enum 
{
	AISPEECH_MANAGER_INFORM_WAKEUP = ((unsigned int)0),
	AISPEECH_MANAGER_INFORM_NATIVE_TTS,
	AISPEECH_MANAGER_INFORM_CLOUD_GRAM_START,
	AISPEECH_MANAGER_INFORM_CLOUD_GRAM_END,
	AISPEECH_MANAGER_INFORM_CLOUD_GRAM_RESULT,
	AISPEECH_MANAGER_INFORM_MAX
}AISPEECH_MANAGER_MSG_T;

extern INT32 u_ai_manager_send_msg(AISPEECH_MSG_T* pt_event);
//extern void u_aispeech_manager_set_gram_mp3_params(AISPEECH_GRAM_MP3_PARAM_LIST_T ** param);
#endif
