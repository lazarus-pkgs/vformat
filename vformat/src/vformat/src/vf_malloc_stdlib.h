/******************************************************************************

    (C) Nick Marley, 2001 -

    This software is distributed under the GNU Lesser General Public Licence.
    Please read and understand the comments at the top of vf_iface.h before use!

FILE
    $Workfile: vf_malloc.h $
    $Revision: 1.2 $
    $Author: tilda $
         
ORIGINAL AUTHOR
    Nick Marley

DESCRIPTION
    Externs for the malloc() based memory allocator.

MODIFICATION HISTORY
 *  $Log: vf_malloc_stdlib.h,v $
 *  Revision 1.2  2005/07/30 14:01:17  tilda
 *  Various header file tidy-ups.
 *
 *  Revision 1.1  2002/10/26 15:57:11  tilda
 *  Initial Version
 * 
 *******************************************************************************/

#ifndef INC_VF_MALLOC_STDLIB_H
#define INC_VF_MALLOC_STDLIB_H

#ifndef NORCSID
static const char vf_malloc_stdlib_h_vss_id[] = "$Header: /cvsroot/vformat/src/vformat/src/vf_malloc_stdlib.h,v 1.2 2005/07/30 14:01:17 tilda Exp $";
#endif

/*=============================================================================*
 Public Includes
 *============================================================================*/
/* None */

/*=============================================================================*
 Public Defines
 *============================================================================*/
/* None */

/*=============================================================================*
 Public Types
 *============================================================================*/
/* None */

/*=============================================================================*
 Public Functions
 *============================================================================*/
/* None */

/*=============================================================================*
 End of file
 *============================================================================*/

/*----------------------------------------------------------------------------*
 * NAME
 *      _vf_stdlib_malloc(), _vf_stdlib_realloc(), _vf_stdlib_free()
 * 
 * DESCRIPTION
 *      Memory allocation functions provided in terms of C runtime library
 *      malloc() etc.  If VFORMAT_MEM_DEBUG is defined the line & file are
 *      passed through for ebugging purposes.
 *
 * RETURNS
 *      (various)
 *----------------------------------------------------------------------------*/

#if defined(VFORMAT_MEM_DEBUG)

extern void *_vf_stdlib_malloc(uint32_t s, const char *file, int line);
extern void *_vf_stdlib_realloc(void *p, uint32_t ns, const char *file, int line);
extern void _vf_stdlib_free(void *p, const char *file, int line);

#else

extern void *_vf_stdlib_malloc(uint32_t s);
extern void *_vf_stdlib_realloc(void *p, uint32_t ns);
extern void _vf_stdlib_free(void *p);

#endif

/*=============================================================================*
 FIN
 *============================================================================*/

#endif /*INC_VF_MALLOC_STDLIB_H*/
