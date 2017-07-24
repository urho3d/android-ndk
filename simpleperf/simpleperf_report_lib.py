#!/usr/bin/env python
#
# Copyright (C) 2016 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

"""simpleperf_report_lib.py: a python wrapper of libsimpleperf_report.so.
   Used to access samples in perf.data.

"""

import ctypes as ct
import os
import subprocess
import sys
import unittest
from utils import *


def _get_native_lib():
    return get_host_binary_path('libsimpleperf_report.so')


def _is_null(p):
    return ct.cast(p, ct.c_void_p).value is None


def _char_pt(str):
    if sys.version_info < (3, 0):
        return str
    # In python 3, str are wide strings whereas the C api expects 8 bit strings, hence we have to convert
    # For now using utf-8 as the encoding.
    return str.encode('utf-8')


def _char_pt_to_str(char_pt):
    if sys.version_info < (3, 0):
        return char_pt
    return char_pt.decode('utf-8')


class SampleStruct(ct.Structure):
    _fields_ = [('ip', ct.c_uint64),
                ('pid', ct.c_uint32),
                ('tid', ct.c_uint32),
                ('thread_comm', ct.c_char_p),
                ('time', ct.c_uint64),
                ('in_kernel', ct.c_uint32),
                ('cpu', ct.c_uint32),
                ('period', ct.c_uint64)]


class EventStruct(ct.Structure):
    _fields_ = [('name', ct.c_char_p)]


class MappingStruct(ct.Structure):
    _fields_ = [('start', ct.c_uint64),
                ('end', ct.c_uint64),
                ('pgoff', ct.c_uint64)]


class SymbolStruct(ct.Structure):
    _fields_ = [('dso_name', ct.c_char_p),
                ('vaddr_in_file', ct.c_uint64),
                ('symbol_name', ct.c_char_p),
                ('symbol_addr', ct.c_uint64),
                ('mapping', ct.POINTER(MappingStruct))]


class CallChainEntryStructure(ct.Structure):
    _fields_ = [('ip', ct.c_uint64),
                ('symbol', SymbolStruct)]


class CallChainStructure(ct.Structure):
    _fields_ = [('nr', ct.c_uint32),
                ('entries', ct.POINTER(CallChainEntryStructure))]


# convert char_p to str for python3.
class SampleStructUsingStr(object):
    def __init__(self, sample):
        self.ip = sample.ip
        self.pid = sample.pid
        self.tid = sample.tid
        self.thread_comm = _char_pt_to_str(sample.thread_comm)
        self.time = sample.time
        self.in_kernel = sample.in_kernel
        self.cpu = sample.cpu
        self.period = sample.period


class EventStructUsingStr(object):
    def __init__(self, event):
        self.name = _char_pt_to_str(event.name)


class SymbolStructUsingStr(object):
    def __init__(self, symbol):
        self.dso_name = _char_pt_to_str(symbol.dso_name)
        self.vaddr_in_file = symbol.vaddr_in_file
        self.symbol_name = _char_pt_to_str(symbol.symbol_name)
        self.symbol_addr = symbol.symbol_addr
        self.mapping = symbol.mapping


class CallChainEntryStructureUsingStr(object):
    def __init__(self, entry):
        self.ip = entry.ip
        self.symbol = SymbolStructUsingStr(entry.symbol)


class CallChainStructureUsingStr(object):
    def __init__(self, callchain):
        self.nr = callchain.nr
        self.entries = []
        for i in range(self.nr):
            self.entries.append(CallChainEntryStructureUsingStr(callchain.entries[i]))


class ReportLibStructure(ct.Structure):
    _fields_ = []


