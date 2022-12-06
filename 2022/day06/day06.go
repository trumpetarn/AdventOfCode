package main

/*
   Day 06: https://adventofcode.com/2022/day/6
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day06.txt", "Relative path to input-file")

func star1(data string) {
	for i := 0; i < len(data)-4; i++ {
		substr := data[i : i+4]
		set := make(map[rune]bool)
		for _, r := range substr {
			set[r] = true
		}
		if len(set) == 4 {
			fmt.Println("Star 1:", i+4)
			break
		}
	}
}

func star2(data string) {
	for i := 0; i < len(data)-14; i++ {
		substr := data[i : i+14]
		set := make(map[rune]bool)
		for _, r := range substr {
			set[r] = true
		}
		if len(set) == 14 {
			fmt.Println("Star 2:", i+14)
			break
		}
	}
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n")
	star1(data[0])
	star2(data[0])
}
