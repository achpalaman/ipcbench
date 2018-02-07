#! /bin/bash
ROOT=`pwd`
find . -name '*.out' -delete
go build
cd $ROOT/serv
gcc server_tcp.c helpers.c callbacks.c -luv -o tcp.out
./tcp.out > /dev/null 2>&1 &
TCPID=$!
gcc server_uds.c helpers.c callbacks.c -luv -o uds.out
./uds.out > /dev/null 2>&1 &
UDPID=$!
cd $ROOT
go test -bench=.
kill $TCPID
kill $UDPID
find . -name '*.out' -delete
