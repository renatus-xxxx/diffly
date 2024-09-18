zcc +msx -create-app -O3 -subtype=msxdos diffly.c -bn DIFFLY.COM
del DIFFLY.img
move /y DIFFLY.COM bin
cd bin
START /WAIT DISKMGR.exe -A -F -C DIFFLY.DSK DIFFLY.COM
cd ../
