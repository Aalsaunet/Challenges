package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func getInvalidProductNumberPart1(num string) int {
	if len(num)%2 != 0 {
		return 0
	}

	first := num[0 : len(num)/2]
	last := num[len(num)/2:]

	if first == last {
		n, _ := strconv.Atoi(num)
		return n
	}
	return 0
}

func getInvalidProductNumberPart2(num string) int {
	len := len(num)

	for sublen := len / 2; sublen > 0; sublen-- {
		if len%sublen != 0 {
			continue
		}

		pattern := num[:sublen]
		repeats := len / sublen
		if strings.Repeat(pattern, repeats) == num {
			n, _ := strconv.Atoi(num)
			return n
		}
	}

	return 0
}

func main() {
	data, err := os.ReadFile("input.txt")
	if err != nil {
		fmt.Println("Error reading from file: ", err)
	}

	sum1 := 0
	sum2 := 0

	for _, v := range strings.Split(string(data), ",") {
		startstop := strings.Split(v, "-")
		start, _ := strconv.Atoi(startstop[0])
		stop, _ := strconv.Atoi(startstop[1])
		allNums := make([]string, 1, (stop-start)+1)
		allNums[0] = startstop[0]
		for num := start + 1; num <= stop; num++ {
			allNums = append(allNums, strconv.Itoa(num))
		}

		for _, num := range allNums {
			sum1 += getInvalidProductNumberPart1(num)
			sum2 += getInvalidProductNumberPart2(num)
		}
	}

	fmt.Println("Result for part 1:", sum1)
	fmt.Println("Result for part 2:", sum2)
}
