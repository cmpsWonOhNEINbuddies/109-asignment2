// $Id: bigint.cpp,v 1.61 2014-06-26 17:06:06-07 - - $

#include <cstdlib>
#include <cctype>
#include <exception>
#include <limits>
#include <stack>
#include <stdexcept>
using namespace std;
#include "bigint.h"
#include "debug.h"
#include "util.h"

bigint::bigint(long that){
    
   big_value = parseL(that);
   negative = false;
   if( that < 0){
    negative = true;

   }
  // DEBUGF ('~', this << " -> " << long_value)
}

bigint::bigint (const string& that) {
   auto itor = that.cbegin();
    negative = false;
   if (itor != that.cend() and *itor == '_') {
      
      negative = true;
      ++itor;
   }
   int newval = 0;
     itor = that.cend();
   while (itor != that.cbegin()){
      char temp =  *itor;
      if(isdigit(temp)){
      big_value.push_back(temp);
      }
     itor--;
   }
   if(!negative){
    char temp =  *itor;
      big_value.push_back(temp);
   }
     // newval = newval * 10 + *itor++ - '0';
     // long_value = isnegative ? - newval : + newval;
   // DEBUGF ('~', this << " -> " << long_value)
     }

    void bigint::print(){
       if(negative){
          cout << "_";
        }
      for( int  i = (big_value.size() - 1) ; i >= 0; i--){
        cout << big_value[i];
      }
       
        cout << "   " <<  big_value.size();
        cout << endl;
    }


bigint operator+ (const bigint& left, const bigint& right) {
  //  const int OFFSET = 48;
         int lbegin = 0;
         int rbegin = 0;
         int carry = 0;
         bigint DyrMyer(0);
           if(left.negative && ! right.negative){
	  bigint copl = left;
	  copl.negative = false;
          DyrMyer = right - copl;
          return DyrMyer;
         }
         
          if( !left.negative && right.negative ){
	    bigint copr = right;
	     copr.negative = false;
             DyrMyer =  left - copr;
             return DyrMyer;
          }
        
          if(left.negative && right.negative){
	       DyrMyer.negative = true; 
          }
                 
         if((!left.negative && !right.negative) || (left.negative && right.negative) ){
         while( lbegin < left.big_value.size() || rbegin < right.big_value.size() ){
	   char l = '0';
           char r = '0';
	   if( lbegin >= left.big_value.size()  ){ // !isdigit(left.big_value[lbegin]) ){
                  l = '0';  
             }
             else{
                  l = left.big_value[lbegin];
                }
	   if(rbegin >=  right.big_value.size() ){ // !isdigit(right.big_value[rbegin]) ){
            r = '0';
         }
         else{
            r = right.big_value[rbegin];
         }
             
	    int el = (int)l - 48;
            int ar = (int)r - 48;
           int add = el + ar  + carry;
            carry = 0;
           if(add >= 10){
              carry = 1;
              add = add % 10;
           }
           char fin = '0' + add;
           DyrMyer.big_value.push_back(fin);
	   
           rbegin++;
           lbegin++;
         }
	 if(carry == 1){
	   char foo = '1';
           DyrMyer.big_value.push_back(foo);
	 }
           return DyrMyer;    
         }

       
         

}





bigint operator- (const bigint& left, const bigint& right) {
  bigint frak(0);
  int lbegin = 0;
  int rbegin = 0;
  int carryover = 0;
  int LMax = left.big_value.size();
  int RMax = right.big_value.size();
  if(left.negative && right.negative){
    bigint copr = right;
    copr.negative = false;
    bigint copl = left;
    copl.negative = false; 
    frak = copr - copl;
    return frak;
  }
  if(left.negative && !right.negative){
    bigint copr = right;
    copr.negative = false;
    bigint copl = left;
    frak = copl + copr;
    frak.negative = true;
    return  frak;
  }
  if(!left.negative && right.negative){
    bigint copr = right;
    copr.negative = false;
    bigint copl = left;
    frak = copl + copr;
    return frak;
  }
  bool Rbig = false;
       Rbig =  left < right;
  if( !( left.negative ) && !( right.negative )){
   
    if(Rbig){
      frak.negative = true;
      cout << "rbig true " << endl;
    }
     
    while( lbegin < LMax ||  rbegin < RMax){
      char lop = '0';
      char rop = '0';
      if(  lbegin <  LMax ){
         lop = left.big_value[lbegin];
      }
      if( rbegin < RMax){
         rop = right.big_value[rbegin];
      }            
      char difference = lop - ( (int)(rop) - 48 )  - carryover;
      if(Rbig){
	difference = rop - (int)((lop) - 48) - carryover;
      }
      if( difference < '0' ){
	difference =  '0' +  (int)( lop + 10 - rop)  - carryover;
	if(Rbig) { difference = '0' + (int)(rop + 10 - lop) - carryover; }   
       carryover = 1;
      }
      else{
	carryover = 0;
      }
     
      if(isdigit(difference)){
	frak.big_value.push_back(difference);
      }
        lbegin++;
        rbegin++;
         
    }
  }
 
  return frak; 
}

