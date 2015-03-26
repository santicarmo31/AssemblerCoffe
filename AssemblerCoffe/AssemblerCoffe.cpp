// PruebaCooffeStar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <sstream>

using namespace std;

float SUELDO_BASICO = 644350.00;
float SUBSIDIO_TRANSPORTE = 74000.00;
float APORTE_SALUD_EMPLEADO = 0.04;
float APORTE_PENSION_EMPLEADO = 0.04;
float APORTE_SALUD_EMPRESA = 0.045;
float APORTE_PENSION_EMPRESA = 0.08;
float APORTE_FONDO_SOLIDARIDAD1 = 0.01;
float APORTE_FONDO_SOLIDARIDAD2 = 0.012;
float APORTE_FONDO_SOLIDARIDAD3 = 0.014;
float APORTE_FONDO_SOLIDARIDAD4 = 0.016;
float APORTE_FONDO_SOLIDARIDAD5 = 0.018;
float APORTE_FONDO_SOLIDARIDAD6 = 0.02;
float COMPARACION_AFSP1 = 4.0;
float COMPARACION_AFSP2 = 16.0;
float COMPARACION_AFSP3 = 17.0;
float COMPARACION_AFSP4 = 18.0;
float COMPARACION_AFSP5 = 19.0;
float COMPARACION_AFSP6 = 20.0;
float NUMERO_DOS = 2.00;
float NUMERO_CUATRO = 4.00;
float NUMERO_16 = 16.00;
float NUMERO_17 = 17.00;
float NUMERO_18 = 18.00;
float NUMERO_19 = 19.00;
float NUMERO_20 = 20.00;
float PORCENTAJE_ILG = 0.25;
float PESOS_EN_UVTs = 28279.00;
float UVTS_95 = 95.00;
float UVTS_150 = 150.00;
float UVTS_360 = 360.00;
float PORCENTAJE_UVTS19 = 0.19;
float PORCENTAJE_UVTS28 = 0.28;
float PORCENTAJE_UVTS33 = 0.33;
float LIMPIAR_REGISTROS = 0.0;
float nomina = 2577400.00;
float numSueldo;

//Imprime detalles de sueldo
float numeroDeMinimos(float nomina) {
	float resultado;
	__asm {
		FLD dword ptr[nomina];
		FLD dword ptr[SUELDO_BASICO];
		FDIV;
		FSTP dword ptr[resultado];
	}
	return resultado;
}

float aporteSaludEmpleado(float nomina){
	float resultado;
	__asm {
		FLD dword ptr[nomina];
		FLD dword ptr[APORTE_SALUD_EMPLEADO];
		FMUL;
		FSTP dword ptr[resultado];
	}
	return resultado;
}
float aporteSaludEmpresa(float nomina){
	float resultado;
	__asm {
		FLD dword ptr[nomina];
		FLD dword ptr[APORTE_SALUD_EMPRESA];
		FMUL;
		FSTP dword ptr[resultado];
	}
	return resultado;
}

float aportePensionEmpleado(float nomina){
	float resultado;
	__asm {
		FLD dword ptr[nomina];
		FLD dword ptr[APORTE_PENSION_EMPLEADO];
		FMUL;
		FSTP dword ptr[resultado];
	}
	return resultado;
}

float aportePensionEmpresa(float nomina){
	float resultado;
	__asm {
		FLD dword ptr[nomina];
		FLD dword ptr[APORTE_PENSION_EMPRESA];
		FMUL;
		FSTP dword ptr[resultado];
	}
	return resultado;
}

float subsidioTransporte(float numSueldo){
	float resultado;
	__asm {
		FLD dword ptr[numSueldo];
		FLD dword ptr[NUMERO_DOS];
		FCOMIP ST(0), ST(1);
		JB nopaga;
		FSTP dword ptr[resultado];
		FLD dword ptr[SUBSIDIO_TRANSPORTE];
		JMP retorno;
	nopaga:
		FSTP dword ptr[resultado];
		FLD dword ptr[LIMPIAR_REGISTROS];
		JMP retorno;
	retorno:
		FSTP dword ptr[resultado];
	}
	return resultado;
}

