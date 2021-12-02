package main
/*
Day 01: Sonar Sweep

https://adventofcode.com/2021/day/1
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
	"strconv"
)

var inputFile = flag.String("inputFile", "../inputs/day01.txt", "Relative path to input-file")

func star1(lines []string) {
	prev,_ := strconv.Atoi(lines[0])
	incr := 0
	for _, ln := range lines[1:] {
		new,_ := strconv.Atoi(ln)
		if new > prev {
			incr++
		}
		prev = new
	}
	fmt.Println("Star 1:", incr)
}

func star2(data []string) {
	incr := 0
	for i, _ := range data[:len(data)-3] {
		a,_ := strconv.Atoi(data[i])
		b,_ := strconv.Atoi(data[i+1])
		c,_ := strconv.Atoi(data[i+2])
		d,_ := strconv.Atoi(data[i+3])
		wA := a+b+c
		wB := b+c+d
		if wB > wA {
			incr++
		}
	}
	fmt.Println("Star 2:", incr)
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	data := strings.Split(string(raw), "\n")
	star1(data)
	star2(data)
}