/** 
 * XML Security Library (http://www.aleksey.com/xmlsec).
 *
 * "XML Key Management Specification v 2.0" implementation
 *  http://www.w3.org/TR/xkms2/
 * 
 * This is free software; see Copyright file in the source
 * distribution for preciese wording.
 * 
 * Copyrigth (C) 2002-2003 Aleksey Sanin <aleksey@aleksey.com>
 */
#ifndef __XMLSEC_XKMS_H__
#define __XMLSEC_XKMS_H__    

#ifndef XMLSEC_NO_XKMS
	
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */ 
#include <stdio.h>		

#include <libxml/tree.h>
#include <libxml/parser.h> 

#include <xmlsec/xmlsec.h>
#include <xmlsec/buffer.h>
#include <xmlsec/list.h>
#include <xmlsec/keys.h>
#include <xmlsec/keysmngr.h>
#include <xmlsec/keyinfo.h>
#include <xmlsec/transforms.h>

/**
 * xmlXkmsCtxMode:
 * @xmlXkmsCtxModeLocateRequest: 	the <xkms:LocateRequest/> node processing.
 * @xmlXkmsCtxModeValidateRequest:	the <xkms:ValidateRequest/> node processing.
 *
 * XKMS request processing mode.
 */
typedef enum {
    xmlXkmsCtxModeLocateRequest = 0,
    xmlXkmsCtxModeValidateRequest
} xmlXkmsCtxMode;

/** 
 * xmlSecXkmsCtx:
 * @userData:			the pointer to user data (xmlsec and xmlsec-crypto libraries
 *				never touches this).
 * @flags:			the XML Encryption processing flags.
 * @flags2:			the XML Encryption processing flags.
 * @keyInfoReadCtx:		the reading key context.
 * @keyInfoWriteCtx:		the writing key context (not used for signature verification).
 * @reserved0:			reserved for the future.
 * @reserved1:			reserved for the future.
 * 
 * XKMS context.
 */
struct _xmlSecXkmsCtx {
    /* these data user can set before performing the operation */
    void*			userData;
    unsigned int		flags;
    unsigned int		flags2;    
    xmlXkmsCtxMode		mode;
    xmlSecKeyInfoCtx		keyInfoReadCtx;
    xmlSecKeyInfoCtx		keyInfoWriteCtx;
    
    /* these data are returned */
    xmlDocPtr			result;
    xmlSecPtrList		keys;

    /* these are internal data, nobody should change that except us */
    xmlNodePtr			opaqueClientDataNode;
    xmlNodePtr 			firtsMsgExtNode;
    xmlNodePtr 			firtsRespMechNode;
    xmlNodePtr 			firtsRespWithNode;
    xmlNodePtr 			keyInfoNode;
    
    /* reserved for future */
    void*			reserved0;
    void*			reserved1;
};

XMLSEC_EXPORT xmlSecXkmsCtxPtr	xmlSecXkmsCtxCreate		(xmlSecKeysMngrPtr keysMngr);
XMLSEC_EXPORT void 		xmlSecXkmsCtxDestroy		(xmlSecXkmsCtxPtr xkmsCtx);
XMLSEC_EXPORT int		xmlSecXkmsCtxInitialize		(xmlSecXkmsCtxPtr xkmsCtx,
								 xmlSecKeysMngrPtr keysMngr);
XMLSEC_EXPORT void		xmlSecXkmsCtxFinalize		(xmlSecXkmsCtxPtr xkmsCtx);
XMLSEC_EXPORT int		xmlSecXkmsCtxCopyUserPref	(xmlSecXkmsCtxPtr dst,
								 xmlSecXkmsCtxPtr src);
XMLSEC_EXPORT void		xmlSecXkmsCtxReset		(xmlSecXkmsCtxPtr xkmsCtx);
XMLSEC_EXPORT int		xmlSecXkmsCtxLocate		(xmlSecXkmsCtxPtr xkmsCtx,
								 xmlNodePtr node);
XMLSEC_EXPORT int		xmlSecXkmsCtxValidate		(xmlSecXkmsCtxPtr xkmsCtx,
								 xmlNodePtr node);
XMLSEC_EXPORT void		xmlSecXkmsCtxDebugDump		(xmlSecXkmsCtxPtr xkmsCtx,
								 FILE* output);
XMLSEC_EXPORT void		xmlSecXkmsCtxDebugXmlDump	(xmlSecXkmsCtxPtr xkmsCtx,
								 FILE* output);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XMLSEC_NO_XKMS */

#endif /* __XMLSEC_XKMS_H__ */
