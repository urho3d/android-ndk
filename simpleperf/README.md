# Introduction of simpleperf
## What is simpleperf
Simpleperf is a native profiling tool for Android. Its command-line interface
supports broadly the same options as the linux-tools perf, but also supports
various Android-specific improvements.

Simpleperf is part of the Android Open Source Project. The source code is at
https://android.googlesource.com/platform/system/extras/+/master/simpleperf/.
Bugs and feature requests can be submitted at
http://github.com/android-ndk/ndk/issues.

## How simpleperf works
Modern cpus have a hardware component called the performance monitoring unit
(PMU). The PMU has several hardware counters, counting events like how many cpu
cycles have happened, how many instructions have executed, or how many cache
misses have happened.

The Linux kernel wraps these hardware counters into hardware perf events. In
addition, the Linux kernel also provides hardware independent software events
and tracepoint events. The Linux kernel exposes all this to userspace via the
perf_event_open system call, which simpleperf uses.

Simpleperf has three main functions: stat, record and report.

The stat command gives a summary of how many events have happened in the
profiled processes in a time period. Here’s how it works:
1. Given user options, simpleperf enables profiling by making a system call to
linux kernel.
2. Linux kernel enables counters while scheduling on the profiled processes.
3. After profiling, simpleperf reads counters from linux kernel, and reports a
counter summary.

The record command records samples of the profiled process in a time period.
Here’s how it works:
1. Given user options, simpleperf enables profiling by making a system call to
linux kernel.
2. Simpleperf creates mapped buffers between simpleperf and linux kernel.
3. Linux kernel enable counters while scheduling on the profiled processes.
4. Each time a given number of events happen, linux kernel dumps a sample to a
mapped buffer.
5. Simpleperf reads samples from the mapped buffers and generates perf.data.

The report command reads a "perf.data" file and any shared libraries used by
the profiled processes, and outputs a report showing where the time was spent.

## Main simpleperf commands
Simpleperf supports several subcommands, including list, stat, record, report.
Each subcommand supports different options. This section only covers the most
important subcommands and options. To see all subcommands and options,
use --help.

    # List all subcommands.
    $simpleperf --help

    # Print help message for record subcommand.
    $simpleperf record --help

### simpleperf list
simpleperf list is used to list all events available on the device. Different
devices may support different events because of differences in hardware and
kernel.

    $simpleperf list
    List of hw-cache events:
      branch-loads
      ...
    List of hardware events:
      cpu-cycles
      instructions
      ...
    List of software events:
      cpu-clock
      task-clock
      ...

### simpleperf stat
simpleperf stat is used to get an event counter summary of the profiled program.
By passing options, we can select which events to use, which processes/threads
to monitor, and how long to monitor. Below is an example.

    # Stat using default events (cpu-cycles,instructions,...), and monitor
    # process 7394 for 10 seconds.
    $simpleperf stat -p 7394 --duration 10
    Performance counter statistics:

     1,320,496,145  cpu-cycles         # 0.131736 GHz                     (100%)
       510,426,028  instructions       # 2.587047 cycles per instruction  (100%)
         4,692,338  branch-misses      # 468.118 K/sec                    (100%)
    886.008130(ms)  task-clock         # 0.088390 cpus used               (100%)
               753  context-switches   # 75.121 /sec                      (100%)
               870  page-faults        # 86.793 /sec                      (100%)

    Total test time: 10.023829 seconds.

#### Select events
We can select which events to use via -e option. Below are examples:

    # Stat event cpu-cycles.
    $simpleperf stat -e cpu-cycles -p 11904 --duration 10

    # Stat event cache-references and cache-misses.
    $simpleperf stat -e cache-references,cache-misses -p 11904 --duration 10

When running the stat command, if the number of hardware events is larger than
the number of hardware counters available in the PMU, the kernel shares hardware
counters between events, so each event is only monitored for part of the total
time. In the example below, there is a percentage at the end of each row,
showing the percentage of the total time that each event was actually monitored.

    # Stat using event cache-references, cache-references:u,....
    $simpleperf stat -p 7394 -e     cache-references,cache-references:u,cache-references:k,cache-misses,cache-misses:u,cache-misses:k,instructions --duration 1
    Performance counter statistics:

    4,331,018  cache-references     # 4.861 M/sec    (87%)
    3,064,089  cache-references:u   # 3.439 M/sec    (87%)
    1,364,959  cache-references:k   # 1.532 M/sec    (87%)
       91,721  cache-misses         # 102.918 K/sec  (87%)
       45,735  cache-misses:u       # 51.327 K/sec   (87%)
       38,447  cache-misses:k       # 43.131 K/sec   (87%)
    9,688,515  instructions         # 10.561 M/sec   (89%)

    Total test time: 1.026802 seconds.

