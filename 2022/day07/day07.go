
    package main

    /*
    Day 07: https://adventofcode.com/2022/day/7
    */

    import (
        "flag"
        "fmt"
        "io/ioutil"
        "strings"
        "strconv"
    )

    var inputFile = flag.String("input", "../inputs/day07.txt", "Relative path to input-file")
    
    type Node struct {
        name string
        size int
        parent *Node
    }

    func generateTree(data []string) {
        pos := Node{"/", 0, nil}
        for _,ln := range data {
            if ln[0] == '$' {
                var cmd, dest string
                fmt.Sscanf(ln, "$ %s %s", &cmd, &dest)
                if cmd == "cd" {
                    if dest == ".." {
                        size := pos.size
                        pos = *pos.parent
                        pos.size += size
                    } else {
                        new := Node{dest, 0, &pos}
                        pos = new
                    } 
                } else if cmd == "ls" {
                    // Do nothing
                }
            }else {
                lsOut := strings.Split(ln, " ")
                // List
                if lsOut[0] == "dir" {

                } else {
                    size,_ := strconv.Atoi(lsOut[0])
                    pos.size += size
                }
            }
        }
        fmt.Println(pos)
    }

    func star1(data []string) {
        fmt.Println("Star 1:", data[0])
    }

    func star2(data []string) {
        fmt.Println("Star 2:", data[0])
    }

    func main() {
        flag.Parse()
        raw, err := ioutil.ReadFile(*inputFile)
        if err != nil {
            panic("Invalid file")
        }
        rawStr := strings.TrimSpace(string(raw))
        data := strings.Split(rawStr, "\n")
        generateTree(data)
        star1(data)
        star2(data)
    }
    