#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;


vector<unordered_map<string, string>> items;

void user_choice();
void add_item(string report_type);
void match_items(unordered_map<string, string>& items);
void search_items();
void view_matches();

void save_data(){
    json j;

    for(auto &item : items){
        j.push_back(item);
    }

    ofstream file("data.json");
    file << j.dump(4);
    file.close();
    
}

void load_data(){
    ifstream file("data.json");

    if (!file.is_open()) return;

    items.clear();

    json j;
    file >> j;

    for(auto &element : j){
        unordered_map<string, string> item;

        for(auto &pair : element.items()){
            item[pair.key()] = pair.value();
        }

        items.push_back(item);
        save_data();
    }

    file.close();                       
}
void display_menu(){
    cout << "\nDIGITAL LOST AND FOUND BULLETIN\n";
    cout << "===============================\n";
    cout << "1. Report Lost Item\n";
    cout << "2. Report Found Item\n";
    cout << "3. Search Item\n";
    cout << "4. View Matches\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
    save_data();
}

void user_choice(){
        int choice;
      
        do
        {
            cin >> choice;
            switch (choice)
            {
            case 1: 
                add_item("Lost");
                break;
            case 2:
                add_item("Found"s);
                break;
            case 3:
                search_items();
                break;
            case 4: 
                view_matches();
                break;
            case 5:
                cout << "Exiting Program.";
                break;
            
            default:
                cout << "Invalid Choice, Choose again.\n";
                break;
            }
        } while (choice != 5);
        
}

void search_items(){
    string keyword;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter item name to search: ";
    getline(cin, keyword);

    bool found = false;

    for(auto &item : items){
        if(item["name"].find(keyword) != string::npos){
            cout << "\nType: " << item["report_type"]
                 << "\nName: " << item["name"]
                 << "\nCategory: " << item["category"]
                 << "\nLocation: " << item["location"]
                 << "\nStatus: " << item["status"]
                 << "\n------------------------\n";
            
            found = true;
        }
    }

    if(!found){
        cout << "No items found.\n";
    }

}

void add_item(string report_type){
    unordered_map<string, string>item;

    string name, category, location, description, date;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter item name: ";
    getline(cin, name);

    cout << "Enter item category: ";
    getline(cin, category);

    cout << "Enter item location: ";
    getline(cin, location);

    cout << "Enter item description: ";
    getline(cin, description);

    cout << "Enter item date: ";
    getline(cin, date);

    item["report_type"] = report_type;
    item["name"] = name;
    item["category"] = category;
    item["location"] = location;
    item["description"] = description;
    item["date"] = date;
    item["status"] = "unclaimed";

    items.push_back(item);

    match_items(items.back());
    cout << "\nItem successfully added to bulletin.\n";
}

void match_items(unordered_map<string, string>& newItem){
    for(auto &item : items){
        if (&item == &newItem) continue;

        if(item["name"] == newItem["name"] &&
            item["category"] == newItem["category"] ||
            item["description"] == newItem["description"] &&
            item["report_type"] != newItem["report_type"]
        ){
            item["status"] = "Matched";
            newItem["status"] = "Matched";
        }
    }
}

void view_matches(){
    bool found = false;

    for(auto &item : items){
        if(item["status"] == "Matched"){
            cout << "\n[ MATCHED ]\n";
            cout << "Type of report: " << item["report_type"]
                 << "\nName: " << item["name"]
                 << "\nCategory: " << item["category"]
                 << "\nLocation: " << item["location"]
                 << "\nDescription: " << item["description"]
                 << "\nDate: " << item["date"]
                 << "\nStatus: " << item["status"]
                 << "\n------------------------\n";

            found = true;
        }
    }

    if(!found){
        cout << "\nNo matched items found.\n";
    }

}

int main(){
    load_data();  

    int choice;
    
    do
    {
        display_menu();
        cin >> choice;
        switch (choice)
        {
        case 1: 
            add_item("Lost");
            break;
        case 2:
            add_item("Found"s);
            break;
        case 3:
            search_items();
            break;
        case 4: 
            view_matches();
            break;
        case 5:
            cout << "Exiting Program.";
            break;
        
        default:
            cout << "Invalid Choice, Choose again.\n";
            break;
        }
    } while (choice != 5);
    
}