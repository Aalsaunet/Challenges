package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
)

func getJoltage(bank []float64, count float64) float64 {
	if count == 0 {
		return 0
	}
	indexOfMax := 0
	for i := 1; i <= len(bank)-int(count); i++ {
		if bank[i] > bank[indexOfMax] {
			indexOfMax = i
		}
	}
	return bank[indexOfMax]*math.Pow(10, count-1) + getJoltage(bank[indexOfMax+1:], count-1)
}

func main() {
	sum1, sum2 := 0.0, 0.0
	file, _ := os.Open("input.txt")
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		bank := make([]float64, len(line))
		for i, ch := range line {
			bank[i] = float64(ch - '0')
		}
		sum1 += getJoltage(bank, 2)
		sum2 += getJoltage(bank, 12)
	}

	fmt.Println(int(sum1))
	fmt.Println(int(sum2))
}
