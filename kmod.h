#ifndef __LINUX_KMOD_MODULE_H
#define __LINUX_KMOD_MODULE_H

struct kmod_ioctl_struct {
	int val1;
	int val2;
};

#define KMODIOC1 _IO('i', 145)
#define KMODIOC2 _IO('i', 146)
#define KMODIOC3 _IO('i', 147)

#endif
