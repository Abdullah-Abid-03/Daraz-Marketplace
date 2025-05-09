#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include<cmath>
#include <filesystem>

using namespace std;



class User {
protected:
    std::string name;
    std::string email;
    std::string password;

    void setName() {
        cout << "Enter Your Name = ";
        cin.ignore();
        getline(cin, name);
    }
    string getName() {
        return name;
    }
    void setEmail() {
        cout << "Enter Email Address  = ";
        cin.ignore();
        getline(cin, email);
    }
    string getEmail() {
        return email;
    }
    void setPassword() {
        cout << "Enter 8 Digit Password = ";
        cin >> password;
    }
    string getPassword() {
        return password;
    }
public:
    User() {

    }


    virtual void SignUp() = 0;  // pure virtual function
};

class Product {
public:
    string prod_id;
    string prod_name;
    double prod_price;
    int prod_quant;
    string category;


public:
    Product() {
        //default constructor
    }

    Product(string id, string name, float price, int quantity) {
        prod_id = id;
        prod_name = name;
        prod_price = price;
        prod_quant = quantity;

    }

    void setId(string id) {
        prod_id = id;
    }
    void setName(string name) {
        prod_name = name;
    }
    void setPrice(double price) {
        prod_price = price;
    }
    void set_quantity(int stock) {
        prod_quant = stock;
    }

    string getId() {
        return prod_id;
    }
    string getName() {
        return prod_name;
    }
    double getPrice() {
        return prod_price;
    }
    int get_quantity() {
        return prod_quant;
    }

    //void add_stocks() {
    //    int num;
    //    cout << "Enter the product quantity to be updated = ";
    //    cin >> num;
    //    prod_quant += num;
    //    //cout << "Total Stock for the product is = " << prod_quant << endl;
    //}

    string ProductCategory() {
        int count = 1;
        cout << "Enter your Product Category = ";
        cin.ignore();
        getline(cin, category);
        ofstream cat("Categories.txt", ios::out | ios::app);
        cat << endl;
        count++; // for serial number of categories, laso to find out total categories.
        cat << count << "- " << category << endl;

        cat.close();

        return category;
    }


    void add_products() {
        vector<Product> products;  // Vector to store product details


        while (true) {
            cout << endl << "Enter product details (or enter NULL to stop):\n";

            // Temporary product to store user input
            Product tempProduct;


            cout << "Product ID: ";
            cin >> tempProduct.prod_id;


            if (tempProduct.prod_id == "NULL" || tempProduct.prod_id == "null") {
                break;
            }

            cout << "Product Name: ";
            cin.ignore();
            getline(cin, tempProduct.prod_name);

            cout << "Product Price: ";
            cin >> tempProduct.prod_price;

            cout << "Product Stock: ";
            cin >> tempProduct.prod_quant;

            // Add the product to the vector
            products.push_back(tempProduct);
        }


        // Save product details to a file
        string category_file;
        ofstream outfile;
        category_file = category + ".txt";
        outfile.open(category_file.c_str(), ios::out | ios::app);  // Open the file in append mode

        if (outfile.is_open())
        {
            outfile << setw(30) << category << endl;
            outfile << setw(30) << "       ================" << endl << endl;
            for (size_t i = 0; i < products.size(); ++i) {
                // Write product details to the file
                outfile << "PRODUCT ID = " << products[i].prod_id << left << setw(20) << "  " << " PRODUCT NAME = " << products[i].prod_name << left << setw(20) << "  " << " PRODUCT PRICE = " << products[i].prod_price << fixed << setprecision(2) << left << setw(20) << "  " << " PRODUCT STOCK = " << products[i].prod_quant << left << '\n';

            }

            outfile.close();
            cout << endl << "Product details saved to file.\n";
            //cout << "Want to add more products:- ";
        }
        else {
            cout << "Unable to open the file for writing. This Category already exist.\n";
        }

    }

};


class Seller : public User {

private:
    int ID, i;
    string Id, confirm, seller_file_name;
    Product prod;  // Private Composition. Product class and its object. B/c Seller HAS the Products.


public:
    Seller() {

        srand(time(NULL));

    }


