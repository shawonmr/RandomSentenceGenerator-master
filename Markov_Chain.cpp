// Markov_Chain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "dirent.h"

using namespace std;

//This is a simple markov chain for generating
//random text from given input files
//The program creates maps for prefix and suffixes
//and then generate text randomly accessing the map
//Command line : Markov_Cahin.exe Folder Name P N 


map<string, list<string> > sentenceGenerator; // Main map for generating sentences

//Function declaration
vector<string> open(string path);
void generate(int nwords, map<string, list<string> >& stringGenerator, int P);
void add(string dir_name, vector<string>& filenames, map<string, list<string> >& stringGenerator, int P);

//Main Function
int main(int argc, char *argv[])
{
    
	if(argc < 3)
	{
		cout<<"Not enough arguments. Please provide right number of arguments"<<endl;
		return -1;
	}
	printf("%s, %s, %s, %s\n",argv[0],argv[1],argv[2],argv[3]);
	string dir_name = argv[1]; //first directory name
	int P = atoi(argv[2]);     //Prefix length
	int nwords = atoi(argv[3]); //Number of words    

	//Temp variable
	int i, j;


	//Initializing randomness
    srand(time(NULL));
    
	std::vector<std::string> f;

    f = open(dir_name); // pass which dir to open   

	add(dir_name,f,sentenceGenerator,P);
    generate(nwords,sentenceGenerator,P);
	getchar();
    return 0;
}


// reads file names from the path
vector<string> open(string path) {

    DIR*    dir;
    dirent* pdir;
    std::vector<std::string> files;

    dir = opendir(path.c_str());

    while (pdir = readdir(dir)) {
        files.push_back(pdir->d_name);
    }
    
    return files;
}



// reads from the files get prefix and suffixes and adds to the map
void add(string dir_name, vector<string>& filenames, map<string, list<string> >& sentenceGenerator, int P)
{

	int i,j,k;
	ifstream file;
    
	for(i = 0; i< filenames.size(); i++)
	{
		if(filenames[i].size()>3)
		{
		char dir_file_name[1024];
		for(j = 0; j < dir_name.size(); j++)
		{
			dir_file_name[j] = dir_name[j];
		}
		dir_file_name[j++] = '\\';
		for(k = 0; k < filenames[i].size(); k++)
		{
			dir_file_name[j++]= filenames[i][k];
		}
		dir_file_name[j++]='\0';

		file.open(dir_file_name);
		
		string line;
		if(file==NULL)
		{
			cout<<"Can not open input file :"<<filenames[0]<<endl;
			exit(1);
		}

		while(getline(file,line))
		{
			stringstream string_parse(line);
			string word, prefix;
			list <string> suffix;
			while(getline(string_parse,word,' '))
			{
				if(word.size()==P)
				{
					//Found prefix
					prefix = word;
				}
				else
				{
					suffix.push_back(word);
				}

			}
			sentenceGenerator.insert(pair<string,list<string>>(prefix,suffix));//inserting in the main map




		}


		file.close();
	}
	}

}
// generates unique prefixes and one word per line at the end
void generate(int nwords, map<string, list<string>>&sentenceGenerator, int P)
{
   
    int i, j,count;	
	map<string, list<string>>::iterator it;	    
    
	//Printing unique prefix
	cout<<"Unique Prefix"<<endl;
	for(it = sentenceGenerator.begin(); it!=sentenceGenerator.end(); it++)
    {
		cout<<it->first<<endl;
    }


	for (i = 0; i < nwords; i++) 
	{
		
		j = rand() % sentenceGenerator.size(); //generates a random number between the size of the map		
		count = 0;
		for(it = sentenceGenerator.begin(); it!=sentenceGenerator.end(); it++)
		{
			count++;
			if(count==j)  //It will print those prefix and suffix corresponding to the random access number
			{
				cout<<it->first<<" ";
				list<string> retrieved_suffix = it->second;
				list<string>::iterator list_iter;
				for(list_iter = retrieved_suffix.begin(); list_iter != retrieved_suffix.end(); list_iter++)
				{
					cout<<(*list_iter)<<" ";
				}
				cout<<"\n";
				break;
			}
		}

		
    }
}



