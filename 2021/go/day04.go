package main

/*
Day 04: Giant Squid

https://adventofcode.com/2020/day/4
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day04.txt", "Relative path to input-file")

type Board struct {
	vals [5][5]int
}

func sumBoard(b Board) int {
	sum := 0
	for i := 0; i < 5; i++ {
		for j := 0; j < 5; j++ {
			sum += b.vals[i][j]
		}
	}
	return sum
}

func findBingo(b Board, order []string) (int, int) {
	for x, s := range order {
		n, _ := strconv.Atoi(s)
		for i := 0; i < 5; i++ {
			for j := 0; j < 5; j++ {
				if b.vals[i][j] == n {
					b.vals[i][j] = 0
					break
				}
			}
		}
		for i := 0; i < 5; i++ {
			if b.vals[0][i]+b.vals[1][i]+b.vals[2][i]+b.vals[3][i]+b.vals[4][i] == 0 {
				return sumBoard(b) * n, x
			}
			if b.vals[i][0]+b.vals[i][1]+b.vals[i][2]+b.vals[i][3]+b.vals[i][4] == 0 {
				return sumBoard(b) * n, x
			}
		}

	}
	return 0, len(order) + 1
}

func star1(data []string) {
	order := strings.Split(data[0], ",")
	var boards []Board
	for _, board := range data[1:] {
		rows := strings.Split(board, "\n")
		var newB Board
		for i, r := range rows {
			if i == 5 {
				break
			}
			var a, b, c, d, e int
			fmt.Sscanf(r, "%d %d %d %d %d", &a, &b, &c, &d, &e)
			newB.vals[i][0] = a
			newB.vals[i][1] = b
			newB.vals[i][2] = c
			newB.vals[i][3] = d
			newB.vals[i][4] = e
		}
		boards = append(boards, newB)
	}
	bSmall := len(order)
	bScore := -1
	for _, b := range boards {
		score, bingo := findBingo(b, order)
		if bingo < bSmall {
			bSmall = bingo
			bScore = score
		}
	}
	fmt.Println("Star 1:", bScore)
}

func star2(data []string) {

	order := strings.Split(data[0], ",")
	var boards []Board
	for _, board := range data[1:] {
		rows := strings.Split(board, "\n")
		var newB Board
		for i, r := range rows {
			if i == 5 {
				break
			}
			var a, b, c, d, e int
			fmt.Sscanf(r, "%d %d %d %d %d", &a, &b, &c, &d, &e)
			newB.vals[i][0] = a
			newB.vals[i][1] = b
			newB.vals[i][2] = c
			newB.vals[i][3] = d
			newB.vals[i][4] = e
		}
		boards = append(boards, newB)
	}
	bBig := 0
	bScore := -1
	for _, b := range boards {
		score, bingo := findBingo(b, order)
		if bingo > bBig {
			bBig = bingo
			bScore = score
		}
	}
	fmt.Println("Star 2:", bScore)
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	data := strings.Split(string(raw), "\n\n")
	star1(data)
	star2(data)
}
