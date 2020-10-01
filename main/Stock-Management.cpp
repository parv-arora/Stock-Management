#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<fstream>
#include<conio.h>
#define CELL_WIDTH 20
using namespace std;

class Stock{
	int id;
	char productName[100];
	char category[100];
	int qty;
	double unitCost;
	char attr1[100];	
	char attr2[100];	
	char attr3[100];
	
	public : 
	
	void getData()
	{
		id = generateStockId();
		fflush(stdin);
		fflush(stdout);
		
		cout<<"Enter id : "; 
		cin>>id;
		fflush(stdout);
		fflush(stdin);
			
		cout<<"Enter product name : ";
		gets(productName);
		fflush(stdin);
		fflush(stdout);	
		
		cout<<"Enter Category : ";  
		gets(category);
		fflush(stdin);
		fflush(stdout);	
			
		cout<<"Enter Quantity : ";  
		cin>>qty;
		fflush(stdin);
		fflush(stdout);	
			
		cout<<"Enter unit cost : ";  
		cin>>unitCost;
		fflush(stdin);
		fflush(stdout);
			
		//additional attributes		
		return;
	}	
	
	void modify()
	{
		
		char ch;
		
		cout<<"Do you want to change product name (y/n) : ";
		cin>>ch;
		
		fflush(stdin); fflush(stdout);
		if(ch=='y')
		{
			cout<<"Enter Product name : "; gets(productName);
		}

		cout<<"Do you want to change Quantity (y/n) : ";
		cin>>ch;
		
		fflush(stdin); fflush(stdout);
		if(ch=='y')
		{
			cout<<"Enter Qty :"; cin>>qty;
		}
		
		cout<<"Do you want to change Category (y/n) : ";
		cin>>ch;
		
		fflush(stdin); fflush(stdout);
		if(ch=='y')
		{
			cout<<"Enter Category : "; gets(category);
		}
		
		cout<<"Do you want to change Unit cost (y/n) : ";
		cin>>ch;
	
		fflush(stdin); fflush(stdout);	
		if(ch=='y')
		{
			cout<<"Enter Unit Cost :"; cin>>unitCost;
		}
		// additional attributes
		return;
		
	}
	void divider()
	{
		cout<<setw(CELL_WIDTH)<<left<<setfill('-')<<"+";
		cout<<setw(CELL_WIDTH)<<left<<setfill('-')<<"+";
		cout<<"+\n";
		return;
	}

	void print()
	{
		divider();

		cout<<setw(CELL_WIDTH)<<left<<setfill(' ')<<"|Id"<<"|";
		cout<<setw(CELL_WIDTH-1)<<left<<setfill(' ')<<id;
		cout<<"|\n";

		divider();

		cout<<setw(CELL_WIDTH)<<left<<setfill(' ')<<"|Product Name"<<"|";
		cout<<setw(CELL_WIDTH-1)<<left<<setfill(' ')<<productName;
		cout<<"|\n";

		divider();
		
		cout<<setw(CELL_WIDTH)<<left<<setfill(' ')<<"|Category"<<"|";
		cout<<setw(CELL_WIDTH-1)<<left<<setfill(' ')<<category;
		cout<<"|\n";

		divider();
		cout<<setw(CELL_WIDTH)<<left<<setfill(' ')<<"|Qty"<<"|";
		cout<<setw(CELL_WIDTH-1)<<left<<setfill(' ')<<qty;
		cout<<"|\n";

		divider();
		cout<<setw(CELL_WIDTH)<<left<<setfill(' ')<<"|Unit Cost"<<"|";
		cout<<setw(CELL_WIDTH-1)<<left<<setfill(' ')<<unitCost;
		cout<<"|\n";

		divider();
		
		cout<<setw(80)<<setfill('#')<<"";
		cout<<"\n";
		//additional attributes
		return;
	}
	
	int getId()
	{
		return id;
	}
	
	
	int generateStockId()
	{
		ifstream fin("stocks.dat",ios::in|ios::binary);
		
		fin.seekg(0,ios::end);
		int size = fin.tellg();
		int count = size/sizeof(Stock);        //important
		
		if(count == 0)
			return 1;
		
		int pos = size - sizeof(Stock);
		fin.seekg(pos);
	
		Stock temp;
		fin.read((char*)&temp,sizeof(Stock));
	
		return temp.getId() + 1;
	}
	int getQty()
	{
		return qty;
	}
	
} gstock;

class Purchase
{
	char customerName[100];
	char mobile[20];
	int qty;
	double amount;
	int stockId;
	public:
		void getData(Stock stock)
		{
			stockId = stock.getId();
			fflush(stdin); fflush(stdout);
			
			cout<<"Enter Customer name : ";
			gets(customerName);
			fflush(stdin);
			fflush(stdout);	
			
			cout<<"Enter Mobile : ";  
			gets(mobile);
			fflush(stdin);
			fflush(stdout);	
				
			cout<<"Enter Quantity : ";  
			cin>>qty;
			fflush(stdin);
			fflush(stdout);	
				
			cout<<"Enter Amount : ";  
			cin>>amount;
			fflush(stdin);
			fflush(stdout);
				
			//additional attributes	 
			return;
		}
		
