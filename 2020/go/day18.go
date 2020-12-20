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

func calc(s string) int {
	var op,x,y int
	first := true
	s = strings.Replace(s, "(", "",-1)
	s = strings.Replace(s, ")", "",-1)
	sl := strings.Split(s, " ")
	//fmt.Println(sl)
	for _,v := range sl {
		if len(v) == 0{
			continue
		}
		switch v{
		case "(":
			continue
		case ")":
			continue
		case " ":
			continue
		case "+":
			op=0
		case "*":
			op=1
		default:
			if first {
				x,_=strconv.Atoi(v)
				first = false
				//fmt.Println("x",x)
			}else{
				y,_=strconv.Atoi(v)
				//fmt.Println("y",y)
				if op==0 {
					x += y
				}else{
					x *= y
				}
			}
			//fmt.Println(x,y)
		}
	}
	return x
}

func calc2(s string) int {
	var op,x,y int
	first := true
	s = strings.Replace(s, "(", "",-1)
	s = strings.Replace(s, ")", "",-1)
	sl := strings.Split(s, " ")
	var next []string
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
					//fmt.Println("pre",next)
					trim := len(next)-3
					if trim >= 0 {
						next = next[:trim]
					}
					x = x+y
					next = append(next, strconv.Itoa(x))
					//fmt.Println("post",next)
				}else{
					
				}
			}
			//fmt.Println(x,y)
		}
	}
	//fmt.Println("",next)
	op=1
	first = true
	x=0
	y=0

	for _,v := range next {
		if len(v) == 0{
			continue
		}
		//fmt.Println(v,x,y)
		switch v{
		case "+":
			panic("+")
		case "*":
			op=1
		default:
			if first {
				x,_=strconv.Atoi(v)
				first = false
			}else{
				y,_=strconv.Atoi(v)
				if op==1 {
					x *= y
				}else{
					
				}
			}
			
		}
	}
	//fmt.Println("    ",next)
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
			//fmt.Println("m", l)
		default:
			continue
		}
	}
	if b{
		//fmt.Println("f", l)
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
	fmt.Println("Star 2:", ans)
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day18.txt")
	data := strings.Split(string(raw), "\n")
	star1(data[:len(data)-1])
	//star1([]string{"1 + (2 * 3) + (4 * (5 + 6))", "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2", "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))"})
	//fmt.Println("Ans:", 51, 13632, 12240)
	star2(data[:len(data)-1])
	//a := []string{"1 + (2 * 3) + (4 * (5 + 6))", "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))", "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2"}
	//star2(a)
	//fmt.Println("Ans:", 51, 669060, 23340)
}