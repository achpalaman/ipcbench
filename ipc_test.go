package main

import (
	"testing"
)

func BenchmarkCGoNoCopy(b *testing.B) {
	// Setup test
	msg := setupBytes(10)

	b.ResetTimer()
	for n := 0; n < b.N; n++ {
		CGoNoCopy(msg)
	}
}

func BenchmarkCGoCopy(b *testing.B) {
	// Setup test
	msg := setupBytes(10)

	b.ResetTimer()
	for n := 0; n < b.N; n++ {
		CGoCopy(msg)
	}
}

/* Uncomment lines 57, 58 in callbacks.c to run the test
   with two-way communication between C and Go
 */

func BenchmarkTCP(b *testing.B) {
	// Setup test
	msg := setupBytes(10)
	conn := setupTCPConn()
	//scratch := make([]byte, 10)

	b.ResetTimer()
	for n := 0; n < b.N; n++ {
		conn.Write(msg)
		//conn.Read(scratch)
	}
}

func BenchmarkUDS(b *testing.B) {
	// Setup test
	msg := setupBytes(10)
	conn := setupUDSConn()
	//scratch := make([]byte, 10)

	b.ResetTimer()
	for n := 0; n < b.N; n++ {
		conn.Write(msg)
		//conn.Read(scratch)
	}
}