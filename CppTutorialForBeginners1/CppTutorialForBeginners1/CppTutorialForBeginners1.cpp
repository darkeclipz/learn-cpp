#include <iostream>
#include <vector>

class vector {
	int sz;
	double* elem;
public:
	vector(int s)
		:sz(s),
		elem(new double[s])
	{
		for (int i = 0; i < s; ++i) elem[i] = 0;
	}
	~vector()
	{
		delete[] elem;
	}
	int size() const { return sz; }
	double get(int n) const { return elem[n]; }
	void set(int n, double v) { elem[n] = v; }
};

struct Link {
	std::string value;
	Link* prev;
	Link* succ;
	Link(const std::string& v, Link* p, Link* s = 0)
		: value(v), prev(p), succ(s) { }
};

Link* insert(Link* p, Link* n) {
	n->succ = p;
	p->prev->succ = n;
	n->prev = p->prev;
	p->prev = n;
	return n;
}

// Replace all uppercase characters with lower case characters.
void to_lower(char* s)
{
	for (int i = 0; int c = s[i];) 
		s[i++] += (c >= 65 && c < 91) ? 32 : 0;
}

void print_ascii_table() {
	std::cout << "ASCII Table\n";
	for (int i = 0; i < 255; i++) {
		std::cout << i 
			<< " = " 
			<< char(i) 
			<< std::endl;
	}
}

char* cstr(char* s) {
	int n = 0;
	while (s[n++]);

	char* p = new char[n];

	for (int i = 0; i < n; i++) {
		p[i] = s[n - i]; 
	}

	return p;
}

void print_str(char* s) {
	for (int i = 0; s[i];) std::cout << s[i++];
	std::cout << std::endl;
}

int main()
{
	char hello[] = "Hello World!";
	char* rev_hello = cstr(hello);

	print_str(rev_hello);

	print_ascii_table();

	
	to_lower(hello);
	for (int i = 0; hello[i]; i++) {
		std::cout << hello[i];
	}
	std::cout << std::endl;

	int n = 1;
	std::vector<int> numbers(n);

	std::cout << "Enter 10 numbers:" << std::endl;

	for (int i = 0; i < n; i++)
		std::cin >> numbers[i];
	
	for (int x : numbers) 
		std::cout << x << std::endl;


	char ch = 'c';
	char* pc = &ch;

	int ii = 17;
	int* pi = &ii;

	std::cout << "pc=" << pc << " contents of pc=" << *pc << std::endl;
	std::cout << "pi=" << pi << " contents of pi " << *pi << std::endl;

	vector v = vector(5);
	for (int i = 0; i < v.size(); i++) {
		v.set(i, 1.1*i);
		std::cout << "v[" << i << "] = " << v.get(i) << "\n";
	}
	
	Link* norse_gods = new Link("Thor", 0, 0);


	return 0;
}
