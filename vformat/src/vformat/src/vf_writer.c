/******************************************************************************

    (C) Nick Marley, 2001 -

    This software is distributed under the GNU Lesser General Public Licence.
    Please read and understand the comments at the top of vf_iface.h before use!

FILE
    $Workfile$
    $Revision: 1.18 $
    $Author: tilda $
         
ORIGINAL AUTHOR
    Nick Marley.

DESCRIPTION
    Code for converting a memory object back to the textal representation.
    Used by the various flavours of "writing" calls.

    TODO: reduce the amount of intermediate memory used by the writer, which
    currently assumes that it can store amounts of text roughly equal to the
    encoded output of each property.  The buffered text should be stored in
    such a way that static strings or values taken directly from the object
    do not need copying to store.

REFERENCES
    (none)    

MODIFICATION HISTORY
 *  $Log: vf_writer.c,v $
 *  Revision 1.18  2005/08/02 15:13:04  tilda
 *  Minor mods to writer before re-write!
 *
 *  Revision 1.17  2005/07/29 22:05:06  tilda
 *  Various compiler warnings.  Whitespace donated to charity.
 *
 *  Revision 1.16  2003/09/24 18:18:21  tilda
 *  XAP portability issues - compiler warnings etc.
 *
 *  Revision 1.15  2003/09/24 11:42:47  tilda
 *  Minor improvements to writer.
 *
 *  Revision 1.14  2003/09/24 10:50:47  tilda
 *  IID485267 - Remove assumption about non-blocking writer streams.
 *
 *  Revision 1.13  2003/09/13 10:18:35  tilda
 *  Initial implementation change and provision of new write interface.
 *
 *  Revision 1.12  2002/11/03 18:43:16  tilda
 *  IID619851 - Update and check headers and function prototypes.
 *
 *  Revision 1.11  2002/11/02 08:56:17  tilda
 *  Start of internationalisation changes.
 *
 *  Revision 1.10  2002/10/26 16:09:23  tilda
 *  IID629125 - Ensure string functions used are portable.
 *
 *  Revision 1.9  2002/10/08 21:45:07  tilda
 *  IID620473 - reduce c-runtime dependencies.
 *
 *  Revision 1.8  2002/10/08 21:11:35  tilda
 *  Remove common.h.
 *
 *  Revision 1.7  2002/02/24 17:10:34  tilda
 *  Add API for "is modified" functionality.
 *
 *  Revision 1.6  2001/12/13 06:45:35  tilda
 *  IID488021 - Various bugs with quoted printable format.
 *
 *  Revision 1.5  2001/11/18 21:45:10  tilda
 *  Add newline after BASE64 encodings
 *
 *  Revision 1.4  2001/11/14 22:36:55  tilda
 *  Add parameter to vf_find_prop_qual_index()
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
 *******************************************************************************/

#ifndef NORCSID
static const char vf_writer_c_vss_id[] = "$Header: /cvsroot/vformat/src/vformat/src/vf_writer.c,v 1.18 2005/08/02 15:13:04 tilda Exp $";
#endif

/*=============================================================================*
 ANSI C & System-wide Header Files
 *=============================================================================*/

#include <common/types.h>

#include <ctype.h>
#include <string.h>

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
#include "vf_strings.h"

/*============================================================================*
 Public Data
 *============================================================================*/
/* None */

/*============================================================================*
 Private Defines
 *============================================================================*/

#if !defined(VFQPMAXPERLINE)
#define VFQPMAXPERLINE              (76)
#endif

#if !defined(VFBASE64MAXPERLINE)
#define VFBASE64MAXPERLINE          (64)
#endif

#define VW_WRITE_BEGIN              ((vw_state_t)0)
#define VW_WRITE_NAME               ((vw_state_t)1)
#define VW_WRITE_VALUE              ((vw_state_t)2)
#define VW_WRITE_END                ((vw_state_t)3)
#define VW_WRITE_DONE               ((vw_state_t)4)

/*============================================================================*
 Private Data Types
 *============================================================================*/

typedef uint8_t vw_state_t;         /* State variable */

typedef struct VWRITER_STACK_T
{
    VOBJECT_T *p_vobject;           /* The object we're currently writing */
    VPROP_T *p_prop;                /* The current property being written */
    uint32_t index;                 /* Index into string arrays we're writing at */
    vw_state_t vw_state;            /* State variable for the property writer */
    struct VWRITER_STACK_T *p_prev; /* Previous nested entry */
}
VWRITER_STACK_T;

