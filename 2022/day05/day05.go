package main

/*
   Day 05: https://adventofcode.com/2022/day/5
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day05.txt", "Relative path to input-file")

func input2matrix(data string) [][]string {
	rows := strings.Split(data, "\n")
	A, B := rows[:len(rows)-1], rows[len(rows)-1]
	N := (len(B) + 1) / 4
	ret := make([][]string, N)
	for _, ln := range A {
		j := 0
		for i := 1; i < len(ln); i += 4 {
			if ln[i] != ' ' {
				ret[j] = append(ret[j], string(ln[i]))
			}
			j++
		}
	}

	return ret
}

func readFirst(data [][]string) string {
	res := ""
	for _, sl := range data {
		if len(sl) > 0 {
			res += sl[0]
		} else {
			res += "*"
		}
	}
	return res
}

func star1(data []string) {
	stack := input2matrix(data[0])
	instr := strings.Split(data[1], "\n")
	for _, ln := range instr[:len(instr)-1] {
		var amount, from, to int
		fmt.Sscanf(ln, "move %d from %d to %d", &amount, &from, &to)
		for i := 0; i < amount; i++ {
			x, y := stack[from-1][0], stack[from-1][1:]
			stack[from-1] = y
			stack[to-1] = append([]string{x}, stack[to-1]...)
		}
	}
	fmt.Println("Star 1:", readFirst(stack))
}

func star2(data []string) {
	stack := input2matrix(data[0])
	instr := strings.Split(data[1], "\n")
	for _, ln := range instr[:len(instr)-1] {
		var amount, from, to int
		fmt.Sscanf(ln, "move %d from %d to %d", &amount, &from, &to)
		x, y := stack[from-1][:amount], stack[from-1][amount:]
		z := make([]string, len(y))
		copy(z, y)
		stack[from-1] = z
		stack[to-1] = append(x, stack[to-1]...)
	}
	fmt.Printf("%v\n", stack)
	fmt.Println("Star 2:", readFirst(stack))
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}

	data := strings.Split(string(raw), "\n\n")
	star1(data)
	star2(data)
}
