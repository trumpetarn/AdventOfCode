package main
/*
Day XX: Title

Some description
*/

import (
	"fmt"
	//"io"
	"io/ioutil"
	"strings"
)

func main() {
	data, _ := ioutil.ReadFile("dayXX.txt")
	lnData := strings.Split(string(data), "\n")
	for i, s := range lnData {
    fmt.Println(i, s)
	}
}