# Simpleperf Introduction
## What is simpleperf
Simpleperf is a native profiling tool for Android. Its command-line interface
supports broadly the same options as the linux-tools perf, but also supports
various Android-specific improvements.

Simpleperf is part of the Android Open Source Project. The source code is at
https://android.googlesource.com/platform/system/extras/+/master/simpleperf/.
The latest document is at
https://android.googlesource.com/platform/system/extras/+show/master/simpleperf/README.md.
Bugs and feature requests can be submitted at
http://github.com/android-ndk/ndk/issues.

## How simpleperf works
Modern CPUs have a hardware component called the performance monitoring unit
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
simpleperf stat is used to get a raw event counter information of the profiled program
or system-wide. By passing options, we can select which events to use, which
processes/threads to monitor, how long to monitor and the print interval.
Below is an example.

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
Simpleperf can also fork a child process to run the new command and then monitor
the child process. Below are examples.

    # Stat process 11904 and 11905.
    $simpleperf stat -p 11904,11905 --duration 10

    # Stat thread 11904 and 11905.
    $simpleperf stat -t 11904,11905 --duration 10

    # Start a child process running `ls`, and stat it.
    $simpleperf stat ls

#### Decide how long to monitor
When monitoring existing threads, we can use --duration option to decide how long
to monitor. When monitoring a child process running a new command, simpleperf
monitors until the child process ends. In this case, we can use Ctrl-C to stop monitoring
at any time. Below are examples.

    # Stat process 11904 for 10 seconds.
    $simpleperf stat -p 11904 --duration 10

    # Stat until the child process running `ls` finishes.
    $simpleperf stat ls

    # Stop monitoring using Ctrl-C.
    $simpleperf stat -p 11904 --duration 10
    ^C

#### Decide the print interval
When monitoring perf counters, we can also use --interval option to decide the print
interval. Below are examples.

    # Print stat for process 11904 every 300ms.
    $simpleperf stat -p 11904 --duration 10 --interval 300

    # Print system wide stat at interval of 300ms for 10 seconds (rooted device only).
    # system wide profiling needs root privilege
    $su 0 simpleperf stat -a --duration 10 --interval 300

#### Display counters in systrace
simpleperf can also work with systrace to dump counters in the collected trace.
Below is an example to do a system wide stat

    # capture instructions (kernel only) and cache misses with interval of 300 milliseconds for 15 seconds
    $su 0 simpleperf stat -e instructions:k,cache-misses -a --interval 300 --duration 15
    # on host launch systrace to collect trace for 10 seconds
    (HOST)$external/chromium-trace/systrace.py --time=10 -o new.html sched gfx view
    # open the collected new.html in browser and perf counters will be shown up

### simpleperf record
simpleperf record is used to dump records of the profiled program. By passing
options, we can select which events to use, which processes/threads to monitor,
what frequency to dump records, how long to monitor, and where to store records.

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
-f 4000 means dumping approximately 4000 records every second when the monitored
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
a row. There are several columns, each column shows piece of information
belonging to a sample entry. The first column is Overhead, which shows the
percentage of events inside current sample entry in total events. As the
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
possible, it gives suggestions when facing errors, like how to disable
perf_harden to enable profiling.
2. Support unwinding while recording. If we want to use -g option to record and
report call-graph of a program, we need to dump user stack and register set in
each record, and then unwind the stack to find the call chain. Simpleperf
supports unwinding while recording, so it doesn’t need to store user stack in
perf.data. So we can profile for a longer time with limited space on device.'
3. Support scripts to make profiling on Android more convenient.
4. Build in static binaries. Simpleperf is a static binary, so it doesn’t need
supporting shared libraries to run. It means there is no limitation of Android
version that simpleperf can run on, although some devices don’t support
profiling.

# Simpleperf tools in ndk
Simpleperf tools in ndk contain three parts: simpleperf executable running on
Android device, simpleperf executable running on host, and python scripts.

## Simpleperf on device
Simpleperf running on device is located at bin/android directory. It contains
static binaries running on Android on different architectures. They can be used
to profile processes running device, and generate perf.data.

