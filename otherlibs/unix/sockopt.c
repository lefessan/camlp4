/***********************************************************************/
/*                                                                     */
/*                           Objective Caml                            */
/*                                                                     */
/*            Xavier Leroy, projet Cristal, INRIA Rocquencourt         */
/*                                                                     */
/*  Copyright 1996 Institut National de Recherche en Informatique et   */
/*  en Automatique.  All rights reserved.  This file is distributed    */
/*  under the terms of the GNU Library General Public License.         */
/*                                                                     */
/***********************************************************************/

/* $Id$ */

#include <mlvalues.h>
#include "unixsupport.h"

#ifdef HAS_SOCKETS

#include <sys/types.h>
#include <sys/socket.h>

#ifndef SO_BROADCAST
#define SO_BROADCAST (-1)
#endif
#ifndef SO_OOBINLINE
#define SO_OOBINLINE (-1)
#endif

static int sockopt[] = {
  SO_DEBUG, SO_BROADCAST, SO_REUSEADDR, SO_KEEPALIVE, 
  SO_DONTROUTE, SO_OOBINLINE };

value unix_getsockopt(value socket, value option)
{
  int optval;
#ifdef HAS_SOCKLEN_T
  socklen_t optsize;
#else
  int optsize;
#endif
  optsize = sizeof(optval);
  if (getsockopt(Int_val(socket), SOL_SOCKET, sockopt[Int_val(option)],
                 (void *) &optval, &optsize) == -1)
    uerror("getsockopt", Nothing);
  return Val_int(optval);
}

value unix_setsockopt(value socket, value option, value status)
{
  int optval = Int_val(status);
  if (setsockopt(Int_val(socket), SOL_SOCKET, sockopt[Int_val(option)],
                 (void *) &optval, sizeof(optval)) == -1)
    uerror("setsockopt", Nothing);
  return Val_unit;
}

#else

value unix_getsockopt(value socket, value option)
{ invalid_argument("getsockopt not implemented"); }

value unix_setsockopt(value socket, value option, value status)
{ invalid_argument("setsockopt not implemented"); }

#endif
