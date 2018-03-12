#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "u_common.h"
#include "u_amb.h"
#include "u_am.h"
#include "u_assert.h"
#include "u_cli.h"
#include "u_dbg.h"
#include "u_app_thread.h"
#include "u_c4a_stub.h"
#include "u_assistant_stub.h"
#include "u_app_def.h"
//#include "u_acfg.h"
//#include "mas_lib.h"
#include "led.h"

/*-----------------------------------------------------------------------------
 * macro definitions
 *---------------------------------------------------------------------------*/
#define APPMAIN_TAG "<appmain>"
#define APPMAIN_DEBUG(x) printf x
#define APPMAIN_OK 0
#define APPMAIN_FAIL -1

UINT32 ui4_enable_all_log = 1;

/*-----------------------------------------------------------------------------
 * structure definitions
 *---------------------------------------------------------------------------*/

typedef struct _APP_MNGR_INIT_SEQ_T
{
    HANDLE_T  h_sema;  /* Semaphore handle for the application manager sequencing. */
    BOOL  b_ok;        /* Boolean state indicating application manager init successfull. */
}APP_MNGR_INIT_SEQ_T;


typedef VOID (*app_register_fct)(AMB_REGISTER_INFO_T * );


typedef struct{
	app_register_fct _regfct;
	AMB_REGISTER_INFO_T _reginfo;
	char * app_name;
}APP_REG;

/*-----------------------------------------------------------------------------
 * extern function declarations
 *---------------------------------------------------------------------------*/
extern VOID a_hellotest_register(AMB_REGISTER_INFO_T* pt_reg);
#if CONFIG_SUPPORT_DM_APP
extern VOID a_dm_register(AMB_REGISTER_INFO_T* pt_reg);
#endif
extern VOID a_sm_register(AMB_REGISTER_INFO_T* pt_reg);
extern VOID a_playback_uri_register(AMB_REGISTER_INFO_T* pt_reg);
extern VOID a_playback_tts_register(AMB_REGISTER_INFO_T* pt_reg);
extern VOID a_playback_prompt_register(AMB_REGISTER_INFO_T* pt_reg);
extern VOID a_button_sound_register(AMB_REGISTER_INFO_T* pt_reg);
extern VOID a_timerd_register(AMB_REGISTER_INFO_T* pt_reg);
extern VOID a_acfg_register(AMB_REGISTER_INFO_T*  pt_reg);
extern VOID a_user_interface_register(AMB_REGISTER_INFO_T*  pt_reg);
#if CONFIG_SUPPORT_BT_APP
extern VOID a_bluetooth_register(AMB_REGISTER_INFO_T* pt_reg);
#endif
extern VOID a_wifi_setting_register(AMB_REGISTER_INFO_T* pt_reg);
extern VOID a_misc_register(AMB_REGISTER_INFO_T* pt_reg);
extern VOID a_upg_register(AMB_REGISTER_INFO_T* pt_reg);
extern VOID a_upg_control_register(AMB_REGISTER_INFO_T* pt_reg);
#if CONFIG_SUPPORT_BT_HFP_APP
extern VOID a_bluetooth_hfp_register(AMB_REGISTER_INFO_T* pt_reg);
#endif

/*-----------------------------------------------------------------------------
 * private function declarations
 *---------------------------------------------------------------------------*/
VOID x_appl_init (VOID);


/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
//void* g_mas_handle = NULL;

static APP_REG app_to_reg[] = {
#if 0
		{a_timerd_register,{0},TIMERD_THREAD_NAME},
        {a_acfg_register,{0},ACFG_THREAD_NAME},
		{a_sm_register,{0},SM_THREAD_NAME},
        {a_assistant_stub_register,{0},ASSISTANT_STUB_THREAD_NAME},
	    {a_wifi_setting_register,{0},WIFI_SETTING_THREAD_NAME},
	    {a_misc_register,{0},MISC_THREAD_NAME},
		{a_upg_register,{0},UPG_THREAD_NAME},
        {a_playback_uri_register,{0},PB_URI_THREAD_NAME},
        {a_playback_tts_register,{0},PB_TTS_THREAD_NAME},
        {a_playback_prompt_register,{0},PB_PROMPT_THREAD_NAME},
		{a_button_sound_register,{0},BTN_SOUND_THREAD_NAME},
#if CONFIG_SUPPORT_DM_APP
		{a_dm_register,{0},DM_THREAD_NAME},
#endif
	    {a_user_interface_register,{0},USER_INTERFACE_THREAD_NAME},
#if CONFIG_SUPPORT_BT_APP
	    {a_bluetooth_register,{0},BLUETOOTH_THREAD_NAME},
#endif
#if CONFIG_SUPPORT_BT_HFP_APP
        {a_bluetooth_hfp_register,{0},BLUETOOTH_HFP_THREAD_NAME},
#endif
        {a_upg_control_register, {0}, UPG_CONTROL_THREAD_NAME},
#endif
		{NULL,{0},NULL}
};

