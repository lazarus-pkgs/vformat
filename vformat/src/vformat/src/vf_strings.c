/******************************************************************************

    (C) Nick Marley, 2001 -

    This software is distributed under the GNU Lesser General Public Licence.
    Please read and understand the comments at the top of vf_iface.h before use!

FILE
    $Workfile$
    $Revision: 1.12 $
    $Author: tilda $
         
ORIGINAL AUTHOR
    Nick Marley

DESCRIPTION
    String handling functions.  The library uses the p_ functions (where hopefully
    the 'p' stands for 'portable') and they are provided here in terms of C runtime
    functions or implemented explicitly.

REFERENCES
    (none)    

MODIFICATION HISTORY
 *  $Log: vf_strings.c,v $
 *  Revision 1.12  2005/07/30 08:32:04  tilda
 *  Compiler warnings.  p_strncat() for unreferenced buffer sizes.
 *
 *  Revision 1.11  2005/07/29 22:05:06  tilda
 *  Various compiler warnings.  Whitespace donated to charity.
 *
 *  Revision 1.10  2003/09/24 18:18:21  tilda
 *  XAP portability issues - compiler warnings etc.
 *
 *  Revision 1.9  2002/11/15 09:15:00  tilda
 *  IID638823 - Various portability issues.
 *
 *  Revision 1.8  2002/10/26 16:09:23  tilda
 *  IID629125 - Ensure string functions used are portable.
 *
 *  Revision 1.7  2002/10/08 21:45:07  tilda
 *  IID620473 - reduce c-runtime dependencies.
 *
 *  Revision 1.6  2002/10/08 21:11:36  tilda
 *  Remove common.h.
 *
 *  Revision 1.5  2001/11/05 21:07:19  tilda
 *  Various changes for initial version of vfedit.
 *
 *  Revision 1.4  2001/10/14 20:42:37  tilda
 *  Addition of group searching.
 *
 *  Revision 1.3  2001/10/13 16:22:08  tilda
 *  Introduce VBINDATA_T and VOBJDATA_T to tidy up internals.
 *
 *  Revision 1.2  2001/10/13 14:58:56  tilda
 *  Tidy up version headers, add vf_strings.h where needed.
 *
 *  Revision 1.1  2001/10/13 14:50:33  tilda
 *  Add string array code to unify handling of names / values.
 * 
 *******************************************************************************/

#ifndef NORCSID
static const char vf_strings_c_vss_id[] = "$Header: /cvsroot/vformat/src/vformat/src/vf_strings.c,v 1.12 2005/07/30 08:32:04 tilda Exp $";
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

#include "vformat/vf_iface.h"

/*============================================================================*
 Local Header File
 *============================================================================*/

#include "vf_config.h"
#include "vf_internals.h"
#include "vf_strings.h"

/*============================================================================*
 Public Data
 *============================================================================*/
/* None */

/*============================================================================*
 Private Defines
 *============================================================================*/
/* None */

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
/* None */

/*============================================================================*
 Public Function Implementations
 *============================================================================*/

/*----------------------------------------------------------------------------*
 * NAME
 *      p_strlen()
 * 
 * DESCRIPTION
 *      Find length of string.
 *
 * RETURNS
 *      Length of strings.
 *----------------------------------------------------------------------------*/

int p_strlen(
    const char *p_string                /* String to measure */
    )
{
#if defined(HAVE_STRLEN)
    return strlen(p_string);
#else
    int len = 0;
    
    while (*p_string)
    {
        p_string++;
        len++;
    }

    return len;
#endif
}

/*----------------------------------------------------------------------------*
 * NAME
 *      p_strcpy()
 * 
 * DESCRIPTION
 *      Copy string to buffer.
 *
 * RETURNS
 *      Pointer to buffer.
 *----------------------------------------------------------------------------*/

char *p_strcpy(
    char *p_string1,                /* Buffer to copy to */
    const char *p_string2           /* String to copy */
    )
{
#if defined(HAVE_STRCPY)
    return strcpy(p_string1, p_string2);
#else
  char *p_return = p_string1;

  while ('\0' != ((*p_string1++ = *p_string2++)))
    ;

  return p_return;
#endif
}

/*----------------------------------------------------------------------------*
 * NAME
 *      p_strcmp()
 * 
 * DESCRIPTION
 *      Case sensitive string comparison.
 *
 * RETURNS
 *      0<=>strings match, !=0 else.
 *----------------------------------------------------------------------------*/

int p_strcmp(
    const char *p_string1,
    const char *p_string2
    )
{
#if defined(HAVE_STRCMP)
    return strcmp(p_string1, p_string2);
#else
    while (*p_string1 && (*p_string1 == *p_string2))
    {
        p_string1++;
        p_string2++;
    }

    return (*(unsigned char *)p_string1) - (*(unsigned char *)p_string2);    
#endif
}

/*----------------------------------------------------------------------------*
 * NAME
 *      p_strcat()
 * 
 * DESCRIPTION
 *      Append one string to another.
 *
 * RETURNS
 *      Pointer to resulting string.
 *----------------------------------------------------------------------------*/

char *p_strcat(
    char *p_string1,                            /* String to append to */
    const char *p_string2                       /* String to append */
    )
{
#if defined(HAVE_STRCAT)
    return strcat(p_string1, p_string2);
#else
    char *p_return = p_string1;

    while (*p_string1)
        p_string1++;

    while ('\0' != ((*p_string1++ = *p_string2++)))
        ;

    return p_return;
#endif
}

