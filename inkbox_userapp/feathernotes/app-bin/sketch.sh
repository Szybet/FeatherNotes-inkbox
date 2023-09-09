#!/system-bin/sh
cd /app-bin
# Remember app lib before the rest
env PRODUCT=luna PATH="/app-bin:/system-bin" LD_LIBRARY_PATH="/app-lib:/system-lib/lib:/system-lib/qt/lib" /system-lib/lib/ld-linux-armhf.so.3 ./sketch-bin /app-data
