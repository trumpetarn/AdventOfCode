package main

/*
Day 05: Hydrothermal Venture

https://adventofcode.com/2021/day/5
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"math"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day05.txt", "Relative path to input-file")

const gridSize = 1024

/*
type Point struct {
	x int
	y int
}

type Line struct {
	p1 Point
	p2 Point
}
*/
func star1(instructions []string) {
	var x1, x2, y1, y2 int
	var grid [gridSize][gridSize]int
	for _, ins := range instructions {
		fmt.Sscanf(ins, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2)
		// Only horizontal/vertical
		if x1 == x2 {
			for i := y1; i <= y2; i++ {
				grid[x1][i]++
			}
			for i := y1; i >= y2; i-- {
				grid[x1][i]++
			}
		} else if y1 == y2 {
			for i := x1; i <= x2; i++ {
				grid[i][y1]++
			}
			for i := x1; i >= x2; i-- {
				grid[i][y1]++
			}
		}

	}
	var res int
	for i := 0; i < gridSize; i++ {
		for j := 0; j < gridSize; j++ {
			if grid[i][j] > 1 {
				res++
			}
		}
	}
	fmt.Println("Star 1:", res)
}

func star2(instructions []string) {
	var x1, x2, y1, y2 int
	var grid [gridSize][gridSize]int
	for _, ins := range instructions {
		fmt.Sscanf(ins, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2)
		if x1 == x2 {
			for i := y1; i <= y2; i++ {
				grid[x1][i]++
			}
			for i := y1; i >= y2; i-- {
				grid[x1][i]++
			}
		} else if y1 == y2 {
			for i := x1; i <= x2; i++ {
				grid[i][y1]++
			}
			for i := x1; i >= x2; i-- {
				grid[i][y1]++
			}
		} else {
			//diagonal

			for i := 0; i <= int(math.Abs(float64(x1-x2))); i++ {
				if x1 < x2 && y1 < y2 {
					grid[x1+i][y1+i]++
				} else if x1 > x2 && y1 < y2 {
					grid[x1-i][y1+i]++
				} else if x1 < x2 && y1 > y2 {
					grid[x1+i][y1-i]++
				} else {
					grid[x1-i][y1-i]++
				}
			}
		}
	}
	var res int
	for i := 0; i < gridSize; i++ {
		for j := 0; j < gridSize; j++ {
			if grid[i][j] > 1 {
				res++
			}
		}
	}
	fmt.Println("Star 2:", res)
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	data := strings.Split(string(raw), "\n")
	star1(data[:len(data)-1])
	star2(data[:len(data)-1])
}