In the example above, each event is monitored about 87% of the total time. But
there is no guarantee that any pair of events are always monitored at the same
time. If we want to have some events monitored at the same time, we can use
--group option. Below is an example.

    # Stat using event cache-references, cache-references:u,....
    $simpleperf stat -p 7394 --group cache-references,cache-misses --group cache-references:u,cache-misses:u --group cache-references:k,cache-misses:k -e instructions --duration 1
    Performance counter statistics:

    3,638,900  cache-references     # 4.786 M/sec          (74%)
       65,171  cache-misses         # 1.790953% miss rate  (74%)
    2,390,433  cache-references:u   # 3.153 M/sec          (74%)
       32,280  cache-misses:u       # 1.350383% miss rate  (74%)
      879,035  cache-references:k   # 1.251 M/sec          (68%)
       30,303  cache-misses:k       # 3.447303% miss rate  (68%)
    8,921,161  instructions         # 10.070 M/sec         (86%)

    Total test time: 1.029843 seconds.

#### Select target to monitor
We can select which processes or threads to monitor via -p option or -t option.
Monitoring a process is the same as monitoring all threads in the process.
Simpleperf can also fork a child processing running a new command and monitor
the child process. Below are examples.

    # Stat process 11904 and 11905.
    $simpleperf stat -p 11904,11905 --duration 10

    # Stat thread 11904 and 11905.
    $simpleperf stat -t 11904,11905 --duration 10

    # Start a child process running `ls`, and stat it.
    $simpleperf stat ls

#### Decide how long to monitor
When monitoring exist threads, we can use --duration option to decide how long
to monitor. When monitoring a child process running a new command, simpleperf
monitors until the child process ends. And we can use Ctrl-C to stop monitoring
at any time. Below are examples.

    # Stat process 11904 for 10 seconds.
    $simpleperf stat -p 11904 --duration 10

    # Stat until the child process running `ls` finishes.
    $simpleperf stat ls

    # Stop monitoring using Ctrl-C.
    $simpleperf stat -p 11904 --duration 10
    ^C

### simpleperf record
simpleperf record is used to dump records of the profiled program. By passing
options, we can select which events to use, which processes/threads to monitor,
the frequency to dump records, how long to monitor, and where to store records.

    # Record on process 7394 for 10 seconds, using default event (cpu-cycles),
    # using default sample frequency (4000 samples per second), writing records
    # to perf.data.
    $simpleperf record -p 7394 --duration 10
    simpleperf I 07-11 21:44:11 17522 17522 cmd_record.cpp:316] Samples recorded: 21430. Samples lost: 0.

#### Select events
In most cases, the cpu-cycles event is used to evaluate consumed cpu time.
As a hardware event, it is both accurate and efficient. We can also use other
events via -e option. Below is an example.

    # Record using event instructions.
    $simpleperf record -e instructions -p 11904 --duration 10

#### Select target to monitor
The way to select target in record command is similar to that in stat command.
Below are examples.

    # Record process 11904 and 11905.
    $simpleperf record -p 11904,11905 --duration 10

    # Record thread 11904 and 11905.
    $simpleperf record -t 11904,11905 --duration 10

    # Record a child process running `ls`.
    $simpleperf record ls

#### Set the frequency to record
We can set the frequency to dump records via the -f or -c options. For example,
-f 4000 means dumping approximately 4000 records every second the monitored
thread runs. If a monitored thread runs 0.2s in one second (it can be preempted
or blocked in other times), simpleperf dumps about 4000 * 0.2 / 1.0 = 800
records every second. Another way is using -c option. For example, -c 10000
means dumping one record whenever 10000 events happen. Below are examples.

    # Record with sample frequency 1000: sample 1000 times every second running.
    $simpleperf record -f 1000 -p 11904,11905 --duration 10

    # Record with sample period 100000: sample 1 time every 100000 events.
    $simpleperf record -c 100000 -t 11904,11905 --duration 10

