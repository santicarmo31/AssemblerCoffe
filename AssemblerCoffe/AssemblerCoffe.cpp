// PruebaCooffeStar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" //Reduce tiempo de compilación
#include <fstream> //Manejo de archivos
#include <iostream> //Entrada y salida de datos
#include <string> //Manejar String
#include <windows.h>
#include<conio.h>
#include <sstream> 

using namespace std;

float SUELDO_BASICO = 644350.00;			//sueldo basico para calculos (ejem: para encontrar numMinimos)
float SUBSIDIO_TRANSPORTE = 74000.00;		//subsidio de transporte para calculos
float APORTE_SALUD_EMPLEADO = 0.04;			//porcentaje de aporte a la salud por parte de los empleados (4%)
float APORTE_PENSION_EMPLEADO = 0.04;		//porcentaje de aporte a la pension por parte de los empleados (4%)
float APORTE_SALUD_EMPRESA = 0.045;			//porcentaje de aporte a la salud por parte de los empresa (4.5%)
float APORTE_PENSION_EMPRESA = 0.08;		//porcentaje de aporte a la pension por parte de los empresa (8%)
float APORTE_FONDO_SOLIDARIDAD1 = 0.01;		//porcentaje de aporte al fondo de solidaridad pensional (1%)
float APORTE_FONDO_SOLIDARIDAD2 = 0.012;	//porcentaje de aporte al fondo de solidaridad pensional (1.2%)
float APORTE_FONDO_SOLIDARIDAD3 = 0.014;	//porcentaje de aporte al fondo de solidaridad pensional (1.4%)
float APORTE_FONDO_SOLIDARIDAD4 = 0.016;	//porcentaje de aporte al fondo de solidaridad pensional (1.6%)
float APORTE_FONDO_SOLIDARIDAD5 = 0.018;	//porcentaje de aporte al fondo de solidaridad pensional (1.8%)
float APORTE_FONDO_SOLIDARIDAD6 = 0.02;		//porcentaje de aporte al fondo de solidaridad pensional (2%)
float NUMERO_DOS = 2.00;
float NUMERO_CUATRO = 4.00;					//numero 4 para calculos en aporte al fondo de solidaridad pensional
float NUMERO_16 = 16.00;					//numero 16 para calculos en aporte al fondo de solidaridad pensional
float NUMERO_17 = 17.00;					//numero 17 para calculos en aporte al fondo de solidaridad pensional
float NUMERO_18 = 18.00;					//numero 18 para calculos en aporte al fondo de solidaridad pensional
float NUMERO_19 = 19.00;					//numero 19 para calculos en aporte al fondo de solidaridad pensional
float NUMERO_20 = 20.00;					//numero 20 para calculos en aporte al fondo de solidaridad pensional
float PORCENTAJE_ILG = 0.25;				//porcentaje para encontrar el ilg en pesos (25%)
float PESOS_EN_UVTs = 28279.00;				//pesos en uvts para dividirlo al ilg y asi encontrar los uvts para calculos en la retencion
float UVTS_10 = 10.00;                      //UVTS cuando uvts < 360
float UVTS_69 = 69.00;						//UVTS cuando uvts >360
float UVTS_95 = 95.00;						//numero 95 para calculos en retencion en la fuente
float UVTS_150 = 150.00;					//numero 150 para calculos en retencion en la fuente
float UVTS_360 = 360.00;					//numero 360 para calculos en retencion en la fuente
float PORCENTAJE_UVTS19 = 0.19;				//porcentaje para calculos en retencion en la fuente (19%)
float PORCENTAJE_UVTS28 = 0.28;				//porcentaje para calculos en retencion en la fuente (28%)
float PORCENTAJE_UVTS33 = 0.33;				//porcentaje para calculos en retencion en la fuente (33%)
float LIMPIAR_REGISTROS = 0.0;				//variable para limpiar registros
//float nomina = 645000.00; 
float numSueldo;
float ilg;
float uvts;
float tarifaRetenFuente;

//Imprime detalles de numero de sueldos
float numeroDeMinimos(float nomina) {
	float resultado = 0.00;
	__asm {
		FLD dword ptr[nomina];
		FLD dword ptr[SUELDO_BASICO];
		FDIV;
		FSTP dword ptr[resultado];
	}
	return resultado;
}

//Imprime detalles del aporte a salud del empleado
float aporteSaludEmpleado(float nomina){
	float resultado = 0.00;
	__asm {
		FLD dword ptr[nomina];
		FLD dword ptr[APORTE_SALUD_EMPLEADO];
		FMUL;
		FSTP dword ptr[resultado];
	}
	return resultado;
}

//Imprime detalles del aporte a pension del empleado
float aporteSaludEmpresa(float nomina){
	float resultado = 0.00;
	__asm {
		FLD dword ptr[nomina];
		FLD dword ptr[APORTE_SALUD_EMPRESA];
		FMUL;
		FSTP dword ptr[resultado];
	}
	return resultado;
}

