package main

/*
Day 20: Title

https://adventofcode.com/2021/day/20
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day20.txt", "Relative path to input-file")

func star1(data []string) {
	fmt.Println("Star 1:", data[0])
}

func star2(data []string) {
	fmt.Println("Star 2:", data[0])
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n\n")
	star1(data)
	star2(data)
}
