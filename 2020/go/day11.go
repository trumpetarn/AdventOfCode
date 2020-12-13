package main

/*
Day 11: Seating System

https://adventofcode.com/2020/day/11
*/

import (
	"fmt"
	"io/ioutil"
	"strings"
	//"strconv"
	//"sort"
)

func initMap(data []string) [][]rune {
	newMap := make([][]rune, len(data))
	for i, line := range data {
		newMap[i] = make([]rune, len(data[i]))
		for j, r := range line {
			newMap[i][j] = r
		}
	}
	return newMap
}

func getAdjacent(rmap [][]rune, i0 int, j0 int) []rune {
	istart := i0 - 1
	iend := i0 + 1
	jstart := j0 - 1
	jend := j0 + 1

	if istart < 0 {
		istart = 0
	}
	if jstart < 0 {
		jstart = 0
	}
	if iend >= len(rmap) {
		iend = len(rmap) - 1
	}
	if jend >= len(rmap[i0]) {
		jend = len(rmap[i0]) - 1
	}

	adj := make([]rune, (iend-istart+1)*(jend-jstart+1))
	x := 0
	for i := istart; i <= iend; i++ {
		for j := jstart; j <= jend; j++ {
			if i == i0 && j == j0 {
				continue
			}
			adj[x] = rmap[i][j]
			x++
		}
	}
	return adj
}

func getVisible(rmap [][]rune, i0 int, j0 int) []rune {
	allVis := make([]rune, 8*len(rmap))
	var f1, f2, f3, f4, f5, f6, f7, f8 bool
	x := 0
	for i := 1; i < len(rmap); i++ {
		if i0-i >= 0 && !f1 {
			allVis[x] = rmap[i0-i][j0]
			if allVis[x] != '.' {
				f1 = true
			}
			x++
		}
		if j0-i >= 0 && !f2 {
			allVis[x] = rmap[i0][j0-i]
			if allVis[x] != '.' {
				f2 = true
			}
			x++
		}
		if i0+i < len(rmap) && !f3 {
			allVis[x] = rmap[i0+i][j0]
			if allVis[x] != '.' {
				f3 = true
			}
			x++
		}
		if j0+i < len(rmap[0]) && !f4 {
			allVis[x] = rmap[i0][j0+i]
			if allVis[x] != '.' {
				f4 = true
			}
			x++
		}

		if i0+i < len(rmap) && j0+i < len(rmap[0]) && !f5 {
			allVis[x] = rmap[i0+i][j0+i]
			if allVis[x] != '.' {
				f5 = true
			}
			x++
		}

		if i0-i >= 0 && j0+i < len(rmap[0]) && !f6 {
			allVis[x] = rmap[i0-i][j0+i]
			if allVis[x] != '.' {
				f6 = true
			}
			x++
		}

		if i0-i >= 0 && j0-i >= 0 && !f7 {
			allVis[x] = rmap[i0-i][j0-i]
			if allVis[x] != '.' {
				f7 = true
			}
			x++
		}

		if i0+i < len(rmap) && j0-i >= 0 && !f8 {
			allVis[x] = rmap[i0+i][j0-i]
			if allVis[x] != '.' {
				f8 = true
			}
			x++
		}
		if f1 && f2 && f3 && f4 && f5 && f6 && f7 && f8 {
			break
		}
	}
	return allVis[:x]
}

func freeSeat(rmap [][]rune, i int, j int, vis bool) rune {
	var seats []rune
	if vis {
		seats = getVisible(rmap, i, j)
	} else {
		seats = getAdjacent(rmap, i, j)
	}
	for _, r := range seats {
		if r == '#' {
			return 'L'
		}
	}
	return '#'
}

func occupiedSeat(rmap [][]rune, i int, j int, vis bool) rune {
	var seats []rune
	if vis {
		seats = getVisible(rmap, i, j)
	} else {
		seats = getAdjacent(rmap, i, j)
	}
	occ := 0
	for _, r := range seats {
		if r == '#' {
			occ++
		}
	}
	n := 4
	if vis {
		n = 5
	}
	if occ >= n {
		return 'L'
	}
	return '#'
}

func countRune(r rune, rmap [][]rune) int {
	res := 0
	for _, n := range rmap {
		for _, m := range n {
			if m == r {
				res++
			}
		}
	}
	return res
}

func tick(oldMap [][]rune, s2 bool) [][]rune {
	newMap := make([][]rune, len(oldMap))
	for i := 0; i < len(oldMap); i++ {
		newMap[i] = make([]rune, len(oldMap[i]))
		for j := 0; j < len(oldMap[i]); j++ {
			switch oldMap[i][j] {
			case 'L':
				//free
				newMap[i][j] = freeSeat(oldMap, i, j, s2)
			case '#':
				newMap[i][j] = occupiedSeat(oldMap, i, j, s2)
			case '.':
				newMap[i][j] = '.'
			default:
				panic("Invalid rune")
			}
		}
	}
	return newMap
}

func star1(data []string) {
	smap := initMap(data)
	last := -1
	next := countRune('#', smap)
	for last != next {
		smap = tick(smap, false)
		last = next
		next = countRune('#', smap)
	}
	fmt.Println("Star 1:", next)
}

func star2(data []string) {
	smap := initMap(data)
	last := -1
	next := countRune('#', smap)
	for last != next {
		smap = tick(smap, true)
		last = next
		next = countRune('#', smap)
	}
	fmt.Println("Star 2:", next)
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day11.txt")
	data := strings.Split(string(raw), "\n")
	star1(data[:len(data)-1])
	star2(data[:len(data)-1])
}