    void SignUp() {
        cout << endl << "Enter the SignUp Details: " << endl;
        cout << " ==========================" << endl;
        // Name of the seller jis ki file bany gi..
        setName();
        // writing seller details to the file
        ofstream sell;

        // Id += name[0] + name[name.length()-1]; this gives error, b/c it performs on the ASCII values and when it adds ASCII values it results in a new character.
        Id += name[0];
        ID = rand();
        stringstream ss;  // to convert integer into string to append 1st and last character of the name to the ID.
        ss << ID;
        Id += ss.str();
        Id += name[name.length() - 1];
        cout << "Your Seller ID = " << Id << " (*Remeber Seller ID for future Login.)" << endl << endl;
        seller_file_name = Id + ".txt"; //file is created by the Unique seler id b/c of uniqueness.
        sell.open(seller_file_name.c_str(), ios::out);
        sell << "NAME = " << getName() << endl;
        sell << "Seller ID = " << Id << endl;

        //Email address = ";
        setEmail();

        while (true) {
            if (email.find('@') != string::npos) {
                // Password = ";
                setPassword();
                while (getPassword().length() < 7 || getPassword().length() == 7) {
                    cout << "Enter again, Password must be 8 digits or greater = ";
                    cin >> password;  // protected in Abstract class, hence directly set.
                }
                cout << "Valid Email and Password. Now Proceed further." << endl;
                break;

            }
            else {
                cout << "Incorrect Email. Enter Again. ";
                cin >> email;  // protected in Abstract class, hence directly set.
            }

        }
        sell << "EMAIL ID = " << email << endl;
        sell << "PASSWORD = " << password << endl << endl << endl;


        cout << "Enter your Seller ID again for authentication = ";
        cin >> confirm;
        while (Id.compare(confirm) != 0) {
            cout << "Wrong Seller ID. Enter Again. :- ";
            cin >> confirm;
        }
        cout << "\n Account created...\a\a\a\a\a" << endl;
        cout << "=======================================================" << endl << endl;
        system("cls");
        cout << "Enter your Products Information. " << endl << endl;
        cout << endl << setw(30) << prod.ProductCategory() << endl;
        sell << "Category =  " << prod.ProductCategory() << endl << endl;
        prod.add_products(); // products category kii file mein add hongi.



        sell.close();
    }

    void Login() {
        int choice, num;
        string confirm, sellerfile, info, cat, categoryFile, reading;
        cout << "Enter your Seller ID correctly = ";
        cin >> confirm;
        ifstream read;
        sellerfile = confirm + ".txt";  // concatenating the file name with .txt mode.
        read.open(sellerfile.c_str(), ios::in);
        while (true) {
            if (read.is_open() != 0) {
                while (getline(read, info)) {
                    cout << info << endl;
                }
                read.close(); // close the user file
                // search for the file name, if the file name found then read email and Seller ID and display products category and then user select the categroy then show the respective items to console ;
                cout << "Enter your product category = ";
                cin.ignore();
                getline(cin, cat);
                categoryFile = cat + ".txt";
                cout << " 1)View Product " << endl; // **add product.  this option can seller do by him self directly
                // ** remove product, update product
                // **for the above options, seller should contact admin  to do these operations and updated one should be in file.
                cout << "Select the option = ";
                cin >> choice;
                if (choice == 1) {
                    cout << endl;
                    read.open(categoryFile.c_str(), ios::in);
                    while (read.eof() == 0) {
                        getline(read, reading);
                        cout << reading << endl;
                    }
                    read.close();
                    exit(0);
                }
                

            }
            else if (read.is_open() == 0) {
                cout << "File Does not Exist OR ID is not written correclty" << endl;
                cout << "Enter (1) to enter the Correct the Seller ID or (2) SignUp first to creat account = ";
                cin >> choice;
                if (choice == 1) {
                    Login();
                }
                else if (choice == 2) {
                    SignUp();
                }
            }

        }


    }


    ~Seller() {

    }
};


class Customer : public User {  // Customer is-a user
private:
    int OTP, recieved;
    string confirm;
    Product buy_product; // private composition (has-a)

public:
    Customer() : User() {

    }
    //USer name


