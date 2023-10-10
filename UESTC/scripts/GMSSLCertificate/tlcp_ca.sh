#!/bin/bash -x

# ca begin

gmssl sm2keygen -pass $1 -out ca.key.pem
gmssl certgen -C CN -ST Chengdu -L QHSM -O ZDXLZ -OU CS -CN CA -days 365 -key ca.key.pem -pass $1 -key_usage keyCertSign -key_usage cRLSign -ca -out ca.crt.pem
gmssl certparse -in ca.crt.pem

# ca end