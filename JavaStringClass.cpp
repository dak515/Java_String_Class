#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
#include <map>
#include <iterator>
#include <stack>
#include <string.h>
#include <cstring>

using namespace std;

// Stores the number of references and the cstring received 
class StringData {
private:
	// Number of times each word was named
	int number_of_references;
	// The word itself
	const char* word;
public:
	// Constructor which receives the number of references of each word and the cstring
	StringData(int n, const char* w) {
		number_of_references = n;
		word = w;
	}
	// Destructor of the object
	~StringData(){
	} 
	// Accessor of private member (the cstring)
	char const* getWord(){
		return(word);
	}
	// Increments the number of references to each cstring
	void setReferences() {
		number_of_references++;
	}
	// Decrements the number of references
	void removeReferences() {
		number_of_references--;
	}
	// Accessor to return the value of the number of times each word was named
	int getReferences() {
		return(number_of_references);
	}
};

// StringTable class stores a vector of objects of type StringData
// This class is where all the important functions are defined and then
// called by the class MyString

class StringTable{
	private:
		// A static vector of objects of type StringData, each object stores the
		// number of references of a word and the word itself
		static vector<StringData> data;
		// Static pointer to object of type StringTable itself to make this a 
		// singleton class
		static StringTable *instance;
		// This variable remains 0 if both the new cstring matches a 
		// word already existing in the vector
		// The variable does not remain 0 if the new cstring doesn't
		// match any word from pre-existing words in the vector
		int check = 0;
	public:
		// If the instance is being created for the first time, create the object
		// otherwise point to the same already existing instance
		static StringTable* GetInstance()
		{
			if (instance == nullptr) {
				instance = new StringTable();
			}
			return instance;
		}

		// This function receives the string literal and returns the index in the vector at
		// which this word is stored
		int getIndex(const char* word){
			
			// If there are no elements in the vector, add the word and set number of
			// references to be 1
			if (data.size() == 0){
				data.push_back(StringData(1, word));
				return(0);
			}

			// If there already are elements in the vector
			else if (data.size() != 0)
			{   
				// Iterate through all elements in the vector
				for (int i = 0; i < data.size(); i++){
					// If the new word already exists in the vector, 
					// the following statement assigns 0 to integer variable check
					check = strcmp(word, data[i].getWord());
					// If check is equal to 0, break the loop
					// else continue checking
					if (check == 0){
						break;
					}
				}

				{ // If check is equal to 0, increase the number of
						// references to that word
					if (check == 0) {
						// The getInde(word) function gets index of the word
						// that already exists in the list
						//The getInde function is defined later in this class
						data[getInde(word)].setReferences();
						// Return the index of the word
						return(getInde(word));
					}
					

						// Else if check is not equal to 0
						// i.e., if the word is a new one that doesn't already exist
					else if (check != 0) {
						// Create an object of StringData that stores the new word and sets
						// the number of references to be 1
						StringData(1, word);
						// Store the object in the vector of objects
						data.push_back(StringData(1, word));
						// Return the index of the word that now finally exists in the vector
						return(getInde(word));
					}
				}
			}

		}

		// getInde is a function that receives a word
		// that already exists in the vector and returns the
		// index of that word
		int getInde(const char* ww) {
			for (int k = 0; k < data.size(); k++){
				int c = strcmp(data[k].getWord(), ww);
				if (c == 0){
					return(k);
				}
			}
		}

		// Accessor to return the word stored in a particular index in the vector
		const char* getStringLiteral(int ind) {
			return(data[ind].getWord());
		}

		// Print displays all the elements of vector
		void print() {
			for (int i = 0; i < data.size(); i++){
				if (data[i].getReferences() >= 1){
					cout << i << ' ' << data[i].getReferences() << ' ' << data[i].getWord() << endl;
				}
			}
		}

		// This function receives the index number of a word and
		// if the number of references of that word was greater than
		// 1 then decrement number of references
		// else if the number of references was equal to 1 then
		// then still drecrease number of references to 0
		void decrease(int dex){
			if (data[dex].getReferences() > 1){
				data[dex].removeReferences();
			}
			else if (data[dex].getReferences() == 1){
				data[dex].removeReferences();
				//StringData* ptr = &data[dex];
				//delete[] ptr;
				//ptr = nullptr;
				//data.erase(data.begin()+(dex));
			} 
		}
};

// Defining the aforementioned static variables outside of the class
StringTable* StringTable::instance = 0;
vector<StringData> StringTable::data;


// MyString class receives index of every word and 
// is capable of returning the string literal
// and printing the whole vector as well
class MyString {
	private:
		// Index of the word
		int index;
		// A static object of type StringTable
		static StringTable obj;
	public:
		// Constructor that receives a cstring and gets index of that word in the vector
		MyString(const char* word){
			index = obj.getIndex(word);
		}
		// Destructor calls for the decrease function
		~MyString(){
			obj.decrease(index);
		}
		// Returns the string literal
		const char* intern(){
			return(obj.getStringLiteral(index));
		}
		// Displays the vector
		static void displayPool(){
			obj.print();
		}

};

// Defining the static variable
StringTable MyString::obj;


int main() {

	// Test case
	MyString s0("hello");
	MyString s1("my");
		
	{ 
		MyString s2("world");
		  MyString::displayPool();    
		  cout << endl;  
	} 

	MyString::displayPool();
	cout << endl;
	MyString s3("hello");
	MyString s4("you");
	MyString * s5;
	MyString::displayPool();
	cout << endl;  
		
	{
		   s5 = new MyString("world");
		   MyString::displayPool(); 
		   cout << endl;  
	}  
		
	MyString s6("everyone");
	MyString::displayPool();
	cout << endl;
	delete s5;
	MyString::displayPool();
	cout << endl;
	MyString s7("Hello");
	MyString::displayPool();
	cout << endl;
	cout << "now print out all the strings:" << endl;
	cout << s0.intern() << endl;
	cout << s1.intern() << endl;
	cout << s3.intern() << endl;
	cout << s4.intern() << endl;
	cout << s6.intern() << endl;
	cout << s7.intern() << endl;

	system("pause");
	return(0);
} 
