
    package main

    /*
    Day 02: https://adventofcode.com/2023/day/2
    */

    import (
        "flag"
        "fmt"
        "io/ioutil"
        "strings"
        "regexp"
        "strconv"
    )
    
    var inputFile = flag.String("input", "../inputs/day02.txt", "Relative path to input-file")
    
    func star1(ins []string) {
        ans := 0
        for i, ln := range ins {
            s1 := strings.Split(ln, ":")
            s2 := strings.Split(s1[1], ";")
            check := true
            for _,s3 := range s2 {
                r := regexp.MustCompile(`(\d+ (red|green|blue))`)
                matches := r.FindAllString(s3, -1)
                cube := make(map[string]int)
                cube["blue"] = 0
                cube["green"] = 0
                cube["red"] = 0
                for _, v := range matches {
                    tmp := strings.Split(v, " ")
                    cube[tmp[1]],_ = strconv.Atoi(tmp[0])
                    if (cube["red"] >12 || cube["green"] >13 || cube["blue"] >14) {
                        check = false
                        break
                    }
                }   
            }
            if (check) {
                ans += i+1
            }
        }
        fmt.Println("Star 1:", ans)
    }

    func star2(ins []string) {
        ans := 0
        for _, ln := range ins {
            s1 := strings.Split(ln, ":")
            s2 := strings.Split(s1[1], ";")
            power := 0
            min_red := 0
            min_blue := 0
            min_green := 0
            for _,s3 := range s2 {
                r := regexp.MustCompile(`(\d+ (red|green|blue))`)
                matches := r.FindAllString(s3, -1)
                cube := make(map[string]int)
                cube["blue"] = 0
                cube["green"] = 0
                cube["red"] = 0
                
                for _, v := range matches {
                    tmp := strings.Split(v, " ")
                    cube[tmp[1]],_ = strconv.Atoi(tmp[0])
                    if (cube["red"] > min_red) {
                        min_red = cube["red"]
                    }
                    if (cube["green"] > min_green) {
                        min_green = cube["green"]
                    }
                    if (cube["blue"] > min_blue) {
                        min_blue = cube["blue"]
                    }
                } 
            }
            power = min_blue*min_green*min_red 
            fmt.Println(power)
            ans += power
        }
        fmt.Println("Star 2:", ans)
    }

    func main() {
        flag.Parse()
        raw, err := ioutil.ReadFile(*inputFile)
        if err != nil {
            panic("Invalid file")
        }
        rawStr := strings.TrimSpace(string(raw))
        data := strings.Split(rawStr, "\n")
        star1(data)
        star2(data)
    }
    