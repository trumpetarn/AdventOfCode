package main

/*
   Day 03: https://adventofcode.com/2022/day/3
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day03.txt", "Relative path to input-file")

func string2set(A string) map[rune]bool {
	ret := make(map[rune]bool)
	for _, i := range A {
		ret[i] = true
	}
	return ret
}

func star1(data []string) {
	//hmm := make([]map[rune]bool, len(data))
	sum := 0
	for _, ln := range data {
		N := len(ln)
		comp1 := string2set(ln[:N/2])
		comp2 := string2set(ln[N/2:])
		inter := make(map[rune]bool)
		for k, _ := range comp2 {
			if comp1[k] {
				inter[k] = true
				priority := k - 'a' + 1
				if priority < 0 { //Uppercase
					priority = k - 'A' + 27
				}
				sum += int(priority)
			}
		}
		//hmm[i] = inter
	}
	fmt.Println("Star 1:", sum)
}

func star2(data []string) {
	sum := 0
	for i, ln := range data {
		if i%3 == 0 {
			ln1 := string2set(ln)
			ln2 := string2set(data[i+1])
			ln3 := string2set(data[i+2])
			for k, _ := range ln3 {
				if ln1[k] && ln2[k] {
					priority := k - 'a' + 1
					if priority < 0 { //Uppercase
						priority = k - 'A' + 27
					}
					sum += int(priority)
				}
			}
		}
	}
	fmt.Println("Star 2:", sum)
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n")

	star1(data)
	star2(data)
}
