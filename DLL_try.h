/*
#ifdef DLL_TRY
#define DLL_TRY_F __declspec (dllexport)
#else
#define DLL_TRY_F __declspec (dllimport)
#endif
*/
//#include <Windows.h>
#include <afx.h>
extern "C" __declspec (dllexport) void _modificate1(unsigned char* arr, int num);
extern "C" __declspec (dllexport) void _modificate2(unsigned char* arr, int num);
extern "C" __declspec (dllexport) void _modificate3(char* arr, int num);
extern "C" __declspec (dllexport) void _modificate4(char* arr, int num);
extern "C" __declspec (dllexport) void _modificate5(CStringW& arr, int& code);
extern "C" __declspec (dllexport) void _modificate6(CStringW& arr);
