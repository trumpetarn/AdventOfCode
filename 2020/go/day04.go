package main

/*
Day 04: Passport processing

https://adventofcode.com/2020/day/4
*/

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

/*
   byr
   iyr (Issue Year)
   eyr (Expiration Year)
   hgt (Height)
   hcl (Hair Color)
   ecl (Eye Color)
   pid (Passport ID)
   cid (Country ID)
*/
type passport struct {
	byr    int    // Birth Year
	iyr    int    // Issue Year
	eyr    int    // Expiration Year
	hgt    string // Height
	hcl    string // Hair Color
	ecl    string // Eye Color
	pid    int    // Passport ID
	pidlen int    // Length of Pid
	cid    int    // Country ID
}

func newPassport() *passport {
	return &passport{
		byr:    -1,
		iyr:    -1,
		eyr:    -1,
		hgt:    "",
		hcl:    "",
		ecl:    "",
		pid:    -1,
		pidlen: 0,
		cid:    -1,
	}
}

func Split(r rune) bool {
	return r == '\n' || r == ' '
}

/*
   byr (Birth Year) - four digits; at least 1920 and at most 2002.
   iyr (Issue Year) - four digits; at least 2010 and at most 2020.
   eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
   hgt (Height) - a number followed by either cm or in:
       If cm, the number must be at least 150 and at most 193.
       If in, the number must be at least 59 and at most 76.
   hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
   ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
   pid (Passport ID) - a nine-digit number, including leading zeroes.
   cid (Country ID) - ignored, missing or not.
*/
func isValidFields(p *passport) bool {
	return (p.byr != -1 && p.iyr != -1 && p.eyr != -1 && p.pid != -1 && len(p.hgt) > 0 && len(p.hcl) > 0 && len(p.ecl) > 0)
}

func isValidEcl(ecl string) bool {
	valid := [7]string{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"}
	for _, s := range valid {
		if s == ecl {
			return true
		}
	}
	return false
}

func isValidHgt(hgt string) bool {
	height, _ := strconv.Atoi(hgt[:len(hgt)-2])
	unit := hgt[len(hgt)-2:]
	if string(unit) == "cm" {
		if height >= 150 && height <= 193 {
			return true
		}
	} else if string(unit) == "in" {
		if height >= 59 && height <= 76 {
			return true
		}
	}
	return false
}

func isValidHcl(hcl string) bool {
	if len(hcl) != 7 {
		return false
	}
	valid := "0123456789abcdef#"
	for i, c := range hcl {
		if c == '#' && i > 0 {
			return false
		}
		if !strings.ContainsRune(valid, c) {
			return false
		}
	}
	return true
}

func isValidData(p *passport) bool {
	if !isValidFields(p) {
		return false
	}
	if p.byr < 1920 || p.byr > 2002 {
		return false
	}
	if p.iyr < 2010 || p.iyr > 2020 {
		return false
	}
	if p.eyr < 2020 || p.eyr > 2030 {
		return false
	}
	if p.pidlen != 9 {
		return false
	}
	if !isValidHcl(p.hcl) {
		return false
	}
	if !isValidEcl(p.ecl) {
		return false
	}
	if !isValidHgt(p.hgt) {
		return false
	}
	return true
}

func input2Passport(data []string, p *passport) {
	for _, s := range data {
		keyval := strings.Split(s, ":")
		key, val := keyval[0], keyval[1]
		switch key {
		case "byr":
			p.byr, _ = strconv.Atoi(val)
		case "iyr":
			p.iyr, _ = strconv.Atoi(val)
		case "eyr":
			p.eyr, _ = strconv.Atoi(val)
		case "hgt":
			p.hgt = val
		case "hcl":
			p.hcl = val
		case "ecl":
			p.ecl = val
		case "pid":
			p.pidlen = len(val)
			p.pid, _ = strconv.Atoi(val)
		case "cid":
			p.cid, _ = strconv.Atoi(val)
		default:
			fmt.Println("Oops, something went worng!")
		}
	}
}

func star1(data []string) {
	var valid int
	for _, s := range data {
		p := newPassport()
		a := strings.FieldsFunc(s, Split)
		input2Passport(a, p)
		if isValidFields(p) {
			valid++
		}
	}
	fmt.Println("Star 1:", valid)
}

func star2(data []string) {
	var valid int
	for _, s := range data {
		p := newPassport()
		a := strings.FieldsFunc(s, Split)
		input2Passport(a, p)
		if isValidData(p) {
			valid++
		}
	}
	fmt.Println("Star 2:", valid)
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day04.txt")
	data := strings.Split(string(raw), "\n\n")
	star1(data)
	star2(data)
}
