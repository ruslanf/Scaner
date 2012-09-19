
/** \file 4InRdr.api.h
 * 
 * \brief Declares Olivetti Four Inches Reader API functions; it is part of \ref api.
 *
 */
  
#ifndef __4INRDR_API_C__
#define __4INRDR_API_C__		1

#ifndef __4INREADERIOCTL_H__
#pragma message("__4INREADERIOCTL_H__ UNDEFINED. INCLUDE 4INRDRIOCTL.H")
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/** \brief Opens an <I>HANDLE</I> to device driver.
 *
 * The <I>HANDLE</I> returned by this call is used with each of the functions listed below;
 * Use the ::SCNClose function, once finished using the device, to release claimed resources.
 *
 * @param Share IN If <I>FALSE</I> device is accessed exclusively.
 * @return If the function succeeds, the return value is an handle to the reader device driver that can
 * be used with subsequential API library calls.
 * If the function fails, the return value is INVALID_HANDLE_VALUE. To get extended error information, call
 * <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>. 
 */
HANDLE
WINAPI SCNCreate(
	IN	BOOL Share
	);
			
/** \brief Returns currently running firmware component.
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.  
 * @param FwProcess OUT Pointer to a user allocated <I>BYTE</I> that, once the function is returned, may assume
 * one of the following values:
 * <table>
 * <tr>
 * <td><b>0xBB</b></td><td>Bootstrap</td>
 * </tr>
 * <tr>
 * <td><b>0xAA</b></td><td>Application</td> 
 * </tr>
 * <tr>
 * <td><b>0xDD</b></td><td>Loader (available for older serial devices only)</td> 
 * </tr> 
 * </table>
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>.   
 * @remarks This function is available for every firmware component.
 */				
BOOL
WINAPI SCNWhatsRunning(
	IN	HANDLE Scanner,
	OUT	LPBYTE FwProcess
	);
			
/** \brief Initializes reader.
 *
 * In order to use device for reading operations it is necessary to initialize it; at device
 * power up, it is in a non-initialized state.
 * By using this function it is possible to initialize device estabilishing reading parameters
 * such vertical or horizontal resolution.
 * Once function succeeds, device uses supplied parameters for each
 * subsequantial reading operation until this function is newly called.
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.
 * @param EngineStartDelay IN Interval that elapses between document relevation and dragging engine activation ((EngineStartDelay * 10) msec).
 * @param HorizontalResolution IN Horizontal resolution; refer to hardware documentation for more informations.
 * @param VerticalResolution IN Vertical resolution; refer to hardware documentation for more informations.
 * @param Depth IN Bit per pixel codification; It may assume one of the following values:
 * <table>
 * <tr><td>0x01</td><td>1 bit per pixel</td></tr>
 * <tr><td>0x02</td><td>2 bit per pixel</td></tr>	 
 * <tr><td>0x04</td><td>4 bits per pixel</td></tr>
 * <tr><td>0x08</td><td>8 bits per pixel</td></tr>
 * </table> 
 * @param ResponseType IN Device response type; it may assume one of the following values:
 * <table>
 * <tr><td>0x31</td><td>Acquired image interpretation</td></tr>
 * <tr><td>0x32</td><td>Acquired image bitmap</td></tr>
 * <tr><td>0x33</td><td>Acquired image interpretation and bitmap</td></tr>	 
 * </table>
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>.
 * @remarks This function is available only while device is running <I>application</I> firmware component.
 * @see SCNWhatsRunning
 * @see SCNRead
 * @see SCNReadTicket
 */
BOOL
WINAPI SCNInitialize(
	IN	HANDLE Scanner,
	IN	BYTE EngineStartDelay,
	IN	BYTE HorizontalResolution,
	IN	BYTE VerticalResolution,
	IN	BYTE Depth,
	IN	BYTE ResponseType
	);
			
