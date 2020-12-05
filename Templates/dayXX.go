package main
/*
Day XX: Title

https://adventofcode.com/2020/day/X
*/

import (
	"fmt"
	"io/ioutil"
	"strings"
)

func star1(data []string) {
	fmt.Println("Star 1:", data[0])
}

func star2(data []string) {
	fmt.Println("Star 2:", data[0])
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/dayXX.txt")
	data := strings.Split(string(raw), "\n\n")
	star1(data)
	star2(data)
}