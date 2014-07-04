/**
 * File: $Id:$
 *
 *  This header file implements the MSGBUF generic functions and types.
 *
 *  Copyright (c) 2012 Nagravision. All rights reserved.
 *  CH-1033 Cheseaux, Switzerland
 *  Tel: +41 21 7320311  Fax: +41 21 7320100
 *  http://www.nagra.com
 *
 *  All trademarks and registered trademarks are the property of their respective
 *  owners.
 *
 *  This document is supplied with an understanding that the notice(s) herein or
 *  any other contractual agreement(s) made that instigated the delivery of a
 *  hard copy, electronic copy, facsimile or file transfer of this document are
 *  strictly observed and maintained.
 *
 *  The information contained in this document is subject to change without notice.
 *
 *  Security Policy of Nagravision Kudelski Group
 *  Any recipient of this document, without exception, is subject to a
 *  Non-Disclosure Agreement (NDA) and access authorization.
 **/

#ifndef __MSGBUF_API_H_
#define __MSGBUF_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "inc/msgbuf_types.h"


#define MSGBUF_ENUM_DESCRIPTOR_MAGIC_ID      0x1234567
#define MSGBUF_MESSAGE_DESCRIPTOR_MAGIC_ID   0x1234560
#define MSGBUF_SERVICE_DESCRIPTOR_MAGIC_ID   0x2222222
#define MSGBUF_PACKAGE_DESCRIPTOR_MAGIC_ID   0x3333333

/* Macro used in field generation */
/* TODO: move it to generated c-file */
#define MSGBUF_OFFSET_OF(_struct, _member)     \
  ((size_t)(&((_struct*)0)->_member))

/* MSGBUF Structure type definitions */
typedef struct SMsgBuf_enumValue         TMsgBuf_enumValue;
typedef struct SMsgBuf_enumDescriptor    TMsgBuf_enumDescriptor;
typedef struct SMsgBuf_messageDescriptor TMsgBuf_messageDescriptor;
typedef struct SMsgBuf_message           TMsgBuf_message;
typedef struct SMsgBuf_fieldDescriptor   TMsgBuf_fieldDescriptor;
typedef struct SMsgBuf_methodDescriptor  TMsgBuf_methodDescriptor;
typedef struct SMsgBuf_serviceDescriptor TMsgBuf_serviceDescriptor;
typedef struct SMsgBuf_packageDescriptor TMsgBuf_packageDescriptor;

typedef void (*TMsgBuf_messageInit)(
  TMsgBuf_message *,
  const TMsgBuf_messageDescriptor *);


/* TODO: Is RPC related, so might be moved to another interface */
typedef TRpc_status (*TMsgBuf_rpcFctEntry) (
  TMsgBuf_rpcHandler       xRpcHandler,
  const TMsgBuf_message *  pxInMsg,
  TMsgBuf_message       ** pxOutMsg );


/* MSGBUF field types definition */
typedef enum
{
  MSGBUF_FIELDTYPE_INT32      = 0,
  MSGBUF_FIELDTYPE_SINT32     = 1,
  MSGBUF_FIELDTYPE_SFIXED32   = 2,
  MSGBUF_FIELDTYPE_INT64      = 3,
  MSGBUF_FIELDTYPE_SINT64     = 4,
  MSGBUF_FIELDTYPE_SFIXED64   = 5,
  MSGBUF_FIELDTYPE_UINT32     = 6,
  MSGBUF_FIELDTYPE_FIXED32    = 7,
  MSGBUF_FIELDTYPE_UINT64     = 8,
  MSGBUF_FIELDTYPE_FIXED64    = 9,
  MSGBUF_FIELDTYPE_FLOAT      = 10,
  MSGBUF_FIELDTYPE_DOUBLE     = 11,
  MSGBUF_FIELDTYPE_BOOL       = 12,
  MSGBUF_FIELDTYPE_ENUM       = 13,
  MSGBUF_FIELDTYPE_STRING     = 14,
  MSGBUF_FIELDTYPE_BYTES      = 15,
  MSGBUF_FIELDTYPE_MESSAGE    = 16
} TMsgBuf_fieldType;


