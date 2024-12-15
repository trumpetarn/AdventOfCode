package main

/*
$title_comment
*/

import (
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

var inputFile = flag.String("input", ".$input_file", "Relative path to input-file")

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
