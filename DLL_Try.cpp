#include "DLL_try.h"
#include <iostream>
#include <map>
#include <string>

void _modificate1(char* arr, int num)
{
	if (0 == num) return;
	int way=-1;
	int sign = -1;
	while (-1 == way)
	{
		sign++;
		if (sign < num)
		{
			if ((arr[sign] > 63) && (92 > arr[sign]))	{ way = 0; break; }
			if ((arr[sign] > 95) && (127 > arr[sign]))	{ way = 0; break; }
			if ((arr[sign] > 92) && (95 > arr[sign]))	{ way = 0; break; }
			if ((arr[sign] == 35) || (36 == arr[sign])) { way = 0; break; }
			if ((arr[sign] > 37) && (42 > arr[sign]))	{ way = 0; break; }
			if ((arr[sign] == 44)) { way = 0; break; }

			if ((arr[sign] > -65) && (0 > arr[sign]))	{ way = 1; break; }
			if ((arr[sign] == -88) || (-72 ==arr[sign])){ way = 1; break; }
			if ((arr[sign] == -71)) { way = 1; break; }
		}
		else { way = 0; break; }
	}
	if (0 == way)
	{
		std::cout << "English to russian" << std::endl;
		std::map <char, char> EN_RU = {
			{ 65, -44 },
			{ 66, -56 },
			{ 67, -47 },
			{ 68, -62 },
			{ 69, -45 },
			{ 70, -64 },
			{ 71, -49 },
			{ 72, -48 },
			{ 73, -40 },
			{ 74, -50 },
			{ 75, -53 },
			{ 76, -60 },
			{ 77, -36 },
			{ 78, -46 },
			{ 79, -39 },
			{ 80, -57 },
			{ 81, -55 },
			{ 82, -54 },
			{ 83, -37 },
			{ 84, -59 },
			{ 85, -61 },
			{ 86, -52 },
			{ 87, -42 },
			{ 88, -41 },
			{ 89, -51 },
			{ 90, -33 },
			{ 60, -63 },
			{ 62, -34 },
			{ 63, 44 },
			{ 58, -58 },
			{ 34, -35 },
			{ 123, -43 },
			{ 125, -38 },
			{ 124, 47 },
			{ 64, 34 },
			{ 35, -71 },
			{ 36, 59 },
			{ 94, 58 },
			{ 38, 63 },
			{ 126, -88 },
			{ 97, -12 },
			{ 98, -24 },
			{ 99, -15 },
			{ 100, -30 },
			{ 101, -13 },
			{ 102, -32 },
			{ 103, -17 },
			{ 104, -16 },
			{ 105, -8 },
			{ 106, -18 },
			{ 107, -21 },
			{ 108, -28 },
			{ 109, -4 },
			{ 110, -14 },
			{ 111, -7 },
			{ 112, -25 },
			{ 113, -23 },
			{ 114, -22 },
			{ 115, -5 },
			{ 116, -27 },
			{ 117, -29 },
			{ 118, -20 },
			{ 119, -10 },
			{ 120, -9 },
			{ 121, -19 },
			{ 122, -1 },
			{ 44, -31 },
			{ 46, -2 },
			{ 47, 46 },
			{ 59, -26 },
			{ 39, -3 },
			{ 91, -11 },
			{ 93, -6 },
			{ 96, -72 }
		};
		std::map <char, char>::iterator temp;
		for (int i = 0; i<num; i++)
		{
			temp = EN_RU.find(*(i + arr));
			if (temp!= EN_RU.end())
			{
				*(arr + i) = temp->second;
			}
		}
	}
	else 
	{
		std::cout << "Russian to english" << std::endl;
		std::map <char,char> RU_EN =
		{
			{ -44, 65 },
			{ -56, 66 },
			{ -47, 67 },
			{ -62, 68 },
			{ -45, 69 },
			{ -64, 70 },
			{ -49, 71 },
			{ -48, 72 },
			{ -40, 73 },
			{ -50, 74 },
			{ -53, 75 },
			{ -60, 76 },
			{ -36, 77 },
			{ -46, 78 },
			{ -39, 79 },
			{ -57, 80 },
			{ -55, 81 },
			{ -54, 82 },
			{ -37, 83 },
			{ -59, 84 },
			{ -61, 85 },
			{ -52, 86 },
			{ -42, 87 },
			{ -41, 88 },
			{ -51, 89 },
			{ -33, 90 },
			{ -63, 60 },
			{ -34, 62 },
			{ 44, 63 },
			{ -58, 58 },
			{ -35, 34 },
			{ -43, 123 },
			{ -38, 125 },
			{ 47, 124 },
			{ 34, 64 },
			{ -71, 35 },
			{ 59, 36 },
			{ 58, 94 },
			{ 63, 38 },
			{ -88, 126 },
			{ -12, 97 },
			{ -24, 98 },
			{ -15, 99 },
			{ -30, 100 },
			{ -13, 101 },
			{ -32, 102 },
			{ -17, 103 },
			{ -16, 104 },
			{ -8, 105 },
			{ -18, 106 },
			{ -21, 107 },
			{ -28, 108 },
			{ -4, 109 },
			{ -14, 110 },
			{ -7, 111 },
			{ -25, 112 },
			{ -23, 113 },
			{ -22, 114 },
			{ -5, 115 },
			{ -27, 116 },
			{ -29, 117 },
			{ -20, 118 },
			{ -10, 119 },
			{ -9, 120 },
			{ -19, 121 },
			{ -1, 122 },
			{ -31, 44 },
			{ -2, 46 },
			{ 46, 47 },
			{ -26, 59 },
			{ -3, 39 },
			{ -11, 91 },
			{ -6, 93 },
			{ -72, 96 }
		};
		std::map <char, char>::iterator temp;
		for (int i = 0; i<num; i++)
		{
			temp = RU_EN.find(*(i + arr));
			if (temp != RU_EN.end())
			{
				*(arr + i) = temp->second;
			}
		}
	}
	return;
}

