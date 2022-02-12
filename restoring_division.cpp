#include <bits/stdc++.h>

using namespace std;

string decimalToBinary(int n) {
    string curr="";
    if(n==0) return "0";
    while(n>0) {
        curr = to_string(n%2) + curr;
        n=n/2;
    }
    return curr;
}

string twosComplement(string M) {
    string twos;
    for(int i=0;i<M.length();i++) {
    if(M[i]=='0')
    twos+=to_string(1);
    else
    twos+=to_string(0);
    }
    for(int i=twos.length()-1;i>=0;i--) {
        if(twos[i]=='1') twos[i]='0';
        else {
            twos[i]='1';
            break;
        }
    }
    return twos;
}

vector<string> shiftLeft(string C, string AC, string Q) {
    C = AC[0];
    for(int i=0;i<AC.length()-1;i++) AC[i] = AC[i+1];
    AC[AC.length()-1]=Q[0];
    for(int i=0;i<Q.length()-1;i++) Q[i] = Q[i+1];
    Q[Q.length()-1]='X';
    return {C, AC, Q};
}

string addition(string C, string AC, string M) {
    string curr="";
    string foradd = C+AC;
    int carry=0;
    for(int i=M.length()-1;i>=0;i--) {
        if(carry==1 && foradd[i]=='1' && M[i]=='1') curr = "1"+curr;
        else if(carry==1 && (foradd[i]=='1' || M[i]=='1')) curr = "0"+curr;
        else if(carry==1) {
            curr = "1"+curr;
            carry=0;
        }
        else if(foradd[i]=='1' && M[i]=='1') {
            curr = "0"+curr;
            carry=1;
        }
        else if(foradd[i]=='1' || M[i]=='1') {
            curr = "1"+curr;
        }
        else curr = "0"+curr;
    }
    
    return curr;
}

int main()
{
    int ac=0, m, q, count;
    cout << "Enter divident: ";
    cin >> q;
    cout << "Enter Divisor: ";
    cin >> m;
    cout << "C\tAC\tQ\t\tOperation" << endl;
    cout << "-------------------------------------------" << endl;
    string Q = decimalToBinary(q);
    string M = decimalToBinary(m);
    int mlen=M.length();
    for(int i=0;i<=(Q.length()-mlen);i++) M = "0"+M;
    string not_M = twosComplement(M);
    string AC;
    string C = "0";
    

    for(int i=0;i<Q.length();i++) AC=AC+"0";
    
    cout << C << "\t";
    cout << AC << "\t";
    cout << Q << "\t\t";
    cout << "Initialization" << endl << endl;
    
    count = Q.length();
    
    vector<string> v;
    v.push_back(C);
    v.push_back(AC);
    v.push_back(Q);
    bool flag=false;
    while(count>0) {
        cout << "-----------------Cycle--------------------" << endl;
        
        v = shiftLeft(v[0], v[1], v[2]);
        cout << v[0] << "\t";
        cout << v[1] << "\t";
        cout << v[2] << "\t\t";
        cout << "Left Shift" << endl;
        
        string pstadd;
        if(!flag) {
            pstadd = addition(v[0], v[1], not_M);
            cout << pstadd[0] << "\t";
            cout << pstadd.substr(1) << "\t";
            cout << v[2] << "\t\t";
            cout << "AC = AC-M" << endl;
        } else {
            pstadd = addition(v[0], v[1], M);
            cout << pstadd[0] << "\t";
            cout << pstadd.substr(1) << "\t";
            cout << v[2] << "\t\t";
            cout << "AC = AC+M" << endl;
        }
        
        cout << pstadd[0] << "\t";
        cout << pstadd.substr(1) << "\t";
        
        if(pstadd[0]=='0') {
            flag=false;
            v[2][Q.length()-1]='1';
            cout << v[2] << "\t\t";
            cout << "Q0-->1" << endl << endl;
        }
        else {
            flag=true;
            v[2][Q.length()-1]='0';
            cout << v[2] << "\t\t";
            cout << "Q0-->0" << endl << endl;
        }
        v[0]=pstadd[0];
        v[1]=pstadd.substr(1);
        
        
        count--;
    }
    
    return 0;
}
