package main

/*
Day 16: Ticket Translation

https://adventofcode.com/2020/day/16
*/

import (
	"fmt"
	"io/ioutil"
	"math"
	"strconv"
	"strings"
)

type Rule struct {
	n1 int
	n2 int
	n3 int
	n4 int
}

type PosibleRule struct {
	rule     string
	possible []int
}

func parseInput(data []string) (map[string]Rule, []int, [][]int) {
	part := 0
	rules := make(map[string]Rule)
	var myTicket []int
	var otherTickets [][]int
	for _, s := range data {
		if len(s) == 0 {
			part++
			continue
		}
		if s[len(s)-1] == ':' {
			continue // title, skip
		}
		var n1, n2, n3, n4 int
		switch part {
		case 0:
			split := strings.Split(s, ":")
			key := split[0]
			fmt.Sscanf(split[1], "%d-%d or %d-%d", &n1, &n2, &n3, &n4)
			rules[key] = Rule{n1: n1, n2: n2, n3: n3, n4: n4}
		case 1:
			split := strings.Split(s, ",")
			for _, v := range split {
				i, _ := strconv.Atoi(v)
				myTicket = append(myTicket, i)
			}
		case 2:
			split := strings.Split(s, ",")
			var ticket []int
			for _, v := range split {
				i, _ := strconv.Atoi(v)
				ticket = append(ticket, i)
			}
			otherTickets = append(otherTickets, ticket)
		default:
			continue
		}
	}
	return rules, myTicket, otherTickets
}

func star1(r map[string]Rule, t []int, o [][]int) [][]int {
	ans := 0
	var valid [][]int
	for _, t := range o {
		b := true
		for _, n := range t {
			isValid := false
			for _, v := range r {
				if (v.n1 <= n && n <= v.n2) || (v.n3 <= n && n <= v.n4) {
					isValid = true
					break
				}
			}
			if !isValid {
				ans += n
				b = false
				// Is it okay to break? Works for my input
			}
		}
		if b {
			valid = append(valid, t)
		}
	}
	fmt.Println("Star 1:", ans)
	return valid
}

func getIdx(n int64) []int {
	var ret []int
	k := 0
	for i := int64(1); i <= n; i *= 2 {
		if (i & n) == i {
			ret = append(ret, k)
		}
		k++
	}
	return ret
}

func exists(x int, s []int) bool {
	for _, i := range s {
		if i == x {
			return true
		}
	}
	return false
}

func star2(rs map[string]Rule, mt []int, ot [][]int) {
	decode := make([]PosibleRule, len(rs))
	for s, r := range rs {
		possible := int64(math.Pow(2, float64(len(ot[0])))) - 1
		for _, t := range ot {
			tmp := int64(0)
			for i, n := range t {
				if ((r.n1 <= n) && (n <= r.n2)) || ((r.n3 <= n) && (n <= r.n4)) {
					tmp += int64(math.Pow(2, float64(i)))
				}
			}
			possible = possible & tmp
		}
		x := getIdx(possible)
		decode[len(x)-1] = PosibleRule{rule: s, possible: x}
	}
	var foundIds []int
	ans := 1
	for _, v := range decode {
		for _, n := range v.possible {
			if !exists(n, foundIds) {
				if len(v.rule) > 9 && v.rule[:9] == "departure" {
					ans *= mt[n]
				}
				foundIds = append(foundIds, n)
			}
		}
	}

	fmt.Println("Star 2:", ans)
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day16.txt")
	data := strings.Split(string(raw), "\n")
	rules, ticket, other := parseInput(data)
	valid := star1(rules, ticket, other)
	star2(rules, ticket, valid)
}
