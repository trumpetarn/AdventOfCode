package main

/*
Day 23: Crab Cups

https://adventofcode.com/2020/day/23
*/

import (
	"container/ring"
	"flag"
	"fmt"
	"strconv"
)

var input = flag.String("input", "598162734", "Input")
var star = flag.Int("star", 0, "Which star to run (0=both)")

func crabCups(data []int, iter int) *ring.Ring {
	cups := ring.New(len(data))
	valMap := make(map[int]*ring.Ring)
	max := -1
	for _, v := range data {
		cups.Value = v
		valMap[v] = cups
		cups = cups.Next()
		if v > max {
			max = v
		}
	}
	for i := 0; i < iter; i++ {
		cvalue := cups.Value.(int)
		dvalue := cvalue - 1
		if dvalue < 1 {
			dvalue = max - dvalue
		}
		picked := cups.Unlink(3)
		for k := 0; k < 3; k++ {
			for j := 0; j < 3; j++ {
				if dvalue == picked.Value.(int) {
					dvalue--
					if dvalue < 1 {
						dvalue = max - dvalue
					}
				}
				picked = picked.Next()
			}
		}
		dest := valMap[dvalue]
		dest.Link(picked)
		cups = cups.Next()
	}
	return valMap[1]
}

func star1(data string) {
	cups := make([]int, len(data))
	for i, r := range data {
		cups[i], _ = strconv.Atoi(string(r))
	}
	r := crabCups(cups, 100)
	fmt.Print("Star 1: ")
	r.Do(func(p interface{}) {
		if p.(int) != 1 {
			fmt.Print(p.(int))
		}
	})
	fmt.Print("\n")
}

func star2(data string) {
	cups := make([]int, len(data))
	for i, r := range data {
		cups[i], _ = strconv.Atoi(string(r))
	}
	for i := 10; i <= 1000000; i++ {
		cups = append(cups, i)
	}
	r := crabCups(cups, 10000000)
	prod := r.Next().Value.(int)
	r = r.Next()
	prod *= r.Next().Value.(int)
	fmt.Println("Star 2:", prod)
}

func main() {
	flag.Parse()
	data := *input
	if *star == 0 || *star == 1 {
		star1(data)
	}
	if *star == 0 || *star == 2 {
		star2(data)
	}
}
