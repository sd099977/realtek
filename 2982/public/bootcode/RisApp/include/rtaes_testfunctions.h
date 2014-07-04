/** \mainpage
 * This is the doxygen generated documentation for the Riscure test application. The test application
 * runs on the embedded target. The vendor is requested to implement methods defined in testfunctions.h.
 *
 * Guidance on how to integrate this source into the target is given in testapp.c.
 */

/** \file
 * This file contains the function definitions for crypto operations, triggering and
 * OTP read operations.
 *
 * Crypto operations and OTP reading are described in more detail below.
 *
 * \section crypto Hardware crypto engines
 *
 * Crypto operations can be split in two parts. There is a preparation phase, where input data and/or key data is set and
 * there is a computation phase where the actual cryptographic operation is
 * performed. These phases are split so that there is fine grained control
 * over the power or EMA measurements.
 *
 * In our tests we focus on the cryptographic engines that are related to the
 * chip internal root keys. Typically in a chip one can perform hardware
 * accelerated crypto operations, or one can use key ladder operations.
 * If physically the same hardware is used between hardware accelerated crypto
 * and key ladder operations, then the hardware accelerated crypto should be used
 * to implement the crypto operations with user-settable key, input, and observable
 * output.
 *
 * If physically not the same hardware engine is used, the (first step) of a
 * key ladder operation should be used to implement the crypto operations with user-settable input. If the decrypt output is not available, no output is returned to the test tool.
 *
 * Commonly a chipset supports the acceleration of several cryptographic algorithms
 * and could be interesting to test. However, only the cryptographic algorithms
 * used for descrambling and PVR are relevant (usually DES and AES). The vendor is
 * responsible for identifying the relevant cryptographic operations using the
 * relevant crypto engines and relevant hardware embedded keys and implement the API
 * calls in the accordingly.
 *
 * During our test setup and power analysis we need the lowest level of control
 * over the user code before the hardware crypto operations are started. The
 * source of the code path from the crypto call in our test application to
 * trigger the start of the hardware crypto must be available in source form
 * (no calls into binary libraries are allowed).
 *
 * \section otp OTP reading
 *
 * The target test application contains API calls for OTP fuse reads. This code is used in fault
 * injection tests. During the fault injection tests on the OTP fuse reads, faults are introduced
 * into the chipset that may cause the chipset to return OTP fuse values from another OTP fuse bank
 * or area than it is supposed to, such as the key ladder root keys, which are normally unreadable.
 *
 * For implementing the OTP fuse reads, it is assumed that there is a mechanism or API in the chipset
 * to read fuse values (either direct, or through RAM or flipflops) by some addressing or indexing
 * mechanism. If the only publicly readable OTP fuse values are hardwired to registers, this part
 * of the API does not have to be implemented.
 *
 */

#ifndef _testfunctions_h
#define _testfunctions_h

/**
 * This function must configure the UART to be running at 115200 baud
 * and 8N1 mode (8 data bits, no parity, 1 stop bit).
 */
void initSerial();

/**
 * The test application must configure the chipset as efficient as possible
 * for testing. All noise should be kept at a minimum to increase the efficiency
 * of the measurements.
 *
 * If possible, power saving modes should be activated to decrease the noise
 * while taking measurements. Preferably the chip is put into a standby mode
 * where the main core and crypto operations still run.
 *
 * All unused clocks of the chipset increase the noise in the measurements made
 * during DPA and DEMA testing. They should be switched off if not required for
 * the test application to run.
 *
 * All unused peripherals (e.g. USB, Ethernet, Descrambler, etc) increase the
 * noise in the measurements made during DPA and DEMA testing.
 *
 */
void initBoard();

