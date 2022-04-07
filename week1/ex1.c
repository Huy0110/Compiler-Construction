#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "lib.h"
#define CONSTANT 100

treetype search(treetype Tree, char* word)
{
	elmType wordSearch;
	treetype result;
	strcpy(wordSearch.word, word);
	//printf("Thanh cong");
	result = searchT(Tree, wordSearch);
	return result;
}

void addWhenNull(treetype* words ,char *word, int line)
{
	elmType wordAdd;
	strcpy(wordAdd.word, word);
	wordAdd.appearCount=1;

	makeNullList(&(wordAdd.rootLine), &(wordAdd.curLine), &(wordAdd.tailLine));
	appendList(line, &(wordAdd.rootLine), &(wordAdd.curLine), &(wordAdd.tailLine));
	insertNode(words, wordAdd);
	//print("Da add thanh cong\n")
}

void addThongThuong(treetype* words ,char *word, int line, treetype newW)
{
	newW->element.appearCount++;

	appendList(line, &(newW->element.rootLine), &(newW->element.curLine), &(newW->element.tailLine));
	//print("Da add thanh cong\n")
}

void add(treetype* wordTree ,char *word, int line)
{
	elmType wordAdd;
	treetype newW = search(*wordTree, word);
	if(newW!=NULL)
	{
		addThongThuong(wordTree,word,line,newW);
	}
	else
	{
		addWhenNull(wordTree,word,line);
	}
}

void readFile(char* fileName ,treetype* words, treetype* stopWs)
{
	char c, prevC, pre_pre;
	char word[20];
	int count = 0;
	int line = 1;
	bool isTen = false;
	bool isWord = false;
	treetype resultSearch;
	FILE *f=fopen(fileName,"r");
	pre_pre = 'a';

	if(f==NULL)
	{
		printf("Open error file %s\n", fileName);
		return;
	}

	//duyet file
	for(prevC='z';(c=fgetc(f))!=EOF;prevC = c)
	{
		//gap ki tu la chu cai in hoa
		if(c>='A'&&c<='Z')
		{
			c = tolower(c);
			if(prevC>='a'&&prevC<='z')
			{
				//ky tu phia truoc la chu cai thi khong phai ten
				isTen=false;
			}
			else
			{
				isTen = true;	
			}

			//kiem tra them dieu kien kieu "abc. Xyz"
			if(prevC == ' ' && pre_pre == '.')
			{
				//printf("Here");
				isTen = false;
			}
			
		}
		//gap ki tu khong phai chu cai
		if((c<'a'||c>'z')&&c!='\'')
		{
			//kiem tra khong phai ten rieng va la 1 tu
			if(!isTen && isWord)
			{
				word[count]='\0';
				//kiem tra co trong stopws khong
				resultSearch = search(*stopWs, word);
				if(resultSearch==NULL)
				{
					//them tu
					add(words, word, line);
				}
			}

			//them dong
			if(c=='\n')
			{
				line++;
			}

			//set up lai
			count=0;
			isTen=false;
			isWord=false;
		} else 
		{
			//cap nhat tu
			word[count++]=c;
			if(!isWord) isWord=true;
		}		
	}
	fclose(f);
}

int main()
{
	treetype words, stopWs;
	makeNullTree(&words);
	makeNullTree(&stopWs);

	readFile("stopw.txt", &stopWs, &words);
	readFile("vanban.txt", &words, &stopWs);

	inOrderPrint(words);

	freeTree(words);
	freeTree(stopWs);
	return 0;
}