## Simpleperf on host
Simpleperfs running on host are located at bin/darwin, bin/linux and
bin/windows.They can be used to parse perf.data on host.

## Scripts
Scripts are used to make it convenient to profile and parse profiling results.
app_profiler.py is used to profile an android application. It prepares
profiling environments, downloads simpleperf on device, generates and pulls
perf.data on host. It is configured by app_profiler.config.
binary_cache_builder.py is used to pull native binaries from device to host.
It is used by app_profiler.py.
annotate.py is used to annotate source files using perf.data. It is configured
by annotate.config.
report.py reports perf.data in a GUI window.
simpleperf_report_lib.py is used to enumerate samples in perf.data. Internally
it uses libsimpleperf_report.so to parse perf.data. It can be used to translate
samples in perf.data to other forms. One example using simpleperf_report_lib.py
is report_sample.py.

# Examples of using simpleperf tools
This section shows how to use simpleperf tools to profile an Android
application.

## Prepare a debuggable Application
The package name of the application is com.example.sudogame. It has both java
code and c++ code. We need to run a copy of the app with
android:debuggable=”true” in its AndroidManifest.xml <application> element,
because we can’t use run-as for non-debuggable apps. The application should
has been installed on device, and we can connect device via adb.

## Profile using command line
To record profiling data, we need to download simpleperf and native libraries
with debug information on device, run simpleperf to generate profiling data
file: perf.data, and run simpleperf to report perf.data. Below are the steps.

### 1. Enable profiling

    $adb shell setprop security.perf_harden 0

### 2. Find the process running the app
Run `ps` in the app’s context. On >=O devices, run `ps -e` instead.

    $adb shell
    angler:/ $ run-as com.example.sudogame
    angler:/data/data/com.example.sudogame $ ps
    u0_a93    10324 570   1030480 58104 SyS_epoll_ 00f41b7528 S com.example.sudogame
    u0_a93    10447 10441 7716   1588  sigsuspend 753c515d34 S sh
    u0_a93    10453 10447 9112   1644           0 7ba07ff664 R ps

So process 10324 runs the app.

### 3. Download simpleperf to the app’s data directory
First we need to find out which architecture the app is using. There are many
ways, here we just check the map of the process.

    angler:/data/data/com.example.sudogame $cat /proc/10324/maps | grep boot.art
    70f34000-7144e000 r--p 00000000 fd:00 1082  /system/framework/arm/boot.oat

The file path shows it is arm. So we download simpleperf in arm directory on
device.

    $adb push bin/android/arm/simpleperf /data/local/tmp
    $adb shell
    angler:/ $ run-as com.example.sudogame
    angler:/data/data/com.example.sudogame $ cp /data/local/tmp/simpleperf .

### 4. Record perf.data

    angler:/data/data/com.example.sudogame $./simpleperf record -p 10324 --duration 30
    simpleperf I 01-01 09:26:39 10598 10598 cmd_record.cpp:341] Samples recorded: 49471. Samples lost: 0.
    angler:/data/data/com.example.sudogame $ls -lh perf.data
    -rw-rw-rw- 1 u0_a93 u0_a93 2.6M 2017-01-01 09:26 perf.data

Don’t forget to run the app while recording. Otherwise, we may get no samples
because the process is always sleeping.

### 5. Report perf.data
There are different ways to report perf.data. Below shows some examples.

Report samples in different threads.

    angler:/data/data/com.example.sudogame $./simpleperf report --sort pid,tid,comm
    Cmdline: /data/data/com.example.sudogame/simpleperf record -p 10324 --duration 30
    Arch: arm64
    Event: cpu-cycles (type 0, config 0)
    Samples: 49471
    Event count: 16700769019

    Overhead  Pid    Tid    Command
    66.31%    10324  10324  xample.sudogame
    30.97%    10324  10340  RenderThread
    ...

