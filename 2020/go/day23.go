package main
/*
Day 23: Crab Cups	

https://adventofcode.com/2020/day/23
*/

import (
	"flag"
	"fmt"
	//"io/ioutil"
	//"strings"
	"strconv"
)

var input = flag.String("input", "598162734", "Input")
var star = flag.Int("star", 0, "Which star to run (0=both)")

func star1(data string) {
	cups := make([]int, len(data))
	for i,r := range data {
		cups[i],_ = strconv.Atoi(string(r))
	}
	var current,dest int
	var jC, jD, j1, j2 int
	for i:=0;i<100;i++ {
		if len(cups) == 0 {
			panic("Zero")
		}
		jC = i % len(cups)
		j1 = (i+1) % len(cups)
		j2 = (i+4) % len(cups) 
		current=cups[jC]

		//fmt.Println("-- move", i+1, "--")
		//fmt.Println("cups:", cups, current)
		// Rule 1
		pickedUp := make([]int, 3)
		if j1 < j2 {
			copy(pickedUp, cups[j1:j2])
			cups = append(cups[:j1], cups[j2:]...)
		} else {
			copy(pickedUp, append(cups[j1:], cups[:j2]...))
			cups = cups[j2:j1]
		}
		// Rule 2
		dest = current
		match := false
		for !match {
			dest--
			if dest < 1 {
				dest = 9
			}
			for k,v := range cups {
				if v == dest {
					match = true
					jD = k
					break
				}
			}
		}
		//fmt.Println("pick up:", pickedUp)
		//fmt.Println("destination:", cups[jD])
		// Rule 3
		if jD+1<len(cups) {
			pickedUp = append(pickedUp, cups[jD+1:]...)
		}
		cups = append(cups[:jD+1], pickedUp...)

		if jD < jC {
			for k:=0; k<3 && k<len(cups[jC:])-1; k++ {
				tmp := cups[0]
				cups = append(cups[1:], tmp)
			}
		}
	}
	ans := ""
	ind:=0
	for k,v := range cups {
		if v == 1 {
			ind=k
			break
		}
	}
	for i:=0;i<len(cups)-1;i++ { 
		ind++
		ind = ind % len(cups)
		ans += strconv.Itoa(cups[ind])
	}
	fmt.Println("Star 1:", ans)
}

func star2(data string) {
	M := 1000000
	//N := 500
	cups := make([]int, len(data))
	for i,r := range data {
		cups[i],_ = strconv.Atoi(string(r))
	}
	for i:=10;i<=M;i++{
		cups = append(cups, i)
	}
	

	var current,dest int
	var jC, jD, j1, j2 int
	for i:=0;i<500;i++ {
		jC = i % len(cups)
		/*if (jC>=N) && (jC<=(10*M-N)) {
			continue
		}*/
		j1 = (i+1) % len(cups)
		j2 = (i+4) % len(cups) 
		current=cups[jC]

		//fmt.Println("-- move", i+1, "--")
		//fmt.Println("cups:", cups, current)
		// Rule 1
		pickedUp := make([]int, 3)
		if j1 < j2 {
			copy(pickedUp, cups[j1:j2])
			cups = append(cups[:j1], cups[j2:]...)
		} else {
			copy(pickedUp, append(cups[j1:], cups[:j2]...))
			cups = cups[j2:j1]
		}
		// Rule 2
		dest = current
		match := false
		for !match {
			dest--
			if dest < 1 {
				dest = 9
			}
			for k,v := range cups {
				if v == dest {
					match = true
					jD = k
					break
				}
			}
		}
		//fmt.Println("pick up:", pickedUp)
		//fmt.Println("destination:", cups[jD])
		// Rule 3
		if jD+1<len(cups) {
			pickedUp = append(pickedUp, cups[jD+1:]...)
		}
		cups = append(cups[:jD+1], pickedUp...)

		if jD < jC {
			for k:=0; k<3 && k<len(cups[jC:])-1; k++ {
				tmp := cups[0]
				cups = append(cups[1:], tmp)
			}
		}
	}

	ind:=0
	for k,v := range cups {
		if v == 1 {
			ind=k
			break
		}
	}
	fmt.Println(cups[ind-10:ind+10], ind)
	fmt.Println("Star 2:", cups[ind+1]*cups[ind+2])
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