//Imprime detalles del aporte a salud de la empresa
float aportePensionEmpleado(float nomina){
	float resultado = 0.00;
	__asm {
		FLD dword ptr[nomina];
		FLD dword ptr[APORTE_PENSION_EMPLEADO];
		FMUL;
		FSTP dword ptr[resultado];
	}
	return resultado;
}

//Imprime detalles del aporte a pension de la empresa
float aportePensionEmpresa(float nomina){
	float resultado = 0.00;
	__asm {
		FLD dword ptr[nomina];
		FLD dword ptr[APORTE_PENSION_EMPRESA];
		FMUL;
		FSTP dword ptr[resultado];
	}
	return resultado;
}

//Imprime detalles si paga o no subsidio de transporte
float subsidioTransporte(float numSueldo){
	float resultado = 0.00;
	__asm {
		FLD dword ptr[numSueldo];//7
		FLD dword ptr[NUMERO_DOS];//2
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

//Imprime detalles de calculos para fondo de solidaridad pensional
float aporteFondoSolidaridadPensional(float numSueldo){
	float resultado = 0.00;
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

//Imprime detalles para encontrar el aporte al fondo de solidaridad pensional
float encontrarAporteFondoSolidaridadPensional(float porcentaje,float nomina){
	float resultado = 0.00;
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

//Encontrar el ILG en pesos para comparar con UVTS
float ingresoLaboralGravado(float salud, float pension, float fondo,float nomina){
	float resultado = 0.00;
	__asm {
		FLD dword ptr[nomina];
		FLD dword ptr[salud];
		FSUB;
		FLD dword ptr[pension];
		FSUB;
		FLD dword ptr[fondo];
		FSUB;
		FST dword ptr[ilg]; // se almacena el ilg 
		FLD dword ptr[PORCENTAJE_ILG];
		FMUL;
		FSTP dword ptr[resultado];
		FLD dword ptr[ilg];
		FLD dword ptr[resultado];
		FSUB;
		FSTP dword ptr[resultado];
	}
	return resultado; // es la base de la retencion en la fuente
}

//Imprime detalles para encontrar los UVTs 
float encontrarUvts(float valor){
	float resultado = 0.00;
	__asm{
		FLD dword ptr[valor];
		FLD dword ptr[PESOS_EN_UVTs];
		FDIV;
		FSTP dword ptr[resultado];
	}
	return resultado;
}

//Imprime detalles para encontrar la rentencion en la fuente
float encontrarRetencionEnLaFuente(float uvts, float BGP){
	float resultado = 0.0;
	__asm{
		FLD dword ptr[UVTS_95]; //Carga en la pila(0) el 95
		FLD dword ptr[uvts]; //carga en la pila(1) el valor de uvts 
		FCOMIP ST(0), ST(1); //compara 95 uvt  con  uvt 
		JB nopaga; //Si uvts es menor a 95 
		FSTP dword ptr[resultado];
		FLD dword ptr[UVTS_150]; //carga 150 uvt 
		FLD dword ptr[uvts];   //carga 120.67 uvt 
		FCOMIP ST(0), ST(1);   
		JB esmenor150; 
		FSTP dword ptr[resultado];
		FLD dword ptr[UVTS_360];
		FLD dword ptr[uvts];
		FCOMIP ST(0), ST(1);
		JB esmenor360;
		JA esmayor360;
	nopaga:
		//FSTP dword ptr[resultado];
		FLD dword ptr[LIMPIAR_REGISTROS];
		FST dword ptr[tarifaRetenFuente];
		JMP retorno;
	esmenor150:
		FLD dword ptr[uvts];
		FLD dword ptr[UVTS_95];
		FSUB;
		FLD dword ptr[PORCENTAJE_UVTS19];
		FST dword ptr[tarifaRetenFuente];
		FMUL;
		FLD dword ptr[BGP];
		FMUL;
		FLD dword ptr[uvts];
		FDIV;
		JMP retorno;
	esmenor360:
		//FSTP dword ptr[resultado];
		//FLD dword ptr[PORCENTAJE_UVTS28];
		FLD dword ptr[uvts];
		FLD dword ptr[UVTS_150];
		FSUB;
		FLD dword ptr[PORCENTAJE_UVTS28];
		FST dword ptr[tarifaRetenFuente];
		FMUL;
		FLD dword ptr[UVTS_10];
		FADD;
		FLD dword ptr[BGP];
		FMUL;
		FLD dword ptr[uvts];
		FDIV;
		JMP retorno;
	esmayor360:
		//7FSTP dword ptr[resultado];
		//FLD dword ptr[PORCENTAJE_UVTS33];
		FLD dword ptr[uvts];
		FLD dword ptr[UVTS_360];
		FSUB;
		FLD dword ptr[PORCENTAJE_UVTS33];
		FMUL;
		FLD dword ptr[UVTS_69];
		FSUB;
		FLD dword ptr[BGP];
		FMUL;
		FLD dword ptr[uvts];
		FDIV;
		JMP retorno;
	retorno:
		FSTP dword ptr[resultado];
	}
	return resultado;
}

float sueldoFinal(float ILB, float retencion, float transporte){
	float resultado;
	_asm{
		FLD dword ptr[ILB];
		FLD dword ptr[retencion];
		FSUB;
		FLD dword ptr[transporte];
		FADD;
		FSTP dword ptr[resultado]
	}
	return resultado;
}

//Main principal
int _tmain(int argc, _TCHAR* argv[])
{
	ifstream inFile;
	inFile.open("nomina.txt");
	
	float numSueldo;
	float saludemple;
	float saludEmpresa;
	float pensionemple;
	float pensionEmpresa;
	float fondo;
	float ingrelabgravado;
	float aportefonsolipensio;
	float retenenlafuente;
	float subTransporte;
	float salario;
	string salida = "";
	if (inFile.is_open()){
		while (!inFile.eof()){
			string cedula;
			string nombre;
			string sueldo;
			getline(inFile, cedula, ';');
			getline(inFile, nombre, ';');
			getline(inFile, sueldo, '\n');
			stringstream ss(sueldo);
			float nomina;
			ss >> nomina;
			numSueldo = numeroDeMinimos(nomina);
			saludemple = aporteSaludEmpleado(nomina);
			saludEmpresa = aporteSaludEmpresa(nomina);
			pensionemple = aportePensionEmpleado(nomina);
			pensionEmpresa = aportePensionEmpresa(nomina);
			aportefonsolipensio = aporteFondoSolidaridadPensional(numSueldo);
			fondo = encontrarAporteFondoSolidaridadPensional(aportefonsolipensio,nomina);
			ingrelabgravado = ingresoLaboralGravado(saludemple, pensionemple, fondo,nomina);
			uvts = encontrarUvts(ingrelabgravado);
			retenenlafuente = encontrarRetencionEnLaFuente(uvts, ingrelabgravado);
			subTransporte = subsidioTransporte(numSueldo);
			salario = sueldoFinal(ilg, retenenlafuente, subTransporte);
			//float uvt2(encontrarUvts(ingresoLaboralGravado(aporteSaludEmpleado(sueldoF), aportePensionEmpleado(sueldoF), encontrarAporteFondoSolidaridadPensional(aporteFondoSolidaridadPensional(numeroDeMinimos(sueldoF))))));
			//cout << cedula << nombre;
			
			salida = salida + cedula + ";" + nombre + ";" + to_string(nomina) + ";";
			salida = salida + to_string(numSueldo) + ";" + to_string(saludemple) + ";";
			salida = salida + to_string(saludEmpresa) + ";" + to_string(pensionemple) + ";";
			salida = salida + to_string(pensionEmpresa) + ";" + to_string(fondo) + ";";
			salida = salida + to_string(ilg) + ";" + to_string(ingrelabgravado) + ";";
			salida = salida + to_string(uvts) + ";" + to_string(tarifaRetenFuente) + ";";
			salida = salida + to_string(subTransporte) + ";" + to_string(salario) + "; \n";

			/*
			numSueldo = 0.0;
			saludemple = 0.0;
			saludEmpresa = 0.0;
			pensionemple = 0.0;
			pensionEmpresa = 0.0;
			fondo = 0.0;
			ingrelabgravado = 0.0;
			aportefonsolipensio = 0.0;
			retenenlafuente = 0.0;
			subTransporte = 0.0;
			salario = 0.0;
			*/

			printf("%.2f\n", nomina);
			printf("El numero de minimos es: %.2f\n", numSueldo);
			printf("El subsidio de transporte es: %.2f\n", subTransporte);
			printf("El Aporte a Salud del empleado es: %.2f\n", saludemple);
			printf("El Aporte a Pension del empleado es: %.2f\n", pensionemple);
			printf("El porcentaje de aporte al fondo de solidaridad pensional es: %.2f\n", aportefonsolipensio);
			printf("El Aporte al fondo de solidaridad pensional es: %.2f\n", fondo);
			printf("el ilg es : %.2f\n", ilg);
			printf("La base en la retencion en la fuente es : %.2f\n", ingrelabgravado);
			printf("La cantidad de uvts: %.2f\n", uvts);
			printf("el porcentaje en la retencion en la fuente es: %.2f\n", retenenlafuente);
		}
	}
	else{
		cout << "Error abriendo el archivo nomina.txt" << endl;
	}
	try{
		ofstream creararchivo("salidaarchivo.txt");
		creararchivo << salida;
		creararchivo.close();
		cout << "Se ha generado el archivo salidaarchivo.txt" << endl;
		system("pause");
		return 0;
	} catch (exception ex){}
}

