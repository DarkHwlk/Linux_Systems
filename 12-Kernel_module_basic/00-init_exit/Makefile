# Hello world kernel module

EXTRA_CFLAGS = -Wall  # -Wall: warning all, show all warning when build
obj-m = hello.o

KDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=`pwd` modules

clean:
	make -C $(KDIR) M=`pwd` clean
