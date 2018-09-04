package main

import "fmt"

/* Eratosthenes(n) returns the list of prime numbers inferior or equal to n */
func Eratosthenes(n int) (primes []int) {
  primes = []int {2}
  non_primes := make(map[int]int)
  i := 3
  for i <= n {
    for i <= n && non_primes[i] != 0 {
      delete(non_primes, i)
      i += 2
    }
    if i > n {
      return primes
    }
    j := i
    for i * j <= n {
      non_primes[i*j] = 1
      j += 1
    }
    i += 1
  }
  return primes
}

func main() {
	prime := Eratosthenes(100000)
	fmt.Println(prime)
}