Report samples in different binaries in the main thread.

    angler:/data/data/com.example.sudogame $./simpleperf report --tids 10324 --sort dso -n
    ...
    Overhead  Sample  Shared Object
    37.71%    9970    /system/lib/libc.so
    35.45%    9786    [kernel.kallsyms]
    8.71%     3305    /system/lib/libart.so
    6.44%     2405    /system/framework/arm/boot-framework.oat
    5.64%     1480    /system/lib/libcutils.so
    1.55%     426     /data/app/com.example.sudogame-1/lib/arm/libsudo-game-jni.so
    ...

Report samples in different functions in libsudo-game-jni.so in the main thread.

    angler:/data/data/com.example.sudogame $./simpleperf report --tids 10324 --dsos  /data/app/com.example.sudogame-1/lib/arm/libsudo-game-jni.so --sort symbol -n
    ...
    Overhead  Sample  Symbol
    8.94%     35      libsudo-game-jni.so[+1d54]
    5.71%     25      libsudo-game-jni.so[+1dae]
    5.70%     23      @plt
    5.09%     22      libsudo-game-jni.so[+1d88]
    4.54%     19      libsudo-game-jni.so[+1d82]
    3.61%     14      libsudo-game-jni.so[+1f3c]
    ...

In the above result, most symbols are binary name[+virual_addr]. It is because
libsudo-game-jni.so used on device has stripped .symbol section. We can
download libsudo-game-jni.so having debug information on device. In android
studio project, it locates at
app/build/intermediates/binaries/debug/arm/obj/armeabi-v7a/libsudo-game-jni.so.
We have to download libsudo-game-jni.so to the same relative path as recorded
in perf.data (otherwise, simpleperf can’t find it). In this case, it is
/data/app/com.example.sudogame-1/lib/arm/libsudo-game-jni.so.

Report symbols using libraries with debug information.

    $adb push app/build/intermediates/binaries/debug/arm/obj/armeabi-v7a/libsudo-game-jni.so /data/local/tmp
    $adb shell
    angler:/ $ run-as com.example.sudogame
    angler:/data/data/com.example.sudogame $ mkdir -p data/app/com.example.sudogame-1/lib/arm
    angler:/data/data/com.example.sudogame $cp /data/local/tmp/libsudo-game-jni.so data/app/com.example.sudogame-1/lib/arm
    angler:/data/data/com.example.sudogame $./simpleperf report --tids 10324 --dsos  /data/app/com.example.sudogame-1/lib/arm/libsudo-game-jni.so --sort symbol -n --symfs .
    ...
    Overhead  Sample  Symbol
    75.18%    317     checkValid(Board const&, int, int)
    14.43%    60      canFindSolution_r(Board&, int, int)
    5.70%     23      @plt
    3.51%     20      randomBlock_r(Board&, int, int, int, int, int)
    ...

Report samples in one function

    angler:/data/data/com.example.sudogame $./simpleperf report --tids 10324 --dsos  /data/app/com.example.sudogame-1/lib/arm/libsudo-game-jni.so --symbols “checkValid(Board const&, int, int)” --sort vaddr_in_file -n --symfs .
    ...
    Overhead  Sample  VaddrInFile
    11.89%    35      0x1d54
    7.59%     25      0x1dae
    6.77%     22      0x1d88
    6.03%     19      0x1d82
    ...

### 6. Record and report call graph
A call graph is a tree showing function call relations. Below is an example.

    main() {
        FunctionOne();
        FunctionTwo();
    }
    FunctionOne() {
        FunctionTwo();
        FunctionThree();
    }
    callgraph:
        main-> FunctionOne
           |    |
           |    |-> FunctionTwo
           |    |-> FunctionThree
           |
           |-> FunctionTwo

#### Record dwarf based call graph
To generate call graph, simpleperf needs to generate call chain for each record.
Simpleperf requests kernel to dump user stack and user register set for each
record, then it backtraces the user stack to find the function call chain. To
parse the call chain, it needs support of dwarf call frame information, which
usually resides in .eh_frame or .debug_frame section of the binary.  So we need
to use --symfs to point out where is libsudo-game-jni.so with debug information.

    angler:/data/data/com.example.sudogame $./simpleperf record -p 10324 -g --symfs . --duration 30
    simpleperf I 01-01 09:59:42 11021 11021 cmd_record.cpp:341] Samples recorded: 60700. Samples lost: 1240.

