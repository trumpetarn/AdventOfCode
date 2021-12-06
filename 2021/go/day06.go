package main

/*
Day 6: Title

https://adventofcode.com/2020/day/6
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day06.txt", "Relative path to input-file")

func list2int(list []string) []int {
	var ret []int
	for i, s := range list {
		x, err := strconv.Atoi(s)
		if err != nil {
			fmt.Println(err, "on line", i)
		}
		ret = append(ret, x)
	}
	return ret
}

func star1(data []int) {
	for day := 0; day < 80; day++ {
		n := len(data)
		for i := 0; i < n; i++ {
			data[i]--
			if data[i] < 0 {
				data[i] = 6
				data = append(data, 8)
			}
		}
	}
	fmt.Println("Star 1:", len(data))
}

func star2(data []int) {
	var n1, n2, n3, n4, n5, n6, n7 int
	var n1k, n2k, n3k, n4k, n5k, n6k, n7k int
	for _, n := range data {
		if n == 1 {
			n1++
		} else if n == 2 {
			n2++
		} else if n == 3 {
			n3++
		} else if n == 4 {
			n4++
		} else if n == 5 {
			n5++
		} else if n == 6 {
			n6++
		}
	}
	// Why one day less?
	for day := 0; day < 255; day++ {
		n := (day % 7)
		if n == 0 {
			n1k = n1
			n1 += n6k
			n6k = 0
		} else if n == 1 {
			n2k = n2
			n2 += n7k
			n7k = 0
		} else if n == 2 {
			n3k = n3
			n3 += n1k
			n1k = 0
		} else if n == 3 {
			n4k = n4
			n4 += n2k
			n2k = 0
		} else if n == 4 {
			n5k = n5
			n5 += n3k
			n3k = 0
		} else if n == 5 {
			n6k = n6
			n6 += n4k
			n4k = 0
		} else if n == 6 {
			n7k = n7
			n7 += n5k
			n5k = 0
		}
	}
	total := n1 + n2 + n3 + n4 + n5 + n6 + n7 + n1k + n2k + n3k + n4k + n5k + n6k + n7k
	fmt.Println("Star 2:", total)
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	trim := strings.Trim(string(raw), "\n")
	data := strings.Split(trim, ",")
	star1(list2int(data))
	star2(list2int(data))
}
