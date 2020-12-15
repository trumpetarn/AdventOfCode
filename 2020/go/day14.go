package main

/*
Day 14: Shuttle Search

https://adventofcode.com/2020/day/14
*/

import (
	"fmt"
	"io/ioutil"
	"strings"
)

func getMasks(s string) (int64, int64, int64, int64) {
	var mask, xmask, invmask, invxmask int64
	mask = 0
	invmask = 1
	xmask = 0
	invxmask = 0
	for i := 0; i < len(s); i++ {
		mask = mask << 1
		invmask = invmask << 1
		xmask = xmask << 1
		invxmask = invxmask << 1
		switch s[i] {
		case '0':
			invxmask += 1
		case '1':
			invmask += 1
			invxmask += 1
			mask += 1
		case 'X':
			invmask += 1
			xmask += 1
		default:
			panic("Invalid Mask value")
		}
	}
	return mask, invmask, xmask, invxmask
}

func star1(data []string) {
	var mask, invmask, addr, val int64
	mem := make(map[int64]int64)
	for _, s := range data {
		if s[:4] == "mask" {
			mask, invmask, _, _ = getMasks(s[7:])
		} else {
			fmt.Sscanf(s, "mem[%d] = %d", &addr, &val)
			mem[addr] = (val & invmask) | mask
		}
	}
	var sum int64
	for _, v := range mem {
		sum += v
	}
	fmt.Println("Star 1:", sum)
}

func star2(data []string) {
	var mask, xmask, invxmask, addr, val int64
	var masks []int64
	mem := make(map[int64]int64)
	for _, s := range data {
		if s[:4] == "mask" {
			masks = make([]int64, 0)
			mask, _, xmask, invxmask = getMasks(s[7:])
			masks = append(masks, mask)
			var i int64
			for i = 1; i <= xmask; i *= 2 {
				x := (i & xmask)
				if x > 0 {
					l := len(masks)
					for j := 0; j < l; j++ {
						masks = append(masks, x|masks[j])
					}
				}
			}
		} else {
			fmt.Sscanf(s, "mem[%d] = %d", &addr, &val)
			addr = addr & invxmask // set X positions to zero
			for _, m := range masks {
				mem[addr|m] = val // Apply bitmask
			}
		}
	}
	var sum int64
	for _, v := range mem {
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
