#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include<iomanip>

using namespace std;
using namespace std::chrono;
using namespace std::filesystem;

class atm
{
public:
    int account;
    float balance;
    int password;

    atm()       // constructor for check the existance of my file
    {
        if (!exists("account.txt"))
        {
            cout << "Please contact  the Bank";
        }
        if (!exists("history.txt"))     // opening history.txt to save transaction history
        {
            ofstream newfile("history.txt");
        }
    }

    string time()   //for time
    {
        time_t now = ::time(0);
        tm* ltm = localtime(&now);
        
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%d %b %Y  %I:%M %p", ltm); 
        
        return buffer;
    }

    bool check_password(int acc) // using this for matchpassword
    {
        int i = 4;
        while (i >= 0)
        {
            string user_pass;
            cout << "Enter Your 4 digit Secret PIN: ";
            cin >> user_pass;

            string pass;

            string line;
            ifstream file("account.txt");
            getline(file, line);
            while (file >> account >> pass >> balance)
            {
                if (acc == account and user_pass == pass and user_pass.size()==4)
                {
                    return true;
                    break;
                }
                else if (acc == account and user_pass.size()==4 and user_pass != pass)
                {
                    cout << "Incorrect PIN!" << endl;
                    cout << "Careful,You have only " << i << " attempts left!" << endl;
                }
                else if(acc == account and user_pass != pass and user_pass.size()!=4)
                {
                    cout<<"Please enter your 4 digit password"<<endl;
                    cout << "Careful,You have only " << i << " attempts left!" << endl;

                }
                
            }
            file.close();
            i--;
        }
        return false;
    }

    int log_in() //log in using id and password.
    {
        while (true)
        {
            int user_id;
            cout << "Enter Your Account Number: ";
            cin >> user_id;

            bool id_found = false;

            ifstream filez("account.txt");
            string line;
            getline(filez, line);

            while (filez >> account >> password >> balance)
            {
                if (user_id == account)
                {
                    bool pass_dici=check_password(user_id); //calling check_password function and check. 
                    if (pass_dici)
                    {
                        return user_id;     //will run if fucntion returns the account id.
                        id_found=true;
                    }
                    else 
                    {
                        cout<<"Session Blocked! Try again later. Goodbye!"<<endl;     //will run if fucntion returns false.
                    }
                    id_found=true;      //if log in successful make it ture
                }
            }
            filez.close();
            
            if(!id_found) {cout<<"Account Dose Exist"<<endl; return -1;}      //checking if log in successful or not
        }
    }
     
    void user_balance() // check user balance
    {
        int check=log_in();     //storing the return value of log_in function.

        ifstream file("account.txt");
        string line;
        getline(file,line);

        while(file>>account>>password>>balance)
        {
            if(check==account)      // finding the account to show the balance.
            {
                cout<<"Your total amount is: "<<balance<<endl;
                break;
            }
        }
    }
    
    void user_deposit() //for diposit
    {
        int check=log_in();
        float user_bal;
        bool deposit=false;
        
        ifstream file("account.txt");
        string line;
        getline(file,line);

        ofstream temp("temp.txt");
        temp<<line<<endl;

        ofstream his("history.txt", ios::app);

        while(file>>account>>password>>balance)
        {
            if(check==account)
            {
                cout<<"Enter Amount: ";
                cin>>user_bal;

                temp<<account<<"\t"<<password<<"\t"<<balance+user_bal<<endl;

                his<<account<<"\tDeposit amount: "<<user_bal
                   <<"\tTotal Balance: "<<balance+user_bal
                   <<"\t\t"<<time()<<endl;

                deposit=true;
            }
            else
            {
                temp<<account<<"\t"<<password<<"\t"<<balance<<endl;
            }
        }
        file.close();
        temp.close();
        his.close();

        if(deposit) {cout<<"Cash Deposited Successfully!"<<endl;}
        else {cout<<"Deposit Failed!"<<endl;}

        remove("account.txt");
        rename("temp.txt","account.txt");
    }
    
    void user_withdraw()
    {
        int check=log_in();
        float user_bal;
        bool withdraw=false;
        
        ifstream file("account.txt");
        string line;
        getline(file,line);

        ofstream temp("temp.txt");
        temp<<line<<endl;

        ofstream his("history.txt", ios::app);


        while(file>>account>>password>>balance)
        {
            if(check==account)
            {
                cout<<"Your total balance is: "<<balance<<endl;
                
                cout<<"Enter Amount: ";
                cin>>user_bal;        

                if(user_bal<=balance)
                {
                    temp<<account<<"\t"<<password<<"\t"<<balance-user_bal<<endl;

                    his<<account<<"\tWithdraw amount: "<<user_bal
                       <<" \tTotal Balance: "<<balance-user_bal<<
                       "\t\t"<<time()<<endl;

                    withdraw=true;
                }
                else 
                {
                    temp<<account<<'\t'<<password<<"\t"<<balance<<endl;
                    withdraw=false;
                }
            }

            else
            {
                temp<<account<<" "<<password<<" "<<balance<<endl;
            }
        }
        file.close();
        temp.close();
        his.close();

        if(withdraw) {cout<<"Please Collect Your Cash!"<<endl;}
        else {cout<<"Transaction Failed! Insufficient Balance."<<endl;}

        remove("account.txt");
        rename("temp.txt","account.txt");
    }

   void user_history() 
   {
    
    int check=log_in();

    ifstream file("history.txt");
    string word2, word3, word4, word5;
    int total_bal;

    bool history=false;

    while(file>>account)
    {
        if(check==account)
        {
            file.ignore();
            string line1,line2,time;
            getline(file,line1,'\t');
            getline(file, line2,'\t');
            file.ignore();
            file.ignore();
            getline(file,time);

            cout<<line1<<"\t"<<line2<<"\t"<<"Time: "<<time<<endl;
            history=true;
        }
    }
    if(!history)
    {
        cout<<"You have not done any transaction yet!"<<endl;
    }

   }
    
};

int main()
{
    int i=0;
    while(i<5)
    {
    atm obj;
    
    cout<<"\n::: Welcome to Smart ATM Simulator :::"<<endl;
    cout<<" "<<"1. Check Balance"<<endl;
    cout<<" "<<"2. Deposit"<<endl;
    cout<<" "<<"3. Withdraw"<<endl;
    cout<<" "<<"4. Check Transaction history"<<endl;
    cout<<" "<<"5. Exit"<<endl;


    int x;
    cout<<"Enter: ";
    cin>>x;

    switch(x)
    {
        case 1: obj.user_balance(); break;
        case 2: obj.user_deposit(); break;
        case 3: obj.user_withdraw(); break;
        case 4: obj.user_history(); break;
        case 5: cout<<"Thank you for banking with us! Have a great day!"<<endl; break;
        default: cout<<"Please enter a valid number!"<<endl; break;
    }
    if(x==5) {break;}

    }
    i++;
}