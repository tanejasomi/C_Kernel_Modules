#Device Management modules
UNIX has three major kinds of device drivers:
1)Character device driver
2)Block device driver for devices like disks
3)Networks device drivers

Character devices are those that read and write byte-oriented data from and to hardware devices such as mice, serial and parallel ports, and terminals.

#Program dev_access.c

Program to hack linux kernal module for character devices.
User can provide any of three inputs: 0/2/1
Command line argument "0":
it opens /dev/input/mouse0 and then in an infinite loop uses the read() system call to read a single byte at a time; as these bytes are read, they are printed to STDOUT as integer values, one value per line.
Command line argument "1":
it opens /dev/urandom for reading and /dev/null for writing and then reads 10 MB of pseudorandomness, dumping it to /dev/null and printing the total elapsed time taken to do this using a pair of gettimeofday() calls; you are to do this using as few read() and write() calls as possible; in other words, the inital read() should be passed a count parameter of 10,000,000 and subsequent calls should be for fewer bytes as appropriate
Command line argument "2":
It extends already existing program ticket.c to change it into driver that serves up tickets to user-mode processes like at the bakery. Each time an integer is read from this device it will get the next value in order. The first process to read from this device gets 1000, the second gets 1001, etc


Command to compile code:
gcc -O2 -Wall -Wextra dev_access.c -o dev_access


Command to run code:
sudo ./dev_access 0/1/2
