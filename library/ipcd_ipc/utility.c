#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utility.h"


/*******************************************************************************/
/* UTILITY local definitions                                                   */
/*******************************************************************************/
#define SYS_Printf printf

/*******************************************************************************/
/* UTILITY local prototypes                                                    */
/*******************************************************************************/


/*******************************************************************************/
/* UTILITY local variables                                                     */
/*******************************************************************************/


/*******************************************************************************/
/* UTILITY local functions                                                     */
/*******************************************************************************/


/*******************************************************************************/
/* UTILITY functions                                                           */
/*******************************************************************************/
ssize_t safe_read(int fd, void *buf, size_t count)
{
	ssize_t n;
  ssize_t tot = 0;
  ssize_t localcnt = count;
  //SYS_Printf("Safe read tot : %d !!\n", count);

	do {
		n = read(fd, buf, localcnt);
        //SYS_Printf("Safe read : %d, fd : %d !!\n", n, fd);
    if (n < 0)
    {
      if (errno == EINTR)
            {
        n = 0;
            }
      else
      {
        SYS_Printf("Safe read error : %s !!\n", (char *)strerror(errno));
        return n;
      }
    }
        
    tot += n;
    if (tot >= count)
        {
      return count;
        }
    else
    {
      localcnt -= n;
      buf   += n;
      //SYS_Printf("Safe read cnt : %d --- tot: %d \n", n, tot);
    }
	} while (localcnt > 0);

	return n;
}


ssize_t safe_write(int fd, const void *buf, size_t count)
{
	ssize_t n;
  ssize_t tot = 0;
  ssize_t localcnt = count;
  //SYS_Printf("Safe write tot : %d !!\n", count);

	do {
		n = write(fd, buf, localcnt);
        //SYS_Printf("Safe write : %d , fd : %d!!\n", n, fd);
    if (n < 0)
    {
      if (errno == EINTR)
            {
        n = 0;
            }
      else
      {
        SYS_Printf("Safe write error : %s !!\n", (char *)strerror(errno));
        return n;
      }
    }
        
    tot += n;
    if (tot >= count)
        {
      return count;
        }
    else
    {
      localcnt -= n;
      buf   += n;
      //SYS_Printf("Safe write cnt : %d --- tot : %d \n", n, tot);
    }
	} while (localcnt > 0);

	return n;
}

