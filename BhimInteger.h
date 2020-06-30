#ifndef BhimInteger_H_INCLUDED
#define BhimInteger_H_INCLUDED

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

#define absBhim BhimInteger::absBhimInteger
#define factBhim BhimInteger::factBhimInteger
#define maxBhim BhimInteger::maxBhimInteger
#define minBhim BhimInteger::minBhimInteger
#define to_Bhim BhimInteger::to_BhimInteger
#define revBhim BhimInteger::revBhimInteger
#define countBhim BhimInteger::countBhimInteger
#define eraseBhim BhimInteger::eraseBhimInteger
#define isPaliBhim BhimInteger::isPaliBhimInteger
#define sortBhim BhimInteger::sortBhimInteger

class BhimInteger {

    private:
        string str;

    public:

    BhimInteger ()
    {
        str = "0";
    }

    BhimInteger (string s)
    {
        str = s;
    }

    BhimInteger (int n)
    {
        ostringstream convertstr;
        convertstr << n;
        str = convertstr.str();
    }

    BhimInteger (long long int n)
    {
        ostringstream convertstr;
        convertstr << n;
        str = convertstr.str();
    }

    BhimInteger (const BhimInteger &N2)
    {
        str = N2.str;
    }


    friend ostream &operator<<( ostream &output, const BhimInteger &N )
    {
         output<<N.str;
         return output;
    }

    friend istream &operator>>( istream  &input, BhimInteger &N )
    {
         input >> N.str;
         return input;
    }

    static BhimInteger to_BhimInteger(string s)
    {
        BhimInteger N3;
        N3.str = s;
        return N3;
    }

    static BhimInteger to_BhimInteger(int n)
    {
        BhimInteger N3;
        ostringstream convertstr;
        convertstr << n;
        N3.str = convertstr.str();
        return N3;
    }

    static BhimInteger to_BhimInteger(long long int n)
    {
        BhimInteger N3;
        ostringstream convertstr;
        convertstr << n;
        N3.str = convertstr.str();
        return N3;
    }


    static string removeZero(string str)
    {
        int i = 0, flag = 0;
        if(str[0] == '-')
        {
            flag = 1;
            i++;
        }
        while (str[i] == '0')
           i++;
        if(flag)
            str.erase(1, i);
        else
            str.erase(0, i);
        return str;
    }

    static string add(string s, string s1)
    {
        int carry=0,i,j;
        int sum=0;
        int m=s.length();
        int n=s1.length();
        vector<int>v;
        for(i=m-1,j=n-1;i>=0||j>=0;i--,j--)
        {
            sum=carry;
            if(i>=0)
            {
                sum+=s[i]-'0';
            }
            if(j>=0)
            {
                sum+=s1[j]-'0';
            }
            v.push_back(sum%10);
            carry=sum/10;
        }
        if(carry!=0)
        v.push_back(carry);

        string y = "";
        for(i=v.size()-1;i>=0;i--)
        y += (char)(v[i]+48);
        return y;
    }

    static string subtract(string s1,string s2)
    {
        string answer="",ans,temp;
        int carry=0,i,j,k,y=0,flag=0,flag1=0;
        int sum=0;
        if(s1==s2)
        {
            return "0";
        }
        else if(s1[0]=='-' and s2[0]=='-')
        {
            flag1=1;
            s1=s1.substr(1);
            s2=s2.substr(1);
        }
        else if(s1[0]=='-' and s2[0]!='-')
        {
            s1=s1.substr(1);
            answer=add(s1,s2);
            answer='-'+answer;
            return answer;
        }
        else if(s1[0]!='-' and s2[0]=='-')
        {
            s2=s2.substr(1);
            answer=add(s1,s2);
            return answer;
        }
        ans=maxCompare(s1,s2);
        if(ans==s2)
        {
            temp=s1;
            s1=s2;
            s2=temp;
            flag=1;
        }
        int m=s1.length();
        int n=s2.length();
        if(m>n)
        k=m;
        else
        k=n;
        int A[k+1]={0};
        for(i=m-1,j=n-1;i>=0||j>=0;i--,j--)
        {
            sum=0;
            if(i>=0)
            {
                sum+=s1[i]-'0';
            }
            if(j>=0)
            {
                if(sum<s2[j]-'0'+carry)
                {
                    sum+=10;
                    sum-=s2[j]-'0'+carry;
                    carry=1;
                }
                else
                {
                    sum-=s2[j]-'0'+carry;
                    carry=0;
                }
            }
            if(carry!=0 and j<0)
            {
              if(sum<carry)
              {
                sum+=10;
                sum-=carry;
                carry=1;
              }
              else
              {
                sum-=carry;
                carry=0;
              }
            }
            A[y++]=sum;
            //carry=sum/10;
        }
        for(i=k-1;i>=0;i--)
        {
            answer += (char)(A[i] + 48);
        }
        answer=removeZero(answer);
        if(flag1==1 and flag==0)
        {
            answer='-'+answer;
        }
        else if(flag1==0 and flag==1)
        {
            answer='-'+answer;
        }
        return answer;
    }