    void SignUp() {
        string buyer_file_name;
        cout << endl << "Enter the SignUp Details: " << endl;
        cout << " ==========================" << endl;
        //Enter Name;
        setName();
        //Enter your email address ;
        setEmail();
        ofstream buy;
        buyer_file_name = getName() + ".txt";
        buy.open(buyer_file_name.c_str(), ios::out); /* This converts the contents of the string object buyer_file_name
                                                    into a C-style string (const char*) that can be used as the file name.*/
        buy << "NAME = " << getName() << endl;


        while (true) {
            if (email.find('@') != string::npos)  /*find() function returns the position of the first occurrence of the substring in the string,
                and npos is used to indicate the absence or failure of a specific value or position, especially when searching within strings.*/
            {

                setPassword();
                while (getPassword().length() < 8) {
                    cout << "Enter again, Password must be 8 digits or greater= ";
                    setPassword();  // protected in Abstract class, hence directly set.
                }
                break;

            }
            else {
                cout << "Incorrect Email. Enter Again. ";
                cin >> email;  // protected in Abstract class, hence directly set.

            }
        }


        srand(time(0));
        OTP = rand();
        cout << "OTP = " << OTP << endl;
        cout << "Enter OTP recieved on Mobile or Email = ";
        cin >> recieved;
        while (OTP != recieved) {
            cout << "Wrong OTP. Enter again = ";
            cin >> recieved;
        }
        buy << "OTP = " << recieved << endl;
        buy << "EMAIL = " << getEmail() << endl;
        buy << "PASSWORD = " << getPassword() << endl;

        time_t now = time(0);

        // convert now to string form using ctime_s
        char date_time[26]; // ctime_s requires a buffer of at least 26 characters
        if (ctime_s(date_time, sizeof(date_time), &now) != 0) {
            cout << "Error converting time." << std::endl;

        }

        cout << " date and time is: " << date_time << std::endl;
        buy << endl << endl;
        buy << " date and time is: " << date_time << endl;


        add_to_cart(buyer_file_name);
        buy.close();
    }

    void add_to_cart(string buyer_file_name) {
        int total_products = 0, quantity, i, total_cost = 0;
        string selected_category, category_reading, product_reading, purchased_ID, confirm_ID, display, opened, useless, product_name;
        float purchased_price;
        double total_price;

        ifstream category_read;
        category_read.open("Categories.txt", ios::in);
        if (category_read) {
            while (getline(category_read, display)) {
                cout << display << endl;
            }
            category_read.close(); // category file closed.
            cout << "Select the category from the above = ";
            cin.ignore();
            getline(cin, selected_category);
            cout << endl;
            ifstream product_file; //open that category file for displaying products.
            opened = selected_category.append(".txt");
            //opened.append(".txt");
            product_file.open(opened, ios::in);
            if (product_file.is_open()) {
                getline(product_file, useless);
                while (product_file.eof() == 0) {
                    getline(product_file, product_reading);
                    cout << product_reading << endl;
                    //display products to the console.
                }
                product_file.close();
                product_file.open(opened, ios::in);
                if (product_file.is_open() == 1) {
                    product_file.close();

                    while (purchased_ID != "null") {
                        cout << "Enter (correct) Product ID to be purchased OR null if the purchasing is done =  ";
                        cin >> purchased_ID; //user will input product ID what he want purchased. then this ID will be compared to the ID which is in the file.
                        product_file.open(opened, ios::in);
                        getline(product_file, useless);
                        while (product_file.eof() == 0) {
                            getline(product_file, useless, '=');
                            product_file >> confirm_ID; // reading after = sign to read the ID, if the ID matched then goes inside the if-statement.
                            if (purchased_ID == confirm_ID) {
                                getline(product_file, useless, '=');
                                product_file >> product_name; // storing  the product name 
                                getline(product_file, useless, '=');
                                // after 2 is equals to sign it will get the price of the product.
                                product_file >> purchased_price;
                                cout << "Enter the quantity of the product = ";
                                cin >> quantity; /// Quantity of that pirticular product
                                total_products += quantity; // total number of products.
                                //open the same customer file in appended mode and store his product details reepectively.
                                ofstream buy_product;  // buyer_file_name already appended with .txt in the signup().
                                buy_product.open(buyer_file_name, ios::app);

                                buy_product << "ID =  " << confirm_ID << endl;
                                buy_product << "Product NAme = " << product_name << endl;
                                buy_product << "Quantity = " << quantity << endl;
                                buy_product << "Price of the product = " << purchased_price << endl;
                                buy_product << "Cost = " << quantity * purchased_price << endl << endl;
                                total_cost += (quantity * purchased_price);
                                buy_product.close();
                                cout << "==>> Product is added to the cart!!. " << endl << endl;

                                break;
                            }
                            else if (product_file.eof() != 0 && purchased_ID != confirm_ID) {
                                cout << "This product is not available right now." << endl << endl;
                                product_file.close();
                                break;
                            }
                            getline(product_file, useless, '\n'); // skipping the line when the desired ID is found.
                        }//while loop inside for-loop ends here.
                        product_file.close();
                    }//outer while loop ends
                }
            }
            else {
                cout << "Product file not opened. \n";
            }
        }
        ofstream buy_product; // here we have to open the file again for in appended mode b/c once the previous stream goes out of scope, it will be automatically closed if we do not close the file 
        buy_product.open(buyer_file_name, ios::app);
        buy_product << "FINAL BILL TO BE PAID : " << endl;
        buy_product << " Total products = " << total_products << endl;
        buy_product << "Total Cost = " << total_cost << endl;
        buy_product << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;

        buy_product.close();
        Payment_Options(buyer_file_name, total_cost);




    }
    void Login() {
        string customer_file, check, check_name, file_read, verify_OTP, OTP, check_OTP, original;
        int option;
        cout << "Enter your Name of the file = ";
        cin.ignore();
        getline(cin, customer_file);
        
        cout << endl << " 1) View cart\n 2)Add to Cart\n ";
        cout << "Select the option: ";
        cin >> option;
        cout << endl;
        if (option == 1) {
            // file will be opened in reading mode only to only view.

            ifstream read_customer;
            customer_file.append(".txt");
            read_customer.open(customer_file.c_str(), ios::in);
            if (read_customer.is_open()) {
                cout << "Your file details are below::" << endl << endl;
                while (read_customer.eof() == 0) {
                    getline(read_customer, file_read);
                    cout << file_read << endl;
                }



            }
            else {
                cout << "Customer does not exist." << endl;
            }
            read_customer.close();
            cout << endl;


        }
        else if (option == 2) {
            //since this is a login() here file will be opened in append mode so that previou details remains saved and new will be saved.
            customer_file.append(".txt");
            add_to_cart(customer_file);
        }
        else {
            cout << "Sorry, No option available." << endl;
        }



    }

