#ifndef __NETINFD_H__
#define __NETINFD_H__


/*******************************************************************************/
/* NETINFD definitions                                                           */
/*******************************************************************************/

//#define NETINFD_SERV_PORT 55050

/*******************************************************************************/
/* NETINFD prototypes                                                            */
/*******************************************************************************/

/*******************************************************************************/
/* NETINFD variables                                                             */
/*******************************************************************************/

/*******************************************************************************/
/* NETINFD functions                                                             */
/*******************************************************************************/
extern int netinfd_get(char *key, char **value);
extern int netinfd_set(char *key, char *value);
extern int netinfd_dhcp(char *key, char *value);
extern int netinfd_ifconf(char *key, char *value);
extern int netinfd_nienable(char *key, char *value);
extern int netinfd_dnslookup(char * key, char * value);

#endif	// __NETINFD_H__
