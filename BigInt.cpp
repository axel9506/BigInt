#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

//convertisseur d'un nombre décimal en binaire
void numberConverter(vector<unsigned int>& result, unsigned int number, unsigned int taille)
{

	if (number == 0)
		for (unsigned int i = 0; i < taille; i++)
			result.push_back(0);

	else
	{
		while (number != 0)
		{
			result.push_back(number % 2);
			number = number / 2;
		}

		if (result.size() < taille)
			for (unsigned int i = result.size(); i < taille; i++)
				result.push_back(0);
	}

}

//convertisseur d'un nombre binaire en nombre décimal
unsigned int BitConverter(vector<unsigned int>& number)
{
	unsigned int sum = 0;

	for (unsigned int i = 0; i < number.size(); i++)
		sum += number[i] * pow(2, i);

	return sum;
}

//opération intermédiaire pour la multiplication des paquets
void decalageBit(vector<unsigned int>& result, vector<unsigned int>& number, unsigned int nbDecalage)
{
	for (unsigned int i = 0; i < nbDecalage; i++)
		result.push_back(0);

	for (unsigned int i = 0; i < number.size(); i++)
		result.push_back(number[i]);
}

//addition des paquets
unsigned int Addition(vector<unsigned int>& result, vector<unsigned int>& A, vector<unsigned int>& B, unsigned int c)
{

	unsigned int carry = c;

	if(A.size() < B.size())
		for (unsigned int i = A.size(); i < B.size(); i++)
			A.push_back(0);
	else if(B.size() < A.size())
		for (unsigned int i = B.size(); i < A.size(); i++)
			B.push_back(0);

	for (unsigned int i = 0; i < A.size(); i++)
	{

		switch(carry + A[i] + B[i])
		{
			case 0:
				result.push_back(0);
				carry = 0;
				break;

			case 1:
				result.push_back(1);
				carry = 0;
				break;

			case 2:
				result.push_back(0);
				carry = 1;
				break;

			case 3:
				result.push_back(1);
				carry = 1;
				break;
		}
	}
	
	return carry;

}

//multiplication des paquets
unsigned int Multiplication(vector<unsigned int>& result, vector<unsigned int>& A, vector<unsigned int>& B, vector<unsigned int>& carry, unsigned int taille)
{
	unsigned int k = 0;
	vector<unsigned int> temp;

	for (unsigned int i = 0; i < B.size(); i++)
		if(B[i] == 1)
		{
			k = i;
			break;
		}

	decalageBit(temp, A, k);
	
	for(unsigned int i = 0; i < temp.size(); i++)
		result.push_back(temp[i]);

	unsigned int l = k;
	k = 0;
	temp.clear();

	vector<unsigned int> temp2;

	for (unsigned int i = l + 1; i < B.size(); i++)
		if(B[i] == 1)
		{
			k = 0;
			
			decalageBit(temp, A, i);

			k = Addition(temp2, result, temp, k);
			if(k == 1)
				temp2.push_back(k);
			
			result.clear();
			
			for(unsigned int i = 0; i < temp2.size(); i++)
				result.push_back(temp2[i]);

			temp2.clear();

			temp.clear();
		}
		
	k = taille;
	
	if(result.size() > k)
	{
		for(unsigned int i = k; i < result.size(); i++)
			carry.push_back(result[i]);
			
		l = result.size();
		
		for(unsigned int i = k; i < l; i++)
			result.pop_back();
	}
	
	return k;
}

//addition grand nombre 
void addition(vector<vector<unsigned int> >& result, vector<vector<unsigned int> >& A, vector<vector<unsigned int> >& B)
{
	unsigned int carry = 0;
	vector<unsigned int> temp(0);

	if(A.size() < B.size())
		for (unsigned int i = A.size(); i < B.size(); i++)
			A.push_back(temp);
	else if(B.size() < A.size())
		for (unsigned int i = B.size(); i < A.size(); i++)
			B.push_back(temp);

	for (unsigned int i = 0; i < A.size(); i++)
	{
		temp.clear();
		carry = Addition(temp, A[i], B[i],carry);
		result.push_back(temp);
		temp.clear();
	}
	if (carry == 1){
		temp.push_back(1);
		result.push_back(temp);
	}

}

