printk() // Logging


dmesg // Xem hoat dong cua kernel ke tu luc no khoi dong
modinfo rand_module.ko // Xem thong tin cua mot module
sudo insmod rand_module.ko // cai dat module hello.ko vao kernel
lsmod | grep hello // Kiem tra module da lap vao hay chua
sudo rmmod rand_module // Xoa module hello ra khoi kernel

cat /dev/rand_device
cat /proc/devices 