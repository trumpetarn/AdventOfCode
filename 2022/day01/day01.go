package main

/*
Day 01: Calorie Counting

https://adventofcode.com/2022/day/1
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"sort"
	"strconv"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day01.txt", "Relative path to input-file")

func sum(sl []int) int {
	sum := 0
	for _, n := range sl {
		sum += n
	}
	return sum
}

func star1o2(data []string) {
	var sums []int
	for _, ln := range data {
		sum := 0
		split := strings.Split(ln, "\n")
		for _, n := range split {
			x, _ := strconv.Atoi(n)
			sum += x
		}
		fmt.Println(sum)
		sums = append(sums, sum)
	}
	sort.Ints(sums)
	fmt.Println("Star 1:", sums[len(sums)-1])
	fmt.Println("Star 2:", sum(sums[len(sums)-3:len(sums)]))
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n\n")
	fmt.Println(data)
	star1o2(data)
}
