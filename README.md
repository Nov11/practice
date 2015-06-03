# practice
ugly getpid() syscall record implementation
###how to make them run online?###
###build external kernel module###
on fresh installed fedora 21
yum groupinstall "Development tools"//get gcc and so on
yum install kernel-devel-`uname -r` //kernel headers for building module
'grep sys_call_table /proc/kallsyms'  can get sys_call_table addr. Place it in record.c
run 'make' build module
run './load.sh' load module
getpid is compiled from gp.c
normal user run setup to begin recording getpid.
run replay to replay getpid
more rework is done on lngpr
