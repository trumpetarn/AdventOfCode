package main

/*
Day 12: Passage Pathing

https://adventofcode.com/2021/day/12
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
	"unicode"
)

var inputFile = flag.String("input", "../inputs/day12.txt", "Relative path to input-file")

func contains(a []string, s string) bool {
	for _, as := range a {
		if as == s {
			return true
		}
	}
	return false
}

func traverse(nodes map[string][]string, start, end string, small []string, numVisit int) int {
	if start == end {
		return 1
	}

	if unicode.IsLower(rune(start[0])) {
		if !contains(small, start) {
			small = append(small, start)
		} else if numVisit > 1 && start != "start" {
			//fmt.Println(small, start)
			numVisit--
		}
	}
	nEnd := 0
	for _, n := range nodes[start] {
		if !contains(small, n) { // Will not cover loops
			nEnd += traverse(nodes, n, end, small, numVisit)
		} else if numVisit > 1 && n != "start" {
			nEnd += traverse(nodes, n, end, small, numVisit)
		}
	}
	return nEnd
}

func star1(data []string) {
	nodes := make(map[string][]string)
	for _, row := range data {
		tmp := strings.Split(row, "-")
		p1 := tmp[0]
		p2 := tmp[1]
		nodes[p1] = append(nodes[p1], p2)
		nodes[p2] = append(nodes[p2], p1)
	}
	var small []string
	n := traverse(nodes, "start", "end", small, 1)
	fmt.Println("Star 1:", n)
}

func star2(data []string) {
	nodes := make(map[string][]string)
	for _, row := range data {
		tmp := strings.Split(row, "-")
		p1 := tmp[0]
		p2 := tmp[1]
		nodes[p1] = append(nodes[p1], p2)
		nodes[p2] = append(nodes[p2], p1)
	}
	var small []string
	small = append(small, "start")
	n := traverse(nodes, "start", "end", small, 2)
	fmt.Println("Star 2:", n)
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n")
	star1(data)
	star2(data)
}
