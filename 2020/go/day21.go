package main
/*
Day 21: Allergen Assessment	

https://adventofcode.com/2020/day/21
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
	"sort"
)

var input = flag.String("input", "../inputs/day21.txt", "Relative path to input-file")

func intersection(a,b []string) []string {
	inA := make(map[string]bool)
	for _, item := range a {
		inA[item] = true
	}
	var c []string
	for _, item := range b {
		if _, ok := inA[item]; ok {
			c = append(c, item)
		}
	}
  return c
}

func stringInMap(s string, m map[string][]string) (bool, string) {
	for k,v := range m {
		for _,x := range v {
			if x == s {
				return true, k
			}
		}
	}
	return false, ""
}

func star1(data []string) {
	allergens := make(map[string][]string)
	ingredients := make(map[string]int)
	for _,row := range data {
		sp := strings.Split(row, " (contains ")
		ing := strings.Split(sp[0], " ")
		aller := strings.Split(strings.Trim(sp[1], ")"), ", ")
		for _, a := range aller {
			if val, ok := allergens[a]; ok {
				allergens[a] = intersection(val, ing)
 			} else {
				allergens[a] = ing
			}
		}
		for _,i := range ing {
			ingredients[i] += 1
		}
	}
	var a_free []string
	for in,_ := range ingredients {
		if ok, _ := stringInMap(in, allergens); !ok {
			a_free = append(a_free, in)
		}
	}
	sum := 0
	for _,v := range a_free {
		sum += ingredients[v]
	}
	fmt.Println("Star 1:", sum)
}

func star2(data []string) {
	allergens := make(map[string][]string)
	ingredients := make(map[string]int)
	for _,row := range data {
		sp := strings.Split(row, " (contains ")
		ing := strings.Split(sp[0], " ")
		aller := strings.Split(strings.Trim(sp[1], ")"), ", ")
		for _, a := range aller {
			if val, ok := allergens[a]; ok {
				allergens[a] = intersection(val, ing)
 			} else {
				allergens[a] = ing
			}
		}
		for _,i := range ing {
			ingredients[i] += 1
		}
	}
	allergens2 := make(map[string]string)
	for len(allergens2) < len(allergens) {
		tmp := ""
		for k,v := range allergens {
			if len(v) == 1 {
				allergens2[k] = v[0]
				tmp = v[0]
				break
			}
		}
		
		for k,v := range allergens {
			var sl []string
			for _,x := range v {
				if tmp != x {
					sl = append(sl, x) 
				}
			}
			allergens[k] = sl
		}
	}
	

	keys := make([]string, 0, len(allergens2))
	for k := range allergens2 {
		keys = append(keys, k)
	}
	sort.Strings(keys)
	res := ""
	for _,v := range keys {
		res += allergens2[v] + ","
	}
	fmt.Println("Star 2:", res[:len(res)-1])
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*input)
	if err != nil {
		panic("Invalid file")
	}
	data := strings.Split(string(raw), "\n")
	star1(data[:len(data)-1])
	star2(data[:len(data)-1])
}