		void print()
		{
			cout<<customerName<<"\t";
			cout<<mobile<<"\t";
			cout<<qty<<"\t";
			cout<<amount<<"\t";
			return;
		}	
		
		int getStockId()
		{
			return stockId;
		}
		
		int getQty()
		{
			return qty;
		}
};

void viewStock()
{
	Stock temp;
	ifstream fin("stocks.dat",ios::in|ios::binary);
	while(fin.read((char*)&temp,sizeof(Stock)))
	{
		temp.print();
	}
	fin.close();
	return;
}

void addStock()
{
	Stock stock;
	stock.getData();
	
	ofstream fout("stocks.dat",ios::out|ios::binary|ios::app);
	fout.write((char*)&stock,sizeof(Stock));
	fout.flush();
	fout.close();
	return;
}

void deleteStock()
{
	int id;
	cout<<"Enter the id of stock to delete: ";
	cin>>id;
	
	ifstream fin("stocks.dat",ios::in|ios::binary);
	ofstream fout("temp.dat",ios::out|ios::binary);
	
	Stock temp;
	int flag=0;
	while(fin.read((char*)&temp,sizeof(Stock)))
	{
		if(temp.getId()!=id){
			fout.write((char*)&temp,sizeof(Stock));
		}else{
			flag= 1;
		}
	}
	fout.flush();
	fout.close();
	fin.close();
	
	if(flag==0)
	{	cout<<"Stock not found!";
		return;
	}
	
	remove("stocks.dat");
	rename("temp.dat","stocks.dat");
	
	cout<<"Stock Removed!";
	return;
}

void modifyStock()
{
	int id;
	cout<<"Enter the id of Stock to modify : ";
	cin>>id;
	
	ifstream fin("stocks.dat",ios::in|ios::binary);
	ofstream fout("stocks.dat",ios::in|ios::out|ios::ate|ios::binary);
	Stock temp;	
	int flag = 0;
	
	while(fin.read((char*)&temp,sizeof(Stock)))
	{
		if(temp.getId() == id)
		{
			flag = 1;
			temp.modify();
			int pos = fin.tellg() - sizeof(Stock);
			fout.seekp(pos);
			fout.write((char*)&temp,sizeof(Stock));
		}
	}
	fout.flush();
	fout.close();
	fin.close();
		
	if(flag==0)
	{	cout<<"Stock not found!";
		return;
	}
	
	cout<<"Stock Modified !!";
	return;
}

Stock* findStock(int id)
{
	ifstream fin("stocks.dat",ios::in|ios::binary);
	while(fin.read((char*)&gstock,sizeof(Stock)))
	{
		if(gstock.getId() == id)
		{
			return &gstock;
		}
	}
	return NULL;
}

void addPurchase(Stock stock)
{
	ofstream fout("purchases.dat",ios::out|ios::app|ios::binary);
	Purchase temp;
	temp.getData(stock);
	
	if(temp.getQty()>stock.getQty())
	{
		cout<<"!!NOT SUFFICIENT STOCK!!";
		return;
	}
	
	fout.write((char*)&temp,sizeof(Purchase));
	fout.flush();
	fout.close();
	
	cout<<"!!Purchase Added!!";
	return;
}

void viewPurchases(int id)
{
	ifstream fin("purchases.dat",ios::in|ios::binary);
	Purchase temp;
	
	while(fin.read((char*)&temp,sizeof(Purchase)))
	{
		if(temp.getStockId() == id)
		temp.print();
	}
	fin.close();
	return;
}

void purchaseMenu()
{
	int id;
	cout<<"Enter the id of stock to select : ";
	cin>>id;
	
	Stock* stock;
	stock = findStock(id);
	if(stock==NULL)
	{
		cout<<"!!stock not found!!";
		return;
	}
	int ch;
	cout<<"Enter a option to choose : \n";
	cout<<"0 - Main menu\n";
	cout<<"1 - View Purchases\n";
	cout<<"2 - Add Purchases\n";
	cin>>ch;
	
	switch(ch)
	{
		case 0 : return;
			break;
		case 1 : viewPurchases(id);
			break;
		case 2 : addPurchase(*stock);
			break;
	}
	return;
}

int main()
{
	while(1)
	{
//		clrscr()
		system("cls");
	
		int ch;
		cout<<"Choose a option : \n";
		cout<<"0 - exit\n";
		cout<<"1 - View Stock\n";
		cout<<"2 - Add Stock\n";
		cout<<"3 - Remove Stock\n";
		cout<<"4 - Modify Stock\n";
		cout<<"5 - Select Stock\n";
		cin>>ch;
	
		switch(ch)
		{
			case 0 : return 0;
				break;
			case 1 : viewStock();
				break;
			case 2 : addStock();
				break;
			case 3 : deleteStock();
				break;
			case 4 : modifyStock();
				break;
			case 5 : purchaseMenu();
				break;
		}
	
		_getch();
	}
	return 0;
}
