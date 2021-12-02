package main

/*
Day 02: Dive!

https://adventofcode.com/2021/day/2
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day02.txt", "Relative path to input-file")

type Coord struct {
	x   int
	y   int
	aim int
}

func star1(data []string) {
	var pos Coord
	var s string
	var n int
	for _, instr := range data {
		m, _ := fmt.Sscanf(instr, "%s %d", &s, &n)
		if m != 2 {
			break
		}
		switch s {
		case "down":
			pos.y += n
		case "up":
			pos.y -= n
		case "forward":
			pos.x += n
		default:
			continue
		}
	}
	fmt.Println("Star 1:", pos.x*pos.y)
}

func star2(data []string) {
	var sub Coord
	var s string
	var n int
	for _, instr := range data {
		m, _ := fmt.Sscanf(instr, "%s %d", &s, &n)
		if m != 2 {
			break
		}
		switch s {
		case "down":
			sub.aim += n
		case "up":
			sub.aim -= n
		case "forward":
			sub.x += n
			sub.y += n * sub.aim
		default:
			continue
		}
	}
	fmt.Println("Star 2:", sub.x*sub.y)
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	data := strings.Split(string(raw), "\n")
	star1(data)
	star2(data)
}
