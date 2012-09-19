/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package scanner;

import com.sun.jna.Memory;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.platform.win32.WinNT.HANDLE;

import com.sun.jna.ptr.ByteByReference;
import com.sun.jna.ptr.IntByReference;
import com.sun.jna.win32.StdCallLibrary;
import java.nio.Buffer;
import java.nio.ByteBuffer;
import libforscaner.LibForScanerLibrary;

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
//        int status = 0;
//        Status status= new Status();
//        Pointer outBuffer = new Pointer(10000000);
//        Pointer bytesReturned = new Pointer(1000000);
//        byte outSize;// = new Byte(1000000);
        int outSize = 1000000;
        byte test = 0x00;
        byte Progr = 0x00;
        byte CRC = 0x00;
        //short status = 0;


        SCNapi scn = (SCNapi) Native.loadLibrary("4InRdr.api.dll", SCNapi.class);
//        SCNapi scn = SCNapi.INSTANCE;
        // Get Handle from Scaner
        ScannerClass.scanerHandle = scn.SCNCreate(Boolean.TRUE);
        System.out.println("work - " + ScannerClass.scanerHandle);
        
        short[] Status = new short[1];

//        System.out.println("SCNgetStatus - " + scn.SCNGetStatus(ScannerClass.scanerHandle, Status));
        if (scn.SCNGetStatus(ScannerClass.scanerHandle, Status)) {
            System.out.println("SCNgetStatus - " + Status);
        } else {
            System.out.println("SCNgetStatus - " + Status);
        }
//        ByteBuffer Progr = ByteBuffer.allocate(1);
//        Byte Progr = new Byte("1");
//        Progr.parseByte("0x00");
//        .put((byte) 0x00);
//        ByteBuffer CRC = ByteBuffer.allocate(1);
//        Byte CRC = new Byte(1);
//        CRC.parseByte("0x00");

//        if (scn.SCNGetFWRelease(ScannerClass.scanerHandle, Progr, CRC, outBuffer, outSize, bytesReturned)) {
//            System.out.println("bytes - " + bytesReturned.getByte(0));
//        } else {
//            System.out.println("Error SCNGetFWRelease");
//        }

        // RunApplication
        if (scn.SCNRunApplication(ScannerClass.scanerHandle)) {
            System.out.println("Runned");
        } else {
            System.out.println("Error");
        }

        // Closed Handle after work with scaner
        if (scn.SCNClose(ScannerClass.scanerHandle)) {
            System.out.println("Closed");
        }
    }
}
