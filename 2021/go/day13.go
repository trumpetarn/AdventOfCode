package main

/*
Day 13: Transparent Origami

https://adventofcode.com/2021/day/13
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day13.txt", "Relative path to input-file")

type Point struct {
	x int
	y int
}

func foldX(pts []Point, x int) {
	for i, p := range pts {
		if p.x > x {
			p.x = p.x - 2*(p.x-x)
			pts[i] = p
		}
	}
}

func foldY(pts []Point, y int) {
	for i, p := range pts {
		if p.y > y {
			p.y = p.y - 2*(p.y-y)
			pts[i] = p
		}
	}
}

func unique(pts []Point) int {
	mp := make(map[Point]bool)
	for _, p := range pts {
		mp[p] = true
	}
	return len(mp)
}

func star1(points []Point, ins []string) {

	var c rune
	var n int
	fmt.Sscanf(ins[0], "fold along %c=%d", &c, &n)
	if string(c) == "x" {
		foldX(points, n)
	} else {
		foldY(points, n)
	}
	fmt.Println("Star 1:", unique(points))
}

func printPoints(pts []Point) {
	var xMax, yMax int
	for _, p := range pts {
		if p.x > xMax {
			xMax = p.x
		}
		if p.y > yMax {
			yMax = p.y
		}
	}
	matrix := make([][]string, yMax+1)
	for i := range matrix {
		matrix[i] = make([]string, xMax+1)
		for j := range matrix[i] {
			matrix[i][j] = " "
		}
	}
	for _, p := range pts {
		matrix[p.y][p.x] = "#"
	}
	for _, row := range matrix {
		fmt.Println(row)
	}
}

func star2(points []Point, ins []string) {
	for _, i := range ins {
		var c rune
		var n int
		fmt.Sscanf(i, "fold along %c=%d", &c, &n)
		if string(c) == "x" {
			foldX(points, n)
		} else {
			foldY(points, n)
		}
	}
	fmt.Println("Star 2:")
	printPoints(points)
}

func string2point(data string) []Point {
	sp := strings.Split(data, "\n")
	ps := make([]Point, len(sp))
	for i, s := range sp {
		ss := strings.Split(s, ",")
		x, _ := strconv.Atoi(ss[0])
		y, _ := strconv.Atoi(ss[1])
		ps[i] = Point{x, y}
	}
	return ps
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n\n")
	points := string2point(data[0])
	instructions := strings.Split(data[1], "\n")
	star1(points, instructions)
	star2(points, instructions)
}
