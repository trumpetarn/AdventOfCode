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
	"strconv"
)

func parseString(s string) (string, string, int, int) {
	s1 := strings.Split(s, ": ")
	s2 := strings.Split(s1[0], " ")
	s3 := strings.Split(s2[0], "-")
	pass := s1[1]
	c := s2[1]
	x, _ := strconv.Atoi(s3[0])
	y, _ := strconv.Atoi(s3[1])
	return pass, c, x, y
}

func star1(data []string) {
	// x-y c: string
	valid := 0
	for _, s := range data {
		pass, c, x, y := parseString(s)
		n := strings.Count(pass, c)
		if x <= n && n <= y {
			valid++
		}
	}
	fmt.Println("Star 1:", valid)
}

func star2(data []string){
	valid := 0
	for _, s := range data {
		pass, c, x, y := parseString(s)
		if (pass[x-1]==c[0] || pass[y-1]==c[0]) && !(pass[x-1]==c[0] && pass[y-1]==c[0]) {
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