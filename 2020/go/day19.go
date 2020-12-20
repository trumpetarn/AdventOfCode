package main
/*
Day 19: Title

https://adventofcode.com/2020/day/19
*/

import (
	"fmt"
	"io/ioutil"
	"strings"
	"strconv"
)

func parseRules(rs string) [][]string {
	d := strings.Split(string(rs), "\n")
	rules := make([][]string, len(d))
	//letters := make(map[int]rune)
	for _,s := range d {
		split := strings.Split(s, ": ")
		i,_ := strconv.Atoi(split[0])
		rules[i] = strings.Split(split[1], " ")
		/*if rules[i][0][0] == '"' {
			letters[i] = rune(rules[i][0][1])
		}*/
	}
	return rules
}



func parseRule(n int, r [][]string) string {
	str := ""
	for _,s := range r[n] {
		//fmt.Println(s)
		if s == "|" {
			str += ","
			continue
		} else if s == "\"a\"" || s == "\"b\"" {
			//fmt.Println("ok")
			return string(s[1])
		}
		m,_ := strconv.Atoi(s)
		str += parseRule(m, r)
	}
	return str
}

func star1(rules string, messages string) {
	r := parseRules(rules)
	fmt.Println(r)
	x := parseRule(4,r) + "+" + parseRule(1,r) + "+" + parseRule(5,r)
	/*
	for msg := range strings.Split(messages, "\n") {

	}
	*/	
	fmt.Println("Star 1:", x)
}

func star2(rules string, messages string) {
	fmt.Println("Star 2:", messages[0])
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day19_example.txt")
	data := strings.Split(string(raw), "\n\n")

	star1(data[0],data[1])
	star2(data[0],data[1])
}
