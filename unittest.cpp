#include <gtest/gtest.h>
#include <algorithm>
#include <random>
#include <string>

using namespace std;

extern int sum();

/* TEST 1 */
TEST(Sum, Test1) {
    EXPECT_EQ(sum(), 15);
}

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

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}