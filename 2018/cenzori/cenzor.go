package main

import (
	"fmt"
	"time"
)

func interval(ID []uint, posun int) {
	min := ID[0]
	maxID := ID[0]
	maxI := 0
	XOR := uint(0)
	for _, id := range ID {
		if id < min {
			min = id
		}
	}
	fmt.Printf("%v\n", min)
	for i, id := range ID {
		if id > maxID {
			maxID = id
			maxI = i
		}
	}
	fmt.Printf("%d\n", maxI+posun)
	for _, id := range ID {
		XOR ^= id
	}
	fmt.Printf("%d\n", XOR)
}

func main() {
	var T, N, Q, B, E uint
	var cenzor uint
	fmt.Scanf("%d", &T)
	for i := uint(0); i < T; i++ {
		var ID []uint
		fmt.Scanf("%d%d", &N, &Q)
		for ; N > 0; N-- {
			fmt.Scanf("%d", &cenzor)
			ID = append(ID, cenzor)
		}
		for ; Q > 0; Q-- {
			fmt.Scanf("%d%d", &B, &E)
			go interval(ID[B:E+1], int(B))
		}
	}
	time.Sleep(3 * time.Second)
}