class ReportLib(object):

    def __init__(self, native_lib_path=None):
        if native_lib_path is None:
            native_lib_path = _get_native_lib()

        self._load_dependent_lib()
        self._lib = ct.CDLL(native_lib_path)
        self._CreateReportLibFunc = self._lib.CreateReportLib
        self._CreateReportLibFunc.restype = ct.POINTER(ReportLibStructure)
        self._DestroyReportLibFunc = self._lib.DestroyReportLib
        self._SetLogSeverityFunc = self._lib.SetLogSeverity
        self._SetSymfsFunc = self._lib.SetSymfs
        self._SetRecordFileFunc = self._lib.SetRecordFile
        self._SetKallsymsFileFunc = self._lib.SetKallsymsFile
        self._ShowIpForUnknownSymbolFunc = self._lib.ShowIpForUnknownSymbol
        self._GetNextSampleFunc = self._lib.GetNextSample
        self._GetNextSampleFunc.restype = ct.POINTER(SampleStruct)
        self._GetEventOfCurrentSampleFunc = self._lib.GetEventOfCurrentSample
        self._GetEventOfCurrentSampleFunc.restype = ct.POINTER(EventStruct)
        self._GetSymbolOfCurrentSampleFunc = self._lib.GetSymbolOfCurrentSample
        self._GetSymbolOfCurrentSampleFunc.restype = ct.POINTER(SymbolStruct)
        self._GetCallChainOfCurrentSampleFunc = self._lib.GetCallChainOfCurrentSample
        self._GetCallChainOfCurrentSampleFunc.restype = ct.POINTER(
            CallChainStructure)
        self._GetBuildIdForPathFunc = self._lib.GetBuildIdForPath
        self._GetBuildIdForPathFunc.restype = ct.c_char_p
        self._instance = self._CreateReportLibFunc()
        assert(not _is_null(self._instance))

        self.convert_to_str = (sys.version_info >= (3, 0))

    def _load_dependent_lib(self):
        # As the windows dll is built with mingw we need to also find "libwinpthread-1.dll".
        # Load it before libsimpleperf_report.dll if it does exist in the same folder as this script.
        if is_windows():
            libwinpthread_path = os.path.join(get_script_dir(), "libwinpthread-1.dll")
            if os.path.exists(libwinpthread_path):
                self._libwinpthread = ct.CDLL(libwinpthread_path)
            else:
                log_fatal('%s is missing' % libwinpthread_path)

    def Close(self):
        if self._instance is None:
            return
        self._DestroyReportLibFunc(self._instance)
        self._instance = None

    def SetLogSeverity(self, log_level='info'):
        """ Set log severity of native lib, can be verbose,debug,info,error,fatal."""
        cond = self._SetLogSeverityFunc(self.getInstance(), _char_pt(log_level))
        self._check(cond, "Failed to set log level")

    def SetSymfs(self, symfs_dir):
        """ Set directory used to find symbols."""
        cond = self._SetSymfsFunc(self.getInstance(), _char_pt(symfs_dir))
        self._check(cond, "Failed to set symbols directory")

    def SetRecordFile(self, record_file):
        """ Set the path of record file, like perf.data."""
        cond = self._SetRecordFileFunc(self.getInstance(), _char_pt(record_file))
        self._check(cond, "Failed to set record file")

    def ShowIpForUnknownSymbol(self):
        self._ShowIpForUnknownSymbolFunc(self.getInstance())

    def SetKallsymsFile(self, kallsym_file):
        """ Set the file path to a copy of the /proc/kallsyms file (for off device decoding) """
        cond = self._SetKallsymsFileFunc(self.getInstance(), _char_pt(kallsym_file))
        self._check(cond, "Failed to set kallsyms file")

    def GetNextSample(self):
        sample = self._GetNextSampleFunc(self.getInstance())
        if _is_null(sample):
            return None
        if self.convert_to_str:
            return SampleStructUsingStr(sample[0])
        return sample[0]

    def GetEventOfCurrentSample(self):
        event = self._GetEventOfCurrentSampleFunc(self.getInstance())
        assert(not _is_null(event))
        if self.convert_to_str:
            return EventStructUsingStr(event[0])
        return event[0]

    def GetSymbolOfCurrentSample(self):
        symbol = self._GetSymbolOfCurrentSampleFunc(self.getInstance())
        assert(not _is_null(symbol))
        if self.convert_to_str:
            return SymbolStructUsingStr(symbol[0])
        return symbol[0]

    def GetCallChainOfCurrentSample(self):
        callchain = self._GetCallChainOfCurrentSampleFunc(self.getInstance())
        assert(not _is_null(callchain))
        if self.convert_to_str:
            return CallChainStructureUsingStr(callchain[0])
        return callchain[0]

    def GetBuildIdForPath(self, path):
        build_id = self._GetBuildIdForPathFunc(self.getInstance(), _char_pt(path))
        assert(not _is_null(build_id))
        return _char_pt_to_str(build_id)

    def getInstance(self):
        if self._instance is None:
            raise Exception("Instance is Closed")
        return self._instance

    def _check(self, cond, failmsg):
        if not cond:
            raise Exception(failmsg)


class TestReportLib(unittest.TestCase):
    def setUp(self):
        self.perf_data_path = os.path.join(os.path.dirname(get_script_dir()),
                                           'testdata', 'perf_with_symbols.data')
        if not os.path.isfile(self.perf_data_path):
            raise Exception("can't find perf_data at %s" % self.perf_data_path)
        self.report_lib = ReportLib()
        self.report_lib.SetRecordFile(self.perf_data_path)

    def tearDown(self):
        self.report_lib.Close()

    def test_build_id(self):
        build_id = self.report_lib.GetBuildIdForPath('/data/t2')
        self.assertEqual(build_id, '0x70f1fe24500fc8b0d9eb477199ca1ca21acca4de')

    def test_symbol_addr(self):
        found_func2 = False
        while True:
            sample = self.report_lib.GetNextSample()
            if sample is None:
                break
            symbol = self.report_lib.GetSymbolOfCurrentSample()
            if symbol.symbol_name == 'func2(int, int)':
                found_func2 = True
                self.assertEqual(symbol.symbol_addr, 0x4004ed)
        self.assertTrue(found_func2)

    def test_sample(self):
        found_sample = False
        while True:
            sample = self.report_lib.GetNextSample()
            if sample is None:
                break
            if sample.ip == 0x4004ff and sample.time == 7637889424953:
                found_sample = True
                self.assertEqual(sample.pid, 15926)
                self.assertEqual(sample.tid, 15926)
                self.assertEqual(sample.thread_comm, 't2')
                self.assertEqual(sample.cpu, 5)
                self.assertEqual(sample.period, 694614)
                event = self.report_lib.GetEventOfCurrentSample()
                self.assertEqual(event.name, 'cpu-cycles')
                callchain = self.report_lib.GetCallChainOfCurrentSample()
                self.assertEqual(callchain.nr, 0)
        self.assertTrue(found_sample)


def main():
    test_all = True
    if len(sys.argv) > 1 and sys.argv[1] == '--test-one':
        test_all = False
        del sys.argv[1]

    if test_all:
        subprocess.check_call(['python', os.path.realpath(__file__), '--test-one'])
        subprocess.check_call(['python3', os.path.realpath(__file__), '--test-one'])
    else:
        sys.exit(unittest.main())


if __name__ == '__main__':
    main()