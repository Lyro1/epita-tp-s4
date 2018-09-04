package main

import "fmt"

func MemoFibo(n int, memo []int) int {
  if memo[n] == -1 {
    memo[n] = Fibo(n)
  }
  return memo[n]
}

func Fibo(n int) (r int) {
	p := 1
	r = 1
	for i := 1; i < n; i++ {
		r += p
		p = r - p
	}
	return
}

const (
	size = 50
)

func main() {
	for i := 0; i < size; i++ {
		fmt.Printf("fibo(%d) = %d\n", i, Fibo(i))
	}
	memo := make([]int, size)
	memo[0], memo[1] = 1, 1
	for i := 2; i < len(memo); i++ {
		memo[i] = -1
	}
	for i := 0; i < size; i++ {
		fmt.Printf("fibo(%d) = %d\n", i, MemoFibo(i, memo))
	}
}
