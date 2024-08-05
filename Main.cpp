#include<process.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>

class product
{   private:
	int pno;
	char name[50];
	float price;
	float qty;
	float tax;
	float dis;
    public:
	void create_product();
	void show_product();
	void write_product();
	void display_all();
	void display_sp(int n);
	void modify_product();
	void delete_product();
	void admin_menu();
	void cust_menu();
	product()
	{pno=102;
	}
}pr;
fstream fp;
void product::create_product()
{
		cout << "\nProduct No.: "<<pno;
		cout << "\n\nPlease Enter The Name of The Product ";
		gets(name);
		cout << "\nPlease Enter The Price of The Product ";
		cin >> price;
		cout << "\nPlease Enter The Discount (%) ";
		cin >> dis;
}
void product::show_product()
{
	    cout << "\nThe Product No. of The Product : " << pno;
	    cout << "\nThe Name of The Product : "<<name;
	    cout << "\nThe Price of The Product : " << price;
	    cout << "\nDiscount : " << dis;
}
void product::write_product()
{
    fp.open("Shop.dat", ios::app | ios::binary);
    pr.create_product();
    fp.write((char * ) & pr, sizeof(product));
    fp.close();
    cout << "\n\nThe Product Has Been Created ";
    pno++;
    getch();
}
void product::display_all()
{
    clrscr();
    cout << "\n\n\n\t\tCatalog\n\n";
    fp.open("Shop.dat", ios:: in | ios::binary );
    while (fp.read((char * ) & pr, sizeof(product)))
    {
	pr.show_product();
	cout << "\n\n******************************\n";
	getch();
    }
    fp.close();
    getch();
}
void product::display_sp(int n)
{
    int flag = 0;
    fp.open("Shop.dat", ios:: in | ios::binary );
    while (fp.read((char * ) & pr, sizeof(pr)))
    {
	if (pr.pno == n)
	{
	    clrscr();
	    pr.show_product();
	    flag = 1;
	}
    }
    fp.close();
    if (flag == 0)
    {	cout << "\n\nrecord not exist";}
    getch();
}
void product::modify_product()
{   fstream fp1;
    int no;
    char ans;
    clrscr();
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Product No. of The Product";
    cin >> no;
    fp.open("Shop.dat", ios::in | ios::binary);
    fp1.open("Temp.dat",ios::out | ios::binary);
    while (fp.read((char * ) & pr, sizeof(pr)))
    {
	if (pr.pno == no)
	{
	    pr.show_product();
	    cout<<"\nIs this the record you want to modify";
	    cin>>ans;
	    if(ans=='y'||ans=='Y')
	    {
	     cout << "\nPlease Enter The New Details of Product" << endl;
	     pr.create_product();
	     fp1.write((char*)&pr,sizeof(pr));
	    }
	    else
	    {
	      fp1.write((char*)&pr,sizeof(pr));
	    }
	 }
	 fp.close();
	 fp1.close();
	 remove("Shop.dat");
	 rename("Temp.dat", "Shop.dat");
	    cout << "\n\n\t Record Updated";
    }

    getch();
}
void product::delete_product()
{
    int no;
    char ans;
    clrscr();
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nEnter The product no. of The Product You Want To Delete";
    cin >> no;
    fp.open("Shop.dat", ios:: in | ios::binary);
    fstream fp1;
    fp1.open("Temp.dat", ios::out | ios::binary);

    while (fp.read((char * ) & pr, sizeof(product)))
    {     if(pr.pno==no)
	    {
	    pr.show_product();
	    cout<<"\nIs this the record you want to delete";
	    cin>>ans;
	    if(ans=='n'||ans=='N')
	    {
	     fp1.write((char*)&pr,sizeof(pr));
	    }
	    }
    }
    fp.close();
    fp1.close();
    remove("Shop.dat");
    rename("Temp.dat", "Shop.dat");
    cout << "\n\n\tRecord Deleted ..";
    getch();
}
void product::cust_menu()
{
    int order[50], quant[50], a = 0;
    float amt, damt, total = 0;
    char ch;
    display_all();
    cout << "\n******************************";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n******************************\n";
    do
    {
	cout << "\n\nEnter The Product No. Of The Product : ";
	cin >> order[a];
	cout << "\nQuantity in number : ";
	cin >> quant[a];
	a++;
	cout << "\nDo You Want To Order Another Product ? (y/n)";
	cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You For Placing The Order";
    getch();
    clrscr();
    cout << "\n\n******************************** RECIPT ************************\n";
    cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
    for (int x = 0; x <= a; x++)
    {
	fp.open("Shop.dat", ios:: in );
	fp.read((char * ) & pr, sizeof(product));
	while (!fp.eof())
	{
	    if (pr.pno == order[x])
	    {
		amt = pr.price * quant[x];
		damt = amt - (amt * pr.dis / 100);
		cout << "\n" << order[x] << "\t" << pr.name <<
		    "\t" << quant[x] << "\t\t" << pr.price << "\t" << amt << "\t\t" << damt;
		total += damt;
	    }
	    fp.read((char * ) & pr, sizeof(product));
	}

	fp.close();
    }
    cout << "\n\n\t\t\t\t\tTOTAL = " << total;
    getch();
}
void product::admin_menu()
{
    clrscr();
    char ch2;
    cout << "\n\n\n\tADMIN MENU";
    cout << "\n\n\t1.CREATE PRODUCT";
    cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
    cout << "\n\n\t3.SEARCH FOR A SPECIFIC PRODUCT ";
    cout << "\n\n\t4.MODIFY PRODUCT";
    cout << "\n\n\t5.DELETE PRODUCT";
    cout << "\n\n\t6.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-6) ";
    ch2=getche();
    clrscr();
    switch (ch2)
    {
    case '1':
	write_product();
	break;
    case '2':
	display_all();
	break;
    case '3':
	int num;
	clrscr();
	cout << "\n\n\tPlease Enter The Product No. ";
	cin >> num;
	display_sp(num);
	break;
    case '4':
	modify_product();
	break;
    case '5':
	delete_product();
	break;
    case '6':
	break;
    default:
	cout << "Wrong Choice Enter Again!";
	admin_menu();
    }
}
void intro();
void main()
{
    char ch;
    while(1)
    {   intro();
	clrscr();
	cout << "\n\n\n\tMAIN MENU";
	cout << "\n\n\t01. CUSTOMER";
	cout << "\n\n\t02. ADMINISTRATOR";
	cout << "\n\n\t03. EXIT";
	cout << "\n\n\tPlease Select Your Option (1-3) ";
	ch=getche();
	switch (ch)
	{
	case '1':
	    clrscr();
	    pr.cust_menu();
	    getch();
	    break;
	case '2':
	    pr.admin_menu();
	    break;
	case '3':
	    exit(0);
	default:
	    exit(0);
	}
    }
}
void intro()
{
clrscr();
cout<<"\t\t\tSUPERMARKET BILLING PROJECT\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
cout<<"\t\t\t\t\t\tPROJECT MADE BY-"<<endl;
cout<<"\t\t\t\t\t\tUDAY PRATAP SINGH";
getch();
}