void _modificate2(char* arr, int num)
{
	std::cout << "CAPS LOCK, length="<<num<< std::endl;
	if (0 == num)	return;
	//std::cout << "CAPS LOCK, length=" << num << std::endl;
	int done = 0;
	for (int i = 0; i < num; i++)
	{
		//std::cout << "CAPS LOCK, sybol=" << i << std::endl;
		//EN:
		done = 0;
		if ((!done) && (*(arr + i) < 91) && (*(arr + i) > 64))
		{
			*(arr + i) = *(arr + i) + 'a' - 'A';
			done = 1;
		}
		if ((!done) && (*(arr + i) < 123) && (*(arr + i) > 96))
		{
			*(arr + i) = *(arr + i) + 'A' - 'a';
			done = 1;
		}
		//RU:
		//capital->small
		if ((!done) && (*(arr + i) < -32) && (*(arr + i) > -65))
		{
			done = 1;
			*(arr + i) = *(arr + i) + 32;
		}
		//small->capital
		if ((!done) && (*(arr + i) < 0) && (*(arr + i) > -31))
		{
			done = 1;
			*(arr + i) = *(arr + i) - 32;
		}
		if (-88 == *(arr + i)) {i[arr] = -72; done = 1;} //E with ':'
		if ((!done)&&(-72 == i[arr])) *(arr + i) = -88;	//e with ':'
	}
}

