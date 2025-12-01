package main

// import (
// 	"bufio"
// 	"fmt"
// 	"os"
// 	"strconv"
// )

// const RoundTurnValue = 100

// var currentValue = 50
// var zeroCount = 0

// func main2() {
// 	file, err := os.Open("input.txt")
// 	if err != nil {
// 		fmt.Println("Error opening file:", err)
// 		return
// 	}
// 	defer file.Close()

// 	scanner := bufio.NewScanner(file)
// 	if err := scanner.Err(); err != nil {
// 		fmt.Println("Error reading file:", err)
// 	}

// 	for scanner.Scan() {
// 		line := scanner.Text()
// 		dir := line[0] // First character is the direction
// 		if dir != 'L' && dir != 'R' {
// 			fmt.Println("Invalid character in line:", dir)
// 			return
// 		}

// 		dist, err := strconv.Atoi(line[1:]) // The rest of the string is the number -> parse to int
// 		if err != nil {
// 			fmt.Println("Invalid number in line:", line)
// 			continue
// 		}

// 		diff := dist % RoundTurnValue
// 		if dir == 'L' {
// 			diff *= -1
// 		} else {
// 			diff *= 1
// 		}

// 		currentValue = (currentValue + diff) % RoundTurnValue
// 		if currentValue == 0 {
// 			zeroCount++
// 		}
// 	}
// 	fmt.Println(zeroCount)
// }
