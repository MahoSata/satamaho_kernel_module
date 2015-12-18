#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/file.h>
#include <linux/types.h>
#include <linux/poll.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/sched/rt.h>
#include <linux/task_work.h>
#include <linux/tick.h>
#include <linux/kthread.h>
#include <linux/ktime.h>
#include <linux/mm.h>
#include <linux/io.h>
#include <linux/proc_fs.h>
#include <linux/cpu.h>
#include <linux/uio.h>

#include <linux/sata_tcp.h>

#include "kmod.h"

static int kmod_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "open\n");
	return 0;
}

long kmod_ioctl(struct file *filp, u_int cmd, u_long data)
{
	struct kmod_ioctl_struct kioc;

	printk(KERN_INFO "%s\n", __func__);

	if (copy_from_user(&kioc, (void *)data, sizeof(struct kmod_ioctl_struct)) != 0) {
		printk(KERN_INFO "Copy fail\n");
		goto out;
	}

	switch (cmd) {
		case KMODIOC1:
			printk(KERN_INFO "KMODIOC1 val1: %d\n", kioc.val1);
			sata_x = kioc.val1;
			break;
		case KMODIOC2:
			printk(KERN_INFO "KMODIOC2 val2: %d\n", kioc.val2);
			sata_y = kioc.val2;
			break;
		case KMODIOC3:
			printk(KERN_INFO "sata_x %d, sata_y %d\n",
								sata_x, sata_y);
			break;
		default:
			printk(KERN_INFO "No handler\n");
			break;
	}

out:
	return 0;
}

static int kmod_release(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "release\n");
	return 0;
}

static struct file_operations kmod_fops = {
	.owner = THIS_MODULE,
	.open = kmod_open,
	.unlocked_ioctl = kmod_ioctl,
	.release = kmod_release,
};

struct miscdevice kmod_cdevsw = {
	MISC_DYNAMIC_MINOR,
	"kmod",
	&kmod_fops,
};

void kmod_init(void)
{
	misc_register(&kmod_cdevsw);
}

void kmod_exit(void)
{
	misc_deregister(&kmod_cdevsw);
}

static int __init kmod_module_init(void)
{
	printk(KERN_INFO "KMOD Loaded\n");
	kmod_init();
	return 0;
}

static void __exit kmod_module_exit(void)
{
	kmod_exit();
	printk(KERN_INFO "KMOD Unloaded\n");
	return;
}

module_init(kmod_module_init);
module_exit(kmod_module_exit);

MODULE_AUTHOR("Kenichi Yasukata");
MODULE_DESCRIPTION("Kernel Module Template");
MODULE_LICENSE("Dual BSD/GPL");
