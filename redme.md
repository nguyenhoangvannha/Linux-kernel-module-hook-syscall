
Môi trường: Ubuntu 14.04
Linux kernel: 4.4.0-142-generic
Các package yêu cầu: make, gcc

Phần 1. Linux kernel module dùng để tạo ra số ngẫu nhiên.
1.1 Build project và cài module.
- Mở terminal.
- cd vào thư mục source/phan1/kernelspace.
- chạy lệnh 'make' để build
- chạy lệnh 'sudo insmod rand_module.ko'
Kết thúc lệnh trên thì module đã được lắp vào.

1.2 Test module vừa gắn vào
- Mở terminal
- cd vào thư mục source/phan1/userspace.
-   chạy lệnh 'make' để build
- chạy lênh 'sudo ./random_test' để test module vừa gắn vào
- màn hình terminal sẽ hiển thị số ngẫu nhiên nhận được.

Phần 2. Chương trình hook vào một system call.
2.1 Build project và cài module.
- Mở terminal.
- cd vào thư mục source/phan2
- chạy lệnh 'make' để build
- chạy lệnh 'sudo insmod hook_mod.ko'
Kết thúc lệnh trên thì module đã được lắp vào.

2.2 Test module vừa gắn vào
- Mở terminal
- chạy lệnh 'dmesg' và xem kết quả log, các log sẽ bắt đầu bằng từ 'HOOK'

-------------------------------------------------------------------------
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
