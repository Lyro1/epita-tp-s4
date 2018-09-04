/*
    fibo: a basic fibonacci function implementation
*/

package main

import (
    "fmt"
    "log"
    "os"
    "strconv"
)

// _Fibo(n) : computes the recursive fibonacci value of n
func _Fibo(n int) (int, int) {
    if n == 0 {
        return 0,1
    }
    if n <= 2 {
        return 1,1
    }
    a,b := _Fibo(n-1)
    return a+b,a
}

func Fibo(n int) int  {
    x, _ := _Fibo(n)
    return x
}

func main() {
	if len(os.Args) < 2 {
		log.Fatalln("missing arguments")
	}
	n, err := strconv.ParseInt(os.Args[1], 10, 32)
	if err != nil || n < 0 {
		log.Fatalf("argument %v is not a proper positive integer", os.Args[1])
	}
	fmt.Printf("Fibo(%v) = %v\n", n, Fibo(int(n)))
}
