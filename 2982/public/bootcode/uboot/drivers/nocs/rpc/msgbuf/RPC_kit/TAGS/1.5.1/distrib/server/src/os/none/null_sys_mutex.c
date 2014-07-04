/**
**  @file null_sys_mutex.c
**
** @brief
**    This header file implements the NULL MSGBUF system mutex interface.
**    (only used in non-multitreaded environment.
**
**  $Id:$
**  $Change:$
**
** REMARK:
**   Comments in this file use special tags to allow automatic API
**   documentation generation in HTML format, using the GNU-General
**   Public Licensed Doxygen tool. For more information about Doxygen,
**   please check www.doxygen.org
**
**   Depending on the platform, the CHM file may not open properly if it
**   is stored on a network drive. So either the file should be moved on
**   a local drive or add the following registry entry on Windows platform
**  (regedit):\n
**   [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x\\ItssRestrictions] "MaxAllowedZone"=dword:00000003
*/

#include "inc/os/msgbuf_sys_mutex.h"


/* */
TMsgbuf_thread_mutex MSGBUF_SYS_createThreadMutex (void)
{
  return (TMsgbuf_thread_mutex)-1;
}


/* */
int MSGBUF_SYS_deleteThreadMutex
(
  TMsgbuf_thread_mutex xMutex
)
{
  return 0;
}


/* */
int MSGBUF_SYS_acquireThreadMutex
(
  TMsgbuf_thread_mutex xMutex
)
{
  return 0;
}


/* */
int MSGBUF_SYS_releaseThreadMutex
(
  TMsgbuf_thread_mutex xMutex
)
{
  return 0;
}


/* */
TMsgbuf_thread_sem MSGBUF_SYS_createThreadSem
(
  int xInitialToken
)
{
  return (TMsgbuf_thread_sem)-1;
}


/* */
int MSGBUF_SYS_deleteThreadSem
(
  TMsgbuf_thread_sem xSem
)
{
  return 0;
}


/* */
int MSGBUF_SYS_acquireThreadSem
(
  TMsgbuf_thread_sem xSem
)
{
  return 0;
}


/* */
int MSGBUF_SYS_releaseThreadSem
(
  TMsgbuf_thread_sem xSem
)
{
  return 0;
}
