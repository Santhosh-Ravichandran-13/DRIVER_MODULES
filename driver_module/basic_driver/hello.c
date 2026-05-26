#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

static int __init hello_init(void){
	printk(KERN_INFO"Hello driver from santhosh loaded\n");
	return ;
	}

static void __exit hello_exit(void){
	printk(KERN_INFO"Hello driver removed\n");
	return ;
	}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SANTHOSH");
MODULE_DESCRIPTION("Simple basic drviver loaded");
