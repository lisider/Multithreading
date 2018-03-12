#ifndef __X_IPCD_H__
#define __X_IPCD_H__

#ifdef __cplusplus
extern "C"
{
#endif
/*******************************************************************************/
/* IPCD definitions                                                           */
/*******************************************************************************/

//#define IPCD_SERV_PORT 58530
typedef enum _IPCD_EVENT_T
{
    IPCD_EXEC_FAILED = -1,
    IPCD_EXEC_SUCESS = 0
}IPCD_EVENT_T;

typedef void (* IPCD_EXEC_CB_FP)(IPCD_EVENT_T event);

/*******************************************************************************/
/* IPCD prototypes                                                            */
/*******************************************************************************/

/*******************************************************************************/
/* IPCD variables                                                             */
/*******************************************************************************/

/*******************************************************************************/
/* IPCD functions                                                             */
/*******************************************************************************/
extern int ipcd_exec(char *cmd, char *priv);
extern int ipcd_exec_security(char *cmd, char *priv);
extern int ipcd_exec_async(char *cmd, char *priv, IPCD_EXEC_CB_FP callback);
extern int ipcd_get_env(char* envName, char* envVal);
extern int ipcd_set_env(char* envName, char* envVal);
extern int net_get_validMac(char* pmac);

#ifdef __cplusplus
}
#endif
#endif	// __X_IPCD_H__
