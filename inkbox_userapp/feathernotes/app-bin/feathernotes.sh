#!/system-bin/sh
i2cset -y -f 3 0x32 0xb3 0x20
echo host > /sys/kernel/debug/ci_hdrc.0/role
echo 2 > /sys/class/graphics/fb0/rotate
echo 2 > /sys/class/graphics/fb0/rotate
echo 2 > /sys/class/graphics/fb0/rotate
echo 2 > /sys/class/graphics/fb0/rotate
sleep 3
env -i DEVICE="${DEVICE}" DEVICE_CODENAME="${DEVICE_CODENAME}" QT_FONT_DPI=${QT_FONT_DPI} PATH="/app-bin:/system-bin" LD_LIBRARY_PATH="/system-lib/lib:/system-lib/qt/lib:/app-lib" QT_QPA_PLATFORM="kobo" LC_ALL="en_US" /system-lib/lib/ld-linux-armhf.so.3 /app-bin/feathernotes-bin
