/******************************************************************************

    (C) Nick Marley, 2001 -

    This software is distributed under the GNU Lesser General Public Licence.
    Please read and understand the comments at the top of vf_iface.h before use!

FILE
    $Workfile$
    $Revision: 1.4 $
    $Author: tilda $
         
ORIGINAL AUTHOR
    Nick Marley.

DESCRIPTION
    Code for writing vformat files.  There are several parts to this:

    The lowest layer is a system for flattening vformat objects.  This allows
    a caller to recreate on demand sections of the text stream version of
    the object.  This code is presented in vf_writer.c and is independant
    of stdio etc.

    The second layer provides an API which streams a vformat object to a
    user supplied callback function.  This is presented in vf_write_callback.c
    and is also platform independant.

    Code below uses the VF_WRITER_T concept to write a vobject to a file
    using stdio functions.

    I imagine this sounds more complicated than you might expect but bear in
    mind my usual bad tempered gripe about embedded systems and the general
    irrelevance of stdio to the portable interface layers they require :).

REFERENCES
    (none)    

MODIFICATION HISTORY
 *  $Log: vf_write_file.c,v $
 *  Revision 1.4  2005/07/29 22:05:06  tilda
 *  Various compiler warnings.  Whitespace donated to charity.
 *
 *  Revision 1.3  2003/09/24 10:50:47  tilda
 *  IID485267 - Remove assumption about non-blocking writer streams.
 *
 *  Revision 1.2  2003/09/13 10:54:01  tilda
 *  Include vf_clone_object() contributed by Mark Flerakas.
 *
 *  Revision 1.33  2003/09/13 10:18:35  tilda
 *  Initial implementation change and provision of new write interface.
 *
 *******************************************************************************/

#ifndef NORCSID
static const char vf_write_file_c_vss_id[] = "$Header: /cvsroot/vformat/src/vformat/src/vf_write_file.c,v 1.4 2005/07/29 22:05:06 tilda Exp $";
#endif

/*=============================================================================*
 ANSI C & System-wide Header Files
 *=============================================================================*/

#include <common/types.h>

#include <stdio.h>

/*============================================================================*
 Interface Header Files
 *============================================================================*/

#include <vformat/vf_iface.h>

/*============================================================================*
 Local Header File
 *============================================================================*/

#include "vf_config.h"
#include "vf_internals.h"

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
#define VFWRITEBUFSIZE          (32)
#endif
 
/*
 * Makefile overridable for other stdio.
 */
#if !defined(VFFILEWRITEMODE)
#define VFFILEWRITEMODE         "wb"
#endif

/*============================================================================*
 Private Data Types
 *============================================================================*/
/* None */

/*============================================================================*
 Private Function Prototypes
 *============================================================================*/

static bool_t write_to_stdio(
    FILE *fp,                   /* The FILE* we're writing to */
    char *p_buffer,             /* The buffer to fo whatever you're going to do */
    uint32_t charcount          /* Number of characters in the buffer */
    );

/*============================================================================*
 Private Data
 *============================================================================*/
/* None of course */

/*============================================================================*
 Public Function Implementations
 *============================================================================*/

/*----------------------------------------------------------------------------*
 * NAME
 *      vf_write_file()
 * 
 * DESCRIPTION
 *      Write indicated vobject to file.
 *
 * RETURNS
 *      TRUE <=> written OK, FALSE else.
 *----------------------------------------------------------------------------*/

bool_t vf_write_file(
    const char *p_name,         /* Outpt filename */
    VF_OBJECT_T *p_object,      /* The object to write */
    vf_write_flags_t flags      /* Flags controlling operation */
    )
{
    bool_t ret = FALSE;

    if (p_object && p_name)
    {
        FILE *fp = fopen(p_name, VFFILEWRITEMODE);

        if (fp)
        {
            char buffer[VFWRITEBUFSIZE];
            uint16_t bytes_written;
            VF_WRITER_T *p_writer;

            if (vf_write_init(&p_writer, p_object, flags))
            {
                do
                {
                    ret = vf_write_to_buf(p_writer, buffer, sizeof(buffer), &bytes_written);
                    ret &= write_to_stdio(fp, buffer, bytes_written);
                }
                while (ret && (0 < bytes_written))
                    ;

                /*
                 * Have to have a tidy up function since callback may have failed and
                 * left the writer with allocated memory - but this can't fail so "void".
                 */
                vf_write_end(p_writer);

                if (0 != fclose(fp))
                {
                    ret = FALSE;
                }
            }
        }
    }

    return ret;
}

/*============================================================================*
 Private Function Implementations
 *============================================================================*/

/*----------------------------------------------------------------------------*
 * NAME
 *      write_to_stdio()
 * 
 * DESCRIPTION
 *      Wrapper on fwrite().
 *
 * RETURNS
 *      TRUE <=> written OK, FALSE else.
 *----------------------------------------------------------------------------*/

bool_t write_to_stdio(
    FILE *fp,                   /* The FILE* we're writing to */
    char *p_buffer,             /* The buffer to fo whatever you're going to do */
    uint32_t charcount          /* Number of characters in the buffer */
    )
{
    return (bool_t)((charcount == (uint32_t)fwrite(p_buffer, 1, charcount, fp)) ? TRUE : FALSE);
}

/*============================================================================*
 End Of File
 *============================================================================*/