    static string multiply(string s, string s1)
    {
        int flag=0;
        int m=s.length();
        int n=s1.length();
        int A[m+n]={0};
        for(int i=m-1;i>=0;i--)
        {
            for(int j=n-1;j>=0;j--)
            {
                int mul=(s[i]-'0')*(s1[j]-'0');
                int sum=A[i+j+1]+mul;
                A[i+j]+=sum/10;
                A[i+j+1]=sum % 10;
            }
        }

        string finalanswer = "";
        for(int i=0;i<m+n;i++)
        {
            if(A[i]==0 && flag==0 ){}
                else if(A[i]!=0 )
                    flag=1;

            if(flag==1)
                finalanswer += (char)(A[i]+48);
        }
        if(finalanswer.length() == 0)
            finalanswer = "0";
        return finalanswer;
    }

    BhimInteger operator++()
    {
        string s = "1";
        str = add(this->str,s);
        return *this;
    }

    BhimInteger operator--()
    {
        string s = "1";
        str = subtract(this->str,s);
        return *this;
    }

    BhimInteger operator++(int)
    {
        BhimInteger N3;
        N3.str = this->str;
        string s = "1";
        str = add(this->str,s);
        return N3;
    }

    BhimInteger operator--(int)
    {
        BhimInteger N3;
        N3.str = this->str;
        string s = "1";
        str = subtract(this->str,s);
        return N3;
    }

    BhimInteger operator + (BhimInteger const &N2)
    {
        BhimInteger N3;
        string s = str;
	    string s1 = N2.str;
        N3.str = add(s,s1);
        return N3;
    }

    BhimInteger operator - (BhimInteger const &N2)
    {
        BhimInteger N3;
        string s = str;
	    string s1 = N2.str;
        N3.str = subtract(s,s1);
        return N3;
    }

    BhimInteger operator * (BhimInteger const &N2)
    {
        BhimInteger N3;
        string s = str;
	    string s1 = N2.str;
        N3.str = multiply(s,s1);
        return N3;
    }

    BhimInteger operator / (BhimInteger const &N2)
    {
        BhimInteger N3;
        string s1 = str;
	    string s2 = N2.str;
        stringstream convertnum(s2);
        long long int div = 0;
        convertnum>>div;
        N3.str = division(s1,div);
        return N3;
    }

    bool operator == (BhimInteger const &N2)
    {
        return this->str == N2.str;
    }

    bool operator != (BhimInteger const &N2)
    {
        return this->str != N2.str;
    }

    BhimInteger& operator += (BhimInteger N2)
    {
        this->str = add(this->str,N2.str);
        return *this;
    }

    BhimInteger& operator -= (BhimInteger N2)
    {
        this->str = subtract(this->str,N2.str);
        return *this;
    }

    BhimInteger& operator *= (BhimInteger N2)
    {
        this->str = multiply(this->str,N2.str);
        return *this;
    }

    BhimInteger& operator /= (BhimInteger N2)
    {
        string s2 = N2.str;
        stringstream convertnum(s2);
        long long int div = 0;
        convertnum>>div;
        this->str = division(this->str,div);
        return *this;
    }

    friend BhimInteger operator +(BhimInteger &N1,int num)
    {
        BhimInteger N3;
        ostringstream convertstr;
        convertstr << num;
        N3.str = convertstr.str();
        N3.str = add(N1.str,N3.str);
        return N3;
    }