typedef struct VWRITER_T
{
    vf_write_flags_t flags;         /* Flags controlling operation */
    char *p_saved_text;             /* Formatted but not yet written to buffer */
    uint16_t saved_posn;            /* Position in buffered text */
    uint16_t saved_length;          /* Length of saved text */
    VOBJECT_T *p_top_vobject;       /* The object we started writing */
    VWRITER_STACK_T *p_stack;       /* Stack of possibly nested state machines */
    uint16_t charsonline;           /* Number of characters since last newline */
}
VWRITER_T;

/*============================================================================*
 Private Function Prototypes
 *============================================================================*/

static bool_t get_text_from_vobject(
    VWRITER_T *p_writer             /* The writer encapsulation */
    );

static void deallocate_writer(
    VWRITER_T *p_writer             /* The writer encapsulation */
    );

static bool_t push_text_to_store(
    VWRITER_T *p_vwriter,           /* The writer encapsulation */
    const char *p_text              /* The text we're saving */
    );

static bool_t write_name_fields(
    VWRITER_T *p_vwriter            /* The writer encapsulation */
    );

static bool_t write_value_fields(
    VWRITER_T *p_vwriter            /* The writer encapsulation */
    );

static bool_t write_quoted_printable(
    VWRITER_T *p_vwriter,           /* The writer encapsulation */
    uint32_t n_string               /* Which value string to write */
    );

static bool_t qp_needs_quoting(
    uint8_t c                       /* Char to test */
    );

static void at_end_of_property(
    VWRITER_T *p_vwriter            /* The writer encapsulation */
    );

static void at_end_of_object(
    VWRITER_T *p_vwriter            /* The writer encapsulation */
    );

static bool_t write_base64_chars(
    VWRITER_T *p_vwriter            /* File we're writing */
    );

static char char_to_base64(
    uint8_t b                       /* Byte to convert */
    );

static void char_to_hexadecimal(
    char *buffer,                   /* Ooutput buffer */
    char c                          /* Char value to convert */
    );

static char nibble_to_hexadecimal(
    int c                           /* Nibble value to convert */
    );

/*============================================================================*
 Private Data
 *============================================================================*/

static const char sz_crnl[3] = { 0x0D, 0x0A, 0x00 };

/*============================================================================*
 Public Function Implementations
 *============================================================================*/

/*----------------------------------------------------------------------------*
 * NAME
 *      vf_write_init()
 * 
 * DESCRIPTION
 *      Allocate and initialise a writer.  To write a VCARD (or any vObject)
 *      a user associates a writer with the object and requests chunks of
 *      text from the writer until the entire object has been converted.
 *
 *      Various flags are available to influence which parts of the object
 *      are streamed.  It is up to the caller to provide buffer space for
 *      the conversion (see vf_write_to_buf()).  Usually the process looks
 *      like this:
 *
 *          VF_WRITER_T *p_writer;
 *
 *          if (vf_write_init(&p_writer, p_object, flags))
 *          {
 *              do
 *              {
 *                  char buffer[...];
 *                  uint16_t charsread;
 *              
 *                  if (vf_write_to_buf(p_writer, buffer, sizeof(buffer), &charsread) &&
 *                          (charsread > 0))
 *                  {
 *                      dispose_of_chars_somewhere(...);
 *                  }
 *              }
 *              while (ret && (0 < charsread))
 *                  ;
 *
 *              vf_write_end(p_writer);
 *          }
 *
 *      A writer allocated by vf_write_init(), must be deallocated by calling
 *      vf_write_end() whether or not writing succeeds. Writing will be complete
 *      on return from vf_write_to_buf() when charsread is zero.  A return of
 *      FALSE from vf_write_to_buf() indicates memory allocation failure.
 *
 * RETURNS
 *      TRUE iff writer allocated successfully.
 *----------------------------------------------------------------------------*/

