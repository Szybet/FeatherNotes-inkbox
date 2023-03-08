#!/system-bin/sh
echo 2 > /sys/class/graphics/fb0/rotate
echo 2 > /sys/class/graphics/fb0/rotate
echo 2 > /sys/class/graphics/fb0/rotate
sleep 3

# Remember not to env -i, it messes up with DEVICE_CODENAME for example
# Debug
env PATH="/app-bin:/system-bin" LD_LIBRARY_PATH="/system-lib/lib:/system-lib/qt/lib:/app-lib" QT_QPA_PLATFORM="kobo:debug:keyboard:mouse" QT_PLUGIN_PATH="/system-lib/qt/plugins/" QT_LOGGING_RULES=qt.qpa.input=true /system-lib/lib/ld-linux-armhf.so.3 /app-bin/feathernotes.bin

# Normal
# env PATH="/app-bin:/system-bin" LD_LIBRARY_PATH="/system-lib/lib:/system-lib/qt/lib:/app-lib" QT_QPA_PLATFORM="kobo:keyboard:mouse" QT_PLUGIN_PATH="/system-lib/qt/plugins/" /system-lib/lib/ld-linux-armhf.so.3 /app-bin/feathernotes.bin
