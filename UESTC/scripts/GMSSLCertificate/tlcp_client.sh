#!/bin/bash -x

# client begin

gmssl sm2keygen -pass $1 -out client.key.pem
gmssl reqgen -C CN -ST Chengdu -L QHSM -O ZDXLZ -OU CS -CN localclient -key client.key.pem -pass $1 -out client.req.pem
gmssl reqsign -in client.req.pem -days 365 -key_usage digitalSignature -cacert ca.crt.pem -key ca.key.pem -pass $1 -out client.crt.pem
gmssl certparse -in client.crt.pem

# client end