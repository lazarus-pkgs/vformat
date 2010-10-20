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
    $Revision: 1.41 $
    $Author: tilda $

ORIGINAL AUTHOR
    Tilda@users.sourceforge.net <Nick Marley>

DESCRIPTION
    Main include file for the vFormat object library.

REFERENCES
    (none)

MODIFICATION HISTORY
 *  $Log: vf_iface.h,v $
 *  Revision 1.41  2010/10/11 19:51:52  tilda
 *  Applied patch ID 3084926 : requred -> required.
 *
 *  Revision 1.40  2005/07/30 14:01:18  tilda
 *  Various header file tidy-ups.
 *
 *  Revision 1.39  2005/07/30 13:50:35  tilda
 *  Fix compiler warnings by implementing function.
 *
 *  Revision 1.38  2005/07/30 08:32:04  tilda
 *  Compiler warnings.  p_strncat() for unreferenced buffer sizes.
 *
 *  Revision 1.37  2005/07/29 22:05:06  tilda
 *  Various compiler warnings.  Whitespace donated to charity.
 *
 *  Revision 1.36  2003/09/24 18:19:01  tilda
 *  XAP portability issues - compiler warnings etc.
 *
 *  Revision 1.35  2003/09/24 10:50:47  tilda
 *  IID485267 - Remove assumption about non-blocking writer streams.
 *
 *  Revision 1.34  2003/09/13 10:54:01  tilda
 *  Include vf_clone_object() contributed by Mark Flerakas.
 *
 *  Revision 1.33  2003/09/13 10:18:35  tilda
 *  Initial implementation change and provision of new write interface.
 *
 *  Revision 1.32  2003/07/14 11:42:23  tilda
 *  Various vCalendar updates from home PC #2.
 *
 *  Revision 1.31  2003/04/10 12:49:16  monos
 *  included type defs in vf_iface.h, started info documentation
 *
 *  Revision 1.30  2002/12/07 17:25:44  monos
 *  *** empty log message ***
 *
 *  Revision 1.29  2002/11/24 14:26:22  tilda
 *  IID484686 - More vcard work.
 *
 *  Revision 1.28  2002/11/17 10:01:02  tilda
 *  IID484686 - Yet more vCalendar stuff.
 *
 *  Revision 1.27  2002/11/16 13:19:10  tilda
 *  IID639288 - Implement method for adding subobjects.
 *
 *  Revision 1.26  2002/11/03 18:43:16  tilda
 *  IID619851 - Update and check headers and function prototypes.
 *
 *  Revision 1.25  2002/11/02 18:29:26  tilda
 *  IID485157 - UI does character conversion based on CHARSET property.
 *
 *  Revision 1.24  2002/11/02 08:56:17  tilda
 *  Start of internationalisation changes.
 *
 *  Revision 1.23  2002/10/08 21:45:07  tilda
 *  IID620473 - reduce c-runtime dependencies.
 *
 *  Revision 1.22  2002/10/08 21:15:56  tilda
 *  IID619851 - Update comments.
 *
 *  Revision 1.21  2002/02/24 17:10:35  tilda
 *  Add API for "is modified" functionality.
 *
 *  Revision 1.20  2002/02/16 19:14:36  tilda
 *  Various mods improving the command line options.
 *
 *  Revision 1.19  2002/01/12 15:55:32  tilda
 *  Add pragmas for linking.
 *
 *  Revision 1.18  2002/01/06 16:18:48  tilda
 *  Add dialog box for events / todos.
 *
 *  Revision 1.17  2001/12/28 17:23:50  tilda
 *  Minor mods to VTODO etc. defines.
 *
 *  Revision 1.16  2001/11/16 22:34:49  tilda
 *  New vf_get_property() allows append as well as find,
 *
 *  Revision 1.15  2001/11/15 08:55:15  tilda
 *  Minor reorganisation & add comments where missing.
 *
 *  Revision 1.14  2001/11/14 22:36:56  tilda
 *  Add parameter to vf_find_prop_qual_index()
 *
 *  Revision 1.13  2001/11/14 16:04:16  tilda
 *  Add VFP_ names.
 *
 *  Revision 1.12  2001/11/12 20:24:54  tilda
 *  Add properties.
 *
 *  Revision 1.11  2001/11/06 22:51:05  tilda
 *  Supporting access functions for image selection / deletion.
 *
 *  Revision 1.10  2001/11/05 21:08:02  tilda
 *  Various changes for initial version of vfedit.
 *
 *  Revision 1.9  2001/10/24 18:36:45  tilda
 *  BASE64 bugfixes.  Split reader/writer code. Start create/modify work.
 *
 *  Revision 1.8  2001/10/24 05:33:16  tilda
 *  Start work on object create/modify API.
 *
 *  Revision 1.7  2001/10/16 05:50:53  tilda
 *  Debug support for lists of vobjects from single file (ie. a phonebook).
 *
 *  Revision 1.6  2001/10/14 20:42:37  tilda
 *  Addition of group searching.
 *
 *  Revision 1.5  2001/10/14 16:40:35  tilda
 *  Initial testing of access functions.
 *
 *  Revision 1.4  2001/10/13 14:58:56  tilda
 *  Tidy up version headers, add vf_strings.h where needed.
 *
 *  Revision 1.3  2001/10/10 20:54:34  tilda
 *  Various minor tidy ups.
 *  
 *  Revision 1.2  2001/10/09 22:01:59  tilda
 *  Remove older version control comments.
 *
 *****************************************************************************/

