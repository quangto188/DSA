#include "main.h"

class imp_res : public Restaurant
{	public:
		int counter;
		int counterQueue;
		int counterdau;
		int counterDOMAND;
		customer *first;
		customer *firstDM;
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
			counterDOMAND=0;
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
			//cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);
			logicRED(cus);
			
		}
		void BLUE(int num)
		{	if (counter>0){
			if (num >= counter) {
				counter=0;
				first->next=NULL;
				first->prev=NULL;
				for(int i=0; i < counterQueue; i){
					logicRED(removeFirstQueue());
				}
			}else if (num< counter && counterQueue>0) {
				for (int i=0; i< num; i++){
					removeFirstHistory();
				}
				counterdau=counter-num;
				dau =copylist(firstHistory,num);
				counter=0;
				first->next=NULL;
				first->prev=NULL;				
			
				for (int i=0; i< counterdau;i++){
					logicRED(dau);
					dau=dau->next;
				}
				int j= min(num,counterQueue);
				for (int i=0;i<j;i++){
					logicRED(removeFirstQueue());
				}
			}else {
				for (int i=0; i< num; i++){
					removeFirstHistory();
				}
				counterdau=counter-num;
				dau =copylist(firstHistory,num);
				counter=0;
				first->next=NULL;
				first->prev=NULL;				
			
				for (int i=0; i< counterdau;i++){
					logicRED(dau);
					dau=dau->next;
				}
			}
		}
				// customer *a = first;
				// for (int i=0; i< counter; i++){
				// 	a->print();
				// 	a=a->next;
				// }
		}
		void PURPLE()
		{
			//cout << "purple"<< endl;
		}
		void REVERSAL()
		{
			//cout << "reversal" << endl;
		}
		void UNLIMITED_VOID()
		{
			//cout << "unlimited_void" << endl;
		}
		void deletenodeQueueam(){
				while (firstQueue->energy<0 && firstQueue->next !=NULL){
					firstQueue->print();
					firstQueue= firstQueue->next;
					counterQueue--;
				}
			if (counterQueue ==1){
				if (firstQueue->energy <0) firstQueue->print();
				return;
			}
			customer *p=firstQueue->next;
			while (p->next!=NULL){
				if (p->energy<0){
					p->print();
					customer *temp=p;
					p=p->next;
					counterQueue--;
					delete(temp);
				}else p=p->next;
			}
			if (p->next==NULL & p->energy <0){
				p->print();
				counterQueue--;
				delete(p);
			}
			
		}
		void deletenodeQueueduong(){
			while (firstQueue->energy>0 && firstQueue->next !=NULL){
					firstQueue->print();
					firstQueue= firstQueue->next;
					counterQueue--;
				}
			if (counterQueue ==1){
				if (firstQueue->energy >0) firstQueue->print();
				return;
			}
			customer *p=firstQueue->next;
			while (p->next!=NULL){
				if (p->energy>0){
					p->print();
					customer *temp=p;
					p=p->next;
					counterQueue--;
					delete(temp);
				}else p=p->next;
			}
			if (p->next==NULL & p->energy >0){
				p->print();
				counterQueue--;
				delete(p);
			}
			
		}
		void deletenodeHistoryam(){
			customer *p=firstHistory;
			if (p->energy <0) {
				firstHistory->print();
				firstHistory=firstHistory->next;
				free(p);
				return;
			}
			while (p->next!=NULL){
				if (p->next->energy <0){
					customer *temp = p->next;
					temp->print();
					p->next =p->next->next;
					free(temp);
				}else p=p->next;
			}
		}
		void deletenodeHistoryduong(){
			customer *p=firstHistory;
			if (p->energy >0) {
				firstHistory->print();
				firstHistory=firstHistory->next;
				free(p);
				return;
			}
			while (p->next!=NULL){
				if (p->next->energy >0){
					customer *temp = p->next;
					temp->print();
					p->next =p->next->next;
					free(temp);
				}else p=p->next;
			}
			
		}


		bool checkdomain(){
			int tongam=0;
			int tongduong=0;
			customer *a=first;
			for (int i=0; i < counter; i++){
				if (a ->energy <0 ) tongam +=a->energy;
				else tongduong+=a->energy;
				a=a->next;
			}
			if (counterQueue>0){
				customer *aqueue= firstQueue;
				for (int i=0; i< counterQueue; i++){
					if (aqueue ->energy <0) tongam+=aqueue->energy;
					else tongduong+=aqueue->energy;
					aqueue=aqueue->next;
				}
			}
			if (abs(tongam) > tongduong) return 0;
			else return 1;
		}
		void DOMAIN_EXPANSION(){
			customer* a = first;
			int x= counter;
			if(checkdomain() == 1) {
				// lay duong
				for(int i =0 ; i< x ;i++)
				{
					if(a->energy > 0) {
						customer* cus = new customer(a->name , a->energy , nullptr  , nullptr);
						if (counterDOMAND ==0){ 
							firstDM = cus;
							counterDOMAND++;
						}else if (counterDOMAND==1){
							firstDM->next=cus;
							firstDM->prev =cus;
							cus->next= firstDM;
							cus->prev = firstDM;
							X= cus;
							counterDOMAND++;
						}else {
							customer *N= X->next;
							X->next=cus;
							cus->prev=X;
							cus->next=N;
							N->prev=cus;
							X=X->next;
							counterDOMAND++;
						}
					}
					a = a->next;
				}
				deletenodeHistoryam();
				if (counterQueue>0) deletenodeQueueam();
			}
			else {
				// lay am
				
				for(int i =0 ; i< x ;i++)
				{
					if(a->energy < 0) {
						customer* cus = new customer(a->name , a->energy , nullptr  , nullptr);
						if (counterDOMAND ==0){ 
							firstDM = cus;
							counterDOMAND++;
						}else if (counterDOMAND==1){
							firstDM->next=cus;
							firstDM->prev =cus;
							cus->next= firstDM;
							cus->prev = firstDM;
							X= cus;
							counterDOMAND++;
						}else {
							customer *N= X->next;
							X->next=cus;
							cus->prev=X;
							cus->next=N;
							N->prev=cus;
							X=X->next;
							counterDOMAND++;
						}
					}
					a = a->next;
				}
				deletenodeHistoryduong();
				if (counterQueue>0) deletenodeQueueduong();
			}
		first=firstDM;
		counter=counterDOMAND;
		if (counterQueue >0 && counter <MAXSIZE){
			int x=min(MAXSIZE-counter, counterQueue);
			for(int i=0; i<x; i++){
				logicRED(removeFirstQueue());
			}
		}		
	}
		void LIGHT(int num)
		{
			if (num >0 ){
				customer *a = X;
				for (int i=0; i< counter; i++){
					a->print();
					a=a->next;
				}
			}else if (num <0){
				customer *a = X;
				for (int i=0; i< counter; i++){
					a->print();
					a=a->prev;
				}
			}else {
				customer *a=firstQueue;
				for (int i=0; i< counterQueue ; i++){
					a->print();
					a=a->next;
				}
			}
		}
		
};