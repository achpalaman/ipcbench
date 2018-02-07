package main

/*
#include "bridge.h"
*/
import "C"

import (
	"fmt"
	"math/rand"
	"unsafe"
	"net"
	"os"
)

func main() {
	fmt.Println("Please run runtests.sh from this directory")
}

func CGoNoCopy(msg []byte) interface{} {
	return C.processBytes((*C.char)(unsafe.Pointer(&msg[0])), (C.int)(len(msg)))
}

func CGoCopy(msg []byte) interface{} {
	return C.processBytes((*C.char)(C.CBytes(msg)), (C.int)(len(msg)))
}

func setupBytes(size int) []byte {
	msg := make([]byte, size)
	rand.Read(msg)
	return msg
}

func setupTCPConn() *net.TCPConn {
	addr := ":9890"
	tcp, err := net.ResolveTCPAddr("tcp", addr)
	if err != nil {
		println("ResolveTCPAddr failed:", err.Error())
		os.Exit(1)
	}
	conn, err := net.DialTCP("tcp", nil, tcp)
	if err != nil {
		panic(err)
	}
	return conn
}

func setupUDSConn() *net.UnixConn {
	path := "serv/tmp.out"
	uds, err := net.ResolveUnixAddr("unix", path)
	if err != nil {
		println("ResolveUnixAddr failed:", err.Error())
		os.Exit(1)
	}
	conn, err := net.DialUnix("unix", nil, uds)
	if err != nil {
		panic(err)
	}
	return conn
}