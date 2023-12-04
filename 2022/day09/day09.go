package main

/*
   Day 09: https://adventofcode.com/2022/day/9
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day09.txt", "Relative path to input-file")

type Pos struct {
	x int
	y int
}

func isAdjacent(P1, P2 Pos) bool {
	if P1.x == P2.x || P1.x+1 == P2.x || P1.x-1 == P2.x {
		if P1.y == P2.y || P1.y+1 == P2.y || P1.y-1 == P2.y {
			return true
		}
	}
	return false
}

func star1(data []string) {
	var dir rune
	var l int
	H := Pos{0, 0}
	T := Pos{0, 0}
	history := make(map[Pos]bool)
	history[T] = true
	for _, ln := range data {
		fmt.Sscanf(ln, "%c %d", &dir, &l)
		for i := 0; i < l; i++ {
			prevH := Pos{H.x, H.y}
			switch dir {
			case 'U':
				H.y++
			case 'R':
				H.x++
			case 'L':
				H.x--
			case 'D':
				H.y--
			default:
				panic("Unkown direction")
			}
			if !isAdjacent(T, H) {
				T = prevH
				history[T] = true
			}
		}
	}
	fmt.Println("Star 1:", len(history))
}

func star2(data []string) {
	var dir rune
	var l int
	rope := make([]Pos, 2)
	for i := 0; i < len(rope); i++ {
		rope[i] = Pos{0, 0}
	}
	history := make(map[Pos]bool)
	history[rope[len(rope)-1]] = true
	for _, ln := range data {
		fmt.Sscanf(ln, "%c %d", &dir, &l)
		for i := 0; i < l; i++ {
			switch dir {
			case 'U':
				rope[0].y++
			case 'R':
				rope[0].x++
			case 'L':
				rope[0].x--
			case 'D':
				rope[0].y--
			default:
				panic("Unkown direction")
			}

			for j := 1; j < len(rope); j++ {
				if rope[j-1].x > rope[j].x+1 && rope[j-1].y == rope[j].y {
					rope[j].x++
				} else if rope[j-1].x < rope[j].x-1 && rope[j-1].y == rope[j].y {
					rope[j].x--
				} else if rope[j-1].y > rope[j].y+1 && rope[j-1].x == rope[j].x {
					rope[j].y++
				} else if rope[j-1].y < rope[j].y-1 && rope[j-1].x == rope[j].x {
					rope[j].y--
				} else if !isAdjacent(rope[j], rope[j-1]) {
					//diagonal
					if rope[j-1].x < rope[j].x {
						rope[j].x--
					} else {
						rope[j].x++
					}
					if rope[j-1].y > rope[j].y-1 {
						rope[j].y--
					} else {
						rope[j].y++
					}
				}

			}
			//fmt.Println("  ", rope)
			history[rope[len(rope)-1]] = true
		}
		//fmt.Println(rope)
	}

	fmt.Println("Star 2:", len(history))
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n")
	star1(data)
	star2(data)
}
