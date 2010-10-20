/****************************************************************************

    (C) Nick Marley, 2001 -

    This software is distributed under the GNU Lesser General Public Licence.
    Please read and understand the comments at the top of vf_iface.h before use!

FILE
    $Workfile: vf_access.c $
    $Revision: 1.21 $
    $Author: tilda $
         
ORIGINAL AUTHOR
    Nick Marley

DESCRIPTION
    Wrappers on the core access functions & other utility functions.

REFERENCES
    (none)    

MODIFICATION HISTORY
 *  $Log: vf_access_wrappers.c,v $
 *  Revision 1.21  2005/07/30 13:50:35  tilda
 *  Fix compiler warnings by implementing function.
 *
 *  Revision 1.20  2005/07/30 08:32:03  tilda
 *  Compiler warnings.  p_strncat() for unreferenced buffer sizes.
 *
 *  Revision 1.19  2005/07/29 22:05:05  tilda
 *  Various compiler warnings.  Whitespace donated to charity.
 *
 *  Revision 1.18  2003/09/24 18:18:21  tilda
 *  XAP portability issues - compiler warnings etc.
 *
 *  Revision 1.17  2003/07/14 11:42:23  tilda
 *  Various vCalendar updates from home PC #2.
 *
 *  Revision 1.16  2002/11/16 13:19:10  tilda
 *  IID639288 - Implement method for adding subobjects.
 *
 *  Revision 1.15  2002/11/03 18:43:16  tilda
 *  IID619851 - Update and check headers and function prototypes.
 *
 *  Revision 1.14  2002/11/02 18:29:26  tilda
 *  IID485157 - UI does character conversion based on CHARSET property.
 *
 *  Revision 1.13  2002/10/26 16:09:24  tilda
 *  IID629125 - Ensure string functions used are portable.
 *
 *  Revision 1.12  2002/10/08 21:45:07  tilda
 *  IID620473 - reduce c-runtime dependencies.
 *
 *  Revision 1.11  2002/10/08 21:11:36  tilda
 *  Remove common.h.
 *
 *  Revision 1.10  2001/11/18 22:07:02  tilda
 *  Ensure empty BASE64 properties get the encoding set correctly.
 *
 *  Revision 1.9  2001/11/18 21:48:18  tilda
 *  Remove redundant code.
 *
 *  Revision 1.8  2001/11/17 17:40:29  tilda
 *  Image / sound dialog box now works.
 *
 *  Revision 1.7  2001/11/16 22:34:50  tilda
 *  New vf_get_property() allows append as well as find,
 *
 *  Revision 1.6  2001/11/15 08:56:06  tilda
 *  Fix bug in qualifier location code.
 *
 *  Revision 1.5  2001/11/14 22:36:56  tilda
 *  Add parameter to vf_find_prop_qual_index()
 *
 *  Revision 1.4  2001/11/14 16:05:06  tilda
 *  Extend capabilities of vf_find_prop_qual_index().
 *
 *  Revision 1.3  2001/11/06 22:51:05  tilda
 *  Supporting access functions for image selection / deletion.
 *
 *  Revision 1.2  2001/10/24 18:56:29  tilda
 *  Tidy headers after import.  Fix include path in release build.
 *
 *  Revision 1.1  2001/10/24 18:34:35  tilda
 *  Initial Version.
 *
 *****************************************************************************/

#ifndef NORCSID
static const char vf_access_wrappers_c_vss_id[] = "$Header: /cvsroot/vformat/src/vformat/src/vf_access_wrappers.c,v 1.21 2005/07/30 13:50:35 tilda Exp $";
#endif

/*============================================================================*
 ANSI C & System-wide Header Files
 *============================================================================*/

#include <common/types.h>

/*===========================================================================*
 Interface Header Files
 *===========================================================================*/

#include "vformat/vf_iface.h"

/*===========================================================================*
 Local Header File
 *===========================================================================*/

#include "vf_config.h"
#include "vf_malloc.h"
#include "vf_internals.h"
#include "vf_strings.h"
#include "vf_string_arrays.h"

