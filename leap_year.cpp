include <iostream>

using namespace std;;

int main(){
	int year;
	cin>>year;
	if(year % 4 == 0){
		if(year % 100 == 0){
			if(year % 400 ==0)
				cout<<"yes";
			else
				cout<<"NO";
		}
		else
			cout<<"NO";
	}
	else
		cout<<"NO";
	
	return 0;

}
