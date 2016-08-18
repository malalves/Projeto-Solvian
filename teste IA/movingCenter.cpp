#include <iostream>
#include <cmath>
#include <cstring>

#define mtoFrio 0
#define frio 15
#define bom 25
#define quente 35
#define mtoQuente 50

#define Tmin 0
#define Tmax 50

using namespace std;

int get_temp(){
	int tmp;
	cin >> tmp;
	return tmp;
}

void output(int outTmp, int outFan){
	cout<<"temperatura: "<< outTmp << "\nFan: " << outFan <<endl;
}

class CFuzzyFunction{
	protected :
		double dLeft, dRight;
		char   cType;
		char*  sName;

	public:
		CFuzzyFunction(){};
		
		virtual ~CFuzzyFunction(){
			delete [] sName;
			sName=NULL;
		}

		virtual void setInterval(double l,double r){
			dLeft=l; dRight=r;
		}

		virtual void setMiddle( double dL=0,double dR=0)=0;

		virtual void setType(char c){
			cType=c;
		}

		virtual void setName(const char* s){ 
		  sName = new char[strlen(s)+1];
		  strcpy(sName,s);
		}

		bool isDotInInterval(double t){
			if((t>=dLeft)&&(t<=dRight)) return true; else return false;
		}

		char getType(void)const{ return cType;}

		void getName() const{
			cout<<sName<<endl;
		}

		virtual double getValue(double t)=0;
};

class CTriangle : public CFuzzyFunction{
	private: 
		double dMiddle;

	public:
		void setMiddle(double dL, double dR){
			dMiddle=dL;
		}

		double getValue(double t){
			if(t<=dLeft)
				return 0;
			else if(t<dMiddle)
				return (t-dLeft)/(dMiddle-dLeft);
			else if(t==dMiddle)
				return 1.0;
			else if(t<dRight)
				return (dRight-t)/(dRight-dMiddle);
			else
				return 0;
		}
};

class CTrapezoid : public CFuzzyFunction{
	private:
		double dLeftMiddle, dRightMiddle;

	public:
		void setMiddle(double dL, double dR){
			dLeftMiddle=dL;
			dRightMiddle=dR;
		}

		double getValue(double t){
			if(t<=dLeft)
				return 0;
			else if(t<dLeftMiddle)
				return (t-dLeft)/(dLeftMiddle-dLeft);
			else if(t<=dRightMiddle)
				return 1.0;
			else if(t<dRight)
				return (dRight-t)/(dRight-dRightMiddle);
			else 
				return 0;
		}   
};

int main(){
	CFuzzyFunction *FuzzySet[5];
	FuzzySet[0] = new CTriangle;
	FuzzySet[1] = new CTriangle;
	FuzzySet[2] = new CTriangle;
	FuzzySet[3] = new CTriangle;
	FuzzySet[4] = new CTriangle;

	FuzzySet[0]->setInterval(mtoFrio,frio);
	FuzzySet[0]->setMiddle(mtoFrio,mtoFrio);
	FuzzySet[0]->setType('t');
	FuzzySet[0]->setName("mtoFrio");

	FuzzySet[1]->setInterval(mtoFrio,bom);
	FuzzySet[1]->setMiddle(frio,frio);
	FuzzySet[1]->setType('t');
	FuzzySet[1]->setName("frio");

	FuzzySet[2]->setInterval(frio,quente);
	FuzzySet[2]->setMiddle(bom,bom);
	FuzzySet[2]->setType('t');
	FuzzySet[2]->setName("bom");

	FuzzySet[3]->setInterval(bom,mtoQuente);
	FuzzySet[3]->setMiddle(quente,quente);
	FuzzySet[3]->setType('t');
	FuzzySet[3]->setName("quente");

	FuzzySet[4]->setInterval(quente,mtoQuente);
	FuzzySet[4]->setMiddle(mtoQuente,mtoQuente);
	FuzzySet[4]->setType('t');
	FuzzySet[4]->setName("mtoQuente");

	double dValue;
	
	do{	
		char menu = 0;
		cout<<"\nInput the operation type:\n"<<"a - set center\n"<<"b - Input a value" << endl;
		cin >> menu;
		switch (menu){
			case 'a':
				cout<<"imput the center temperature: ";
				double var;
				var = (bom - get_temp());
				FuzzySet[0]->setMiddle(mtoFrio - var,mtoFrio - var);
				FuzzySet[1]->setMiddle(frio - var,frio - var);
				FuzzySet[2]->setMiddle(bom - var,bom - var);
				FuzzySet[3]->setMiddle(quente - var,quente - var);
				FuzzySet[4]->setMiddle(mtoQuente - var,mtoQuente - var);
				continue;

			case 'b':
				cout<<"\nInput the value:" <<endl;
				dValue=get_temp();
				break;

			default:
				continue;
		}


		if(dValue < Tmin) continue;
		if(dValue > Tmax) continue;

		for(int i=0; i<5; i++){
			cout<<"In function:";
			FuzzySet[i]->getName();
		
			if(FuzzySet[i]->isDotInInterval(dValue))
				cout<<"In the interval";
			else
				cout<<"Not in the interval";
			cout<<endl;

			cout<<"and the membership is=";
			cout<<FuzzySet[i]->getValue(dValue)<<endl<<endl;
	  }

	}
	while(true);

	return 0;
}