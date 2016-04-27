#include <iostream>
using namespace std;

class Complexe
{
public:
	Complexe(int a=0,int b=0): a(a),b(b) {}
	int a;
	int b;
	string c = to_string(a) + " " + to_string(b);
};

const Complexe operator+(Complexe aa, Complexe const& bb){
	return Complexe(aa.a+bb.a,aa.b+bb.b);
};



int main(){
	Complexe a = Complexe(1,2);
	Complexe b = Complexe(1,2);
	Complexe c = Complexe(1,2);
	c = a + b;
	c = a;
	string d;
	cout << d << "hi";
	return 0;
}