void _modificate3(unsigned char* arr, int num)
{
	if (0 == num) return;
	int way = -1;
	int sign = -1;
	while (-1 == way)
	{
		sign++;
		if (sign < num)
		{
			if ((arr[sign] > 63) && (92 > arr[sign]))	{ way = 0; break; }
			if ((arr[sign] > 95) && (127 > arr[sign]))	{ way = 0; break; }
			if ((arr[sign] > 92) && (95 > arr[sign]))	{ way = 0; break; }
			if ((arr[sign] == 35) || (36 == arr[sign])) { way = 0; break; }
			if ((arr[sign] > 37) && (42 > arr[sign]))	{ way = 0; break; }
			if ((arr[sign] == 44)) { way = 0; break; }

			if ((arr[sign] > 127) && (176 > arr[sign]))	{ way = 1; break; }
			if ((arr[sign] > 223) && (242 > arr[sign]))	{ way = 1; break; }
			if ((arr[sign] == 252)) { way = 1; break; }
		}
		else { way = 0; break; }
	}
	if (0 == way)
	{
		std::cout << "English to russian" << std::endl;
		std::map <int, int> EN_RU = {
			{ 65, 148 },
			{ 66, 136 },
			{ 67, 145 },
			{ 68, 130 },
			{ 69, 147 },
			{ 70, 128 },
			{ 71, 143 },
			{ 72, 144 },
			{ 73, 152 },
			{ 74, 142 },
			{ 75, 139 },
			{ 76, 132 },
			{ 77, 156 },
			{ 78, 146 },
			{ 79, 153 },
			{ 80, 135 },
			{ 81, 137 },
			{ 82, 138 },
			{ 83, 155 },
			{ 84, 133 },
			{ 85, 131 },
			{ 86, 140 },
			{ 87, 150 },
			{ 88, 151 },
			{ 89, 141 },
			{ 90, 159 },
			{ 40, 129 },
			{ 41, 158 },
			{ 63, 44 },
			{ 58, 134 },
			{ 34, 157 },
			{ 123, 149 },
			{ 125, 154 },
			{ 124, 47 },
			{ 64, 34 },
			{ 35, 252 },
			{ 36, 59 },
			{ 94, 58 },
			{ 38, 63 },
			{ 126, 240 },
			//small now
			{ 97, 228 },
			{ 98, 168 },
			{ 99, 225 },
			{ 100, 162 },
			{ 101, 227 },
			{ 102, 160 },
			{ 103, 175 },
			{ 104, 224 },
			{ 105, 232 },
			{ 106, 174 },
			{ 107, 171 },
			{ 108, 164 },
			{ 109, 236 },
			{ 110, 226 },
			{ 111, 233 },
			{ 112, 167 },
			{ 113, 169 },
			{ 114, 170 },
			{ 115, 235 },
			{ 116, 165 },
			{ 117, 163 },
			{ 118, 172 },
			{ 119, 230 },
			{ 120, 231 },
			{ 121, 173 },
			{ 122, 239 },
			{ 44, 161 },
			{ 46, 238 },
			{ 47, 46 },
			{ 59, 166 },
			{ 39, 237 },
			{ 91, 229 },
			{ 93, 234 },
			{ 96, 241 }
		};
		std::map <int, int>::iterator temp;
		for (int i = 0; i<num; i++)
		{
			temp = EN_RU.find(*(i + arr));
			if (temp != EN_RU.end())
			{
				*(arr + i) = temp->second;
			}
		}
	}
	else
	{
		std::cout << "Russian to english" << std::endl;
		std::map <int, int> RU_EN =
		{
			{ 148, 65 },
			{ 136, 66 },
			{ 145, 67 },
			{ 130, 68 },
			{ 147, 69 },
			{ 128, 70 },
			{ 143, 71 },
			{ 144, 72 },
			{ 152, 73 },
			{ 142, 74 },
			{ 139, 75 },
			{ 132, 76 },
			{ 156, 77 },
			{ 146, 78 },
			{ 153, 79 },
			{ 135, 80 },
			{ 137, 81 },
			{ 138, 82 },
			{ 155, 83 },
			{ 133, 84 },
			{ 131, 85 },
			{ 140, 86 },
			{ 150, 87 },
			{ 151, 88 },
			{ 141, 89 },
			{ 159, 90 },
			{ 129, 40 },
			{ 158, 41 },
			{ 44, 63 },
			{ 134, 58 },
			{ 157, 34 },
			{ 149, 123 },
			{ 154, 125 },
			{ 47, 124 },
			{ 34, 64 },
			{ 252, 35 },
			{ 59, 36 },
			{ 58, 94 },
			{ 63, 38 },
			{ 240, 126 },
			{ 228, 97 },
			{ 168, 98 },
			{ 225, 99 },
			{ 162, 100 },
			{ 227, 101 },
			{ 160, 102 },
			{ 175, 103 },
			{ 224, 104 },
			{ 232, 105 },
			{ 174, 106 },
			{ 171, 107 },
			{ 164, 108 },
			{ 236, 109 },
			{ 226, 110 },
			{ 233, 111 },
			{ 167, 112 },
			{ 169, 113 },
			{ 170, 114 },
			{ 235, 115 },
			{ 165, 116 },
			{ 163, 117 },
			{ 172, 118 },
			{ 230, 119 },
			{ 231, 120 },
			{ 173, 121 },
			{ 239, 122 },
			{ 161, 44 },
			{ 238, 46 },
			{ 46, 47 },
			{ 166, 59 },
			{ 237, 39 },
			{ 229, 91 },
			{ 234, 93 },
			{ 241, 96 }
		};
		std::map <int, int>::iterator temp;
		for (int i = 0; i<num; i++)
		{
			temp = RU_EN.find(*(i + arr));
			if (temp != RU_EN.end())
			{
				*(arr + i) = temp->second;
			}
		}
	}
	return;
}

