package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

func getAccessibleRolls(rolls *[][]bool, limit int) int {
	accessableCount := 0
	adjacents := make([][]int, len(*rolls))
	for i := range adjacents {
		adjacents[i] = make([]int, len((*rolls)[i]))
	}

	for i := 1; i < len(*rolls)-1; i++ {
		for j := 1; j < len((*rolls)[i])-1; j++ {
			if !(*rolls)[i][j] {
				continue
			}

			adjacents[i-1][j-1]++
			adjacents[i-1][j]++
			adjacents[i-1][j+1]++
			adjacents[i][j-1]++
			adjacents[i][j+1]++
			adjacents[i+1][j-1]++
			adjacents[i+1][j]++
			adjacents[i+1][j+1]++

		}
	}

	for i := 1; i < len(*rolls)-1; i++ {
		for j := 1; j < len((*rolls)[i])-1; j++ {
			if (*rolls)[i][j] && adjacents[i][j] < limit {
				accessableCount++
				(*rolls)[i][j] = false
			}
		}
	}

	return accessableCount
}

func main() {
	sum1, sum2 := 0, 0
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	var rolls [][]bool
	rolls = append(rolls, []bool{})
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		var row []bool
		row = append(row, false)
		for _, ch := range line {
			if ch == '@' {
				row = append(row, true)
			} else {
				row = append(row, false)
			}
		}
		row = append(row, false)
		rolls = append(rolls, row)
	}
	rolls[0] = make([]bool, len(rolls[1]))
	rolls = append(rolls, make([]bool, len(rolls[1])))
	sum1 = getAccessibleRolls(&rolls, 4)
	sum2 = sum1
	for {
		result := getAccessibleRolls(&rolls, 4)
		if result == 0 {
			break
		}
		sum2 += result
	}
	fmt.Println(int(sum1))
	fmt.Println(int(sum2))
}
