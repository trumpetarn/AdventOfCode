
    package main

    /*
    Day 04: https://adventofcode.com/2023/day/4
    */

    import (
        "flag"
        "fmt"
        "io/ioutil"
        "strings"
    )

    var inputFile = flag.String("input", "../inputs/day04.txt", "Relative path to input-file")
    
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
        data := strings.Split(rawStr, "\n\n")
        star1(data)
        star2(data)
    }
    