    friend BhimInteger operator -(BhimInteger &N1,int num)
    {
        BhimInteger N3;
        ostringstream convertstr;
        convertstr << num;
        N3.str = convertstr.str();
        N3.str = subtract(N1.str,N3.str);
        return N3;
    }

    friend BhimInteger operator *(BhimInteger &N1,int num)
    {
        BhimInteger N3;
        ostringstream convertstr;
        convertstr << num;
        N3.str = convertstr.str();
        N3.str = multiply(N1.str,N3.str);
        return N3;
    }

    friend BhimInteger operator /(BhimInteger &N1,int num)
    {
        BhimInteger N3;
        N3.str = division(N1.str,(long long int)num);
        return N3;
    }

    friend BhimInteger operator +(int num, BhimInteger &N1)
    {
        BhimInteger N3;
        ostringstream convertstr;
        convertstr << num;
        N3.str = convertstr.str();
        N3.str = add(N1.str,N3.str);
        return N3;
    }

    friend BhimInteger operator -(int num, BhimInteger &N1)
    {
        BhimInteger N3;
        ostringstream convertstr;
        convertstr << num;
        N3.str = convertstr.str();
        N3.str = subtract(N3.str,N1.str);
        return N3;
    }

    friend BhimInteger operator *(int num, BhimInteger &N1)
    {
        BhimInteger N3;
        ostringstream convertstr;
        convertstr << num;
        N3.str = convertstr.str();
        N3.str = multiply(N1.str,N3.str);
        return N3;
    }

    friend BhimInteger operator /(int num, BhimInteger &N1)
    {
        BhimInteger N3;
        ostringstream convertstr;
        convertstr << num;
        N3.str = convertstr.str();
        string s2 = N1.str;
        stringstream convertnum(s2);
        long long int div = 0;
        convertnum>>div;
        N3.str = division(N3.str,div);
        return N3;
    }

    static string division(string s1, long long int div)
    {
        string result;
        int index = 0;
        long long int temp = s1[index] - '0';
        while (temp < div)
        {
            temp = temp*10 + (s1[++index] - '0');

            if(index >= s1.length())
                break;
        }


        while (s1.length() > index) {
            result += (temp / div) + '0';
            temp = (temp % div)*10 + s1[++index] - '0';
        }

        if (result.length() == 0)
            return "0";

        return result;
    }

    static string division(string s1, int div)
    {
        string result;
        int index = 0;
        int temp = s1[index] - '0';
        while (temp < div)
        {
            temp = temp*10 + (s1[++index] - '0');

            if(index >= s1.length())
                break;
        }


        while (s1.length() > index) {
            result += (temp / div) + '0';
            temp = (temp % div)*10 + s1[++index] - '0';
        }

        if (result.length() == 0)
            return "0";

        return result;
    }

    static string factorial(int n)
    {
        int i=2;
        int j=0;
        int len=1;
        int A[100000]={0};
         A[0]=1;
        int num=0;
        while(i<=n)
        {
            j=0;
            num=0;
            while(j<len)
            {
                A[j]=A[j]*i;
                A[j]=A[j]+num;
                num=A[j]/10;
                A[j]=A[j]%10;
                j++;
            }
            while(num!=0)
            {
                A[len]=num%10;
                num=num/10;
                len++;
            }
            i++;
        }
        len--;
        string y = "";
        while(len>=0)
        {
            y += (char)(A[len]  + '0');
            len=len-1;
        }
        return y;
    }

    static BhimInteger factBhimInteger(int n)
    {
        BhimInteger N3;
        N3.str = factorial(n);
        return N3;
    }

    static BhimInteger factBhimInteger(BhimInteger N1)
    {
        BhimInteger N3;
        string s = N1.str;
        stringstream convertnum(s);
        int n = 0;
        convertnum>>n;
        N3.str = factorial(n);
        return N3;
    }

    static BhimInteger factBhimInteger(string s)
    {
        BhimInteger N3;
        stringstream convertnum(s);
        int n = 0;
        convertnum>>n;
        N3.str = factorial(n);
        return N3;
    }

