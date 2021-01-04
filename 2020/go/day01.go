package main

/*
Day 01: Report repair
https://adventofcode.com/2020/day/1
Star 1: Find two values from input that sums to 2020. Return the product of the two numbers
Star 2: Find three values from input that sums to 2020. Return the product of the three numbers
*/

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

func star1(lnData []string) {
	for _, s1 := range lnData {
		a, _ := strconv.Atoi(s1)
		for _, s2 := range lnData {
			b, _ := strconv.Atoi(s2)
			if a+b == 2020 {
				fmt.Println("Star 1:", a*b)
				return
			}
		}
	}
}

func star2(lnData []string) {
	for _, s1 := range lnData {
		a, _ := strconv.Atoi(s1)
		for _, s2 := range lnData {
			b, _ := strconv.Atoi(s2)
			for _, s3 := range lnData {
				c, _ := strconv.Atoi(s3)
				if a+b+c == 2020 {
					fmt.Println("Star 2:", a*b*c)
					return
				}
			}
		}
	}
}

func main() {
	data, _ := ioutil.ReadFile("../inputs/day01.txt")
	lnData := strings.Split(string(data), "\n")
	star1(lnData[:len(lnData)-1])
	star2(lnData[:len(lnData)-1])
}
