/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package scanner;

import com.sun.jna.Callback;
import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.PointerType;
import com.sun.jna.ptr.IntByReference;
import com.sun.jna.ptr.PointerByReference;
import java.nio.ByteBuffer;

/**
 *
 * @author Ruslan
 */
public class ScannerClass {
    
    public static long scanerHandle;
    
    public interface SCNapi extends Library {
        
        SCNapi INSTANCE = (SCNapi) Native.loadLibrary("4InRdr.api.dll", SCNapi.class);
        
        
        
        public long SCNCreate(Boolean share);                   // Get Handle of the scanner
        public int SCNClose(long scanerHandle);             // Close connection with scanner
        public int SCNGetStatus(long scanerHandle, Pointer Status);
//        public int SCNGetFWRelease(long scanerHandle, byte prog, 
//                byte crcVerify, Pointer outBuffer, int outSize, Pointer bytesReturned);
        public int SCNGetFWRelease(long scanerHandle, byte prog, 
                byte crcVerify, IntByReference outBuffer, int outSize, IntByReference bytesReturned);
        
        public int SCNRunApplication(long scanerHandle);  // Работает, но надо вначале проинициализировать SCNGetFWRelease
        public int SCNWhatsRunning(long scanerHandle, Pointer FwProcess);
        public int SCNRunLoader(long scanerHandle);

//        public int SCNGetFWRelease(long scanerHandle, ByteBuffer Progr, 
//                ByteBuffer CRC, Pointer outBuf, int outSize, Pointer bytesRet);
//        public int SCNGetFWRelease(GetFWCallback callback);
//        public interface GetFWCallback extends Callback {
//            void invoke(long scanerHandle, ByteBuffer Progr, ByteBuffer CRC, 
//                    Pointer outBuf, int outSize, Pointer bytesRet);
//        }
//        public GetFWCallback getFWoutBuf(Pointer outBuf, GetFWCallback getFWCallbackO);
//        public GetFWCallback getFWbytesRest(Pointer bytesRet, GetFWCallback getFWCallbackB);

    }
}