/* Field member tag definition */
typedef enum
{
  MSGBUF_TAGLABEL_REQUIRED    = 0,
  MSGBUF_TAGLABEL_OPTIONAL    = 1,
  MSGBUF_TAGLABEL_REPEATED    = 2

} TMsgBuf_tagLabel;


/* --- wire format enums --- */
typedef enum
{
  MSGBUF_WIRE_TYPE_VARINT          = 0,
  MSGBUF_WIRE_TYPE_64BIT           = 1,
  MSGBUF_WIRE_TYPE_LENGTH_PREFIXED = 2,
  MSGBUF_WIRE_TYPE_START_GROUP     = 3, /* unsupported */
  MSGBUF_WIRE_TYPE_END_GROUP       = 4, /* unsupported */
  MSGBUF_WIRE_TYPE_32BIT           = 5
} TMsgBuf_wireType;



/* TODO: define in this file... */
typedef struct _ProtobufCIntRange ProtobufCIntRange; /* private */


/* TMsgBuf_enumValue:  this represents a single value of
 * an enumeration.
 * 'name' is the string identifying this value, as given in the .proto file.
 * 'c_name' is the full name of the C enumeration value.
 * 'value' is the number assigned to this value, as given in the .proto file.
 */
struct SMsgBuf_enumValue
{
  int          value;
  const char * pName;
  const char * c_name;
};

/* TMsgBuf_enumDescriptor: the represents the enum as a whole,
 * with all its values.
 * 'magic' is a code we check to ensure that the api is used correctly.
 * 'name' is the qualified name (e.g. "namespace.Type").
 * 'short_name' is the unqualified name ("Type"), as given in the .proto file.
 * 'package_name' is the '.'-separated namespace
 * 'n_values' is the number of distinct values.
 * 'values' is the array of distinct values.
 * 'n_value_names' number of named values (including aliases).
 * 'value_names' are the named values (including aliases).
 *
 * The rest of the values are private essentially.
 *
 * see also: Use protobuf_c_enum_descriptor_get_value_by_name()
 * and protobuf_c_enum_descriptor_get_value() to efficiently
 * lookup values in the descriptor.
 */
struct SMsgBuf_enumDescriptor
{
  uint32_t magic;

  const char              * pName;
  const char              * pShortName;
  const char              * c_name;
  const char              * pPackageName;

  /* sorted by value */
  unsigned int              n_values;
  const TMsgBuf_enumValue * pValues;

  /* sorted by name */
  /* unsigned int                   n_value_names; */
  /* const TMsgBuf_enumValueIndex * pValuesByName; */
};


/*********************************/
/* Message-based type definition */
/*********************************/


/* TMsgBuf_fieldDescriptor: description of a single field
 * in a message.
 * 'name' is the name of the field, as given in the .proto file.
 * 'id' is the code representing the field, as given in the .proto file.
 * 'label' is one of MSGBUF_TAGLABEL_{REQUIRED,OPTIONAL,REPEATED}
 * 'type' is the type of field.
 * 'quantifier_offset' is the offset in bytes into the message's C structure
 *        for this member's "has_MEMBER" field (for optional members) or
 *        "n_MEMBER" field (for repeated members).
 * 'offset' is the offset in bytes into the message's C structure
 *        for the member itself.
 * 'descriptor' is a pointer to a ProtobufC{Enum,Message}Descriptor
 *        if type is MSGBUF_FIELDTYPE_{ENUM,MESSAGE} respectively,
 *        otherwise NULL.
 * 'default_value' is a pointer to a default value for this field,
 *        where allowed.
 */
struct SMsgBuf_fieldDescriptor
{
  const char       * pName;
  TMsgBuf_fieldType  type;
  TMsgBuf_tagLabel   label;
  TMsgBuf_bool       packed;
  uint32_t           id;
  unsigned int       sizeof_field;
  unsigned int       qoffset;
  unsigned int       offset;
  const void       * pDescriptor;    /* for MESSAGE and ENUM types */
  const void       * pDefaultValue;  /* or NULL if no default-value */
};


