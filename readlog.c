#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/string.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>

#define FILE_PATH	"/home/c6s/test/log"

struct file* filp;

static int __init init(void)
{
	mm_segment_t old_fs;
	char buf[20];
	int ret;
	long saved_pid;
	filp = filp_open(FILE_PATH, O_RDWR, 0644);
	if(IS_ERR(filp)){
		printk(KERN_INFO"ERROR filp_OPEN\n");
		return -1;
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);
	ret = filp->f_op->read(filp, buf, 20, &filp->f_pos);
	printk(KERN_INFO"read %d char\n", ret);
	set_fs(old_fs);
	printk(KERN_INFO"read out: %s\n", buf);

	if(kstrtol(buf, 10, &saved_pid)){
		printk(KERN_INFO"error kstrtol\n");
	}
	printk(KERN_INFO"the pid in long int : %ld\n", saved_pid);
	return 0;
}

static void __exit ex(void)
{
	filp_close(filp, NULL);
}

MODULE_LICENSE("GPL");
module_init(init);
module_exit(ex);

