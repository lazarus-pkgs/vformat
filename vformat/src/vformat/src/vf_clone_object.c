/******************************************************************************

    (C) Nick Marley, 2001 -

    This software is distributed under the GNU Lesser General Public Licence.
    Please read and understand the comments at the top of vf_iface.h before use!

FILE
    $Revision: 1.2 $
    $Author: tilda $
         
ORIGINAL AUTHOR
    Marc Flerackers.

DESCRIPTION
    The vf_clone_object() function.

REFERENCES
    (none)    

MODIFICATION HISTORY
 *  $Log: vf_clone_object.c,v $
 *  Revision 1.2  2005/07/29 22:05:05  tilda
 *  Various compiler warnings.  Whitespace donated to charity.
 *
 *  Revision 1.1  2003/09/13 10:54:01  tilda
 *  Include vf_clone_object() contributed by Mark Flerakas.
 *
 *
 *******************************************************************************/

#ifndef NORCSID
static const char vf_clone_object_c_vss_id[] = "$Header: /cvsroot/vformat/src/vformat/src/vf_clone_object.c,v 1.2 2005/07/29 22:05:05 tilda Exp $";
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
 *      vf_clone_object()
 * 
 * DESCRIPTION
 *      Clones a vformat object.  Performs a deep copy of the supplied
 *      vformat - subobjects are also cloned.
 *
 * RETURNS
 *      Ptr to object if created else NULL.
 *---------------------------------------------------------------------------*/

VF_OBJECT_T *vf_clone_object(
    VF_OBJECT_T *p_object,          /* The object to clone */
    VF_OBJECT_T *p_parent           /* Parent object if any */
    )
{
    VOBJECT_T *object = (VOBJECT_T*)p_object;
    VOBJECT_T *new_object = NULL;

    if (object)
    {
        new_object = vf_malloc(sizeof(VOBJECT_T));

        if (new_object)
        {
            VPROP_T *new_props = NULL;
            VPROP_T *props;

            p_memset(new_object, '\0', sizeof(VOBJECT_T));

            new_object->p_type = vf_malloc(1 + p_strlen(object->p_type));
            p_strcpy(new_object->p_type, object->p_type);

            for (props = object->p_props; props != NULL; props = props->p_next)
            {
                if (new_props == NULL)
                    new_props = new_object->p_props = (VPROP_T *)vf_malloc(sizeof(VPROP_T));
                else
                    new_props = new_props->p_next = (VPROP_T *)vf_malloc(sizeof(VPROP_T));

                if (new_props)
                {
                    uint32_t index;

                    p_memset(new_props, '\0', sizeof(VPROP_T));

                    new_props->p_parent = new_object;

                    if (props->p_group)
                    {
                        new_props->p_group = vf_malloc(1 + p_strlen(props->p_group));
                        p_strcpy(new_props->p_group, props->p_group);
                    }
                    else
                        new_props->p_group = NULL;

                    /* copy name fields */
                    new_props->name.n_strings = props->name.n_strings;
                    new_props->name.pp_strings = vf_malloc(new_props->name.n_strings * sizeof(char*));

                    for (index = 0; index < props->name.n_strings; index++)
                    {
                        if (props->name.pp_strings[index])
                        {
                            new_props->name.pp_strings[index] =
                                vf_malloc(1 + p_strlen(props->name.pp_strings[index]));

                            p_strcpy(new_props->name.pp_strings[index],
                                props->name.pp_strings[index]);
                        }
                        else
                            new_props->name.pp_strings[index] = NULL;
                    }

                    /* copy value fields */
                    new_props->value.encoding = props->value.encoding;

                    switch (props->value.encoding)
                    {
                        case VF_ENC_VOBJECT:
                        {
                            /* Deep copy optional?! */
                            new_props->value.v.o.p_object = (VOBJECT_T *)
                                vf_clone_object((VF_OBJECT_T *)props->value.v.o.p_object, (VF_OBJECT_T *)new_object);
                            break;
                        }

                        case VF_ENC_7BIT:
                        case VF_ENC_QUOTEDPRINTABLE:
                        {
                            new_props->value.v.s.n_strings = props->value.v.s.n_strings;
                            new_props->value.v.s.pp_strings = vf_malloc(props->value.v.s.n_strings * sizeof(char*));

                            for (index = 0; index < props->value.v.s.n_strings; index++)
                            {
                                if (props->value.v.s.pp_strings[index])
                                {
                                    new_props->value.v.s.pp_strings[index] =
                                        vf_malloc(1 + p_strlen(props->value.v.s.pp_strings[index]));

                                    p_strcpy(new_props->value.v.s.pp_strings[index],
                                        props->value.v.s.pp_strings[index]);
                                }
                                else
                                    new_props->value.v.s.pp_strings[index] = NULL;
                            }

                            break;
                        }
                        case VF_ENC_8BIT:
                        case VF_ENC_BASE64:
                        {
                            new_props->value.v.b.n_bufsize = props->value.v.b.n_bufsize;

                            if (props->value.v.b.p_buffer)
                            {
                                new_props->value.v.b.p_buffer =
                                    vf_malloc(props->value.v.b.n_bufsize);

                                p_memcpy(new_props->value.v.b.p_buffer,
                                    props->value.v.b.p_buffer, props->value.v.b.n_bufsize);
                            }
                            else
                                new_props->value.v.b.p_buffer = NULL;

                            break;
                        }
                    }               
                }
            }

            new_object->p_parent = (VOBJECT_T*)p_parent;
        }
    }

    return (VF_OBJECT_T *)new_object;
}

/*===========================================================================*
 Private Function Implementations
 *===========================================================================*/
/* None */

/*===========================================================================*
 End Of File
 *===========================================================================*/
