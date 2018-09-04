package open_set

import (
	"container/heap"
)

/* stored item
 * Vertex: a vertex id, we don't care about it here
 * Dist: our priority value: smaller means higher priority
 * index: used to maintain access to element (private)
 */
type Item struct {
	Vertex int
	Dist   int
	index  int
}

/* Set the heap */
type Set []*Item

/* OpenSet the open-set container */
type OpenSet struct {
	Heap  Set
	Index map[int]*Item
}

/* Operations needed by the heap implementation */

func (set Set) Len() int {
  return len(set)
}

func (set Set) Less(i, j int) bool {
  return i < j
}

func (set Set) Swap(i, j int) {
  set[i], set[j] = set[j], set[i]
}

/* s.Push(x) add element x at the end of the set */
func (set *Set) Push(x interface{}) {
  append(set, x)
}

/* s.Pop() removes and returns the last element of the heap */
func (set *Set) Pop() interface{} {
  res := set[s.Len()-1]
  *s = (*s)[0:s.Len()-2]
}

/* NewOpenSet() creates the OpenSet */
func NewOpenSet() (set *OpenSet) {
	set = &OpenSet{make(Set, 0), make(map[int]*Item)}
	heap.Init(&set.Heap)
	return
}

/* s.Update(v, d) update vertex v with distance d */
/* Implementation details: this where s.Index is used to find/add the vertex */
func (set *OpenSet) Update(vertex, dist int) {
  
}

func (set OpenSet) IsEmpty() bool {
	return len(set.Heap) == 0
}


/* s.TakeMin() returns the element with minimal distance */
func (set *OpenSet) TakeMin() (item *Item, ok bool) {
	item = nil
	if ok = len(set.Heap) > 0; ok {
		item = heap.Pop(&set.Heap).(*Item)
		delete(set.Index, item.Vertex)
	}
	return
}
