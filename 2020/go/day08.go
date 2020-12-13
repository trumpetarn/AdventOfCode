package main

/*
Day 08: Handheld Halting

https://adventofcode.com/2020/day/8
*/

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

/* Runs instructions (acc, jmp, nop),
returns accumulated value (acc) and bool (true if ending correctly)
*/
func runInstructions(data []string) (int, bool) {
	var acc int
	visited := make(map[int]bool)
	i := 0
	for {
		if visited[i] || i >= len(data) {
			return acc, i >= len(data)
		}
		visited[i] = true
		row := strings.Split(data[i], " ")
		val, _ := strconv.Atoi(row[1])
		switch row[0] {
		case "acc":
			acc += val
			i++
		case "jmp":
			i += val
		case "nop":
			i++
		default:
			fmt.Println("Oops, something went wrong")
		}
		//fmt.Println(row[0], row[1])
	}
}

func star1(data []string) {
	acc, _ := runInstructions(data)
	fmt.Println("Star 1:", acc)
}

func star2(data []string) {
	var acc int
	var end bool
	for i, ins := range data {
		if ins[0:3] == "jmp" {
			data[i] = "nop" + ins[3:]
			acc, end = runInstructions(data)
			data[i] = "jmp" + ins[3:]
		} else if ins[0:3] == "nop" {
			data[i] = "jmp" + ins[3:]
			acc, end = runInstructions(data)
			data[i] = "nop" + ins[3:]
		}
		if end {
			break
		}
	}
	fmt.Println("Star 2:", acc)
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day08.txt")
	data := strings.Split(string(raw), "\n")
	star1(data[:len(data)-1])
	star2(data[:len(data)-1])
}
