/*
    hello: my first go program
*/

package main

import (
        "fmt"
        "math/rand"
)

// MyFun(n): prints n and returns it
func MyFun(n int) int {
    fmt.Println("An int : ", n);
    return n;
}

func main() {
    fmt.Println("Hello World!")
    n:=MyFun(rand.Int())
    fmt.Println("return n: ", n);
}