/** \brief Reads a document.
 *
 * By using this function it is possible to acquire a document bitmap in raw format, without any interpretation;
 * <I>this is a blocking function that does not returns until a document is inserted and read.</I>
 * Once device is engaged to perform this operation, it will does not accept any other command
 * except for ::SCNStopReading.
 * If the amount of memory allocated by the application is insufficient to store all device incoming data, operation fails and
 * <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a> will return
 * <I>ERROR_INSUFFICIENT_BUFFER</I>; in this case <I>BytesReturned</I> parameter will report required memory amount.
 * This behavior can be used by an application to know <I>a priori</I> how many bytes it has to allocate to read a given document by 
 * perform a fake call, suppling zero as <I>OutSize</I> parameter. 
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.
 * @param OutBuffer OUT User allocated memory that will be used to store raw data incoming from device.
 * @param OutSize IN <I>OutBuffer</I> size in bytes.
 * @param BytesReturned OUT Pointer to a user allocated <I>DWORD</I> that, once the function is returned, reports amount of data, in bytes,
 * written to <I>OutBuffer</I>. If supplied output memory is insufficient to store all device's incoming data, ::SCNRead fails and <I>BytesReturned</I>
 * reports required amount.
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>. 
 * Function specific error values are:
 * <table>
 * <tr>
 * <td><b>ERROR_OPERATION_ABORTED</b></td><td>A reading operation has been canceled by the user.</td>
 * </tr>
 * </table>   
 * @remarks This function is available only while device is running <I>application</I> firmware component.
 * @see SCNWhatsRunning 
 * @see SCNInitialize
 * @see SCNReadTicket
 */				
BOOL
WINAPI SCNRead(
	IN	HANDLE Scanner,
	OUT	LPBYTE OutBuffer,
	IN	DWORD OutSize,
	OUT	LPDWORD BytesReturned
	);
	
/** \brief Reads and interprets a ticket.
 *
 * By using internal recognition engine, the scanner device reads a ticket and returns codified marks;
 * <I>this is a blocking function that does not returns until a document is inserted and read.</I>
 * Once device is engaged in this operation, it will does not accept any other command
 * except for ::SCNStopReading.
 * If the amount of memory allocated by the application is insufficient to store all device incoming data, operation fails and
 * <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a> will return
 * <I>ERROR_INSUFFICIENT_BUFFER</I>; in this case <I>BytesReturned</I> parameter will report required memory amount.
 * This behavior can be used by an application to know <I>a priori</I> how many bytes it has to allocate to read a given document by 
 * perform a fake call, suppling zero as <I>OutSize</I> parameter. 
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.
 * @param OutBuffer OUT A byte representing firmware result, followed by a pointer to a buffer that represent the recognized marks.
 * The format of these data depends on the internal recognition engine; refer to relative manual for extra information.   
 * Notice that if device fails reconition operations, only the firmware result byte is returned. 
 * @param OutSize IN <I>OutBuffer</I> size in bytes.
 * @param BytesReturned OUT Pointer to a user allocated <I>DWORD</I> that, once the function is returned, reports amount of data, in bytes,
 * written to <I>OutBuffer</I>. If supplied output memory is insufficient to store all device's incoming data, ::SCNReadTicket fails and <I>BytesReturned</I>
 * reports required amount.
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>. 
 * Function specific error values are:
 * <table>
 * <tr>
 * <td><b>ERROR_OPERATION_ABORTED</b></td><td>A reading operation has been canceled by the user.</td>
 * </tr>
 * </table>  
 * @remarks This function is available only while device is running <I>application</I> firmware component.
 * @see SCNWhatsRunning 
 * @see SCNInitialize
 * @see SCNRead
 */			
BOOL
WINAPI SCNReadTicket(
	IN	HANDLE Scanner,
	OUT	LPBYTE OutBuffer,
	IN	DWORD OutSize,
	OUT	LPDWORD BytesReturned
	);
		
/** \brief Cancels a document reading operation.
 *
 * This is the only command that device accepts while engaged in a read operation;
 * if device is blocked in a document reading operation, this function will abort it.
 * It takes no effect if scanner is not executing a read request.
 * Document reading operation cancelled by ::SCNStopReading fails due to <I>ERROR_OPERATION_ABORTED</I>.
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>.  
 * @remarks This function is available only while device is running <I>application</I> firmware component.
 * @see SCNWhatsRunning 
 * @see SCNRead
 * @see SCNReadTicket 
 */			
BOOL
WINAPI SCNStopReading(
	IN	HANDLE Scanner
	);
		