/*===========================================================================*
 Public Data
 *===========================================================================*/
/* None */

/*===========================================================================*
 Private Defines
 *===========================================================================*/
/* None */

/*===========================================================================*
 Private Data Types
 *===========================================================================*/
/* None */

/*===========================================================================*
 Private Function Prototypes
 *===========================================================================*/
/* None */

/*===========================================================================*
 Private Data
 *===========================================================================*/
/* None */

/*===========================================================================*
 Public Function Implementations
 *===========================================================================*/

bool_t vf_prop_belongs_to_object(
    VF_PROP_T *p_prop,
    VF_OBJECT_T *p_object
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_prop_value_string()
 * 
 * DESCRIPTION
 *      Obtain string pointer value from VF_PROP_T.  If the array contains
 *      an entry for the indicated string return it. Return NULL if out of
 *      range request, ie. n_string=3 for N=0;1;2
 *
 * RETURNS
 *      Pointer to string value if value present, NULL if index  too large.
 *---------------------------------------------------------------------------*/

char *vf_get_prop_value_string(
    VF_PROP_T *p_prop,
    uint32_t n_string
    )
{
    VPROP_T *p_vprop = (VPROP_T *)p_prop;
    char *p_ret = NULL;

    if (p_vprop->value.v.s.pp_strings)
    {      
        if (n_string < p_vprop->value.v.s.n_strings)
        {
            p_ret = p_vprop->value.v.s.pp_strings[n_string];
        }
    }

    return p_ret;
}

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_set_prop_value_string()
 * 
 * DESCRIPTION
 *      Set the value of a property.
 *
 * RETURNS
 *      TRUE <=> set successfully.
 *---------------------------------------------------------------------------*/

bool_t vf_set_prop_value_string(
    VF_PROP_T *p_prop,
    uint32_t n_string,
    const char *p_string
    )
{
    return vf_set_prop_value(p_prop, (char *)p_string, n_string, VF_ENC_7BIT, TRUE);
}

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_prop_value_base64()
 * 
 * DESCRIPTION
 *      Obtain data pointer for BASE64 data.
 *
 * RETURNS
 *      Pointer to data.
 *---------------------------------------------------------------------------*/

const uint8_t *vf_get_prop_value_base64(
    VF_PROP_T *p_prop,                          /* Property we're setting a value in */
    uint32_t *p_length                          /* Length of the binary data */
    )    
{
    const uint8_t *p_return = NULL;

    if (p_prop)
    {
        VPROP_T *p_vprop = (VPROP_T *)p_prop;

        p_return = (uint8_t *)p_vprop->value.v.b.p_buffer;

        if (p_length)
        {
            *p_length = p_vprop->value.v.b.n_bufsize;
        }
    }

    return p_return;
}

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_set_prop_value_base64()
 * 
 * DESCRIPTION
 *      Set the value of a property.
 *
 * RETURNS
 *      TRUE <=> set successfully.
 *---------------------------------------------------------------------------*/

bool_t vf_set_prop_value_base64(
    VF_PROP_T *p_prop,                          /* Property we're setting a value in */
    const uint8_t *p_data,                      /* Pointer to the binary data */
    uint32_t length,                            /* Length of the binary data */
    bool_t copy                                 /* Copy or keep pointer */
    )
{
    return vf_set_prop_value(p_prop, (char *)p_data, length, VF_ENC_BASE64, copy);
}

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_prop_value_object()
 * 
 * DESCRIPTION
 *      Obtain object pointer value from VF_PROP_T.
 *
 * RETURNS
 *      Pointer to vobject value (or NULL if not found).
 *---------------------------------------------------------------------------*/

VF_OBJECT_T *vf_get_prop_value_object(
    VF_PROP_T *p_prop
    )
{
    VPROP_T *p_vprop = (VPROP_T *)p_prop;

    if (VF_ENC_VOBJECT == p_vprop->value.encoding)
    {
        return (VF_OBJECT_T *)(p_vprop->value.v.o.p_object);
    }

    return NULL;
}

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_set_prop_value_object()
 * 
 * DESCRIPTION
 *      Set the value of the indicated property to be a VOBJECT.
 *
 * RETURNS
 *      TRUE <=> set successfully.
 *---------------------------------------------------------------------------*/

bool_t vf_set_prop_value_object(
    VF_PROP_T *p_prop,
    VF_OBJECT_T *p_object
    )
{
    VPROP_T *p_vprop = (VPROP_T *)p_prop;
    bool_t ret = FALSE;

    /*
     * Avoid various sillies.
     */
    if (p_prop && p_object && !vf_prop_belongs_to_object(p_prop, p_object))
    {
        delete_prop_contents(p_prop, FALSE);
        
        p_vprop->value.v.o.p_object = (VOBJECT_T *)p_object;
        p_vprop->value.encoding = VF_ENC_VOBJECT;

        ret = TRUE;
    }

    return ret;
}

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_prop_name_string()
 * 
 * DESCRIPTION
 *      Get n'th name string.
 *
 * RETURNS
 *      Pointer to string value if value present, NULL if index  too large.
 *---------------------------------------------------------------------------*/

char *vf_get_prop_name_string(
    VF_PROP_T *p_prop,
    uint32_t n_string
    )
{
    VPROP_T *p_vprop = (VPROP_T *)p_prop;
    char *p_ret = NULL;

    if (p_vprop->name.pp_strings)
    {      
        if (n_string < p_vprop->name.n_strings)
        {
            p_ret = p_vprop->name.pp_strings[n_string];
        }
    }

    return p_ret;
}

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_set_prop_name_string()
 * 
 * DESCRIPTION
 *      Set n'th name string.
 *
 * RETURNS
 *      TRUE iff allocation OK, FALSE else.
 *---------------------------------------------------------------------------*/

bool_t vf_set_prop_name_string(
    VF_PROP_T *p_prop,                          /* Property we're setting a value in */
    uint32_t n_string,                          /* Index to string */
    const char *p_string                        /* Pointer to string */
    )
{
    VPROP_T *p_vprop;
    bool_t ret = FALSE;

    p_vprop = (VPROP_T *)p_prop;

    if (p_vprop)
    {
        if ((-1) == n_string)
        {
            ret = add_string_to_array(&p_vprop->name, p_string);
        }
        else
        {
            ret = set_string_array_entry(&p_vprop->name, p_string, n_string);
        }
    }

    return TRUE;
}

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_find_prop_qual_index()
 * 
 * DESCRIPTION
 *      Various search methods for finding property qualifiers. For example
 *      if we have a property:
 *
 *      NAME;THIRD;TIME;LUCKY=JIM:VALUE1;VALUE2;VALUE3
 *
 *      Then there are two possible searches:
 *
 *      1) we can look for the property qualifier which can take values from
 *      the array { "FIRST", "SECOND", THIRD" } in which case the array is
 *      passed as pp_possible_values and the function returns with the
 *      values *p_found_value_index=2, p_qualifier_index=1.  p_token is
 *      set to NULL in this case.
 *
 *      2) we can look for the token with value "TIME" in which case p_token
 *      is set to "TIME" and the function returns *p_qualifier_index=2.
 *      pp_possible_values is set to NULL in this case.
 *
 * RETURNS
 *      TRUE iff found, FALSE else.
 *---------------------------------------------------------------------------*/

