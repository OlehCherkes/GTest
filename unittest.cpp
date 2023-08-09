//#include "pch.h"
#include <gtest/gtest.h>
#include <algorithm>
#include <random>
#include <string>
#include <bitset>
#include <vector>
#include <future>
#include <thread>
//#include "soo.h"

using namespace std;
#if 0
extern int sum();

/* TEST 1 */
// TEST(Sum, Test1) {
//     EXPECT_EQ(sum(), 15);
// } 

/* TEST 2 */
TEST(ConstructorTest, Test2) {

  class MyClass {
  public:
    int count;
    MyClass()
    {
      count++;
      cout << "Created\n";
    }

    ~MyClass()
    {
      count--;
      cout << "Destroyed\n";
    }
  };

  MyClass obj;
}

/* TEST 3 */
TEST(StringTest, Test3) {
  string s1 = "Oleh";
  string s2 = "Cherkes";
  EXPECT_EQ(s1, s2);
  cout << s1 + ' ' + s2 + ' ' + "Anatolievich\n";
}

/* TEST 4 */
TEST(VectorTest, Test4) {
  vector<string> vs;
  vs.push_back("Oleh");
  vs.push_back("Cherkes");
  vs.push_back("Anatolievich");

  sort(vs.begin(), vs.end(), greater<>());
  for (string value : vs) {
    cout << value << ' ';
  }
  cout << '\n';

  reverse(vs.begin(), vs.end());
  for (string value : vs) {
    cout << value << ' ';
  }
  cout << '\n';

  //auto rng = default_random_engine{};   //  random generator
  random_device rd;
  mt19937 rng(rd());
  shuffle(vs.begin(), vs.end(), rng);
  for (string value : vs) {
    cout << value << ' ';
  }
  cout << '\n';

  string target = "Oleh";
  bool found = binary_search(vs.begin(), vs.end(), target);
  ASSERT_TRUE(found);
}

/* TEST 5 */
TEST(ReturnTest, Test5) {
  using T = vector<uint8_t>;

  unique_ptr<T> d = make_unique<T>(100);
  (*d)[100] = 123;
  auto g = 123 == d->back();
}

/*--------------------------------------------------*/
/*  Set/Get */
TEST(GetSetTest, Test6) {
  class TPoint {
    int y;
  public:
    int x;
    void SetY(int y1) {
      y = y1;
    }

    int GetY() {
      return y;
    }
  };

  TPoint obj;
  obj.x = 3;
  obj.SetY(10);
  std::cout << obj.x << std::endl;
  std::cout << obj.GetY() << std::endl;
}

/*  New и Delete */
// new and delete call the constructor constructor
TEST(DynamicMemory, Test7)
{
  int* p = new int(33);
  std::cout << *p << std::endl;
  delete p;
}

/*  Dynamic Array */
TEST(DynamicArray, Test8)
{
  int* p = new int[5];
  p[0] = 7;
  std::cout << p[0] << std::endl;
  delete[] p;
}

/*  unique_ptr  */
TEST(Unique_ptr, Test8)
{
  unique_ptr<int> p1(new int(25));
  int* p2 = p1.get(); // get raw ptr
  std::cout << *p1 << std::endl;
  std::cout << *p2 << std::endl;

  *p1 = 30;
  std::cout << *p1 << std::endl;
  std::cout << *p2 << std::endl;

  p1.reset(); // free memory
  if (p1 == nullptr)
    std::cout << "p1 == nullptr" << std::endl;
  else
    std::cout << "p1 != nullptr" << std::endl;

  unique_ptr<int> p3(new int(100));   //  Transfer rights
  int* p4 = p3.release();
  std::cout << *p4 << std::endl;

  if (p3 == nullptr)
    std::cout << "p3 == nullptr" << std::endl;
  else
    std::cout << "p3 != nullptr" << std::endl;

  //  move
  unique_ptr<int> p5(new int(50));
  unique_ptr<int> p6 = std::move(p5);

  if (p5 == nullptr)
    std::cout << "p5 == nullptr" << std::endl;
  else
    std::cout << "p5 != nullptr" << std::endl;
}

/*  shared_ptr  */
TEST(Shared_ptr, Test9)
{
  shared_ptr<float> pF1(new float(2.8f));
  shared_ptr<float> pF2(new float(7.55f));

  shared_ptr<float> pF3 = pF1;

  std::cout << "pF1 => " << *pF1 << std::endl;
  std::cout << "pF2 => " << *pF2 << std::endl;
  std::cout << "pF3 => " << *pF3 << std::endl;

  pF2 = pF3;

  std::cout << "pF1 => " << *pF1 << std::endl;
  std::cout << "pF2 => " << *pF2 << std::endl;
  std::cout << "pF3 => " << *pF3 << std::endl;

  //  swap
  shared_ptr<int> p1(new int(33));
  shared_ptr<int> p2(new int(77));

  p1.swap(p2);
  std::cout << *p1 << std::endl;
  std::cout << *p1 << std::endl;

  // get
  int* pI = p1.get();
  cout << *pI << std::endl;
  cout << *p1 << std::endl;

  //  reset
  p2.reset();
  if (p2 == nullptr)
    std::cout << "p2 == nullptr" << std::endl;
  else
    std::cout << "p2 != nullptr" << std::endl;

  // count shared_ptr
  std::cout << p1.use_count() << std::endl;
}