/**
 * Sends one character over the line and returns the status to the caller.

 * @param data byte to send
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t serial_send(uint8_t data);

/**
 * Receives 1 byte and stores it in the data argument. This function must be blocking.
 *
 * @param data pointer to where to store the byte
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t serial_recv(uint8_t* data);

/**
 * Enable the output that is used as trigger (e.g. a GPIO pin). Care must be taken that
 * the code that enables or disables the trigger is time constant and has a delay
 * (between calling the routine and performing the trigger operation) as small as
 * possible.
 */
void enableTrigger();

/**
 * Disable the output that is used as trigger (the same one previously enabled with enableTrigger())
 */
void disableTrigger();

/**
 * This function receives an input a byte array address of length addressLength which encodes
 * the offset or index into OTP data that should be returned in parameter data. If for example the
 * chipset only supports indexed access to OTP blocks of a fixed size, address may only contain a
 * single byte (assumed that there are no more than 256 indexes). See also \ref otp.
 *
 * The length of the returned data has to be written in dataLength. If the read operation fails,
 * this function must return an error.
 *
 * @param address pointing to OTP data
 * @param addressLength length of the address
 * @param data (output parameter) OTP data read at the specified address
 * @param dataLength (output parameter) length of OTP data read.
 * @return
 */
uint8_t readOTP(uint16_t* address, uint16_t addressLength, uint8_t* data, uint16_t* dataLength);
uint8_t writeOTP(uint16_t* address, uint16_t addressLength, uint8_t* data, uint16_t* dataLength);



/**
 * Sets the input for the DES operation. For applicability of this method, see \ref crypto.
 *
 * @param data to use as input for the crypto operation.
 * @param length of the data (8 for DES).
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t desSetData(uint8_t* data, uint16_t length);

/**
 * Sets the key for the crypto operation. For applicability of this method, see \ref crypto.
 *
 * @param key data to set as key
 * @param length of the key
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t desSetKey(uint8_t* key, uint16_t length);

/**
 * Runs a DES encrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t desEncrypt(uint8_t* response, uint16_t* length);

/**
 * Runs a DES decrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t desDecrypt(uint8_t* response, uint16_t* length);

/**
 * Sets the input for the TDES operation. For applicability of this method, see \ref crypto.
 *
 * @param data to use as input for the crypto operation.
 * @param length of the data (8 for DES).
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t tdesSetData(uint8_t* data, uint16_t length);

/**
 * Sets the key for the crypto operation. For applicability of this method, see \ref crypto.
 *
 * @param key data to set as key
 * @param length of the key
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t tdesSetKey(uint8_t* key, uint16_t length);

/**
 * Runs a TDES encrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t tdesEncrypt(uint8_t* response, uint16_t* length);

/**
 * Runs a TDES decrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t tdesDecrypt(uint8_t* response, uint16_t* length);

/**
 * Sets the input for the AES operation. For applicability of this method, see \ref crypto.
 *
 * @param data to use as input for the crypto operation.
 * @param length of the data (8 for DES).
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t aesSetData(uint8_t* data, uint16_t length);

/**
 * Sets the key for the crypto operation. For applicability of this method, see \ref crypto.
 *
 * @param key data to set as key
 * @param length of the key
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t aesSetKey(uint8_t* key, uint16_t length);

/**
 * Runs a AES encrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t aesEncrypt(uint8_t* response, uint16_t* length);

/**
 * Runs a AES decrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t aesDecrypt(uint8_t* response, uint16_t* length);

/**
 * Sets the input for the AES operation. For applicability of this method, see \ref crypto.
 *
 * @param data to use as input for the crypto operation.
 * @param length of the data (8 for DES).
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t rsaSetData(uint8_t* data, uint16_t length);

/**
 * Sets the key for the crypto operation. For applicability of this method, see \ref crypto.
 *
 * @param key data to set as key
 * @param length of the key
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t rsaSetKey(uint8_t* key, uint16_t length);

/**
 * Runs a RSA encrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t rsaEncrypt(uint8_t* response, uint16_t* length);

/**
 * Runs a RSA decrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t rsaDecrypt(uint8_t* response, uint16_t* length);

#endif
