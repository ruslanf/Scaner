
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

HANDLE WINAPI SCNCreate(BOOL Share);
BOOL WINAPI SCNWhatsRunning(HANDLE Scanner, LPBYTE FwProcess );
BOOL WINAPI SCNInitialize(HANDLE Scanner, BYTE EngineStartDelay, BYTE HorizontalResolution, BYTE VerticalResolution, BYTE Depth, BYTE ResponseType);
BOOL WINAPI SCNRead(HANDLE Scanner, LPBYTE OutBuffer, DWORD OutSize, LPDWORD BytesReturned);
BOOL WINAPI SCNReadTicket(HANDLE Scanner, LPBYTE OutBuffer, DWORD OutSize, LPDWORD BytesReturned);
BOOL WINAPI SCNStopReading(HANDLE Scanner);
BOOL WINAPI SCNGetStatus(HANDLE Scanner, LPWORD Status);
BOOL WINAPI SCNSetLedIntensity(HANDLE Scanner, BYTE Red, BYTE Green, BYTE Blue, BYTE OnOff);
BOOL WINAPI SCNStaticRead(HANDLE Scanner, BYTE RedGain, BYTE GreenGain, BYTE BlueGain, BYTE RedOffset, BYTE GreenOffset, BYTE BlueOffset, BYTE RowsAmount, BYTE Normalization, LPBYTE OutBuffer, DWORD OutSize, LPDWORD BytesReturned);
BOOL WINAPI SCNEngageEngine(HANDLE Scanner, WORD Interval);
BOOL WINAPI SCNSetFER(HANDLE Scanner, LPBYTE InBuffer, DWORD InSize);
BOOL WINAPI SCNWriteRam(HANDLE Scanner, DWORD DestAddress, LPBYTE InBuffer, DWORD InSize);
BOOL WINAPI SCNWriteFlash(HANDLE Scanner, DWORD DestAddress, LPBYTE InBuffer, DWORD InSize);
BOOL WINAPI SCNSaveTuningParams(HANDLE Scanner);
BOOL WINAPI SCNSaveTicketDescriptor(HANDLE Scanner);
BOOL WINAPI SCNGetFWRelease(HANDLE Scanner, BYTE Program, BYTE CRCVerify, LPBYTE OutBuffer, DWORD OutSize, LPDWORD BytesReturned);
BOOL WINAPI SCNRunApplication(HANDLE Scanner);
BOOL WINAPI SCNRunBootstrap(HANDLE Scanner);
BOOL WINAPI SCNRunLoader(HANDLE Scanner);
BOOL WINAPI SCNFlashBlockErase(HANDLE Scanner, BYTE FlashBlock);
BOOL WINAPI SCNReadMemory(HANDLE Scanner, DWORD StartAddress, DWORD EndAddress, LPBYTE OutBuffer, DWORD OutSize, LPDWORD BytesReturned);
BOOL WINAPI SCNClose(HANDLE Scanner);
		
#ifdef  __cplusplus
}
#endif
	
#endif
