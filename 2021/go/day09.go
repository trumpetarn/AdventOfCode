package main

/*
Day 09: Smoke Basin

https://adventofcode.com/2021/day/9
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"sort"
	"strconv"
	"strings"
)

type Point struct {
	x int
	y int
}

var inputFile = flag.String("input", "../inputs/day09.txt", "Relative path to input-file")

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

func star1(data [][]int) []Point {
	h := len(data)
	w := len(data[0])
	risk := 0
	var lows []Point
	for i := 0; i < h; i++ {
		for j := 0; j < w; j++ {
			var adj []int
			pos := data[i][j]
			if i > 0 {
				adj = append(adj, data[i-1][j])
			}
			if i+1 < h {
				adj = append(adj, data[i+1][j])
			}
			if j > 0 {
				adj = append(adj, data[i][j-1])
			}
			if j+1 < w {
				adj = append(adj, data[i][j+1])
			}

			lp := true
			for _, n := range adj {
				if pos >= n {
					lp = false
					break
				}
			}
			if lp {
				risk += pos + 1
				lows = append(lows, Point{i, j})
			}
		}
	}
	fmt.Println("Star 1:", risk)
	return lows
}

func star2(data [][]int, lows []Point) {
	h := len(data)
	w := len(data[0])
	var basins []int
	for _, p := range lows {
		basin := make(map[Point]bool)
		var points []Point
		basin[p] = true
		points = append(points, p)
		if p.x > 0 {
			np := Point{p.x - 1, p.y}
			if data[np.x][np.y] < 9 {
				basin[np] = true
				points = append(points, np)
			}
		}
		if p.x+1 < h {
			np := Point{p.x + 1, p.y}
			if data[np.x][np.y] < 9 {
				basin[np] = true
				points = append(points, np)
			}
		}
		if p.y > 0 {
			np := Point{p.x, p.y - 1}
			if data[np.x][np.y] < 9 {
				basin[np] = true
				points = append(points, np)
			}
		}
		if p.y+1 < w {
			np := Point{p.x, p.y + 1}
			if data[np.x][np.y] < 9 {
				basin[np] = true
				points = append(points, np)
			}
		}
		i := 1
		for i < len(points) {
			pt := points[i]
			if pt.x > 0 {
				np := Point{pt.x - 1, pt.y}
				if !basin[np] && data[np.x][np.y] < 9 {
					basin[np] = true
					points = append(points, np)
				}
			}
			if pt.x+1 < h {
				np := Point{pt.x + 1, pt.y}
				if !basin[np] && data[np.x][np.y] < 9 {
					basin[np] = true
					points = append(points, np)
				}
			}
			if pt.y > 0 {
				np := Point{pt.x, pt.y - 1}
				if !basin[np] && data[np.x][np.y] < 9 {
					basin[np] = true
					points = append(points, np)
				}
			}
			if pt.y+1 < w {
				np := Point{pt.x, pt.y + 1}
				if !basin[np] && data[np.x][np.y] < 9 {
					basin[np] = true
					points = append(points, np)
				}
			}
			i++
		}
		basins = append(basins, len(points))
	}
	sort.Ints(basins)
	fmt.Println("Star 2:", basins[len(basins)-1]*basins[len(basins)-2]*basins[len(basins)-3])
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n")
	input := input2slice(data)
	lows := star1(input)
	star2(input, lows)
}