bool_t vf_write_init(
    VF_WRITER_T **pp_writer,        /* Ptr to where to allocate writer object */
    VF_OBJECT_T *p_object,          /* The object to write */
    vf_write_flags_t flags          /* Flags controlling operation */
    )
{
    bool_t ret = FALSE;

    if (pp_writer && p_object)
    {
        VWRITER_T *p_vwriter = (VWRITER_T *)vf_malloc(sizeof(VWRITER_T));

        if (p_vwriter)
        {
            memset(p_vwriter, '\0', sizeof(VWRITER_T));
            p_vwriter->p_stack = (VWRITER_STACK_T *)vf_malloc(sizeof(VWRITER_STACK_T));

            if (p_vwriter->p_stack)
            {
                /* Clear the objects */
                memset(p_vwriter->p_stack, '\0', sizeof(VWRITER_STACK_T));

                /* Store user's flags & the object we're writing */
                p_vwriter->flags = flags;
                p_vwriter->p_top_vobject = (VOBJECT_T *)p_object;

                /* Initialise with flattening the object */
                p_vwriter->p_stack->p_vobject = (VOBJECT_T *)p_object;
                p_vwriter->p_stack->p_prop = p_vwriter->p_stack->p_vobject->p_props;
                p_vwriter->p_stack->vw_state = VW_WRITE_BEGIN;

                /* Pass back handle to writer object */
                *pp_writer = (VF_WRITER_T *)p_vwriter;

                ret = TRUE;
            }
            else
            {
                vf_free(p_vwriter);
            }
        }
    }

    return ret;
}

/*----------------------------------------------------------------------------*
 * NAME
 *      vf_write_to_buf()
 * 
 * DESCRIPTION
 *      Fetch chunk of textual format of object into indicated buffer.  See
 *      description under vf_write_init().
 *
 * RETURNS
 *      TRUE <=> written OK, FALSE else.  Consult the *p_byteswritten value
 *      to determine if the conversion operation has finished.
 *----------------------------------------------------------------------------*/

bool_t vf_write_to_buf(
    VF_WRITER_T *p_writer,          /* The writer we're asking to write */
    char *p_buffer,                 /* Buffer to write to */
    uint16_t bufsize,               /* Size of buffer */
    uint16_t *p_byteswritten        /* Ptr to return count via */
    )
{
    VWRITER_T *p_vwriter = (VWRITER_T *)p_writer;
    bool_t ret = FALSE;

    if (p_vwriter && p_buffer && bufsize && p_byteswritten)
    {
        ret = TRUE;

        *p_byteswritten = '\0';

        do
        {
            /*
             * If we have any text left over after the last
             * iteration, copy this into the buffer first.
             */
            if (p_vwriter->p_saved_text)
            {
                uint16_t remlen = strlen(p_vwriter->p_saved_text + p_vwriter->saved_posn);

                uint16_t bytestocopy = (remlen < bufsize) ? remlen : bufsize;

                memcpy(p_buffer, p_vwriter->p_saved_text + p_vwriter->saved_posn, bytestocopy);
            
                p_vwriter->saved_posn += bytestocopy;

                bufsize -= bytestocopy;
                p_buffer += bytestocopy;

                *p_byteswritten += bytestocopy;

                if ('\0' == p_vwriter->p_saved_text[p_vwriter->saved_posn])
                {
                    vf_free(p_vwriter->p_saved_text);
                    p_vwriter->p_saved_text = NULL;

                    p_vwriter->saved_posn = 0;
                }
            }

            /*
             * If there's space left in the buffer and we've emptied our store
             * of text cached from last time then generate some more text.
             */
            if ((0 < bufsize) && !p_vwriter->p_saved_text && p_vwriter->p_stack)
            {
                ret = get_text_from_vobject(p_vwriter);
            }
        }
        while (ret && (0 < bufsize) && p_vwriter->p_saved_text && p_vwriter->p_stack)
            ;

        if (!ret)
        {
            deallocate_writer(p_vwriter);
        }
    }

    return ret;
}

/*----------------------------------------------------------------------------*
 * NAME
 *      vf_write_end()
 * 
 * DESCRIPTION
 *      Deallocate a vobject writer.
 *
 * RETURNS
 *      (none)
 *----------------------------------------------------------------------------*/

void vf_write_end(
    VF_WRITER_T *p_writer           /* The writer we're finished with */
    )
{
    VWRITER_T *p_vwriter = (VWRITER_T *)p_writer;

    if (p_writer)
    {
        deallocate_writer(p_vwriter);
    }
}

/*============================================================================*
 Private Function Implementations
 *============================================================================*/

/*----------------------------------------------------------------------------*
 * NAME
 *      get_text_from_vobject()
 * 
 * DESCRIPTION
 *      Fetch more text from the indicated vobject.
 *
 * RETURNS
 *      TRUE iff memory allocation OK, FALSE else.
 *----------------------------------------------------------------------------*/