    static string maxCompare(string s1,string s2)
    {
        string answer="";
        int i;
        if(s1[0]=='-' and s2[0]!='-')
        {
            return s2;
        }
        else if(s1[0]!='-' and s2[0]=='-')
        {
            return s1;
        }
        else if(s1[0]!='-' and s2[0]!='-' and s1.length()>s2.length())
        {
            return s1;
        }
        else if(s1[0]!='-' and s2[0]!='-' and s2.length()>s1.length())
        {
            return s2;
        }
        else if(s1[0]=='-' and s2[0]=='-' and s1.length()>s2.length())
        {
            return s2;
        }
        else if(s1[0]=='-' and s2[0]=='-' and s2.length()>s1.length())
        {
            return s1;
        }
        else if(s1[0]!='-' and s2[0]!='-' and s2.length()==s1.length())
        {
            for(i=0;i<s1.length();i++)
            {
                if(s1[i]-'0'<s2[i]-'0')
                {
                    return s2;
                }
                else if(s1[i]==s2[i])
                {
                    continue;
                }
                else if(s1[i]-'0'>s2[i]-'0')
                {
                    return s1;
                }
            }
        }
        else if(s1[0]=='-' and s2[0]=='-' and s2.length()==s1.length())
        {
            for(i=0;i<s1.length();i++)
            {
                if(s1[i]-'0'<s2[i]-'0')
                {
                    return s1;
                }
                else if(s1[i]==s2[i])
                {
                    continue;
                }
                else if(s1[i]-'0'>s2[i]-'0')
                {
                    return s2;
                }
            }
        }
    }

    static string minCompare(string s1,string s2)
    {
        string ans;
        ans=maxCompare(s1,s2);
        if(ans==s1)
        {
            return s2;
        }
            return s1;
    }

    static BhimInteger maxBhimInteger(BhimInteger N1, BhimInteger N2)
    {
        string s1,s2,ans;
        s1 = N1.str;
        s2 = N2.str;

        ans=maxCompare(s1,s2);

        if(N1.str == ans)
            return N1;
        else
            return N2;

    }


    static BhimInteger minBhimInteger(BhimInteger N1, BhimInteger N2)
    {
        string s1,s2,ans;
        s1 = N1.str;
        s2 = N2.str;

        ans=minCompare(s1,s2);

        if(N1.str == ans)
            return N1;
        else
            return N2;

    }

    static BhimInteger absBhimInteger(BhimInteger N1)
    {
        string s1 = N1.str;

        if(s1[0]=='-')
            s1=s1.substr(1);

        BhimInteger N2(s1);
        return N2;
    }

    static BhimInteger revBhimInteger(BhimInteger N1)
    {
        string s2 = "",s1 = N1.str;
        for(int i= s1.length()-1; i>=0; i--)
            s2 += s1[i];
        BhimInteger N2(s2);
        return N2;
    }

    static int countBhimInteger(BhimInteger N1, int n)
    {
        char c = (char)(n + '0');
        int counti = 0;
        for(int i=0; i< N1.str.length(); i++)
        {
            if(N1.str[i] == c)
                counti++;
        }
        return counti;
    }

    static BhimInteger eraseBhimInteger(BhimInteger N1, int n)
    {
        char c = (char)(n + '0');
        string s2 = "";
        int counti = 0;
        for(int i=0; i< N1.str.length(); i++)
        {
            if(N1.str[i] != c)
                s2 += N1.str[i];
        }
        s2 = removeZero(s2);
        if(s2 == "" or s2 == "-")
        {
            BhimInteger N2(0);
            return N2;
        }
        else
        {
            BhimInteger N2(s2);
            return N2;
        }
    }

    static bool isPaliBhimInteger(BhimInteger N1)
    {
        string s1 = N1.str;
        int i = 0, j = s1.length()-1;
        if(s1[0] == '-')
            i++;
        while(i<j)
        {
            if(s1[i] != s1[j])
                return false;
            i++;
            j--;
        }
        return true;
    }

    static BhimInteger sortBhimInteger(BhimInteger N1)
    {
        string s1 = N1.str;
        int flag = 0;
        if(s1[0] == '-')
        {
            flag = 1;
            s1.erase(0,1);
        }

        sort(s1.begin(), s1.end());

        s1 = removeZero(s1);

        if(flag)
            s1 = '-' + s1;

        if(s1 == "" or s1 == "-")
        {
            BhimInteger N2(0);
            return N2;
        }
        BhimInteger N2(s1);
        return N2;
    }
};

#endif // BhimInteger_H_INCLUDED