//soustraction grand nombre
void soustraction(vector<vector<unsigned int> >& result, vector<vector<unsigned int> >& A, vector<vector<unsigned int> >& B)
{
	if(A.size() > B.size())
	{
		unsigned int taille = A.size();
		
		vector<vector<unsigned int> > tempB;
		vector<unsigned int> tempPaquet;
		
		for(unsigned int i = 0; i < B.size(); i++)
			tempB.push_back(tempPaquet);
		
		for(unsigned int i = 0; i < B.size(); i++)
			for(unsigned int j = 0; j < B[i].size(); j++)
				tempB[i].push_back(1 - B[i][j]);
				
		tempPaquet.push_back(1);
		
		vector<vector<unsigned int> > temp;
		temp.push_back(tempPaquet);
				
		vector<vector<unsigned int> > tempB2;
		addition(tempB2, tempB, temp);
		
		addition(result, A, tempB2);
		
		if(result.size() != taille)
			result.pop_back();
	}
	
	else 
	{
		unsigned int taille = B.size();
	
		vector<vector<unsigned int> > tempA;
		vector<unsigned int> tempPaquet;
		
		for(unsigned int i = 0; i < A.size(); i++)
			tempA.push_back(tempPaquet);
		
		for(unsigned int i = 0; i < A.size(); i++)
			for(unsigned int j = 0; j < A[i].size(); j++)
				tempA[i].push_back(1 - A[i][j]);
				
		tempPaquet.push_back(1);
		
		vector<vector<unsigned int> > temp;
		temp.push_back(tempPaquet);
				
		vector<vector<unsigned int> > tempA2;
		addition(tempA2, tempA, temp);
		
		addition(result, B, tempA2);
		
		if(result.size() != taille)
			result.pop_back();
	}
}

/*
	multiplication grand nombre
	je n'ai malheureusement pas réussi à implémenter cette opération
	à cause d'une erreur de bit au bout du 34ème paquet
*/
void multiplication(vector<vector<unsigned int> >& result, vector<vector<unsigned int> >& A, vector<vector<unsigned int> >& B, unsigned int taille)
{
	unsigned int l;
	unsigned int j = taille;
	vector<unsigned int> carry;
	
	
	vector<unsigned int> tempResultat;
	
	j = Multiplication(tempResultat, A[0], B[0], carry, j);
	
	result.push_back(tempResultat);
	
	tempResultat.clear();
	
	vector<unsigned int> tempProduit;
	tempResultat.push_back(0);
	
	for (unsigned int k = 1; k < A.size() + B.size() - 1; k++)
	{	
		for (unsigned int i = 0; i <= k ; i++)
		{	
			if ((i < A.size()) && (k - i < B.size()))
			{
				tempProduit.clear();
				
				unsigned int m = 2 * j;
				
				m = Multiplication(tempProduit, A[i], B[k - i], carry, m);
				
				vector<unsigned int> tempPaquet;
				
				l = 0;
				l = Addition(tempPaquet, tempResultat, tempProduit, l);
				if(l == 1)
					tempPaquet.push_back(l);
				
				tempResultat.clear();
				
				for(unsigned int i = 0; i < tempPaquet.size(); i++)
					tempResultat.push_back(tempPaquet[i]);
					
				tempPaquet.clear();
			}
		}
		
		vector<unsigned int> tempResultat2;
		l = 0;
		l = Addition(tempResultat2, tempResultat, carry, l);
		if(l == 1)
			tempResultat2.push_back(l);
			
		tempResultat.clear();
		for(unsigned int  i = 0; i < tempResultat2.size(); i++)
			tempResultat.push_back(tempResultat2[i]);
			
		carry.clear();
		
		if(tempResultat.size() > j)
		{
			for(unsigned int i = j; i < tempResultat.size(); i++)
				carry.push_back(tempResultat[i]);
				
			unsigned int n = tempResultat.size();
			
			for (unsigned int i = j; i < n; i++)
				tempResultat.pop_back();
		}
		
		result.push_back(tempResultat);
	}
	
	result.push_back(carry);
}


