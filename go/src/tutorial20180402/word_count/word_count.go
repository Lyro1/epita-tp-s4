package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

/*
   WordCount(words) build a map of each distinct words appearing in the string
   slice words and attach the number of occurrences of each words.
*/
func WordCount(words []string) (wc map[string]int) {
  wc = make(map[string]int)
  for i := 0; i < len(words); i++ {
    wc[words[i]] += 1
  }
  return wc
}

/*
   LoadFile(fname) opens the file fname, reads the content and split it into
   words.
*/
func LoadFile(fname string) (words []string) {
  file, err := os.Open(fname) // For read access.
  if err != nil {
  	panic(err)
  }

  str, err := ioutil.ReadAll(file) // To get the string from file
	if err != nil {
		panic(err)
	}

  words = strings.Fields(string(str))
  return
}

func main() {
	if len(os.Args) < 2 {
		panic("Missing argument")
	}
	wc := WordCount(LoadFile(os.Args[1]))
	fmt.Println(wc)
}
