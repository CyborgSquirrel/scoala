class A {
public:
	A() { }
};

class B : public A {
public:
	B() : A() { }
};

int main() {
	B();
	return 0;
}
