#include<linux/module.h>
#include<linux/uaccess.h>
#include<linux/fs.h>

#define DEVICE "convertdev"

static int major;

static ssize_t dev_write(struct file* file,const char __user* buf,size_t len,loff_t* off){
	char kbuf[256];
	char output[1024];
	int i,pos=0;
	
	copy_from_user(kbuf,buf,len);
	
	kbuf[len]='\0';
	
	for(i=0;i<len;i++){
		if(kbuf[i] >= "a" && kbuf[i] <= "z"){
			
			pos+=sprintf(output+pos,"%d",kbuf[i]-'a'+1);
		}
		else if(kbuf[i] >= "A" && kbuf[i] <= "Z"){
			pos+=sprintf(output+pos,"%d",kbuf[i]-'A'+1);
		}
		else{
			output[pos++]=kbuf[i];
			}
			}
		
	output[pos]='\0';
	
	printk(KERN_INFO "converted:%s\n",output);
	return len;
	}
	
	static struct file_operations fops={
	.write=dev_write,};
	
	static int __init start(void){
		major =register_chrdev(0,DEVICE,&fops);
		
		printk(KERN_INFO "Converted driver loaded.");
		printk(KERN_INFO"Major Number:%d\n",major);
		
		return 0;
		}
	static void __exit end(void){
		unregister_chrdev(major,DEVICE);
		printk(KERN_INFO "Converted driver Removed:\n");
		}
	
	module_init(start);
	module_exit(end);
	
	MODULE_LICENSE("GPL");
	MODULE_AUTHOR("SANTHOSH");
	MODULE_DESCRIPTION("Converting alphabets into numbers driver loaded");
	
		