#ifndef INC_VF_IFACE_H
#define INC_VF_IFACE_H

#ifndef NORCSID
static const char vf_iface_h_vss_id[] = "$Header: /cvsroot/vformat/src/vformat/vf_iface.h,v 1.41 2010/10/11 19:51:52 tilda Exp $";
#endif

/*============================================================================*
 Public Includes
 *============================================================================*/

/* We make heavy use of varargs()... */
#include <stdarg.h>

/* Default .DLL build using the symbols maintained by MSDEV */
#if defined(WIN) || defined(WIN32)
#include "vf_win32libs.h"
#endif

#if !defined(_TYPES_H_)
#include <common/types.h>
#endif

/*============================================================================*
 Public defines
 *============================================================================*/

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * Remove VFORMATDECLSPEC if not defined.
 */
#ifndef VFORMATDECLSPEC
 #define VFORMATDECLSPEC
#endif

/*----------------------------------------------------------------------------*
 * PURPOSE
 *      Definitions of the standard properties.
 *----------------------------------------------------------------------------*/

#define VFP_AALARM              "AALARM"
#define VFP_ADDITIONALNAMES     "ADDN"
#define VFP_ADR                 "ADR"
#define VFP_AGENT               "AGENT"
#define VFP_AIFF                "AIFF"
#define VFP_AOL                 "AOL"
#define VFP_APPLELINK           "APPLELINK"
#define VFP_ATTACH              "ATTACH"
#define VFP_ATTENDEE            "ATTENDEE"
#define VFP_ORGANIZER           "ORGANIZER"
#define VFP_OWNER               "OWNER"
#define VFP_DELEGATE            "DELEGATE"
#define VFP_ACCEPTED            "ACCEPTED"
#define VFP_NEEDSACTION         "NEEDS ACTION"
#define VFP_SENT                "SENT"
#define VFP_TENTATIVE           "TENTATIVE"
#define VFP_CONFIRMED           "CONFIRMED"
#define VFP_DECLINED            "DECLINED"
#define VFP_COMPLETED           "COMPLETED"
#define VFP_DELEGATED           "DELEGATED"
#define VFP_CATERING            "CATERING"
#define VFP_COMPUTERPROJECTOR   "COMPUTER PROJECTOR"
#define VFP_EASEL               "EASEL"
#define VFP_OVERHEADPROJECTOR   "OVERHEAD PROJECTOR"
#define VFP_SPEAKERPHONE        "SPEAKER PHONE"
#define VFP_TABLE               "TABLE"
#define VFP_TV                  "TV"
#define VFP_VCR                 "VCR"
#define VFP_VIDEOPHONE          "VIDEO PHONE"
#define VFP_VEHICLE             "VEHICLE"
#define VFP_ATTMAIL             "ATTMAIL"
#define VFP_AUDIOCONTENT        "AUDIOCONTENT"
#define VFP_AVI                 "AVI"
#define VFP_BBS                 "BBS"
#define VFP_BIRTHDATE           "BDAY"
#define VFP_BMP                 "BMP"
#define VFP_BODY                "BODY"
#define VFP_BUSINESSROLE        "ROLE"
#define VFP_CAPTION             "CAP"
#define VFP_CAR                 "CAR"
#define VFP_CATEGORIES          "CATEGORIES"
#define VFP_CELLULAR            "CELL"
#define VFP_CGM                 "CGM"
#define VFP_CHARSET             "CHARSET"
#define VFP_CID                 "CID"
#define VFP_CIS                 "CIS"
#define VFP_CITY                "L"
#define VFP_CLASS               "CLASS"
#define VFP_COMMENT             "NOTE"
#define VFP_COMPLETED           "COMPLETED"
#define VFP_CONTENTID           "CONTENT-ID"
#define VFP_COUNTRYNAME         "C"
#define VFP_DALARM              "DALARM"
#define VFP_DATASIZE            "DATASIZE"
#define VFP_DAYLIGHT            "DAYLIGHT"
#define VFP_DCREATED            "DCREATED"
#define VFP_DELIVERYLABEL       "LABEL"
#define VFP_DESCRIPTION         "DESCRIPTION"
#define VFP_DIB                 "DIB"
#define VFP_DISPLAYSTRING       "DISPLAYSTRING"
#define VFP_DOMESTIC            "DOM"
#define VFP_DTEND               "DTEND"
#define VFP_DTSTART             "DTSTART"
#define VFP_DUE                 "DUE"
#define VFP_EMAILADDRESS        "EMAIL"
#define VFP_ENCODING            "ENCODING"
#define VFP_EWORLD              "EWORLD"
#define VFP_EXNUM               "EXNUM"
#define VFP_EXPDATE             "EXDATE"
#define VFP_EXPECT              "EXPECT"
#define VFP_EXTADDRESS          "EXT ADD"
#define VFP_FAMILYNAME          "F"
#define VFP_FAX                 "FAX"
#define VFP_FULLNAME            "FN"
#define VFP_GEO                 "GEO"
#define VFP_GEOLOCATION         "GEO"
#define VFP_GIF                 "GIF"
#define VFP_GIVENNAME           "G"
#define VFP_GROUPING            "GROUPING"
#define VFP_HOME                "HOME"
#define VFP_IBMMAIL             "IBMMAIL"
#define VFP_INLINE              "INLINE"
#define VFP_INTERNATIONAL       "INTL"
#define VFP_INTERNET            "INTERNET"
#define VFP_ISDN                "ISDN"
#define VFP_JPEG                "JPEG"
#define VFP_LANGUAGE            "LANG"
#define VFP_LASTMODIFIED        "LAST-MODIFIED"
#define VFP_LASTREVISED         "REV"
#define VFP_LOCATION            "LOCATION"
#define VFP_LOGO                "LOGO"
#define VFP_MAILER              "MAILER"
#define VFP_MALARM              "MALARM"
#define VFP_MCIMAIL             "MCIMAIL"
#define VFP_MESSAGE             "MSG"
#define VFP_MET                 "MET"
#define VFP_MODEM               "MODEM"
#define VFP_MPEG2               "MPEG2"
#define VFP_MPEG                "MPEG"
#define VFP_MSN                 "MSN"
#define VFP_NAMEPREFIXES        "NPRE"
#define VFP_NAME                "N"
#define VFP_NAMESUFFIXES        "NSUF"
#define VFP_NOTE                "NOTE"
#define VFP_ORGNAME             "ORGNAME"
#define VFP_ORG                 "ORG"
#define VFP_ORGUNIT2            "OUN2"
#define VFP_ORGUNIT3            "OUN3"
#define VFP_ORGUNIT4            "OUN4"
#define VFP_ORGUNIT             "OUN"
#define VFP_PAGER               "PAGER"
#define VFP_PALARM              "PALARM"
#define VFP_PARCEL              "PARCEL"
#define VFP_PART                "PART"
#define VFP_PCM                 "PCM"
#define VFP_PDF                 "PDF"
#define VFP_PGP                 "PGP"
#define VFP_PHOTO               "PHOTO"
#define VFP_PROPTYPE            "TYPE"
#define VFP_PICT                "PICT"
#define VFP_PMB                 "PMB"
#define VFP_POSTALBOX           "BOX"
#define VFP_POSTALCODE          "PC"
#define VFP_POSTAL              "POSTAL"
#define VFP_POWERSHARE          "POWERSHARE"
#define VFP_PREFERRED           "PREF"
#define VFP_PRIORITY            "PRIORITY"
#define VFP_PROCEDURENAME       "PROCEDURENAME"
#define VFP_PRODID              "PRODID"
#define VFP_PRODIGY             "PRODIGY"
#define VFP_SOUND               "SOUND"
#define VFP_PS                  "PS"
#define VFP_PUBLICKEY           "KEY"
#define VFP_QP                  "QP"
#define VFP_QUICKTIME           "QTIME"
#define VFP_RDATE               "RDATE"
#define VFP_REGION              "R"
#define VFP_RELATEDTO           "RELATED-TO"
#define VFP_REPEATCOUNT         "REPEATCOUNT"
#define VFP_RESOURCES           "RESOURCES"
#define VFP_RNUM                "RNUM"
#define VFP_ROLE                "ROLE"
#define VFP_RRULE               "RRULE"
#define VFP_RSVP                "RSVP"
#define VFP_RUNTIME             "RUNTIME"
#define VFP_SEQUENCE            "SEQUENCE"
#define VFP_SNOOZETIME          "SNOOZETIME"
#define VFP_START               "START"
#define VFP_STATUS              "STATUS"
#define VFP_STREETADDRESS       "STREET"
#define VFP_SUBTYPE             "SUBTYPE"
#define VFP_SUMMARY             "SUMMARY"
#define VFP_TELEPHONE           "TEL"
#define VFP_TIFF                "TIFF"
#define VFP_TIMEZONE            "TZ"
#define VFP_TITLE               "TITLE"
#define VFP_TLX                 "TLX"
#define VFP_TRANSP              "TRANSP"
#define VFP_UNIQUESTRING        "UID"
#define VFP_URL                 "URL"
#define VFP_URLVALUE            "URLVAL"
#define VFP_VALUE               "VALUE"
#define VFP_VERSION             "VERSION"
#define VFP_VIDEO               "VIDEO"
#define VFP_VOICE               "VOICE"
#define VFP_WAVE                "WAVE"
#define VFP_WMF                 "WMF"
#define VFP_WORK                "WORK"
#define VFP_X400                "X400"
#define VFP_X509                "X509"
#define VFP_XRULE               "XRULE"

