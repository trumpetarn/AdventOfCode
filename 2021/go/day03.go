package main

/*
Day 03: Binary Diagnostic

https://adventofcode.com/2021/day/3
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"math"
	"strconv"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day03.txt", "Relative path to input-file")

func star1(data []string) {
	size := len(data)
	n := len(data[0])
	sums := make([]int, n)
	gamma := float64(0)
	epsilon := float64(0)
	for _, ln := range data {
		for i, c := range ln {
			x, _ := strconv.Atoi(string(c))
			sums[i] += x
		}
	}

	for i, x := range sums {
		if x > size/2 {
			gamma += math.Pow(2, float64(n-i-1))
		} else {
			epsilon += math.Pow(2, float64(n-i-1))
		}
	}

	fmt.Printf("Star 1: %d\n", int64(gamma*epsilon))
}

func filterData(data []string, filter string) []string {
	filtered := []string{}
	n := len(filter)
	for _, ln := range data {
		if ln[:n] == filter {
			filtered = append(filtered, ln)
		}
	}
	return filtered
}

func binary2int(bin string) int64 {
	n := len(bin)
	ret := int64(0)
	for i := 0; i < n; i++ {
		if bin[i] == '1' {
			ret += int64(math.Pow(2, float64(n-i-1)))
		}
	}
	return int64(ret)
}

func star2(data []string) {
	size := len(data)
	n := len(data[0])
	ogr := make([]string, size)
	csr := make([]string, size)
	copy(ogr, data)
	var filter string
	for i := 0; i < n; i++ {
		var ones, zeros int
		for _, ln := range ogr {
			x, _ := strconv.Atoi(string(ln[i]))
			if x == 1 {
				ones++
			} else {
				zeros++
			}
		}
		if ones >= zeros {
			filter += "1"
		} else {
			filter += "0"
		}
		ogr = filterData(ogr, filter)
		if len(ogr) == 1 {
			break
		}
	}
	copy(csr, data)
	filter = ""
	for i := 0; i < n; i++ {
		var ones, zeros int
		for _, ln := range csr {
			x, _ := strconv.Atoi(string(ln[i]))
			if x == 1 {
				ones++
			} else {
				zeros++
			}
		}
		if ones < zeros {
			filter += "1"
		} else {
			filter += "0"
		}
		csr = filterData(csr, filter)
		if len(csr) == 1 {
			break
		}
	}
	lsr := binary2int(ogr[0]) * binary2int(csr[0])
	fmt.Println("Star 2:", lsr)
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	data := strings.Split(string(raw), "\n")
	star1(data[:len(data)-1])
	star2(data[:len(data)-1])
}
