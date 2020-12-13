package main

/*
Day 06: Custom Customs

https://adventofcode.com/2020/day/6
*/

import (
	"fmt"
	"io/ioutil"
	"strings"
)

func star1(data []string) {
	var sum int
	for _, s := range data {
		set := make(map[rune]bool)
		for _, c := range s {
			if c != '\n' {
				set[c] = true
			}
		}
		sum += len(set)
	}
	fmt.Println("Star 1:", sum)
}

func star2(data []string) {
	var sum, ppl int
	for _, s := range data {
		set := make(map[rune]int)
		ppl = 1 // start on 1, last entry will not end on '\n'
		for _, c := range s {
			if c != '\n' {
				set[c] += 1
			} else {
				ppl++
			}
		}
		for _, n := range set {
			if n == ppl {
				sum += 1
			}
		}
	}
	fmt.Println("Star 2:", sum)
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day06.txt")
	data := strings.Split(string(raw), "\n\n")
	star1(data)
	star2(data)
}
