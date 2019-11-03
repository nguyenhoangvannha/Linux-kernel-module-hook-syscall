printk() // Logging


dmesg // Xem hoat dong cua kernel ke tu luc no khoi dong
modinfo rand_module.ko // Xem thong tin cua mot module
sudo insmod rand_module.ko // cai dat module hello.ko vao kernel
lsmod | grep hello // Kiem tra module da lap vao hay chua
sudo rmmod rand_module // Xoa module hello ra khoi kernel

cat /dev/rand_device
cat /proc/devices 


install make, gcc
uname -r

sudo cat /boot/System.map-4.15.0-66-generic | grep sys_call_table
ffffffff81e00240

sudo cat /boot/System.map-5.0.0-32-generic | grep sys_call_table
sudo cat /boot/System.map-5.0.0-31-generic | grep sys_call_table
0xffffffff82000280