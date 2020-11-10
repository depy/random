package main

import (
	"fmt"
)

type Node struct {
	Value int
	Next  *Node
}

type SingleLinkedList struct {
	Start *Node
	End   *Node
}

func (sll *SingleLinkedList) AddToHead(n Node) {
	if sll.Start == nil && sll.End == nil {
		sll.Start = &n
		sll.End = &n
	} else if sll.Start != nil && sll.End != nil {
		n.Next = sll.Start
		sll.Start = &n
	} else {
		panic(fmt.Sprintf("SingleLinkedList is fubar!"))
	}
}

func (sll *SingleLinkedList) RemoveFromHead() {
	if sll.Start.Next != nil {
		sll.Start = sll.Start.Next
	} else {
		sll.Start = nil
	}
}


func (sll SingleLinkedList) Print() {
	n := sll.Start

	for {
		if n == nil {
			fmt.Print("The list is empty")
			return
		}
		
		fmt.Print(n.Value)
		n = n.Next

		if n == nil {
			break
		} else {
			fmt.Print(" -> ")
		}
	}
}

func main() {
	sll := SingleLinkedList{}
	sll.AddToHead(Node{3, nil})
	sll.AddToHead(Node{2, nil})
	sll.AddToHead(Node{1, nil})
	sll.AddToHead(Node{0, nil})
	
	sll.RemoveFromHead()

	sll.Print()
}
