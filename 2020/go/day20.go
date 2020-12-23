package main
/*
Day 20: Jurassic Jigsaw

https://adventofcode.com/2020/day/20
*/

import (
	"fmt"
	"io/ioutil"
	"strings"
	//"strconv"
)

type Piece struct {
	id int
	piece [][]int
	match_id []int
}

func rotate(p *Piece) {
	new := p
	for i:=0;i<len(p.piece);i++{
		for j:=0;j<len(p.piece);j++{
			new.piece[]
		}	
	}
}

func flip(p *Piece) {

}

func matches(p1 Piece, p2 Piece) bool {
	for i:=0; i<4;i++ {
		for j:=0; j<4; j++{
			b := true
			for k:=0; k<len(p1.piece[i]); k++ {
				if p1.piece[i][k] != p2.piece[i][k]{
					b = false
					break
				}
			}
			if b {
				return true
			}
			rotate(&p2)
		}
		rotate(&p1)
	}
	return false
}

func star1(data []string) {	
	pieces := make([]Piece, len(data))
	for i,s := range data {
		p := strings.Split(s, "\n")
		var n int
		fmt.Sscanf(p[0], "Tile %d:", &n) 
		pieces[i].id = n
		for _,v := range p[1:] {
			var a []int
			for _,r := range v {
				if r == '.' {
					a = append(a,0)
				}else{
					a = append(a,1)
				}
			}
			pieces[i].piece = append(pieces[i].piece, a)
		}
	}


	for i,p1 := range pieces {
		for _,p2 := range pieces[i+1:] {
			if matches(p1,p2) {
				pieces[i].match_id = append(pieces[i].match_id, p2.id)
			}
		}
	}
	fmt.Println("Star 1:", pieces[0])
}

func star2(data []string) {
	fmt.Println("Star 2:")
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day20_example.txt")
	data := strings.Split(string(raw), "\n\n")

	star1(data[:len(data)-1])
	star2(data[:len(data)-1])
}
