package main

import (
	"fmt"
	"math/rand"
	"tutorial20180402/merge_sort"
)

func sorted_fill(l []int) {
	for i, _ := range l {
		l[i] = i
	}
}

func rev_fill(l []int) {
	j := len(l) - 1
	for i, _ := range l {
		l[i] = j - i
	}
}

func main() {
	l := make([]int, 256)
	sorted_fill(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)
	l = merge_sort.MergeSort(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)

	rev_fill(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)
	l = merge_sort.MergeSort(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)

	l = rand.Perm(len(l))
	fmt.Println("Array:")
	fmt.Println("  ", l)
	l = merge_sort.MergeSort(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)
}
