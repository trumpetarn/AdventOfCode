package main

/*
Day 15: Rambunctious Recitation

https://adventofcode.com/2020/day/15
*/

import (
	"fmt"
)

func game(data []int, end int) int {
	mem := make(map[int]int)
	for k := 0; k < len(data)-1; k++ {
		mem[data[k]] = k
	}
	last := data[len(data)-1]
	for i := len(data) - 1; i < end-1; i++ {
		if val, ok := mem[last]; ok {
			mem[last] = i
			last = i - val
		} else {
			mem[last] = i
			last = 0
		}
	}
	return last
}

func star1(data []int) {
	fmt.Println("Star 1:", game(data, 2020))
}

func star2(data []int) {
	fmt.Println("Star 2:", game(data, 30000000))
}

func main() {
	data := []int{12, 20, 0, 6, 1, 17, 7}
	//data := []int{0,3,6}
	star1(data)
	star2(data)
}