/*----------------------------------------------------------------------------*
 * NAME
 *      p_strstr()
 * 
 * DESCRIPTION
 *      Case sensitive string searching function.
 *
 * RETURNS
 *      Pointer to position "looked for" has been located or NULL if !found.
 *----------------------------------------------------------------------------*/

char *p_strstr(
    const char *p_searched,                     /* Buffer searched */
    const char *p_lookedfor                     /* String we're looking for */
    )
{
#if defined(HAVE_STRSTR)
    return strstr(p_searched, p_lookedfor);
#else
    if (*p_searched == 0)
    {
        if (*p_lookedfor)
        {
            return (char *)NULL;
        }

        return (char *)p_searched;
    }

    while (*p_searched)
    {
        uint32_t i;

        for (i = 0;;i++)
        {
            if (p_lookedfor[i] == 0)
            {
                return (char *)p_searched;
            }

            if (p_lookedfor[i] != p_searched[i])
            {
                break;
            }
        }

        p_searched++;
    }

    return (char *)NULL;
#endif
}

/*----------------------------------------------------------------------------*
 * NAME
 *      p_stricmp()
 * 
 * DESCRIPTION
 *      Case insensitive string comparison function.
 *
 * RETURNS
 *      0<=>strings match, !=0 else.
 *----------------------------------------------------------------------------*/

#if !defined(XAP) && !defined(__XAP__)

int p_stricmp(
    const char *p_string1,                      /* First string */
    const char *p_string2                       /* Second string */
    )
{
#if defined(HAVE_STRCASECMP)
    return strcasecmp(p_string1, p_string2);
#elif defined(HAVE_STRICMP)
    return stricmp(p_string1, p_string2);
#else
    while (*p_string1 && (tolower(*p_string1) == tolower(*p_string2)))
    {
        p_string1++;
        p_string2++;
    }

    return tolower(*(unsigned char *)p_string1) - tolower(*(unsigned char *)p_string2);
#endif
}

#endif

/*----------------------------------------------------------------------------*
 * NAME
 *      p_stristr()
 * 
 * DESCRIPTION
 *      Case insensitive string searching function.
 *
 * RETURNS
 *      Pointer to position "looked for" has been located or NULL if !found.
 *----------------------------------------------------------------------------*/

char *p_stristr(
    const char *p_searched,                     /* Buffer searched */
    const char *p_lookedfor                     /* String we're looking for */
    )
{
#if defined(HAVE_STRISTR)
    return strstr(p_searched, p_lookedfor);
#else
    if (*p_searched == 0)
    {
        if (*p_lookedfor)
        {
            return (char *)NULL;
        }

        return (char *)p_searched;
    }

    while (*p_searched)
    {
        uint32_t i;

        for (i = 0;;i++)
        {
            if (p_lookedfor[i] == 0)
            {
                return (char *)p_searched;
            }

            if (tolower(p_lookedfor[i]) != tolower(p_searched[i]))
            {
                break;
            }
        }

        p_searched++;
    }

    return (char *)NULL;
#endif
}

/*----------------------------------------------------------------------------*
 * NAME
 *      p_memcpy()
 * 
 * DESCRIPTION
 *      Copy characetrs between buffers.  No checks on overlap.
 *
 * RETURNS
 *      (none)
 *----------------------------------------------------------------------------*/

void p_memcpy(
    void *p_destination,                        /* Pointer to buffer */
    const void *p_source,                       /* Source of copy */
    uint32_t length                             /* Number of characters to copy */
    )
{
#if defined(HAVE_MEMCPY)
    memcpy(p_destination, p_source, length);
#else
    uint8_t *p_dst = (uint8_t *)p_destination;
    uint8_t *p_src = (uint8_t *)p_source;

    while (length--)
    {
        *p_dst++ = *p_src++;
    }
#endif
}

/*----------------------------------------------------------------------------*
 * NAME
 *      p_memset()
 * 
 * DESCRIPTION
 *      Fill buffer with indicated character.
 *
 * RETURNS
 *      (none)
 *----------------------------------------------------------------------------*/

void p_memset(
    void *p_destination,                        /* Pointer to buffer */
    uint8_t v,                                  /* Character to fill with */
    uint32_t length                             /* Length of buffer to set */
    )
{
#if defined(HAVE_MEMSET)
    memset(p_destination, v, length);
#else
    uint8_t *p_dst = (uint8_t *)p_destination;

    while (length--)
        *p_dst++ = v;
#endif
}

/*---------------------------------------------------------------------------*
 * NAME
 *      p_strncat()
 * 
 * DESCRIPTION
 *      Append to a string but only if the buffer holding the string is big
 *      enough to receive the combined text including the null terminator.
 *
 *      For example, in the following code:
 *
 *          char *p, buffer[8];
 *          strcpy(buffer, "Hello");
 *          p = p_strncat(buffer, "Dad", sizeof(buffer));
 *
 *      The value assigned to 'p' will be NULL because the resulting string
 *      'HelloDad' requires a nine byte buffer.
 *
 * RETURNS
 *      The input string if the buffer is big enough, else NULL.
 *---------------------------------------------------------------------------*/

char *p_strncat(
    char *p_out,                                /* Input string */
    const char *p_additional,                   /* Additional text */
    uint32_t bufsize                            /* Size of buffer */
    )
{
    char *p_result;

    if (strlen(p_out) + strlen(p_additional) < bufsize)
    {
        p_strcat(p_out, p_additional);

        p_result = p_out;
    }
    else
    {
        p_result = NULL;
    }
    
    return p_result;
}

/*============================================================================*
 Private Function Implementations
 *============================================================================*/
/* None */

/*============================================================================*
 End Of File
 *============================================================================*/