void _modificate4(unsigned char* arr, int num)
{
	std::cout << "CAPS LOCK, length=" << num << std::endl;
	if (0 == num)	return;
	//std::cout << "CAPS LOCK, length=" << num << std::endl;
	int done = 0;
	for (int i = 0; i < num; i++)
	{
		//std::cout << "CAPS LOCK, sybol=" << i << std::endl;
		//EN:
		done = 0;
		if ((!done) && (*(arr + i) < 91) && (*(arr + i) > 64))
		{
			*(arr + i) = *(arr + i) + 'a' - 'A';
			done = 1;
		}
		if ((!done) && (*(arr + i) < 123) && (*(arr + i) > 96))
		{
			*(arr + i) = *(arr + i) + 'A' - 'a';
			done = 1;
		}
		//RU:
		//capital->small
		if ((!done) && (*(arr + i) < 144) && (*(arr + i) > 127))
		{
			done = 1;
			*(arr + i) = *(arr + i) + 160 - 128;
		}
		if ((!done) && (*(arr + i) < 160) && (*(arr + i) > 143))
		{
			*(arr + i) = *(arr + i) + 224 - 144;
			done = 1;
		}
		//small->capital
		if ((!done) && (*(arr + i) < 176) && (*(arr + i) > 159))
		{
			done = 1;
			*(arr + i) = *(arr + i) + 128 - 160;
		}
		if ((!done) && (*(arr + i) < 240) && (*(arr + i) > 223))
		{
			done = 1;
			*(arr + i) = *(arr + i) - 224 + 144;
		}
		if (240 == *(arr + i)) { i[arr] = 241; done = 1; }
		if ((!done) && (241 == i[arr])) *(arr + i) = 240;
	}
}


void _modificate5(CStringW& arr, int& code)
{
	long num = arr.GetLength() + 1;
	if (0 == num) return;
	int way = -1;
	int sign = -1;
	while (-1 == way)
	{
		sign++;
		if (sign < num)
		{
			if ((arr[sign] > 63) && (92 > arr[sign]))	{ way = 0; break; }
			if ((arr[sign] > 95) && (127 > arr[sign]))	{ way = 0; break; }
			if ((arr[sign] > 92) && (95 > arr[sign]))	{ way = 0; break; }
			if ((arr[sign] == 35) || (36 == arr[sign])) { way = 0; break; }
			if ((arr[sign] > 37) && (42 > arr[sign]))	{ way = 0; break; }
			if ((arr[sign] == 44)) { way = 0; break; }

			if ((arr[sign] > 0x040f) && (0x0450> arr[sign]))	{ way = 1; break; }
			if ((arr[sign] == 0x0451) || (0x0401 == arr[sign])){ way = 1; break; }
			if ((arr[sign] == 0x2116)) { way = 1; break; }
		}
		else { way = 0; break; }
	}
	code = way;
	if (0 == way)
	{
		std::cout << "English to russian" << std::endl;
		std::map <WCHAR, WCHAR> EN_RU = {
			{ 65, 1060 },
			{ 66, 1048 },
			{ 67, 1057 },
			{ 68, 1042 },
			{ 69, 1059 },
			{ 70, 1040 },
			{ 71, 1055 },
			{ 72, 1056 },
			{ 73, 1064 },
			{ 74, 1054 },
			{ 75, 1051 },
			{ 76, 1044 },
			{ 77, 1068 },
			{ 78, 1058 },
			{ 79, 1065 },
			{ 80, 1047 },
			{ 81, 1049 },
			{ 82, 1050 },
			{ 83, 1067 },
			{ 84, 1045 },
			{ 85, 1043 },
			{ 86, 1052 },
			{ 87, 1062 },
			{ 88, 1063 },
			{ 89, 1053 },
			{ 90, 1071 },
			{ 60, 1041 },
			{ 62, 1070 },
			{ 63, 44 },
			{ 58, 1046 },
			{ 34, 1069 },
			{ 123, 1061 },
			{ 125, 1066 },
			{ 124, 47 },
			{ 64, 34 },
			{ 35, 8470 },
			{ 36, 59 },
			{ 94, 58 },
			{ 38, 63 },
			{ 126, 1025 },
			{ 97, 1092 },
			{ 98, 1080 },
			{ 99, 1089 },
			{ 100, 1074 },
			{ 101, 1091 },
			{ 102, 1072 },
			{ 103, 1087 },
			{ 104, 1088 },
			{ 105, 1096 },
			{ 106, 1086 },
			{ 107, 1083 },
			{ 108, 1076 },
			{ 109, 1100 },
			{ 110, 1090 },
			{ 111, 1097 },
			{ 112, 1079 },
			{ 113, 1081 },
			{ 114, 1082 },
			{ 115, 1099 },
			{ 116, 1077 },
			{ 117, 1075 },
			{ 118, 1084 },
			{ 119, 1094 },
			{ 120, 1095 },
			{ 121, 1085 },
			{ 122, 1103 },
			{ 44, 1073 },
			{ 46, 1102 },
			{ 47, 46 },
			{ 59, 1078 },
			{ 39, 1101 },
			{ 91, 1093 },
			{ 93, 1098 },
			{ 96, 1105 }
		};
		std::map <WCHAR, WCHAR>::iterator temp;
		for (int i = 0; i<num; i++)
		{
			temp = EN_RU.find(arr[i]);
			if (temp != EN_RU.end())
			{
				//arr[i] = temp->second;
				arr.SetAt(i, temp->second);
			}
		}
	}
	else
	{
		std::cout << "Russian to english" << std::endl;
		std::map <WCHAR, WCHAR> RU_EN =
		{
			{ 1060, 65 },
			{ 1048, 66 },
			{ 1057, 67 },
			{ 1042, 68 },
			{ 1059, 69 },
			{ 1040, 70 },
			{ 1055, 71 },
			{ 1056, 72 },
			{ 1064, 73 },
			{ 1054, 74 },
			{ 1051, 75 },
			{ 1044, 76 },
			{ 1068, 77 },
			{ 1058, 78 },
			{ 1065, 79 },
			{ 1047, 80 },
			{ 1049, 81 },
			{ 1050, 82 },
			{ 1067, 83 },
			{ 1045, 84 },
			{ 1043, 85 },
			{ 1052, 86 },
			{ 1062, 87 },
			{ 1063, 88 },
			{ 1053, 89 },
			{ 1071, 90 },
			{ 1041, 60 },
			{ 1070, 62 },
			{ 44, 63 },
			{ 1046, 58 },
			{ 1069, 34 },
			{ 1061, 123 },
			{ 1066, 125 },
			{ 47, 124 },
			{ 34, 64 },
			{ 8470, 35 },
			{ 59, 36 },
			{ 58, 94 },
			{ 63, 38 },
			{ 1025, 126 },
			{ 1092, 97 },
			{ 1080, 98 },
			{ 1089, 99 },
			{ 1074, 100 },
			{ 1091, 101 },
			{ 1072, 102 },
			{ 1087, 103 },
			{ 1088, 104 },
			{ 1096, 105 },
			{ 1086, 106 },
			{ 1083, 107 },
			{ 1076, 108 },
			{ 1100, 109 },
			{ 1090, 110 },
			{ 1097, 111 },
			{ 1079, 112 },
			{ 1081, 113 },
			{ 1082, 114 },
			{ 1099, 115 },
			{ 1077, 116 },
			{ 1075, 117 },
			{ 1084, 118 },
			{ 1094, 119 },
			{ 1095, 120 },
			{ 1085, 121 },
			{ 1103, 122 },
			{ 1073, 44 },
			{ 1102, 46 },
			{ 46, 47 },
			{ 1078, 59 },
			{ 1101, 39 },
			{ 1093, 91 },
			{ 1098, 93 },
			{ 1105, 96 }
		};
		std::map <WCHAR, WCHAR>::iterator temp;
		for (int i = 0; i<num; i++)
		{
			temp = RU_EN.find(arr[i]);
			if (temp != RU_EN.end())
			{
				//arr[i] = temp->second;
				arr.SetAt(i, temp->second);
			}
		}
	}
	return;
}

