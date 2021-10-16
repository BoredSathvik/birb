using System;
using System.Diagnostics;
using System.IO;
using System.Security.AccessControl;
using System.Security.Principal;
using System.Threading;

namespace Injector
{
    public class Injector
    {
        public static Process targetProc;
        public static IntPtr pHandle;

        public static void RunBackend()
        {
            Console.WriteLine("Credits to Lunity https://github.com/DisabledMallis/Lunity");
            awaitProcess("Minecraft.Windows");
            Console.WriteLine("Process found");
            Console.WriteLine("Applying ALL_APPLICATION_PACKAGES");
            applyAppPackages("birb.dll");
            Console.WriteLine("Permissions applied");
            Console.WriteLine("Injecting...");
            InjectDll("birb.dll");
            Console.WriteLine("Injection complete");
        }

        public static void awaitProcess(string procName)
        {
            while (true)
            {
                Process[] possiblilties = Process.GetProcessesByName(procName);
                if (possiblilties.Length == 0)
                {
                    Console.WriteLine("Opening minecraft...");
                    Process.Start("minecraft://");
                    Thread.Sleep(5000);

                    possiblilties = Process.GetProcessesByName(procName);
                    if (possiblilties.Length == 0)
                    {
                        throw new Exception("Minecraft not found, install minecraft maybe?");
                    }

                    continue;
                }
                Process temptargetProc = possiblilties[0];
                targetProc = temptargetProc;
                pHandle = Win32.OpenProcess(0x1F0FFF, true, targetProc.Id);
                break;
            }
        }

        public static void applyAppPackages(string file)
        {
            FileInfo fInfo = new FileInfo(file);
            FileSecurity fSecurity = fInfo.GetAccessControl();
            fSecurity.AddAccessRule(new FileSystemAccessRule(new SecurityIdentifier("S-1-15-2-1"), FileSystemRights.FullControl, InheritanceFlags.None, PropagationFlags.NoPropagateInherit, AccessControlType.Allow));
            fInfo.SetAccessControl(fSecurity);
        }

        //Code from https://github.com/erfg12/memory.dll/blob/master/Memory/memory.cs
        public static void InjectDll(string strDllName)
        {
            IntPtr bytesout;

            FileInfo f = new FileInfo(strDllName);
            strDllName = f.FullName;

            foreach (ProcessModule pm in targetProc.Modules)
            {
                if (pm.FileName == strDllName)
                {
                    throw new Exception("");
                };
            }

            if (!targetProc.Responding)
                return;

            int lenWrite = strDllName.Length + 1;
            UIntPtr allocMem = Win32.VirtualAllocEx(pHandle, (UIntPtr)null, (uint)lenWrite, 0x00001000 | 0x00002000, 0x04);

            Win32.WriteProcessMemory(pHandle, allocMem, strDllName, (UIntPtr)lenWrite, out bytesout);
            UIntPtr injector = Win32.GetProcAddress(Win32.GetModuleHandle("kernel32.dll"), "LoadLibraryA");

            if (injector == null)
                return;

            IntPtr hThread = Win32.CreateRemoteThread(pHandle, (IntPtr)null, 0, injector, allocMem, 0, out bytesout);
            if (hThread == null)
                return;

            int Result = Win32.WaitForSingleObject(hThread, 10 * 1000);
            if (Result == 0x00000080L || Result == 0x00000102L)
            {
                if (hThread != null)
                    Win32.CloseHandle(hThread);
                return;
            }
            Win32.VirtualFreeEx(pHandle, allocMem, (UIntPtr)0, 0x8000);

            if (hThread != null)
                Win32.CloseHandle(hThread);

            return;
        }
    }
}