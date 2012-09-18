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
    
    public static long scannerHandle;
    
    public interface SCNapi extends Library {
        
        SCNapi INSTANCE = (SCNapi) Native.loadLibrary("4InRdr.api.dll", SCNapi.class);
        
        public long SCNCreate(Boolean share);                   // Get Handle of the scanner
        public Boolean SCNClose(long scannerHandle);            // Close connection with scanner
        public Boolean SCNGetStatus(long scannerHandle, Pointer status);
        public Boolean SCNGetFWRelease(long scannerHandle, byte prog, 
                byte crcVerify, Pointer outBuffer, int outSize, Pointer bytesReturned);
    }
}
