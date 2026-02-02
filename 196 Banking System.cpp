#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;


struct User{
	string name;
	int accno;
	string password;
	double balance;
};

int capacity = 100;
int index = 0;
User* users = new User[capacity];


// i declared this first so thats why compiler wont give scope issues
int generate_accno();

void savetofile(){
	ofstream tofile;
	tofile.open("Bank Data.txt");
	
	for(int i=0;i<index;i++){
	tofile<<users[i].name<<endl;
	tofile<<users[i].accno<<endl;
	tofile<<users[i].password<<endl;
	tofile<<users[i].balance<<endl;
	tofile<<"------------------------------------------"<<endl;
	}
	
	tofile.close();
}

void loadfromfile(){
	
	ifstream fromfile;
	fromfile.open("Bank Data.txt");
	
	if(!fromfile)
	return;
       
       index =0;
       
	while(true){
	
	// created a object of type User structure	
		User u;
		
		if(!getline(fromfile,u.name))
		break;
		
		fromfile>>u.accno;
		
		fromfile.ignore();
		getline(fromfile,u.password);
		fromfile>>u.balance;
		
		fromfile.ignore();
		string ending_line;
		getline(fromfile,ending_line);
		
		// using array to store the object u 
		//post increment first stores then increments
		users[index++] = u;
	}
    fromfile.close();   	
}
void createacc(){
	
	if(index>=capacity){
		capacity *=2;
	  User* temp = new User[capacity];
         for (int i = 0; i < index; i++)
             temp[i] = users[i];
       delete[] users;
        users = temp;
	}
	
	
	bool istaken ;
	
 //initially we have 0 acc's so we take name's ,balance and other things for the first index 
	 
	cout<<"Enter Your Full Name :";
	
	// the statement below is used to clean the getline function to take correct input
	cin.ignore();
	getline(cin,users[index].name );   
	
	//randomly generated accno will be stored at this desired index
    users[index].accno =  generate_accno();
     
    do{
	
	istaken = false ;
    cout<<"Please create a pin of 4 (characters,digits) :";
    getline(cin , users[index].password);
	
	if(users[index].password.length() !=4){
		cout<<"\nPin must be 4 digit long!"<<endl;
		istaken = true;
		continue;
	}
    for(int i=0;i<index;i++){
    	if(users[index].password == users[i].password ){
		
    	cout<<"Password is already taken"<<endl;
    	istaken = true;
    	break;
	}
	
}
}
    while(istaken);
	
	cout<<"\n**********************************************************************\n";
	cout<<"                         Account Created Successfully                  \n";
	cout<<"**********************************************************************\n";  
	
	cout<<"\nYour name :"<<users[index].name<<endl;
	cout<<"Your Account no :"<<users[index].accno<<endl;
	
	cout<<"\n \"YOU MUST DEPOSIT SOME AMOUNT TO ACTIVATE ACCOUNT\" \n";
	
	users[index].balance = 0 ;
	
	index++;
	savetofile();
}

// this functiojn will generate radnom account no btw 10000 to 99999

int generate_accno(){
	bool istaken;
	int accno;
	
	do{
		istaken = false;
		
		//this keeps the random account no btw 10000 - 99999
		accno = rand() % 90000 + 10000;
		
	        for(int i = 0; i < index; i++) {
            if(users[i].accno == accno) {
                istaken = true;  // already exists
                break;
            }
        }
    } while(istaken);

    return accno;
}

/* whenever the user want to do any funtion that requires his accno 
ts function will be callled that will return the acc no's position so
user can enter password relative to that accno*/

int accountfinder( int accno){
	
	for(int i=0 ; i<index ; i++){
		if(users[i].accno== accno)
		return i;
	}
	return -1;
}


void depositbalance(){
	string pass;
	double amount;
	int accno;

	cout<<"Enter your Account No:";
	cin>>accno;
	
	int position = accountfinder(accno);
	
	if(position==-1){
	
	cout<<"Account not found!";
	return;
}
	cin.ignore();
	
   	  cout<<"Please enter your password :";
      getline(cin,pass);
	
		    if(pass==users[position].password){
	        cout<<"Enter the amount you want to deposit in your account (RS) :";
	        cin>>amount;
	        
	        if(amount < 100){
	        	cout<<"invalid amount !";
	        	return;
			}
	        
	        users[position].balance += amount;
	        
	        savetofile();
	        
	        cout<<"\nYour name :"<<users[position].name<<endl;
	        cout<<"Your Account no :"<<users[position].accno<<endl;
	        cout<<"Your deposited balance :"<<users[position].balance<<" Ruppees"<<endl;
	        return;
		}
	     	else{
		    cout<<"Incorrect Password !";
		    return;
	}
	}


