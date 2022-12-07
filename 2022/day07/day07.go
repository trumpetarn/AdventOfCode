
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
        childs []Node
        parent *Node
    }
    type Data struct {
        name string
        size int
    }

    func generateTree(data []string) {
        root := Node{"/", 0, make([]Node, 0), nil}
        currentPos := &root
        pos := "/"
        test := make(map[string][]Data)
        for _,ln := range data {
            if ln[0] == '$' {
                var cmd, dest string
                fmt.Sscanf(ln, "$ %s %s", &cmd, &dest)
                if cmd == "cd" {
                    if dest == ".." {
                        currentPos = currentPos.parent
                    } else {
                        newFolder := Node{dest, 0, make([]Node, 0), currentPos}
                        currentPos.childs = append(currentPos.childs, newFolder)
                        currentPos = &newFolder
                        pos = dest
                    } 
                } else if cmd == "ls" {
                    // Do nothing
                }
            }else {
                lsOut := strings.Split(ln, " ")
                // List
                if lsOut[0] == "dir" {
                    test[pos] = append(test[pos], Data{lsOut[1], 0})
                } else {
                    size,_ := strconv.Atoi(lsOut[0])
                    newFile := Node{lsOut[1], size, make([]Node, 0), currentPos}
                    currentPos.childs = append(currentPos.childs, newFile)
                    test[pos] = append(test[pos], Data{lsOut[1], size})
                }
            }
            // fmt.Println(currentPos)
        }
        fmt.Println(currentPos.parent)
        fmt.Println(test)
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
    