#define VFP_UTF8                "UTF-8"

#define VFP_PRONUNCIATION       VFP_SOUND   /* ??? */

/*
 * Property tokesn indicating encoding.
 */
#define VFP_7BIT                "7BIT"
#define VFP_8BIT                "8BIT"
#define VFP_BASE64              "BASE64"
#define VFP_QUOTEDPRINTABLE     "QUOTED-PRINTABLE"

/*
 * Names for the "begin" token.
 */
#define VF_NAME_VCALENDAR       "VCALENDAR"
#define VF_NAME_VCARD           "VCARD"
#define VF_NAME_VNOTE           "VNOTE"
#define VF_NAME_VEVENT          "VEVENT"
#define VF_NAME_VTODO           "VTODO"


/*
 * Special token that matches any when searching.
 */
#define VFP_ANY                 "*"

/*
 * Indexes for compound name properties (the "N" property).
 */
#define VFP_NAME_FAMILY         (0)
#define VFP_NAME_GIVEN          (1)
#define VFP_NAME_MIDDLE         (2)
#define VFP_NAME_TITLE          (3)

/*
 * Indexes for compound address properties (the "ADR" property).
 */
#define VFP_ADR_POBOX           (0)
#define VFP_ADR_EXTENDED        (1)
#define VFP_ADR_STREET          (2)
#define VFP_ADR_CITY            (3)
#define VFP_ADR_REGION          (4)
#define VFP_ADR_POSTCODE        (5)
#define VFP_ADR_COUNTRY         (6)