Note that kernel can’t dump user stack >= 64K, so the dwarf based call graph
doesn’t contain call chains consuming >= 64K stack. What’s more, because we
need to dump stack in each record, it is likely to lost records. Usually, it
doesn’t matter to lost some records.

#### Record stack frame based call graph
Another way to generate call graph is to rely on the kernel parsing the call
chain for each record. To make it possible, kernel has to be able to identify
the stack frame of each function call. This is not always possible, because
compilers can optimize away stack frames, or use a stack frame style not
recognized by the kernel. So how well it works depends (It works well on arm64,
but not well on arm).

    angler:/data/data/com.example.sudogame $./simpleperf record -p 10324 --call-graph fp --symfs . --duration 30
    simpleperf I 01-01 10:03:58 11267 11267 cmd_record.cpp:341] Samples recorded: 56736. Samples lost: 0.

**Recording stack frame based call graph doesn't work well on arm architecture,**
**even if compiled using -O0 -g -fno-omit-frame-pointer options. It is because**
**the kernel can't unwind user stack containing both arm/thumb code. So please**
**consider using dwarf based call graph on arm architecture, or profiling in**
**aarch64 environment.**

#### Report call graph
Report accumulated period. In the table below, the first column is “Children”,
it is the cpu cycle percentage of a function and functions called by that
function. The second column is “Self”, it is the cpu cycle percentage of just a
function. For example, checkValid() itself takes 1.28% cpus, but it takes
29.43% by running itself and calling other functions.

    angler:/data/data/com.example.sudogame $./simpleperf report --children --symfs .
    ...
    Children  Self   Command          Pid    Tid    Shared Object                                                 Symbol
    31.94%    0.00%  xample.sudogame  10324  10324  [kernel.kallsyms]                                             [kernel.kallsyms][+ffffffc000204268]
    31.10%    0.92%  xample.sudogame  10324  10324  /system/lib/libc.so                                           writev
    29.43%    1.28%  xample.sudogame  10324  10324  /data/app/com.example.sudogame-1/lib/arm/libsudo-game-jni.so  checkValid(Board const&, int, int)
    28.43%    0.34%  xample.sudogame  10324  10324  /system/lib/liblog.so                                         __android_log_print
    28.24%    0.00%  xample.sudogame  10324  10324  /system/lib/libcutils.so                                      libcutils.so[+107b7]
    28.10%    0.27%  xample.sudogame  10324  10324  /data/app/com.example.sudogame-1/lib/arm/libsudo-game-jni.so  canFindSolution_r(Board&, int, int)
    ...

Report call graph.

    angler:/data/data/com.example.sudogame $./simpleperf report -g --symfs . >report
    angler:/data/data/com.example.sudogame $exit
    angler:/ $cp /data/data/com.example.sudogame/report /data/local/tmp
    angler:/ $exit
    $adb pull /data/local/tmp/report .
    $cat report
    ...
    29.43%    1.28%  xample.sudogame  10324  10324  /data/app/com.example.sudogame-1/lib/arm/libsudo-game-jni.so  checkValid(Board const&, int, int)
           |
           -- checkValid(Board const&, int, int)
              |
              |--95.50%-- __android_log_print
              |    |--0.68%-- [hit in function]
              |    |
              |    |--51.84%-- __android_log_buf_write
              |    |    |--2.07%-- [hit in function]
              |    |    |
              |    |    |--30.74%-- libcutils.so[+c69d]
    ...

Report call graph in callee mode. We can also show how a function is called by
other functions.

    angler:/data/data/com.example.sudogame $./simpleperf report -g callee --symfs . >report
    $adb shell run-as com.example.sudogame cat report >report
    $cat report
    …
    28.43%    0.34%  xample.sudogame  10324  10324  /system/lib/liblog.so                                         __android_log_print
           |
           -- __android_log_print
              |
              |--97.82%-- checkValid(Board const&, int, int)
              |    |--0.13%-- [hit in function]
              |    |
              |    |--94.89%-- canFindSolution_r(Board&, int, int)
              |    |    |--0.01%-- [hit in function]
              |    |    |
    ...