float aporteFondoSolidaridadPensional(float numSueldo){
	float resultado;
	__asm {
		FLD dword ptr[NUMERO_CUATRO];
		FLD dword ptr[numSueldo];
		FCOMIP ST(0), ST(1);
		JB nopaga;
		FSTP dword ptr[resultado];
		FLD dword ptr[NUMERO_16];
		FLD dword ptr[numSueldo];
		FCOMIP ST(0), ST(1);
		JB esmenor16;
		FSTP dword ptr[resultado];
		FLD dword ptr[NUMERO_17];
		FLD dword ptr[numSueldo];
		FCOMIP ST(0), ST(1);
		JB esmenor17;
		FSTP dword ptr[resultado];
		FLD dword ptr[NUMERO_18];
		FLD dword ptr[numSueldo];
		FCOMIP ST(0), ST(1);
		JB esmenor18;
		FLD dword ptr[NUMERO_19];
		FLD dword ptr[numSueldo];
		FCOMIP ST(0), ST(1);
		JB esmenor19;
		FSTP dword ptr[resultado];
		FLD dword ptr[NUMERO_20];
		FLD dword ptr[numSueldo];
		FCOMIP ST(0), ST(1);
		JB esmenor20;
		JA es20mas;
	nopaga:
		FSTP dword ptr[resultado];
		FLD dword ptr[LIMPIAR_REGISTROS];
		JMP retorno;
	esmenor16:
		FSTP dword ptr[resultado];
		FLD dword ptr[APORTE_FONDO_SOLIDARIDAD1];
		JMP retorno;
	esmenor17:
		FSTP dword ptr[resultado];
		FLD dword ptr[APORTE_FONDO_SOLIDARIDAD2];
		JMP retorno;
	esmenor18:
		FSTP dword ptr[resultado];
		FLD dword ptr[APORTE_FONDO_SOLIDARIDAD3];
		JMP retorno;
	esmenor19:
		FSTP dword ptr[resultado];
		FLD dword ptr[APORTE_FONDO_SOLIDARIDAD4];
		JMP retorno;
	esmenor20:
		FSTP dword ptr[resultado];
		FLD dword ptr[APORTE_FONDO_SOLIDARIDAD5];
		JMP retorno;
	es20mas:
		FSTP dword ptr[resultado];
		FLD dword ptr[APORTE_FONDO_SOLIDARIDAD6];
		JMP retorno;
	retorno:
		FSTP dword ptr[resultado];
	}
	return resultado;
}

float encontrarAporteFondoSolidaridadPensional(float porcentaje){
	float resultado;
	cout << porcentaje << endl;
	if (porcentaje > 0){
		__asm {
			FLD dword ptr[nomina];
			FLD dword ptr[porcentaje];
			FMUL;
			FSTP dword ptr[resultado];
		}
	}
	return resultado;
}


//Encontrar el ILG en pesos para comparar con UVTS, aun no esta terminado
float ingresoLaboralGravado(float salud, float pension, float fondo){
	float resultado;
	float ilg;
	__asm {
		FLD dword ptr[nomina];
		FLD dword ptr[salud];
		FSUB;
		FLD dword ptr[pension];
		FSUB;
		FLD dword ptr[fondo];
		FSUB;
		FST dword ptr[ilg];
		FLD dword ptr[PORCENTAJE_ILG];
		FMUL;
		FSTP dword ptr[resultado];
		FLD dword ptr[ilg];
		FLD dword ptr[resultado];
		FSUB;
		FSTP dword ptr[resultado];
		
	}
	return resultado;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream inFile;
	inFile.open("nomina.txt");
	numSueldo = numeroDeMinimos(nomina);
	float salud = aporteSaludEmpleado(nomina);
	float pension = aportePensionEmpleado(nomina);
	float fondo = encontrarAporteFondoSolidaridadPensional(aporteFondoSolidaridadPensional(numSueldo));
	if (inFile.is_open()){
		while (!inFile.eof()){
			string cedula;
			string nombre;
			string sueldo;
			getline(inFile, cedula, ';');
			getline(inFile, nombre, ';');
			getline(inFile, sueldo, ';');
			stringstream ss(sueldo);
			float sueldoF;
			ss >> sueldoF;
			cout << cedula << nombre;
			printf("%.2f\n", nomina);
			printf("El numero de minimos es: %.2f\n", numeroDeMinimos(nomina));
			printf("El subsidio de transporte es: %.2f\n", subsidioTransporte(numeroDeMinimos(nomina)));
			printf("El Aporte a Salud del empleado es: %.2f\n", aporteSaludEmpleado(nomina));
			printf("El Aporte a Pension del empleado es: %.2f\n", aportePensionEmpleado(nomina));
			printf("El porcentaje de aporte al fondo de solidaridad pensional es: %.2f\n", aporteFondoSolidaridadPensional(numSueldo));
			printf("El Aporte al fondo de solidaridad pensional es: %.2f\n", fondo);
			printf("El ILG: %.2f\n", ingresoLaboralGravado(salud,pension,fondo));
		}
	}
	else{
		cout << "Error abriendo el archivo nomina.txt" << endl;
	}
	return 0;
}