void _modificate6(CStringW& arr)
{
	long num = arr.GetLength()+1;
	std::cout << "CAPS LOCK, length=" << num << std::endl;
	if (0 == num)	return;
	//std::cout << "CAPS LOCK, length=" << num << std::endl;
	int done = 0;
	for (int i = 0; i < num; i++)
	{
		//std::cout << "CAPS LOCK, sybol=" << i << std::endl;
		//EN:
		done = 0;
		if ((!done) && (arr[i]< 91) && (arr[i]> 64))
		{
			//arr[i] = arr[i] + 'a' - 'A';
			arr.SetAt(i, arr[i] + 'a' - 'A');
			done = 1;
		}
		if ((!done) && (arr[i]< 123) && (arr[i]> 96))
		{
			//arr[i] = arr[i] + 'A' - 'a';
			arr.SetAt(i, arr[i] + 'A' - 'a');
			done = 1;
		}
		//RU:
		//capital->small
		if ((!done) && (arr[i]< 0x0430) && (arr[i]> 0x040f))
		{
			done = 1;
			//arr[i] = arr[i] + 32;
			arr.SetAt(i, arr[i] + 32);
		}
		//small->capital
		if ((!done) && (arr[i]< 0x0450) && (arr[i]> 0x042f))
		{
			done = 1;
			//arr[i] = arr[i] -32;
			arr.SetAt(i, arr[i] - 32);
		}
		if (0x0451 == arr[i]) { arr.SetAt(i,0x0401); done = 1; } //E with ':'
		if ((!done) && (0x0401== arr[i])) arr.SetAt(i,0x0451);	//e with ':'
	}
}
