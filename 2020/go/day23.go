package main
/*
Day 23: Crab Cups	

https://adventofcode.com/2020/day/23
*/

import (
	"flag"
	"fmt"
	"container/list"
	//"io/ioutil"
	//"strings"
	"strconv"
)

var input = flag.String("input", "598162734", "Input")
var star = flag.Int("star", 0, "Which star to run (0=both)")


func printList(l *list.List, i int, pick []int, d int) {
	fmt.Println("-- Move", i, "--")
	fmt.Print("Cups: ")
	for e := l.Front(); e != nil; e = e.Next() {
		fmt.Print(e.Value)
	}
	fmt.Println("")
	fmt.Print("Pick Up: ")
	for _,v := range pick {
		fmt.Print(v)
	}
	fmt.Println("")
	fmt.Println("Destination:", d)
}

func findValue(l *list.List, le *list.Element, val int) *list.Element {
	fwd := le.Next()
	bck := le.Prev()
	for fwd != le {
		
		if fwd == nil {
			fwd = l.Front()
		}
		if bck == nil {
			bck = l.Back()
		}

		if fwd.Value.(int) == val {
			return fwd
		}
		if bck.Value.(int) == val {
			return bck
		}
		fwd = fwd.Next()
		bck = bck.Prev()
	}
	return nil
}

func crabCups(data []int, iter int) (*list.List, *list.Element) {
	cups := list.New()
	valMap := make(map[int]*list.Element)
	max := -1
	for _,v := range data {
		valMap[v] = cups.PushBack(v)
		if v > max {
			max = v
		}
	}
	data = data[:1]
	//printList(cups, 0, nil, 0)
	current := cups.Front()
	for i:=0;i<iter;i++ {
		s := i%1000000
		if s >= 0 {//s < 5000 || s>995000 {
			cvalue := current.Value.(int)
			dvalue := cvalue-1
			if dvalue < 1 {
				dvalue = max - dvalue
			}

			picked := make([]int, 3)
			for j:=0;j<3;j++ {
				picks := current.Next()
				if picks == nil {
					picks = cups.Front()
				}
				picked[j] = cups.Remove(picks).(int)
			}

			for k:=0;k<3;k++ {
				for j:=0;j<3;j++ {
					if dvalue == picked[j] {
						dvalue--
						if dvalue < 1 {
							dvalue = max - dvalue
						}
					}
				}
			}

			//printList(cups, i+1, picked, dvalue)
			dest := valMap[dvalue]
			for _,v := range picked {
				dest = cups.InsertAfter(v, dest)
				valMap[v] = dest
			}
		}

		current = current.Next()
		if current == nil {
			current = cups.Front()
		}
	}
	return cups, valMap[1]
}

func star1(data string) {
	cups := make([]int, len(data))
	for i,r := range data {
		cups[i],_ = strconv.Atoi(string(r))
	}
	l,a := crabCups(cups, 100)
	a = a.Next()
	if a == nil {
		a = l.Front()
	}

	ans := ""
	for a.Value.(int) != 1 { 
		ans += strconv.Itoa(a.Value.(int))
		a = a.Next()
		if a == nil {
			a = l.Front()
		}
	}
	fmt.Println("Star 1:", ans)
}

func star2(data string) {
	cups := make([]int, len(data))
	for i,r := range data {
		cups[i],_ = strconv.Atoi(string(r))
	}
	for i:=10;i<=1000000;i++ {
		cups = append(cups, i)
	}
	_,a := crabCups(cups, 10000000)

	a = a.Next()
	res := 1
	for f:=0;f<2;f++ {
		res *= a.Value.(int)
		a = a.Next()
	}
	fmt.Println("Star 2:", res)
}

func main() {
	flag.Parse()
	data := *input
	if *star == 0 || *star == 1 {
		star1(data)
	}
	if *star == 0 || *star == 2 {
		star2(data)
	}
}