#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "../kmod.h"

int main(int argc, char const* argv[])
{
	int fd;
	struct kmod_ioctl_struct kioc;

	if ((fd = open("/dev/kmod", O_RDWR)) < 0) {
		perror("open fail");
		return -1;
	}

	memset(&kioc, 0, sizeof(struct kmod_ioctl_struct));
	kioc.val1 = 10;
	kioc.val2 = 1;
	ioctl(fd, KMODIOC1, &kioc);
	ioctl(fd, KMODIOC2, &kioc);
	ioctl(fd, KMODIOC3, &kioc);

	close(fd);

	return 0;
}