int main()
{
	vector<unsigned int> package;
	vector<unsigned int> package2;
	
	numberConverter(package, 5, 4);
	numberConverter(package2, 10, 4);

	vector<vector<unsigned int> > number;
	vector<vector<unsigned int> > number2;
	

	number.push_back(package);
	number.push_back(package);
	number2.push_back(package2);
	number2.push_back(package2);
	
	
	cout << "premier nombre (85) : ";
	for (int i = 0; i < number.size(); i++){
		for (int j = 0; j < number[i].size(); j++)
		{
			cout << number[i][j];
		}
		cout << " | ";
	}
	cout << endl << endl;
	
	cout << "deuxième nombre (170) : ";
	for (int i = 0; i < number2.size(); i++){
		for (int j = 0; j < number2[i].size(); j++)
		{
			cout << number2[i][j];
		}
		cout << " | ";
	}
	cout << endl << endl;
	
	vector<vector<unsigned int> > result;
	
	cout << "somme (185 + 75) : ";
	addition(result, number, number2);	//Somme 85 + 170 (01010101 + 10101010)
	for (int i = 0; i < result.size(); i++){
		for (int j = 0; j < result[i].size(); j++)
		{
			cout << result[i][j];
		}
		cout << " | ";
	}
	cout << endl << endl;

	result.clear();

	cout << "produit (185 * 75) : ";
	multiplication(result, number, number2, 4);	//Produit 85 * 170
	for (int i = 0; i < result.size(); i++){
		for (int j = 0; j < result[i].size(); j++)
		{
			cout << result[i][j];
		}
		cout << " | ";
	}
	cout << endl << endl;


	//même opération que précedemment mais version BigInt
	vector<unsigned int> package3;
	vector<unsigned int> package4;

	numberConverter(package3, 1431655765, 32);
	numberConverter(package4, 2863311530, 32);

	vector<vector<unsigned int> > number3;
	vector<vector<unsigned int> > number4;
	
	for (unsigned int i = 1; i <= 32; i++)
        number3.push_back(package3);
		
	for (unsigned int i = 1; i <= 32; i++)
        number4.push_back(package4);

	cout << "premier nombre : " << endl;
	for (int i = 0; i < number3.size(); i++){
		for (int j = 0; j < number3[i].size(); j++)
		{
			cout << number3[i][j];
		}
		cout << " | ";
	}
	cout << endl << endl;
	
	cout << "deuxième nombre : " << endl;
	for (int i = 0; i < number4.size(); i++){
		for (int j = 0; j < number4[i].size(); j++)
		{
			cout << number4[i][j];
		}
		cout << " | ";
	}
	cout << endl << endl;
	
	vector<vector<unsigned int> > result2;
	
	cout << "addition : " << endl;
	addition(result2, number3, number4);	//le résultat est un BigInt avec que des 1
	for (int i = 0; i < result2.size(); i++){
		for (int j = 0; j < result2[i].size(); j++)
		{
			cout << result2[i][j];
		}
		cout << " | ";
	}
	cout << endl << endl;
	
	vector<unsigned int> packagebis;

	numberConverter(packagebis, 4294967295, 32);

	vector<vector<unsigned int> > numberbis;
	vector<vector<unsigned int> > resultbis;
	vector<vector<unsigned int> > resultbis2;
	vector<vector<unsigned int> > resultbis3;

	for (unsigned int i = 1; i <= 32; i++)
        numberbis.push_back(packagebis);

	cout << "que des 1 : " << endl;
	for (int i = 0; i < numberbis.size(); i++){
		for (int j = 0; j < numberbis[i].size(); j++)
		{
			cout << numberbis[i][j];
		}
		cout << " | ";
	}
	cout << endl << endl;

	cout << "addition : " << endl; //on a bien la propagation de la retenue et le décalage d'un bit
	addition(resultbis, numberbis, numberbis);
	for (int i = 0; i < resultbis.size(); i++){
		for (int j = 0; j < resultbis[i].size(); j++)
		{
			cout << resultbis[i][j];
		}
		cout << " | ";
	}
	cout << endl << endl;
	
	cout << "soustraction : " << endl; //on obtient bien 0 version BigInt
	soustraction(resultbis3, numberbis, numberbis);
	for (int i = 0; i < resultbis3.size(); i++){
		for (int j = 0; j < resultbis3[i].size(); j++)
		{
			cout << resultbis3[i][j];
		}
		cout << " | ";
	}
	cout << endl << endl;
	
	cout << "multiplication : " << endl; //problème au sein de la multiplication au bout du 34ème paquet
	multiplication(resultbis2, numberbis, numberbis, 32);
	for (int i = 0; i < resultbis2.size(); i++){
		for (int j = 0; j < resultbis2[i].size(); j++)
		{
			cout << resultbis2[i][j];
		}
		cout << " | ";
	}
	cout << endl << endl;
	
	return 0;
}


