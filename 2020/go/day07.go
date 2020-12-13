package main

/*
Day 07: Handy Haversacks

https://adventofcode.com/2020/day/7
*/

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

type bag struct {
	contains []string
	nBags    []int
}

func containsGold(b *bag, all map[string]*bag) bool {
	for _, x := range b.contains {
		if x == "shiny gold" {
			return true
		}
	}
	for _, x := range b.contains {
		if containsGold(all[x], all) {
			return true
		}
	}
	return false
}

/* dull brown bags contain 1 light indigo bag, 4 mirrored yellow bags, 5 faded silver bags.
 */
func star1(data []string) {
	bags := make(map[string]*bag, 0)
	for _, s1 := range data {
		a := strings.Split(s1, " bags contain ")
		if a[1] != "no other bags." {
			b := strings.Split(a[1], ", ")
			bags[a[0]] = &bag{contains: make([]string, len(b)), nBags: make([]int, len(b))}
			for i, s2 := range b {
				c := strings.Split(s2, " ")
				strconv.Atoi(c[0])
				bags[a[0]].nBags[i], _ = strconv.Atoi(c[0])
				bags[a[0]].contains[i] = c[1] + " " + c[2]
			}
		} else {
			bags[a[0]] = &bag{contains: make([]string, 0)}
		}
	}
	var ans int
	for _, bag := range bags {
		if containsGold(bag, bags) {
			ans++
		}
	}
	fmt.Println("Star 1:", ans)
	star2(bags)
}

func countBags(b *bag, all map[string]*bag) int {
	sum := 1
	for i, x := range b.contains {
		sum += b.nBags[i] * countBags(all[x], all)
	}
	return sum
}

func star2(bags map[string]*bag) {
	n := countBags(bags["shiny gold"], bags)
	fmt.Println("Star 2:", n-1) // Don't count the outer most bag
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day07.txt")
	data := strings.Split(string(raw), "\n")
	star1(data[:len(data)-1])
}
