// ordered_set: a simple generic set implementation
package ordered_set

/*
OrderedType interface: describes comparable value

Comparable value provides:
  x.Less(y) returns true if x < y
  x.Equals(y) returns true if x == y
*/
type OrderedType interface {
	Less(OrderedType) bool
	Equals(OrderedType) bool
}

// uniq_merge(s1, s2) returns a merge of sorted list s1 and s2 without doublon
func uniq_merge(s1, s2 []OrderedType) (r []OrderedType) {
	r = make([]OrderedType, len(s1) + len(s2))
  pos1 := 0
  pos2 := 0
  for pos1 < len(s1) && pos2 < len(s2) {
    if s1[pos1].Equals(s2[pos2]) {
      r[pos1 + pos2] = s1[pos1]
      pos1 += 1
      pos2 += 1
    } else if s1[pos1].Less(s2[pos2]) {
      r[pos1 + pos2] = s1[pos1]
      pos1 += 1
    } else {
      r[pos1 + pos2] = s2[pos2]
      pos2 += 1
    }
  }
  return
}

// Set: an ordered set of OrderedType elements
type Set []OrderedType

// NewSet() creates a new empty set
func NewSet() *Set {
        s := Set(make([]OrderedType, 0))
        return &s
}

// s.bfind(x) returns expected position of x
// if x is not present, returns position of first element not smaller than x
func (s *Set) bfind(x OrderedType) (pos int) {
	pos = 0
	for pos < len(*s) && (*s)[pos].Less(x) {
		pos += 1
	}
	return
}

// s.Mem(x) returns true if x is in the set
func (s *Set) Mem(x OrderedType) bool {
	p := s.bfind(x)
	return p < len(*s) && x.Equals((*s)[p])
}

// s.Add(x) add x to set s, returns true if x wasn't there, false otherwise
func (s *Set) Add(x OrderedType) bool {
	if s.Mem(x) {
		return false
	}
	// Shift all cells from position p to the end by 1 cell to the right
	p := s.bfind(x)
	*s = append(*s, nil)                // add an empty cell at the end
	copy((*s)[p+1:], (*s)[p:len(*s)-1]) // shift element with copy
	(*s)[p] = x
	return true
}

// s.Remove(x) removes x from s
// returns true if x was in the set, false otherwise
func (s *Set) Remove(x OrderedType) bool {
	if !s.Mem(x) {
		return false
	}
	p := s.bfind(x)
    s1 := (*s)[0:p]
    s2 := (*s)[p+1:len(*s) - 1]
	*s = append(s1, s2...) //TODO : Fix this because Set doesn't implement Equals()
	return true
}

// s.Union(s2) adds elements from s2 to s
func (s *Set) Union(s2 *Set) {
	*s = uniq_merge(*s, *s2)
}

// s.Difference(s2) removes all elements of s2 from s
func (s *Set) Difference(s2 *Set) {
	for i := 0; i < len((*s2)); i++ {
		s.Remove((*s2)[i])
	}
}
