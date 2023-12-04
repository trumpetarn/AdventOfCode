package main

/*
   Day 01: https://adventofcode.com/2023/day/1
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"regexp"
	"strconv"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day01.txt", "Relative path to input-file")

func findSum(data []string) int {
	sum := 0
	for _, ln := range data {
		re := regexp.MustCompile("[0-9]")
		str := re.FindAllString(ln, -1)
		x := 0
		if len(str) > 0 {
			x, _ = strconv.Atoi(str[0] + str[len(str)-1])
		}
		sum += x
	}
	return sum
}

func star1(data []string) {
	fmt.Println("Star 1:", findSum(data))
}

func star2(data []string) {
	var newData []string
	for _, ln := range data {
		ln = strings.ReplaceAll(ln, "one", "one1one")
		ln = strings.ReplaceAll(ln, "two", "two2two")
		ln = strings.ReplaceAll(ln, "three", "three3three")
		ln = strings.ReplaceAll(ln, "four", "four4four")
		ln = strings.ReplaceAll(ln, "five", "five5five")
		ln = strings.ReplaceAll(ln, "six", "six6six")
		ln = strings.ReplaceAll(ln, "seven", "seven7seven")
		ln = strings.ReplaceAll(ln, "eight", "eight8eight")
		ln = strings.ReplaceAll(ln, "nine", "nine9nine")
		newData = append(newData, ln)
	}
	fmt.Println("Star 2:", findSum(newData))
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
