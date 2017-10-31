#ifndef ternary_search_h
#define ternary_search_h

template <typename ArrayLike, typename T>
int ternary_search(const ArrayLike& array, const T& value, int low, int high) {
  int oneThird;
  int twoThird;
  while (low < high) {
    oneThird = (low + ((high - low)/3));
    twoThird = (low + 2*((high - low)/3));

    if (low == high)
      return -1;
    else if (value == array[oneThird]) {
      return oneThird;
    }
    else if (value < array[oneThird]) {
      high = oneThird;
    }
    else if (value == array[twoThird]) {
      return twoThird;
    }
    else if (value < array[twoThird]) {
      low = oneThird + 1;
      high = twoThird;
    }
    else { low = twoThird + 1; };
  }
  return -1;
}

#endif /* ternary_search_h */