/*  weak_ptr  */
TEST(Weak_ptr, Test10)
{
  shared_ptr<int> pShared1(new int(25));
  weak_ptr<int> pWeak = pShared1;
  //  getting the number of copies of the pointers that point to the data
  std::cout << "pWeak.use_count() = " << pWeak.use_count() << std::endl;  // 1

  //weak_ptr -> shared_ptr
  shared_ptr<int> pShared2 = pWeak.lock();
  std::cout << "pWeak.use_count() = " << pWeak.use_count() << std::endl; // 2

  std::cout << "*pShared2 = " << *pShared2 << std::endl;
  // std::cout << *pWeak << std::endl;  // eeror

  //  swap
  weak_ptr<int> pw1;
  weak_ptr<int> pw2;
  shared_ptr<int> ps1(new int(38));
  shared_ptr<int> ps2(new int(55));
  pw1 = ps1; // pw1 => 38
  pw2 = ps2; // pw2 => 55

  pw1.swap(pw2);

  std::cout << "pw1 => " << *pw1.lock().get() << std::endl; // pw1 => 55
  std::cout << "pw2 => " << *pw2.lock().get() << std::endl; // pw2 => 38
}

TEST(Array_pointer, Test11)
{
  int size = 5;
  int* myArray = new int[size];

  for (int i = 0; i < size; ++i) {
    myArray[i] = i * 2;

    std::cout << myArray[i] << std::endl;
  }

  delete[] myArray;
}

TEST(Array_pointers, Test12)
{
  int size = 3;
  int** myArray = new int* [size];

  for (int i = 0; i < size; ++i) {
    myArray[i] = new int;
    *(myArray[i]) = i * 10;

    std::cout << *(myArray[i]) << std::endl;
  }

  for (int i = 0; i < size; ++i) {
    delete myArray[i];
  }
  delete[] myArray;
}

TEST(Vector, Test13)
{
  std::vector<int> numbers = { 10, 8, 6, 4, 2, 1 };
  numbers[5] = 7;
  numbers.at(8) = 4;      // with range check
  numbers.push_back(10);  // add new element
  numbers.size();         // return size of vector
  numbers.capacity();     // capacity of vector
  numbers.resize(10);     // resize vector
  //numbers.reserve(128);   // reserve vector for 128 elements
  //numbers.clear();        // clear vector

  std::sort(numbers.begin(), numbers.end());                      // sort 0 - ~
  std::sort(numbers.begin(), numbers.end(), std::greater<int>()); // sort ~ - 0
  std::reverse(numbers.begin(), numbers.end());                   // reverse vector

  // shuffle vector elements
  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(numbers.begin(), numbers.end(), gen);

  // binary search
  int target = 8;
  bool found = binary_search(numbers.begin(), numbers.end(), target); // must be sorted

  std::cout << "VECTOR: " << numbers[2] << std::endl;
}

TEST(Bitset, Test14)
{
  unsigned int number = 123;

  //  binary view
  std::bitset<8> binary(number);
  std::cout << "DEC: " << number << ", BIN: " << binary << std::endl;

  binary.set(0);      // first bit = 1
  binary.set(2, 1);   // 2 bit = 1
  binary.set(4);      // 4 bit = 1
  binary.flip(0);     // invert bit
  binary.size();      // size of binary
  binary.test(4);     // return true if 5 bit == 1
  binary.count();     // return count of 1
  binary.any();       // return true if even though 1 bit is set
  binary.to_string(); // binary to string
  binary.reset();     // reset bit in 0 or full binary

  std::cout << "BIN: " << binary << std::endl;
}


TEST(Reverse_iterator, Test15)
{
  std::vector<int> numbers = { 1, 2, 3, 4, 5 };
  std::vector<int>::reverse_iterator rit;

  for (rit = numbers.rbegin(); rit != numbers.rend(); ++rit) {
    std::cout << *rit << " ";
  }

  std::cout << std::endl;
}


//----------------  std::future --------------------------//
int addNumbers(int a, int b)
{
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return a + b;
}

TEST(Future, Test16)
{
  std::future<int> result = std::async(addNumbers, 5, 10);

  std::cout << result.valid() << std::endl;       // checks if an object is valid
  // std::cout << result.wait_for() << std::endl; // allows you to wait for a result 

  int sum = result.get();
  std::cout << "Sum: " << sum << std::endl;
}
#endif

