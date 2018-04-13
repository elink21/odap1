#include<bits\stdc++.h>
using namespace std;

struct product{
	int price;
	int stock;
	int id;
	string name;
	string description;
};

stack <product> p;
vector<product> products;





int seekForKey(int key)
{
	for(product x: products)
	{
		if(key==x.id)
		{
			cout<<"A match found!: \n";
			cout<<x.id<<"\n"<<x.name<<"\n";
			cout<<x.description<<"\n"<<x.price<<" "<<x.stock<<"\n\n";
			cout<<"-----------------";
			return true;
		}
	}
	return false;
}



void writeData(stack<product> p)
{
	ofstream seq ("seq.seq");
	seq<<p.size()<<"\n";
	while(!p.empty())
	{
		product x= p.top();
		p.pop();
		
		seq<<x.id<<"\n";
		seq<<x.name<<"\n";
		seq<<x.description<<"\n";
		seq<<x.price<<" "<<x.stock<<"\n\n";
	}
}


void printProducts(vector<product> p)
{
	for(product x:p)
	{
		if(x.id!=-1)
		{
			cout<<x.id<<"\n"<<x.name<<"\n";
			cout<<x.description<<"\n"<<x.price<<" "<<x.stock<<"\n\n";	
		}
		
	}
}

void readProducts()
{
	ifstream inFile ("seq.seq");
	int dataSize;
	string trash;

	inFile>>dataSize;
	getline(inFile,trash);

	for(int i=0;i<dataSize;i++)
	{
		product aux;
		inFile>>aux.id;
		getline(inFile,trash);
		getline(inFile,aux.name);
		getline(inFile,aux.description);
		inFile>>aux.price>>aux.stock;
		getline(inFile,trash);
		p.push(aux);
		products.push_back(aux);
	}
	inFile.close();
	//printProducts(products);
}

int searchIndex(int key)
{
	for (int i = 0; i < products.size(); i++)
	{
		if(products[i].id==key)return i;
	}
	return -1;
}

void update(vector<product> products)
{
	while(!p.empty()) p.pop();
	for(product x:products)
		p.push(x);
	writeData(p);
}

void deleteElement(int key)
{
	while( !p.empty() ) p.pop();
	int index= seekForKey(key);

	if(index!=-1)
	{
		products.erase(products.begin()+index);
		
		for (int i = 0; i < products.size(); i++)
		{
			p.push(products[i]);
		}
		cout<<"\n"<<p.size();

		writeData(p);
		cout<<"\n Element <"<< key<<">  deleted!";
	}
	else cout<<"Product doesnt exists";
}

void deleteWithTrash(int key)
{	
	for(int i=0;i<products.size();i++)
	{
		if(products[i].id==key)
		{
			products[i].id=-1;
			products[i].name="trash";
			products[i].description="trash";
			products[i].price=-1;
			products[i].stock=-1;
		}
		
	}
	update(products);
	writeData(p);
}



void createProducts()
{
	product p1; 
	fstream seq("seq.seq",fstream::app);
	string another;

	do{
		cout<<"Enter id: ";
		cin>>p1.id;
		for(product x: products)
		{
			while(x.id==p1.id)
			{
				cout<<"Duplicated key, please type another: ";
				cin>>p1.id;
			}
		}
		getchar();
		cout<<"Enter product name: ";
		getline(cin,p1.name);
		cout<<"Enter product description: ";
		getline(cin,p1.description);

		cout<<"Enter price: ";
		cin>>p1.price;
		cout<<"Enter stock: ";
		cin>>p1.stock;

		products.push_back(p1);
		p.push(p1);
		cout<<"Another product?: (y/n) \n";
		cin>>another;
	
	} while(another!="n");
	writeData(p);
	seq.close();
}

void updateWithKey(int key)
{
	int index=searchIndex(key);
		getchar();
		cout<<"Enter new name: ";
		getline(cin,products[index].name);
		cout<<"Enter new description: ";
		getline(cin,products[index].description);
		cout<<"Enter new price: ";
		cin>>products[index].price;
		cout<<"Enter new stock: ";
		cin>>products[index].stock;
	update(products);
	writeData(p);
}

int main()
{
	readProducts();
	int option;
	cout<<"Select option\n 1-Create 2-Seek for key 3-Delete with key 4-showList 5-Delete2 6-Updatewk \n";
	cin>>option;
	switch(option)
	{
		case 1:
			createProducts();
		break;

		case 2:
			cout<<"Enter key: ";
			cin>>option;
			seekForKey(option);
		break;

		case 3:
			cout<<"Enter key: ";
			cin>>option;
			deleteElement(option);
		break;

		case 4:
			printProducts(products);
		break;
		case 5:
			cout<<"Enter key: ";
			cin>>option;
			deleteWithTrash(option);
		break;
		case 6:
			cout<<"Enter key: ";
			cin>>option;
			updateWithKey(option);
			break;
		default:
			cout<<"Option doesnt exists\n";
	}
	//writeData();
}