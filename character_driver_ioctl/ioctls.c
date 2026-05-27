#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include <linux/ioctl.h>

#define DEVICE_NAME "ioctldev"
#define MAGIC 'k'

#define LED_ON  _IO(MAGIC, 1)
#define LED_OFF _IO(MAGIC, 2)
static int major;
static long device_ioctl(struct file* file,unsigned int cmd,unsigned long arg){
	switch(cmd){
		case LED_ON:
			printk(KERN_INFO "LED on ");
			break;
		
		case LED_OFF:
			printk(KERN_INFO "LED off");
			break;
		
		default:
			printk("Invalid commnad");
		}
	return 0;
	}

static struct file_operations fops={
	.owner=THIS_MODULE,
	.unlocked_ioctl=device_ioctl,
	};

static int __init driver_start(void){
	major=register_chrdev(0,DEVICE_NAME,&fops);
	
	printk(KERN_INFO "Driver loaded");
	printk(KERN_INFO "Major number:%d\n",major);
	return 0;
	}


static void __exit driver_end(void){
	unregister_chrdev(major,DEVICE_NAME);
	printk(KERN_INFO "Driver removed");
}

module_init(driver_start);
module_exit(driver_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SANTHOSH");
MODULE_DESCRIPTION("IOCTL DRIVER LOADED");