bool_t vf_find_prop_qual_index(
    VF_PROP_T *p_prop,                          /* The property we're querying */
    uint32_t *p_qualifier_index,                /* Ptr to output name index */
    uint32_t *p_found_value_index,              /* Ptr to output index in array */
    const char **pp_possible_values,            /* Array of possible values */
    const char *p_token                         /* Token searched for */
    )
{
    uint32_t n;
    bool_t ret;

    VPROP_T *p_vprop = (VPROP_T *)p_prop;

    for (n = 0, ret = FALSE;!ret && (n < p_vprop->name.n_strings);n++)
    {
        const char *p_string = p_vprop->name.pp_strings[n];

        if (p_string)
        {
            if (pp_possible_values && !p_token)
            {
                uint32_t i;

                for (i = 0;!ret && pp_possible_values[i];i++)
                {
                    if (0 == p_stricmp(pp_possible_values[i], p_string))
                    {
                        if (p_found_value_index)
                            *p_found_value_index = i;
                        if (p_qualifier_index)
                            *p_qualifier_index = n;

                        ret = TRUE;
                    }
                }
            }
            else
            if (!pp_possible_values && p_token)
            {
                if (0 == p_stricmp(p_token, p_string))
                {
                    if (p_qualifier_index)
                        *p_qualifier_index = n;

                    ret = TRUE;
                }
            }
            else
            if (pp_possible_values && p_token)
            {
                /* not used at present */
            }
            else
            {
                /* not meaningful */
            }
        }
    }

    return ret;
}

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_find_property_qualifier_value()
 * 
 * DESCRIPTION
 *      Locate value of property qualifier given name of qualifier.  For
 *      example if we have a property:
 *
 *      NAME;THIRD;TIME;LUCKY=JIM:VALUE1;VALUE2;VALUE3
 *
 *      Then passing p_token="LUCKY" will return *p_qualifier_index=3 and
 *      *pp_value="JIM".
 *
 * RETURNS
 *      TRUE iff found, FALSE else.
 *---------------------------------------------------------------------------*/