/*
 * Indexes for compound organisation properties (the "ORG" property)
 */
#define VFP_ORG_NAME            (0)
#define VFP_ORG_DIVISION        (1)

/*
 * Type declaring macro.
 */
#define VF_DECLARE_TYPE(x) typedef struct _vf_##x { uint8_t _; } x;

/*============================================================================*
 Public Types
 *============================================================================*/

/*
 * Type representing "parser" - an object used to parse VOBJECTS.
 */
VF_DECLARE_TYPE(VF_PARSER_T)

/*
 * Type representing "writer" - an object used to flatten VOBJECTS.
 */
VF_DECLARE_TYPE(VF_WRITER_T)

/*
 * Type representing an "object" - objects are collections of properties.
 */
VF_DECLARE_TYPE(VF_OBJECT_T)

/*
 * Type representing a "property" - properties associate a name & a value.
 */
VF_DECLARE_TYPE(VF_PROP_T)

/*----------------------------------------------------------------------------*
 * PURPOSE
 *      VF_ISO8601_PERIOD_T is used to encapsulate an ISO time 'period'.
 *----------------------------------------------------------------------------*/
 
typedef struct VF_ISO8601_PERIOD_T
{
    uint32_t    years;
    uint32_t    months;
    uint32_t    weeks;
    uint32_t    days;
    uint32_t    hours;
    uint32_t    minutes;
    uint32_t    seconds;
}
VF_ISO8601_PERIOD_T;

/*----------------------------------------------------------------------------*
 * PURPOSE
 *      vf_encoding_t enumerates the supported encodings (formats) of a
 *      vformat object property.  Each "value" has a field of this type.
 *----------------------------------------------------------------------------*/

typedef uint8_t vf_encoding_t;

#define VF_ENC_UNKNOWN          ((vf_encoding_t)(0))
#define VF_ENC_7BIT             ((vf_encoding_t)(1))
#define VF_ENC_8BIT             ((vf_encoding_t)(2))
#define VF_ENC_BASE64           ((vf_encoding_t)(3))
#define VF_ENC_QUOTEDPRINTABLE  ((vf_encoding_t)(4))
#define VF_ENC_VOBJECT          ((vf_encoding_t)(5))

/*----------------------------------------------------------------------------*
 * PURPOSE
 *      vf_get_t controls the operation of vf_get_property() (qv).  Controls
 *      how far the search algorithm is prepared to go in order to return a
 *      property ready for modification.
 *----------------------------------------------------------------------------*/

typedef uint16_t vf_get_t;

#define VFGP_FIND       ((vf_get_t)(0x0001))    /* Search for property            */
#define VFGP_APPEND     ((vf_get_t)(0x0002))    /* Append property, no search     */
#define VFGP_GET        ((vf_get_t)(0x0003))    /* Find & append if not present   */
#define VFGP_ANYNAME    ((vf_get_t)(0x0004))    /* Don't match on name field      */

/*----------------------------------------------------------------------------*
 * PURPOSE
 *      Type of user supplied callback function for vf_write_to_callback().
 *----------------------------------------------------------------------------*/

typedef bool_t (*vf_write_callback_t)(
    const char *p_buffer,       /* The buffer to do whatever you're going to do */
    uint32_t charcount,         /* Number of characters in the buffer */
    uint32_t n_context,         /* Callback context */
    void *p_context             /* A bit more callback context */
    );

/*----------------------------------------------------------------------------*
 * PURPOSE
 *      Various flags controlling the behavious of the vf_write_xxx() calls.
 *  TODO: generalise this to similar behaviours in the vf_read_xxx() calls.
 *  eg. skip binary objects, etc.
 *----------------------------------------------------------------------------*/

typedef uint16_t vf_write_flags_t;

#define VFWF_WRITEALL       ((vf_write_flags_t)0x0001)

/*----------------------------------------------------------------------------*
 * PURPOSE
 *      Check if time_t is defined.
 *----------------------------------------------------------------------------*/

#if defined(_INC_TIME) || defined(_TIME_H) /* +others */
#define VF_TIME_T_DEFINED
#endif

/*============================================================================*
 Public Functions
 *============================================================================*/

