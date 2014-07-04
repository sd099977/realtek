/** \file
 * This file contains the command bytes for messages that are sent to the test application
 * over the serial port.
 *
 * It also contains some generic types for unsigned ints of various sizes.
 */
#ifndef _testapp_h
#define _testapp_h

//#include <stdint.h>
#include "sed_types.h"

#define STATUS_OK               0 //!< Normal return status OK
#define STATUS_ERROR            1 //!< Error status, non specific
#define STATUS_NOT_IMPLEMENTED  2 //!< Function call is not implemented
#define STATUS_COMM_TIMEOUT     3 //!< A timeout occurred
#define STATUS_COMM_ERR         4 //!< A communication error occurred

#define CMD_DES_SET_KEY    0x10 //!< Set DES key
#define CMD_DES_SET_DATA   0x11 //!< Set DES data
#define CMD_DES_ENCRYPT    0x12 //!< Perform DES encryption
#define CMD_DES_DECRYPT    0x13 //!< Perform DES decryption
#define CMD_TDES_SET_KEY   0x20 //!< Set TDES key
#define CMD_TDES_SET_DATA  0x21 //!< Set TDES data
#define CMD_TDES_ENCRYPT   0x22 //!< Perform TDES encryption
#define CMD_TDES_DECRYPT   0x23 //!< Perform TDES decryption
#define CMD_AES_SET_KEY    0x30 //!< Set AES key
#define CMD_AES_SET_DATA   0x31 //!< Set AES data
#define CMD_AES_ENCRYPT    0x32 //!< Perform AES encryption
#define CMD_AES_DECRYPT    0x33 //!< Perform AES decryption
#define CMD_RSA_SET_KEY    0x40 //!< Set RSA key
#define CMD_RSA_SET_DATA   0x41 //!< Set RSA data
#define CMD_RSA_ENCRYPT    0x42 //!< Perform RSA encryption
#define CMD_RSA_DECRYPT    0x43 //!< Perform RSA decryption
#define CMD_LOOP           0x50 //!< Loop test
#define CMD_OTP_READ	   0x51	//!< read data from OTP
#define CMD_OTP_WRITE	   0x52	//!< write data to OTP
#define CMD_TEST           0x74 //!< Test communication

#endif
