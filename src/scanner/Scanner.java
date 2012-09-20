/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package scanner;

import com.sun.jna.LastErrorException;
import com.sun.jna.Memory;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.PointerType;
import com.sun.jna.platform.win32.WinNT.HANDLE;

import com.sun.jna.ptr.ByteByReference;
import com.sun.jna.ptr.IntByReference;
import com.sun.jna.ptr.PointerByReference;
import com.sun.jna.win32.StdCallLibrary;
import java.nio.Buffer;
import java.nio.ByteBuffer;

import scanner.ScannerClass.SCNapi;

/**
 *
 * @author Ruslan
 */
public class Scanner {
    
    

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        SCNapi scn = SCNapi.INSTANCE;
        Native.setProtected(true);
        ScannerClass scanerClass = new ScannerClass();

        // Get Handle from Scaner
        ScannerClass.scanerHandle = scn.SCNCreate(Boolean.TRUE);
        System.out.println("Handle - " + ScannerClass.scanerHandle);

//        short[] Status = new short[1];
//
////        System.out.println("SCNgetStatus - " + scn.SCNGetStatus(ScannerClass.scanerHandle, Status));
//        if (scn.SCNGetStatus(ScannerClass.scanerHandle, Status)) {
//            System.out.println("SCNgetStatus - " + Status);
//        } else {
//            System.out.println("SCNgetStatus - " + Status);
//        }
        ByteBuffer Progr = ByteBuffer.allocate(1);
        Progr.put((byte) 0x00);
        ByteBuffer CRC = ByteBuffer.allocate(1);
        CRC.put((byte) 0x00);
        

        try {
            int outSize = 0;
            Pointer outBuf = new Memory(100);
            Pointer bytesRet = new Memory(100);
            if (scn.SCNGetFWRelease(ScannerClass.scanerHandle, Progr, CRC, 
                    outBuf.getPointer(0), outSize, bytesRet.getPointer(0)) != 0) {
                System.out.println("bytes - " + bytesRet.getString(0));
            } else {
                System.out.println("Error SCNGetFWRelease");
            }

            Pointer Status = new Memory(4);
//            Status.setMemory(0, 0, (byte) 0);
            
            
//            System.out.println("Status: " + Status.getInt(0));
            System.out.println("Status: " + Status.getPointer(0));
            System.out.println("Status: " + Status.getByte(0));
            System.out.println("Status: " + Status.getString(0));
            
//            if (scn.SCNGetStatus(ScannerClass.scanerHandle, Status.getPointer()) != 0) {
//                System.out.println("Status: " + Status.getPointer());
//            } else {
//                System.out.println("Error = " + Native.getLastError());
//            }


            PointerByReference FwProcess = new PointerByReference();
            System.out.println("FwProcess: " + FwProcess.getValue());
            System.out.println("FwProcess: " + FwProcess.getPointer());
            System.out.println("FwProcess: " + FwProcess.getPointer().getString(0));
//            FwProcess.setByte(0, (byte) 0x00);
//            Pointer FwProcess = new Pointer(0x10);
//            FwProcess.setPointer((long) 0, 0x00);
//            FwProcess.getPointer(0);
            
//            if (scn.SCNWhatsRunning(ScannerClass.scanerHandle, FwProcess.getValue().getPointer(0)) != 0) {
//                System.out.println("FwProcess: " + FwProcess.getValue().getByteArray(0, 4));
//            } else {
//                System.out.println("Error = " + Native.getLastError());
//            }


            // RunApplication
            if (scn.SCNRunApplication(ScannerClass.scanerHandle) == 0) {
                System.out.println("Runned " + Native.getLastError());
            } else {
                System.out.println("Error = " + Native.getLastError());
            }
            // RunLoader
            if (scn.SCNRunLoader(ScannerClass.scanerHandle) == 0) {
                System.out.println("LoaderRunned " + Native.getLastError());
            } else {
                System.out.println("Error = " + Native.getLastError());
            }
        } catch (LastErrorException leEx) {
            System.out.println("Exception: " + leEx.getMessage());

        }
        // Closed Handle after work with scaner
        if (scn.SCNClose(ScannerClass.scanerHandle) != 0) {
            System.out.println("Closed");
        } else {
            System.out.println("Error = " + Native.getLastError());
        }
    }
}
