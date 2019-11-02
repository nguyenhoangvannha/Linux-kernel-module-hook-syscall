#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/random.h>

#define DRIVER_AUTHOR "1512363 Nguyen Hoang Van Nha"
#define DRIVER_DESC "A random number generator module"

#define MODULE_NAME "HDH Random Module"
#define DEVICE_CLASS "chardrv"
#define DEVICE_NAME "random_chardrv"

static dev_t dev_info;       // Global variable for the first device number
static struct cdev c_dev; // Global variable for the character device structure
static struct class *dev_class;  // Global variable for the device class

static int rand_dev_open(struct inode *i, struct file *f)
{
    return 0;
}
static int rand_dev_close(struct inode *i, struct file *f)
{
    return 0;
}

static ssize_t rand_dev_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    int random_number;
    get_random_bytes(&random_number, sizeof(random_number));
    if (copy_to_user(buf, &random_number, sizeof(random_number)) != 0)
        return -EFAULT;
    else
        return 1;
}


static struct file_operations pugs_fops =
    {
        .owner = THIS_MODULE,
        .open = rand_dev_open,
        .release = rand_dev_close,
        .read = rand_dev_read,
        };

static int __init init_random(void)
{
    if (alloc_chrdev_region(&dev_info, 0, 3, MODULE_NAME) < 0) //Dang ky so hieu va ten module
    {
        return -1;
    }
    if ((dev_class = class_create(THIS_MODULE, DEVICE_CLASS)) == NULL) //Lop thiet bi
    {
        unregister_chrdev_region(dev_info, 1);
        return -1;
    }
    if (device_create(dev_class, NULL, dev_info, NULL, DEVICE_NAME) == NULL) //Thong tin cua thiet bi trong lop thiet bi
    {
        class_destroy(dev_class);
        unregister_chrdev_region(dev_info, 1);
        return -1;
    }
    cdev_init(&c_dev, &pugs_fops);        //Cau truc thiet bi kieu character
    if (cdev_add(&c_dev, dev_info, 1) == -1) //Dieu khien cau truc nay den he thong file ao VFS
    {
        device_destroy(dev_class, dev_info);
        class_destroy(dev_class);
        unregister_chrdev_region(dev_info, 1);
        return -1;
    }
    printk(KERN_INFO "%s: registered", MODULE_NAME);
    return 0;
}
static void __exit exit_random(void)
{
    cdev_del(&c_dev);
    device_destroy(dev_class, dev_info);
    class_destroy(dev_class);
    unregister_chrdev_region(dev_info, 1);
    printk(KERN_INFO "%s: unregistered", MODULE_NAME);
}

module_init(init_random);
module_exit(exit_random);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("testdevice");