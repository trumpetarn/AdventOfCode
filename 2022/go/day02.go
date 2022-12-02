package main

/*
Day 02: Rock Paper Scissors

https://adventofcode.com/2022/day/2
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day02.txt", "Relative path to input-file")

func star1(data []string) {
	res := 0
	for _, line := range data {
		rs := strings.Split(line, " ")
		if rs[0] == "A" { // Rock
			if rs[1] == "X" { // Rock
				res += 1
				res += 3
			} else if rs[1] == "Y" { // Paper
				res += 2
				res += 6
			} else if rs[1] == "Z" { // Siccors
				res += 3
				res += 0
			}
		} else if rs[0] == "B" { // Paper
			if rs[1] == "X" { // Rock
				res += 1
				res += 0
			} else if rs[1] == "Y" { // Paper
				res += 2
				res += 3
			} else if rs[1] == "Z" { // Siccors
				res += 3
				res += 6
			}
		} else if rs[0] == "C" { // Siccors
			if rs[1] == "X" { // Rock
				res += 1
				res += 6
			} else if rs[1] == "Y" { // Paper
				res += 2
				res += 0
			} else if rs[1] == "Z" { // Siccors
				res += 3
				res += 3
			}
		}
	}
	fmt.Println("Star 1:", res)
}

func star2(data []string) {
	res := 0
	for _, line := range data {
		rs := strings.Split(line, " ")
		if rs[0] == "A" { // Rock
			if rs[1] == "X" { // Lose
				res += 3
				res += 0
			} else if rs[1] == "Y" { // Draw
				res += 1
				res += 3
			} else if rs[1] == "Z" { // Win
				res += 2
				res += 6
			}
		} else if rs[0] == "B" { // Paper
			if rs[1] == "X" { // Lose
				res += 1
				res += 0
			} else if rs[1] == "Y" { // Draw
				res += 2
				res += 3
			} else if rs[1] == "Z" { // Win
				res += 3
				res += 6
			}
		} else if rs[0] == "C" { // Siccors
			if rs[1] == "X" { // Lose
				res += 2
				res += 0
			} else if rs[1] == "Y" { // Draw
				res += 3
				res += 3
			} else if rs[1] == "Z" { // Win
				res += 1
				res += 6
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
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n")
	star1(data)
	star2(data)
}
