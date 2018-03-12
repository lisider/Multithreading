#ifndef __REQUEST_H__
#define __REQUEST_H__


/*******************************************************************************/
/* REQUEST definitions                                                         */
/*******************************************************************************/
#define IPCD_REQUEST_MAGIC			0x8530
#define IPCD_REQUEST_MAX_SIZE		6144
#define IPCD_SERV_PORT 58530

#define SYSTEM_UID     100
#define SYSTEM_GID     100

#define IPCD_UNIX_DOMAIN_PATH "/tmp/ipcd"

#define IPCD_USE_UNIX_SOCKET 1

#define NETINFD_REQUEST_MAGIC			0x8530
#define NETINFD_REQUEST_MAX_SIZE		4096
#define NETINFD_SERV_PORT 55050
/*******************************************************************************/
/* REQUEST prototypes                                                          */
/*******************************************************************************/
enum {
	IPCD_REQUEST_TYPE_EXEC = 0,
	IPCD_REQUEST_TYPE_EXEC_ASYNC,
	
	IPCD_REQUEST_TYPE_SETENV,
	IPCD_REQUEST_TYPE_GETENV,

	IPCD_REQUEST_TYPE_RESERVED	
};


struct ipcd_request {
	unsigned int magic;
	unsigned int type;
	int status;
	int reservedLen;
	char *cmd;
	char *priv;
	char string[IPCD_REQUEST_MAX_SIZE];	/* enough ?? */
};

enum {
	NETINFD_REQUEST_TYPE_GET = 0,
	NETINFD_REQUEST_TYPE_SET,
	NETINFD_REQUEST_TYPE_DHCP,
	NETINFD_REQUEST_TYPE_IFCONF,
	NETINFD_REQUEST_TYPE_NIENABLE,
	NETINFD_REQUEST_TYPE_DNSLOOKUP,
	NETINFD_REQUEST_TYPE_RESERVED
};


struct netinfd_request {
	unsigned int magic;
	unsigned int type;
	int status;
	int reservedLen;
	char *key;
	char *value;
	char string[NETINFD_REQUEST_MAX_SIZE];	/* enough ?? */
};


/*******************************************************************************/
/* REQUEST variables                                                           */
/*******************************************************************************/

/*******************************************************************************/
/* REQUEST functions                                                           */
/*******************************************************************************/
extern int pack_request(struct ipcd_request *request);
extern int unpack_request(struct ipcd_request *request, int size);
extern int connect_request(void);
extern int accept_request(int sockfd);
extern int request_for_ipcd(struct ipcd_request *request);

extern int pack_request_netinf(struct netinfd_request *request);
extern int unpack_request_netinf(struct netinfd_request *request, int size);
extern int connect_request_netinf(void);
extern int request_for_netinfd(struct netinfd_request *request);
#endif	// __REQUEST_H__
