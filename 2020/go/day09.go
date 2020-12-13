package main

/*
Day 09: Encoding Error

https://adventofcode.com/2020/day/9
*/

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

const PS = 25 //Preamble size

func isValid(ix int, res int, data []int) bool {
	vals := data[ix : ix+PS]
	for i, n := range vals {
		for j, m := range vals {
			if j != i {
				if n+m == res {
					return true
				}
			}
		}
	}
	return false
}

func findSlice(ix int, res int, data []int) []int {
	vals := data[:ix]
	sum := 0
	for i := 0; i < len(vals); i++ {
		sum = vals[i]
		for j := i + 1; j < len(vals); j++ {
			sum += vals[j]
			if sum == res {
				return vals[i : j+1]
			}
			if sum > res {
				break
			}
		}
	}
	return nil
}

func evaluate(ns []int) int {
	max := 0
	min := ns[0]
	for _, n := range ns {
		if min > n {
			min = n
		}
		if max < n {
			max = n
		}
	}
	return min + max
}

func star1(data []int) {
	for i, n := range data[PS:] {
		if !isValid(i, n, data) {
			fmt.Println("Star 1:", n)
			star2(i, n, data)
			break
		}
	}
}

func star2(i int, n int, data []int) {
	ans := findSlice(i, n, data)
	//fmt.Println(ans)
	fmt.Println("Star 2:", evaluate(ans))
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day09.txt")
	sdata := strings.Split(string(raw), "\n")
	data := make([]int, len(sdata)-1)
	for i, s := range sdata[:len(sdata)-1] {
		data[i], _ = strconv.Atoi(s)
	}
	star1(data)
}
