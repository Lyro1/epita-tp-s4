package merge_sort

func Merge(a, b []int) (l []int) {
  l = make([]int, len(a) + len(b))
  posa := 0
  posb := 0
  for posa < len(a) && posb < len(b) {
    if a[posa] < b[posb] {
      l[posa + posb] = a[posa]
      posa += 1
    } else {
      l[posa + posb] = b[posb]
      posb += 1
    }
  }
  for posa < len(a) {
    l[posa + posb] = a[posa]
    posa += 1
  }
  for posb < len(b) {
    l[posa + posb] = b[posb]
    posb += 1
  }
  return l
}

func MergeSort(l []int) []int {
  if len(l) < 2 {
    return l
  }
  a := MergeSort(l[0:len(l)/2])
  b := MergeSort(l[len(l)/2:len(l)])
  return Merge(a, b)
}