## Profile java code
Simpleperf only supports profiling native instructions in binaries in ELF
format. If the java code is executed by interpreter, or with jit cache, it
can’t be profiled by simpleperf. As Android supports Ahead-of-time compilation,
it can compile java bytecode into native instructions with debug information.
On devices with Android version <= M, we need root privilege to compile java
bytecode with debug information. However, on devices with Android version >= N,
we don't need root privilege to do so.

### On Android N
#### 1. Fully compile java code into native instructions.

    $adb shell setprop debug.generate-debug-info true
    $adb shell cmd package compile -f -m speed com.example.sudogame
    // restart the app to take effect

#### 2. Record perf.data

    angler:/data/data/com.example.sudogame $./simpleperf record -p 11826 -g --symfs . --duration 30
    simpleperf I 01-01 10:31:40 11859 11859 cmd_record.cpp:341] Samples recorded: 50576. Samples lost: 2139.

#### 3. Report perf.data

    angler:/data/data/com.example.sudogame $./simpleperf report -g --symfs . >report
    angler:/data/data/com.example.sudogame $exit
    angler:/ $cp /data/data/com.example.sudogame/report /data/local/tmp
    angler:/ $exit
    $adb pull /data/local/tmp/report .
    $cat report
    ...
    21.14%    0.00%  xample.sudogame  11826  11826  /data/app/com.example.sudogame-1/oat/arm/base.odex            boolean com.example.sudogame.MainActivity.onOptionsItemSelected(android.view.MenuItem)
           |
           -- boolean com.example.sudogame.MainActivity.onOptionsItemSelected(android.view.MenuItem)
              |
               --99.99%-- void com.example.sudogame.GameView.startNewGame()
                   |--0.01%-- [hit in function]
                   |
                   |--99.87%-- void com.example.sudogame.GameModel.reInit()
                   |    |--0.01%-- [hit in function]
                   |    |
                   |    |--89.65%-- boolean com.example.sudogame.GameModel.canFindSolution(int[][])
                   |    |    |
                   |    |    |--99.95%-- Java_com_example_sudogame_GameModel_canFindSolution
                   |    |    |    |
                   |    |    |    |--99.49%-- canFindSolution(Board&)
                   |    |    |    |    |--0.01%-- [hit in function]
                   |    |    |    |    |
                   |    |    |    |    |--99.97%-- canFindSolution_r(Board&, int, int)
                   |    |    |    |    |           canFindSolution_r(Board&, int, int)
    ...

### On Android M
On M devices, We need root privilege to force Android fully compiling java code
into native instructions in ELF binaries with debug information. We also need
root privilege to read compiled native binaries (because installd writes them
to a directory whose uid/gid is system:install). So profiling java code can
only be done on rooted devices.

    $adb root
    $adb shell setprop dalvik.vm.dex2oat-flags -g

    # Reinstall the app.
    $adb install -r app-debug.apk

    # Change to the app’s data directory.
    $ adb root && adb shell
    device# cd `run-as com.example.sudogame pwd`

    # Record as root as simpleperf needs to read the generated native binary.
    device#./simpleperf record -p 25636 -g --symfs . -f 1000 --duration 30
    simpleperf I 01-02 07:18:20 27182 27182 cmd_record.cpp:323] Samples recorded: 23552. Samples lost: 39.

### On Android L
On L devices, we also need root privilege to compile the app with debug info
and access the native binaries.

    $adb root
    $adb shell setprop dalvik.vm.dex2oat-flags --include-debug-symbols

    # Reinstall the app.
    $adb install -r app-debug.apk

## Profile using scripts
Although using command line is flexible, it can be too complex. So we have
python scripts to help running commands.

