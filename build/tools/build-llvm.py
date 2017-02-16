#!/usr/bin/env python
#
# Copyright (C) 2015 The Android Open Source Project
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
"""Packages the platform's LLVM for the NDK."""
import os
import shutil
import site
import subprocess
import sys

site.addsitedir(os.path.join(os.path.dirname(__file__), '../lib'))

import build_support  # pylint: disable=import-error


def get_llvm_prebuilt_path(host):
    rel_prebuilt_path = 'prebuilts/clang/host/{}'.format(host)
    prebuilt_path = os.path.join(build_support.android_path(),
                                 rel_prebuilt_path)
    if not os.path.isdir(prebuilt_path):
        sys.exit('Could not find prebuilt LLVM at {}'.format(prebuilt_path))
    return prebuilt_path


def main(args):
    LLVM_VERSION = 'clang-2812033'

    host = args.host
    package_dir = args.dist_dir

    # The 32-bit Windows Clang is a part of the 64-bit Clang package in
    # prebuilts/clang.
    os_name = host
    if os_name == 'windows64':
        os_name = 'windows'
    prebuilt_path = get_llvm_prebuilt_path(os_name + '-x86')

    if host == 'darwin':
        host = 'darwin-x86_64'
    elif host == 'linux':
        host = 'linux-x86_64'
    elif host == 'windows':
        host = 'windows'
    elif host == 'windows64':
        host = 'windows-x86_64'

    if host == 'windows':
        # We need to replace clang.exe with clang_32.exe. Copy clang into a
        # temporary directory for rearranging.
        build_path = os.path.join(args.out_dir, 'clang/windows')
        if os.path.exists(build_path):
            shutil.rmtree(build_path)
        install_path = os.path.join(build_path, LLVM_VERSION)
        os.makedirs(build_path)
        shutil.copytree(os.path.join(prebuilt_path, LLVM_VERSION),
                        install_path)
        os.rename(os.path.join(install_path, 'bin/clang_32.exe'),
                  os.path.join(install_path, 'bin/clang.exe'))
        # clang++.exe is not a symlink in the Windows package. Need to copy to
        # there as well.
        shutil.copy2(os.path.join(install_path, 'bin/clang.exe'),
                     os.path.join(install_path, 'bin/clang++.exe'))
        prebuilt_path = build_path

    package_name = 'llvm-{}.zip'.format(host)
    package_path = os.path.join(package_dir, package_name)
    if os.path.exists(package_path):
        os.unlink(package_path)
    os.chdir(prebuilt_path)
    args = ['zip', '-9qr', package_path, LLVM_VERSION]
    if not host.startswith('windows'):
        args.append('--symlinks')
    subprocess.check_call(args)

if __name__ == '__main__':
    build_support.run(main)