bool_t get_text_from_vobject(
    VWRITER_T *p_vwriter            /* The writer encapsulation */
    )
{
    bool_t ret = TRUE;

    switch (p_vwriter->p_stack->vw_state)
    {
    case VW_WRITE_BEGIN:
        {
            ret &= push_text_to_store(p_vwriter, VFP_BEGIN);
            ret &= push_text_to_store(p_vwriter, ":");
            ret &= push_text_to_store(p_vwriter, p_vwriter->p_stack->p_vobject->p_type);
            ret &= push_text_to_store(p_vwriter, sz_crnl);

            p_vwriter->p_stack->vw_state = VW_WRITE_NAME;
            p_vwriter->p_stack->index = 0;
        }
        break;

    case VW_WRITE_NAME:
        {
            if (!p_vwriter->p_stack->p_prop)
            {
                p_vwriter->p_stack->vw_state = VW_WRITE_END;
            }
            else
            if (VF_ENC_VOBJECT == p_vwriter->p_stack->p_prop->value.encoding)
            {
                p_vwriter->p_stack->vw_state = VW_WRITE_VALUE;

                ret &= write_value_fields(p_vwriter);
            }
            else
            {
                ret &= write_name_fields(p_vwriter);
            }
        }
        break;

    case VW_WRITE_VALUE:
        {
            ret &= write_value_fields(p_vwriter);
        }
        break;

    case VW_WRITE_END:
        {
            ret &= push_text_to_store(p_vwriter, VFP_END);
            ret &= push_text_to_store(p_vwriter, ":");
            ret &= push_text_to_store(p_vwriter, p_vwriter->p_stack->p_vobject->p_type);
            ret &= push_text_to_store(p_vwriter, sz_crnl);

            p_vwriter->p_stack->vw_state = VW_WRITE_DONE;
        }
        break;

    case VW_WRITE_DONE:
        {
            /* Complete */

            at_end_of_object(p_vwriter);
        }
        break;

    default:
        {
            ret = FALSE;
        }
        break;
    }

    return ret;
}

/*----------------------------------------------------------------------------*
 * NAME
 *      write_name_fields()
 * 
 * DESCRIPTION
 *      Write name fields to file.
 *
 * RETURNS
 *      TRUE <=> OK so far.
 *----------------------------------------------------------------------------*/

bool_t write_name_fields(
    VWRITER_T *p_vwriter
    )
{
    VSTRARRAY_T *p_strarray = &(p_vwriter->p_stack->p_prop->name);
    bool_t ret = TRUE;

    if (0 == p_vwriter->p_stack->index)
    {
        if (p_vwriter->p_stack->p_prop->p_group)
        {
            ret &= push_text_to_store(p_vwriter, p_vwriter->p_stack->p_prop->p_group);
            ret &= push_text_to_store(p_vwriter, ".");
        }
    }

    if (ret && p_strarray->pp_strings)
    {
        if (p_vwriter->p_stack->index < p_strarray->n_strings)
        {
            char *p_name_field = p_strarray->pp_strings[p_vwriter->p_stack->index];

            if (0 < p_vwriter->p_stack->index)
            {
                ret &= push_text_to_store(p_vwriter, ";");
            }
            if (p_name_field && (0 < p_strlen(p_name_field)))
            {
                ret &= push_text_to_store(p_vwriter, p_name_field);
            }

            p_vwriter->p_stack->index += 1;
        }
        else
        {
            p_vwriter->p_stack->index = 0;

            ret &= push_text_to_store(p_vwriter, ":");

            p_vwriter->p_stack->vw_state = VW_WRITE_VALUE;
        }
    }

    return ret;
}

/*----------------------------------------------------------------------------*
 * NAME
 *      write_value_fields()
 * 
 * DESCRIPTION
 *      Continue writing the value parts of the current property.
 *
 *      TODO: don't send all value fields in one go - send them one at
 *      a time.  Again, this will reduce memory requirements.
 *
 * RETURNS
 *      TRUE iff memory allocation OK, FALSE else.
 *----------------------------------------------------------------------------*/