/*---------------------------------------------------------------------------
 * Name
 *      app_mngr_nfy_fct
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static BOOL app_mngr_nfy_fct (HANDLE_T          h_app_mngr,
                              VOID*             pv_tag,
                              APP_NFY_REASON_T  e_nfy_reason)
{
    if ((pv_tag != NULL)                           &&
        ((e_nfy_reason == APP_NFY_INIT_OK)       ||
         (e_nfy_reason == APP_NFY_INIT_FAILED)))
    {
        if (e_nfy_reason == APP_NFY_INIT_OK)
        {
            ((APP_MNGR_INIT_SEQ_T*) pv_tag)->b_ok = TRUE;
        }

        ASSERT(u_sema_unlock (((APP_MNGR_INIT_SEQ_T*) pv_tag)->h_sema) == OSR_OK);
    }

    return (FALSE);
}

/*---------------------------------------------------------------------------
 * Name
 *      x_appl_init
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
VOID x_appl_init (VOID)
{
    HANDLE_T              h_app_mngr;
    APP_MNGR_INIT_SEQ_T   t_app_mngr_init_seq;
    AMB_REGISTER_INFO_T   t_amb_reg_info;

    /* Create the application manager synchronization semaphore. */
    ASSERT(u_sema_create (&t_app_mngr_init_seq.h_sema, X_SEMA_TYPE_BINARY, X_SEMA_STATE_LOCK) == OSR_OK);


    /* Initialize application manager */
    u_am_init (& t_amb_reg_info);


    t_app_mngr_init_seq.b_ok = FALSE;
    /* Start application manager */
    ASSERT (u_app_start (&(t_amb_reg_info.t_fct_tbl),
                     &(t_amb_reg_info.t_desc),
                     t_amb_reg_info.s_name,
                     app_mngr_nfy_fct, //这个函数作为指针传入,会在想要解锁的时候,执行
                     ((VOID*) &t_app_mngr_init_seq),
                     &h_app_mngr) == AEER_OK);

    /* And now wait until the application manager has signaled that it */
    /* has successfully started.                                       */
    ASSERT(u_sema_lock (t_app_mngr_init_seq.h_sema, X_SEMA_OPTION_WAIT) == OSR_OK); //阻塞,知道 上个 u_app_start 里面开的线程执行了 _CONTINUE (t_g_am.h_bin_sema);
    /* If the application manager could not start successfully, abort.*/
    ASSERT ((t_app_mngr_init_seq.b_ok));
    /* Free the application manager sequencing semaphore. */
    ASSERT (u_sema_delete (t_app_mngr_init_seq.h_sema) == OSR_OK);


    return;
}

/*---------------------------------------------------------------------------
 * Name
 *      app main
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
	int ret = APPMAIN_OK;
	int status; //用来存储 回收进程的状态
	pid_t pid; //用来存储 fork 后的 pid
	int file; //没有用到

	/*mtk demo board led show function*/
	/*fd_led = open(LED_FD,0);
	if(fd_led < 0)
	{
		printf("open device LED_FD fail \n");
	}
	led_horse_race(100,COLOR_BLUE);
	led_light_stop();*/

#if 0
	/*coredump function*/
	if(0 == access("/data/enable_coredump", 0)) //测试是否存在
	{
		system("ulimit -c 200000");//以 512 字节块为单位，指定核心转储的大小 //100000KB 97MB
		system("mkdir /data/coredump");
		system("echo /data/coredump/core.%e.%p.%t > /proc/sys/kernel/core_pattern");
	}
	else
	{
		system("ulimit -c 0"); //不生成core 文件
		system("echo /data/coredump/core.%e.%p.%t > /proc/sys/kernel/core_pattern");
	}
#endif 

#if CONFIG_SUPPORT_APPMAIN_RESTART
	restart:

	pid = fork();

	if(0 > pid)
	{
		APPMAIN_DEBUG((APPMAIN_TAG"fork child process error at line %d\n",__LINE__));
	}
	else if(0 < pid)
	{
		/*parent process*/
		APPMAIN_DEBUG((APPMAIN_TAG"parent process pid is %d, child process pid is %d\n",getpid(),pid));
		int quit_pid = waitpid(pid,&status,0);
		APPMAIN_DEBUG((APPMAIN_TAG"quit pid is %d, exit status is %d\n",quit_pid,WEXITSTATUS(status)));

		APPMAIN_DEBUG((APPMAIN_TAG"kill btservice\n"));
		/*kill main btservice process*/
		system("killall -9 btservice");

		/*need to remove the alsa device handle used flag*/
		system("rm -f /tmp/mtkac0_opened");
		system("rm -f /tmp/mtkac1_opened");
		system("rm -f /tmp/mtkac2_opened");

		/*restart bt service*/
		system("/usr/bin/btservice&");
		goto restart;
	}
	else
