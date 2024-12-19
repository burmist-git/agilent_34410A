#!/bin/bash

n_meas=1000
file_out="agilent_34410A_meas.csv"
echo "time_unix,RES" | tee -a $file_out
for i in $(seq 1 $n_meas)
do
    time_unix=$(date +%s)
    RES=$(sudo python3 agilent_34410A_t.py file /dev/usbtmc0 | grep RES: | awk '{print $2}')
    echo "$time_unix,$RES" | tee -a $file_out
    sleep 1
done
