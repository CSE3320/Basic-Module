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

/** @brief This function is called each time the device is opened.
  * @param inode - A pointer to an inode ( defined in linux/fs.h )
  * @param file  - A pointer to a file object ( defined in linux/fs.h )
  */
static int basic_open(struct inode *inode, struct file *file)
{
    return 0;
}

/** @brief This function is called each time the device is closed.
  * @param inode - A pointer to an inode ( defined in linux/fs.h )
  * @param file  - A pointer to a file object ( defined in linux/fs.h )
  */
static int basic_close(struct inode *inode, struct file *file)
{
    return 0;
}

/** @brief This function is called whenever the device is begin read from
 *  user space, e.g. data is being sent from the device to user space.  
 *  @param file - A pointer to a file ( defined in linux/fs.h )
 *  @param out  - A pointer to the buffer to which this function writes data
 *  @param size - The length of the buffer
 *  @param off  - The offset
 */
static ssize_t basic_read(struct file *file, char __user *out, 
                            size_t size, loff_t *off)
{
    return 0;
}

/** @brief This function is called whener the device is being written to
  * from user space, e.g. data is being sent from the device to user space
  * @param file   - A pointer to a file object ( defined in linux/fs.h )
  * @param buffer - A pointer to the buffer where this function reads from
  * @param size   - The size of the buffer
  * @param off    - The offset
  */
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
    misc_register(&basic_misc_device);
    printk(KERN_INFO "basic device has been registered\n");
    
    return 0;
}

static void __exit basic_exit(void)
{
    misc_deregister(&basic_misc_device);
    printk(KERN_INFO "basic device has been unregistered\n");
}

module_init(basic_init);
module_exit(basic_exit);

