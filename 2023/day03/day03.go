package main

/*
   Day 03: https://adventofcode.com/2023/day/3
*/

import (
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
	"unicode"
)

    var inputFile = flag.String("input", "../inputs/day03.txt", "Relative path to input-file")
    
    func constainsSymbol(rs []rune) bool {
        for _,r := range(rs) {
            if !unicode.IsDigit(r) && r != '.' {
                return true
            }
        }
        return false
    }

    func star1(data [][]rune) {
        sum := 0
        for i,row := range(data) {
            digit := false
            iStart := 0
            for j,r := range(row) {
                if unicode.IsDigit(r) {
                    if (!digit) {
                        iStart = j
                        digit = true
                    }
                    if digit && j == len(row)-1 {
                        digit = false
                        sum += checkAdjacent(iStart, j+1, row, i, data)
                    }
                } else if digit {
                    digit = false
                    sum += checkAdjacent(iStart, j, row, i, data)
                }
                
            }
        }
        fmt.Println("Star 1:", sum)
    }

func checkAdjacent(iStart int, j int, row []rune, i int, data [][]rune) int {
	s1 := iStart - 1
	if s1 < 0 {
		s1 = 0
	}
	s2 := min(j+1, len(row))
	symbol := constainsSymbol(row[s1:s2])
	if i < len(data)-1 && !symbol {
		symbol = constainsSymbol(data[i+1][s1:s2])
	}
	if i > 0 && !symbol {
		symbol = constainsSymbol(data[i-1][s1:s2])
	}
	if symbol {
		n, _ := strconv.Atoi(string(row[iStart:j]))
		return n
	}
    return 0
}

func numberOfNumbers(rs []rune, jS int, jE int) (int, []int) {
    //fmt.Println(string(rs))
    n := 0
    ongoing := false
    start := 0
    end := 0
    var nums []int
    for i,r := range(rs[jS:jE]) {
        if unicode.IsDigit(r) {
            end=jS+i
            if !ongoing {
                n++
                start=jS+i
                if i==0 {
                    for k:=jS;k>=0 && unicode.IsDigit(rs[k]);k-- {
                        start=k
                    }
                }
                ongoing=true
            }
            if end+1==jE {
                for k:=end;k<len(rs) && unicode.IsDigit(rs[k]);k++ {
                    end=k
                }
                x,_ := strconv.Atoi(string(rs[start:end+1]))
                nums = append(nums, x)
            }
        } else if ongoing {
            ongoing=false
            x,_ := strconv.Atoi(string(rs[start:end+1]))
            //fmt.Println("SE", start, end, x)
            nums = append(nums, x)
        }
    }
    return n, nums
}

func star2(data [][]rune) {
    sum := 0
    for i,x := range(data) {
        for j,y := range(x) {
            if y == '*' {
                var nums []int
                jS := j-1
                jE := j+2
                if jS<0 {jS = 0}
                if jE>len(x) {jE = len(x)}
                n0, nums0 := numberOfNumbers(x, jS, jE)
                n := n0
                nums = append(nums, nums0...)
 
                if i > 0{
                    n1, nums1 :=numberOfNumbers(data[i-1], jS, jE)
                    n += n1
                    nums = append(nums, nums1...)
                }
                if i < len(data){
                    n2, nums2 :=numberOfNumbers(data[i+1], jS, jE)
                    n += n2
                    nums = append(nums, nums2...)
                    
                }
                if n==2 {
                    fmt.Println("",n, nums)
                    power := nums[0]*nums[1]
                    sum += power
                }
            }
        }
    }
    fmt.Println("Star 2:", sum)
}

func main() {
    flag.Parse()
    raw, err := os.ReadFile(*inputFile)
    if err != nil {
        panic("Invalid file")
    }
    rawStr := strings.TrimSpace(string(raw))
    data := strings.Split(rawStr, "\n")
    m := make([][]rune, len(data))
    for i, ln := range(data){
        m[i] = make([]rune, len(ln))
        for j, c := range(ln) {
            m[i][j] = c
        }
    }
    star1(m)
    star2(m)
}