bigint operator+ (const bigint& right) {
   return  right;
}

bigint operator- (const bigint& right) {
   return right;
}

long  bigint::to_long() const {
   if (*this <= bigint (numeric_limits<long>::min())
    or *this > bigint (numeric_limits<long>::max()))
               throw range_error ("bigint__to_long: out of range");
   return 1000 ;
}

bool abs_less (const long& left, const long& right) {
   return left < right;
}

//
// Multiplication algorithm.
//
bigint operator* (const bigint& left, const bigint& right) {
   return left;
}

//
// Division algorithm.
//

void multiply_by_2 (bigint::unumber& unumber_value) {
   unumber_value *= 2;
}

void divide_by_2 (bigint::unumber& unumber_value) {
   unumber_value /= 2;
}


bigint::quot_rem divide (const bigint& left, const bigint& right) {
   if (right == 0) throw domain_error ("divide by 0");
   using unumber = unsigned long;
   static unumber zero = 0;
   if (right == 0) throw domain_error ("bigint::divide");
   unumber divisor = 1000;  // right.long_value;
   unumber quotient = 0;
   unumber remainder = 2000;  // left.long_value;
   unumber power_of_2 = 1;
   while (abs_less (divisor, remainder)) {
      multiply_by_2 (divisor);
      multiply_by_2 (power_of_2);
   }
   while (abs_less (zero, power_of_2)) {
      if (not abs_less (remainder, divisor)) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divide_by_2 (divisor);
      divide_by_2 (power_of_2);
   }
   return {quotient, remainder};
}

bigint operator/ (const bigint& left, const bigint& right) {
  return  divide(left, right).first;
}

bigint operator% (const bigint& left, const bigint& right) {
   return divide(left, right).second;
}

bool operator== (const bigint& left, const bigint& right) {
  if(left.big_value.size() != right.big_value.size()){
    return false;
  }
  bool same = true;
  for(unsigned int i = 0; i < left.big_value.size(); i++){
    char temp1 = left.big_value[i];
    if(temp1 != right.big_value[i]){
      same = false;
      break;
    }
  }

   return same;
}

bool operator< ( const bigint& left, const bigint& right ) {
 
  int lsize = left.big_value.size();
  int rsize = right.big_value.size();
  cout << " compare ! r " << rsize << " to l " << lsize << endl;
  if( lsize < rsize){
    return true;
  }

  if(rsize < lsize){
    return false;
  }


    for(int i = lsize - 1; i >= 0; i--){

      char l = left.big_value[i];
      char r = right.big_value[i];
      if( l < r && isdigit(l) && isdigit(r)){
        return true;
      }      

    }
           
  return false;

}

 ostream& operator<< (ostream& out, const bigint& that) {
   out << 200;   // that.long_value;
 return out;
}


bigint pow (const bigint& base, const bigint& exponent) {
   DEBUGF ('^', "base = " << base << ", exponent = " << exponent);
   if (base == 0) return 0;
   bigint base_copy = base;
   long expt = exponent.to_long();
   bigint result = 1;
   if (expt < 0) {
      base_copy = 1 / base_copy;
      expt = - expt;
   }
   while (expt > 0) {
      if (expt & 1) { //odd
         result = result * base_copy;
         --expt;
      }else { //even
         base_copy = base_copy * base_copy;
         expt /= 2;
      }
   }
   DEBUGF ('^', "result = " << result);
   return result;
}
