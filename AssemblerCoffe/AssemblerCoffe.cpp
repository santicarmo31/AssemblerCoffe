// PruebaCooffeStar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" //Reduce tiempo de compilación
#include <fstream> //Manejo de archivos
#include <iostream> //Entrada y salida de datos
#include <string> //Manejar String
#include <windows.h>
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
float ilg;
float uvts;										
float tarifaRetenFuente;					//Porcentaje UVTS

//Imprime detalles de numero de sueldos y recibe como argumento el salario inicial
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

//Imprime detalles del aporte a salud del empleado y recibe como argumento el salario inicial
float aporteSaludEmpleado(float nomina){
	float resultado = 0.00; //Resultado de operacion a retornar
	__asm {
		FLD dword ptr[nomina]; //Carga nomina al a posición(0) de la pila
		FLD dword ptr[APORTE_SALUD_EMPLEADO]; //Carga APORTE_SALUD_EMPLEADO al a posición(1) de la pila
		FMUL; //Multiplica el salario inicial por el 0.04% de aporte a la salud del empleado
		FSTP dword ptr[resultado]; //Almacena en resultado el valor de la ultima operacion realizada
	}
	return resultado;
}

//Imprime detalles del aporte a pension del empleado y recibe como argumento el salario inicial
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

//Imprime detalles del aporte a salud de la empresa y recibe como argumento el salario inicial
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

//Imprime detalles del aporte a pension de la empresa y recibe como argumento el salario inicial
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

//Imprime detalles si paga o no subsidio de transporte y recibe como argumento el numero de salarios minimos
float subsidioTransporte(float numSueldo){
	float resultado = 0.00;
	__asm {
		FLD dword ptr[numSueldo];
		FLD dword ptr[NUMERO_DOS];
		FCOMIP ST(0), ST(1); //Compara las posiciones 0 y 1 de la pila 
		JB nopaga; //Salta a retorno si numSuelo es menor igual a NUMERO_DOS
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
		JA esmayor20;
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
	esmayor20:
		FSTP dword ptr[resultado];
		FLD dword ptr[APORTE_FONDO_SOLIDARIDAD6];
		JMP retorno;
	retorno:
		FSTP dword ptr[resultado];
	}
	return resultado;
}