#### Decide how long to monitor
The way to decide how long to monitor in record command is similar to that in
stat command. Below are examples.

    # Record process 11904 for 10 seconds.
    $simpleperf record -p 11904 --duration 10

    # Record until the child process running `ls` finishes.
    $simpleperf record ls

    # Stop monitoring using Ctrl-C.
    $simpleperf record -p 11904 --duration 10
    ^C

#### Set the path to store records
By default, simpleperf stores records in perf.data in current directory. We can
use -o option to set the path to store records. Below is an example.

    # Write records to data/perf2.data.
    $simpleperf record -p 11904 -o data/perf2.data --duration 10

### simpleperf report
simpleperf report is used to report based on perf.data generated by simpleperf
record command. Report command groups records into different sample entries,
sorts sample entries based on how many events each sample entry contains, and
prints out each sample entry. By passing options, we can select where to find
perf.data and executable binaries used by the monitored program, filter out
uninteresting records, and decide how to group records.

Below is an example. Records are grouped into 4 sample entries, each entry is
a row. There are several columns, each column showing piece of information
belong to a sample entry. The first column is Overhead, which shows the
percentage of events inside current sample entry in total event count. As the
perf event is cpu-cycles, the overhead can be seen as the percentage of cpu
time used in each function.

    # Reports perf.data, using only records sampled in libsudo-game-jni.so,
    # grouping records using thread name(comm), process id(pid), thread id(tid),
    # function name(symbol), and showing sample count for each row.
    $simpleperf report --dsos /data/app/com.example.sudogame-2/lib/arm64/libsudo-game-jni.so --sort comm,pid,tid,symbol -n
    Cmdline: /data/data/com.example.sudogame/simpleperf record -p 7394 --duration 10
    Arch: arm64
    Event: cpu-cycles (type 0, config 0)
    Samples: 28235
    Event count: 546356211

    Overhead  Sample  Command    Pid   Tid   Symbol
    59.25%    16680   sudogame  7394  7394  checkValid(Board const&, int, int)
    20.42%    5620    sudogame  7394  7394  canFindSolution_r(Board&, int, int)
    13.82%    4088    sudogame  7394  7394  randomBlock_r(Board&, int, int, int, int, int)
    6.24%     1756    sudogame  7394  7394  @plt

#### Set the path to read records
By default, simpleperf reads perf.data in current directory. We can use -i
option to select another file to read records.

    $simpleperf report -i data/perf2.data

#### Set the path to find executable binaries
If reporting function symbols, simpleperf needs to read executable binaries
used by the monitored processes to get symbol table and debug information. By
default, the paths are the executable binaries used by monitored processes while
recording. However, these binaries may not exist when reporting or not contain
symbol table and debug information. So we can use --symfs to redirect the paths.
Below is an example.

    $simpleperf report
    # In this case, when simpleperf wants to read executable binary /A/b,
    # it reads file in /A/b.

    $simpleperf report --symfs /debug_dir
    # In this case, when simpleperf wants to read executable binary /A/b,
    # it prefers file in /debug_dir/A/b to file in /A/b.

#### Filter records
When reporting, it happens that not all records are of interest. Simpleperf
supports five filters to select records of interest. Below are examples.

    # Report records in threads having name sudogame.
    $simpleperf report --comms sudogame

    # Report records in process 7394 or 7395
    $simpleperf report --pids 7394,7395

    # Report records in thread 7394 or 7395.
    $simpleperf report --tids 7394,7395

    # Report records in libsudo-game-jni.so.
    $simpleperf report --dsos /data/app/com.example.sudogame-2/lib/arm64/libsudo-game-jni.so

    # Report records in function checkValid or canFindSolution_r.
    $simpleperf report --symbols "checkValid(Board const&, int, int);canFindSolution_r(Board&, int, int)"

#### Decide how to group records into sample entries
Simpleperf uses --sort option to decide how to group sample entries. Below are
examples.

    # Group records based on their process id: records having the same process
    # id are in the same sample entry.
    $simpleperf report --sort pid

    # Group records based on their thread id and thread comm: records having
    # the same thread id and thread name are in the same sample entry.
    $simpleperf report --sort tid,comm

    # Group records based on their binary and function: records in the same
    # binary and function are in the same sample entry.
    $simpleperf report --sort dso,symbol

    # Default option: --sort comm,pid,tid,dso,symbol. Group records in the same
    # thread, and belong to the same function in the same binary.
    $simpleperf report

