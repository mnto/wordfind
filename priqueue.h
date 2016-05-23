/* */
#include<iostream>

using namespace std;

class priqueue {
public:
	typedef string element;
	priqueue(int (*pri)(const element &));
	void add(const element &);
	void remove();
	size_t size();
	element front();
	
private:
	struct node {
		element data;
		node *next;
		node(const element &, node *);
	};
	int (*pri)(const element &);  // pointer to priority function
	size_t _size;
	node * _front;
	void _add_helper(const element &, node * &);
};