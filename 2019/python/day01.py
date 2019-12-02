"""
Day 1: The Tyrrany of the Rocket equation

Calculating the fuel requirements for a space craft
"""

from __future__ import print_function
import math
import time

def fuelNeeded(n):
	fuel = math.trunc(int(n)/3)-2
	if fuel > 0:
		return fuel
	return 0


def star1(file):
	fuelTotal = 0
	for line in file:
		fuel = fuelNeeded(line)
		fuelTotal = fuelTotal + fuel
	return fuelTotal

def star2(file):
	fuelTotal = 0
	for line in file:
		fuel = fuelNeeded(line)
		moduleFuel = fuel
		while fuel > 0:
			fuel = fuelNeeded(fuel)
			moduleFuel = moduleFuel + fuel
		fuelTotal = fuelTotal + moduleFuel
			
	return fuelTotal

def main():
	day01input = open("/repo/AdventOfCode/2019/inputs/day01.txt", 'r')
	ans1 = star1(day01input)
	day01input.seek(0)
	ans2 = star2(day01input)
	print("Star 1:", ans1)
	print("Star 2:", ans2)