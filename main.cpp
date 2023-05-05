#include <algorithm>  // included for std::swap
#include <iostream>
// #include <memory> // included for std::unique_ptr
#include <string>
#include <tuple>
#include <vector>

///
// ---- General utility functions ----
///

bool isOperation(const char c) { return (c == '+' || c == '='); }

int find(const std::string& k, const char c) {
  for (int index = 0; index < k.length(); index++) {
    if (k[index] == c) return index;
  }
  return -1;
}

template <typename T>
void output(std::vector<T> v) {
  for (auto& n : v) {
    std::cout << n << " ";
  }
  std::cout << "\n";
}

///
// ---- ---- ----
//

///
// ---- Equation handling class ----
///

class encryptedEqu {
 public:
  // --- constructor / destructor ---
  encryptedEqu(const std::string str) { origStr = str; }
  ~encryptedEqu() {}

  // --- setters ---
  void addImportant(const char c) { importantNums.push_back(c); }
  void addNum(const std::string str) { nums.push_back(str); }
  void addOp(const char c) { operations.push_back(c); }

  // --- getters ---
  std::vector<char> getImportant() { return importantNums; }
  std::vector<char> getNotImportant() { return notImportant; }
  std::string getKey() { return key; }
  std::vector<std::string> getNums() { return nums; }
  std::vector<char> getOps() { return operations; }

  bool isImportant(const char x) {
    for (int i = 0; i < importantNums.size(); i++) {
      if (importantNums[i] == x) return 1;
    }
    return 0;
  }

  void makeNotImportant() {
    for (int i = 0; i < 10; i++) {
      if (!isImportant(char(i + '0'))) {
        notImportant.push_back(char(i + '0'));
      }
    }
  }

  std::tuple<std::string, bool> tryKey(const std::string k) {
    std::string newStr;
    int numIndex{0};
    bool valid{0};
    std::vector<std::string> newNums{nums};

    for (std::string& num : newNums) {
      for (int i = 0; i < num.length(); i++) {
        num[i] = (char(find(k, num[i]) + '0'));
      }
    }
    for (char& c : operations) {
      if (c == 'n') {
        newStr.append(newNums[numIndex]);
        numIndex++;
      } else {
        newStr.push_back(c);
      }
    }

    if (std::atoi(newNums[0].c_str()) + std::atoi(newNums[1].c_str()) ==
        std::atoi(newNums[2].c_str())) {
      valid = true;  // return valid if A + B = C
    }
    return std::make_tuple(newStr, valid);
  }

 private:
  std::string origStr;
  std::string key;
  std::vector<char> importantNums;
  std::vector<char> notImportant;
  // importantNums stores numbers in the key that have important positions
  std::vector<std::string> nums;
  std::vector<char> operations;
};

// --- other ---

std::string keyCrack(/*std::string& s ,*/ encryptedEqu& eq) {
  std::string s;

  for (int i = 0; i < 10; i++) {
    if (i < eq.getImportant().size()) {
      s.push_back(eq.getImportant().at(i));
    } else {
      s.push_back('-');
    }
  }

  // std::cout << s << "\n";
  std::sort(s.begin(), s.end());
  do {
    std::tuple<std::string, bool> res = eq.tryKey(s);
    if (std::get<1>(res)) {
      std::cout << std::get<0>(res) << "\n";
      break;
    }
  } while (std::next_permutation(s.begin(), s.end()));
  for (int i = 0, j = 0; i < 9; i++) {
    if (s[i] == '-') {
      s[i] = eq.getNotImportant().at(j);
      j++;
    }
  }
  return s;
}

///
// --- --- ---
///



int main() {
  std::string equStr;
  std::getline(std::cin, equStr);
  encryptedEqu eq(equStr);

  // equation number splitter
  std::string tempNum;
  for (int i = 0; i < equStr.length(); i++) {
    if (!isOperation(equStr[i])) {  // build numbers into strings
      tempNum.push_back(equStr[i]);
      if (!eq.isImportant(
              equStr[i])) {  // if number is unique add to important vector
        eq.addImportant(equStr[i]);
      }
    }

    if (i + 1 == equStr.length() ||
        isOperation(equStr[i])) {  // if at the end of number or equation push
                                   // number to class number vector
      eq.addNum(tempNum);
      eq.addOp('n');  // add number stand-in to operation vector
      tempNum.clear();
    }

    if (isOperation(
            equStr[i])) {  // if char is an operation add to operation vector
      eq.addOp(equStr[i]);
    }
  }
  eq.makeNotImportant();
  // ---

  std::cout << keyCrack(eq) << "\n";
  //

  return 0;
}

///
//
// an output of '2371904856' means that
// 2371904856 corresponds with:
// 0123456789
//
// in the equation
// 12+30=90
// 30+15=45
//
// if you think of the two numbers as arrays
// a = 2,3,7,1,9,0,4,8,5,6
// b = 0,1,2,3,4,5,6,7,8,9
//
// b[n] = n
// and
// a[n] becomes b[n]
//
// if x = 0 and a[5] = 0 then x would translate to 5 (b[5])
//
// 12 would translate to 30 because 1 = a[3] and 2 = a[0]
// 30 would translate to 15 because 3 = a[1] and 0 = a[5]
// 90 would translate to 45 because 9 = a[4] and 0 = a[5]
//
//
// in the key '2371904856'
//
// 2013495678
// 0123456789
//
// 12+30=90
// 20+31=51
///
// 2---13--09
// 0123456789
// 12+30=90
// 40+58=98
//
//
// 3567248910
// 0123456789
// 12+4=10
// 84+5=89


//
// 2456137809
// 0123456789
// 12+30=90
// 40+58=98
