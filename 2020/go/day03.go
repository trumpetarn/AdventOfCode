package main

/*
Day 03: Toboggan Trajectory

https://adventofcode.com/2020/day/3
*/

import (
	"fmt"
	"io/ioutil"
	"strings"
)

func slide(rstep int, dstep int, data []string) int {
	x := 0
	trees := 0
	for y, s := range data {
		if y%dstep != 0 {
			continue
		}
		if s[x%len(s)] == '#' {
			trees++
		}
		x += rstep
	}
	return trees
}

func star1(data []string) {
	t := slide(3, 1, data)
	fmt.Println("Star 1:", t)
}

func star2(data []string) {
	t1 := slide(1, 1, data)
	t2 := slide(3, 1, data)
	t3 := slide(5, 1, data)
	t4 := slide(7, 1, data)
	t5 := slide(1, 2, data)
	fmt.Println("Star 2:", t1*t2*t3*t4*t5)
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day03.txt")
	lnData := strings.Split(string(raw), "\n")
	data := lnData[:len(lnData)-1] // Remove last row (empty)
	star1(data)
	star2(data)
}
