#!/bin/python3

import argparse
import datetime
import os
from string import Template
from pathlib import Path


def generate(s, temp_file):
    f = Path(temp_file).read_text()
    temp = Template(f)
    return temp.substitute(s)


def generate_cfile(day, year):
    p1 = """
    #include<stdio.h>
    #include<stdbool.h>
    
    /* Day {d:02d}: https://adventofcode.com/{y}/day/{d} */

    """.format(
        d=day, y=year
    )
    p2 = """
    int main(void)
    {
        return 0;
    }
    """
    return p1 + p2


def setup_parser():
    today = datetime.date.today()
    year = today.strftime("%Y")
    parser = argparse.ArgumentParser(prog="InitializeAoC", description="", epilog="")
    parser.add_argument(
        "lang",
        choices=["py", "go", "c", "c++", "cpp"],
        help="The language you like go use",
    )
    parser.add_argument(
        "day", type=int, help="The number of the day you like to start implementing"
    )
    parser.add_argument(
        "-y",
        "--year",
        type=int,
        help="Enter a year in the format YYYY, default is current year",
        default=year,
        choices=range(2015, int(year) + 1),
    )
    parser.add_argument(
        "-dr",
        "--dry-run",
        action="store_true",
        help="For testing and see what would have cahnged",
    )
    parser.add_argument(
        "-f", "--test-files", action="store_true", help="Create empty test-files"
    )
    return parser.parse_args()


def main():

    args = setup_parser()

    print(args)

    y = "./{}".format(args.year)
    loc = "{}/day{:02d}/".format(y, args.day)
    if args.lang == "py":
        loc = "{}/".format(y)
    file = ""
    substitutes = {
        "title_comment": "Day {:02d}\n\nhttps://adventofcode.com/{}/day/{}".format(
            args.day, args.year, args.day
        ),
        "input_file": "./inputs/day{:02d}.in".format(args.day),
    }
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
        if not os.path.exists(loc + filename):
            print("Create", loc + filename)
            file = generate(substitutes, "./templates/dayXX.go")
            if not args.dry_run:
                f = open(loc + filename, "w+")
                f.write(file)
    elif args.lang == "py":
        filename = "day{:02d}.py".format(args.day)
        if not os.path.exists(loc + filename):
            print("Create", loc + filename)
            file = generate(substitutes, "./templates/dayXX.py")
            if not args.dry_run:
                f = open(loc + filename, "w+")
                f.write(file)
    elif args.lang == "cpp" or args.lang == "c++":
        filename = "day{:02d}.cpp".format(args.day)
        if not os.path.exists(loc + filename):
            print("Create", loc + filename)
            file = generate(substitutes, "./templates/dayXX.cpp")
            if not args.dry_run:
                f = open(loc + filename, "w+")
                f.write(file)
    elif args.lang == "c":
        print("WARNING: C does not have a complete template-file yet")
        filename = "day{:02d}.c".format(args.day)
        if not os.path.exists(loc + filename):
            print("Create", loc + filename)
            file = generate_cfile(args.day, args.year)
            if not args.dry_run:
                f = open(loc + filename, "w+")
                f.write(file)

    if args.test_files:
        in_file = "{}/inputs/day{:02d}.txt".format(y, args.day)
        dbg_file = "{}/inputs/day{:02d}_debug.txt".format(y, args.day)
        if not os.path.exists(in_file) and not args.dry_run:
            f = open(in_file, "w+")
            f.write("\n")
        if not os.path.exists(dbg_file) and not args.dry_run:
            f = open(dbg_file, "w+")
            f.write("\n")
        if args.dry_run:
            print("Creating empty input files")

    if args.dry_run:
        if file == "":
            print("No changes would have been made")
        else:
            print("File content would have been")
            print(file)


if __name__ == "__main__":
    main()
