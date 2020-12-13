package main

/*
Day 13: Shuttle Search

https://adventofcode.com/2020/day/13
*/

import (
	"fmt"
	"io/ioutil"
	"strings"
	//"math"
	"strconv"
	//"sort"
	//"time"
)

func star1(timestamp int, IDs []int) {
	min := 99999
	id := -1
	for _, n := range IDs {
		if n == 1 {
			continue
		}
		// We assume there won't be a perfect match
		x := n - (timestamp % n)
		if x < min {
			min = x
			id = n
		}
	}
	fmt.Println("Star 1:", min*id)
}

func star2(IDs []int) {
	timestamp := 1
	for {
		nextTs := 1
		isDone := true
		for i := 0; i < len(IDs); i++ {
			if (timestamp+i)%IDs[i] != 0 {
				isDone = false
				break
			}
			// We have found a timestamp that works, since all inputs are prime we can multiply
			// all ts that works to find the next time all found will match again
			nextTs *= IDs[i]
		}
		if isDone {
			break
		}
		timestamp += nextTs
	}
	fmt.Println("Star 2:", timestamp)
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day13.txt")
	data := strings.Split(string(raw), "\n")
	ts, _ := strconv.Atoi(data[0])
	IDs := strings.Split(data[1], ",")
	busIDs := make([]int, len(IDs))
	for i, n := range IDs {
		if n != "x" {
			busIDs[i], _ = strconv.Atoi(n)
		} else {
			busIDs[i] = 1
		}
	}
	star1(ts, busIDs)
	star2(busIDs)
}
