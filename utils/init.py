
import argparse
import datetime

today = datetime.date.today()
year = today.strftime("%Y")

parser = argparse.ArgumentParser(prog = "InitializeAoC", description = "", epilog="")

parser.add_argument("day", type=int, help="The number of the day you like to start implementing")
parser.add_argument("lang", choices=["py", "go", "c", "c++", "cpp"], help="The language you like go use")

parser.add_argument("-y", "--year", type=int, help="Enter a year in the format YYYY", default=year)



args = parser.parse_args()

print(args)

if args.lang == "go":
    loc = "./{year}/day{n:02d}".format(year=args.year, n=args.day)
    print("mkdir ", loc)