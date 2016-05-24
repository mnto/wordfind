#include <iostream>
#include "priqueue.h"

using namespace std;


int mypri(const string & item)
{
	string vowels = "aeiouy";
	int sum = 0;
	for (size_t i = 0; i < item.size(); i++) {
		if (vowels.find(item[i]) != string::npos)
			sum++;
	}
	return sum;
}

int main()
{
	priqueue q(mypri);
	q.add("onomatapiay");
	q.add("hi");
	q.add("banana");
	q.add("ho");
	while (q.size() != 0) {
		cout << q.front() << endl;
		q.remove();
	}

}