/*----------------------------------------------------------------------------*
 * NAME
 *      vf_parse_init()
 * 
 * DESCRIPTION
 *      Allocate and initialise a parser.  To parse a VCARD (or any vObject)
 *      a user allocates a parser, pushes data through it using vf_parse_text()
 *      and finally calls vf_parse_end():
 *
 *          VF_PARSER_T *p_parser;
 *
 *          if (vf_parse_init(&p_parser, pp_object))
 *          {
 *              uint16_t charsread;
 *
 *              do
 *              {
 *                  char buffer[...];
 *              
 *                  numchars = get_chars_from_somewhere(buffer, ...);
 *
 *                  ret = vf_parse_text(p_parser, buffer, charsread);
 *              }
 *              while (ret && (0 < charsread))
 *                  ;
 *
 *              if (!vf_parse_end(p_parser))
 *              {
 *                  ret = FALSE;
 *              }
 *          }
 *
 *      A parser allocated by vf_parse_init(), must be deallocated by calling
 *      vf_parse_end() whether or not parsing succeeds. Also, parsing may not
 *      be complete (ie. values may be held buffered and not evaluated fully
 *      or assigned to a VF_OBJECT_T) untill the final call to vf_parse_end()
 *      => after a vf_parse_init() you _must_ vf_parse_end().
 *
 * RETURNS
 *      TRUE iff parser allocated successfully.
 *----------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_parse_init(
    VF_PARSER_T **pp_parser,        /* Ptr to allocated parser */
    VF_OBJECT_T **pp_object         /* The object we're parsing into */
    );

/*----------------------------------------------------------------------------*
 * NAME
 *      vf_parse_text()
 * 
 * DESCRIPTION
 *      Parse indicated text into the object associated with the VPARSE_T.
 *
 *      See notes for vf_parse_init().
 *
 * RETURNS
 *      TRUE <=> allocation & syntax OK, FALSE else.
 *----------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_parse_text(
    VF_PARSER_T *p_parser,      /* The parser */
    char *p_chars,              /* New characters to parse into object */
    uint32_t numchars           /* Number of new characters */
    );

/*----------------------------------------------------------------------------*
 * NAME
 *      vf_parse_end()
 * 
 * DESCRIPTION
 *      Ensure parse completion, release memory associated with the parser.
 *
 *      See notes for vf_parse_init().
 *
 * RETURNS
 *      TRUE <=> parse complete with no error.
 *----------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_parse_end(
    VF_PARSER_T *p_parse            /* The parser */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_read_file()
 * 
 * DESCRIPTION
 *      Reads indicated VOBJECT_T file.
 *
 * RETURNS
 *      TRUE <=> read OK, FALSE else.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_read_file(
    VF_OBJECT_T **pp_object,        /* Pointer to output object */
    const char *p_name              /* Name of file to read */
    );

/*----------------------------------------------------------------------------*
 * NAME
 *      vf_write_init()
 * 
 * DESCRIPTION
 *      Allocate and initialise a writer.  To write a VCARD (or any vObject)
 *      a user associates a writer with the object and requests chunks of
 *      text from the writer until the entire object has been converted.
 *
 *      It is up to the caller to do something sensible with the text so
 *      obtained - eg place it into a file.
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

extern VFORMATDECLSPEC bool_t vf_write_init(
    VF_WRITER_T **pp_writer,        /* Ptr to where to allocate writer object */
    VF_OBJECT_T *p_object,          /* The object to write */
    vf_write_flags_t flags          /* Flags controlling operation */
    );

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

extern VFORMATDECLSPEC bool_t vf_write_to_buf(
    VF_WRITER_T *p_writer,          /* The writer we're asking to write */
    char *p_buffer,                 /* Buffer to write to */
    uint16_t bufsize,               /* Size of buffer */
    uint16_t *p_byteswritten        /* Ptr to return count via */
    );

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

