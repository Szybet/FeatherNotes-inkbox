#!/system-bin/sh
cd /app-bin
env PRODUCT=luna PATH="/app-bin:/system-bin" LD_LIBRARY_PATH="/system-lib/lib:/system-lib/qt/lib:/app-lib" /system-lib/lib/ld-linux-armhf.so.3 ./sketch-bin /app-data