/** \brief Returns informations about device status.
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.
 * @param Status OUT Pointer to a user allocated <I>WORD</I> that, once the function is returned, reports device status.
 * This field is a bit mask that assumes the following meaning:
 * <table>
 * <tr><td>bit 0</td><td>If on the first photosensor is busy</td></tr>
 * <tr><td>bit 1</td><td>If on the second photosensor is busy (still not used)</td></tr>	 
 * <tr><td>bit 2</td><td>If on a new image is in memory</td></tr>
 * <tr><td>bit 3</td><td>If on the keyboard buffer is not empty</td></tr>
 * <tr><td>bit 4</td><td>If on the reader has been initialized</td></tr>
 * <tr><td>bit 5</td><td>If on the keyboard has been initialized</td></tr>	 
 * <tr><td>bit 6</td><td>If on the reader has been tuned</td></tr>
 * <tr><td>bit 7</td><td>If on the device is equipped with a phototransistor sensor; with a photodiod one otherwise</td></tr>
 * <tr><td>bit 8</td><td>If on the printing management module is installed</td></tr>
 * </table>  
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>.  
 * @remarks This function is available only while device is running <I>application</I> firmware component.
 * @see SCNWhatsRunning 
 */			
BOOL
WINAPI SCNGetStatus(
	IN	HANDLE Scanner,
	OUT	LPWORD Status
	);
			
/** \brief Sets leds intensity.
 *
 * Using this function it is possible to modify reader's leds intensity
 * that are used while performing a read operation.
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.
 * @param Red IN Red led; It may assume a value betrween 0x00 and 0xFE.  
 * @param Green IN Green led; It may assume a value betrween 0x00 and 0xFE.  
 * @param Blue IN Blue led; It may assume a value betrween 0x00 and 0xFE.  
 * @param OnOff IN Power switch; it may assume the following values:
 * <table>
 * <tr><td>0x00</td><td>Leds off</td></tr>
 * <tr><td>0x01</td><td>Leds on</td></tr>
 * <tr><td>0xFE</td><td>Leds intensity are set by reading relative values in a fixed position (0xA6000) of device's RAM memory</td></tr>	 
 * <tr><td>0xFF</td><td>Allows to switch device's led with no changes on intensity values</td></tr>	 	 
 * </table>
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>.  
 * @remarks This function is available only while device is running <I>application</I> firmware component.
 * @see SCNWhatsRunning 
 */			
BOOL
WINAPI SCNSetLedIntensity(
	IN	HANDLE Scanner,
	IN	BYTE Red,
	IN	BYTE Green,
	IN	BYTE Blue,
	IN	BYTE OnOff	
	);
			
/** \brief Reads without engage dragging engine.
 *
 * This function lets the device read the supplied amount of rows without engaging the drag engine.
 * This function, normally, is used only during the tuning procedure.
 * If the amount of memory allocated by the application is insufficient to store all device incoming data, operation fails and
 * <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a> will return
 * <I>ERROR_INSUFFICIENT_BUFFER</I>; in this case <I>BytesReturned</I> parameter will report required memory amount.
 * This behavior can be used by an application to know <I>a priori</I> how many bytes it has to allocate to read a given document by 
 * perform a fake call, suppling zero as <I>OutSize</I> parameter. 
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.
 * @param RedGain IN Red gain; it may assume a value betrween 0x00 and 0x3F.  
 * @param GreenGain IN Green gain; it may assume a value betrween 0x00 and 0x3F.  
 * @param BlueGain IN Blue gain; it may assume a value betrween 0x00 and 0x3F.  
 * @param RedOffset IN Red offset; a value between 0x00 and 0x1F add a positive offset from the signal obtained from the red channel; 
 * a value between 0x20 and 0x3F subtract a positive offset from that signal.
 * @param GreenOffset IN Green offset; a value between 0x00 and 0x1F add a positive offset from the signal obtained from the green channel; 
 * a value between 0x20 and 0x3F subtract a positive offset from that signal.
 * @param BlueOffset IN Blue offset; a value between 0x00 and 0x1F add a positive offset from the signal obtained from the blue channel; 
 * a value between 0x20 and 0x3F subtract a positive offset from that signal.
 * @param RowsAmount IN Rows amount to be returned by the reading operation.
 * @param Normalization IN Digital compensation; it may assume the following values: 
 * <table>
 * <tr><td>0x00</td><td>Disabled</td></tr>
 * <tr><td>0x01</td><td>Enabled</td></tr>
 * </table>
 * @param OutBuffer OUT User allocated memory that will be used to store raw data incoming from device.
 * @param OutSize IN <I>OutBuffer</I> size in bytes.
 * @param BytesReturned OUT Pointer to a user allocated <I>DWORD</I> that, once the function is returned, reports amount of data, in bytes,
 * written to <I>OutBuffer</I>. If supplied output memory is insufficient to store all device's incoming data, ::SCNRead fails and <I>BytesReturned</I>
 * reports required amount.
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>. 
 * @remarks This function is available only while device is running <I>application</I> firmware component.
 * @see SCNWhatsRunning 
 * @see SCNRead
 * @see SCNReadTicket
 */							
