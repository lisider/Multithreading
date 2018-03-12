#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include "netinfd.h"
#include "request.h"
#include "utility.h"

/*******************************************************************************/
/* NETINFD local definitions                                                     */
/*******************************************************************************/

/*******************************************************************************/
/* NETINFD local prototypes                                                      */
/*******************************************************************************/

/*******************************************************************************/
/* NETINFD local variables                                                       */
/*******************************************************************************/

/*******************************************************************************/
/* NETINFD local functions                                                       */
/*******************************************************************************/

/*******************************************************************************/
/* NETINFD functions                                                             */
/*******************************************************************************/
int netinfd_get(char *key, char **value)
{
	struct netinfd_request request;

	bzero(&request, sizeof(struct netinfd_request));

	request.magic = NETINFD_REQUEST_MAGIC;
	request.type = NETINFD_REQUEST_TYPE_GET;
	request.key = key;

	if (request_for_netinfd(&request) < 0 || request.key == NULL) {
		*value = NULL;
		return -1;
	}

	if (request.value == NULL) {
		*value = NULL;
	}
	else {
		*value = strdup(request.value);
	}

	return 0;
}

int netinfd_set(char *key, char *value)
{
	struct netinfd_request request;

	bzero(&request, sizeof(struct netinfd_request));

	request.magic = NETINFD_REQUEST_MAGIC;
	request.type = NETINFD_REQUEST_TYPE_SET;
	request.key = key;
	request.value = value;

	if (request_for_netinfd(&request) < 0) {
		return -1;
	}

	return 0;
}

int netinfd_dhcp(char *key, char *value)
{
	struct netinfd_request request;

	bzero(&request, sizeof(struct netinfd_request));

	request.magic = NETINFD_REQUEST_MAGIC;
	request.type = NETINFD_REQUEST_TYPE_DHCP;
	request.key = key;
	request.value = value;
	printf("DHCP cmd : %s, nif : %s\n", key, value);

	if (request_for_netinfd(&request) < 0) {
		return -1;
	}

	return 0;
}

int netinfd_ifconf(char *key, char *value)
{
	struct netinfd_request request;

	bzero(&request, sizeof(struct netinfd_request));

	request.magic = NETINFD_REQUEST_MAGIC;
	request.type = NETINFD_REQUEST_TYPE_IFCONF;
	request.key = key;
	request.value = value;
	printf("IFCONF nif : %s, info: %s\n", key, value);

	if (request_for_netinfd(&request) < 0) {
		return -1;
	}

	return 0;
}

int netinfd_nienable(char *key, char *value)
{
	struct netinfd_request request;
	printf("__%s:%d__\n",__FUNCTION__,__LINE__);

	bzero(&request, sizeof(struct netinfd_request));
	printf("__%s:%d__\n",__FUNCTION__,__LINE__);

	request.magic = NETINFD_REQUEST_MAGIC;
	request.type = NETINFD_REQUEST_TYPE_NIENABLE;
	
	printf("__%s:%d__\n",__FUNCTION__,__LINE__);
	request.key = key;
	request.value = value;
	printf("__%s:%d__\n",__FUNCTION__,__LINE__);
	if (request_for_netinfd(&request) < 0) {
		return -1;
	}

	return 0;
}

int netinfd_dnslookup(char *key, char *value)
{
	struct netinfd_request request;

	bzero(&request, sizeof(struct netinfd_request));

	request.magic = NETINFD_REQUEST_MAGIC;
	request.type =  NETINFD_REQUEST_TYPE_DNSLOOKUP;
	request.key = key;
	request.value = value;
	printf("DNS Lookup URL : %s, timeout : %s\n", key, value);

	if (request_for_netinfd(&request) < 0) {
		return -1;
	}

	return 0;
}

