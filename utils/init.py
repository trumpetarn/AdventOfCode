
import argparse
import datetime
import os



def generate_gofile(day, year):
    top_comment = """
    package main

    /*
    Day {:02d}: https://adventofcode.com/{}/day/{}
    */

    import (
        "flag"
        "fmt"
        "io/ioutil"
        "strings"
    )

    var inputFile = flag.String("input", "../inputs/day{:02d}.txt", "Relative path to input-file")
    """.format(day,year,day,day)

    body = """
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
        data := strings.Split(rawStr, "\\n\\n")
        star1(data)
        star2(data)
    }
    """
    return top_comment+body







today = datetime.date.today()
year = today.strftime("%Y")

parser = argparse.ArgumentParser(prog = "InitializeAoC", description = "", epilog="")

parser.add_argument("lang", choices=["py", "go", "c", "c++", "cpp"], help="The language you like go use")
parser.add_argument("day", type=int, help="The number of the day you like to start implementing")

parser.add_argument("-y", "--year", type=int, help="Enter a year in the format YYYY, default is current year", default=year, choices=range(2015,int(year)+1))



args = parser.parse_args()

print(args)

if args.lang == "go":
    y = "./{}".format(args.year)
    loc = "{}/day{:02d}/".format(y, args.day)
    filename = "day{:02d}.go".format(args.day)
    print("mkdir ", loc)
    if not os.path.exists(y):
        print("Creating", y)
        os.mkdir(y)
    if not os.path.exists(loc):
        print("Creating:", loc)
        os.mkdir(loc)
    if not os.path.exists(loc+filename):
        print("Create", loc+filename)
        
        f = open(loc+filename, 'w+')
        f.write(generate_gofile(args.day, args.year))