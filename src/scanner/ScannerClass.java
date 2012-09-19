/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package scanner;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;

/**
 *
 * @author Ruslan
 */
public class ScannerClass {
    
    public static long scanerHandle;
    
    public interface SCNapi extends Library {
        
        
        
//        SCNapi INSTANCE = (SCNapi) Native.loadLibrary("4InRdr.api.dll", SCNapi.class);
        
        public long SCNCreate(Boolean share);                   // Get Handle of the scanner
        public Boolean SCNClose(long scanerHandle);             // Close connection with scanner
        public Boolean SCNGetStatus(long scanerHandle, short[] Status);
        public Boolean SCNGetFWRelease(long scanerHandle, byte prog, 
                byte crcVerify, Pointer outBuffer, int outSize, Pointer bytesReturned);
        public Boolean SCNRunApplication  (long scanerHandle);  // Работает, но надо вначале проинициализировать SCNGetFWRelease
    }
}
