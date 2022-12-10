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
			//fmt.Print(y)
			if isVisible(y, row, col, i, j) {
				//fmt.Print("* ")
				test++
			} else {
				//fmt.Print("  ")
			}
		}
		//fmt.Println("")
	}
	return test
}

func star1(data [][]int) {
	fmt.Println("Star 1:", findVisible(data))
}

func computeScenicScore(val int, row, col []int, i, j int) int {
	var left, right, top, bottom int
	//left
	for x := j - 1; x >= 0; x-- {
		left++
		if row[x] >= val {
			break
		}
	}
	//right
	for y := j + 1; y < len(row); y++ {
		right++
		if row[y] >= val {
			break
		}
	}
	//top
	for z := i - 1; z >= 0; z-- {
		top++
		if col[z] >= val {
			break
		}
	}
	//right
	for q := i + 1; q < len(col); q++ {
		bottom++
		if col[q] >= val {
			break
		}
	}
	//fmt.Println(i, j, left*right*top*bottom, ":", top, left, bottom, right)
	return left * right * top * bottom
}

func star2(data [][]int) {
	maxCs := 0
	for i, row := range data {
		for j, val := range row {
			col := getCol(data, j)
			cs := computeScenicScore(val, row, col, i, j)
			if cs > maxCs {
				maxCs = cs
			}
		}
	}
	fmt.Println("Star 2:", maxCs)
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
	star1(m)
	star2(m)
}