//Imprime detalles para encontrar el aporte al fondo de solidaridad pensional
float encontrarAporteFondoSolidaridadPensional(float porcentaje, float nomina){
	float resultado = 0.00;
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
float ingresoLaboralGravado(float salud, float pension, float fondo, float nomina){
	float resultado = 0.00;
	__asm {
		FLD dword ptr[nomina];
		FLD dword ptr[salud];
		FSUB;
		FLD dword ptr[pension];
		FSUB;
		FLD dword ptr[fondo];
		FSUB;
		FST dword ptr[ilg]; //Se almacena el ilg 
		FLD dword ptr[PORCENTAJE_ILG];
		FMUL;
		FSTP dword ptr[resultado];
		FLD dword ptr[ilg];
		FLD dword ptr[resultado];
		FSUB;
		FSTP dword ptr[resultado];
	}
	return resultado; //Es la base de la retencion en la fuente
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
		FCOMIP ST(0), ST(1); //compara 95 uvts con uvts 
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

float TotalSaludEmple(float acomulador, float valor){
	float resultado = 0.0;
	_asm{
		FLD dword ptr[acomulador];
		FLD dword ptr[valor];
		FADD;
		FSTP dword ptr[resultado]
	}
	return resultado;
}

float TotalSaludEmpre(float acomulador, float valor){
	float resultado = 0.0;
	_asm{
		FLD dword ptr[acomulador];
		FLD dword ptr[valor];
		FADD;
		FSTP dword ptr[resultado]
	}
	return resultado;
}

float TotalPensionEmple(float acomulador, float valor){
	float resultado = 0.0;
	_asm{
		FLD dword ptr[acomulador];
		FLD dword ptr[valor];
		FADD;
		FSTP dword ptr[resultado]
	}
	return resultado;
}

float TotalPensionEmpre(float acomulador, float valor){
	float resultado = 0.0;
	_asm{
		FLD dword ptr[acomulador];
		FLD dword ptr[valor];
		FADD;
		FSTP dword ptr[resultado]
	}
	return resultado;
}

float TotalAporteFondoPension(float acomulador, float valor){
	float resultado = 0.0;
	_asm{
		FLD dword ptr[acomulador];
		FLD dword ptr[valor];
		FADD;
		FSTP dword ptr[resultado]
	}
	return resultado;
}

float TotalRetenFuente(float acomulador, float valor){
	float resultado = 0.0;
	_asm{
		FLD dword ptr[acomulador];
		FLD dword ptr[valor];
		FADD;
		FSTP dword ptr[resultado]
	}
	return resultado;
}

string aproximar(float valor){
	int parte_entera,dosdecimales,tresdecimales,tercerdecimal;
	float aux,aux2;
	string res;
	parte_entera = valor / 1;
	dosdecimales = ((valor - parte_entera) *100);
	tresdecimales = ((valor-parte_entera)*1000);
	aux = ((valor - parte_entera)*100); //12.5
	tercerdecimal = aux; //12
	tercerdecimal = (aux - tercerdecimal) * 10;
	if (tresdecimales>0){
		if (tercerdecimal >= 5){
			//dosdecimales = dosdecimales + 1;
			if (dosdecimales >= 10){
				res = to_string(parte_entera) + "." + to_string(dosdecimales + 1);
			}
			else
			{   
				//res = to_string(parte_entera) + ".0" + to_string(dosdecimales + 1);
				if (dosdecimales < 9){
					res = to_string(parte_entera) + ".0" + to_string(dosdecimales + 1);
				}
				else
				{
					res = to_string(parte_entera) + "." + to_string(dosdecimales + 1);
				}
			}
		}
		else
		{
			if (dosdecimales<10){
				res = to_string(parte_entera) + ".0" + to_string(dosdecimales);
			}
			else
			{
				res = to_string(parte_entera) + "." + to_string(dosdecimales);
			}
		}
	}
	else
	{
		res = to_string(parte_entera) + ".00";
	}
	return res;
}

//Main principal
int _tmain(int argc, _TCHAR* argv[])
{
	ifstream inFile; //Manejar archivos
	inFile.open("nomina.txt"); //Archivo a abrir 
	float numSueldo = 0.0; //Numero de salarios mínimos mensuales actuales vigentes
	float saludemple = 0.0; //Mondo dado por el empleado a salud
	float saludEmpresa = 0.0; //Mondo subsidiado por el empleador a salud del empleado
	float pensionemple = 0.0; //Mondo dado por el empleado a pension
	float pensionEmpresa = 0.0; //Mondo subsidiado por el empleador a pension del empleado
	float fondo = 0.0; //Monto de salario a ser dado al fondo de solidaridad pensional
	float ingrelabgravado = 0.0; //Monto ingreso laboral gravado
	float aportefonsolipensio = 0.0; //Porcentaje de sueldo a ser dado al fondo de solidaridad pensional
	float retenenlafuente = 0.0; //Monto de rentencion en la fuente
	float subTransporte = 0.0; //Subsidio de transporte
	float salario = 0.0; //Salario final
	float totalAportesSaludEmple = 0.0; //Sumatoria de aportes a salud dado por los empleados
	float totalAportesSaludEmpre = 0.0; //Sumatoria de aportes a salud dado por el empleador
	float totalAportesPensionEmple = 0.0; //Sumatoria de aportes a pencion dado por los empleados
	float totalAportesPensionEmpre = 0.0; //Sumatoria de aportes a pension dado por empleador
	float totalAportesFondoPension = 0.0; //Sumatoria de aportes a fondo de solidaridad pensional
	float totalPagarDian = 0.0; //Sumatoria de total de montos de retencion en la fuente descontado a los empleados
	string salida = "";
	if (inFile.is_open()){
		while (!inFile.eof()){
			string cedula;
			string nombre;
			string sueldo;
			getline(inFile, cedula, ';');  //Obtener texto hasta el ";" el cual almacena en variable cédula
			getline(inFile, nombre, ';');  //Obtener texto hasta el ";" el cual almacena en variable nombre
			getline(inFile, sueldo, '\n'); //Obtener texto hasta el salto de línea "\n" el cual almacena en variable sueldo
			stringstream ss(sueldo); //Conversión de string a flotante 
			float nomina;
			ss >> nomina; //Traspaso de la conversión
			numSueldo = numeroDeMinimos(nomina); //Cálculo de número de salarios mínimos actuales vigentes que posee el salario 
			saludemple = aporteSaludEmpleado(nomina); //Cálculo monto de aporte a salud por parte del empleado
			saludEmpresa = aporteSaludEmpresa(nomina); //Cálculo monto de aporte a salud por parte del empleador
			pensionemple = aportePensionEmpleado(nomina);//Cálculo monto de aporte a pension por parte del empleado 
			pensionEmpresa = aportePensionEmpresa(nomina); //Cálculo monto de aporte a pension por parte del empleador
			aportefonsolipensio = aporteFondoSolidaridadPensional(numSueldo); //Cálculo porcentaje para aporte de solidaridad pensional
			fondo = encontrarAporteFondoSolidaridadPensional(aportefonsolipensio,nomina);//Cálculo aporte fondo de solidaridad pensional
			ingrelabgravado = ingresoLaboralGravado(saludemple, pensionemple, fondo,nomina); //Cálculo ingreso laboral gravado
			uvts = encontrarUvts(ingrelabgravado); //Cálculo de UVTS
			retenenlafuente = encontrarRetencionEnLaFuente(uvts, ingrelabgravado); //Cálculo retención en la fuente
			subTransporte = subsidioTransporte(numSueldo); //Cáculo subsidio de transporte
			salario = sueldoFinal(ilg, retenenlafuente, subTransporte); //Cáculo salario final
			
			//float uvt2(encontrarUvts(ingresoLaboralGravado(aporteSaludEmpleado(sueldoF), aportePensionEmpleado(sueldoF), encontrarAporteFondoSolidaridadPensional(aporteFondoSolidaridadPensional(numeroDeMinimos(sueldoF))))));
			//cout << cedula << nombre;
			
			salida = salida + cedula + ";" + nombre + ";" + sueldo; //aproximar(nomina) + ";" ;
			salida = salida + aproximar(numSueldo) + ";" + aproximar(saludemple) + ";";
			salida = salida + aproximar(saludEmpresa) + ";" + aproximar(pensionemple) + ";";
			salida = salida + aproximar(pensionEmpresa) + ";" + aproximar(fondo) + ";";
			salida = salida + aproximar(ilg) + ";" + aproximar(ingrelabgravado) + ";";
			salida = salida + aproximar(uvts) + ";" + aproximar(tarifaRetenFuente*100) + ";";
			salida = salida + aproximar(retenenlafuente) + ";" + aproximar(subTransporte);
			salida = salida + ";" + aproximar(salario) +  "; \n";

			totalAportesSaludEmple = TotalSaludEmple(totalAportesSaludEmple,saludemple);//Proceso de acomulación total salud empleados
			totalAportesSaludEmpre = TotalSaludEmpre(totalAportesSaludEmpre, saludEmpresa);//Proceso de acomulación total salud empleador
			totalAportesPensionEmple = TotalPensionEmple(totalAportesPensionEmple, pensionemple);//Proceso de acomulación total pesion empleados
			totalAportesPensionEmpre = TotalPensionEmpre(totalAportesPensionEmpre, pensionEmpresa);//Proceso de acomulación total pension de empleador
			totalAportesFondoPension = TotalAporteFondoPension(totalAportesFondoPension, fondo); //Proceso de acomulación total aportefondosolidaridad
			totalPagarDian = TotalRetenFuente(totalPagarDian, retenenlafuente); //Proceso de acomulación a pagar a la DIAN

			//Comentamos todo este párrafo para la entrega final, ya cuando pase la etapa de pruebas
			printf("El sueldo a evular es: %.2f\n", nomina);
			printf("El numero de minimos es: %.2f\n", numSueldo);
			printf("El subsidio de transporte es: %.2f\n", subTransporte);
			printf("El Aporte a Salud del empleado es: %.2f\n", saludemple);
			printf("El Aporte a Pension del empleado es: %.2f\n", pensionemple);
			printf("El porcentaje de aporte al fondo de solidaridad pensional es: %.2f\n", aportefonsolipensio);
			printf("El Aporte al fondo de solidaridad pensional es: %.2f\n", fondo);
			printf("El ilg es: %.2f\n", ilg);
			printf("La base en la retencion en la fuente es: %.2f\n", ingrelabgravado);
			printf("La cantidad de uvts: %.2f\n", uvts);
			printf("La retencion en la fuente es: %.2f\n", retenenlafuente);

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
		}
	}
	else{
		cout << "Error abriendo el archivo nomina.txt" << endl;
	}
	try{
		ofstream creararchivo("salidanomina.txt");
		creararchivo << salida;
		creararchivo.close();
		cout << "Se ha generado el archivo salidanomina.txt" << endl;
		printf("El total Aporte a salud empleados es: %.2f\n", totalAportesSaludEmple);
		printf("El total Aporte a salud empleador es: %.2f\n", totalAportesSaludEmpre);
		printf("El total Aporte a pension empleados es: %.2f\n", totalAportesPensionEmple);
		printf("El total Aporte a pension empleador es: %.2f\n", totalAportesPensionEmpre);
		printf("El total Aporte a fondo de seguridad pensional es: %.2f\n", totalAportesFondoPension);
		printf("El total a pagar a la DIAN es: %.2f\n", totalPagarDian);
		system("pause");
		return 0;
	} catch (exception ex){}
}

