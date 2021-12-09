package main

/*
Day 07: The Treachery of Whales

https://adventofcode.com/2021/day/7
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"math"
	"sort"
	"strconv"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day07.txt", "Relative path to input-file")

func star1(data []int) {
	sort.Ints(data)
	minFuel := float64(999999999)
	var pos int
	for i := data[0]; i < data[len(data)-1]; i++ {
		fuel := float64(0)
		for _, n := range data {
			fuel += math.Abs(float64(n - i))
		}
		if fuel < minFuel {
			minFuel = fuel
			pos = i
		}
	}

	fmt.Println("Star 1:", pos, minFuel)
}

func star2(data []int) {
	sort.Ints(data)
	minFuel := float64(999999999)
	var pos int
	for i := data[0]; i < data[len(data)-1]; i++ {
		fuel := float64(0)
		for _, n := range data {
			dist := math.Abs(float64(n - i))
			fuel += ((dist + 1) / 2) * dist
		}
		if fuel < minFuel {
			minFuel = fuel
			pos = i
		}
	}

	fmt.Printf("Star 2: %d, %d\n", pos, int64(minFuel))
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, ",")
	var pos []int
	for _, s := range data {
		n, _ := strconv.Atoi(s)
		pos = append(pos, n)
	}
	star1(pos)
	star2(pos)
}
