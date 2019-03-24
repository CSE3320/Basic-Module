#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Trevor Bakker <tbakker@gmail.com");
MODULE_DESCRIPTION("Basic module");

static int basic_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int basic_close(struct inode *inode, struct file *file)
{
    return 0;
}

static ssize_t basic_read(struct file *file, char __user *out, 
                            size_t size, loff_t *off)
{
    return 0;
}

static ssize_t basic_write(struct file *file, const char __user *in, 
                             size_t size, loff_t *off) 
{
    return 0;
}

static struct file_operations basic_fops = 
{
    .owner    = THIS_MODULE,
    .open     = basic_open,
    .read     = basic_read,
    .write    = basic_write,
    .release  = basic_close,
    .llseek   = noop_llseek
};

static struct miscdevice basic_misc_device = 
{
    .minor = MISC_DYNAMIC_MINOR,
    .name  = "basic",
    .fops  = &basic_fops
};

static int __init basic_init(void)
{
    printk(KERN_INFO "basic device has been registered\n");
    misc_register(&basic_misc_device);
    
    return 0;
}

static void __exit basic_exit(void)
{
    misc_deregister(&basic_misc_device);
    printk(KERN_INFO "basic device has been unregistered\n");
}

module_init(basic_init);
module_exit(basic_exit);

