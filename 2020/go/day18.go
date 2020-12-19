package main
/*
Day 18: Operation Order

https://adventofcode.com/2020/day/18
*/

import (
	"fmt"
	"io/ioutil"
	"strings"
	"strconv"
)

func calc2(s string) int {
	var op,x,y,sum int
	first := true
	s = strings.Replace(s, "(", "",-1)
	s = strings.Replace(s, ")", "",-1)
	sl := strings.Split(s, " ")
	next := sl
	//fmt.Println(sl)
	for _,v := range sl {
		if len(v) == 0{
			continue
		}
		next = append(next, v)
		switch v{
		case "+":
			op=0
		case "*":
			op=1
			first = true
		default:
			if first {
				x,_=strconv.Atoi(v)
				first = false
				//fmt.Println("x",x)
			}else{
				y,_=strconv.Atoi(v)
				//fmt.Println("y",y)
				if op==0 {
					next = next[:len(next)-3]
					next = append(next, strconv.Itoa(x+y))
				}else{
					
				}
			}
			//fmt.Println(x,y)
		}
	}
	return x
}

func calcLine(l string, b bool) int {
	var par []int
	for i,r := range l {
		//fmt.Println(l)
		switch r {
		case '(':
			par = append(par, i+1)
		case ')':
			n := len(par)-1
			j := par[n]
			par = par[:n]
			var v string
			if b {
				v = strconv.Itoa(calc2(l[j:i]))
			}else{
				v = strconv.Itoa(calc(l[j:i]))
			}
			pad := i-j-len(v)
			//tmp := l
			l = l[:j] + v + strings.Repeat(" ", pad) + l[i:]
		default:
			continue
		}
	}
	if b{
		return calc2(l)
	}
	return calc(l)
}

func star1(data []string) {
	ans := 0
	for _, line := range data {
		ans += calcLine(line, false)
	}
	fmt.Println("Star 1:", ans)
}

func star2(data []string) {
	ans := 0
	for _, line := range data {
		ans += calcLine(line, true)
	}
	fmt.Println("Star 2:", data[0])
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day18.txt")
	data := strings.Split(string(raw), "\n")
	star1(data[:len(data)-1])
	//star1([]string{"1 + 2 * 3 + 4 * 5 + 6", "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2", "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))"})
	//fmt.Println("Ans:", 71, 13632, 12240)
	star2(data[:len(data)-1])
}