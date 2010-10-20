/******************************************************************************

    (C) Nick Marley, 2001 -

    THIS SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
    EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
    WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

    IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY SPECIAL, INCIDENTAL,
    INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER
    RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER OR NOT ADVISED OF
    THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF LIABILITY, ARISING OUT
    OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

FILE
    $Workfile: vf_iface.h $
    $Revision: 1.2 $
    $Author: tilda $

ORIGINAL AUTHOR
    Tilda@users.sourceforge.net <Nick Marley>

DESCRIPTION
    WIN32 library linking header file - avoids exposing various delightful
    compilers to #pragmas they don't recognise.  A compiler which barfs on
    a pragma it doesn't recognise when the whole point of pragmas is that
    they are compiler specific is beyond me, but never mind.

REFERENCES
    (none)

MODIFICATION HISTORY
 *  $Log: vf_win32libs.h,v $
 *  Revision 1.2  2003/09/25 07:25:27  tilda
 *  Tidy header.
 *
 *  Revision 1.1  2003/09/24 18:24:43  tilda
 *  Initial Version.
 *
 *****************************************************************************/

#ifndef _VF_WIN32LIBS_H_
#define _VF_WIN32LIBS_H_

#ifndef NORCSID
static const char vf_win32libs_h_vss_id[] = "$Header: /cvsroot/vformat/src/vformat/vf_win32libs.h,v 1.2 2003/09/25 07:25:27 tilda Exp $";
#endif

/*============================================================================*
 Public Includes
 *============================================================================*/
/* None */

/*============================================================================*
 Public defines
 *============================================================================*/

#if defined(_USRDLL)
 #ifndef VFORMATDECLSPEC
  #ifdef VFORMATL_EXPORTS
   #define VFORMATDECLSPEC __declspec(dllexport)
  #else
   #define VFORMATDECLSPEC __declspec(dllimport)
  #endif
 #endif
#endif

#if !defined(VFORMAT_BUILD)
 #if defined(_DEBUG)
  #pragma comment(lib, "VFORMATLD.lib")
 #else
  #pragma comment(lib, "VFORMATL.lib")
 #endif
#endif

/*============================================================================*
 Public Types
 *============================================================================*/
/* None */

/*============================================================================*
 Public Functions
 *============================================================================*/
/* None */

/*============================================================================*
 End of file
 *============================================================================*/

#endif /*_VF_WIN32LIBS_H_*/