void checkbalance(int position){
	string pass;
	
			cout<<"\nEnter Your Password :";
			cin.ignore();
			getline(cin,pass);
			if(pass==users[position].password){
			cout<<"\nYour balance is :"<< users[position].balance <<" Ruppees"<<endl;
	}
	    else
	    cout<<"Wrong Password!";
	    return;
}


//user withdraws money and if successful it also tell remaining balance 
void withdraw(int position){
	
	double amount ;
	string pass;
	
			cout<<"\nEnter Your Password :";
			cin.ignore();
			getline(cin,pass);
			if(pass==users[position].password){
				cout<<"\nEnter the amount to withdraw :";
				cin>>amount;
				
				if(amount<=0){
					cout<<"Invalid Ammount!";
					return;
				}
				if(amount> users[position].balance ){
					cout<<"Low balance ";
					return;
				}
					
				else if(amount<= users[position].balance){
					cout<<"\nWithdrawal Successful !"<<endl;
				 users[position].balance -= amount;
				 
				 savetofile();
					cout<<"\nYour Remaining balance is :"<<users[position].balance<<" Ruppees\n";
					return;
				}
			}
			else
			cout<<"Incorrect Password!";
			return;
    }

//this is for user panels
void user(){
	
	int choice;
	string name;
    
    do{
    	
    cout<<"\n 1- Enter 1 for creating account  :"<<endl;                    //taking the choice of user what he wants
    cout<<" 2- Enter 2 for depositing amount :"<<endl;
    cout<<" 3- Enter 3 for exiting           :"<<endl;

    cout<<"\n";
    cin>>choice;

       
    switch(choice){
    	
    	// i am calling different functions inside user panel function 
    	case 1:
    		//loops for the interface of this choice
    		
        cout<<"------------------------------Creating Account-----------------------------\n";
	   	createacc();  		
	    break;
	    
	    case 2 :
	    	
    		depositbalance();
			break;	
		 
		 case 3:
		 cout<<"\nThanku For creating an account ! See Ya\n ";
		 break;
		 
		 default:
		 cout<<"invalid choice !"<<endl;   		
		}
			
}
// loop will run until the user selects 3 after 3 the loop exits
    while(choice!=3);
}

void changepass(){
	
	string  pass;
	int accno;
	cout<<"Enter Your Account No :";
	cin>>accno;
	
	int position = accountfinder(accno);
	if(position == -1){
		cout<<"Account not found!\n";
		return;
	}
	        cin.ignore();
			cout<<"Enter Your previous Password :";
			getline(cin,pass);
			if(pass == users[position].password){
				cout<<"\nEnter new Password :";
				getline(cin, users[position].password);
				
				if(users[position].password.length() !=4){
	            	cout<<"\nPin must be 4 digit long!"<<endl;
		            return;
            	}
				cout<<"\nPassword Updated !" <<endl;
		        savetofile(); 
		         
				cout<<"\nName         : "<<" "<<users[position].name<<endl;
				cout<<" Account No    :"<<" "<<users[position].accno<<endl;				
			    cout<<" Balance       :"<<" "<<users[position].balance<<endl;
			}
			  else
			cout<<"Wrong Password !";
			return;
}

void login(){
	int accno , choice;
	string pass;
	
	cout<<"Enter Your Account No :";
	cin>>accno;
	
	int position = accountfinder(accno);
	if(position == -1){
		cout<<"Account not found!\n";
		return;
	}
			
			cin.ignore();
			cout<<"\n Enter Your password :";
		    getline(cin,pass);
		    
		    
		    
		    if(pass==users[position].password){
			
			cout<<"\n \n Welcome Back ! "<< "  "<< users[position].name<<"\n"<<endl;
			do
			{
			cout<<"\n 1- Enter 1 To change password         : "<<endl;                                       // user will login by entering his acc no and pass if correct further menu
			cout<<" 2- Enter 2 To add balance to account   : "<<endl; 
		    cout<<" 3- Enter 3 for checking balance        :"<<endl;
            cout<<" 4- Enter 4 for withdrawing money       :"<<endl;
            cout<<" 5- Enter 5 for exiting                 :"<<endl;                   
			cin>>choice;                                                                     //everthing nested in for loop and further nested in if condition
			                                                                        
			switch(choice){
				case 1 :
					changepass();
					break;
				case 2 :
					depositbalance();
					break;
				case 3 :
				    checkbalance(position);
				    break;
				case 4:
				    withdraw(position);  
				    break;
				    
				case 5:
					cout<<"\n    Good Bye !  "<<users[position].name<<endl;
					break;
				default :
				cout<<"Invalid choice !"<<endl;    
				
			     }
		 }
			while(choice!=5);
		}
		else {
		cout<<"Wrong Password !"<<endl;
		return;
	     }
}

