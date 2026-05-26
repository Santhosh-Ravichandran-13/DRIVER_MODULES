#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/uaccess.h>

#define DEVICE_NAME "mychardev"
#define BUFFER_SIZE 1024

static int major;
static char device_buffer[BUFFER_SIZE]="Hello from Kernel Driver in santhosh";

static int dev_open(struct inode *inode,struct file *file){
	printk(KERN_INFO "Device opened\n");
	return 0;
	}

static int dev_release(struct inode *inode,struct file *file){
	printk(KERN_INFO "Device closed\n");
	return 0;
	}

static ssize_t dev_read(struct file *file,char __user*user_buffer,size_t len,loff_t *offset)
	{
	int bytes_to_read;
	if(*offset>=strlen(device_buffer))
		return 0;
	
	bytes_to_read=strlen(device_buffer)-*offset;
	
	if(len<bytes_to_read)
		bytes_to_read=len;
	
	if(copy_to_user(user_buffer,device_buffer+*offset,bytes_to_read))
	{
	return -EFAULT;
	}

*offset+=bytes_to_read;

printk(KERN_INFO "Data read from Device\n");

return bytes_to_read;
}

static ssize_t dev_write(struct file *file,const char __user*user_buffer,size_t len,loff_t *offset){
	if(len>BUFFER_SIZE-1)
		len=BUFFER_SIZE-1;
	
	if(copy_from_user(device_buffer,user_buffer,len)){
	return -EFAULT;
	}
	
	device_buffer[len]='\0';
	
	printk(KERN_INFO "Data written to device :%s\n",device_buffer);
	return len;
	}
	
	static struct file_operations fops={
	.owner=THIS_MODULE,.open=dev_open,.read=dev_read,.write=dev_write,.release=dev_release};
	static int __init char_driver_init(void){
		major=register_chrdev(0,DEVICE_NAME,&fops);
		if(major<0)
		{
		printk(KERN_INFO "Driver registration failed\n");
		return major;
		}
		
		printk(KERN_INFO "Chararcter Driver loaded\n");
		printk(KERN_INFO "Major numberis %d\n",major);
	return 0;
	}
	
	static void __exit char_driver_exit(void){
		unregister_chrdev(major,DEVICE_NAME);
		printk(KERN_INFO "Character driver removed");
		}
		
		module_init(char_driver_init);
		module_exit(char_driver_exit);
		
		MODULE_LICENSE("GPL");
		MODULE_AUTHOR("SANTHOSH");
		MODULE_DESCRIPTION("Character driver successfull");
		