## Features of simpleperf
Simpleperf works similar to linux-tools-perf, but it has following improvements:
1. Aware of Android environment. Simpleperf handles some Android specific
situations when profiling. For example, it can profile embedded shared libraries
in apk, read symbol table and debug information from .gnu_debugdata section. If
possible, it gives suggestions when meeting errors, like how to disable
perf_harden to enable profiling.
2. Support unwinding while recording. If we want to use -g option to record and
report call-graph of a program, We need to dump user stack and register set in
each record, and then unwind the stack to find the call chain. Simpleperf
supports unwinding while recording, so it doesn’t need to store user stack in
perf.data. So we can profile for a longer time with limited space on device.
3. Build static binaries. Simpleperf is a static binary. So it doesn’t need
supported shared libraries to run. It means there is no limitation of Android
version that simpleperf can run on, although some devices don’t support
profiling.

# Steps to profile native libraries
After introducing simpleperf, this section uses a simple example to show how to
profile jni native libraries on Android using simpleperf. The example profiles
an app called com.example.sudogame, which uses a jni native library
sudo-game-jni.so. We focus on sudo-game-jni.so, not the java code or system
libraries.

## 1. Run debug version of the app on device
We need to run debug version of the app, because we can’t use *run-as* for non
debuggable apps.

## 2. Download simpleperf to the app's directory
Use *uname* to find the architecture on device

    $adb shell uname -m
    aarch64

So we should download simpleperf in arm64 directory to device.

    $adb push device/arm64/simpleperf /data/local/tmp
    $adb shell run-as com.example.sudogame cp /data/local/tmp/simpleperf .
    $adb shell run-as com.example.sudogame chmod a+x simpleperf
    $adb shell run-as com.example.sudogame ls -l
    -rwxrwxrwx 1 u0_a90 u0_a90 3059208 2016-01-01 10:40 simpleperf

Note that some apps use arm native libraries even on arm64 devices (We can
verify this by checking /proc/<process\_id\_of\_app>/maps). In that case, we
should use arm/simpleperf instead of arm64/simpleperf.

## 3. Enable profiling
Android devices may disable profiling by default, and we need to enable
profiling.

    $adb shell setprop security.perf_harden 0

## 4. Find the target process/thread to record

    # Use `ps` to get process id of sudogame.
    $adb shell ps  | grep sudogame
    u0_a102   15869 545   1629824 76888 SyS_epoll_ 0000000000 S com.example.sudogame

    # Use `ps -t` to get thread ids of process 15869.
    # If this doesn’t work, you can try `ps -eT`.
    $adb shell ps -t  | grep 15869
    u0_a102   15869 545   1629824 76888 SyS_epoll_ 0000000000 S com.example.sudogame
    u0_a102   15874 15869 1629824 76888 futex_wait 0000000000 S Jit thread pool
    ...

## 5. Record perf.data

    # Record process 15869 for 30s, and use the app while recording it.
    $adb shell run-as com.example.sudogame ./simpleperf record -p 15869 --duration 30
    simpleperf W 07-12 20:00:33 16022 16022 environment.cpp:485] failed to read /proc/sys/kernel/kptr_restrict: Permission denied
    simpleperf I 07-12 20:01:03 16022 16022 cmd_record.cpp:315] Samples recorded: 81445. Samples lost: 0.

    $adb shell run-as com.example.sudogame ls -lh perf.data
    -rw-rw-rw- 1 u0_a102 u0_a102 4.3M 2016-07-12 20:01 perf.data

So we have recorded perf.data with 81445 records. There is a warning about
failing to read kptr_restrict. It doesn’t matter, only a notification that we
can’t read kernel symbol addresses.

## 6. Report perf.data
Below are several examples reporting on device.

### Report samples in different binaries

    # Report how samples distribute on different binaries.
    $adb shell run-as com.example.sudogame ./simpleperf report -n --sort dso
    simpleperf W 07-12 19:15:10 11389 11389 dso.cpp:309] Symbol addresses in /proc/kallsyms are all zero. `echo 0 >/proc/sys/kernel/kptr_restrict` if possible.
    Cmdline: /data/data/com.example.sudogame/simpleperf record -p 15869 --duration 30
    Arch: arm64
    Event: cpu-cycles (type 0, config 0)
    Samples: 81445
    Event count: 34263925309

    Overhead  Sample  Shared Object
    75.31%    58231   [kernel.kallsyms]
    8.44%     6845    /system/lib64/libc.so
    4.30%     4667    /vendor/lib64/egl/libGLESv2_adreno.so
    2.30%     2433    /system/lib64/libhwui.so
    1.88%     1952    /system/lib64/libart.so
    1.88%     1967    /system/framework/arm64/boot-framework.oat
    1.59%     1218    /system/lib64/libcutils.so
    0.69%     728     /system/lib64/libskia.so
    0.63%     489     /data/app/com.example.sudogame-2/lib/arm64/libsudo-game-jni.so
    0.34%     312     /system/lib64/libart-compiler.so
    ...

