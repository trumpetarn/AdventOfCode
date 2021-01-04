package main

/*
Day 02: Password Philosophy

In: A list of password and rules on the form "x-y c:password"
Star 1: Validate that c occours between x and y number of times in the password
Star 2: Validate the c occours in the index x or y but not both
*/

import (
	"fmt"
	"io/ioutil"
	"strings"
)

func star1(data []string) {
	// x-y c: string
	var pass, c string
	var x, y int
	valid := 0
	for _, s := range data {
		fmt.Sscanf(s, "%d-%d %s %s", &x, &y, &c, &pass)
		n := strings.Count(pass, c[:1])
		if x <= n && n <= y {
			valid++
		}
	}
	fmt.Println("Star 1:", valid)
}

func star2(data []string) {
	var pass, c string
	var x, y int
	valid := 0
	for _, s := range data {
		fmt.Sscanf(s, "%d-%d %s %s", &x, &y, &c, &pass)
		if (pass[x-1] == c[0] || pass[y-1] == c[0]) && !(pass[x-1] == c[0] && pass[y-1] == c[0]) {
			valid++
		}
	}
	fmt.Println("Star 2:", valid)
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day02.txt")
	lnData := strings.Split(string(raw), "\n")
	data := lnData[:len(lnData)-1] // Remove last row (empty)
	star1(data)
	star2(data)
}
