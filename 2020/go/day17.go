package main

/*
Day 17: Conway Cubes

https://adventofcode.com/2020/day/17
*/

import (
	"fmt"
	"io/ioutil"
	//"math"
	//"strconv"
	"strings"
)

func zeroCube(n int) [][][]int {
	ret := make([][][]int, n)
	for k := 0; k < n; k++ {
		ret[k] = make([][]int, n)
		for l := 0; l < n; l++ {
			ret[k][l] = make([]int, n)
		}
	}
	return ret
}

func zeroCube4d(n int) [][][][]int {
	ret := make([][][][]int, n)
	for k := 0; k < n; k++ {
		ret[k] = make([][][]int, n)
		for l := 0; l < n; l++ {
			ret[k][l] = make([][]int, n)
			for m := 0; m < n; m++ {
				ret[k][l][m] = make([]int, n)
			}
		}
	}
	return ret
}

func initCube(data []string) [][][]int {
	start := zeroCube(len(data))
	mid := (len(data)) / 2
	for n, l := range data {
		for i, r := range l {
			if r == '#' {
				start[mid][n][i] = 1
			} else {
				start[mid][n][i] = 0
			}
		}
	}
	return start
}

func initCube4d(data []string) [][][][]int {
	start := zeroCube4d(len(data))
	mid := (len(data)) / 2
	for n, l := range data {
		for i, r := range l {
			if r == '#' {
				start[mid][mid][n][i] = 1
			} else {
				start[mid][mid][n][i] = 0
			}
		}
	}
	return start
}

func getNeighborsVal(x, y, z int, c [][][]int) int {
	val := 0
	for i := x - 1; i <= x+1; i++ {
		if i < 0 || i >= len(c) {
			continue
		}
		for j := y - 1; j <= y+1; j++ {
			if j < 0 || j >= len(c) {
				continue
			}
			for k := z - 1; k <= z+1; k++ {
				if k < 0 || k >= len(c) {
					continue
				}
				if i == x && j == y && k == z {
					continue
				}
				val += c[k][j][i]
			}
		}
	}
	return val
}

func getNeighborsVal4d(x, y, z, w int, c [][][][]int) int {
	val := 0
	for i := x - 1; i <= x+1; i++ {
		if i < 0 || i >= len(c) {
			continue
		}
		for j := y - 1; j <= y+1; j++ {
			if j < 0 || j >= len(c) {
				continue
			}
			for k := z - 1; k <= z+1; k++ {
				if k < 0 || k >= len(c) {
					continue
				}
				for l := w - 1; l <= w+1; l++ {
					if l < 0 || l >= len(c) {
						continue
					}
					if i == x && j == y && k == z && l == w {
						continue
					}
					val += c[l][k][j][i]
				}
			}
		}
	}
	return val
}

func printPlane(p [][]int) {
	for _, j := range p {
		for _, k := range j {
			if k == 1 {
				fmt.Print("#")
			} else {
				fmt.Print(".")
			}
		}
		fmt.Println("")
	}
}

func printCube(cube [][][]int) {
	for _, i := range cube {
		printPlane(i)
		fmt.Println("")
	}
}

func conway(cube [][][]int) [][][]int {
	new := zeroCube(len(cube) + 2)
	for i := -1; i < len(cube)+1; i++ {
		for j := -1; j < len(cube)+1; j++ {
			for k := -1; k < len(cube)+1; k++ {
				nv := getNeighborsVal(k, j, i, cube)
				n := 0
				if (i >= 0 && j >= 0 && k >= 0) && (i < len(cube) && j < len(cube) && k < len(cube)) {
					n = cube[i][j][k]
				}
				if nv == 3 {
					new[i+1][j+1][k+1] = 1
				} else if n == 1 && nv == 2 {
					new[i+1][j+1][k+1] = 1
				} else {
					new[i+1][j+1][k+1] = 0
				}
			}
		}
	}
	return new
}

func conway4d(cube [][][][]int) [][][][]int {
	new := zeroCube4d(len(cube) + 2)
	for i := -1; i < len(cube)+1; i++ {
		for j := -1; j < len(cube)+1; j++ {
			for k := -1; k < len(cube)+1; k++ {
				for l := -1; l < len(cube)+1; l++ {
					nv := getNeighborsVal4d(l, k, j, i, cube)
					n := 0
					if (i >= 0 && j >= 0 && k >= 0 && l >= 0) && (i < len(cube) && j < len(cube) && k < len(cube) && l < len(cube)) {
						n = cube[i][j][k][l]
					}
					if nv == 3 {
						new[i+1][j+1][k+1][l+1] = 1
					} else if n == 1 && nv == 2 {
						new[i+1][j+1][k+1][l+1] = 1
					} else {
						new[i+1][j+1][k+1][l+1] = 0
					}
				}
			}
		}
	}
	return new
}

func sumCube(cube [][][]int) int {
	ret := 0
	for _, p := range cube {
		for _, l := range p {
			for _, n := range l {
				ret += n
			}
		}
	}
	return ret
}

func sumCube4d(cube [][][][]int) int {
	ret := 0
	for _, p := range cube {
		for _, l := range p {
			for _, n := range l {
				for _, v := range n {
					ret += v
				}
			}
		}
	}
	return ret
}

func star1(cube [][][]int) {
	for i := 0; i < 6; i++ {
		cube = conway(cube)
	}
	fmt.Println("Star 1:", sumCube(cube))
}

func star2(cube [][][][]int) {
	for i := 0; i < 6; i++ {
		cube = conway4d(cube)
	}
	fmt.Println("Star 2:", sumCube4d(cube))
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day17.txt")
	data := strings.Split(string(raw), "\n")
	start := initCube(data[:len(data)-1])
	star1(start)
	start2 := initCube4d(data[:len(data)-1])
	star2(start2)
}