### Record using app_profiler.py
app_profiler.py is used to profile an Android application. It sets up profiling
environment, downloads simpleperf and native libraries with debug information,
runs simpleperf to generate perf.data, and pulls perf.data and binaries from
device to host.
It is configured by app_profiler.config. Below is an example.

app_profiler.config:

    app_package_name = “com.example.sudogame”
    android_studio_project_dir = “/AndroidStudioProjects/SudoGame”  # absolute path of the project
    ...
    record_options = "-e cpu-cycles:u -f 4000 -g --dump-symbols --duration 30"
    ...

run app_profiler.py:

    $python app_profiler.py
    ...
    INFO:root:profiling is finished.

It pulls generated perf.data on host, and collects binaries from device in
binary_cache.

### Report using report.py

    $python report.py -g

It generates a GUI interface to report data.

### Process samples using simpleperf_report_lib.py
simpleperf_report_lib.py provides an interface reading samples from perf.data.
An example is report_sample.py.

### Show flamegraph

    $python report_sample.py >out.perf
    $stackcollapse-perf.pl out.perf >out.folded
    $./flamegraph.pl out.folded >a.svg

### Visualize using pprof
pprof is a tool for visualization and analysis of profiling data. It can
be got from https://github.com/google/pprof. pprof_proto_generator.py can
generate profiling data in a format acceptable by pprof.

    $python pprof_proto_generator.py
    $pprof -pdf pprof.profile

### Annotate source code
annotate.py reads perf.data and binaries in binary_cache. Then it knows which
source file:line each sample hits. So it can annotate source code. annotate.py
is configured by annotate.config. Below is an example.

annotate.config:

    ...
    source_dirs = [“/AndroidStudio/SudoGame”]  # It is a directory containing source code.
    ...

run annotate.py:

    $python annotate.py

It generates annotated_files directory.
annotated_files/summary file contains summary information for each source file.
An example is as below.

    /AndroidStudioProjects/SudoGame/app/src/main/jni/sudo-game-jni.cpp: accumulated_period: 25.587937%, period: 1.250961%
      function (checkValid(Board const&, int, int)): line 99, accumulated_period: 23.564356%, period: 0.908457%
      function (canFindSolution_r(Board&, int, int)): line 135, accumulated_period: 22.260125%, period: 0.142359%
      function (canFindSolution(Board&)): line 166, accumulated_period: 22.233101%, period: 0.000000%
      function (Java_com_example_sudogame_GameModel_canFindSolution): line 470, accumulated_period: 21.983184%, period: 0.000000%
      function (Java_com_example_sudogame_GameModel_initRandomBoard): line 430, accumulated_period: 2.226896%, period: 0.000000%

      line 27: accumulated_period: 0.011729%, period: 0.000000%
      line 32: accumulated_period: 0.004362%, period: 0.000000%
      line 33: accumulated_period: 0.004427%, period: 0.000000%
      line 36: accumulated_period: 0.003303%, period: 0.000000%
      line 39: accumulated_period: 0.010367%, period: 0.004123%
      line 41: accumulated_period: 0.162219%, period: 0.000000%

annotated_files/ also contains annotated source files which are found by
annotate.py. For example, part of checkValid() function in libsudo-game-jni.cpp
is annotated as below.

    /* [func] acc_p: 23.564356%, p: 0.908457% */static bool checkValid(const Board& board, int curR, int curC) {
    /* acc_p: 0.037933%, p: 0.037933%         */    int digit = board.digits[curR][curC];
    /* acc_p: 0.162355%, p: 0.162355%         */    for (int r = 0; r < BOARD_ROWS; ++r) {
    /* acc_p: 0.020880%, p: 0.020880%         */        if (r == curR) {
    /* acc_p: 0.034691%, p: 0.034691%         */            continue;
                                                        }
    /* acc_p: 0.176490%, p: 0.176490%         */        if (board.digits[r][curC] == digit) {
    /* acc_p: 14.957673%, p: 0.059022%        */            LOGI("conflict (%d, %d) (%d, %d)", curR, curC, r, curC);
    /* acc_p: 0.016296%, p: 0.016296%         */            return false;
                                                        }
                                                    }
