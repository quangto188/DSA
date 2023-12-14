#include "main.h"
int MAXSIZE;
class Restaurant{
	public:
		Restaurant() {};
		~Restaurant() {};
		virtual void LAPSE(string name)=0;
		virtual void KOKUSEN()=0;
		virtual void KEITEIKEN(int num)=0;
		virtual void HAND()=0;
		virtual void LIMITLESS(int num)=0; 
		virtual void CLEAVE(int num)=0;
		virtual void LIGHT(int num)=0;	
};
class customer{
public:
	string name;
	int Result;
	int ID;
	customer* prev;
	customer*next;
	customer(){}
	customer(string na, customer* p, customer *ne): name(na), prev(p), next(ne){}
	~customer(){}
	public:
	class HuffNode{
		public:
			char it;
			int wgt;
			HuffNode* lc;
			HuffNode* rc;
			HuffNode(){}
			HuffNode(char val, int freq, HuffNode* l, HuffNode* r){
				it=val;
				wgt=freq;
				lc=l;
				rc=r;
			};
			~HuffNode(){
			lc=NULL;
			rc=NULL;
			};
			int weight(){
				return wgt;
			};
			bool isLeaf(){
				if (lc ==NULL && rc== NULL) return false;
				return true;
			};
	};
class IntlNode : public HuffNode{
	public:
		HuffNode* lc;
		HuffNode* rc;
		int wgt;
		IntlNode(HuffNode* l, HuffNode* r){
			wgt= l->weight() + r->weight();
			lc=l;
			rc=r;
		}
		~IntlNode(){
			delete lc;
			delete rc;
		}
		int weight(){
			return wgt;
		}
		bool isLeaf(){
			return false;
		}
		HuffNode* left(){
			return lc;
		}
		void setLeft(HuffNode* b){
			lc=b;
		}
		HuffNode* right(){
			return rc;
		}
		void setRight(HuffNode* b){
			rc=b;
		}
};
class HuffTree {
	public:
		HuffNode *Root;
		string huffmanCodes[256];
	public:
		HuffTree(){}
		HuffTree(char val, int freq){
			Root = new HuffNode(val, freq, NULL, NULL);
		}
		~HuffTree(){
			delete Root;
		}
		HuffNode* root(){
			return Root;
		}
		HuffTree(HuffTree* l, HuffTree* r){
			Root = new IntlNode(l->root(), r->root());
		}
		int weight(){
			return Root->weight();
		}
		HuffNode *Rotate_right(HuffNode * node){
			HuffNode* tmp = node->lc;
			node->lc = tmp->rc;
			tmp->rc = node ;
			return tmp;
		}
		HuffNode* Rotate_left(HuffNode* node){
			HuffNode* tmp = node->rc;
			node->rc = tmp->lc ;
			tmp->lc = node;
			return tmp;
		}
		int getHeightRec(HuffNode *node){
			if (node == NULL)
				return 0;
			if (!node->lc && !node->rc) 
				return 1;
			int lh = this->getHeightRec(node->lc);
			int rh = this->getHeightRec(node->rc);
			return (lh > rh ? lh : rh) + 1;
		}
		int GetBalance(HuffNode* node){
			if(node->lc && node->rc){
				int lh = getHeightRec(node->lc);
				int rh = getHeightRec(node->rc);
				return lh - rh ;
			}else if(node->lc && !node->rc) return getHeightRec(node->lc) ;
			else if (!node->lc && node->rc) return 0 - getHeightRec(node->rc); 
			else  return 0 ;
		}
		void balance(HuffNode* node){
			if (GetBalance(node)==0) return;
			if(GetBalance(node) >= 2 && GetBalance(node->lc) == 1 ) {
				Rotate_right(node) ;
				return ;
				}
			else if(GetBalance(node) <= -2 && GetBalance(node->rc )== -1) {
				Rotate_left(node) ;
				return;
				}
			else if(GetBalance(node)  >= 2 && GetBalance(node->lc ) == -1) {
				node->lc = Rotate_left(node->lc);
				Rotate_right(node);
				return ;
			}else if(GetBalance(node) <= -2 && GetBalance(node->rc) == 1){
				node->rc = Rotate_right(node->rc);
				Rotate_left(node);
				return;
			}
		}
		HuffTree* buildHuff(HuffTree** TreeArray, int count) {
			while (count > 1) {
				// Tìm hai cây có trọng số nhỏ nhất
				int minIndex1 = 0, minIndex2 = 1;
				if (TreeArray[minIndex1]->weight() > TreeArray[minIndex2]->weight()) {
					std::swap(minIndex1, minIndex2);
				}

				for (int i = 2; i < count; ++i) {
					if (TreeArray[i]->weight() < TreeArray[minIndex1]->weight()) {
						minIndex2 = minIndex1;
						minIndex1 = i;
					} else if (TreeArray[i]->weight() < TreeArray[minIndex2]->weight()) {
						minIndex2 = i;
					}
				}
				// Tạo một cây mới bằng cách kết hợp hai cây có trọng số nhỏ nhất
				HuffTree* temp3 = new HuffTree(TreeArray[minIndex1], TreeArray[minIndex2]);
				balance(temp3->root());
				// Xóa hai cây đã kết hợp khỏi danh sách
				delete TreeArray[minIndex1];
				delete TreeArray[minIndex2];
				TreeArray[minIndex1] = temp3;
				TreeArray[minIndex2] = TreeArray[count - 1];
				count--;
				delete temp3;
			}
			return TreeArray[0];
		}
		int findmin(int arr2[]){
			int min;
			int x;
			for (int i=0; i < 52 ; i++){
				if (arr2[i] !=0) {
					min=arr2[i];
					break;
				}
			}
			for (int i=0; i <52 ; i++ )
				if (arr2[i] <= min && arr2[i] != 0){
					min= arr2[i];
					x=i;
				} 
			return x;
		}
		void generateHuffmanCodes(HuffNode* root, string code) {
			if (root->isLeaf()) {
				huffmanCodes[root->it] = code;
				return;
			}
			generateHuffmanCodes(root->lc, code + "0");
			generateHuffmanCodes(root->rc, code + "1");
		}
		string encode(const string& text) {
			string encodedText = "";
			for (char c : text) {
				encodedText += huffmanCodes[c];
			}
			return encodedText;
		}
		int binaryToDecimal(string& binaryString) {
			int decimalNumber = 0;
			int powerOfTwo = 1;

			for (int i = binaryString.length() - 1; i >= 0; --i) {
				if (binaryString[i] == '1') {
					decimalNumber += powerOfTwo;
				}
				powerOfTwo *= 2;
			}
			return decimalNumber;
		}