extern VFORMATDECLSPEC void vf_write_end(
    VF_WRITER_T *p_writer           /* The writer we're finished with */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_write_file()
 * 
 * DESCRIPTION
 *      Write indicated vobject to file.  For lists of objects (eg. read from
 *      a phonebook) the flags parameter allows the caller to control if
 *      the library writes the entire list or just the head item etc.
 *
 * RETURNS
 *      TRUE <=> written OK, FALSE else.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_write_file(
    const char *p_name,             /* Outpt filename */
    VF_OBJECT_T *p_object,          /* The object to write */
    vf_write_flags_t flags          /* Flags controlling operation */
    );

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

extern VFORMATDECLSPEC bool_t vf_write_to_callback(
    VF_OBJECT_T *p_object,      /* The object to write */
    char *p_buffer,             /* Buffer to use */
    uint16_t bufsize,           /* Size of buffer to use */
    vf_write_flags_t flags,     /* Flags controlling operation */
    vf_write_callback_t cb,     /* The callback function */
    uint32_t n_context,         /* Some callback context */
    void *p_context             /* A bit more callback context */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_next_object()
 * 
 * DESCRIPTION
 *      Find "next" vobject.  Typically called after a call to vf_read_file()
 *      which may well read a list of objects from a file for example:
 *
 *          if (vf_read_file(&p_object, p_filename))
 *          {
 *              do
 *              {
 *                  ...
 *              }
 *              while (vf_get_next_object(&p_object))
 *                  ;
 *          }
 *
 *      The value of *pp_object is updated by the call if it returns TRUE.
 *
 * RETURNS
 *      TRUE iff found (ie. there is a "next" object).
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_get_next_object(
    VF_OBJECT_T **pp_object         /* Ptr to pointer to current object */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_create_object()
 * 
 * DESCRIPTION
 *      Creates an empty vformat object.
 *
 * RETURNS
 *      Ptr to object if created else NULL.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC VF_OBJECT_T *vf_create_object(
    const char *p_type,             /* Type of object to create */
    VF_OBJECT_T *p_parent           /* Parent object if any */
    );

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

extern VFORMATDECLSPEC VF_OBJECT_T *vf_clone_object(
    VF_OBJECT_T *p_object,          /* The object to clone */
    VF_OBJECT_T *p_parent           /* Parent object if any */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_object_type()
 * 
 * DESCRIPTION
 *      Return the type string identifying the indicated vformat object,
 *      the string after the 'BEGIN' mark so 'VCARD' or 'VNOTE' etc.
 *
 * RETURNS
 *      Ptr to string.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC const char *vf_get_object_type(
    VF_OBJECT_T *p_object           /* Object to locate type of */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_property()
 * 
 * DESCRIPTION
 *      Basic searching function locating elements of the VOBJECT by qualified
 *      name.  The function is a varargs function (like sprintf) and the list
 *      of arguments must be NULL terminated (hence the appearance of the
 *      p_qualifier argument in the arglist).  Valid calls might be:
 *
 *        vf_get_property(&p_out, p_object, VFGP_FIND, NULL, "N", NULL);
 *          - find and return "N" properties.  If there are none, return FALSE.
 *
 *        vf_get_property(&p_out, p_object, VFGP_FIND, NULL, "TEL", "WORK", NULL);
 *          - find and return "TEL" entries qualified by the "work" attribute
 *            (ie. work phone numbers). If there are none, return FALSE.
 *
 *        vf_get_property(&p_out, p_object, VFGP_GET, NULL, "TEL", "WORK", NULL);
 *          - find and return work phone number.  The entry is automatically
 *          added if not pre-existing.
 *
 *        vf_get_property(&p_out, p_object, VFGP_GET, NULL, "TEL", "WORK", NULL);
 *          - find and return work phone numbers in the group identifier by the "ME"
 *          identifier.  The entry is automatically added if not pre-existing.
 *
 *        vf_get_property(&p_out, p_object, VFGP_FIND, "ME", "*", NULL);
 *          - effectively enumerates all entries in the "ME" group.
 *
 *      A pointer to the first property matching the search criteria is returned
 *      via the pp_prop argument.  The search actually locates all such matches
 *      and pointer to subsequent entries (if there are >1) may be found by
 *      calling the vf_get_next_property() function.
 *
 *      The tags may occur in any order _except_ that the p_name must be first.
 *
 *      Note that the VF_PROP_T returned by pp_prop is an opaque type and the
 *      functions vf_get_prop_xxxx() etc. must be used to locate real "values".
 *
 *      Cached search results (the list enumerated by subsequent calls to the
 *      vf_get_next_property() function) are maintained through the use of a
 *      a single internal pointer therefore this method is not thread safe.
 *
 * RETURNS
 *      TRUE iff found/added successfully.  Ptr to prop returned via pp_prop.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_get_property(
    VF_PROP_T **pp_prop,            /* Output pointer */
    VF_OBJECT_T *p_object,          /* Object to add to */
    vf_get_t ops,                   /* Search flags */
    const char *p_group,            /* Group name if any */
    const char *p_name,             /* Name of tag */
    const char *p_qualifier,        /* First qualifier if any */
    ...                             /* Subequent qualifiers */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_property_ex()
 * 
 * DESCRIPTION
 *      The grunt behind vf_get_property(). Manages the search as described
 *      vf_get_property() but takes the list of arguments as a va_list.
 *      This function should be used when writing higher layer functions
 *      which take varargs (eg. DDX functions).
 *
 * RETURNS
 *      TRUE iff found/added successfully.  ptr to prop returned via pp_prop.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_get_property_ex(
    VF_PROP_T **pp_prop,            /* Output pointer */
    VF_OBJECT_T *p_object,          /* Object to search */
    vf_get_t ops,                   /* Search flags */
    const char *p_group,            /* Group name if any */
    const char *p_name,             /* Name of tag */
    const char *p_qualifier,        /* First qualifier if any */
    va_list args                    /* Argument list */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_next_property()
 * 
 * DESCRIPTION
 *      Find the next property given the current search critera.  User
 *      calls vf_get_property() to locate first in a bunch of properties
 *      and can iterate over the rest by calling vf_get_next_property().
 *
 * RETURNS
 *      TRUE iff found, FALSE else. *pp_prop points to the nex property.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_get_next_property(
    VF_PROP_T **pp_prop             /* Output pointer */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_prop_value()
 * 
 * DESCRIPTION
 *      Get hold of raw fields associated with the property.  These are of
 *      various types:
 *
 *        VF_ENC_VOBJECT
 *          - *pp_value = pointer to contained VF_OBJECT_T which can be
 *          passed back to any of the object manipulation functions.
 *
 *        VF_ENC_7BIT, VF_ENC_QUOTEDPRINTABLE
 *          - *pp_value = ptr to array of char*, *p_size = number of elts.
 *
 *        VF_ENC_8BIT, VF_BASE64
 *          - *pp_value = ptr to bytes, *p_size = number of bytes
 *
 * RETURNS
 *      TRUE <=> encoding is valid, FALSE else.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_get_prop_value(
    VF_PROP_T *p_prop,              /* The property */
    void **pp_value,                /* Pointer value */
    uint32_t *p_size,               /* Integer value */
    vf_encoding_t *p_encoding       /* Type of return values */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_set_prop_value()
 * 
 * DESCRIPTION
 *      Set values associated with a property.
 *
 *      Passing a value of encoding not the same as the current property
 *      encoding will cause the property contents to be freed prior to
 *      setting the indicated value.
 *
 * RETURNS
 *      TRUE <=> re-allocation success & encoding correct, FALSE else.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_set_prop_value(
    VF_PROP_T *p_prop,              /* The property */
    void *p_value,                  /* Pointer to the data */
    uint32_t n_param,               /* Data size or index */
    vf_encoding_t encoding,         /* Encoding in use */
    bool_t copy                     /* Copy the data? */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_prop_value_string()
 * 
 * DESCRIPTION
 *      Obtain string pointer value from VF_PROP_T.  For example a property
 *      may be defined as:
 *
 *      THING;THIS=STUFF;WITH-QUALIFIERS:fred-fred-fred;gogogo;baabaabaa
 *
 *      A call to vf_get_prop_value_string() specifying n_string=1 will
 *      return a pointer to the gogogo value.
 *
 *      Return NULL if out of range request, ie. n_string=3 for N:0;1;2
 *
 * RETURNS
 *      Pointer to string value if value present, NULL if index  too large.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC char *vf_get_prop_value_string(
    VF_PROP_T *p_prop,              /* Property to locate string from */
    uint32_t n_string               /* Index to string required */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_prop_name_string()
 * 
 * DESCRIPTION
 *      Get n'th name string.  For example a property may be defined as:
 *
 *      THING;THIS=STUFF;WITH-QUALIFIERS:fred-fred-fred;gogogo;baabaabaa
 *
 *      A call to vf_get_prop_name_string() specifying n_string=2 will
 *      return a pointer to the WITH-QUALIFIERS value.
 *
 *      Return NULL if out of range request, ie. n_string=4 for X;A;B;C:foo
 *
 * RETURNS
 *      Pointer to string value if value present, NULL if index  too large.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC char *vf_get_prop_name_string(
    VF_PROP_T *p_prop,              /* Property to locate string from */
    uint32_t n_string               /* Index to string required */
    );

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

extern VFORMATDECLSPEC bool_t vf_set_prop_name_string(
    VF_PROP_T *p_prop,              /* Property we're setting a value in */
    uint32_t n_string,              /* Index to string */
    const char *p_string            /* Pointer to string */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_prop_name()
 * 
 * DESCRIPTION
 *      Build the property name string in the indicated buffer.
 *
 * RETURNS
 *      (none)
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC char *vf_get_prop_name(
    VF_PROP_T *p_prop,              /* The property */
    char *p_buffer,                 /* The buffer */
    uint32_t bufsize                /* Size of the buffer */
    );

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

extern VFORMATDECLSPEC VF_OBJECT_T *vf_get_prop_value_object(
    VF_PROP_T *p_prop               /* Property to locate object from */
    );

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

extern VFORMATDECLSPEC bool_t vf_set_prop_value_object(
    VF_PROP_T *p_prop,
    VF_OBJECT_T *p_object
    );

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

extern VFORMATDECLSPEC bool_t vf_set_prop_value_string(
    VF_PROP_T *p_prop,              /* Property we're setting a value in */
    uint32_t n_string,              /* Index to string */
    const char *p_string            /* Pointer to string */
    );

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

extern VFORMATDECLSPEC bool_t vf_set_prop_value_base64(
    VF_PROP_T *p_prop,              /* Property we're setting a value in */
    const uint8_t *p_data,          /* Pointer to the binary data */
    uint32_t length,                /* Length of the binary data */
    bool_t copy                     /* Copy or keep pointer */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_prop_value_base64()
 * 
 * DESCRIPTION
 *      Get a BASE64 property.  Returns ptr, passes length via parameter.
 *
 * RETURNS
 *      Ptr to data.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC const uint8_t *vf_get_prop_value_base64(
    VF_PROP_T *p_prop,              /* Property we're setting a value in */
    uint32_t *p_length              /* Length of the binary data */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_set_property_from_file()
 * 
 * DESCRIPTION
 *      Loads the indicated file into memory and sets the indicated property.
 *
 * RETURNS
 *      TRUE iff succeded, FALSE else.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_set_property_from_file(
    VF_PROP_T *p_prop,              /* The property */
    vf_encoding_t encoding,         /* Encoding to use */    
    const char *p_filename          /* Source filename */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_delete_object()
 * 
 * DESCRIPTION
 *      Cleans up the memory used by the indicated vformat object.
 *
 * RETURNS
 *      (none)
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC void vf_delete_object(
    VF_OBJECT_T *p_object,          /* The object to delete */
    bool_t all                      /* Delete all subsequent objects? */
    );

/*----------------------------------------------------------------------------*
 * NAME
 *      vf_delete_prop()
 * 
 * DESCRIPTION
 *      Deletes indicated property from the indicated object.  Deletes prop
 *      contents if dc is set.
 *
 * RETURNS
 *      (none)
 *----------------------------------------------------------------------------*/

extern VFORMATDECLSPEC void vf_delete_prop(
    VF_OBJECT_T *p_object,          /* The object we're deleting from */
    VF_PROP_T *p_prop,              /* The property we're removing */
    bool_t dc                       /* Should property contents be deleted? */
    );

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

extern VFORMATDECLSPEC bool_t vf_find_prop_qual_index(
    VF_PROP_T *p_prop,                  /* The property we're querying */
    uint32_t *p_qualifier_index,        /* Ptr to output name index */
    uint32_t *p_found_value_index,      /* Ptr to output index in array */
    const char **pp_possible_values,    /* Array of possible values */
    const char *p_token                 /* Token searched for */
    );

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

extern VFORMATDECLSPEC bool_t vf_find_property_qualifier_value(
    VF_PROP_T *p_prop,                  /* The property we're querying */
    uint32_t *p_qualifier_index,        /* Ptr to output name index */
    const char **pp_value,              /* Array of possible values */
    const char *p_token                 /* Token searched for */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_is_modified()
 * 
 * DESCRIPTION
 *      Fetch status of modified flag.
 *
 * RETURNS
 *      TRUE iff modified since list read/write.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_is_modified(
    VF_OBJECT_T *p_object           /* The object */
    );

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

extern bool_t vf_prop_belongs_to_object(
    VF_PROP_T *p_prop,
    VF_OBJECT_T *p_object
    );

/*----------------------------------------------------------------------------*
 * NAME
 *      vf_find_charset()
 * 
 * DESCRIPTION
 *      Locate the CHARSET property which indicates the character encoding
 *      in use - which indicates how the octet stream encoded in the VCARD
 *      is to be decoded into characters.
 *
 * RETURNS
 *      Pointer to character encoding name eg. "UTF-8".
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC const char *vf_find_charset(
    VF_PROP_T *p_prop               /* The property we're querying */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_period_string_to_time()
 * 
 * DESCRIPTION
 *      Convert period definition string to time value.  The format is
 *      P[aaaY][bbbM][cccW][dddD]T[eeeH][fffM][gggS] where 'aaa' is a
 *      number of years, bbb months etc.
 *
 * RETURNS
 *      TRUE <=> conversion OK, FALSE else.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC bool_t vf_period_string_to_time(
    VF_ISO8601_PERIOD_T *p_period,  /* Output time value */
    const char *p_string            /* Input string */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_period_time_to_string()
 * 
 * DESCRIPTION
 *      Convert a VF_ISO8601_PERIOD_T to a string.
 *
 * RETURNS
 *      Number of characters written.
 *---------------------------------------------------------------------------*/

extern VFORMATDECLSPEC uint32_t vf_period_time_to_string(
    char *p_string,                     /* Output string */
    const VF_ISO8601_PERIOD_T *p_period /* Input period value */
    );

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_set_prop_value_time()
 * 
 * DESCRIPTION
 *      Set a time_t value into a VF property.
 *
 * RETURNS
 *      TRUE iff property added & set OK.
 *---------------------------------------------------------------------------*/

#if defined(VF_TIME_T_DEFINED)

extern VFORMATDECLSPEC bool_t vf_set_prop_value_time(
    VF_PROP_T *p_prop,          /* The property */
    uint32_t n_string,          /* Which string we're encoding to */
    const time_t t_value        /* Time value */
    );

#endif

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_get_prop_value_time()
 * 
 * DESCRIPTION
 *      Fetch a time_t value from a VF property.
 *
 * RETURNS
 *      TRUE iff foudn & converted OK.
 *---------------------------------------------------------------------------*/

#if defined(VF_TIME_T_DEFINED)

extern VFORMATDECLSPEC bool_t vf_get_prop_value_time(
    VF_PROP_T *p_prop,          /* The property */
    uint32_t n_string,          /* Which string we're decoding */
    time_t *p_t_value           /* Pointer to output time value */
    );

#endif

/*---------------------------------------------------------------------------*
 * NAME
 *      vf_date_string_to_time()
 * 
 * DESCRIPTION
 *      Convert calendar string to absolute time.  The basic formats are
 *      19960401, 19960401T073000Z
 *
 * RETURNS
 *      TRUE <=> conversion OK, FALSE else.
 *---------------------------------------------------------------------------*/

#if defined(VF_TIME_T_DEFINED)

extern VFORMATDECLSPEC bool_t vf_date_string_to_time(
    time_t *p_time,               /* Output time value */
    const char *p_string            /* Input string */
    );

#endif

#if defined(__cplusplus)
}
#endif

/*============================================================================*
 End of file
 *============================================================================*/

#endif /*INC_VF_IFACE_H*/
