/******************************************************************************

    (C) Nick Marley, 2001 -

    This software is distributed under the GNU Lesser General Public Licence.
    Please read and understand the comments at the top of vf_iface.h before use!

FILE
    $Revision: 1.10 $
    $Author: tilda $
         
ORIGINAL AUTHOR
    Nick Marley.

DESCRIPTION
    The vf_create_object() function.

REFERENCES
    (none)    

MODIFICATION HISTORY
 *  $Log: vf_create_object.c,v $
 *  Revision 1.10  2005/07/29 22:05:05  tilda
 *  Various compiler warnings.  Whitespace donated to charity.
 *
 *  Revision 1.9  2003/09/24 18:18:21  tilda
 *  XAP portability issues - compiler warnings etc.
 *
 *  Revision 1.8  2002/11/16 13:19:10  tilda
 *  IID639288 - Implement method for adding subobjects.
 *
 *  Revision 1.7  2002/11/03 18:43:16  tilda
 *  IID619851 - Update and check headers and function prototypes.
 *
 *  Revision 1.6  2002/10/29 07:19:20  tilda
 *  Tidy headers.
 *
 *  Revision 1.5  2002/10/26 16:09:24  tilda
 *  IID629125 - Ensure string functions used are portable.
 *
 *  Revision 1.4  2002/10/08 21:45:07  tilda
 *  IID620473 - reduce c-runtime dependencies.
 *
 *  Revision 1.3  2002/10/08 21:11:36  tilda
 *  Remove common.h.
 *
 *  Revision 1.2  2002/01/06 13:11:55  tilda
 *  Update header.
 *
 *  Revision 1.1  2002/01/06 13:08:15  tilda
 *  Change file name from vf_createobject.c
 *
 *******************************************************************************/

#ifndef NORCSID
static const char vf_create_object_c_vss_id[] = "$Header: /cvsroot/vformat/src/vformat/src/vf_create_object.c,v 1.10 2005/07/29 22:05:05 tilda Exp $";
#endif

/*============================================================================*
 ANSI C & System-wide Header Files
 *===========================================================================*/

#include <common/types.h>

/*===========================================================================*
 Interface Header Files
 *==========================================================================*/

#include "vformat/vf_iface.h"

/*===========================================================================*
 Local Header File
 *==========================================================================*/

#include "vf_config.h"
#include "vf_malloc.h"
#include "vf_internals.h"
#include "vf_strings.h"
#include "vf_string_arrays.h"

/*===========================================================================*
 Public Data
 *==========================================================================*/
/* None */

/*===========================================================================*
 Private Defines
 *==========================================================================*/
/* None */

/*===========================================================================*
 Private Data Types
 *==========================================================================*/
/* None */

/*===========================================================================*
 Private Function Prototypes
 *==========================================================================*/
/* None */

/*===========================================================================*
 Private Data
 *==========================================================================*/
/* None */

/*===========================================================================*
 Public Function Implementations
 *==========================================================================*/

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_create_object()
 * 
 * DESCRIPTION
 *      Creates and empty vformat object.
 *
 * RETURNS
 *      Ptr to object if created else NULL.
 *---------------------------------------------------------------------------*/

VF_OBJECT_T *vf_create_object(
    const char *p_type,             /* Type of object to create */
    VF_OBJECT_T *p_parent           /* Parent object if any */
    )
{
    VOBJECT_T *p_new = NULL;

    if (p_type)
    {
        p_new = (VOBJECT_T *)vf_malloc(sizeof(VOBJECT_T));

        if (p_new)
        {
            p_memset(p_new, '\0', sizeof(VOBJECT_T));

            p_new->p_type = (char *)vf_malloc(1L + p_strlen(p_type));

            p_new->p_parent = (VOBJECT_T *)p_parent;

            if (p_new->p_type)
            {
                p_strcpy(p_new->p_type, p_type);
            }
            else
            {
                vf_free(p_new);
                p_new = NULL;
            }
        }
    }

    return (VF_OBJECT_T *)p_new;
}

/*===========================================================================*
 Private Function Implementations
 *===========================================================================*/
/* None */

/*===========================================================================*
 End Of File
 *===========================================================================*/