		void buildTree(customer* cus){
			string copyname=cus->name;
			string name= cus->name;
			int arr[52]={0};
			int arr2[52]={0};
			for(int i=0;i<=name.length()-2;i++)
				for(int j=i+1;j<=name.length()-1;j++)
					if(name[i] >= name[j]) {
						int temp = name[i];
						name[i] = name[j];
						name[j] = temp;
					}
			int dem = 1;
			for(int i=0;i<=name.length()-1;i++){
				if(name[i] == name[i+1]) dem++;
				else {
					if ((int)name[i] <91){
						int a=(int)name[i]-65;
						arr[a]=dem;
					}else {
						int a=(int)name[i]-97+26;
						arr[a]=dem;
					}
					dem = 1;
				}
			}
			for (int i=0; i <52; i++){
				if (arr[i]>0){
					int x= (i+arr[i])%52;
					arr2[x]+= arr[i];
				}
			}
			string name2="";
			for (int i=0; i < copyname.size(); i++){
				char b= copyname[i];
				int x = (int)b;
				if (x < 91) {
					x= x-65;
					int a= (x+arr[x])%52+65;
					char c=(char)a;
					name2+=c;
				}else{
					x=x-97+26;
					int a=(x+arr[x])%52+97-26;
					char c=(char)a;
					name2+=c;
				}
			}
			cout<<name2<<endl;
			int count=0;
			for (int i=0; i <52; i++){
				if (arr2[i] > 0 ) {
					count++;
				}
			}
			HuffTree** ArrayTree[count];
			for (int i=0; i < count; i++){
				char a;
				int p=findmin(arr2);
				if (p < 26) a= (char)p+65;
				else a=(char) p+97-26;
				HuffTree * Tree = new HuffTree(a,arr2[p]);
				*ArrayTree[i]=Tree;
				arr2[p]=0;
			}
			HuffTree * huff=buildHuff(*ArrayTree, count);
			cus->tree= huff;
			generateHuffmanCodes(huff->root(), "");
			string encodedtext= huff->encode(name2);
			if(encodedtext.size() >10) encodedtext= encodedtext.substr(0,10);
			cus->Result= binaryToDecimal(encodedtext);
			cus->ID= cus->Result% MAXSIZE +1;
		}
};
public:
	HuffTree* tree;
};
class Node{
	public:
	int data;
	int index;
	Node* lc;
	Node* rc;
	Node(int value) : data(value), lc(nullptr), rc(nullptr) {
		static int currentIndex = 1;
        index = currentIndex++;
	}
};
class BST{
	public:
	Node* root;
	int counter=0;
	Node* findMin(Node* root) {
        while (root->lc != nullptr) {
            root = root->lc;
        }
        return root;
    }
	Node* findMax(Node* root) {
        while (root->rc != nullptr) {
            root = root->rc;
        }
        return root;
    }
	Node* insertRecursive(Node* root, int value) {
        if (root == nullptr) {
			counter=1;
            return new Node(value);
        }

        if (value < root->data) {
            root->lc = insertRecursive(root->lc, value);
        } else if (value >= root->data) {
            root->rc = insertRecursive(root->rc, value);
        }
		counter++;
        return root;
    }
	bool searchRecursive(Node* root, int value) {
        if (root == nullptr) {
            return false;
        }

        if (value == root->data) {
            return true;
        } else if (value < root->data) {
            return searchRecursive(root->lc, value);
        } else {
            return searchRecursive(root->rc, value);
        }
    }
	Node* deleteByValue(Node* root, int value) {
        if (root == nullptr) {
            return root;
        }

        if (value < root->data) {
            root->lc = deleteByValue(root->lc, value);
        } else if (value > root->data) {
            root->rc = deleteByValue(root->rc, value);
        } else {
            // Node with only one child or no child
            if (root->lc == nullptr) {
                Node* temp = root->rc;
                delete root;
                return temp;
            } else if (root->rc == nullptr) {
                Node* temp = root->lc;
                delete root;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = findMax(root->lc);

            // Copy the inorder successor's content to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->lc = deleteByValue(root->lc, temp->data);
        }

        return root;
    }
	Node* deleteMinValue(Node* root) {
        if (root == nullptr) {
            return root;
        }

        if (root->lc == nullptr) {
            Node* temp = root->rc;
            delete root;
            return temp;
        }

        root->lc = deleteMinValue(root->lc);

        return root;
    }


	 void postOrderTraversalRecursive(Node* root, int*& result, int& index) {
        if (root != nullptr) {
            postOrderTraversalRecursive(root->lc, result, index);
            postOrderTraversalRecursive(root->rc, result, index);
            result[index++] = root->data;
        }
    }
	int countPermutations(int arr[], int size) {
		int count = 0;
		do {
			// Kiểm tra xem mảng có tạo ra cây BST giống như cây gốc không
			bool isBST = true;
			for (int i = 1; i < size; ++i) {
				if (arr[i] < arr[i - 1]) {
					isBST = false;
					break;
				}
			}
			if (isBST) {
				++count;
			}
		} while (next_permutation(arr, arr + size));

		return count;
	}
	int sreachindex(Node* root, int index){
		if (root->index==index){
			return root->data;
		}
		sreachindex(root->lc, index);
		sreachindex(root->rc, index);
		return 0;
	}

	BST() : root(nullptr) {}

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    bool search(int value) {
        return searchRecursive(root, value);
    }
	void removeByValue(int value) {
        root = deleteByValue(root, value);
    }
	void removeMinValue() {
        root = deleteMinValue(root);
    }
	int* postOrderTraversal(int& size) {
        int* result = new int[size];
        int index = 0;
        postOrderTraversalRecursive(root, result, index);
        size = index;
        return result;
    }
};

class MinHeap {
private:
    int* heap;
    int capacity = MAXSIZE;
    int size;

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index] < heap[parentIndex]) {
                std::swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < size && heap[leftChild] < heap[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < size && heap[rightChild] < heap[smallest]) {
            smallest = rightChild;
        }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap(){}

    ~MinHeap() {
        delete[] heap;
    }

    void insert(int value) {
        if (size == capacity) {
            std::cerr << "Heap is full." << std::endl;
            return;
        }

        heap[size] = value;
        heapifyUp(size);
        size++;
    }

    int extractMin() {
        if (size == 0) {
            std::cerr << "Heap is empty." << std::endl;
            return -1; // You may choose a different approach for handling an empty heap.
        }

        int minValue = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);

        return minValue;
    }
};