According to the report above, most time is spent in kernel, and
libsudo-game-jni.so costs only 0.63% by itself. It seems libsudo-game-jni.so
can’t be the bottleneck. However, it is possible we didn’t record long enough
to hit the hot spot, or code in libsudo-game-jni.so calls other libraries
consuming most time.

### Report samples in different functions

    # Report how samples distribute inside libsudo-game-jni.so.
    $adb shell run-as com.example.sudogame ./simpleperf report -n --dsos /data/app/com.example.sudogame-2/lib/arm64/libsudo-game-jni.so --sort symbol
    ...
    Overhead  Sample  Symbol
    94.45%    461     unknown
    5.22%     26      @plt
    0.20%     1       Java_com_example_sudogame_GameModel_findConflictPairs
    0.14%     1       Java_com_example_sudogame_GameModel_canFindSolution

In the report above, most samples belong to unknown symbol. It is because the
libsudo-game-jni.so used on device doesn’t contain symbol table. We need to
download shared library with symbol table to device. In android studio 2.1.2,
the binary with symbol table is in
[app_dir]/app/build/intermediates/binaries/debug/obj/arm64-v8a.

    # Make a proper directory to download binary to device. This directory
    # should be the same as the directory of
    # /data/app/com.example.sudogame-2/lib/arm64/libsudo-game-jni.so.
    $adb shell run-as com.example.sudogame mkdir -p data/app/com.example.sudogame-2/lib/arm64
    # Download binary with symbol table.
    $adb push [app_dir]/app/build/intermediates/binaries/debug/obj/arm64-v8a/libsudo-game-jni.so /data/local/tmp
    $adb shell run-as com.example.sudogame cp /data/local/tmp/libsudo-game-jni.so data/app/com.example.sudogame-2/lib/arm64

    # Report how samples distribute inside libsudo-game-jni.so with debug binary
    # support.
    $adb shell run-as com.example.sudogame ./simpleperf report -n --dsos /data/app/com.example.sudogame-2/lib/arm64/libsudo-game-jni.so --sort symbol --symfs .
    ...
    Overhead  Sample  Symbol
    71.08%    347     checkValid(Board const&, int, int)
    15.13%    74      randomBlock_r(Board&, int, int, int, int, int)
    7.94%     38      canFindSolution_r(Board&, int, int)
    5.22%     26      @plt
    0.30%     2       randomBoard(Board&)
    0.20%     1       Java_com_example_sudogame_GameModel_findConflictPairs
    0.14%     1       Java_com_example_sudogame_GameModel_canFindSolution

With the help of debug libsudo-game-jni.so, the report above shows that most
time in libsudo-game-jni.so is spent in function checkValid. And we can look
into it further.

### Report samples in one function

    # Report how samples distribute inside checkValid() function.
    # adb shell command can’t pass ‘(‘ in arguments, so we run the command
    # inside `adb shell`.
    $adb shell
    device$ run-as com.example.sudogame ./simpleperf report -n --symbols "checkValid(Board const&, int, int)" --sort vaddr_in_file --symfs .
    ...
    Overhead  Sample  VaddrInFile
    14.90%    50      0x24d8
    8.48%     29      0x251c
    5.52%     19      0x2468
    ...

The report above shows samples hitting different places inside function
checkValid(). By using objdump to disassemble libsudo-game-jni.so, we can find
which are the hottest instructions in checkValid() function.

    # Disassemble libsudo-game-jni.so.
    $aarch64-linux-android-objdump -d -S -l libsudo-game-jni.so >libsudo-game-jni.asm

## 7. Record and report call graph
### What is a call graph
A call graph is a tree showing function call relations. For example, a program
starts at main() function, and main() calls functionOne() and functionTwo(),
and functionOne() calls functionTwo() and functionThree(). Then the call graph
is as below.

    main() -> functionOne()
          |    |
          |    |-> functionTwo()
          |    |
          |     ->  functionThree()
           -> functionTwo()

