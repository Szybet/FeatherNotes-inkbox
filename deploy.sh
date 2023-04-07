#!/bin/bash -x

cp build/feathernotes/feathernotes inkbox_userapp/feathernotes/app-bin/feathernotes.bin

# Very important
rm -f inkbox_userapp/feathernotes.isa.dgst
rm -f inkbox_userapp/feathernotes.isa

mksquashfs inkbox_userapp/feathernotes/* inkbox_userapp/feathernotes.isa

# Yes, here are my private keys. Is providing this info a security thread? no.
openssl dgst -sha256 -sign /home/szybet/inkbox-keys/userapps.pem -out inkbox_userapp/feathernotes.isa.dgst inkbox_userapp/feathernotes.isa

servername="root@10.42.0.28"
passwd="root"

sshpass -p $passwd ssh $servername "bash -c \"ifsctl mnt rootfs rw\""
sshpass -p $passwd ssh $servername "bash -c \"mkdir /data/onboard/.apps/\""
sshpass -p $passwd ssh $servername "bash -c \"mkdir /data/onboard/.apps/feathernotes\""
sshpass -p $passwd ssh $servername "bash -c \"rm /data/onboard/.apps/feathernotes/feathernotes.isa\""
sshpass -p $passwd ssh $servername "bash -c \"rm /data/onboard/.apps/feathernotes/feathernotes.isa.dgst\""
sshpass -p $passwd ssh $servername "bash -c \"rm /data/onboard/.apps/feathernotes/app.json\""

sshpass -p $passwd scp inkbox_userapp/app.json $servername:/data/onboard/.apps/feathernotes/
sshpass -p $passwd scp inkbox_userapp/feathernotes.isa.dgst $servername:/data/onboard/.apps/feathernotes/
sshpass -p $passwd scp inkbox_userapp/feathernotes.isa $servername:/data/onboard/.apps/feathernotes/


sshpass -p $passwd ssh $servername "bash -c \"sync\""

sshpass -p $passwd ssh $servername "bash -c \"killall -9 feathernotes.sh\"" || EXIT_CODE=0

sshpass -p $passwd ssh $servername "bash -c \"service gui_apps restart\""

# sshpass -p $passwd ssh $servername "bash -c \"service inkbox_gui restart\"" & # to get logs

# To update main json
# sleep 15
# sshpass -p $passwd ssh $servername "bash -c \"touch /kobo/tmp/rescan_userapps\"" # This gets deleted by service restart
# sshpass -p $passwd ssh $servername "bash -c \"killall inkbox-bin\""

# sshpass -p $passwd ssh $servername "bash -c \"rc-service gui_apps restart\""


