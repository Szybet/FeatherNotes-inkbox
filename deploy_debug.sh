#!/bin/bash -x

servername="root@10.42.0.28"
passwd="root"

sshpass -p $passwd ssh $servername "bash -c \"rm /kobo/feathernotes\""
sshpass -p $passwd scp build/feathernotes/feathernotes $servername:/kobo/