### Record dwarf based call graph
To generate call graph, simpleperf needs to generate call chain for each record.
Simpleperf requests kernel to dump user stack and user register set for each
record, then it backtraces the user stack to find the function call chain. To
parse the call chain, it needs support of dwarf call frame information, which
usually resides in .eh_frame or .debug_frame section of the binary.  So we need
to use --symfs to point out where is libsudo-game-jni.so with debug information.

    # Record thread 11546 for 30s, use the app while recording it.
    $adb shell run-as com.example.sudogame ./simpleperf record -t 11546 -g --symfs . --duration 30
    simpleperf I 01-01 07:13:08  9415  9415 cmd_record.cpp:336] Samples recorded: 65279. Samples lost: 16740.
    simpleperf W 01-01 07:13:08  9415  9415 cmd_record.cpp:343] Lost 20.4099% of samples, consider increasing mmap_pages(-m), or decreasing sample frequency(-f), or increasing sample period(-c).

    $adb shell run-as com.example.sudogame ls -lh perf.data
    -rw-rw-rw- 1 u0_a96 u0_a96 8.3M 2016-01-01 08:49 perf.data

Note that kernel can’t dump user stack >= 64K, so the dwarf based call graph
doesn’t contain call chains consuming >= 64K stack. So avoiding allocating
large memory on stack is a good way to improve dwarf based call graph.

### Record stack frame based call graph
Another way to generate call graph is to rely on the kernel parsing the call
chain for each record. To make it possible, kernel has to be able to identify
the stack frame of each function call. This is not always possible, because
compilers can optimize away stack frames, or use a stack frame style not
recognized by the kernel. So how well it works depends.

    # Record thread 11546 for 30s, use the app while recording it.
    $adb shell run-as com.example.sudogame ./simpleperf record -t 11546 --call-graph fp --symfs . --duration 30
    simpleperf W 01-02 05:43:24 23277 23277 environment.cpp:485] failed to read /proc/sys/kernel/kptr_restrict: Permission denied
    simpleperf I 01-02 05:43:54 23277 23277 cmd_record.cpp:323] Samples recorded: 95023. Samples lost: 0.

    $adb shell run-as com.example.sudogame ls -lh perf.data
    -rw-rw-rw- 1 u0_a96 u0_a96 39M 2016-01-02 05:43 perf.data

### Report call graph
#### Report call graph on device
    # Report call graph.
    $adb shell run-as com.example.sudogame ./simpleperf report -n -g --symfs .
    Cmdline: /data/data/com.example.sudogame/simpleperf record -t 11546 -g --symfs . -f 1000 --duration 30
    Arch: arm64
    Event: cpu-cycles (type 0, config 0)
    Samples: 23840
    Event count: 41301992088

    Children  Self    Sample  Command          Pid    Tid    Shared Object                                                   Symbol
    97.98%    0.69%   162     xample.sudogame  11546  11546  /data/app/com.example.sudogame-1/lib/arm64/libsudo-game-jni.so  checkValid(Board const&, int, int)
       |
       -- checkValid(Board const&, int, int)
          |
          |--99.95%-- __android_log_print
          |           |
          |           |--92.19%-- __android_log_buf_write
          |           |           |
          |           |           |--73.50%-- libcutils.so[+1120c]
    ...

#### Report call graph in callee mode
Call graph can be shown in two modes. One is caller mode, showing how functions
call others. The other is callee mode, showing how functions are called by
others. We can use  *-g callee* option to show call graph in callee mode.

    # Report call graph.
    $host/simpleperf report -n -g callee --symfs .
    Cmdline: /data/data/com.example.sudogame/simpleperf record -t 11546 -g --symfs . -f 1000 --duration 30
    Arch: arm64
    Event: cpu-cycles (type 0, config 0)
    Samples: 23840
    Event count: 41301992088

    Children  Self    Sample  Command          Pid    Tid    Shared Object                                                   Symbol
    97.58%    0.21%   48      xample.sudogame  11546  11546  /system/lib64/liblog.so                                         __android_log_print
       |
       -- __android_log_print
          |
          |--99.70%-- checkValid(Board const&, int, int)
          |           |
          |           |--99.31%-- canFindSolution_r(Board&, int, int)
    ...

