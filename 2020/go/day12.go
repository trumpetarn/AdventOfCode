package main
/*
Day 12: Rain Risk

https://adventofcode.com/2020/day/12
*/

import (
    "fmt"
    "io/ioutil"
    "strings"
    "math"
    //"strconv"
    //"sort"
)

type Direction int

const (
    N Direction = iota
    E
    S
    W
)

type Position struct {
    x int
    y int
}

type Ferry struct {
    dir Direction
    pos Position
}

func dir2rune(dir Direction) rune {
    switch dir {
    case N:
        return 'N'
    case E:
        return 'E'
    case S:
        return 'S'
    case W:
        return 'W'
    }
    return 'X'
}

func manhattan(p1 Position, p2 Position) int {
    return int(math.Abs(float64(p2.x-p1.x))+math.Abs(float64(p2.y-p1.y)))
}

func rotate(deg int, dir Direction) Direction {
    steps := deg/90
    n := (int(dir)+steps) % 4
    if n < 0 {
        n = 4 + n
    }
    return Direction(n)
}

func rotateWp(deg int, wp Position) Position{
    var newWp Position
    switch rotate(deg, N){
    case N:
        newWp.x = wp.x
        newWp.y = wp.y
    case E:
        newWp.x = wp.y
        newWp.y = -1*wp.x
    case S:
        newWp.x = -1*wp.x
        newWp.y = -1*wp.y
    case W:
        newWp.x = -1*wp.y
        newWp.y = wp.x
    }
    return newWp
}

func star1(data []string) {
    var sp Position
    var f Ferry
    f.dir = E
    for _, s := range data {
        var r rune
        var n int
        fmt.Sscanf(s, "%c%d", &r, &n)
        if r == 'F' {
            r = dir2rune(f.dir)
        }
        switch r {
        case 'N':
            f.pos.y += n
        case 'E':
            f.pos.x += n
        case 'W':
            f.pos.x -= n
        case 'S':
            f.pos.y -= n
        case 'F':
            continue
        case 'L':
            f.dir = rotate(-n, f.dir)
        case 'R':
            f.dir = rotate(n, f.dir)
        default:
            panic(fmt.Sprintf("Invalid instruction (%c)", r))
        }
    }
    fmt.Println("Star 1:", manhattan(sp, f.pos))
}

func star2(data []string) {
    var wp Position // Relative to derry
    wp.x = 10
    wp.y = 1
    var f Ferry
    f.dir = E
    for _, s := range data {
        var r rune
        var n int
        fmt.Sscanf(s, "%c%d", &r, &n)
        switch r {
        case 'N':
            wp.y += n
        case 'E':
            wp.x += n
        case 'W':
            wp.x -= n
        case 'S':
            wp.y -= n
        case 'F':
            f.pos.x += n*wp.x
            f.pos.y += n*wp.y
        case 'L':
            wp = rotateWp(-n, wp)
        case 'R':
            wp = rotateWp(n, wp)
        default:
            panic(fmt.Sprintf("Invalid instruction (%c)", r))
        }
        //fmt.Println(wp, f.pos)
    }
    var sp Position
    fmt.Println("Star 2:", manhattan(sp, f.pos))
}

func main() {
    raw, _ := ioutil.ReadFile("../inputs/day12.txt")
    data := strings.Split(string(raw), "\n")
    star1(data[:len(data)-1])
    star2(data[:len(data)-1])
}