package main

/*
   Day 04: https://adventofcode.com/2022/day/4
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day04.txt", "Relative path to input-file")

func star1(data []string) {
	count := 0
	for _, ln := range data {
		var a1, a2, b1, b2 int
		fmt.Sscanf(ln, "%d-%d,%d-%d", &a1, &a2, &b1, &b2)
		if (a1 <= b1 && b2 <= a2) || (b1 <= a1 && a2 <= b2) {
			count++
		}
	}

	fmt.Println("Star 1:", count)
}

func star2(data []string) {
	count := 0
	for _, ln := range data {
		var a1, a2, b1, b2 int
		fmt.Sscanf(ln, "%d-%d,%d-%d", &a1, &a2, &b1, &b2)
		if (a1 <= b1 && b1 <= a2) || (b1 <= a1 && a1 <= b2) {
			count++
		}
	}
	fmt.Println("Star 2:", count)
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
