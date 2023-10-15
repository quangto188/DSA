#include "main.h"

class imp_res : public Restaurant
{	public:
		int counter;
		int counterQueue;
		int counterdau;
		customer *first;
		customer *X;
		customer *firstQueue;
		customer *lastQueue;
		customer *firstHistory;
		customer *lastHistory;
		customer *dau;

	public:	
		imp_res() {
			counter=0;
			counterQueue=0;
			counterdau=0;
		};
		customer *copylist(customer *cus,int num){
			customer *current = cus;
			customer *copy = new customer (current->name,current->energy,current->next,NULL);
			customer *const head = copy;
			current=current->next;
			for (int i=1; i < counter -num ; i ++){
				copy= copy ->next =new customer(current->name, current->energy, NULL, NULL);
				current=current->next;
			}
			// while (current !=NULL){
			// 	copy = copy->next =new customer (current->name, current->energy, NULL, NULL);
			// 	// copy = copy->next;
			// 	current= current->next;
			// }
			return head;
		}

		customer *removeFirstQueue(){
			customer *del = firstQueue;
			firstQueue=firstQueue->next;
			del ->next =nullptr;
			counterQueue--;
			return del;
		}


		void removeFirstHistory(){
			customer *del = firstHistory;
			firstHistory = firstHistory->next;
			del ->next =nullptr;
			delete del;
		}
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


		void logicRED(customer* abc) {
			customer *cus=new customer(abc->name, abc->energy,NULL,NULL);
            if (cus->energy ==  0){
				return;
			}
			if (counter ==0){ 
				first = cus;
				customer* histemp = new customer(cus->name , cus->energy ,nullptr, nullptr );
				firstHistory = histemp;
				lastHistory = histemp;
				counter++;
			}else if (counter==1){
				if (!checkname(cus)) return;
				first->next=cus;
				first->prev =cus;
				cus->next= first;
				cus->prev = first;
				X= cus;
				customer* histemp = new customer(cus->name , cus->energy ,nullptr, nullptr );
				lastHistory->next= histemp;
				lastHistory = histemp;
				counter++;
			}else if (counter < MAXSIZE/2){
				if (!checkname(cus)) return;
				customer* histemp = new customer(cus->name , cus->energy ,nullptr, nullptr );
				lastHistory->next= histemp;
				lastHistory = histemp;
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
				customer* histemp = new customer(cus->name , cus->energy ,nullptr, nullptr );
				lastHistory->next= histemp;
				lastHistory = histemp;
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
		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);
			logicRED(cus);
			
		}
		void BLUE(int num)
		{
			cout << "blue "<< num << endl;
			if (num >= counter) {
				counter=0;
				first->next=NULL;
				first->prev=NULL;
				for(int i=0; i < counterQueue; i){
					logicRED(removeFirstQueue());
					//cout<<counterQueue<<endl;
				}
			}else {
				for (int i=0; i< num; i++){
					removeFirstHistory();
				}
				//cout<<" COUNTER: >>>>>>>>>>>>>>>>>>>>>>>>>>>   "<<counter<<endl;
				counterdau=counter-num;
				dau =copylist(firstHistory,num);
				counter=0;
				first->next=NULL;
				first->prev=NULL;				
				// customer *const head=dau;
				// customer *a=head;
				// cout<<"head"<<endl;
				// for (int i=0; i < counterdau ; i++){
				// 	cout<<a->energy<<"     ";
				// 	a=a->next;
				// }
				// cout<<endl;




				for (int i=0; i< counterdau;i++){
					logicRED(dau);
					dau=dau->next;
				}



				// customer *b=head;
				// cout<<"head"<<endl;
				// for (int i=0; i < counterdau ; i++){
				// 	cout<<b->energy<<"     ";
				// 	b=b->next;
				// }
				for (int i=0;i<num;i++){
					logicRED(removeFirstQueue());
				}


			}
			// counterdau=counter-num;
			// dau =copylist(firstHistory,num);
			// cout<<"head"<<endl;
			// for (int i=0; i < counterdau ; i++){
			// 	cout<<dau->energy<<"     ";
			// 	dau=dau->next;
			// }

			// cout<<endl;
			// cout<<" History"<<endl;
			// for(int i=0; i< counterdau;i++){
			// 	cout<<firstHistory->energy<< "     ";
			// 	firstHistory=firstHistory->next;
			// }
			// counter=0;
			// for (int i=0; i< counterdau;i++){
			// 	logicRED(dau);
			// 	dau=dau->next;
			// }
			// for (int i=0;i<num;i++){
			// 	customer *que = removeFirstQueue();
			// 	logicRED(que);
			// }
			
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
			// cout << "--------------danh sach trong head-------------" << endl;
			// customer *f= dau;
			// int mw = 1;
			// while (mw <= counterdau)
			// {
			// 	cout << f->name << " " << f->energy << endl;
			// 	f = f->next;
			// 	mw++;
			// }
			// cout << "--------------danh sach trong history-------------" << endl;
			// customer *c = firstHistory;
			// int m = 1;
			// while (m <= 4)
			// {
			// 	cout << c->name << " " << c->energy << endl;
			// 	c = c->next;
			// 	m++;
			// }
			
		}
};