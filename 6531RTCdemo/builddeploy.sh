echo Building..
make TOOLCHAIN=arm-none-eabi CHIP=1
echo Builded, copying.
cp 6531RTCdemo.bin ~/spd_dump64
echo Start flash!!
cd ~/spd_dump64
./spd_dump fdl nor_fdl1.bin 0x40004000 fdl 6531RTCdemo.bin ram
echo Flashed, start libcserver
./libc_server -- --bright 50 display
cd ../miniFPsdk/
