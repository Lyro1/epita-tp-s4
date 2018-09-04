// bin_search.go: simple binary search in sorted array of integer.
package main

import (
	"flag"
	"fmt"
	"math/rand"
    "time"
)

// BinSearch(tab, x) search for x in tab using efficient binary searching
// algorithm
// Returns a pair made of a position and a boolean, the boolean is false if x
// is not in the array, true otherwise.
func BinSearch(tab []int, x int) (int, bool) {
	begin, end := 0, len(tab) - 1
    m := (end+begin)/2
    for begin < end {
        if tab[m] >= x {
            end = m
        } else {
            begin = m+1
        }
        m = (end+begin)/2
    }
    return m, tab[m] == x
}

// genSortedArray(size) build a random sorted array of len size
func genSortedArray(size int) []int {
	tab := make([]int, size)
	cur := rand.Intn(32)
	for i := 0; i < size; i++ {
		tab[i] = cur
		cur += rand.Intn(16) + 1
	}
	return tab
}

// bin_search: test binary searching
func main() {
	var size int
	var seed int64 // mandatory for rand.Seed()
	// Flags

    flag.IntVar(&size, "s", 10, "Size of the array.")
    flag.Int64Var(&seed, "r", time.Now().UTC().UnixNano(), "The seed used to generate random numbers in the array.")

    flag.Parse()

	// Init random generator
	rand.Seed(seed)

    tab := genSortedArray(size)
	fmt.Println(tab)
	pos := rand.Intn(size)
	x := tab[pos]
	fmt.Println("\nSearch for existing element:", x)
	pos_res, found := BinSearch(tab, x)
	fmt.Printf("BinSearch(tab, x): (%v, %v)\n", pos_res, found)

	x = tab[0] + rand.Intn(tab[len(tab)-1]-tab[0])
	fmt.Println("\nSearch for random element:", x)
	pos_res, found = BinSearch(tab, x)
	fmt.Printf("BinSearch(tab, x): (%v, %v)\n", pos_res, found)
}