//im sorting accounts accordingly their balances
// accounts with most balance will be displayed first
void sortingaccounts(){
	
	for(int i=0;i<index;i++){
		for(int j=i+1;j<index;j++){
			if(users[i].balance< users[j].balance)
			swap(users[i],users[j]);
		}
		
	}
	for(int k=0;k<index;k++){
		cout<<"\n Name         :"<<" "<<users[k].name<<endl;
		cout<<" Account No    :"<<" "<<users[k].accno<<endl;				
	    cout<<" Balance       :"<<" "<<users[k].balance<<endl;	
	}
	
}

//this function will delete a specific account on the basis of account no
void deletespecific(){
	
	int accno;
	cout<<"\nEnter the accno of account to delete:";
	cin>>accno;
	
	int position = accountfinder(accno);
	
	if(position==-1){
		cout<<"Account not found !";
		return;
	}
	
	// this will shift array to left by one such that one account is deleted
	for(int i=position;i<index-1;i++){
		users[i] = users[i+1];
	}
	index--;
	savetofile();
	
	cout<<"\n        Account deleted Successfully!!           "<<endl;
	for(int k=0;k<index;k++){
		cout<<"\n Name         :"<<" "<<users[k].name<<endl;
		cout<<" Account No    :"<<" "<<users[k].accno<<endl;				
	    cout<<" Balance       :"<<" "<<users[k].balance<<endl;	
	}
	
}

// this is for admin panel that will perform multiple actions
void admin(){
	string pass = "admin123";
	string enteredpass;
	int choice;
	
	//if pass matches it will display the admin panel
	cin.ignore();
	cout<<"Enter the password to access admin panel :";
	getline(cin,enteredpass);
	
	if(enteredpass==pass){
	
	cout<<"*************************   Welcome back admin !!   ******************************\n";
	
	do{
	
	cout<<"\nEnter 1 for sorting and displaying all accounts :";
	cout<<"\nEnter 2 for deleting an account                 :";
	cout<<"\nEnter 3 for deleting all accounts               :";
	cout<<"\nEnter 4 for viewing total amount in bank        :";
	cout<<"\nEnter 5 for exiting the panel                   :"<<endl;
	cin>>choice;
	
	switch(choice){
	
	    case 1:
	    	
		if(index==0){
			cout<<"Nothing to display! \n";
			return;
		}
		cout<<"\n-----------------   Displaying All Accounts    -------------------\n ";
		sortingaccounts();
		break;
		
	    case 2:
	         
	    deletespecific();
		break;
		
		// using {} because of cross intialization errors
		case 3:
		{
			
		cout<<"\n----------------       Deleting All Acccounts        --------------------\n";
		delete[] users;
        capacity = 100;
        index = 0;
        users = new User[capacity];
        
        ofstream clear("Bank Data.txt");
        clear.close();

        cout<<"Accounts Deleted Successfully ! ";
        break;
	 }
	    case 4:
	    {
				
	    	double sum =0;
	    	for(int i =0;i<index;i++){
	    		sum+= users[i].balance;
			}
	    	cout<<"\nTotal Amount in Bank is :"<<" "<<sum<<" Ruppees";
	    	break;
	   }
	    case 5:
	    	
	    	cout<<"\n   Good Bye Admin !!     \n";
	    	break;
	    	
		default:
		cout<<"Invalid Choice!";	
}
} while(choice!=5);

}
     
    else
    cout<<"Invalid Password !";
	return ; 
}


int main(){
	int menu ,choice, n;
	
	srand(time(0));
	loadfromfile();
	
	cout<<"********************************************************************\n";
	cout<<"                             MAIN MENU                              \n";
	cout<<"********************************************************************\n";
	
	do{
	cout<<"\nEnter 0 for admin panel   : "<<endl;
	cout<<"Enter 1 for user panel    : "<<endl;
	cout<<"Enter 2 for logging in    : "<<endl;
	cout<<"Enter -1 for exiting      : "<<endl;
	cin>>choice;

// nested switch in do while for user or admin panel
 switch(n){ 
	
	case 0 :
		admin();
		break;
		
	case 1 :
	    user();
	    break;
	    
	case 2 :
		login();
		break;    
		
	case -1 :
	
	cout<<"\nThanku For Using My BANK SYSTEM ! SEE YOU *_* ";
	break;
	
	default:
	cout<<"Invalid choice ! ";		
}
}
while( n!= -1);
	

		delete[] users;		
    	return 0;	
}
