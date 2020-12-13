package main

/*
Day 10: Adapter Array

https://adventofcode.com/2020/day/10
*/

import (
	"fmt"
	"io/ioutil"
	"sort"
	"strconv"
	"strings"
)

func star1(data []int) {
	ones := 0
	threes := 1 // our device
	if data[0] == 1 {
		ones++
	}
	if data[0] == 3 {
		threes++
	}
	for i := 1; i < len(data); i++ {
		if data[i]-data[i-1] == 1 {
			ones++
		}
		if data[i]-data[i-1] == 3 {
			threes++
		}
		if data[i]-data[i-1] > 3 {
			fmt.Println("Oops")
		}
	}
	fmt.Println("Star 1:", ones, threes, ones*threes)
}

func star2(data []int) {
	paths := make([]int, len(data))
	paths[0] = 1
	// paths, how many ways can you reach a certain index (i) in data
	for i := 0; i < len(data); i++ {
		for j := 1; j <= 3 && j+i < len(data); j++ {
			if data[i+j]-data[i] <= 3 {
				paths[i+j] += paths[i]
			}
		}
	}
	// The device will be reached in the same number of ways as the last adapter
	fmt.Println("Star 2:", paths[len(paths)-1])
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day10.txt")
	data := strings.Split(string(raw), "\n")
	intData := make([]int, len(data))
	intData[0] = 0 // adding the first value
	for i, n := range data[:len(data)-1] {
		intData[i+1], _ = strconv.Atoi(n)
	}
	sort.Ints(intData)
	star1(intData)
	star2(intData)
}
