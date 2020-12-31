package main

/*
Day 22: Crab Combat

https://adventofcode.com/2020/day/22
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
	//"time"
)

var input = flag.String("input", "../inputs/day22.txt", "Relative path to input-file")
var star = flag.Int("star", 0, "Which star to run (0=both)")

func star1(data []string) {
	var p1, p2 []int
	p1d := strings.Split(data[0], "\n")
	p2d := strings.Split(data[1], "\n")
	for _, v := range p1d[1:] {
		n, _ := strconv.Atoi(v)
		p1 = append(p1, n)
	}
	for _, v := range p2d[1 : len(p2d)-1] {
		n, _ := strconv.Atoi(v)
		p2 = append(p2, n)
	}

	for len(p1) != 0 && len(p2) != 0 {
		a := p1[0]
		b := p2[0]
		p1 = p1[1:]
		p2 = p2[1:]

		if a > b {
			p1 = append(p1, a)
			p1 = append(p1, b)
		} else {
			p2 = append(p2, b)
			p2 = append(p2, a)
		}
	}
	var winner []int
	if len(p1) > 0 {
		winner = p1
	} else {
		winner = p2
	}
	sum := 0
	for i, v := range winner {
		sum += (len(winner) - i) * v
	}

	fmt.Println("Star 1:", sum)
}
func equals(a []int, b []int) bool {
	if len(a) != len(b) {
		return false
	}
	for i, v := range a {
		if v != b[i] {
			return false
		}
	}
	return true
}

func inHistory(p []int, phist [][]int) bool {
	for _, r := range phist {
		if equals(r, p) {
			//fmt.Println("Hst")
			return true
		}
	}
	return false
}

func recursiveCombat(p1 []int, p2 []int, xy int) (bool, []int, []int) {
	p1wins := false
	var p1hist [][]int
	var p2hist [][]int
	f := 1
	for len(p1) != 0 && len(p2) != 0 {
		//time.Sleep(1 * time.Second)
		// fmt.Println(xy, len(p1hist))
		if inHistory(p1, p1hist) || inHistory(p2, p2hist) {
			return true, p1, p2
		}
		p1hist = append(p1hist, p1)
		p2hist = append(p2hist, p2)

		a := p1[0]
		b := p2[0]
		p1 = p1[1:]
		p2 = p2[1:]
		//fmt.Println("Round", f, "Game", xy)
		//fmt.Println("P1 plays", a, p1)
		//fmt.Println("P2 plays", b, p2)
		p1wins = (a > b)
		if a <= len(p1) && b <= len(p2) {
			p1cpy := make([]int, a)
			p2cpy := make([]int, b)
			for i, v := range p1[:a] {
				p1cpy[i] = v
			}
			for i, v := range p2[:b] {
				p2cpy[i] = v
			}
			//fmt.Println("Recursion", a, b, p1, p2)
			p1wins, _, _ = recursiveCombat(p1cpy, p2cpy, xy+1)
		}

		if p1wins {
			p1 = append(p1, a)
			p1 = append(p1, b)
		} else {
			p2 = append(p2, b)
			p2 = append(p2, a)
		}
		f++
	}
	//fmt.Println("Game done", p1, p2)
	return p1wins, p1, p2
}

func star2(data []string) {
	var p1, p2, p1x, p2x []int
	p1d := strings.Split(data[0], "\n")
	p2d := strings.Split(data[1], "\n")
	for _, v := range p1d[1:] {
		n, _ := strconv.Atoi(v)
		p1 = append(p1, n)
	}
	for _, v := range p2d[1 : len(p2d)-1] {
		n, _ := strconv.Atoi(v)
		p2 = append(p2, n)
	}
	var p1w bool
	p1w, p1x, p2x = recursiveCombat(p1, p2, 1)
	//fmt.Println("P1",p1x)
	//fmt.Println("P2",p2x)

	var winner []int
	if p1w {
		winner = p1x
	} else {
		winner = p2x
	}
	sum := 0
	for i, v := range winner {
		sum += (len(winner) - i) * v
	}

	fmt.Println("Star 2:", sum)
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*input)
	if err != nil {
		panic("Invalid file")
	}
	data := strings.Split(string(raw), "\n\n")
	if *star == 0 || *star == 1 {
		star1(data)
	}
	if *star == 0 || *star == 2 {
		star2(data)
	}
}
