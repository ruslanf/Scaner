/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package scanner;

import com.sun.jna.Memory;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.platform.win32.WinNT.HANDLE;

import scanner.ScannerClass.SCNapi;

/**
 *
 * @author Ruslan
 */
public class Scanner {

//    private HANDLE handleDevice = INVALID_HANDLE_VALUE;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        int status = 0;
        Pointer outBuffer = new Pointer(10000000);
        Pointer bytesReturned = new Pointer(1000000);
        

//        SCNapi scn = (SCNapi) Native.loadLibrary("4InRdr.api.dll", SCNapi.class);
        SCNapi scn = SCNapi.INSTANCE;
        // Get Handle from Scaner
        ScannerClass.scannerHandle = scn.SCNCreate(Boolean.TRUE);
        System.out.println("work - " + ScannerClass.scannerHandle);

        Memory intMem = new Memory(4);  // allocating space
//        intMem.setInt(0, 666); // setting allocated memory to an integer
        Pointer intPointer = intMem.getPointer(0);
        
        if (scn.SCNGetStatus(ScannerClass.scannerHandle, Pointer.NULL)) {
            
        System.out.println("status - " + status);
        } else {
            System.out.println("status - not work");
        }

//        Memory intMem = new Memory(4);  // allocating space
//        //intMem.setInt(0, 666); // setting allocated memory to an integer
//        Pointer intPointer = intMem.getPointer(0);
//        
//        if (scn.SCNGetFWRelease(ScannerClass.scannerHandle, status, status, 
//                Pointer.NULL, 1000000, Pointer.NULL)) {
//            System.out.println("bytes returned - " + bytesReturned);
//        } else {
//            System.out.println("bytes returned - " + bytesReturned);
//        }
        
        // Closed Handle after work with scaner
        if (scn.SCNClose(ScannerClass.scannerHandle)) {
            System.out.println("Closed");
        }
    }
}
