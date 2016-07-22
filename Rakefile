#
# Copyright (c) 2008-2016 the Urho3D project.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

task default: %w[ndk_update]

# Usage: NOT intended to be used manually
desc 'Update Android NDK in the master branch'
task :ndk_update do
    exit 1 if `bash -c 'mem=($(free -m |head -2 |tail -1)); echo ${mem[6]}'` == 0     # Terminate prematurely when this task is run inside a bad Travis CI VM
    system 'sudo apt-get update -q -y && sudo apt-get install -q -y --no-install-recommends libc6:i386 lib32stdc++6' or abort 'Failed to install 32-bit shared dependencies libs'
    system 'wget http://dl.google.com/android/repository/android-ndk-r$VERSION-linux-x86_64.zip && echo Installing... && unzip android-ndk*.zip >/dev/null && rm android-ndk*.zip && ln -s android-ndk* android-ndk-new' or abort 'Failed to download and install the NDK'
    system 'git clone --depth=1 https://github.com/urho3d/android-ndk.git' or abort 'Failed to clone existing NDK installation'
    system 'echo Syncing... && rsync -a --delete -q --exclude .git android-ndk-new/ android-ndk' or abort 'Failed to rsync new NDK installation'
    system "echo Committing... && cd android-ndk && git config user.name '#{ENV['GIT_NAME']}' && git config user.email '#{ENV['GIT_EMAIL']}' && git remote set-url --push origin https://#{ENV['GH_TOKEN']}@github.com/urho3d/android-ndk.git && git add -Af . && ( git commit -q -m \"Travis CI: Android NDK installation at #{Time.now.utc}.\" || true) && git push -q >/dev/null 2>&1" or abort 'Failed to push new NDK installation'
    system "echo Stripping... && bash -c 'cd android-ndk && git checkout -b strip && rm -rf platforms/android-{12,13,14,15,16,17,18,19,22,23,24} prebuilt shader-tools sources/third_party toolchains/mips* ndk* && git add -A . && ( git commit -q -m \"Travis CI: strip Android NDK.\" || true) && git push -qf -u origin strip >/dev/null 2>&1'" or abort 'Failed to strip Android NDK'
end
