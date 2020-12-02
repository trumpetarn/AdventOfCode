package main
/*
Day 01: Report repair

Star 1: Find two values from input that sums to 2020. Return the product of the two numbers
Star 2: Find three values from input that sums to 2020. Return the product of the three numbers
*/

import (
	"fmt"
	//"io"
	"io/ioutil"
	"strings"
	"strconv"
)

func star1(lnData []string) {
	for i, s1 := range lnData {
		a,_ := strconv.Atoi(s1)
    for j, s2 := range lnData {
    	b,_ := strconv.Atoi(s2)
    	if (a +b==2020){
    		fmt.Println("a: ", a, "(", i, ")")
    		fmt.Println("b: ", b, "(", j, ")")
    		fmt.Println("Star 1:", a*b)
    		return
    	}
    }
	}
}

func star2(lnData []string) {
	for i, s1 := range lnData {
		a,_ := strconv.Atoi(s1)
    for j, s2 := range lnData {
    	b,_ := strconv.Atoi(s2)
    	for k, s3 := range lnData {
    		c,_ := strconv.Atoi(s3)
	    	if (a+b+c==2020){
	    		fmt.Println("a: ", a, "(", i, ")")
	    		fmt.Println("b: ", b, "(", j, ")")
	    		fmt.Println("c: ", c, "(", k, ")")
	    		fmt.Println("Star 2:", a*b*c)
	    		return
	    	}
    	}
    }
	}
}

func main() {
	data, _ := ioutil.ReadFile("../inputs/day01.txt")
	lnData := strings.Split(string(data), "\n")
	star1(lnData[:len(lnData)-1])
	star2(lnData[:len(lnData)-1])
}