    void Payment_Options(string buyer_file_name, double payable) {
        int option;
        cout << "PAYMENT OPTIONS" << endl << endl;
        ofstream bill;
        
        cout << "\n 1)Cash on Delivery \n 2)Online Payment Option \n";
        cout << "Select the payment option:- ";
        cin >> option;

        switch (option)
        {
        case 1:
        {
            double amount;
            bill.open(buyer_file_name, ios::app);
            cout << "Enter the total amount to be paid = ";
            cin >> amount;
            if (payable == amount) {
                bill << "Amount paid on COD = " << payable << endl;
                bill << "------------------------------------------------" << endl << endl;
                bill.close();
                cout << "Amount Recieved." << endl;
            }
            else if(payable >= amount){
                amount -= payable;
                cout << "Amount Recieved = " << payable << endl;
                bill.close();
            }
            
            break;
        }
        case 2:
        {
            long int deposit;
            string account_num, choice, code;
            bill.open(buyer_file_name, ios::app);
            bill << "Amount paid online = ";
            cout << "Enter account Number = ";
            cin >> account_num;
            bill << account_num << endl;
            cout << "Amount to be paid = " << payable << endl;
            bill << "Amount to be paid = " << payable << endl;;
            cout << "Amount in your Account ?  ";
            cin >> deposit;
            if (deposit >= payable) {
                cout << "Do you have discount code (yes/no)= ";
                cin >> choice;
                if (choice == "yes" || choice == "Yes") {
                    cout << "Enter the discount code = ";
                    cin >> code;
                    cout << "Amount ot be paid = " << Paid(deposit, payable, code) << endl;
                    bill << "Amount ot be paid with discout = " << Paid(deposit, payable, code) << endl;
                    bill.close();
                }
                else if (choice == "No" || choice == "no") {
                    cout << "Amount paid = " << Paid(deposit, payable) << endl;
                    bill << "Amount paid without discount = " << Paid(deposit, payable) << endl;
                    bill.close();
                }
               
            }
            else {
                cout << "Your Account does not enough balance. Deposit money in the account." << endl;

            }

            break;

        }
        default:
            cout << "No othher option available right now. ";
            break;
        }
    }
    double Paid(long int deposit, double payable, string code) {
        cout << "50% discounted on total payable bill." << endl;
        payable *= 0.5;
        deposit -= payable;
        cout << "Reamianing balaance in account = " << deposit << endl;
        return payable;
    }
    double Paid(long int deposit, double payable) {
        
         deposit -= payable;
         cout << "Remaining Amount in your account = " << deposit << endl;
         return payable;

    }
    ~Customer() {

    }
};

class Admin  {
private:
    string name;
    string password;
    Seller sold;
    Customer bought;

public:

    
    