bool_t write_value_fields(
    VWRITER_T *p_vwriter            /* The writer encapsulation */
    )
{
    bool_t ret = TRUE;

    switch (p_vwriter->p_stack->p_prop->value.encoding)
    {
    case VF_ENC_VOBJECT:
        {
            VWRITER_STACK_T *p_new = (VWRITER_STACK_T *)vf_malloc(sizeof(VWRITER_STACK_T));

            if (p_new)
            {
                memset(p_new, '\0', sizeof(VWRITER_STACK_T));

                p_new->p_vobject = p_vwriter->p_stack->p_prop->value.v.o.p_object;
                p_new->p_prop = p_new->p_vobject->p_props;
                p_new->vw_state = VW_WRITE_BEGIN;
                p_new->p_prev = p_vwriter->p_stack;

                p_vwriter->p_stack = p_new;
            }
            else
            {
                ret = FALSE;
            }
        }
        break;

    case VF_ENC_7BIT:
        {
            uint32_t n;

            for (n = 0;ret && (n < p_vwriter->p_stack->p_prop->value.v.s.n_strings);n++)
            {
                if (n)
                    ret &= push_text_to_store(p_vwriter, ";");

                if (p_vwriter->p_stack->p_prop->value.v.s.pp_strings[n])
                {
                    ret &= push_text_to_store(p_vwriter, p_vwriter->p_stack->p_prop->value.v.s.pp_strings[n]);
                }
            }

            ret &= push_text_to_store(p_vwriter, sz_crnl);

            at_end_of_property(p_vwriter);
        }
        break;

    case VF_ENC_QUOTEDPRINTABLE:
        {
            uint32_t n;

            for (n = 0;ret && (n < p_vwriter->p_stack->p_prop->value.v.s.n_strings);n++)
            {
                if (n)
                    ret &= push_text_to_store(p_vwriter, ";");

                if (p_vwriter->p_stack->p_prop->value.v.s.pp_strings[n])
                {
                    ret &= write_quoted_printable(p_vwriter, n);
                }                    
            }

            ret &= push_text_to_store(p_vwriter, sz_crnl);

            at_end_of_property(p_vwriter);
        }
        break;

    case VF_ENC_8BIT:
        {
            ret = FALSE;
        }
        break;

    case VF_ENC_BASE64:
        {
            ret &= write_base64_chars(p_vwriter);

            ret &= push_text_to_store(p_vwriter, sz_crnl);

            at_end_of_property(p_vwriter);
        }
        break;

    default:
        {
            ret = FALSE;
        }
        break;
    }

    return ret;
}

/*----------------------------------------------------------------------------*
 * NAME
 *      at_end_of_property()
 * 
 * DESCRIPTION
 *      Called when finished writing a property.  Checks to see if there's
 *      another property and if not moves the writer into the "write end"
 *      state to close the object.
 *
 * RETURNS
 *      (none)
 *----------------------------------------------------------------------------*/

void at_end_of_property(
    VWRITER_T *p_vwriter            /* The writer encapsulation */
    )
{
    if (p_vwriter->p_stack->p_prop->p_next)
    {
        p_vwriter->p_stack->p_prop = p_vwriter->p_stack->p_prop->p_next;
        p_vwriter->p_stack->vw_state = VW_WRITE_NAME;
    }
    else
    {
        p_vwriter->p_stack->vw_state = VW_WRITE_END;
    }
}

/*----------------------------------------------------------------------------*
 * NAME
 *      at_end_of_object()
 * 
 * DESCRIPTION
 *      Called when finished writing a n object.  Checks to see if there's
 *      another object and if not pops the current obejct off the stack to
 *      return from a "recursive" operation.
 *
 * RETURNS
 *      (none)
 *----------------------------------------------------------------------------*/

void at_end_of_object(
    VWRITER_T *p_vwriter            /* The writer encapsulation */
    )
{
    p_vwriter->p_stack->p_vobject = p_vwriter->p_stack->p_vobject->p_next;

    if (p_vwriter->p_stack->p_vobject)
    {
        /* Next object in list of objects */

        p_vwriter->p_stack->p_prop = p_vwriter->p_stack->p_vobject->p_props;
        p_vwriter->p_stack->vw_state = VW_WRITE_BEGIN;
    }
    else
    {
        /* Reached end of list of objects => return from recursion */

        VWRITER_STACK_T *p_prev = p_vwriter->p_stack->p_prev;

        vf_free(p_vwriter->p_stack);
        p_vwriter->p_stack = p_prev;

        if (p_vwriter->p_stack)
        {
            at_end_of_property(p_vwriter);            
        }
    }
}

