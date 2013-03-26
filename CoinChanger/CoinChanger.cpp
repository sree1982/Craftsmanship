#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class CoinChanger
{
    private:
        int AmountToDispense;
        vector<int> vDenominations;
        
        void sortDescending(vector<int>& _vDenominations);
        void setAmount(double _AmountToDispense);
        vector<int> greedyAlgorithm(int nRemainingAmount);
        int GetCoinsforDenomination(int& Amount, int denomination);
        int TotalCoinsRequired(int CoinPosition,int Amount);
        bool test(vector<int> vMinimumNumberOfCoins,bool bSpecial);
        vector<int> GetCoinsForSpecialCase(vector< pair <int,int> >vSpecial);
    
    public:
        void setDenominationsInDescending(vector<int>& _vDenominations);    
        vector<int> DispenseChange(double Amount);
       
};

void CoinChanger::setDenominationsInDescending(vector<int>& _vDenominations)
{
    sortDescending(_vDenominations);
    vDenominations = _vDenominations;       
}

void CoinChanger::sortDescending(vector<int>& _vDenominations)
{
    //Sort the denominations in descending order
    sort(_vDenominations.begin(), _vDenominations.end());
    reverse(_vDenominations.begin(), _vDenominations.end());
}

void CoinChanger::setAmount(double _AmountToDispense)
{
    AmountToDispense = round(_AmountToDispense * 100);//Convert to Cents
}

vector<int> CoinChanger::greedyAlgorithm(int nRemainingAmount)
{
    vector<int> vDispensedCoins;
    for(int i = 0; i < vDenominations.size(); i++)
    {
       vDispensedCoins.push_back(nRemainingAmount / vDenominations.at(i));
       nRemainingAmount = nRemainingAmount % vDenominations.at(i);             
    }
    return vDispensedCoins;
}
vector<int> CoinChanger::DispenseChange(double Amount)
{
    vector<int>vDispensedCoins;
      
    setAmount(Amount);        
        
    bool bSpecialCase = false;
    vector< pair <int,int> > vSpecialCoinsPair;
    for(int i = 0; i < vDenominations.size() - 1; i++)
    {
       if(vDenominations[i] < 2 * vDenominations[i+1])
        {
            bSpecialCase = true;
            vSpecialCoinsPair.push_back(make_pair(vDenominations[i+1],vDenominations[i]));            
        }
    } 
    
    if(!bSpecialCase)
        vDispensedCoins = greedyAlgorithm(AmountToDispense);
    else
        vDispensedCoins = GetCoinsForSpecialCase(vSpecialCoinsPair);
    
    //TEST
    if(!test(vDispensedCoins,bSpecialCase))
        cout << "*****TEST FAILED*****" << endl;
    else
        cout << endl << "*****TEST PASSED*****" << endl;
        
    return vDispensedCoins;
}

int CoinChanger::GetCoinsforDenomination(int& Amount, int denomination)
{
   int numberOfCoins = Amount/denomination;
   Amount = Amount%denomination; 
   return  numberOfCoins;  
}

int CoinChanger::TotalCoinsRequired(int CoinPosition,int Amount)
{
   int CoinsRequired = 0;
   while(Amount > 0 && CoinPosition < vDenominations.size())
    {
        CoinsRequired += Amount/vDenominations.at(CoinPosition);
        Amount = Amount % vDenominations.at(CoinPosition);
        CoinPosition++;                   
    } 
    return CoinsRequired;
}



vector<int> CoinChanger::GetCoinsForSpecialCase(vector< pair <int,int> >vSpecial)
{ 
    vector<int>vDispensedCoins;
    int nRemainingAmount = AmountToDispense;
    
    vDispensedCoins.resize(vDenominations.size());
    for(int j = 0; j < vSpecial.size(); j++)
    {   
        if(nRemainingAmount == 0)
            break; 
        int smallerCoin = vSpecial[j].first;
        int biggerCoin = vSpecial[j].second;
        for(int coinPosition = 0; coinPosition < vDenominations.size(); coinPosition++)
        {         
            if(vDenominations[coinPosition] != biggerCoin)
            {
                vDispensedCoins[coinPosition] = GetCoinsforDenomination(nRemainingAmount,vDenominations[coinPosition]);
            }
            else
            {
                int biggerCoinPosition = coinPosition;
                int smallerCoinPosition = coinPosition+1;                
                while(nRemainingAmount >= 2 * vDenominations[biggerCoinPosition])
                {
                    vDispensedCoins[biggerCoinPosition]++;
                    nRemainingAmount -= vDenominations[biggerCoinPosition];
                }
                if(TotalCoinsRequired(biggerCoinPosition,nRemainingAmount) 
                    >  TotalCoinsRequired(smallerCoinPosition, nRemainingAmount))
                {
                    coinPosition = smallerCoinPosition;
                    //i = i+1;                    
                }            
                while(nRemainingAmount > 0)
                {
                    vDispensedCoins[coinPosition]+= GetCoinsforDenomination(nRemainingAmount,vDenominations[coinPosition]);
                    coinPosition++;
                }   
            }
        }
    }      
    return vDispensedCoins;
}

bool CoinChanger::test(vector<int> vMinimumNumberOfCoins,bool bSpecial)
{   
  if(!bSpecial)
    {
        //Check if its the minimum number of coins
        for(int i = 1; i < vDenominations.size() - 1; i++)
        {
            if(vMinimumNumberOfCoins.at(i) * vDenominations.at(i)  >= vDenominations.at(i-1))
            {
                return false;            
            }        
        }
     }
   
 //check if it sums up to the Amount to be Dispensed
     int nSum = 0; 
     for(int i = 0 ; i < vDenominations.size(); i++)
     {
        nSum+= vDenominations.at(i) * vMinimumNumberOfCoins.at(i);        
     }  
                
     if (nSum != AmountToDispense)  
     {
      return false;
     }
     return true;
}

int main()
{
    double nAmount;
    vector<int>vDenominations;
    int size;
    cout << "Enter the amount to be dispensed in dollars" << endl;
    cin >> nAmount;
    
    cout << "Enter the total number of denominations you have" << endl;
    cin >> size;
    vDenominations.resize(size);
    
    cout << "Enter the values of denomination" << endl;
    for (int i=0; i<size; ++i) 
    {
        int input;
        cin >> input;
        vDenominations.at(i) = input;
    }
    CoinChanger objCoinChanger;  
    objCoinChanger.setDenominationsInDescending(vDenominations);     
    vector<int>vChange = objCoinChanger.DispenseChange(nAmount);
    
    while(!vChange.empty())
    {
        cout << "Number of " << vDenominations.back() << " cent coins is " << vChange.back() << endl; 
        vChange.pop_back();
        vDenominations.pop_back();               
    }         
       
return 0;
}
