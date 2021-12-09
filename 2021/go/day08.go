package main

/*
Day 08: Seven Segment Search

https://adventofcode.com/2021/day/8
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"math"
	"sort"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day08.txt", "Relative path to input-file")

func star1(data []string) {
	ans := 0
	for _, s := range data {
		split := strings.Split(s, " ")
		out := split[11:]
		for _, o := range out {
			n := len(o)
			if n == 2 {
				ans++
			} else if n == 3 {
				ans++
			} else if n == 4 {
				ans++
			} else if n == 7 {
				ans++
			} else {
				// nothing
			}
		}
	}
	fmt.Println("Star 1:", ans)
}

func star2(data []string) {
	ans := 0
	for _, s := range data {
		var zero, one, two, three, four, five, six, seven, eight, nine string
		var pos235, pos069 []string
		split := strings.Split(s, " ")
		usp := split[:10]
		out := split[11:]
		for _, o := range usp {
			tmp := strings.Split(o, "")
			sort.Strings(tmp)
			o = strings.Join(tmp, "")
			n := len(o)
			if n == 2 && one == "" {
				one = o
			} else if n == 3 && seven == "" {
				seven = o
			} else if n == 4 && four == "" {
				four = o
			} else if n == 7 && eight == "" {
				eight = o
			} else if n == 5 {
				// 2, 3, 5
				pos235 = append(pos235, o)
			} else if n == 6 {
				// 0, 6, 9
				pos069 = append(pos069, o)
			}
		}
		//fmt.Println(pos069, pos235)
		for _, p := range pos069 {
			if strings.Contains(p, string(one[0])) && strings.Contains(p, string(one[1])) {
				if strings.Contains(p, string(four[0])) && strings.Contains(p, string(four[1])) &&
					strings.Contains(p, string(four[2])) && strings.Contains(p, string(four[3])) {
					nine = p
				} else {
					zero = p
				}
			} else {
				six = p
			}
			if zero != "" && nine != "" && six != "" {
				break
			}
		}

		for _, p := range pos235 {
			if strings.Contains(p, string(one[0])) && strings.Contains(p, string(one[1])) {
				three = p
			} else {
				if strings.Contains(six, string(p[0])) && strings.Contains(six, string(p[1])) &&
					strings.Contains(six, string(p[2])) && strings.Contains(six, string(p[3])) &&
					strings.Contains(six, string(p[4])) {
					five = p
				} else {
					two = p
				}
			}
			if two != "" && three != "" && five != "" {
				break
			}
		}
		n := len(out)
		for i, o := range out {
			tmp := strings.Split(o, "")
			sort.Strings(tmp)
			o = strings.Join(tmp, "")
			ten := int(math.Pow10(n - i - 1))
			switch o {
			case zero:
				ans += 0
			case one:
				ans += 1 * ten
			case two:
				ans += 2 * ten
			case three:
				ans += 3 * ten
			case four:
				ans += 4 * ten
			case five:
				ans += 5 * ten
			case six:
				ans += 6 * ten
			case seven:
				ans += 7 * ten
			case eight:
				ans += 8 * ten
			case nine:
				ans += 9 * ten
			default:
				fmt.Println(o)
			}
		}
	}
	fmt.Println("Star 2:", ans)
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n")
	star1(data)
	star2(data)
}
