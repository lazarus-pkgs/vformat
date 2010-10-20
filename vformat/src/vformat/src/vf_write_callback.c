/******************************************************************************

    (C) Nick Marley, 2001 -

    This software is distributed under the GNU Lesser General Public Licence.
    Please read and understand the comments at the top of vf_iface.h before use!

FILE
    $Workfile$
    $Revision: 1.3 $
    $Author: tilda $
         
ORIGINAL AUTHOR
    Nick Marley.

DESCRIPTION
    Callback to a user supplied function passing text.

REFERENCES
    (none)    

MODIFICATION HISTORY
 *  $Log: vf_write_callback.c,v $
 *  Revision 1.3  2005/07/29 22:05:06  tilda
 *  Various compiler warnings.  Whitespace donated to charity.
 *
 *  Revision 1.2  2003/09/13 10:54:01  tilda
 *  Include vf_clone_object() contributed by Mark Flerakas.
 *
 *  Revision 1.33  2003/09/13 10:18:35  tilda
 *  Initial implementation change and provision of new write interface.
 *
 *******************************************************************************/

#ifndef NORCSID
static const char vf_write_callback_c_vss_id[] = "$Header: /cvsroot/vformat/src/vformat/src/vf_write_callback.c,v 1.3 2005/07/29 22:05:06 tilda Exp $";
#endif

/*=============================================================================*
 ANSI C & System-wide Header Files
 *=============================================================================*/

#include <common/types.h>

/*============================================================================*
 Interface Header Files
 *============================================================================*/

#include <vformat/vf_iface.h>

/*============================================================================*
 Local Header File
 *============================================================================*/

#include "vf_config.h"
#include "vf_internals.h"
#include "vf_malloc.h"

/*============================================================================*
 Public Data
 *============================================================================*/
/* None */

/*============================================================================*
 Private Defines
 *============================================================================*/

/*
 * Increase for (slighty) better performance at the penalty of stack space.
 */
#if !defined(VFWRITEBUFSIZE)
#define VFWRITEBUFSIZE      (32)
#endif

/*============================================================================*
 Private Data Types
 *============================================================================*/
/* None */

/*============================================================================*
 Private Function Prototypes
 *============================================================================*/
/* None */

/*============================================================================*
 Private Data
 *============================================================================*/
/* None of course */

/*============================================================================*
 Public Function Implementations
 *============================================================================*/

/*----------------------------------------------------------------------------*
 * NAME
 *      vf_write_to_callback()
 * 
 * DESCRIPTION
 *      Convert indicated vobject to textual representation and pass text to
 *      a user supplied callback function.  Could be used to stream vformat
 *      objects to disk etc.
 *
 *      Buffer can be user allocated or allocated from the VFORMAT library
 *      heap.  Pass NULL as buffer pointer to request the latter.
 *
 *      Different applications will dispose of the text produced by the
 *      VF_WRITER_T object in diferent ways - it may be more efficient
 *      to code your own streaming loop depending on what you're doing.
 *
 * RETURNS
 *      TRUE <=> written OK, FALSE else.
 *----------------------------------------------------------------------------*/

bool_t vf_write_to_callback(
    VF_OBJECT_T *p_object,      /* The object to write */
    char *p_buffer,             /* Buffer to use */
    uint16_t bufsize,           /* Size of buffer to use */
    vf_write_flags_t flags,     /* Flags controlling operation */
    vf_write_callback_t cb,     /* The callback function */
    uint32_t n_context,         /* Some callback context */
    void *p_context             /* A bit more callback context */
    )
{
    bool_t ret = FALSE;

    if (p_object && cb)
    {
        char *p_callback_buffer;
        uint16_t bytes_written;
        VF_WRITER_T *p_writer;

        if (p_buffer)
        {
            /* user supplied buffer */

            p_callback_buffer = p_buffer;
        }
        else
        {
            /* library allocated buffer */

            bufsize = VFWRITEBUFSIZE;
            p_callback_buffer = vf_malloc(bufsize);
        }

        if (p_callback_buffer)
        {
            if (vf_write_init(&p_writer, p_object, flags))
            {
                do
                {
                    if (vf_write_to_buf(p_writer, p_callback_buffer, bufsize, &bytes_written))
                    {
                        ret = cb(p_callback_buffer, bytes_written, n_context, p_context);
                    }
                }
                while (ret && (0 < bytes_written))
                    ;

                /*
                 * Have to have a tidy up function since callback may have failed and
                 * left the writer with allocated memory - but this can't fail so "void".
                 */
                vf_write_end(p_writer);
            }

            if (!p_buffer)
            {
                vf_free(p_callback_buffer);
            }
        }
    }

    return ret;
}

/*============================================================================*
 Private Function Implementations
 *============================================================================*/
/* None */

/*============================================================================*
 End Of File
 *============================================================================*/
