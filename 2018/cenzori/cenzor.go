package main

import (
	"fmt"
)

func interval(ID []uint, posun int, task chan uint) {
	min := ID[0]
	maxID := ID[0]
	maxI := 0
	XOR := uint(0)
	for _, id := range ID {
		if id < min {
			min = id
		}
	}
	//fmt.Printf("%v\n", min)
	task <- min
	for i, id := range ID {
		if id > maxID {
			maxID = id
			maxI = i
		}
	}
	//fmt.Printf("%d\n", maxI+posun)
	task <- uint(maxI + posun)
	for _, id := range ID {
		XOR ^= id
	}
	//fmt.Printf("%d\n", XOR)
	task <- XOR
}

func main() {
	var T, N, Q, B, E uint
	var cenzor uint
	var tasks []chan uint

	fmt.Scanf("%d", &T)
	for i := uint(0); i < T; i++ {
		var ID []uint
		fmt.Scanf("%d%d", &N, &Q)
		for j := uint(0); j < Q; j++ {
			tasks = append(tasks, make(chan uint, 3))
		}
		for ; N > 0; N-- {
			fmt.Scanf("%d", &cenzor)
			ID = append(ID, cenzor)
		}
		for j := uint(0); j < Q; j++ {
			fmt.Scanf("%d%d", &B, &E)
			//interval(ID[B:E+1], int(B))
			go interval(ID[B:E+1], int(B), tasks[j])
		}
		for j := uint(0); j < Q; j++ {
			for k := 0; k < 3; k++ {
				fmt.Printf("%d\n", <-tasks[j])
			}
		}
	}
}