    void removeSeller(string seller_file_name) {
        string sellerFile = seller_file_name + ".txt"; // Assuming seller files are named with their IDs
        if (remove(sellerFile.c_str()) != 0) {
            cout << "Error deleting seller " << seller_file_name << endl;
        }
        else {
            cout << "Seller " << seller_file_name << " removed successfully" << endl;
        }
    }

    

    void SignUp() {
        string admin_name, admin_pass, name_read, check_name; // Your admin username
        ifstream admin("Admin.txt",  ios::in); //only reading 
        cout << "Enter admin user name = ";
        cin >> admin_name;
        cout << "Enter Admin Password = ";
        cin >> admin_pass;
        getline(admin, name_read, '=');
        check_name = name_read;
        admin >> name_read;

        // Validate username to grant access to admin functions
        if (admin) {// file open check
            if (admin_name == name_read) {
                cout << "Admin login successful!" << endl;
                // Provide access to admin functionalities
                int choice;
                cout << "What do you want to do?\n";
                cout << "1. Remove a seller\n";
                cout << "2. Other admin tasks...\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1: {
                    string sellerIDToRemove;
                    cout << "Enter the seller ID to remove: ";
                    cin >> sellerIDToRemove;
                    removeSeller(sellerIDToRemove);
                    break;
                }
                      // Add more cases for other admin tasks if needed
                      // ...
                      //else if (choice == 2) {
                //    string targetID, confirm;
                //    //searching for the file and update that product record.
                //    cout << "Enter the Product ID to be update the product = ";
                //    cin >> targetID;
                //    read.open(categoryFile.c_str(), ios::in);
                //    //now open file in reading mode and search the target ID to update it
                //    if (read) {
                //        while (getline(read, confirm)) {
                //            if (confirm == targetID) {
                //                bool found = true;
                //                break;
                //            }
                //        }
                //        /*cout << "Enter the updated information of the product  \n";
                //        cout << "Product ID = ";
                //        cin >> prod_id;
                //        cout << "Product name = ";
                //        cin >> name;
                //        cout << "Product Stock = ";
                //        cin >> stock;*/

                //    }
                //    else if(!read){
                //        cout << "File does not exist" << endl;
                //    }
                //}
                //else if (choice == 3) {
                //    cout << "How many products to be added = ";
                //    cin >> num;
                //    read.open(categoryFile.c_str(), ios::app);
                //        for (i = 1; i < num; i++) {
                //            // manually write the whole

                //    }//for loop ends

                //        read.close();
                //}
                /*this all should be managed in the Admin class for the Seller.*/





                default:
                    cout << "Invalid choice";
                    break;
                }
            }
            
        }
        else {
            cout << "Access denied! Not an admin user." << endl;
        }
    }
    
};
int main() {
    int n;
    string type, ans;

    cout << setw(53) << " =========================" << endl;
    cout << setw(52) << " ||                   ||" << endl;
    cout << setw(53) << " ||ONLINE MARKET PLACE|| " << endl;
    cout << setw(52) << " ||                   ||" << endl;
    cout << setw(54) << "==========================" << endl
        << endl;

    cout << "\n\n Select Your Type :- \n  -Seller\n -Customer\n " << endl;
    system("pause > 0");
    while (true) {
        cout << "Enter type = ";
        cin >> type;

        //if (type == "Admin" || type == "admin") {
        //    /*string seller_deleted;
        //    Admin admit;
        //    cout << "Enter seller file name to be deleted = ";
        //    cin >> seller_deleted;
        //    admit.removeSeller(seller_deleted);*/


        //}
         if (type == "Seller" || type == "seller") {

            Seller sell; // object of Seller

            cout << "Are You the new Seller (Yes/No) = ";
            cin >> ans;
            if (ans == "Yes" || ans == "yes") {
                sell.SignUp();

            }
            else if (ans == "No" || ans == "no") {
                sell.Login();
            }
            break;
        }
        else if (type == "Customer" or type == "customer") {
            Customer customer;

            cout << "Are You the new Customer (Yes/No) = ";
            cin >> ans;
            if (ans == "Yes" || ans == "yes") {
                customer.SignUp();
                //when he signup means that he is a new customer so diplay add_to_cart() so that his details will be store to his file.

            }
            else if (ans == "No" || ans == "no") {
                customer.Login();
            }
            break;

        }
        else {
            cout << "Invalid Choice!!! Try Again. Enter 0 to exit and 1 to continue. : ";
            cin >> n;
            if (n == 0) {
                break;
            }
        }
    }
    cout << endl << endl << setw(50) << "******>THANK YOU FOR USING PLATFORM<******," << endl;
    return 0;
}