/*----------------------------------------------------------------------------*
 * NAME
 *      write_quoted_printable()
 * 
 * DESCRIPTION
 *      Write the indicated field back to the file in quoted printable format.
 *
 *      TODO: don't send all value fields in one go - send them one at
 *      a time.  Again, this will reduce memory requirements.
 *
 * RETURNS
 *      TRUE iff memory allocation succeeds, FALSE else.
 *----------------------------------------------------------------------------*/

static bool_t write_quoted_printable(
    VWRITER_T *p_vwriter,           /* The writer encapsulation */
    uint32_t n_string               /* Which value string to write */
    )
{
    uint32_t i;
    bool_t ret;

    char *s = p_vwriter->p_stack->p_prop->value.v.s.pp_strings[n_string];

    for (i = 0, ret = TRUE;ret && s;i++)
    {
        uint8_t c = s[i];

        if ('\0' == c)
        {
            break;
        }
        else
        {
            if (3 + p_vwriter->charsonline > VFQPMAXPERLINE)
            {
                push_text_to_store(p_vwriter, "=");
                push_text_to_store(p_vwriter, sz_crnl);
            }

            if (qp_needs_quoting(c))
            {
                char buffer[5];
                
                char_to_hexadecimal(buffer, c);

                push_text_to_store(p_vwriter, "=");
                push_text_to_store(p_vwriter, buffer);

                if (0x0D == c)
                {
                    push_text_to_store(p_vwriter, "=");
                    push_text_to_store(p_vwriter, sz_crnl);
                }
            }
            else
            {
                char buffer[2];
                buffer[0] = c;
                buffer[1] = '\0';

                ret &= push_text_to_store(p_vwriter, buffer);
            }
        }
    }

    return ret;
}

/*----------------------------------------------------------------------------*
 * NAME
 *      char_to_hexadecimal()
 * 
 * DESCRIPTION
 *      Convert indicated character value to two digit hex string.
 *
 * RETURNS
 *      (none)
 *----------------------------------------------------------------------------*/

void char_to_hexadecimal(
    char *buffer,                   /* Ooutput buffer */
    char c                          /* Char value to convert */
    )
{
    buffer[0] = nibble_to_hexadecimal((c & 0xF0) >> 4);
    buffer[1] = nibble_to_hexadecimal((c & 0x0F) >> 0);
    buffer[2] = '\0';
}

/*----------------------------------------------------------------------------*
 * NAME
 *      nibble_to_hexadecimal()
 * 
 * DESCRIPTION
 *      Convert indicated nibble value to hex character.
 *
 * RETURNS
 *      A hex character.
 *----------------------------------------------------------------------------*/

char nibble_to_hexadecimal(
    int c                           /* Nibble value to convert */
    )
{
    if ((0 <= c) && (c <= 9))
        return (char)('0' + c);

    if ((0x0A <= c) && (c <= 0x0F))
        return (char)('A' + (c - 0x0A));

    return '?';
}

/*----------------------------------------------------------------------------*
 * NAME
 *      qp_needs_quoting()
 * 
 * DESCRIPTION
 *      Works out of 'c' needs quoting in quoted printable format.
 *
 * RETURNS
 *      TRUE <=> need to quote.
 *----------------------------------------------------------------------------*/

static bool_t qp_needs_quoting(
    uint8_t c               /* Char to test */
    )
{
    /* TBD - look in the RFC?! */

    bool_t needs_quoting = FALSE;

    switch (c)
    {
    case ' ':
    case ',':
    case '-':
    case '.':
    case '!':
    case '?':
    case '\'':
        return FALSE;

    default:
        if (isalnum(c))
            needs_quoting = FALSE;
        else
            needs_quoting = TRUE;
        break;
    }

    return needs_quoting;
}

/*----------------------------------------------------------------------------*
 * NAME
 *      write_base64_chars()
 * 
 * DESCRIPTION
 *      Write the indicated binary data stream out to FILE* using BASE64
 *      encoding.
 *
 * RETURNS
 *      TRUE iff memory allocation succeeds, FALSE else.
 *----------------------------------------------------------------------------*/

