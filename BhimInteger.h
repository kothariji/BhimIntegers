#ifndef BhimInteger_H_INCLUDED
#define BhimInteger_H_INCLUDED

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>

/**************************************************

	Author: Dhruv Kothari
		Nishant Handge
		Tanuj Mehta

****************************************************/

namespace Bhim
{
    class BhimInteger{
    private:
        std::string val;
    public:
        BhimInteger()
        {
            this->val = "0";
        }
        BhimInteger(const std::string& str)
        {
            if(!isInputCorrect(str)) {
                std::cerr << "Invalid Input.. Please Use Valid BhimInteger" << std::endl;
                exit(0);
            }
            this->val = str;
        }
        template<typename int_type, typename = typename std::enable_if<std::is_integral<int_type>::value>::type>
        BhimInteger(const int_type n)
        {
            this->val = std::to_string(n);
        }
        BhimInteger(const BhimInteger& N2)
        {
            this->val = N2.val;
        }
        // Input Validator
        bool isInputCorrect(const std::string& str) {
            if(str.size() == 0)
                return false;
            for(size_t i = (str[0] == '-'); i < str.length(); i++) {
                if(!std::isdigit(str[i]))
                    return false;
            }
            return true;
        }
        friend std::ostream &operator<<(std::ostream &output, const BhimInteger &N)
        {
             output << N.val;
             return output;
        }
        friend std::istream &operator>>(std::istream  &input, BhimInteger &N)
        {
             input >> N.val;
             return input;
        }
        static BhimInteger to_Bhim(std::string str)
        {
            BhimInteger N3;
            N3.val = str;
            return N3;
        }
        template<typename int_type, typename = typename std::enable_if<std::is_integral<int_type>::value>::type>
        static BhimInteger to_Bhim(int_type n)
        {
            BhimInteger N3;
            N3.val = std::to_string(n);
            return N3;
        }
        static std::string removeZero(std::string str)
        {
            int i = 0;
            bool isNegative = false;
            if(str[0] == '-')
            {
                isNegative = true;
                i++;
            }
            while (str[i] == '0')
               i++;
            str.erase(isNegative, i);
            return str;
        }
        static std::string add(std::string str1, std::string str2)
        {
            int carry=0,i,j;
            int sum=0;
            int m=str1.length();
            int n=str2.length();
            std::string y = "";
            if(m == 0 && n == 0)
            {
                y = "0";
            }
            else if(str1[0] == '-' && str2[0] == '-')
            {
                y = add(str1.erase(0,1), str2.erase(0, 1));
                y = '-' + y;
            }
            else if(str1[0] == '-')
            {
                y = subtract(str2, str1.erase(0, 1));
            }
            else if(str2[0] == '-')
            {
                y = subtract(str1, str2.erase(0, 1));
            }
            else
            {
                std::vector<int> v;
                for(i=m-1,j=n-1;i>=0||j>=0;i--,j--)
                {
                    sum=carry;
                    if(i>=0)
                    {
                        sum+=str1[i]-'0';
                    }
                    if(j>=0)
                    {
                        sum+=str2[j]-'0';
                    }
                    v.push_back(sum%10);
                    carry=sum/10;
                }
                if(carry!=0)
                    v.push_back(carry);
                for(i=v.size()-1;i>=0;i--)
                    y += (char)(v[i]+48);
            }
            return y;
        }
        static std::string subtract(std::string str1,std::string str2)
        {
            std::string answer="",ans;
            int carry=0,i,j,k,y=0;
            bool flag1 = false, flag2 = false;
            int sum=0;
            if(str1==str2)
            {
                return "0";
            }
            else if(str1[0]=='-' and str2[0]=='-')
            {
                flag2=true;
                str1=str1.substr(1);
                str2=str2.substr(1);
            }
            else if(str1[0]=='-' and str2[0]!='-')
            {
                str1=str1.substr(1);
                answer=add(str1,str2);
                answer='-'+answer;
                return answer;
            }
            else if(str1[0]!='-' and str2[0]=='-')
            {
                str2=str2.substr(1);
                answer=add(str1,str2);
                return answer;
            }
            ans=maxCompare(str1,str2);
            if(ans==str2)
            {
                std::swap(str1,str2);
                flag1 = true;
            }
            int m=str1.length();
            int n=str2.length();
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
                    sum+=str1[i]-'0';
                }
                if(j>=0)
                {
                    if(sum<str2[j]-'0'+carry)
                    {
                        sum+=10;
                        sum-=str2[j]-'0'+carry;
                        carry=1;
                    }
                    else
                    {
                        sum-=str2[j]-'0'+carry;
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
            if(flag2 && !flag1)
            {
                answer='-'+answer;
            }
            else if(!flag2 && flag1)
            {
                answer='-'+answer;
            }
            return answer;
        }
        static std::string multiply(std::string s, std::string s1)
        {
            bool flag=false;
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
            std::string finalanswer = "";
            for(int i=0;i<m+n;i++)
            {
                if(A[i]==0 && !flag){}
                    else if(A[i]!=0 )
                        flag=1;

                if(flag)
                    finalanswer += (char)(A[i]+48);
            }
            if(finalanswer.length() == 0)
                finalanswer = "0";
            return finalanswer;
        }
        BhimInteger operator++()
        {
            this->val = add(this->val,"1");
            return *this;
        }
        BhimInteger operator--()
        {
            this->val = subtract(this->val,"1");
            return *this;
        }
        BhimInteger operator++(int)
        {
            BhimInteger N3;
            N3.val = this->val;
            this->val = add(this->val,"1");
            return N3;
        }
        BhimInteger operator--(int)
        {
            BhimInteger N3;
            N3.val = this->val;
            this->val = subtract(this->val,"1");
            return N3;
        }
        BhimInteger operator + (BhimInteger const &N2)
        {
            BhimInteger N3;
            N3.val = add(this->val,N2.val);
            return N3;
        }
        BhimInteger operator - (BhimInteger const &N2)
        {
            BhimInteger N3;
            N3.val = subtract(this->val,N2.val);
            return N3;
        }
        BhimInteger operator * (BhimInteger const &N2)
        {
            BhimInteger N3;
            N3.val = multiply(this->val,N2.val);
            return N3;
        }
        BhimInteger operator / (BhimInteger const &N2)
        {
            BhimInteger N3;
            N3.val = division(this->val,std::stol(N2.val));
            return N3;
        }
        bool operator == (BhimInteger const &N2)
        {
            return this->val == N2.val;
        }
        bool operator != (BhimInteger const &N2)
        {
            return this->val != N2.val;
        }
        BhimInteger& operator += (BhimInteger N2)
        {
            this->val = add(this->val,N2.val);
            return *this;
        }
        BhimInteger& operator -= (BhimInteger N2)
        {
            this->val = subtract(this->val,N2.val);
            return *this;
        }
        BhimInteger& operator *= (BhimInteger N2)
        {
            this->val = multiply(this->val,N2.val);
            return *this;
        }
        BhimInteger& operator /= (BhimInteger N2)
        {
            std::stringstream convertnum(N2.val);
            long long int div = 0;
            convertnum>>div;
            this->val = division(this->val,div);
            return *this;
        }
        friend BhimInteger operator +(BhimInteger &N1,int num)
        {
            BhimInteger N3;
            std::ostringstream convertstr;
            convertstr << num;
            N3.val = convertstr.str();
            N3.val = add(N1.val,N3.val);
            return N3;
        }
        friend BhimInteger operator -(BhimInteger &N1,int num)
        {
            BhimInteger N3;
            std::ostringstream convertstr;
            convertstr << num;
            N3.val = convertstr.str();
            N3.val = subtract(N1.val,N3.val);
            return N3;
        }
        friend BhimInteger operator *(BhimInteger &N1,int num)
        {
            BhimInteger N3;
            std::ostringstream convertstr;
            convertstr << num;
            N3.val = convertstr.str();
            N3.val = multiply(N1.val,N3.val);
            return N3;
        }
        friend BhimInteger operator /(BhimInteger &N1,int num)
        {
            BhimInteger N3;
            N3.val = division(N1.val,(long long int)num);
            return N3;
        }
        friend BhimInteger operator +(int num, BhimInteger &N1)
        {
            BhimInteger N3;
            N3.val = add(N1.val,std::to_string(num));
            return N3;
        }
        friend BhimInteger operator -(int num, BhimInteger &N1)
        {
            BhimInteger N3;
            N3.val = subtract(std::to_string(num),N1.val);
            return N3;
        }
        friend BhimInteger operator *(int num, BhimInteger &N1)
        {
            BhimInteger N3;
            N3.val = multiply(N1.val,std::to_string(num));
            return N3;
        }
        friend BhimInteger operator /(int num, BhimInteger &N1)
        {
            BhimInteger N3;
            N3.val = division(std::to_string(num),std::stol(N1.val));
            return N3;
        }
        template<typename int_type, typename = typename std::enable_if<std::is_integral<int_type>::value>::type>
        static std::string division(std::string s1, int_type div)
        {
            std::string result;
            size_t index = 0;
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
        static std::string power(std::string str1, std::string str2) {
            if(str2 == "0") {
                return "1";
            } else if(str1 == "0") {
                if(str2[0] == '-')
                    return std::to_string((long long int)std::pow(0, -5));
                return "0";
            } else if(str1[0] == '-' && str2[0] == '-') {
                if(str1 == "-1" && str2 == "-1") {
                    return "-1";
                } else if(str1 == "-1") {
                    if((((int)str2[str2.length()-1])-48) & 1) {
                        return "-1";
                    } else {
                        return "1";
                    }
                } else {
                    return "0";
                }
            } else if(str1[0] == '-') {
                if((((int)str2[str2.length()-1])-48) & 1)
                    return '-' + power(str1.erase(0, 1), str2);
                return power(str1.erase(0, 1), str2);
            } else if(str2[0] == '-') {
                if(str1 == "1") {
                    return str1;
                } else {
                    return "0";
                }
            } else {
                std::string init_str1 = str1;
                while(str2 != "1") {
                    str1 = multiply(str1, init_str1);
                    str2 = subtract(str2, "1");
                }
                return str1;
            }
        }
        static BhimInteger powBhim(std::string str1, std::string str2)
        {
            BhimInteger temp;
            temp.val = power(str1, str2);
            return temp;
        }
        static BhimInteger powBhim(BhimInteger &n1, std::string str2)
        {
            BhimInteger temp;
            temp.val = power(n1.val, str2);
            return temp;
        }
        static BhimInteger powBhim(std::string str1, BhimInteger &n2)
        {
            BhimInteger temp;
            temp.val = power(str1, n2.val);
            return temp;
        }
        static BhimInteger powBhim(BhimInteger &n1, BhimInteger &n2)
        {
            BhimInteger temp;
            temp.val = power(n1.val, n2.val);
            return temp;
        }
        template <typename int_type, typename = typename std::enable_if<std::is_integral<int_type>::value>::type>
        static BhimInteger powBhim(int_type n1, int_type n2)
        {
            BhimInteger temp;
            temp.val = power(std::to_string(n1), std::to_string(n2));
            return temp;
        }
        static std::string factorial(int n)
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
            std::string y = "";
            while(len>=0)
            {
                y += (char)(A[len]  + '0');
                len=len-1;
            }
            return y;
        }

        static BhimInteger factBhim(int n)
        {
            BhimInteger N3;
            N3.val = factorial(n);
            return N3;
        }

        static BhimInteger factBhim(BhimInteger N1)
        {
            BhimInteger N3;
            std::stringstream convertnum(N1.val);
            int n = 0;
            convertnum>>n;
            N3.val = factorial(n);
            return N3;
        }

        static BhimInteger factBhim(std::string s)
        {
            BhimInteger N3;
            std::stringstream convertnum(s);
            int n = 0;
            convertnum>>n;
            N3.val = factorial(n);
            return N3;
        }
        static std::string maxCompare(std::string s1,std::string s2)
        {
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
                for(size_t i=0;i<s1.length();i++)
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
                for(size_t i=0;i<s1.length();i++)
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
            return "";
        }
        static std::string minCompare(std::string s1,std::string s2)
        {
            if(s1 == maxCompare(s1,s2))
            {
                return s2;
            }
            return s1;
        }
        static BhimInteger maxBhim(BhimInteger N1, BhimInteger N2)
        {
            std::string s1,s2,ans;
            s1 = N1.val;
            s2 = N2.val;

            ans=maxCompare(N1.val,N2.val);

            if(N1.val == ans)
                return N1;
            else
                return N2;
        }
        static BhimInteger minBhim(BhimInteger N1, BhimInteger N2)
        {
            std::string s1,s2,ans;
            s1 = N1.val;
            s2 = N2.val;

            ans=minCompare(s1,s2);

            if(N1.val == ans)
                return N1;
            else
                return N2;
        }
        static BhimInteger absBhim(BhimInteger N1)
        {
            std::string s1 = N1.val;

            if(s1[0]=='-')
                s1=s1.substr(1);

            BhimInteger N2(s1);
            return N2;
        }

        static BhimInteger revBhim(BhimInteger N1)
        {
            std::string s2 = "",s1 = N1.val;
            for(int i= s1.length()-1; i>=0; i--)
                s2 += s1[i];
            BhimInteger N2(s2);
            return N2;
        }

        static int countBhim(BhimInteger N1, int n)
        {
            char c = (char)(n + '0');
            int counti = 0;
            for(size_t i=0; i< N1.val.length(); i++)
            {
                if(N1.val[i] == c)
                    counti++;
            }
            return counti;
        }
        static BhimInteger eraseBhim(BhimInteger N1, int n)
        {
            char c = (char)(n + '0');
            std::string s2 = "";
            for(size_t i=0; i< N1.val.length(); i++)
            {
                if(N1.val[i] != c)
                    s2 += N1.val[i];
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
        static bool isPalindromeBhim(BhimInteger N1)
        {
            std::string s1 = N1.val;
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
        static BhimInteger sortBhim(BhimInteger N1)
        {
            std::string s1 = N1.val;
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
}

#define factBhim BhimInteger::factBhim
#define maxBhim BhimInteger::maxBhim
#define minBhim BhimInteger::minBhim
#define to_Bhim BhimInteger::to_Bhim
#define revBhim BhimInteger::revBhim
#define countBhim BhimInteger::countBhim
#define eraseBhim BhimInteger::eraseBhim
#define isPaliBhim BhimInteger::isPalindromeBhim
#define sortBhim BhimInteger::sortBhim
#define powBhim BhimInteger::powBhim
#define absBhim BhimInteger::absBhim
#endif // BhimInteger_H_INCLUDED
