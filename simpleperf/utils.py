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

"""utils.py: export utility functions.
"""

from __future__ import print_function
import logging
import os.path
import subprocess
import sys

def get_script_dir():
    return os.path.dirname(os.path.realpath(__file__))


def is_windows():
    return sys.platform == 'win32' or sys.platform == 'cygwin'


def log_debug(msg):
    logging.debug(msg)


def log_info(msg):
    logging.info(msg)


def log_warning(msg):
    logging.warning(msg)


def log_fatal(msg):
    raise Exception(msg)


def get_target_binary_path(arch, binary_name):
    if arch == 'aarch64':
        arch = 'arm64'
    arch_dir = os.path.join(get_script_dir(), "bin", "android", arch)
    if not os.path.isdir(arch_dir):
        log_fatal("can't find arch directory: %s" % arch_dir)
    binary_path = os.path.join(arch_dir, binary_name)
    if not os.path.isfile(binary_path):
        log_fatal("can't find binary: %s" % binary_path)
    return binary_path


def get_host_binary_path(binary_name):
    dir = os.path.join(get_script_dir(), 'bin')
    if is_windows():
        if binary_name.endswith('.so'):
            binary_name = binary_name[0:-3] + '.dll'
        dir = os.path.join(dir, 'windows')
    elif sys.platform == 'darwin': # OSX
        if binary_name.endswith('.so'):
            binary_name = binary_name[0:-3] + '.dylib'
        dir = os.path.join(dir, 'darwin')
    else:
        dir = os.path.join(dir, 'linux')
    dir = os.path.join(dir, 'x86_64' if sys.maxsize > 2 ** 32 else 'x86')
    binary_path = os.path.join(dir, binary_name)
    if not os.path.isfile(binary_path):
        log_fatal("can't find binary: %s" % binary_path)
    return binary_path


class AdbHelper(object):
    def __init__(self, adb_path):
        self.adb_path = adb_path


    def run(self, adb_args):
        return self.run_and_return_output(adb_args)[0]


    def run_and_return_output(self, adb_args):
        adb_args = [self.adb_path] + adb_args
        log_debug('run adb cmd: %s' % adb_args)
        subproc = subprocess.Popen(adb_args, stdout=subprocess.PIPE)
        (stdoutdata, _) = subproc.communicate()
        result = (subproc.returncode == 0)
        if stdoutdata:
            log_debug(stdoutdata)
        log_debug('run adb cmd: %s  [result %s]' % (adb_args, result))
        return (result, stdoutdata)


    def check_run(self, adb_args):
        self.check_run_and_return_output(adb_args)


    def check_run_and_return_output(self, adb_args):
        result, stdoutdata = self.run_and_return_output(adb_args)
        if not result:
            log_fatal('run "adb %s" failed' % adb_args)
        return stdoutdata


    def switch_to_root(self):
        result, stdoutdata = self.run_and_return_output(['shell', 'whoami'])
        if not result:
            return False
        if stdoutdata.find('root') != -1:
            return True
        build_type = self.get_property('ro.build.type')
        if build_type == 'user':
            return False
        self.run(['root'])
        result, stdoutdata = self.run_and_return_output(['shell', 'whoami'])
        if result and stdoutdata.find('root') != -1:
            return True
        return False

    def get_property(self, name):
        result, stdoutdata = self.run_and_return_output(['shell', 'getprop', name])
        if not result:
            return None
        return stdoutdata


    def set_property(self, name, value):
        return self.run(['shell', 'setprop', name, value])


def load_config(config_file):
    if not os.path.exists(config_file):
        log_fatal("can't find config_file: %s" % config_file)
    config = {}
    execfile(config_file, config)
    return config


logging.getLogger().setLevel(logging.DEBUG)
