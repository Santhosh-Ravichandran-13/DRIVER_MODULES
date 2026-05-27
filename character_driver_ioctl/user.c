#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include <sys/ioctl.h>

#define MAGIC 'k'

#define LED_ON  _IO(MAGIC, 1)
#define LED_OFF _IO(MAGIC, 2)

#define DEVICE_NAME "ioctldev"

int main(){
	int fd;
	
	fd=open("/dev/ioctldev",O_RDWR);
	
	if(fd<0){
	printf("cannot open the file");
	return -1;
	}

  if(ioctl(fd, LED_ON) < 0)
{
    perror("IOCTL ON Failed");
}
   sleep(2);
  if(ioctl(fd, LED_OFF) < 0)
{
    perror("IOCTL OFF Failed");
}
   close(fd);
   return 0;
   }
   

