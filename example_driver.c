#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define EXAMPLE_MAJOR 119
#define EXAMPLE_MINOR 0

static struct cdev example_cdev;

static int example_open(struct inode *inode, struct file *file) {
    printk(KERN_DEBUG"%s",__func__);
    return 0;
}

static int example_device_open(struct inode *inode, struct file *file) {
    printk(KERN_DEBUG"%s",__func__);
    return 0;
}

static int example_device_release(struct inode *inode, struct file *file) {
    printk(KERN_DEBUG"%s",__func__);
    return 0;
}

static ssize_t example_device_read(struct file *file, char __user *buf, size_t count, loff_t *offset) {
    printk(KERN_DEBUG"%s",__func__);    
    return 0;
}

static ssize_t example_device_write(struct file *file, const char __user *buf, size_t count, loff_t *offset) {
    printk(KERN_DEBUG"%s",__func__);
    return 0;
}

static loff_t example_device_llseek(struct file *file, loff_t offset, int whence) {
    printk(KERN_DEBUG"%s",__func__);
    return 0;
}

static long example_device_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    printk(KERN_DEBUG"%s",__func__);
    return 0;
}

static int example_device_mmap(struct file *file, struct vm_area_struct *vma) {
    printk(KERN_DEBUG"%s",__func__);
    return 0;
}

static struct file_operations example_fops = {
    .owner   = THIS_MODULE,
    .open    = example_device_open,
    .release = example_device_release,
    .read    = example_device_read,
    .write   = example_device_write,
    .llseek  = example_device_llseek,
    .unlocked_ioctl = example_device_ioctl,
    .mmap    = example_device_mmap,
};

static int __init example_init(void)
{
    dev_t dev = MKDEV(EXAMPLE_MAJOR, EXAMPLE_MINOR);
    int result;

    result = register_chrdev_region(dev, 1, "exampledev");
    if (result < 0) {
        printk(KERN_ERR"Error: failed to register device\n");
        return result;
    }

    cdev_init(&example_cdev, &example_fops);
    result = cdev_add(&example_cdev, dev, 1);
    if (result < 0) {
        unregister_chrdev_region(dev, 1);
        return result;
    }

    printk(KERN_INFO"example driver loaded\n");
    return 0;
}

static void __exit example_exit(void)
{
    cdev_del(&example_cdev);
    unregister_chrdev_region(MKDEV(EXAMPLE_MAJOR, EXAMPLE_MINOR), 1);
    printk(KERN_INFO"example driver unloaded\n");
}

module_init(example_init);
module_exit(example_exit);
MODULE_LICENSE("GPL");
