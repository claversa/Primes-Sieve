/*******************************************************************************
 * Author      : Caroline LaVersa
 * Date        : 9/14/22
 *****************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit); //limit is last number, same as size of array

    ~PrimesSieve() { //destructor, takes apart arrays not needed anymore
    //when corresponding objedt disappear, this will remove the array because it would just stay in memory
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;


private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;


    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // displays the primes in the format specified in the requirements document.
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
    int endRow =1; //HAS TO BE 1 NOT 0
    for(int i = 2; i<=limit_;i++){
        if(is_prime_[i]==true){
            if(count_num_primes()<primes_per_row){ //just one line 
                if(i<max_prime_){ //not the last element
                    cout<<i<<" "; //space
                }
                else{ //last element
                    cout<<i; //NO SPACE 
                } 
            }
            else{ //more than 1 line
                if(i!=max_prime_){ //not the last element
                    if(endRow<primes_per_row){ //not last element in row
                        cout<<setw(max_prime_width)<<i<<" "; //space 
                        endRow++; //increments number of primes printed so far
                    }
                    else{//last in row
                        cout<<setw(max_prime_width)<<i<<endl; //NO SPACE, next line
                        endRow=1; 
                    }   
                }
                else{
                    cout<<setw(max_prime_width)<<i;
                }
            }
        }
    }
    
}

int PrimesSieve::count_num_primes() const {
    // counts the number of primes found
    int count=0;


    for(int i = 2; i<=limit_; i++){
        if(is_prime_[i]){
            count++;
        }
    }
    return count;
}

void PrimesSieve::sieve() {
    //by end all prime numbers in is_prime will be T, all composite will be F
    for(int i = 0; i<=limit_; i++){
        is_prime_[i]=true;
    }
    for(int i = 2;i<=sqrt(limit_);i++){
         if(is_prime_[i]){ //if element is set to true
            for(int j = pow(i,2); j<=limit_; j+=i){ //i^2, i^2+i, i^2+2i,...
                is_prime_[j]=false; //change to false
            }
         }

    }
    for(int i = limit_; i>=0;i--){ // start at top, find first element set to true
        if(is_prime_[i]==true){
            max_prime_=i; //set max prime to first element set true
            break;
        }
    }
    num_primes_ = count_num_primes();

}

int PrimesSieve::num_digits(int num) {
    //determines how many digits are in an integer
    int count = 0;
    while(num>0){ 
        count++; //increment count 
        num/=10; //integer division truncates when gets to decimal
    }
    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: "; 
    string limit_str;
    cin >> limit_str;
    int limit;
    istringstream iss(limit_str);
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    PrimesSieve sieve(limit);
    cout<<"\nNumber of primes found: "<<sieve.num_primes()<<endl;
    cout<<"Primes up to "<<limit<<":"<<endl;
    sieve.display_primes();
    cout<<endl; 
    return 0;
}