#!/bin/bash -x

# server begin

gmssl sm2keygen -pass $1 -out sig.key.pem
gmssl reqgen -C CN -ST Chengdu -L QHSM -O ZDXLZ -OU CS -CN localserver -key sig.key.pem -pass $1 -out sig.req.pem
gmssl reqsign -in sig.req.pem -days 365 -key_usage digitalSignature -cacert ca.crt.pem -key ca.key.pem -pass $1 -out sig.crt.pem
gmssl certparse -in sig.crt.pem

gmssl sm2keygen -pass $1 -out enc.key.pem
gmssl reqgen -C CN -ST Chengdu -L QHSM -O ZDXLZ -OU CS -CN localserver -key enc.key.pem -pass $1 -out enc.req.pem
gmssl reqsign -in enc.req.pem -days 365 -key_usage keyEncipherment -cacert ca.crt.pem -key ca.key.pem -pass $1 -out enc.crt.pem
gmssl certparse -in enc.crt.pem

cat sig.crt.pem > certs.pem
cat enc.crt.pem >> certs.pem

# server end