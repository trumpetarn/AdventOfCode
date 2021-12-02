package main

/*
Day XX: Title

https://adventofcode.com/2020/day/X
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

var inputFile = flag.String("input", "../inputs/dayXX.txt", "Relative path to input-file")

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
	data := strings.Split(string(raw), "\n\n")
	star1(data)
	star2(data)
}
