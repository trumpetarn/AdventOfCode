package main
/*
Day 05: Binary boarding

https://adventofcode.com/2020/day/5
*/

import (
	"fmt"
	"io/ioutil"
	"strings"
)

const ROWS = 128
const COLS = 8

func newArray(n int) []int {
	a := make([]int, n)
  for i := range a {
      a[i] = i
  }
  return a
} 

func findRow(s string) int {
	rows := newArray(ROWS)
	for _, c := range s {
		var n int
		n = len(rows)/2
		switch c {
		case 'F':
			rows = rows[:n]
		case 'B':
			rows = rows[n:]
		default:
			fmt.Println("Oops something went wrong (char not F/B)")
		}
	}
	return rows[0]
}

func findColumn(s string) int {
	cols := newArray(COLS)
	for _, c := range s {
		var n int
		n = len(cols)/2
		switch c {
		case 'L':
			cols = cols[:n]
		case 'R':
			cols = cols[n:]
		default:
			fmt.Println("Oops something went wrong (char not L/C)")
		}
	}
	return cols[0]
}

func star1(data []string) {
	var r,c,max int
	for _, s := range data {
		r = findRow(s[:len(s)-3])
		c = findColumn(s[len(s)-3:])
		sid := r*8 + c
		if sid > max {
			max = sid
		}
	}
	fmt.Println("Star 1:", max)
}

func star2(data []string) {
	var r,c,max int
	min := ROWS*8+COLS
	sids := make([]int, min)
	for _, s := range data {
		r = findRow(s[:len(s)-3])
		c = findColumn(s[len(s)-3:])
		sid := r*8 + c
		sids[sid] = 1
		if sid > max {
			max = sid
		}
		if sid < min {
			min = sid
		}
	}
	for i, j := range sids[min:max] {
		if j == 0 {
			fmt.Println("Star 2:", i+min, "|", min, "-", max)
			break
		}
	}
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day05.txt")
	data := strings.Split(string(raw), "\n")
	star1(data[:len(data)-1])
	star2(data[:len(data)-1])
}