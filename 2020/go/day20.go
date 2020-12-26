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

// Rotates 90 degrees clockwise
func rotate(p [][]int) ([][]int) {
	l := len(p)
	newP := make([][]int, l)
	for k:=0;k<l;k++{
		newP[k] = make([]int, l)
	}
	for i:=0;i<l;i++{ 
		row := p[i]
		for j:=0;j<l;j++{
			newP[j][l-1-i] = row[j]
		}
	}
	return newP
}

func flipX(p [][]int) ([][]int) {
	l := len(p)
	newP := make([][]int, l)
	for k:=0;k<l;k++{
		newP[k] = make([]int, l)
	}
	for i:=0;i<l;i++{ 
		row := p[i]
		for j:=0;j<l;j++{
			newP[i][j] = row[l-1-j]
		}
	}
	return newP
}

func flipY(p [][]int) ([][]int) {
	l := len(p)
	newP := make([][]int, l)
	for k:=0;k<l;k++{
		newP[k] = make([]int, l)
	}

	for i:=0;i<l;i++{ 
		for j:=0;j<l;j++{
			newP[i][j] = p[l-1-i][j]
		}
	}
	return newP
}


func matches(p1 Piece, p2 Piece) bool {
	//a,b,c,d,e,f,g,h := true,true,true,true,true,true,true,true
	l:=len(p1.piece)
	for x:=0;x<2;x++{
		for y:=0;y<2;y++{
			for b:=0;b<4;b++{
				for c:=0;c<4;c++{
					a:=true
					for i:=0;i<l;i++ {
						if (p1.piece[i][0] != p2.piece[i][0]) {
							a=false
							break
						}
					}
					if a {
						return true
					}
					p2.piece = rotate(p2.piece)
				}
				p1.piece = rotate(p1.piece)
			}
			p1.piece = flipY(p1.piece)
		}
		p1.piece = flipX(p1.piece)
	}
	return false
}

func align(p1 [][]int, p2 [][]int) ([][]int, [][]int) {
	//a,b,c,d,e,f,g,h := true,true,true,true,true,true,true,true
	l:=len(p1)
	for x:=0;x<2;x++{
		for y:=0;y<2;y++{
			for b:=0;b<4;b++{
				for c:=0;c<4;c++{
					a:=true
					for i:=0;i<l;i++ {
						if (p1[i][0] != p2[i][0]) {
							a=false
							break
						}
					}
					if a {
						return p1, p2
					}
					p2 = rotate(p2)
				}
				p1 = rotate(p1)
			}
			p1 = flipY(p1)
		}
		p1 = flipX(p1)
	}
	return p1, p2
}

func initPieces(data []string) []Piece {
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
	return pieces
}

func initPiecesMap(data []Piece) map[int]Piece {
	pieces := make(map[int]Piece)
	for _,v := range data {
		pieces[v.id] = v
	}
	return pieces
}


func printM(M [][]int) {
	for _,v := range M {
		fmt.Println(v)
	}
}

func star1(data []string) []Piece{	
	pieces := initPieces(data)
	for i:=0;i<len(pieces);i++ {
		for j:=i+1;j<len(pieces);j++ {
			if (matches(pieces[i],pieces[j])) {
				pieces[i].match_id = append(pieces[i].match_id, pieces[j].id)
				pieces[j].match_id = append(pieces[j].match_id, pieces[i].id)
			}
		}
	}
	prod := 1
	for _,p:=range pieces {
		if len(p.match_id) == 2 {
			prod *= p.id
		}
	}
	fmt.Println("Star 1:", prod)
	return pieces
}

func trimSlice(s []int, r map[int]bool) []int {
	var ret []int
	for _,v := range s {
		if !r[v] {
			ret = append(ret, v)
		}
	}
	return ret
}

func trimPiece(p Piece) Piece {
	fmt.Println(p)
	var newPiece Piece
	newPiece.id = p.id
	newPiece.match_id = p.match_id
	for _,row := range p.piece[1:len(p.piece)-1] {
		newPiece.piece = append(newPiece.piece, row[1:len(row)-1])
	}
	fmt.Println(newPiece)
	return newPiece
}

func assemble(pieces map[int]Piece) [][]int {
	// find a starting point (corner piece)

	start := 0
	for _,p := range pieces {
		if len(p.match_id) == 2 {
			start = p.id
		}
	}
	grid := make([][]int, 0	)

	placed := make(map[int]bool)
	placed[start] = true
	next := start

	// First row
	var row []int
	if next == start {
		row = append(row, next)
	}
	//Loops
	lineBr:= false
	for !lineBr {
		placed[next] = true
		alt := pieces[next].match_id
		alt = trimSlice(alt, placed)
		tmp := -1
		for _,v := range alt {
			// Find which piece is edge piece 
			x := pieces[v].match_id
			x = trimSlice(x, placed)
			if len(x)<3 {
				tmp = v
				if len(x)==1 {
					lineBr=true //new line
				}
			}
		} 
		if len(alt) == 0 {
			//fmt.Println(pieces[next].match_id)
			//fmt.Println(placed)
			return grid
			// last piece
		}
		next = tmp
		row = append(row, next)
	}
	placed[next] = true
	// Reseterande 

	grid = append(grid, row)
	for len(placed) < len(pieces) {
		var newRow []int
		for _,id := range row {
			alt := pieces[id].match_id
			alt = trimSlice(alt, placed)
			if len(alt) != 1 {
				//fmt.Println(len(alt), placed)
				panic("oops")
			}
			placed[alt[0]] = true
			newRow = append(newRow, alt[0])
		}
		grid = append(grid, newRow)
		row = newRow
	}

	return grid
}


func star2(p []Piece) {
	pm := initPiecesMap(p)
	a := assemble(pm)

	trimPiece(pm[a[0][0]])
	fmt.Println("Star 2:", a)
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day20_example.txt")
	data := strings.Split(string(raw), "\n\n")

	p := star1(data[:len(data)-1])
	star2(p)
}
