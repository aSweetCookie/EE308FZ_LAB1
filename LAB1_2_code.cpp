#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void openFile();
int level1();

ifstream inFile,inFile1,inFile2;
string path = "";
int level = 0;
const int keywordNumber=32;
int count[keywordNumber] = {0};
string str;

string keyword[]={"auto","break","case","char","const","continue","default","do",
	"double","else","enum","extern","float","for","goto","if",
	"int","long","register","return","short","signed","sizeof","stastic",
	"struct","switch","typedef","union","unsigned","void","volatile","while"};

int main(){
	openFile();
	int total = level1();
	//sw={switch, case, default}
	int sw[3]={25,2,6};
	string ifelse[3]={"else if", "if","else"};
	int struc[count[sw[0]]]={0};
	int x[3]={0,0,-1};
	//操作inFile1
	while (getline (inFile1, str)){
		int pos;
		for(;;){
			//level 2:output the number of "case" corresponding to each group
			if((int)str.find(keyword[sw[1]]) != -1){
				if((int)str.find("//") != -1) break;
				else{
					//第x[0]个switch-case结构有struc[x[0]]个case
					struc[x[0]]++;
					break;
				}
			}
			if((int)str.find(keyword[sw[2]]) != -1){
				if((int)str.find("//") != -1) break;
				else{
					//用default计算是第x[0]个switch-case结构
					x[0]++;
					break;
				}
			}
			//排除掉else if的情况
			if((int)str.find(ifelse[0]) != -1){
				pos = str.find(ifelse[0]);
				//将str字符串已搜索部分删去
				str = str.substr(pos + ifelse[0].length(),str.length() - pos - ifelse[0].length());
			}
			//用if计算总共有多少个if结构
			if((int)str.find(ifelse[1]) != -1){
				if((int)str.find("//") != -1) break;
				else{
					x[1]++;
					break;
				}
			}
			else break;
		}	
	}
	//level 3: output the number of "if else" structures
	//level 4: output the number of "if, else if, else" structures
	int divide[x[1]]={0}, ely=0,eln=0;
	//操作inFile2
	while (getline (inFile2, str)){
		for(;;){
			//第x[2]个if结构有divide[x[2]]个else if
			if((int)str.find(ifelse[0]) != -1){
				if((int)str.find("//") != -1) break;
				else{
					divide[x[2]]++;
					break;
				}
			}
			//用if计算是第x[2]个if结构
			if((int)str.find(ifelse[1]) != -1){
				if((int)str.find("//") != -1) break;
				else{
					x[2]++;
					break;
				}
			}
			else break;
		}
	}
	for(int m=0;m<x[1];m++){
		//没有else if的即为'if else'结构
		if(divide[m]==0){
			eln++;
		}
		//有else if的即为'if, else if, else'结构
		else{
			ely++;				
		}	
	}
	//identify level + display output
	for(int i=1; i<level+1; i++){
		switch(i){
		case 1:
			cout<<"1. There are "<<total<<" keywords in total."<<endl;
			cout<<"    The details are as follows:"<<endl;
			for(int j=0;j<keywordNumber;j++){	
				if(count[j]!=0){
					cout<<"\t"<<keyword[j]<<": "<<count[j]<<endl;
				}
			}
			break;
		case 2:
			if(count[sw[0]]!=count[sw[2]]){
				cout<<" wrong switch structure"<<endl;
			}
			else{
				cout<<"2. The number of 'switch case' structures is:"<<count[sw[0]]<<endl;
				for(int j=0;j<count[sw[0]];j++){
					cout<<"    There are "<<struc[j]<<" cases in switch "<<j+1<<endl;
				}
			}
			break;
		case 3:
			cout<<"3. The number of 'if else' structures is: "<<eln<<endl;
			break;
		case 4:
			cout<<"4. The number of 'if, else if, else' structures is: "<<ely<<endl;
			break;
		default:
			cout<<"wrong"<<endl;
		}
	}
	inFile.close();
	inFile1.close();
	inFile2.close();
	return 0;

}
void openFile(){
	//receive input
	cout<<"Please enter the path of the target file:";
	cin>>path;
	cout<<"Please enter the level you want to make statistics(from 1 to 4):";
	cin>> level;
	//open file
	inFile.open(path.c_str(),ios::in);
	inFile1.open(path.c_str(),ios::in);
	inFile2.open(path.c_str(),ios::in);
	if(!inFile|| !inFile1 ||!inFile2){
		cout <<"Error! Please check the path of target file!" << endl;
		exit(0); 
	}
}
int level1(){
	//level 1: output "keyword" statistics（关键字分别有几个） 
	//operate inFile
	//遍历每一行
	while (getline (inFile, str)){
		//遍历每个关键字
		for(int i=0;i<keywordNumber;i++){
			int pos;
			for(;;){
				if((int)str.find(keyword[i]) != -1){
					//忽略注释行
					if((int)str.find("//") != -1) break;
					else{
						//找到即+1
						pos = str.find(keyword[i]);
						count[i]++;
						//且将str字符串已搜索部分删去
						if(keyword[i]!="do"){	
							str = str.substr(pos + keyword[i].length(),str.length() - pos - keyword[i].length());
						}else{
							if(str[str.find(keyword[i])+2]=='u'){
								count[i]--;
								break;
							}else{
								break;
							}
						}
					}
				} 
				else break;
			}	
		}
	}
	//level 1: output "keyword" statistics（关键字总共有几个）
	int total=0; 
	for(int j=0;j<keywordNumber;j++){
		if(count[j]!=0){
			total+=count[j];	
		}
	}
	return total;
}