BOOL
WINAPI SCNStaticRead(
	IN	HANDLE Scanner,
	IN	BYTE RedGain,
	IN	BYTE GreenGain,
	IN	BYTE BlueGain,
	IN	BYTE RedOffset,
	IN	BYTE GreenOffset,
	IN	BYTE BlueOffset,
	IN	BYTE RowsAmount,
	IN	BYTE Normalization,
	OUT	LPBYTE OutBuffer,
	IN	DWORD OutSize,
	OUT	LPDWORD BytesReturned	
	);
	
/** \brief Engages device engine.
 *
 * Normally, this function is used for diagnostic purposes only.
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function. 
 * @param Interval IN A <I>WORD</I> value that represents engaging interval in milliseconds.
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>.  
 * @remarks This function is available only while device is running <I>application</I> firmware component.
 * @see SCNWhatsRunning 
 */				
BOOL
WINAPI SCNEngageEngine(
	IN	HANDLE Scanner,
	IN	WORD Interval
	);
		
/** \brief Analog Front End Registers.
 *
 * By this function it is possible to manually set the Analog Front End registers.
 * Normally, this function is used for diagnostic purposes only.
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.  
 * @param InBuffer IN Buffer representing a variable size array of front end register structures. 
 * These structures are constituted by a pair of bytes each; the first byte represents register's address,
 * while the second byte represents the relative value.
 * @param InSize IN <I>InBuffer</I> size, in bytes.
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>.  
 * @remarks This function is available only while device is running <I>application</I> firmware component.
 * @see SCNWhatsRunning 
 */			
BOOL
WINAPI SCNSetFER(
	IN	HANDLE Scanner,
	IN	LPBYTE InBuffer,
	IN	DWORD InSize
	);
				
/** \brief Writes data to device RAM memory.
 * 
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.  
 * @param DestAddress IN Device RAM memory destination address.
 * @param InBuffer IN Buffer representing the data to be written to device RAM memory.
 * @param InSize IN <I>InBuffer</I> size, in bytes. 
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>.   
 * @remarks This function is available for every firmware component.
 * @see SCNWriteFlash 
 */							
BOOL
WINAPI SCNWriteRam(
	IN	HANDLE Scanner,
	IN	DWORD DestAddress,
	IN	LPBYTE InBuffer,
	IN	DWORD InSize
	);
			
/** \brief Writes data to device FLASH memory.
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.  
 * @param DestAddress IN Device FLASH memory destination address.
 * @param InBuffer IN Buffer representing the data to be written to device FLASH memory.
 * @param InSize IN <I>InBuffer</I> size, in bytes. Notice that this size has to be SCRMAXMEMAMOUNT multiple, otherwise the function will fail.
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>.   
 * Function specific error values are:
 * <table>
 * <tr>
 * <td><b>ERROR_BAD_COMMAND</b></td><td>If commands sequence was wrong.</td>
 * </tr>
 * <tr>
 * <td><b>ERROR_NOT_READY</b></td><td>If FLASH was not ready.</td>
 * </tr>
 * <tr>
 * <td><b>ERROR_SWAPERROR</b></td><td>If there was a page programming error.</td>
 * </tr> 
 * </table> 
 * @remarks This function is available for every firmware component.
 * @see SCNWriteRam
 */				
BOOL
WINAPI SCNWriteFlash(
	IN	HANDLE Scanner,
	IN	DWORD DestAddress,
	IN	LPBYTE InBuffer,
	IN	DWORD InSize
	);
		
/** \brief Saves tuning parameters.
 *
 * By this function the tuning parameters, written before to device RAM
 * memory, are premanently saved to device FLASH memory. Refer to hardware
 * documentation to learn about tuning data structure.
 * 
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.  
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>.    
 * @remarks This function is available only while device is running <I>application</I> firmware component.
 * @see SCNWhatsRunning
 */				