static bool_t write_base64_chars(
    VWRITER_T *p_vwriter                /* File we're writing */
    )
{
    bool_t ret = TRUE;

    uint8_t *p_buffer = (uint8_t *)p_vwriter->p_stack->p_prop->value.v.b.p_buffer;
    uint32_t n_chars = p_vwriter->p_stack->p_prop->value.v.b.n_bufsize;

    uint32_t posn;
    char quad[5];
    uint8_t b;

    quad[4] = 0;

    for (posn = 0;ret && (posn < n_chars);)
    {
        int i;
        uint32_t triplet = 0;
        uint8_t bits = 0;

        /* Form triplet from data if available */

        for (i = 0;i < 3;i++, posn++)
        {
            triplet = triplet << 8;

            if (posn < n_chars)
            {
                triplet |= *(p_buffer + posn);

                bits += 8;
            }
        }

        /* Convert the triplet to text */

        for (i = 0;i < 4;i++)
        {
            b = (uint8_t)((0xFC0000 & triplet) >> 18);

            triplet = triplet << 6;

            quad[i] = (char)((i <= (bits/6)) ? char_to_base64(b) : '=');
        }

        /* Output the text prefixed by newlines if necessary */

        if (((posn - 3) % (VFBASE64MAXPERLINE / 4)) == 0)
        {
            ret &= push_text_to_store(p_vwriter, sz_crnl);
            ret &= push_text_to_store(p_vwriter, "    ");
        }

        ret &= push_text_to_store(p_vwriter, quad);
    }

    return ret;
}

/*----------------------------------------------------------------------------*
 * NAME
 *      char_to_base64()
 * 
 * DESCRIPTION
 *      Converts byte to BASE64.
 *
 * RETURNS
 *      Character encoded.
 *----------------------------------------------------------------------------*/

static char char_to_base64(
    uint8_t b       /* Byte to convert */
    )
{
    char ret;

    if (b < 26)
    {
        ret = (char)(b + 'A');
    }
    else
    if (b < 52)
    {
        ret = (char)((b - 26) + 'a');
    }
    else
    if (b < 62)
    {
        ret = (char)((b - 52) + '0');
    }
    else
    if (b == 62)
    {
        ret = '+';
    }
    else
    {
        ret = '/';
    }

    return ret;
}

/*----------------------------------------------------------------------------*
 * NAME
 *      push_text_to_store()
 * 
 * DESCRIPTION
 *      Append indicated string to the cache of text currently waiting.
 *
 *      If the CR/NL string is appended, we reset the lenght of line
 *      counter used by the various encoders to ensure line length
 *      is kept within spec.
 *
 * RETURNS
 *      TRUE iff memory allocation succeeds, FALSE else.
 *----------------------------------------------------------------------------*/

bool_t push_text_to_store(
    VWRITER_T *p_vwriter,           /* The writer encapsulation */
    const char *p_text              /* The text we're saving */
    )
{
    uint32_t currlen, newlen;
    char *p_tmp;
    bool_t ret = TRUE;

    currlen = p_vwriter->p_saved_text ? strlen(p_vwriter->p_saved_text) : 0;
    newlen = strlen(p_text);

    p_tmp = (char *)vf_realloc(p_vwriter->p_saved_text, currlen + newlen + 1L);
    if (p_tmp)
    {
        p_tmp[currlen] = '\0';

        p_vwriter->p_saved_text = p_tmp;

        strcat(p_vwriter->p_saved_text, p_text);

        if (p_text == sz_crnl)
        {
            p_vwriter->charsonline = 0;
        }
        else
        {
            p_vwriter->charsonline += (uint16_t)newlen;
        }
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}

/*----------------------------------------------------------------------------*
 * NAME
 *      deallocate_writer()
 * 
 * DESCRIPTION
 *      Frees all memory associated with the indicated VWRITER object.
 *
 * RETURNS
 *      (none)
 *----------------------------------------------------------------------------*/

void deallocate_writer(
    VWRITER_T *p_vwriter             /* The writer we're finished with */
    )
{
    if (p_vwriter->p_saved_text)
    {
        vf_free(p_vwriter->p_saved_text);
        p_vwriter->p_saved_text = NULL;
    }

    while (p_vwriter->p_stack)
    {
        VWRITER_STACK_T *p_prev = p_vwriter->p_stack->p_prev;

        vf_free(p_vwriter->p_stack);

        p_vwriter->p_stack = p_prev;
    }

    vf_free(p_vwriter);
}

/*============================================================================*
 End Of File
 *============================================================================*/
