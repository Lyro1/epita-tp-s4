/*
    factorial: a simple factorial demo
*/

package main

import (
    "fmt"
    "log"
    "os"
    "strconv"
)

// Fact(n): computes n!
func Fact(n int) int {
    if n == 0 || n == 1 {
        return 1
    }
    return n*Fact(n-1)
}

func main() {
	if len(os.Args) < 2 {
		log.Fatalln("missing arguments")
	}
	n, err := strconv.ParseInt(os.Args[1], 10, 32)
	if err != nil || n < 0 {
		log.Fatalf("argument %v is not a proper positive integer", os.Args[1])
	}
	fmt.Printf("Fact(%v) = %v\n", n, Fact(int(n)))
}
