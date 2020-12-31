package main

/*
Day 19: Title

https://adventofcode.com/2020/day/19
*/

import (
	"fmt"
	"io/ioutil"
	"regexp"
	"strconv"
	"strings"
)

func parseRules(rs string) [][]string {
	d := strings.Split(string(rs), "\n")
	rules := make([][]string, len(d)+42)
	//letters := make(map[int]rune)
	for _, s := range d {
		split := strings.Split(s, ": ")
		i, _ := strconv.Atoi(split[0])
		rules[i] = strings.Split(split[1], " ")
		/*if rules[i][0][0] == '"' {
			letters[i] = rune(rules[i][0][1])
		}*/
	}
	return rules
}

func parseRule(n int, r [][]string) string {
	str := ""
	for _, s := range r[n] {
		//fmt.Println(s)
		if s == "|" {
			str += ","
			continue
		} else if s == "\"a\"" || s == "\"b\"" {
			//fmt.Println("ok")
			return string(s[1])
		}
		m, _ := strconv.Atoi(s)
		str += parseRule(m, r)
	}
	return str
}

func createRegex(n int, r [][]string) string {
	str := ""
	par := false
	for _, s := range r[n] {
		if s == "|" {
			str += "|"
			par = true
		} else if s == "\"a\"" || s == "\"b\"" {
			str += string(s[1])
		} else {
			k, _ := strconv.Atoi(s)
			str += createRegex(k, r)
		}
	}
	if par {
		str = "(" + str
		str += ")"
	}
	return str
}

func createRegexInf(n int, r [][]string, mem []int) (string, int) {
	y := 0
	/* 	I dont really understad why recursion more than 5 times works but it does
	Probably my "+" addition is wrong and by recursion we include all possible
	versions instead		*/
	for i, k := range mem {
		if n == k {
			y++
			if y > 5 {
				//fmt.Println(mem)
				return "+", i
			}
		}
	}
	mem = append(mem, n)
	str := ""
	par := false
	for _, s := range r[n] {
		if s == "|" {
			str += "|"
			par = true
		} else if s == "\"a\"" || s == "\"b\"" {
			str += string(s[1])
		} else {
			k, _ := strconv.Atoi(s)
			tmp, m := createRegexInf(k, r, mem)
			str += tmp
			if m >= 0 {
				str = "(?:(" + str + ")+)"
				par = true
			}
		}
	}
	if par {
		str = "(?:" + str + ")"
	}
	return str, -1
}

func star1(rules string, messages string) {
	r := parseRules(rules)
	//fmt.Println(r)
	x := "^" + createRegex(0, r) + "$"
	re, _ := regexp.Compile(x)
	num := 0
	for _, msg := range strings.Split(messages, "\n") {
		if re.MatchString(msg) {
			num++
		}
	}
	fmt.Println("Star 1:", num)
}

func star2(rules string, messages string) {
	r := parseRules(rules)
	r[8] = []string{"42", "|", "42", "8"}
	r[11] = []string{"42", "31", "|", "42", "11", "31"}
	//fmt.Println(r)
	var mem []int
	x, _ := createRegexInf(0, r, mem)
	x = "^" + x + "$"
	//fmt.Println(x)
	re, _ := regexp.Compile(x)
	num := 0
	for _, msg := range strings.Split(messages, "\n") {
		if re.MatchString(msg) {
			num++
		}
	}
	fmt.Println("Star 2:", num)
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day19.txt")
	data := strings.Split(string(raw), "\n\n")

	star1(data[0], data[1])
	star2(data[0], data[1])
}
