/*************
*Decimal conversion
*By Matchman-colo
*Continuous improvement
*************/
#include<iostream>
#include<cstring>
#include<sstream>
#include<cmath>
#include <algorithm>

using namespace std;

bool judgeBin(string bin);
bool judgeHex(string hex);
string decToBin(int dec);
int binToDec(string bin);
string binToHex(string bin);
string hexToBin(string hex);

int main()
{
	int choice = 0;
	cout << '\n' << 
	"二进制转十进制:1   \
	十进制转二进制:2    \
	二进制转十六进制:3  \
	十六进制转二进制:4" << endl << "请输入您的选择：";
	cin >> choice;
	switch (choice) {
		case 1: {
			string bin;
			cout << "请输入二进制数：";
			cin >> bin;
			if (judgeBin(bin))
				cout << binToDec(bin) << endl;
			else
				cout << "请输入有效的二进制数" << endl;
			break;
		}
		case 2: {
			int dec = 0;
			cout << "请输入十进制数：";
			cin >> dec;
			cout << decToBin(dec) << endl;
			break;
		}
		case 3: {
			string bin;
			cout << "请输入二进制数：";
			cin >> bin;
			if (judgeBin(bin))
				cout << binToHex(bin) << endl;
			else
				cout << "请输入有效的二进制数" << endl;
			break;
		}
		case 4: {
			string hex;
			cout << "请输入十六进制数：";
			cin >> hex;
			if(judgeHex(hex))
				cout << hexToBin(hex) << endl;
			else
				cout << "请输入有效的十六进制数" << endl;
			break;
		}

		default:
			cout << "请输入有效数字" << endl;
	}
	return 0;
}

bool judgeBin(string bin)
{
	for (int i = 0; i < bin.size(); i++) {
		if (bin[i] != '0' && bin[i] != '1'&&bin[i] != '-')
			return false;
	}
	return true;
}

bool judgeHex(string hex) {
	for (int i = 0; i < hex.size(); i++) {
		char ch = hex[i];
		int tag = 0;
		for (int j = 0; j <= 9; j++) {
			if (ch == '0' + j) {
				tag = 1;
				break;
			}
			if (j <= 5) {
				if (i == 1 && ch == 'x') {
					tag = 1;
					break;
				}
				if (ch == 'A' + j || ch == 'a' + j) {
					tag = 1;
					break;
				}
			}
		}
		if (!tag)
			return false;
	}
	return true;
}

string decToBin(int dec)
{
	int quotient = abs(dec), remainder = 0;
	string bin="";
	ostringstream str;
	while (quotient != 0)
	{
		remainder = quotient % 2;
		quotient = quotient >> 1;
		str << remainder;
	}
	bin = str.str();
	if (dec < 0)
		bin += "-";
	reverse(bin.begin(), bin.end());
	return bin;
}

int binToDec(string bin)
{
	int dec = 0,tag = 0;
	if (bin[0] == '-') 
		tag = 1;
	for (int i = 0+tag; i < bin.size(); i++)
	{
		dec += (bin[i] - '0')*pow(2,(bin.size() - i - 1));
	}
	if (bin[0] == '-')
		dec *= -1;
	return dec;
}

string binToHex(string bin)
{
	char ch = '0';
	int fill = 4-(bin.size()%4);
	ostringstream hex;
	string newHex;
	for (int i = 0; i < fill; i++) {
		bin = ch + bin;
	}
	for (int i = 0; i <= bin.size()-4; i += 4) {
		string mid;
		int mid1=0;
		for (int j = 0; j < 4; j++) {
			mid += bin[i + j];
		}
		mid1 = binToDec(mid);
		if (mid1 < 10)
			hex << mid1;
		else {
			switch (mid1){
				case 10: hex << 'A'; break;
				case 11: hex << 'B'; break;
				case 12: hex << 'C'; break;
				case 13: hex << 'D'; break;
				case 14: hex << 'E'; break;
				case 15: hex << 'F'; break;
				default:
					break;
			}
		}
	}
	newHex = "0x" + hex.str();
	return newHex;
}

string hexToBin(string hex)
{
	ostringstream bin;
	if (hex[0] == '0' && hex[1] == 'x') {
		string newHex;
		for (int i = 2; i < hex.size(); i++) {
			newHex += hex[i];
		}
		hex = newHex;
	}
	for (int i = 0; i < hex.size(); i++) {
		char ch = hex[i];
		switch (ch)
		{
			case 'a':
			case 'A': bin << decToBin(10); break;
			case 'b':
			case 'B': bin << decToBin(11); break;
			case 'c':
			case 'C': bin << decToBin(12); break;
			case 'd':
			case 'D': bin << decToBin(13); break;
			case 'e':
			case 'E': bin << decToBin(14); break;
			case 'f':
			case 'F': bin << decToBin(15); break;
			default: {
				if (i != 0) {
					string mid = decToBin(ch - '0');
					int fill = 4 - mid.size();
					for (int j = 0; j < fill; j++) {
						mid = '0' + mid;
					}
					bin << mid;
					break;
				}
				else {
					bin << decToBin(ch - '0');
				}
			}
		}
	}
	return bin.str();
}
