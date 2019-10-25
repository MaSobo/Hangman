#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <algorithm>

void shuffle(std::vector<std::string>& dik )
{


    std::mt19937 generator(std::time(nullptr));

    std::shuffle(dik.begin(), dik.end(), generator);



}

std::string readWordfromFile ()
{
    std::ifstream file("dictionary.txt");
      if(!file.is_open())
        {
            std::cerr << "cannot open";
            return "error";
        }
    std::vector<std::string> dictionary = {};

    for(std::string word; file >> word; )
        {
           dictionary.emplace_back(word);          
        }
    
    shuffle(dictionary);

    std::fstream stream;
    stream.open("dictionary.txt", stream.trunc | stream.out);
    if(!stream.is_open())
        {
            std::cerr << "cannot open";
            return "error";
        }
    

    for (std::string w : dictionary)
        stream << w << "\n";
    
    return dictionary[0];
}

int main()
{
    std::string guess = " ";
    std::string word = " ";
    std::string ans;
    bool flag = false;
    int l=7;
    
    std::cout<<"Would you like to input your own word [w] or take it from randomized dictionary [d]?";
    char select;
    std::cin >> select;
    std::cin.ignore(1,'\n');
    if(select == 'w')
        {
            std::cout << "Input secret word: ";
            std::cin >> word;
        }
    if(select == 'd')
        {
            word = readWordfromFile();
        }
    else
    {
        std::cout << "Catastrofic failure. Closing down.";
    }
    

    system("cls");
    std::cout << "The word has "<< word.length() << " letters. \n";
    
    for (int i=0; i<word.length(); ++i)
        {
            ans.push_back('_');
        }
   


    while (guess != word && l > 0)
    {
    std::cout << ans <<std::endl;
    std::cout << "Guess a letter / the word: \n";
    std::cin >> guess; 
    flag = false;
        if (guess.length() == 1)
        {
            for (int i=0; i<word.length(); ++i)
                {

                    if (word[i] == guess[0])
                        {
                            ans[i]=guess[0];
                            flag=true;
                        }
                    else
                    {
                        if (flag != true) 
                            flag=false;
                    }
                    

                }        
        
        }
        else 
            if (guess == word )
                {
                    std::cout << "You won!";
                    return 0;
                }

    if (flag == true)
        {
            std::cout << "CONGRATS! \n";
            std::cout<< "You have " << l << " tries left!";
        }
    else
        {
            std::cout << "WRONG!!! \n";
            l--;
            std::cout<< "You have " << l << " tries left!";
        }
  
    }
            std::cout<<"You lost! \n";
            std::cout<<"The secret word was "<<word;


    return 0;
}