#### Report using report.py
The call graph generated by simpleperf report may be hard to read in text mode.
Simpleperf provides a python script showing gui interface of call graph.
It can be used as below.

    # Show call graph in gui interface.
    $adb shell run-as com.example.sudogame ./simpleperf report -n -g --symfs . >perf.report
    $python report.py perf.report

# Steps to profile java code on rooted devices
Simpleperf only supports profiling native instructions in binaries in ELF
format. If the java code is executed by interpreter, or with jit cache, it
can’t be profiled by simpleperf. As Android supports Ahead-of-time compilation,
it can compile java bytecode into native instructions. We currently need root
privilege to force Android fully compiling java code into native instructions
in ELF binaries with debug information (this could be fixed by a
profileable=”true” in AndroidManifest that causes PackageManager to pass -g to
dex2oat). We also need root privilege to read compiled native binaries
(because installd writes them to a directory whose uid/gid is system:install).
So profiling java code can currently only be done on rooted devices.

## 1. Fully compile java code into native instructions
### On Android N

    # Restart adb as root. It needs root privilege to setprop below.
    $adb root
    # Set the property to compile with debug information.
    $adb shell setprop dalvik.vm.dex2oat-flags -g

    # Fully compile the app instead of using interpreter or jit.
    $adb shell cmd package compile -f -m speed com.example.sudogame

    # Restart the app on device.

### On Android M

    # Restart adb as root. It needs root privilege to setprop below.
    $adb root
    # Set the property to compile with debug information.
    $adb shell setprop dalvik.vm.dex2oat-flags -g

    # Reinstall the app.
    $adb install -r app-debug.apk

### On Android L

    # Restart adb as root. It needs root privilege to setprop below.
    $adb root
    # Set the property to compile with debug information.
    $adb shell setprop dalvik.vm.dex2oat-flags --include-debug-symbols

    # Reinstall the app.
    $adb install -r app-debug.apk

## 2. Record perf.data

    # Change to the app’s data directory.
    $ adb root && adb shell
    device# cd `run-as com.example.sudogame pwd`

    # Record as root as simpleperf needs to read the generated native binary.
    device#./simpleperf record -t 25636 -g --symfs . -f 1000 --duration 30
    simpleperf I 01-02 07:18:20 27182 27182 cmd_record.cpp:323] Samples recorded: 23552. Samples lost: 39.

    device#ls -lh perf.data
    -rw-rw-rw- 1 root root 11M 2016-01-02 07:18 perf.data

## 3. Report perf.data
    # Report how samples distribute on different binaries.
    device#./simpleperf report -n --sort dso
    Cmdline: /data/data/com.example.sudogame/simpleperf record -t 25636 -g --symfs . -f 1000 --duration 30
    Arch: arm64
    Event: cpu-cycles (type 0, config 0)
    Samples: 23552
    Event count: 40662494587

    Overhead  Sample  Shared Object
    85.73%    20042   [kernel.kallsyms]
    9.41%     2198    /system/lib64/libc.so
    2.29%     535     /system/lib64/libcutils.so
    0.95%     222     /data/app/com.example.sudogame-1/lib/arm64/libsudo-game-jni.so
    ...
    0.04%     16      /system/lib64/libandroid_runtime.so
    0.03%     10      /data/app/com.example.sudogame-1/oat/arm64/base.odex
    ...

As in the report above, there are samples in
/data/app/com.example.sudogame-1/oat/arm64/base.odex, which is the native binary
compiled from java code.

    # Report call graph.
    device#./simpleperf report -n -g --symfs .
    Cmdline: /data/data/com.example.sudogame/simpleperf record -t 25636 -g --symfs . -f 1000 --duration 30
    Arch: arm64
    Event: cpu-cycles (type 0, config 0)
    Samples: 23552
    Event count: 40662494587

    Children  Self    Sample  Command          Pid    Tid    Shared Object                                                   Symbol
    98.32%    0.00%   1       xample.sudogame  25636  25636  /data/app/com.example.sudogame-1/oat/arm64/base.odex            void com.example.sudogame.GameModel.reInit()
       |
       -- void com.example.sudogame.GameModel.reInit()
          |
          |--98.98%-- boolean com.example.sudogame.GameModel.canFindSolution(int[][])
          |           Java_com_example_sudogame_GameModel_canFindSolution
          |           |
          |           |--99.93%-- canFindSolution(Board&)
    ...

As in the report above, function reInit() and canFindSolution() are java
functions.
