package main

/*
Day 14: Title

https://adventofcode.com/2021/day/14
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day14.txt", "Relative path to input-file")

func runRules(pairIns []string, template string) string {
	newTmp := ""
	for i, r := range template[:len(template)-1] {
		found := false
		for _, pi := range pairIns {
			AB := strings.Split(pi, " -> ")
			if string(template[i:i+2]) == AB[0] {
				newTmp += string(r) + AB[1]
				found = true
				break
			}
		}
		if !found {
			newTmp += string(r)
		}
	}
	newTmp += string(template[len(template)-1])
	return newTmp
}

func runRules2(pairIns []string, template string) string {
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
	fmt.Println(letters)
	for i, r := range template[:len(template)-1] {
		found := false
		for _, pi := range pairIns {
			AB := strings.Split(pi, " -> ")
			if string(template[i:i+2]) == AB[0] {
				newTmp += string(r) + AB[1]
				found = true
				break
			}
		}
		if !found {
			newTmp += string(r)
		}
	}
	newTmp += string(template[len(template)-1])
	return newTmp
}

func star1(pairIns []string, template string) {
	for i := 0; i < 10; i++ {
		template = runRules(pairIns, template)
	}
	rN := make(map[rune]int)
	for _, r := range template {
		rN[r]++
	}
	max := 0
	min := len(template)
	for _, v := range rN {
		if v > max {
			max = v
		}
		if v < min {
			min = v
		}
	}
	fmt.Println("Star 1:", max-min)
}

func star2(pairIns []string, template string) {
	for i := 0; i < 10; i++ {
		template = runRules2(pairIns, template)
	}
	rN := make(map[rune]int)
	/*for _, r := range template {
		rN[r]++
	}
	max := 0
	min := len(template)
	for _, v := range rN {
		if v > max {
			max = v
		}
		if v < min {
			min = v
		}
	}*/
	fmt.Println("Star 2:", rN)
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
