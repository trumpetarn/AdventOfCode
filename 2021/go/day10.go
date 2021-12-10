package main

/*
Day 10: Syntax Scoring

https://adventofcode.com/2021/day/10

	): 3 points.
	]: 57 points.
	}: 1197 points.
	>: 25137 points.

*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"sort"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day10.txt", "Relative path to input-file")

func star1n2(data []string) {
	points1 := 0
	var points2 []int
	for _, s := range data {
		chars := strings.Split(s, "")
		var x, y, z, w int
		corrupt := false
		var latest []string
		p := 0
		for _, c := range chars {
			switch c {
			case "(":
				latest = append(latest, c)
				x++
			case "[":
				latest = append(latest, c)
				y++
			case "{":
				latest = append(latest, c)
				z++
			case "<":
				latest = append(latest, c)
				w++
			case ")":
				x--
				if latest[len(latest)-1] != "(" {
					corrupt = true
					p = 3
					break
				} else {
					latest = latest[:len(latest)-1]
				}
			case "]":
				y--
				if latest[len(latest)-1] != "[" {
					corrupt = true
					p = 57
					break
				} else {
					latest = latest[:len(latest)-1]
				}
			case "}":
				z--
				if latest[len(latest)-1] != "{" {
					corrupt = true
					p = 1197
					break
				} else {
					latest = latest[:len(latest)-1]
				}
			case ">":
				w--
				if latest[len(latest)-1] != "<" {
					corrupt = true
					p = 25137
					break
				} else {
					latest = latest[:len(latest)-1]
				}
			}
			if corrupt {
				points1 += p
				break
			}
		}
		if !corrupt {
			/*): 1 points,
			  ]: 2 points.
			  }: 3 points.
			  >: 4 points */
			p2 := 0
			for k := len(latest) - 1; k >= 0; k-- {
				p2 = p2 * 5
				switch latest[k] {
				case "(":
					p2 += 1
				case "[":
					p2 += 2
				case "{":
					p2 += 3
				case "<":
					p2 += 4
				}
			}
			points2 = append(points2, p2)
		}

	}
	sort.Ints(points2)
	fmt.Println("Star 1:", points1)
	fmt.Println("Star 2:", points2[len(points2)/2])
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n")
	star1n2(data)
}
