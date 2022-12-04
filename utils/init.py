
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

def generate_pyfile(day, year):
    body = """
    \"\"\"
    Day {d:02d}: https://adventofcode.com/{y}/day/{d}
    \"\"\"
    from __future__ import print_function

    def star1(file):
        return file

    def star2(file):
        return file

    def main():
        day{d}input = open("/repo/AdventOfCode/{y}/inputs/day{d:02d}.txt", 'r')
        ans1 = star1(day{d}input)
        ans2 = star2(day{d}input)
        print("Star 1:", ans1)
        print("Star 2:", ans2)
    """.format(d=day, y=year)
    return body

def generate_cppfile(day, year):
    p1 = """
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <cstdint>
    #include <string>
    #include <vector>
    #include <algorithm>
    #include <map>
    #include <set>
    #include <numeric>
    #include <unistd.h>
    #include <iterator>
    #include <list>

    /* Day {d:02d}: https://adventofcode.com/{y}/day/{d} */
    
    using namespace std;
    namespace day{d:02d}""".format(d=day,y=year)
    p2 = """
    {
    vector<string> read_input(string loc)
    {
        vector<string> in;
        string line;
        ifstream infile (loc);
        if (infile.is_open())
        {
            while (getline(infile,line))
            {
                in.push_back(line);
            }
        }
        return in;
    }

    int main()
    {
    """
    p3 = """
        string loc = "../inputs/day{d:02d}.txt";
    """.format(d=day)
    p4 = """
        if (argc >= 2)
            loc = argv[1];

        vector<string> in = read_input(loc);
        return 0;
    }
    }
    """
    return p1+p2+p3+p4

def generate_cfile(day, year):
    p1="""
    #include<stdio.h>
    #include<stdbool.h>
    
    /* Day {d:02d}: https://adventofcode.com/{y}/day/{d} */

    """.format(d=day,y=year)
    p2 = """
    int main(void)
    {
        return 0;
    }
    """    
    return p1+p2

today = datetime.date.today()
year = today.strftime("%Y")

parser = argparse.ArgumentParser(prog = "InitializeAoC", description = "", epilog="")

parser.add_argument("lang", choices=["py", "go", "c", "c++", "cpp"], help="The language you like go use")
parser.add_argument("day", type=int, help="The number of the day you like to start implementing")

parser.add_argument("-y", "--year", type=int, help="Enter a year in the format YYYY, default is current year", default=year, choices=range(2015,int(year)+1))
parser.add_argument("-dr", "--dry-run", action='store_true', help="For testing and see what would have cahnged")



args = parser.parse_args()

print(args)

y = "./{}".format(args.year)
loc = "{}/day{:02d}/".format(y, args.day)
file = ""
if args.dry_run:
    print("Dry Run:")

if not os.path.exists(y):
    print("Creating", y)
    if not args.dry_run:
        os.mkdir(y)

if not os.path.exists(loc):
    print("Creating:", loc)
    if not args.dry_run:
        os.mkdir(loc)

if args.lang == "go":
    filename = "day{:02d}.go".format(args.day)
    if not os.path.exists(loc+filename):
        print("Create", loc+filename)
        file = generate_gofile(args.day, args.year)
        if not args.dry_run:
            f = open(loc+filename, 'w+')
            f.write(file)
elif args.lang == "py":
    filename = "day{:02d}.py".format(args.day)
    if not os.path.exists(loc+filename):
        print("Create", loc+filename)
        file = generate_pyfile(args.day, args.year)
        if not args.dry_run:
            f = open(loc+filename, 'w+')
            f.write(file)
elif args.lang == "cpp" or args.lang == "c++":
    filename = "day{:02d}.cpp".format(args.day)
    if not os.path.exists(loc+filename):
        print("Create", loc+filename)
        file = generate_cppfile(args.day, args.year)
        if not args.dry_run:
            f = open(loc+filename, 'w+')
            f.write(file)
elif args.lang == "c":
    print("WARNING: C does not have a complete template-file yet")
    filename = "day{:02d}.c".format(args.day)
    if not os.path.exists(loc+filename):
        print("Create", loc+filename)
        file = generate_cfile(args.day, args.year)
        if not args.dry_run:
            f = open(loc+filename, 'w+')
            f.write(file)

if args.dry_run:
    if file == "":
        print("No changes would have been made")
    else:
        print("File content would have been")
        print(file)
