package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

const RoundTurnValue = 100

var currentValue = 50
var zeroCount = 0

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		line := scanner.Text()
		if len(line) < 2 {
			continue
		} // Basic safety check

		dir := line[0]
		dist, err := strconv.Atoi(line[1:])
		if err != nil {
			fmt.Println("Invalid number:", line)
			continue
		}

		// 1. Handle Full Rotations mathematically
		zeroCount += dist / RoundTurnValue

		// 2. Simulate the remainder step-by-step
		remainder := dist % RoundTurnValue

		for i := 0; i < remainder; i++ {
			if dir == 'L' {
				currentValue--
				// Wrap around 0 -> 99
				if currentValue < 0 {
					currentValue = 99
				}
			} else { // R
				currentValue++
				// Wrap around 99 -> 0
				if currentValue >= RoundTurnValue {
					currentValue = 0
				}
			}

			// Only count if we land ON zero
			if currentValue == 0 {
				zeroCount++
			}
		}
	}
	fmt.Println(zeroCount)
}
