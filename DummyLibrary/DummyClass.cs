using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using DllExporter;

namespace DummyLibrary
{
    [StructLayout(LayoutKind.Sequential)]
    public struct DummyStruct
    {
        public short a;
        public ulong b;
        public byte c;
        public double d;
    }

    public class DummyClass
    {
        [DllExport]
        public static void DummyMethod() { }

        [DllExport(EntryPoint = "SayHello")]
        [return:MarshalAs(UnmanagedType.LPTStr)]
        public static string Hello([MarshalAs(UnmanagedType.LPTStr)]string name)
        {
            return string.Format("Hello from .NET assembly, {0}! Howge added this", name);
        }

        [DllExport]
        public static int Add([MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)]int[] values, int count)
        {
            int result = 0;

            for (int i = 0; i < values.Length; i++)
                result += values[i];

            return result;
        }

        [DllExport]
        public static DummyStruct TestStruct() { return new DummyStruct { a = 1, b = 2, c = 3, d = 4 }; }

        [DllExport]
        public static void TestStructRef(ref DummyStruct dummyStruct)
        {
            dummyStruct.a += 5;
            dummyStruct.b += 6;
            dummyStruct.c += 7;
            dummyStruct.d += 8;
        }
    }
}