BOOL
WINAPI SCNSaveTuningParams(
	IN	HANDLE Scanner
	);
		
/** \brief Saves ticket descriptor.
 *
 * If the scanner device is using the embedded recogition engine, it uses
 * the informations about tickets stored in the device FLASH memory to perform
 * its task. These informations have to be written before to device RAM memory
 * at a position between 0x32400 and 0x343FF, and then stored at device's FLASH
 * memory by using this function. For more informations about ticket description
 * format see recognition engine documentation. 
 *  
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.  
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>.    
 * @remarks This function is available only while device is running <I>application</I> firmware component.
 * @see SCNWhatsRunning
 */				
BOOL
WINAPI SCNSaveTicketDescriptor(
	IN	HANDLE Scanner
	);
			
/** \brief Returns device firmware components releases.
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.  
 * @param Program IN A <I>BYTE</I> that may assume the following values:
 * <table>
 * <tr><td>0x00</td><td>Application</td></tr>
 * <tr><td>0x01</td><td>Loader (available for older serial devices only)</td></tr>
 * <tr><td>0x02</td><td>Bootstrap</td></tr>	 
 * <tr><td>0x03</td><td>Recognition</td></tr>	 	 
 * </table>
 * @param CRCVerify IN Integrity checking. Set it to 0x01 if you want to perform an extra integrity check; to 0x00 otherwise.
 * @param OutBuffer OUT User allocated memory that will be used to store raw data incoming from device.
 * @param OutSize IN <I>OutBuffer</I> size in bytes.
 * @param BytesReturned OUT Pointer to a user allocated <I>DWORD</I> that, once the function is returned, reports amount of data, in bytes,
 * written to <I>OutBuffer</I>. If supplied output memory is insufficient to store all device's incoming data, ::SCNRead fails and <I>BytesReturned</I>
 * reports required amount.
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>. 
 * Function specific error values are:
 * <table>
 * <tr>
 * <td><b>ERROR_CRC</b></td><td>If required firmware component was corrupted or absent.</td>
 * </tr>
 * </table>   
 * @remarks This function is available for every firmware component.
 */			
BOOL
WINAPI SCNGetFWRelease(
	IN	HANDLE Scanner,
	IN	BYTE Program,
	IN	BYTE CRCVerify,
	OUT	LPBYTE OutBuffer,
	IN	DWORD OutSize,
	OUT	LPDWORD BytesReturned		
	);
	
/** \brief Jumps to <I>application</I> firmware component.
 *
 * Notice that, before this function may succeeds, it is necessary to have requested
 * <I>application</I> component release whith CRC checking, using the ::SCNGetFWRelease function.
 * Since current firmware process, to satisfy the request, has to
 * leave control to <I>application</I>, this command will always fail due I/O timeout error
 * because <I>application</I>, that has not received any request, returns no response. 
 * The function fails if <I>application</I> is already running. 
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.  
 * @return This function always returns zero; but, if it succeeds, the error reported by 
 * <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a> 
 * is ERROR_SEM_TIMEOUT. Function specific error values are:
 * <table>
 * <tr>
 * <td><b>ERROR_CRC</b></td><td>If firmware <I>application</I> CRC has not been previously verified.</td>
 * </tr>
 * </table>    
 * @remarks This function is available only while device is running <I>bootstrap</I> firmware component.
 * @see SCNWhatsRunning
 * @see SCNGetFWRelease
 */				
BOOL
WINAPI SCNRunApplication(
	IN	HANDLE Scanner
	);
			
/** \brief Jumps to <I>bootstrap</I> firmware component.
 *
 * Notice that, before this function may succeeds, it is necessary to have requested
 * <I>bootstrap</I> component release whith CRC checking, using the ::SCNGetFWRelease function.
 * Since current firmware process, to satisfy the request, has to
 * leave control to <I>bootstrap</I>, this command will always fail due I/O timeout error
 * because <I>bootstrap</I>, that has not received any request, returns no response. 
 * The function fails if <I>bootstrap</I> is already running. 
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.  
 * @return This function always returns zero; but, if it succeeds, the error reported by 
 * <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a> 
 * is ERROR_SEM_TIMEOUT. Function specific error values are:
 * <table>
 * <tr>
 * <td><b>ERROR_CRC</b></td><td>If firmware <I>bootstrap</I> CRC has not been previously verified.</td>
 * </tr>
 * </table>    
 * @remarks This function is available only while device is running <I>bootstrap</I> firmware component.
 * @see SCNWhatsRunning
 * @see SCNGetFWRelease
 */				