#endif
	{
#if 0
		/*init output log type*/
		if(0 == access("/home/suweishuai/tmp/log_all",0)){
			ui4_enable_all_log = 0;
			APPMAIN_DEBUG((APPMAIN_TAG"enable all ouput in appmainprog!!\n"));
		}
#endif
		ui4_enable_all_log = 1;
		APPMAIN_DEBUG((APPMAIN_TAG"enable all ouput in appmainprog!!\n"));
		APPMAIN_DEBUG((APPMAIN_TAG"**********************************************\n"));
		APPMAIN_DEBUG((APPMAIN_TAG"child process id is %d\n",getpid()));
		APPMAIN_DEBUG((APPMAIN_TAG"Appcliation Init Begin\n"));
//		APPMAIN_DEBUG((APPMAIN_TAG"Audio Mas process Init\n"));
//		CHECK_ASSERT(mas_create(&g_mas_handle)); //这个函数 在  libmas2.so libmas.so  中 ,是 预编译的 //nm -D  /home/suweishuai/mtk_root/8516/build/tmp/work/aud8516p1v2_consys_slc-poky-linux/mtk-image-aud-8516/1.0-r0/rootfs/usr/lib64/libmas.so |grep mas_creat
#if CONFIG_SUPPORT_BT_HFP_APP
		//if custom's SPK only support 48k, please set fix sample rate to MAS
//		CHECK_ASSERT(mas_set_out_samplerate_rule(g_mas_handle,MAS_OUT_SR_FIX,48000)); //nm -D  /home/suweishuai/mtk_root/8516/build/tmp/work/aud8516p1v2_consys_slc-poky-linux/mtk-image-aud-8516/1.0-r0/rootfs/usr/lib64/libmas2.so |grep mas_set_out_samplerate_rule
#endif
//		CHECK_ASSERT(mas_start(g_mas_handle));

		APPMAIN_DEBUG((APPMAIN_TAG"OS thread Init\n"));
		CHECK_ASSERT(os_thread_init()); //初始化了一个上帝线程

#if CLI_SUPPORT//没有定义
		APPMAIN_DEBUG((APPMAIN_TAG"Cli Init\n"));
		CHECK_ASSERT(u_cli_init());
#endif

		APPMAIN_DEBUG((APPMAIN_TAG"Dbg Backtrace Init\n"));
		//CHECK_ASSERT(dbg_init()); //信号安装器

		APPMAIN_DEBUG((APPMAIN_TAG"AEE Init\n"));
		CHECK_ASSERT(aee_init()); //不知道是干什么的

		APPMAIN_DEBUG((APPMAIN_TAG"Handle Usr Init\n"));
		CHECK_ASSERT(u_handle_usr_init(256));//申请了 256 + 5个handle结构体 ,并初始化了这些结构体

		APPMAIN_DEBUG((APPMAIN_TAG"Am Init\n"));
		x_appl_init(); //启动了一个app ? 来管理 //Start application manager  启动成功才会返回,启动不成功直接退出

		int i = 0;
		APP_REG * app = app_to_reg;//这些都是要注册的
		while(app->_regfct != NULL)
		{
			APPMAIN_DEBUG((APPMAIN_TAG"%d.%s Init Begin\n",i+1,app->app_name));
			app->_regfct(&app->_reginfo); //填充info
			if(APPMAIN_OK == (ret = u_amb_register_app(&app->_reginfo))) //注册 app 
			{
				if(APPMAIN_OK == (ret = u_amb_sync_start_app(app->app_name)))
					APPMAIN_DEBUG((APPMAIN_TAG"%d.%s Init Successful\n",i+1,app->app_name));
				else
					APPMAIN_DEBUG((APPMAIN_TAG"%d.%s sync start fail ret %d\n",i+1,app->app_name,ret));
			}
			else
			{
				APPMAIN_DEBUG((APPMAIN_TAG"%d.%s register fail ret %d\n",i+1,app->app_name,ret));
			}
			app = &app_to_reg[++i];
		}
		APPMAIN_DEBUG((APPMAIN_TAG"Appcliation Init Finish\n"));
		APPMAIN_DEBUG((APPMAIN_TAG"**********************************************\n"));

		/*mtk demo board led show function*/
		/*led_blink(100,3,COLOR_BLUE);
		led_light_stop();
		led_light(100,COLOR_BLUE);*/

		while(1)
		{
			pid = waitpid(-1,&status,WNOHANG);
			if(pid > 0)
				APPMAIN_DEBUG((APPMAIN_TAG"waitpid pid %d,status = %08x\n",pid,status));
			sleep(1);
		}
	}
}
