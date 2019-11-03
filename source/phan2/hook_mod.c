#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/delay.h>
#include <asm/paravirt.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("1512363 Nguyen Hoang Van Nha");
MODULE_DESCRIPTION("A kernel module hook sys_call open and write");

unsigned long **sys_call_table;

asmlinkage int (*original_open)(const char __user *, int, mode_t);

asmlinkage int (*original_write)(unsigned int, const char __user *, size_t);

asmlinkage int new_open(const char __user *pathname, int flags, mode_t mode)
{
	printk(KERN_INFO "HOOK OPEN - Process: %s | File: %s\n", current->comm, pathname);
	return (*original_open)(pathname, flags, mode);
}

asmlinkage int new_write(unsigned int fd, const char __user *buf, size_t count)
{
	int bytes_write;
	bytes_write = (*original_write)(fd, buf, count);
	printk(KERN_INFO "HOOK WRITE - Process: %s | Bytes count: %d\n", current->comm, bytes_write);
	return bytes_write;
}

static void get_sys_call_table(void)
{
	unsigned long int offset;
	for (offset = PAGE_OFFSET; offset < ULLONG_MAX; offset += sizeof(void *))
	{
		sys_call_table = (unsigned long **)offset;
		if (sys_call_table[__NR_close] == (unsigned long *)sys_close)
			break;
	}
}

static void allow_write(void)
{
	write_cr0(read_cr0() & ~0x10000);
}

static void disable_write(void)
{
	write_cr0(read_cr0() | 0x10000);
}

static int entry_point(void)
{
	get_sys_call_table();
	original_write = (void *)sys_call_table[__NR_write];
	original_open = (void *)sys_call_table[__NR_open];
	allow_write();
	sys_call_table[__NR_write] = (unsigned long *)new_write;
	sys_call_table[__NR_open] = (unsigned long *)new_open;
	disable_write();
	return 0;
}

static void exit_point(void)
{
	allow_write();
	sys_call_table[__NR_write] = (unsigned long *)original_write;
	sys_call_table[__NR_open] = (unsigned long *)original_open;
	disable_write();
}

module_init(entry_point);
module_exit(exit_point);