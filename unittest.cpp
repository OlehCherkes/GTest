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
	vs.push_back( "Oleh");
	vs.push_back( "Cherkes");
	vs.push_back( "Anatolievich");

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
    int *p = new int(33);
    std::cout << *p << std::endl;
    delete p; 
}

/*  Dynamic Array */
TEST(DynamicArray, Test8)
{
    int *p = new int [5];
    p[0] = 7;
    std::cout << p[0] << std::endl;
    delete [] p;
}

/*  unique_ptr  */
TEST(Unique_ptr, Test8)
{
    unique_ptr<int> p1(new int(25));
    int *p2 = p1.get(); // get raw ptr
    std::cout << *p1 <<std::endl;
    std::cout << *p2 <<std::endl;

    *p1 = 30;
    std::cout << *p1 <<std::endl;
    std::cout << *p2 <<std::endl;

    p1.reset(); // free memory
    if (p1 == nullptr)
        std::cout << "p1 == nullptr" << std::endl;
    else
        std::cout << "p1 != nullptr" << std::endl;

    unique_ptr<int> p3(new int(100));   //  Transfer rights
    int *p4 = p3.release();
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
    int *myArray = new int[size];
    
    for (int i = 0; i < size; ++i) {
        myArray[i] = i * 2;

        std::cout << myArray[i] << std::endl;
    }

    delete[] myArray;
}

TEST(Array_pointers, Test12)
{
    int size = 3;
    int **myArray = new int *[size];
   
    for (int i = 0; i < size; ++i) {
        myArray[i] = new int;
        *(myArray[i]) = i * 10;

        std::cout << *(myArray[i]) << std::endl;
    }

    for (int i = 0; i < size; ++i) {
        delete myArray[i];
    }
    delete [] myArray;
}

#endif

TEST(SOO, Test15)
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
    Point *p2 = new Point;

    std::cout << "Point on stack: ";
    p1.print();

    std::cout << "Point on heap: ";
    p2->print();

    delete p2;
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

TEST(Default, Test16)
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

TEST(Copy_constructor, Test17)
{
    myClass b;
    proc(b);

    myClass c(b);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