VFORMATDECLSPEC bool_t vf_find_property_qualifier_value(
    VF_PROP_T *p_prop,                          /* The property we're querying */
    uint32_t *p_qualifier_index,                /* Ptr to output name index */
    const char **pp_value,                      /* Array of possible values */
    const char *p_token                         /* Token searched for */
    )
{
    bool_t ret = FALSE;
    VPROP_T *p_vprop = (VPROP_T *)p_prop;

    if (p_token && p_vprop)
    {
        char *p_value;

        if (!string_array_contains_string(&p_vprop->name, p_qualifier_index, &p_value, (uint32_t)-1, p_token, FALSE))
        {
            p_value = NULL;
        }
        else
        {
            p_value += 1 + p_strlen(p_token);

            ret = TRUE;
        }

        if (pp_value)
        {
            *pp_value = p_value;
        }
    }

    return ret;
}

/*----------------------------------------------------------------------------*
 * NAME
 *      vf_find_charset()
 * 
 * DESCRIPTION
 *      Locate the charset 
 *
 * RETURNS
 *      vf_charset_t.
 *---------------------------------------------------------------------------*/

const char *vf_find_charset(
    VF_PROP_T *p_prop
    )
{
    const char *p_value;

    vf_find_property_qualifier_value(p_prop, NULL, &p_value, VFP_CHARSET);

    return p_value;
}

/*----------------------------------------------------------------------------*
 * NAME
 *      vf_prop_belongs_to_object()
 * 
 * DESCRIPTION
 *      Check to see if 'p_prop' belongs to 'p_object'
 *
 * RETURNS
 *      (bool_t)
 *---------------------------------------------------------------------------*/

bool_t vf_prop_belongs_to_object(
    VF_PROP_T *p_prop,
    VF_OBJECT_T *p_object
    )
{
    bool_t ret = FALSE;
    VPROP_T *p_vprop = (VPROP_T *)p_prop;
    VOBJECT_T *p_vobject = (VOBJECT_T *)p_object;

    if (p_vprop)
    {
        VOBJECT_T *p_parent = p_vprop->p_parent;

        while (p_parent)
        {
            if (p_parent == p_vobject)
            {
                ret = TRUE;
            }

            p_parent = p_parent->p_parent;
        }
    }

    return ret;
}

/*===========================================================================*
 Private Function Implementations
 *===========================================================================*/
/* None */

/*===========================================================================*
 End Of File
 *===========================================================================*/
