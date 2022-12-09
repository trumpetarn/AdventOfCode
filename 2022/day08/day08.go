package main

/*
   Day 08: https://adventofcode.com/2022/day/8
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day08.txt", "Relative path to input-file")

func inputToMatrix(data []string) [][]int {
	mx := make([][]int, len(data))
	for i, ln := range data {
		mx[i] = make([]int, len(ln))
		for j, r := range ln {
			a, _ := strconv.Atoi(string(r))
			mx[i][j] = a
		}
	}
	return mx
}

func isLargerThan(x int, y []int) bool {
	for _, v := range y {
		if v >= x {
			return false
		}
	}
	return true
}

func isVisible(val int, row, col []int, i, j int) bool {
	if i == 0 || j == 0 || i == len(col)-1 || j == len(row)-1 {
		return true
	}

	left := row[:j]
	right := row[j+1:]
	top := col[:i]
	bottom := col[i+1:]

	if isLargerThan(val, left) {
		return true
	}

	if isLargerThan(val, right) {
		return true
	}

	if isLargerThan(val, top) {
		return true
	}
	return isLargerThan(val, bottom)
}

func getCol(m [][]int, c int) []int {
	col := make([]int, 0)
	for _, row := range m {
		col = append(col, row[c])
	}
	return col
}

func findVisible(data [][]int) int {
	test := 0
	for i, row := range data {
		for j, y := range row {
			col := getCol(data, j)
			fmt.Print(y)
			if isVisible(y, row, col, i, j) {
				fmt.Print("* ")
				test++
			} else {
				fmt.Print("  ")
			}
		}
		fmt.Println("")
	}
	return test
}

func star1(data [][]int) {
	fmt.Println("Star 1:", findVisible(data))
}

func star2(data [][]int) {
	fmt.Println("Star 2:", data[0])
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n")
	m := inputToMatrix(data)
	fmt.Println(m)
	star1(m)
	star2(m)
}
