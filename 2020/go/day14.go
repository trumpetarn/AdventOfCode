package main

/*
Day 14: Shuttle Search

https://adventofcode.com/2020/day/14
*/

import (
	"fmt"
	"io/ioutil"
	"strings"
	"math"
	"strconv"
	//"sort"
	//"time"
)

// Todo: simplify first
func star1(data []string) {
	var mask map[int]byte
	mem := make(map[int]int64)
	for _, s := range data {
		if s[:4] == "mask" {
			mask = make(map[int]byte)
			for i:=len(s)-1; i>6; i--{
				if s[i] != 'X' {
					mask[len(s)-i] = s[i]
				}
			}
		}else{
			var idx int
			var val,toAdd int64
			fmt.Sscanf(s, "mem[%d] = %d", &idx, &val)
			bin := []byte(strconv.FormatInt(val, 2))
			for key, v := range mask {
				if key<=len(bin){
					bin[len(bin)-key] = v
				}else if v == '1'{
					toAdd += int64(math.Pow(2,float64(key-1)))
				}
			}
			x,_ := strconv.ParseInt(string(bin), 2, 64)
			mem[idx] = x+toAdd
		}
	}
	var sum int64
	for _,v := range mem {
		sum += v
	}
	fmt.Println("Star 1:", sum)
}

func star2(data []string) {
	var mask,xmask,invxmask,addr,val int64
	var masks []int64
	mem := make(map[int64]int64)
	for _, s := range data {
		if s[:4] == "mask" {
			masks = make([]int64,0)
			mask = 0
			xmask = 0
			invxmask = 0
			for i:=7; i<len(s); i++{
				mask = mask << 1
				xmask = xmask << 1
				invxmask = invxmask << 1
				switch s[i]{
				case '0': 
					invxmask += 1
				case '1': 
					invxmask += 1
					mask += 1
				case 'X':
					xmask += 1
				default:
					panic("invalid")
				}
			}
			masks = append(masks, mask)
			var i int64
			for i=1; i<=xmask; i*=2 {
				x := (i & xmask)
				if x > 0 {
					l := len(masks)
					for j:=0; j<l; j++{
						masks = append(masks, x | masks[j])
					}
				}
			}
		}else{
			fmt.Sscanf(s, "mem[%d] = %d", &addr, &val)
			addr = addr & invxmask // set X positions to zero
			for _,m := range masks {
				mem[addr|m] = val // Apply bitmask
			}
		}
	}
	var sum int64
	for _,v := range mem {
		sum += v
	}
	fmt.Println("Star 2:", sum)
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day14.txt")
	data := strings.Split(string(raw), "\n")
	star1(data[:len(data)-1])
	star2(data[:len(data)-1])
}