BOOL
WINAPI SCNRunBootstrap(
	IN	HANDLE Scanner
	);
			
/** \brief Jumps to <I>loader</I> firmware component.
 *
 * Notice that, before this function may succeeds, it is necessary to have requested
 * <I>loader</I> component release whith CRC checking, using the ::SCNGetFWRelease function.
 * Since current firmware process, to satisfy the request, has to
 * leave control to <I>loader</I>, this command will always fail due I/O timeout error
 * because <I>loader</I>, that has not received any request, returns no response. 
 * The function fails if <I>loader</I> is already running. 
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.  
 * @return This function always returns zero; but, if it succeeds, the error reported by 
 * <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a> 
 * is ERROR_SEM_TIMEOUT. Function specific error values are:
 * <table>
 * <tr>
 * <td><b>ERROR_CRC</b></td><td>If firmware <I>loader</I> CRC has not been previously verified.</td>
 * </tr>
 * </table>    
 * @remarks This function is available only while device is running <I>bootstrap</I> firmware component.
 * @see SCNWhatsRunning
 * @see SCNGetFWRelease
 * @deprecated This function is exported only for compatibility reasons; older devices only have the <I>loader</> component. 
 */				
BOOL
WINAPI SCNRunLoader(
	IN	HANDLE Scanner
	);
			
/** \brief Deletes device's FLASH blocks.
 *
 * An application, usually, does not have need to recur to this function;
 * it is involved only in firmware upgrading operations.
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.   
 * @param FlashBlock IN A <I>BYTE</I> that represents device FLASH block to be deleted; it may assume a value between 0x00 and 0x06.
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>.   
 * Function specific error values are:
 * <table>
 * <tr>
 * <td><b>ERROR_BAD_COMMAND</b></td><td>If commands sequence was wrong.</td>
 * </tr>
 * <tr>
 * <td><b>ERROR_GEN_FAILURE</b></td><td>Block deleteing error.</td>
 * </tr>
 * </table>  
 * @remarks This function is available while device is running both firmware components.
 * @warning Use this function with extreme caution; it may result in device inoperability.
 * @see SCNWriteFlash
 */				
BOOL
WINAPI SCNFlashBlockErase(
	IN	HANDLE Scanner,
	IN	BYTE FlashBlock
	);
			
/** \brief Reads from device memory.
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.   
 * @param StartAddress IN Device memory start address.   
 * @param EndAddress IN Device memory end address.    
 * @param OutBuffer OUT User allocated memory that will be used to store raw data incoming from device.
 * @param OutSize IN <I>OutBuffer</I> size in bytes.
 * @param BytesReturned OUT Pointer to a user allocated <I>DWORD</I> that, once the function is returned, reports amount of data, in bytes,
 * written to <I>OutBuffer</I>. If supplied output memory is insufficient to store all device's incoming data, ::SCNRead fails and <I>BytesReturned</I>
 * reports required amount.
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>. 
 * @remarks This function is available only for USB device, while it is running <I>application</I> firmware component.
 * @see SCNWhatsRunning
 */			
BOOL
WINAPI SCNReadMemory(
	IN	HANDLE Scanner,
	IN	DWORD StartAddress,
	IN	DWORD EndAddress,
	OUT	LPBYTE OutBuffer,
	IN	DWORD OutSize,
	OUT	LPDWORD BytesReturned			
	);
								
/** \brief Closes device handle.
 *
 * Using this function it is possible to free system resources releasing the <I>HANDLE</I> obtained by
 * a ::SCNCreate call.
 *
 * @param Scanner IN Handle to the reader device driver; it is returned by ::SCNCreate function.
 * @return If the function succeeds, the return value is nonzero; if the function fails, the return value is zero. 
 * To get extended error information, call <a href=http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/getlasterror.asp>GetLastError</a>. 
 * @see SCNCreate
 */				
BOOL
WINAPI SCNClose(
	IN	HANDLE Scanner
	);
		
#ifdef  __cplusplus
}
#endif
	
#endif
