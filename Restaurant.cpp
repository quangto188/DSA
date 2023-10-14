#include "main.h"

class imp_res : public Restaurant
{	public:
		int counter;
		int counterQueue;
		customer *first;
		customer *X;
		customer *firstQueue;
		customer *lastQueue;

	public:	
		imp_res() {
			counter=0;
			counterQueue=0;
		};
		customer *find_RES(customer *cus){
			int RES = abs(first->energy - cus->energy);
			customer *a=first;
			customer *result = a;
			int index=0;
			while (index <counter){
				if (abs(a->energy-cus->energy) > RES){
					RES = abs(a->energy-cus->energy);
					result = a;
				}
				a=a->next;
				index++;
			}
			return result;
		}
		bool checkname(customer *cus){
			customer *a= first;
			int index=0;
			while (index < counter ){
				if (a->name == cus->name) return false;
				a= a->next;
				index++;
			}
			return true;
		}
		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);
			if (cus->energy ==  0){
				return;
			}
			if (counter ==0){ 
				first = cus;
				counter++;
			}else if (counter==1){
				if (!checkname(cus)) return;
				first->next=cus;
				first->prev =cus;
				cus->next= first;
				cus->prev = first;
				X= cus;
				counter++;
			}else if (counter < MAXSIZE/2){
				if (!checkname(cus)) return;
				if (cus->energy >= X->energy){
					customer *N= X->next;
					X->next=cus;
					cus->prev=X;
					cus->next=N;
					N->prev=cus;
					X=X->next;
					counter++;
				}else{
					customer *N= X->prev;
					X->prev =cus;
					cus->next=X;
					cus->prev=N;
					N->next= cus;
					X= X->prev;
					counter++;
				}
			}else if ( counter < MAXSIZE){
				if (!checkname(cus)) return;
				X= find_RES(cus); //tim X
				int RES= cus->energy-X->energy;
				if (RES >=0){
					customer *N= X->next;
					X->next=cus;
					cus->prev=X;
					cus->next=N;
					N->prev=cus;
					X=X->next;
					counter++;
				}else{
					customer *N= X->prev;
					X->prev =cus;
					cus->next=X;
					cus->prev=N;
					N->next= cus;
					X= X->prev;
					counter++;
				}
			}else if (counter == MAXSIZE && counterQueue ==0){
				if (!checkname(cus)) return;
				lastQueue=cus;
				firstQueue=cus;
				counterQueue=1;
			}else{
				if (!checkname(cus)) return;
				if (counterQueue== MAXSIZE) return;
				lastQueue->next= cus;
				lastQueue = cus;
				counterQueue++;
			}
			
			return;
		}
		void BLUE(int num)
		{
			cout << "blue "<< num << endl;
		}
		void PURPLE()
		{
			cout << "purple"<< endl;
		}
		void REVERSAL()
		{
			cout << "reversal" << endl;
		}
		void UNLIMITED_VOID()
		{
			cout << "unlimited_void" << endl;
		}
		void DOMAIN_EXPANSION()
		{
			cout << "domain_expansion" << endl;
		}
		void LIGHT(int num)
		{
			cout << "light " << num << endl;
		}
		void SHOW()
		{
			cout << "--------------danh sach trong ban--------------" << endl;
			customer *a = first;
			int max = 1;
			while (max <= counter)
			{
				cout << a->name << " " << a->energy << endl;
				a = a->next;
				max++;
			}
			cout << "--------------danh sach trong queue-------------" << endl;
			customer *b = firstQueue;
			int mx = 1;
			while (mx <= counterQueue)
			{
				cout << b->name << " " << b->energy << endl;
				b = b->next;
				mx++;
			}
		}
};