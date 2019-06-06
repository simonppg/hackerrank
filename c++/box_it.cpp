#include<bits/stdc++.h>

using namespace std;

class Box {
	private:
		int l, b, h;
	public:
		Box();
		Box(int l, int b, int h);
		Box(const Box&);
		int getLength();
		int getBreadth();
		int getHeight();
		long long CalculateVolume();
		friend ostream& operator<< (ostream& output, const Box& B);

		bool operator < (Box const &B)
		{
			if (l < B.l)
				return true;

			if (b < B.b && l == B.l)
				return true;

			if (h < B.h && l == B.l && b == B.b)
				return true;

			return false;
		}
};

Box::Box() {
	l = 0;
	b = 0;
	h = 0;
}

Box::Box(int l, int b, int h) {
	this->l = l;
	this->b = b;
	this->h = h;
}

Box::Box(const Box& box) {
	l = box.l;
	b = box.b;
	h = box.h;
}

int Box::getLength() {
	return this->l;
}

int Box::getBreadth() {
	return this->b;
}

int Box::getHeight() {
	return this->h;
}

long long Box::CalculateVolume() {
	return (long long) this->l * this->b * this->h;
}


ostream& operator << (ostream& output, const Box& B){
	output << B.l << " " << B.b << " " << B.h;
	return output;
}

void check2()
{
	int n;
	cin>>n;
	Box temp;
	for(int i=0;i<n;i++)
	{
		int type;
		cin>>type;
		if(type ==1)
		{
			cout<<temp<<endl;
		}
		if(type == 2)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			temp=NewBox;
			cout<<temp<<endl;
		}
		if(type==3)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			if(NewBox<temp)
			{
				cout<<"Lesser\n";
			}
			else
			{
				cout<<"Greater\n";
			}
		}
		if(type==4)
		{
			cout<<temp.CalculateVolume()<<endl;
		}
		if(type==5)
		{
			Box NewBox(temp);
			cout<<NewBox<<endl;
		}

	}
}

int main()
{
	check2();
}