TEST(Сopy_constructor, Test17)
{
  class MyClass {
  private:
    int value;
    std::string text;

  public:

    // default constructor
    MyClass() : value(0), text("Oleh") {}

    // Constructor with parameters
    MyClass(int val, const std::string& txt) : value(val), text(txt) {}

    // copy constructor
    explicit MyClass(const MyClass& other) : value(other.value), text(other.text) {}


    void display() const {
      std::cout << "Value: " << value << ", Text: " << text << std::endl;
    }

    void set(int val) {
      value = val;
    }

    int GetY() {
      return value;
    }
  };

  MyClass obj1;
  MyClass obj2(obj1);

  obj2.set(10);

  obj1.display();
  obj2.display();
}


void printValues(std::initializer_list<int> values) {
  std::cout << "Values: ";
  for (int value : values) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}

TEST(Initializer_list, Test18)
{
  printValues({ 10, 20, 30 });

  class MyClass {
  public:
    MyClass(std::initializer_list<int> values) {
      std::cout << "MyClass Constructor Called with Values: ";
      for (int value : values) {
        std::cout << value << " ";
      }
      std::cout << std::endl;
    }
  };

  MyClass obj1 = { 100, 200, 300 };
}

TEST(Operator, Test19)
{
  class MyClass {
  private:
    int value;
    std::string text;

  public:
    MyClass() : value(0), text("") {}

    MyClass(int val, const std::string& txt) : value(val), text(txt) {}

    MyClass& operator=(const MyClass& other) {
      if (this == &other) {
        return *this;
      }

      this->value = other.value;
      this->text = other.text;

      return *this;
    }

    void display() const {
      std::cout << "Value: " << value << ", Text: " << text << std::endl;
    }
  };

  MyClass obj1(42, "Hello");
  MyClass obj2;

  obj2 = obj1;

  std::cout << "Object 1: ";
  obj1.display();

  std::cout << "Object 2: ";
  obj2.display();
}

TEST(Auto, Test20)
{
  //auto sum(int a, int b) -> int;

  //auto sum(int a, int b) -> int;
  //{
  //  return a + b;
  //}
}

// type of value
TEST(Decltype, Test21)
{
  double a = 5.0;
  decltype(a) result;
  std::cout << "result: " << typeid(result).name() << std::endl;
}

TEST(SOO, Test22)
{
  class Point {
  private:
    float x, y;

    // if isOnStack = true, then the data is stored on the stack, otherwise on the heap
    bool isOnStack;

  public:
    // Constructor for a point on the stack
    Point(float x, float y) : x(x), y(y), isOnStack(true) {}

    // Constructor for point on the heap
    Point() : x(0), y(0), isOnStack(false) {}

    void print() {
      std::cout << "X: " << x << ", Y: " << y << " isOnStack: " << isOnStack << std::endl;
    }
  };

  // Create a pointer on the stack
  Point p1(1.5f, 2.5f);

  // Create a point on the heap (common memory allocation)
  Point* p2 = new Point;

  std::cout << "Point on stack: ";
  p1.print();

  std::cout << "Point on heap: ";
  p2->print();

  delete p2;
}

TEST(Constexpr, Test23)
{
  constexpr unsigned char b = 0x80;
  std::cout << "Value of b: " << static_cast<int>(b) << std::endl;
}

//--------------------------- POW --------------------//
int pow(int base, int exp)
{
  int result = 1;
  while (exp)
  {
    if (exp & 1)
      result *= base;
    exp >>= 1;
    base *= base;
  }

  return result;
}

TEST(Pow, Test24)
{
  uint32_t res = pow(3,7);
  std::cout << "POW: " << res << std::endl;
}

//----------- default setting / function overload ----------/
void def(int a = 5, char b = '@')
{
    std::cout << a << ' '<< b << std::endl;
}

void over()
{
    std::cout << "First" << std::endl;
}

void over(int a)
{
    std::cout << "Second " << a << std::endl;
}

TEST(Default, Test25)
{
    def(2);
    over();
}

//---------- constructor of copy ------------/
class myClass 
{
    public:
    myClass()
    {
        std::cout << "default constructor" << std::endl;
    }

    myClass(const myClass &p)
    {
        std::cout << "constructor of copy" << std::endl;
    }
};

void proc(myClass x)
{
    std::cout << "proc" << std::endl;
}

TEST(Copy_constructor, Test26)
{
    myClass b;
    proc(b);

    myClass c(b);
}

//------------- operator overload -------/
struct TPoint
{
  int x;
  int y;

  // TPoint operator- () { TPOint tmp = {-x, -y}; return *this; };
  // TPoint& operator++ () { ++x; ++y; return *this; };

  TPoint& operator= (int i) { x = y = i; return *this; }
};

TPoint operator- (TPoint pnt) { pnt.x = -pnt.x; pnt.y = -pnt.y; return pnt; };
TPoint& operator++ (TPoint &pnt) { ++pnt.x; ++pnt.y; return pnt; }

TPoint operator+ (TPoint pnt, int i) { TPoint tmp {pnt.x + i, pnt.y + i}; return tmp; }
TPoint operator+ (int i, TPoint pnt) { return pnt + i; };

TEST(Operator_overload, Test27)
{
  TPoint p = {4, 5};
  p = -p;
  ++p;
  std::cout << p.x << std::endl;
  std::cout << p.y << std::endl;
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}