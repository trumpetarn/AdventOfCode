package main

/*
   Day 07: https://adventofcode.com/2022/day/7
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

var inputFile = flag.String("input", "../inputs/day07.txt", "Relative path to input-file")

type File struct {
	name string
	size int
}

type Folder struct {
	files   []File
	folders []string
	size    int
}

func generateTree(data []string) map[string]Folder {
	folders := make(map[string]Folder)
	stack := make([]string, 0)
	root := Folder{make([]File, 0), make([]string, 0), 0}
	pos := "/"
	stack = append(stack, pos)
	folders[pos] = root
	total1 := 0
	total2 := 0
	for _, ln := range data {
		//fmt.Println(ln)
		if ln[0] == '$' {
			var cmd, dest string
			fmt.Sscanf(ln, "$ %s %s", &cmd, &dest)
			if cmd == "cd" {
				if dest == ".." {
					N := len(stack)
					stack = stack[:N-1]
					pos = stack[N-2]
				} else if dest == "/" {
					if len(stack) > 0 {
						stack = stack[:1]
						pos = dest
					}
				} else {
					pos += dest + "/"
					stack = append(stack, pos)
				}
			} /*else if cmd == "ls" {
				// Do nothing
				fmt.Println(pos)
			}*/
		} else {
			lsOut := strings.Split(ln, " ")
			// List
			if lsOut[0] == "dir" {
				current := folders[pos]
				current.folders = append(folders[pos].folders, lsOut[1])
				folders[pos] = current
			} else {
				current := folders[pos]
				s, _ := strconv.Atoi(lsOut[0])
				newFile := File{lsOut[1], s}
				current.files = append(folders[pos].files, newFile)
				folders[pos] = current
				for _, f := range stack {
					x := folders[f]
					x.size += s
					folders[f] = x
					total1 += s
				}
				total2 += s
			}
		}
		//fmt.Println(pos, stack)
	}
	return folders
}

func star1(data map[string]Folder) {
	subSize := 0
	for _, f := range data {
		if f.size <= 100000 {
			subSize += f.size
		}
	}
	fmt.Println("Star 1:", subSize)
}

func star2(data map[string]Folder) {
	diskSize := 70000000
	needed := 30000000
	used := data["/"].size
	free := diskSize - used
	smallest := diskSize
	for _, f := range data {
		if (free + f.size) >= needed {
			if f.size < smallest {
				smallest = f.size
			}
		}
	}
	fmt.Println("Star 2:", smallest)
}

func main() {
	flag.Parse()
	raw, err := ioutil.ReadFile(*inputFile)
	if err != nil {
		panic("Invalid file")
	}
	rawStr := strings.TrimSpace(string(raw))
	data := strings.Split(rawStr, "\n")
	fs := generateTree(data)
	star1(fs)
	star2(fs)
}
