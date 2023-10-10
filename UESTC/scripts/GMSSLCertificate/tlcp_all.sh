#!/bin/bash -x

#rootca begin

#gmssl sm2keygen -pass 123456 -out root.ca.key.pem
#gmssl certgen -C CN -ST Chengdu -L QHSM -O ZDXLZ -OU CS -CN ROOTCA -days 365 -key root.ca.key.pem -pass 123456 -key_usage keyCertSign -key_usage cRLSign -ca -out root.ca.crt.pem
#gmssl certparse -in root.ca.crt.pem

#rootca end

# ca begin

gmssl sm2keygen -pass $1 -out ca.key.pem
gmssl certgen -C CN -ST Chengdu -L QHSM -O ZDXLZ -OU CS -CN CA -days 365 -key ca.key.pem -pass $1 -key_usage keyCertSign -key_usage cRLSign -ca -out ca.crt.pem
gmssl certparse -in ca.crt.pem

# ca end

# client begin

gmssl sm2keygen -pass $1 -out client.key.pem
gmssl reqgen -C CN -ST Chengdu -L QHSM -O ZDXLZ -OU CS -CN localclient -key client.key.pem -pass $1 -out client.req.pem
gmssl reqsign -in client.req.pem -days 365 -key_usage digitalSignature -cacert ca.crt.pem -key ca.key.pem -pass $1 -out client.crt.pem
gmssl certparse -in client.crt.pem

# client end

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