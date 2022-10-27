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
	//����inFile1
	while (getline (inFile1, str)){
		int pos;
		for(;;){
			//level 2:output the number of "case" corresponding to each group
			if((int)str.find(keyword[sw[1]]) != -1){
				if((int)str.find("//") != -1) break;
				else{
					//��x[0]��switch-case�ṹ��struc[x[0]]��case
					struc[x[0]]++;
					break;
				}
			}
			if((int)str.find(keyword[sw[2]]) != -1){
				if((int)str.find("//") != -1) break;
				else{
					//��default�����ǵ�x[0]��switch-case�ṹ
					x[0]++;
					break;
				}
			}
			//�ų���else if�����
			if((int)str.find(ifelse[0]) != -1){
				pos = str.find(ifelse[0]);
				//��str�ַ�������������ɾȥ
				str = str.substr(pos + ifelse[0].length(),str.length() - pos - ifelse[0].length());
			}
			//��if�����ܹ��ж��ٸ�if�ṹ
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
	//����inFile2
	while (getline (inFile2, str)){
		for(;;){
			//��x[2]��if�ṹ��divide[x[2]]��else if
			if((int)str.find(ifelse[0]) != -1){
				if((int)str.find("//") != -1) break;
				else{
					divide[x[2]]++;
					break;
				}
			}
			//��if�����ǵ�x[2]��if�ṹ
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
		//û��else if�ļ�Ϊ'if else'�ṹ
		if(divide[m]==0){
			eln++;
		}
		//��else if�ļ�Ϊ'if, else if, else'�ṹ
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
	//level 1: output "keyword" statistics���ؼ��ֱַ��м����� 
	//operate inFile
	//����ÿһ��
	while (getline (inFile, str)){
		//����ÿ���ؼ���
		for(int i=0;i<keywordNumber;i++){
			int pos;
			for(;;){
				if((int)str.find(keyword[i]) != -1){
					//����ע����
					if((int)str.find("//") != -1) break;
					else{
						//�ҵ���+1
						pos = str.find(keyword[i]);
						count[i]++;
						//�ҽ�str�ַ�������������ɾȥ
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
	//level 1: output "keyword" statistics���ؼ����ܹ��м�����
	int total=0; 
	for(int j=0;j<keywordNumber;j++){
		if(count[j]!=0){
			total+=count[j];	
		}
	}
	return total;
}
