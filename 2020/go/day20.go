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
	l1 := len(p)
	l2 := len(p[0])
	newP := make([][]int, l2)
	for k:=0;k<l2;k++{
		newP[k] = make([]int, l1)
	}
	for i:=0;i<l1;i++{ 
		row := p[i]
		for j:=0;j<l2;j++{
			newP[j][l1-1-i] = row[j]
		}
	}
	return newP
}

func flipX(p [][]int) ([][]int) {
	l1 := len(p)
	l2 := len(p[0])
	newP := make([][]int, l1)
	for k:=0;k<l1;k++{
		newP[k] = make([]int, l2)
	}
	for i:=0;i<l1;i++{ 
		row := p[i]
		for j:=0;j<l2;j++{
			newP[i][j] = row[l2-1-j]
		}
	}
	return newP
}

func flipY(p [][]int) ([][]int) {
	l1 := len(p)
	l2 := len(p[0])
	newP := make([][]int, l1)
	for k:=0;k<l1;k++{
		newP[k] = make([]int, l2)
	}

	for i:=0;i<l1;i++{ 
		for j:=0;j<l2;j++{
			newP[i][j] = p[l1-1-i][j]
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
		for _,n := range v {
			if n==1 {
				fmt.Print("#")
			} else if n == 2 {
				fmt.Print("O")
			} else {
				fmt.Print(".")
			}
		}
		fmt.Print("\n")
	}
	fmt.Print("\n")
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
	var newPiece Piece
	newPiece.id = p.id
	newPiece.match_id = p.match_id
	for _,row := range p.piece[1:len(p.piece)-1] {
		newPiece.piece = append(newPiece.piece, row[1:len(row)-1])
	}
	return newPiece
}


func trimPiece2(p [][]int) [][]int {
	var newPiece [][]int
	for _,row := range p[1:len(p)-1] {
		newPiece = append(newPiece, row[1:len(row)-1])
	}
	return newPiece
}


func assemble(pieces map[int]Piece) [][]Piece {
	// find a starting point (corner piece)

	start := 0
	for _,p := range pieces {
		if len(p.match_id) == 2 {
			start = p.id
		}
	}
	grid := make([][]Piece, 0	)

	placed := make(map[int]bool)
	placed[start] = true
	next := start

	// First row
	var row []Piece
	if next == start {
		row = append(row, pieces[next])
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
		row = append(row, pieces[next])
	}
	placed[next] = true
	// Reseterande 

	grid = append(grid, row)
	for len(placed) < len(pieces) {
		var newRow []Piece
		for _,id := range row {
			alt := pieces[id.id].match_id
			alt = trimSlice(alt, placed)
			if len(alt) != 1 {
				//fmt.Println(len(alt), placed)
				panic("oops")
			}
			placed[alt[0]] = true
			newRow = append(newRow, pieces[alt[0]])
		}
		grid = append(grid, newRow)
		row = newRow
	}

	return grid
}

func merge(p1 [][]int, p2 [][]int) [][]int {
	//a,b,c,d,e,f,g,h := true,true,true,true,true,true,true,true
	xyz:=0
	for len(p1) != len(p2) {
		p2 = rotate(p2)
		if xyz>4 {
			fmt.Println(len(p1), len(p1[0]))
			printM(rotate(p1))
			fmt.Println(len(p2), len(p2[0]))
			printM(p2)
			panic("mismatch")
		}
		xyz++
	}
	l:=len(p1)
	
	for x:=0;x<4;x++{
		for y:=0;y<4;y++{
			for b:=0;b<4;b++{
				for c:=0;c<4;c++{
					a:=true
					l1:=len(p1[0])
					if len(p1) != len(p2) {
						continue
					}
					for i:=0;i<l;i++ {
						if (p1[i][l1-1] != p2[i][0]) {
							a=false
							break
						}
					}
					if a {
						// merge
						var newP [][]int
						for j,_ := range p1 {
							newRow := append(p1[j][:l1-1],p2[j][1:]...)
							newP = append(newP,newRow)
						}
						return newP
					}
					p1 = flipX(p1)
				}
				p1 = flipY(p1)	
			}
			p1 = rotate(p1)
		}
		p2 = rotate(p2)
	}
	printM(p1)
	printM(rotate(p1))
	printM(p2)
	panic("oh no")
	return nil
}


func findSeamonsters(img [][]int) int {
	h:=len(img)
	l:=len(img[0])
	rough := 0
	for _,r := range img {
		for _,n := range r {
			rough += n
		}
	}
	//fmt.Println(rough)

	var seamonster [][]int 
	seamonster = append(seamonster, []int{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0})
	seamonster = append(seamonster, []int{1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1})
	seamonster = append(seamonster, []int{0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0})
	smh := len(seamonster)
	sml := len(seamonster[0])
	smrough:=0
	printM(seamonster)
	for _,r := range seamonster {
		for _,n := range r {
			smrough += n
		}
	}
	
	printM(img)
	fmt.Println(rough, smrough)
	found := 0
	for x:=0;x<4;x++{
		for y:=0;y<4;y++{
			for z:=0;z<4;z++{
				fmt.Println(z)
				printM(img)

				isSm := true
				for i:=0;i<h-smh;i++ {
					for j:=0;j<l-sml;j++ {
						isSm = true
						for a:=0;a<smh;a++ {
							for b:=0;b<sml;b++ {
								if seamonster[a][b] == 1 {
									fmt.Print(seamonster[a][b], img[i][j], ",")
									if img[i][j] != 1 {
										isSm = false
										break
									}
								}
							}
							if !isSm {
								break
							}
						}
						if isSm {
							printM(seamonster)
							fmt.Println(i,j, smh, sml)
							printM(img[i:i+smh])
							found++
							i += smh
							j += sml
						}
					}	
				}
				if found > 0 {
					printM(img)
					fmt.Println(rough, smrough, found)
					return rough - smrough*found
				}
					
				img = rotate(img)
			}
			img = flipX(img)
		}
		img = flipY(img)
	}
	printM(img)
	//panic("WTF!")
	return rough
}

func makeImage(grid [][]Piece) [][]int {
	var img [][]int
	for i,row := range grid {
		var imgR [][]int
		for j,p := range row {
			if j == 0 {
				imgR = p.piece
			} else {
				imgR = merge(imgR, p.piece)
			}
			
		}
		/*fmt.Println("Row", i)
		fmt.Println(len(imgR), len(imgR[0]))
		imgR = rotate(imgR)
		fmt.Println(len(imgR), len(imgR[0]))*/
		if i == 0 {
			img = imgR
		} else {
			img = merge(img, imgR)
		}
	}
	/*img = trimPiece2(img)
	printM(img)
	printM(rotate(img))*/
	return img
}

func star2(p []Piece) {
	pm := initPiecesMap(p)
	a := assemble(pm)
	img := makeImage(a)
	img = trimPiece2(img)

	b:= findSeamonsters(img)

	fmt.Println("Star 2:", b)
	/*for i:=0;i<4;i++ {
		img = rotate(img)
		printM(img)
	}
	img = flipX(img)
	for i:=0;i<4;i++ {
		img = rotate(img)
		printM(img)
	}
	img = flipY(img)
	for i:=0;i<4;i++ {
		img = rotate(img)
		printM(img)
	}*/
	//fmt.Println(".#.#..#.##...#.##..#####\n###....#.#....#..#......\n##.##.###.#.#..######...\n###.#####...#.#####.#..#\n##.#....#.##.####...#.##\n...########.#....#####.#\n....#..#...##..#.#.###..\n.####...#..#.....#......\n#..#.##..#..###.#.##....\n#.####..#.####.#.#.###..\n###.#.#...#.######.#..##\n#.####....##..########.#\n##..##.#...#...#.#.#.#..\n...#..#..#.#.##..###.###\n.#.#....#.##.#...###.##.\n###.#...#..#.##.######..\n.#.#.###.##.##.#..#.##..\n.####.###.#...###.#..#.#\n..#.#..#..#.#.#.####.###\n#..####...#.#.#.###.###.\n#####..#####...###....##\n#.##..#..#...#..####...#\n.#.###..##..##..####.##.\n...###...##...#...#..###")
}

func main() {
	raw, _ := ioutil.ReadFile("../inputs/day20_example.txt")
	data := strings.Split(string(raw), "\n\n")

	p := star1(data[:len(data)-1])
	star2(p)
}