class im_res :public Restaurant{
		public:
		BST* nhaG; //nha g
		MinHeap* nhaS; //nhaS

		void LAPSE(string name){
			customer* cus= new customer(name, nullptr, nullptr);
			cout<<"done1"<<endl;
			cus->tree->buildTree(cus);
			cout<<"done2"<<endl;
			cout<<cus->name;
			if (cus->Result %2==1) {
				//nha g
				nhaG->insert(cus->Result);
			}else {
				//nhaS

			}
		};
		void KOKUSEN(){
			int Y = nhaG->countPermutations(nhaG->postOrderTraversal(nhaG->counter), nhaG->counter);
			if (Y > nhaG->counter) nhaG->root=nullptr;
			for (int i=1 ; i <=Y; i++){
				int valuedelete = nhaG->sreachindex(nhaG->root, i);
				nhaG->deleteByValue(nhaG->root,valuedelete);
			}
		};
		void KEITEIKEN(int num){

		};
		void HAND(){

		};
		void LIMITLESS(int num){

		}; 
		void CLEAVE(int num){

		};
		void LIGHT(int num){

		};
};


void simulate(string filename)
{	im_res* r = new im_res();
	ifstream ss(filename);
	string str, maxsize, name, num;
	while(ss >> str)
	{
		if(str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
    	}
        else if(str == "LAPSE")
        {
            ss >> name;
            r->LAPSE(name);
    	}
    	else if(str == "KOKUSEN") 
    	{
    			r->KOKUSEN();
		}
    	else if(str == "KEITEIKEN") 
    	{
				ss>>num;
    			r->KEITEIKEN(stoi(num));
		}
		else if(str == "HAND") 
		{
    			r->HAND();	
		}
    	else if(str == "LIMITLESS") 
     	{   	
				ss>>num;
    			r->LIMITLESS(stoi(num));
    	}
    	else
    	{
				ss>> num;
    			r->CLEAVE(stoi(num));
    	}
    }
}


