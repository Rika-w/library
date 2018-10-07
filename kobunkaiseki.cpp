#include<iostream>
#include<string>
using namespace std;

int number();
int factor();
int term();
int expression();

string s;
int ind;

int number(){
  int ret = 0;
  while(isdigit(s[ind])){
    ret *= 10;
    ret += s[ind] - '0';
    ind++;
  }
  return ret;
}

int factor(){
  if(s[ind] == '('){
    ind++;
    int ret = expression();
    ind++;
    return ret;
  }else{
    return number();
  }
}

int term(){
  int ret = number();
  while(1){
    if(s[ind] == '*'){
      ind++;
      ret *= factor();
    }else if(s[ind] == '/'){
      ind++;
      ret /= factor();
    }else{
      break;
    }
  }
  return ret;
}

int expression(){
  int ret = term();
  while(1){
    if(s[ind] == '+'){
      ind++;
      ret += term();
    }else if(s[ind] == '-'){
      ind++;
      ret -= term();
    }else{
      break;
    }
  }
  return ret;
}

/*
//演算子の優先順序なし
int f(){
    int ret = number();
    while(1){
        if(s[ind] == '+'){
            ind++;
            ret += number();
	}else if(s[ind] == '-'){
	    ind++;
	    ret -= number();
        }else if(s[ind] == '*'){
            ind++;
            ret *= number();
	}else if(s[ind] == '/'){
	    ind++;
	    ret /= number();
        }else{
            break;
        }
    }
    return ret;
}



 */
int main(void) {
  int i,j;
  cin >> s;
  ind = 0;
  int ret = expression();
  cout << ret << endl;
}
