package main

/*
Day 14: Extended Polymerization

https://adventofcode.com/2021/day/14
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day14.txt", "Relative path to input-file")

func runRules(pairIns []string, template string) (string, int) {
	newTmp := ""
	var letters string
	for _, r := range template {
		if !strings.Contains(letters, string(r)) {
			letters += string(r)
		}
	}
	rules := make(map[string]string)
	for _, pi := range pairIns {
		AB := strings.Split(pi, " -> ")
		rules[AB[0]] = AB[1]
		if !strings.Contains(letters, AB[1]) {
			letters += AB[1]
		}
	}

	for i, r := range template[:len(template)-1] {
		found := false
		for k, v := range rules {
			if string(template[i:i+2]) == k {
				newTmp += string(r) + v
				found = true
				break
			}
		}
		if !found {
			newTmp += string(r)
		}
	}
	newTmp += string(template[len(template)-1])
	max := 0
	min := len(newTmp)
	for _, r := range letters {
		n := strings.Count(newTmp, string(r))
		if n > max {
			max = n
		}
		if n < min {
			min = n
		}
	}
	return newTmp, max - min
}

func string2pairs(s string) map[string]int {
	pairs := make(map[string]int)
	for i, _ := range s[:len(s)-1] {
		pairs[s[i:i+2]]++
	}
	return pairs
}
func strings2rules(pairIns []string) map[string]string {
	rules := make(map[string]string)
	for _, pi := range pairIns {
		AB := strings.Split(pi, " -> ")
		rules[AB[0]] = AB[1]
	}
	return rules
}

func runRules2(pairs map[string]int, rules map[string]string) map[string]int {
	new := make(map[string]int)
	for k, v := range rules {
		if pairs[k] > 0 {
			a := string(k[0]) + v
			b := v + string(k[1])
			//fmt.Println(a, b, k, v)
			new[a] += pairs[k]
			new[b] += pairs[k]
		}
	}
	return new
}

func star1(pairIns []string, template string) {
	n := 0
	for i := 0; i < 10; i++ {
		template, n = runRules(pairIns, template)
	}
	fmt.Println("Star 1:", n)
}

func star2(pairIns []string, template string) {
	first := string(template[0])
	last := string(template[len(template)-1])
	temp := string2pairs(template)
	rules := strings2rules(pairIns)
	for i := 0; i < 40; i++ {
		temp = runRules2(temp, rules)
	}
	nR := make(map[string]int)
	// all letters are counted twice except first and last
	nR[first] = 1
	nR[last] = 1
	for k, v := range temp {
		nR[string(k[0])] += v
		nR[string(k[1])] += v
	}
	max := 0
	min := nR[first]
	for _, v := range nR {
		if v/2 > max {
			max = v / 2
		}
		if v/2 < min {
			min = v / 2
		}
	}
	fmt.Println("Star 2:", max-min)
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n\n")
	pins := strings.Split(data[1], "\n")
	star1(pins, data[0])
	star2(pins, data[0])
}
