// integer bianry search
bool check(int x) {/* ... */} // 检查x是否满足某种性质

// 区间[l, r]被划分成[l, mid]和[mid + 1, r]时使用：
int bsearch_1(int l, int r) {
  while (l < r) {
    int mid = l + r >> 1;
    if (check(mid)) {
      // check()判断mid是否满足性质
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return l;
}
// 区间[l, r]被划分成[l, mid - 1]和[mid, r]时使用：
int bsearch_2(int l, int r) {
  while (l < r) {
    int mid = l + r + 1 >> 1;
    if (check(mid)) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  return l;
}

// double binary search
bool check(double x) {/* ... */} // 检查x是否满足某种性质

double bsearch_3(double l, double r) {
  // eps 表示精度，取决于题目对精度的要求
  // 一般让 eps 比题目的要求精度高两位
  const double eps = 1e-6;
  while (r - l > eps) {
    double mid = (l + r) / 2;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid;
    }
  }
  return l;
}

// we can simply do this:
for (int it = 0; it < 100; it++) {
  double mid = (l + r) / 2;
  if (check(mid)) {

  } else {

  }
}
