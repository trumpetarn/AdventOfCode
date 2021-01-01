package main

/*
Day 25: Combo Breaker
https://adventofcode.com/2020/day/25
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
	"strconv"
)

var input = flag.String("input", "../inputs/day25.txt", "Relative path to input-file")

func star1(ck, dk int) {
	val := 1
	subj:= 7
	loopC := 0
	for val != ck {
		val *= subj
		val = val % 20201227
		loopC++
	}

	val = 1
	loopD := 0
	for val != dk {
		val *= subj
		val = val % 20201227
		loopD++
	}

	subj = dk
	val = 1
	for i:=0;i<loopC;i++ {
		val *= subj
		val = val % 20201227
	}

	fmt.Println("Star 1:", val)
}

func star2() {
	fmt.Println("Star 2:", "Well Done! You finished AoC!, Merry Christmas!")
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*input)
	if err != nil {
		panic("Invalid file")
	}
	data := strings.Split(string(raw), "\n")
	cardkey,_ := strconv.Atoi(data[0])
	doorkey,_ := strconv.Atoi(data[1])
	star1(cardkey, doorkey)
	star2()
}
