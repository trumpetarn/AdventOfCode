package main

/*
Day 11: Dumbo Octopus

https://adventofcode.com/2021/day/11
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

type Point struct {
	x int
	y int
}

var inputFile = flag.String("input", "../inputs/day11.txt", "Relative path to input-file")

const ticks = 100

func input2slice(data []string) [][]int {
	var heights [][]int
	for _, s := range data {
		var tmp []int
		for _, r := range strings.Split(s, "") {
			n, _ := strconv.Atoi(r)
			tmp = append(tmp, n)
		}
		heights = append(heights, tmp)
	}
	return heights
}

func incByOne(matrix [][]int) {
	for i, row := range matrix {
		for j, _ := range row {
			matrix[i][j]++
		}
	}
}

func flash(x, y int, matrix [][]int, flashed map[Point]bool) {
	p := Point{x, y}
	if flashed[p] {
		return
	}
	flashed[p] = true
	h := len(matrix)
	w := len(matrix[0])
	matrix[x][y] = 0
	for i := x - 1; i <= x+1; i++ {
		if i < 0 || i >= h {
			continue
		}
		for j := y - 1; j <= y+1; j++ {
			if j < 0 || j >= w || flashed[Point{i, j}] {
				continue
			}
			matrix[i][j]++
			if matrix[i][j] > 9 {
				flash(i, j, matrix, flashed)
			}
		}
	}
	for k, b := range flashed {
		if b {
			matrix[k.x][k.y] = 0 // since other flashes might have increased once more
		}
	}
}

func printMatrix(m [][]int) {
	for _, row := range m {
		fmt.Println(row)
	}
}
func star1(data [][]int) {
	nFlash := 0
	for i := 0; i < ticks; i++ {
		incByOne(data)
		f := make(map[Point]bool)
		for i, row := range data {
			for j, n := range row {
				if n > 9 {
					flash(i, j, data, f)
					f[Point{i, j}] = true
				}
			}
		}
		nFlash += len(f)
		if len(f) == len(data)*len(data[0]) {
			fmt.Println("Star 2:", i)
		}
	}
	fmt.Println("Star 1:", nFlash)
}

func star2(data [][]int) {
	for i := 0; ; i++ {
		incByOne(data)
		f := make(map[Point]bool)
		for i, row := range data {
			for j, n := range row {
				if n > 9 {
					flash(i, j, data, f)
					f[Point{i, j}] = true
				}
			}
		}
		if len(f) == len(data)*len(data[0]) {
			fmt.Println("Star 2:", i+1)
			return
		}
	}
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n")
	star1(input2slice(data))
	star2(input2slice(data))
}
