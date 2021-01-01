package main

/*
Day 24: Lobby Layout

https://adventofcode.com/2020/day/24
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

var input = flag.String("input", "../inputs/day24.txt", "Relative path to input-file")

const (
	WHITE = 0
	BLACK = 1
)

type Coord struct {
	x float64
	y float64
}

func countBlack(grid map[Coord]int) int {
	sum := 0
	for _, tile := range grid {
		if tile == BLACK {
			sum++
		}
	}
	return sum
}

func star1(data []string) map[Coord]int {
	grid := make(map[Coord]int)
	for _, line := range data {
		var tile Coord
		for i := 0; i < len(line); i++ {
			switch line[i] {
			case 'e':
				tile.x += 1
			case 'w':
				tile.x -= 1
			case 's':
				i++
				tile.y -= 0.5
				if line[i] == 'e' {
					tile.x += 0.5
				} else if line[i] == 'w' {
					tile.x -= 0.5
				} else {
					panic("oops")
				}
			case 'n':
				i++
				tile.y += 0.5
				if line[i] == 'e' {
					tile.x += 0.5
				} else if line[i] == 'w' {
					tile.x -= 0.5
				} else {
					panic("woops")
				}
			default:
				panic("unknown char")
			}
		}
		if grid[tile] == WHITE {
			grid[tile] = BLACK
		} else {
			grid[tile] = WHITE
		}
	}
	sum := countBlack(grid)
	fmt.Println("Star 1:", sum)
	return grid
}

func addCoord(c1 Coord, c2 Coord) Coord {
	c1.x += c2.x
	c1.y += c2.y
	return c1
}

func countAdj(m map[Coord]int, c Coord) int {
	sum := 0
	var E, SE, SW, W, NW, NE Coord
	E.x = 1
	E.y = 0

	SE.x = 0.5
	SE.y = -0.5

	SW.x = -0.5
	SW.y = -0.5

	W.x = -1
	W.y = 0

	NW.x = -0.5
	NW.y = 0.5

	NE.x = 0.5
	NE.y = 0.5

	if m[addCoord(c, E)] == BLACK {
		sum += 1
	}
	if m[addCoord(c, SE)] == BLACK {
		sum += 1
	}
	if m[addCoord(c, SW)] == BLACK {
		sum += 1
	}
	if m[addCoord(c, W)] == BLACK {
		sum += 1
	}
	if m[addCoord(c, NW)] == BLACK {
		sum += 1
	}
	if m[addCoord(c, NE)] == BLACK {
		sum += 1
	}
	return sum
}

func star2(m map[Coord]int) {
	var E, SE, SW, W, NW, NE Coord
	E.x = 1
	E.y = 0
	SE.x = 0.5
	SE.y = -0.5
	SW.x = -0.5
	SW.y = -0.5
	W.x = -1
	W.y = 0
	NW.x = -0.5
	NW.y = 0.5
	NE.x = 0.5
	NE.y = 0.5

	numBlack := 0
	for i := 0; i < 100; i++ {
		newM := make(map[Coord]int)
		for c, tile := range m {
			numBlack = countAdj(m, c)
			newM[c] = tile

			if tile == WHITE {
				if numBlack == 2 {
					newM[c] = BLACK
				}
			} else { //BLACK
				if numBlack == 0 || numBlack > 2 {
					newM[c] = WHITE
				}
			}

			// Adj
			tmp := addCoord(c, E)
			numBlack = countAdj(m, tmp)
			if m[tmp] == WHITE {
				if numBlack == 2 {
					newM[tmp] = BLACK
				}
			} else { //BLACK
				if numBlack == 0 || numBlack > 2 {
					newM[tmp] = WHITE
				}
			}

			tmp = addCoord(c, SE)
			numBlack = countAdj(m, tmp)
			if m[tmp] == WHITE {
				if numBlack == 2 {
					newM[tmp] = BLACK
				}
			} else { //BLACK
				if numBlack == 0 || numBlack > 2 {
					newM[tmp] = WHITE
				}
			}

			tmp = addCoord(c, SW)
			numBlack = countAdj(m, tmp)
			if m[tmp] == WHITE {
				if numBlack == 2 {
					newM[tmp] = BLACK
				}
			} else { //BLACK
				if numBlack == 0 || numBlack > 2 {
					newM[tmp] = WHITE
				}
			}

			tmp = addCoord(c, W)
			numBlack = countAdj(m, tmp)
			if m[tmp] == WHITE {
				if numBlack == 2 {
					newM[tmp] = BLACK
				}
			} else { //BLACK
				if numBlack == 0 || numBlack > 2 {
					newM[tmp] = WHITE
				}
			}

			tmp = addCoord(c, NW)
			numBlack = countAdj(m, tmp)
			if m[tmp] == WHITE {
				if numBlack == 2 {
					newM[tmp] = BLACK
				}
			} else { //BLACK
				if numBlack == 0 || numBlack > 2 {
					newM[tmp] = WHITE
				}
			}

			tmp = addCoord(c, NE)
			numBlack = countAdj(m, tmp)
			if m[tmp] == WHITE {
				if numBlack == 2 {
					newM[tmp] = BLACK
				}
			} else { //BLACK
				if numBlack == 0 || numBlack > 2 {
					newM[tmp] = WHITE
				}
			}
		}
		m = newM
	}
	sum := countBlack(m)
	fmt.Println("Star 2:", sum)
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*input)
	if err != nil {
		panic("Invalid file")
	}
	data := strings.Split(string(raw), "\n")
	g := star1(data[:len(data)-1])
	star2(g)
}