/* TMsgBuf_messageDescriptor: description of a message.
 *
 * 'magic' is a code we check to ensure that the api is used correctly.
 * 'name' is the qualified name (e.g. "namespace.Type").
 * 'short_name' is the unqualified name ("Type"), as given in the .proto file.
 * 'c_name' is the c-formatted name of the structure
 * 'package_name' is the '.'-separated namespace
 * 'sizeof_message' is the size in bytes of the C structure
 *        representing an instance of this type of message.
 * 'n_fields' is the number of known fields in this message.
 * 'fields' is the fields sorted by id number.
 * 'fields_sorted_by_name', 'n_field_ranges' and 'field_ranges'
 *       are used for looking up fields by name and id. (private)
 */
struct SMsgBuf_messageDescriptor
{
  uint32_t magic;

  const char * pName;
  const char * pShortName;
  const char * c_name;
  const char * pPackageName;

  size_t        sizeof_message;
  const void  * pInitValue;

  /* sorted by field-id */
  unsigned                        n_fields;
  const TMsgBuf_fieldDescriptor * pFields;
  /* const unsigned                * pFieldsSortedByName; */

  /* ranges, optimization for looking up fields */
  /* unsigned int              n_field_ranges; */
  /* const ProtobufCIntRange * pFieldRanges; */

  TMsgBuf_messageInit  message_init;
};


/* TMsgBuf_message: an instance of a message.
 *
 * TMsgBuf_message is sort-of a lightweight
 * base-class for all messages.
 *
 * In particular, TMsgBuf_message doesn't have
 * any allocation policy associated with it.
 * That's because it is common to create TMsgBuf_message's
 * on the stack.  In fact, we that's what we recommend
 * for sending messages (because if you just allocate from the
 * stack, then you can't really have a memory leak).
 *
 * This means that functions like protobuf_c_message_unpack()
 * which return a TMsgBuf_message must be paired
 * with a free function, like protobuf_c_message_free_unpacked().
 *
 * 'descriptor' gives the locations and types of the members of message
 * 'n_unknown_fields' is the number of fields we didn't recognize.
 * 'unknown_fields' are fields we didn't recognize.
 */
struct SMsgBuf_message
{
  const TMsgBuf_messageDescriptor * pDescriptor;
};



struct SMsgBuf_methodDescriptor
{
  const char                      * pName;
  const TMsgBuf_messageDescriptor * pInput;
  const TMsgBuf_messageDescriptor * pOutput;
  TMsgBuf_rpcFctEntry               rpcFctEntry;
};


struct SMsgBuf_serviceDescriptor
{
  uint32_t magic;

  const char                     * pServiceName;
  const char                     * pPackage;
  const int                        serviceId;
  unsigned int                     n_methods;
  const TMsgBuf_methodDescriptor * pMethods;  /* in order from .proto file */
  /* const unsigned              * pMethodIndicesByName; */
};


struct SMsgBuf_packageDescriptor
{
  uint32_t       magic;
  const char   * pName;
  const char   * pShortName;
  const char   * c_name;
  unsigned int   n_services;
  const TMsgBuf_serviceDescriptor ** pService;   /* in order from .proto file */
};


/*----------------------------------------------------------------------------
 * Low level generic function prototypes
 *--------------------------------------------------------------------------*/

void msgbuf_genericMessageInit (
  TMsgBuf_message                 * pxBaseMessage,
  const TMsgBuf_messageDescriptor * pxMessageDescriptor );


void msgbuf_genericMessageDeallocate (
  TMsgBuf_message                 * pxBaseMessage );


int msgbuf_genericTestEnum (
  TMsgBuf_enumDescriptor const * pxEnumDescriptor,
  int                            xValue);


TRpc_status rpc_call (
  TMsgBuf_rpcHandler       xRpcHandler,
  const TMsgBuf_message  * pxInMsg,
  TMsgBuf_message       ** pxOutMsg,
  TMsgBuf_serviceHandle    xServiceHandle,
  uint32_t                 xMethodId );


TRpc_status rpc_notify (
  TMsgBuf_rpcHandler      xRpcHandler,
  const TMsgBuf_message * pxInMsg,
  TMsgBuf_serviceHandle   xServiceHandle,
  uint32_t                xMethodId );

#ifdef __cplusplus
}
#endif


#endif /* __MSGBUF_API_H_ */
