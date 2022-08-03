#include<iostream>
#include<vector>
#include<iomanip>
#include<string>
#include<conio.h>
#include "Textable.h"
#include <windows.h>
#include<locale.h>//librería para idioma y acentos
#include<fstream>//Libreria para el procesamiento de archivos de texto

//FUNCIÓN QUE ELIMINA EL PRIMER ELEMENTO DE UN VECTOR, UNA VARIANTE DE POP_BACK
void pop_front(std::vector<int> &v)
{
    if (v.size() > 0) {
        v.erase(v.begin());
    }
}

using namespace std;
//PROTOTIPOS DE FUNCIONES QUE VALIDAN LOS CAMPOS QUE INGRESARÁN AL SISTEMA
bool checkForfilewrmInt(vector<int> arr, int data); //recibe vector tipo int y dato a evaluar tipo int
bool checkForfilewrmString(vector<string> arr, string data); //recibe vector tipo string y dato a evaluar tipo string
bool checkForfilewrmDate(int anioTaxi); //recibe un dato a evaluar tipo date, valida rango: año < 2010, el cual no es valido

//PROTOTIPOS DE FUNCIONES QUE IMPRIMEN COLA DISPONIBLE (TANTO T & E) Y COLA EN RUTA (TANTO T & E)
void printTableD(vector<int> colaDisponibleT, vector<int> colaDisponibleE, vector<int> vTaxi, vector<string> vPlaca, vector<string> vModelo, vector<string> vMarca, vector<int> vAnio, vector<string> vCategoria, vector<string> vTransmision, vector<string> vConductorNombre, vector<string> vConductorApellido, vector<string> vConductorLicencia, vector<string> vConductorDui, vector<string> vConductorTelefono, vector<int> vConductorEdad); //recibe vectores de disponibles a imprimir
void printTableR(vector<int> colaRutaT, vector<int> colaRutaE, vector<int> vTaxi, vector<string> vPlaca, vector<string> vModelo, vector<string> vMarca, vector<int> vAnio, vector<string> vCategoria, vector<string> vTransmision, vector<string> vConductorNombre, vector<string> vConductorApellido, vector<string> vConductorLicencia, vector<string> vConductorDui, vector<string> vConductorTelefono, vector<int> vConductorEdad); //recibe vectores de en ruta a imprimir
void printTableV(vector<int> vSol, vector<string> vSolCategoriaViaje, vector<string> vSolInicioViaje, vector<string> vSolFinViaje, vector<double> vSolCostoViaje, vector<int> vSolIdTaxi, vector<int> vTaxi, vector<string> vPlaca, vector<string> vModelo, vector<string> vConductorNombre, vector<string> vConductorApellido, vector<string> vConductorLicencia);

//Prototipos para archivos txt
void printTxt(vector<int> vTaxi, vector<string> vPlaca, vector<string> vModelo, vector<string> vMarca, vector<int> vAnio, vector<string> vCategoria, vector<string> vTransmision, vector<string> vConductorNombre, vector<string> vConductorApellido, vector<string> vConductorLicencia, vector<string> vConductorDui, vector<string> vConductorTelefono, vector<int> vConductorEdad);   //recibe datos del condcutor y los autos para la filewrura y escritura en un fichero txt

//PROTOTIPO DE FUNCIÓN QUE REMOVERÁ AL TAXI DESEADO DE LA COLA EN RUTA Y REDIMENSIONARÁ ESE VECTOR Y AGREGARÁ A COLA DISPONIBLE
vector<int> eliminarPosicion(int rePosicion, vector<int> &colaRuta); //función que elimina el dato especificado por posición, en las colas de ruta tradicional y ejecutiva

int main(){
	setlocale(LC_CTYPE, "Spanish");//para idioma y acentos
	char continuar='\0'; //recibe s,S,n,N que decide si se seguirá ejecutando el programa
	int opcion; //respuesta seleccionada del menu
	string decisionCategoria; //almacenará la categoría a la que pertenece el taxi, en función de su año de fabricación
	string decisionTransmision; //almacenará el tipo de transmisión que posee el taxi

	//DECLARACIÓN DE VECTORES QUE ALMACENARÁN CADA DATO IMPORTANTE DEL TAXI Y SU CONDUCTOR
	vector<int> vTaxi; //vector que almacena todos los ID de los taxis
	vector<string> vPlaca; //vector que almacena todas los placas de los taxis
	vector<string> vNumeroMotor; //vector qwe almacena todos los números de motor de los taxis
	vector<string> vModelo; //vector que almacena todos los módelos de los taxis
	vector<string> vMarca; //vector que almacena todas las marcas de los taxis
	vector<int> vAnio; //vector que almacena todos los años de fabricación de los taxis
	vector<string> vTransmision; //vector que almacena todas las transmisiones de los taxis
	vector<string> vCategoria; //vector que almacena las categorías de los taxis

	vector<string> vConductorNombre; //vector que almacena todos los nombres de los conductores
	vector<string> vConductorApellido; //vector que almacena todos los apellidos de los conductores
	vector<string> vConductorDui; //vector que almacena todos los DUI de los conductores
	vector<string> vConductorIsss; //vector que almacena todos los números de seguro de los conductores
	vector<string> vConductorTelefono; //vector que almacena todos los números telefónicos de los conductores
	vector<string> vConductorLicencia; //vector que almacena todas los números de licencia de los conductores
	vector<int> vConductorEdad; //vector que almacena todas las edades de los conductores
	
	//DECLARACIÓN DE DATO QUE SE TOMA EN CADA CICLO Y QUE SE SOBREESCRIBE EN EL SIGUIENTE CICLO
	int filewrmTaxi; ////ID del taxi que se captura e ingresa en el vector respectivo
	string filewrmPlaca; //placas que se capturan e ingresarán en el vector respectivo
	string filewrmNumeroMotor; //número de motor que se captura e ingresa en el vector respectivo
	string filewrmModelo; //modelo que se captura e ingresa en el vector respectivo
	string filewrmMarca; //marca que se captura e ingresa en el vector respectivo
	int filewrmAnio; ////año de fabricación que se captura e ingresa en el vector respectivo
	string filewrmTransmision; //transmisión que se captura e ingresa en el vector respectivo
	string filewrmCategoria; //categoría del taxi, en función de su año de fabricación

	string filewrmConductorNombre; //nombres que se captura e ingresa en el vector respectivo
	string filewrmConductorApellido; //apellidos que se captura e ingresa en el vector respectivo
	string filewrmConductorDui; //DUI que se captura e ingresa en el vector respectivo
	string filewrmConductorIsss; //número de seguro que se captura e ingresa en el vector respectivo
	string filewrmConductorTelefono; //número teléfonico que se captura e ingresa en el vector respectivo
	string filewrmConductorLicencia; //número de licencia que se captura e ingresa en el vector respectivo
	int filewrmConductorEdad; //edad que se captura e ingresa en el vector respectivo
	
	//DECLARACIÓN DE VECTORES QUE TENDRÁN LOS IDS DEL TAXI, EN FUNCIÓN DE SU CATEGORÍA Y SU ESTADO (DISPONIBLE, EN RUTA)
	vector<int> colaDisponibleT; //controlará orden de taxis tradicionales disponibles
	vector<int> colaDisponibleE; //controlará orden de taxis ejecutivos disponibles
    vector<int> colaRutaT; //controlará orden de taxis tradicionales en ruta
    vector<int> colaRutaE; //controlará orden de taxis ejecutivos en ruta

	//DATOS USADOS EN LA SOLICITUD DE VIAJE (DE COLA DISPONIBLE A COLA EN RUTA)
	vector<int> vSol; //vector que almacena todos los ID de las solicitudes
	vector<string> vSolCategoriaViaje; //vector que almacena todas las categorías de las solicitudes
	vector<string> vSolInicioViaje; //vector que almacena todos los inicios de los viajes solicitados
	vector<string> vSolFinViaje; //vector que almacena todos los finales de los viajes solicitados
	vector<double> vSolCostoViaje; //vector que almacena todos los costos de los viajes solicitados
	vector<int> vSolIdTaxi; //vector que almacena los ID de los taxis que realizan los viajes. No se necesita item incersi�n directa
	
	int filewrmSol; //identificador de la solicitud que está gestionando el usuario
	int filewrmSolCategoriaViaje; //categoría del taxi que está solicitando el usuario
	string filewrmSolInicioViaje; //donde iniciará el viaje solicitado por el usuario
	string filewrmSolFinViaje; //donde finalizará el viaje solicitado por el usuario
	double filewrmSolCostoViaje; //dinero que costará el viaje solicitado por el usuario
	
	//DATOS USADOS EN REINGRESO DE TAXI, FINALZIACIÓN DEL VIAJE (DE COLA EN RUTA A COLA DISPONIBLE)
	int reCategoriaViaje; //categoría del taxi que finalizó el viaje y volverá a quedar disponible
	int reIdTaxi; //identificador del taxi que acabó el viaje y volverá a quedar disponible
	int rePosicion; //lugar donde está almacenado el identificador del taxi que acabó el viaje y volverá a quedar disponible
	
	int count = 1; //variable para hacer que forzar que un ciclo se ejecuta una sola vez
	int suma = 0; //variable para la suma de ingresos de los veh�culos

	int idBuscarTaxi = 0; //servir� para buscar datos de un taxi en especifico
	bool existe; //bandera para verificar si el taxi existe.
	TextTable t( '-', '|', '+' ); //servir� para los headers de la tabla de busqueda de taxi
    //TextTable r( '-', '|', '+' ); //servir� para los headers de la tabla de busqueda de taxi
	int taxisEncontrados = 0; //contar� si encuentra viajes del taxi en especifico

    //INICIO CARGA DE DATOS DESDE TXT
	string line;
    ifstream frd ("CARS_STORAGE.txt");
	if(frd.is_open()){
		while(true) {
            getline(frd, line);
            if(line.length()!=0){
                vTaxi.push_back(stoi(line));
                getline(frd, line);
                vPlaca.push_back(line);
                getline(frd, line);
                vModelo.push_back(line);
                getline(frd, line);
                vMarca.push_back(line);
                getline(frd, line);
                vAnio.push_back(stoi(line));
                getline(frd, line);
                vCategoria.push_back(line);
                getline(frd, line);
                vTransmision.push_back(line);
                getline(frd, line);
                vConductorNombre.push_back(line);
                getline(frd, line);
                vConductorApellido.push_back(line);
                getline(frd, line);
                vConductorLicencia.push_back(line);
                getline(frd, line);
                vConductorDui.push_back(line);
                getline(frd, line);
                vConductorTelefono.push_back(line);
                getline(frd, line);
                vConductorEdad.push_back(stoi(line));
            }
            else{
                break;
            }
		}
		frd.close();
	}

    ifstream frd_disponibleT ("COLA_DISPONIBLE_T.txt");
	if(frd_disponibleT.is_open()){
		while(true) {
            getline(frd_disponibleT, line);
            if(line.length()!=0){
                colaDisponibleT.push_back(stoi(line));
            }
            else{
                break;
            }
		}
		frd_disponibleT.close();
	}
	else{
		for(int i=0; i<vTaxi.size(); i++){
			if(vCategoria.at(i)=="Tradicional"){
				colaDisponibleT.push_back(vTaxi.at(i));
			}
		}
	}

    ifstream frd_disponibleE ("COLA_DISPONIBLE_E.txt");
	if(frd_disponibleE.is_open()){
		while(true) {
            getline(frd_disponibleE, line);
            if(line.length()!=0){
                colaDisponibleE.push_back(stoi(line));
            }
            else{
                break;
            }
		}
		frd_disponibleE.close();
	}
	else{
		for(int i=0; i<vTaxi.size(); i++){
			if(vCategoria.at(i)=="Ejecutiva"){
				colaDisponibleE.push_back(vTaxi.at(i));
			}
		}
	}

    ifstream frd_rutaT ("COLA_RUTA_T.txt");
	if(frd_rutaT.is_open()){
		while(true) {
            getline(frd_rutaT, line);
            if(line.length()!=0){
                colaRutaT.push_back(stoi(line));
            }
            else{
                break;
            }
		}
		frd_rutaT.close();
	}

    ifstream frd_rutaE ("COLA_RUTA_E.txt");
	if(frd_rutaE.is_open()){
		while(true) {
            getline(frd_rutaE, line);
            if(line.length()!=0){
                colaRutaE.push_back(stoi(line));
            }
            else{
                break;
            }
		}
		frd_rutaE.close();
	}

    ifstream frd_solicitudes ("TRANSACTION_LOG.txt");
	if(frd_solicitudes.is_open()){
		while(true) {
            getline(frd_solicitudes, line);
            if(line.length()!=0){
                vSol.push_back(stoi(line));
                getline(frd_solicitudes, line);
                vSolCategoriaViaje.push_back(line);
                getline(frd_solicitudes, line);
                vSolInicioViaje.push_back(line);
                getline(frd_solicitudes, line);
                vSolFinViaje.push_back(line);
                getline(frd_solicitudes, line);
                vSolCostoViaje.push_back(stod(line));
				getline(frd_solicitudes, line);
				vSolIdTaxi.push_back(stoi(line));
            }
            else{
                break;
            }
		}
		frd_solicitudes.close();
	}

    //FIN CARGA DATOS DESDE TXT
    do{
		system("cls");
		//system("Color 07");
		TextTable t( '-', '|', '+' ); //para vaciar la variable, porque sino se acumulaba cada respuesta devuelta de opc 7
		cout<<"\t***** Sistema de gestión de taxis True Drive *****\n";
		cout<<"\t***** Menú de opciones: *****\n"<<endl;
		cout<<"\t1. Agregar taxi al sistema"<<endl; //ingreso de datos de los taxis y su respectivo conductor
		cout<<"\t2. Mostrar los taxis disponibles"<<endl; //impresión de los taxis en la cola disponible (T & E)
		cout<<"\t3. Agregar solicitud de usuario"<<endl; //ingreso de solicitudes de viaje de los usuarios
		cout<<"\t4. Mostrar los taxis en ruta"<<endl; //impresión de los taxis en la cola en ruta (T & E)
		cout<<"\t5. Reingresar taxi (pasar de en ruta a disponible)"<<endl; //reingreso de taxi al sistema, escribiendo su ID
		cout<<"\t6. Reporte: listado de todos los viajes realizados por los taxis"<<endl; //reporte de la bitacora de todos viajes
		cout<<"\t7. Reporte: listado de todos los viajes realizados por un taxi en especifico"<<endl; //reporte de viajes especificos
		cout<<"\t8. Salir del sistema"<<endl;
		cout<<"\t--------------------------------------------------"<<endl<<endl;
		cout<<"Favor, ingrese la opción deseada: ";
		cin>>opcion;
				
		switch(opcion){
			case 1:
				//system("Color 0E");
				cout<<"\n***** Se encuentra en la opción 1 *****\n";
				do{
					cout<<"ID taxi: ";
					cin>>filewrmTaxi;
				}while(checkForfilewrmInt(vTaxi, filewrmTaxi));
				vTaxi.push_back(filewrmTaxi); //captura, validación e ingreso del campo para ID taxi
				do{
					cout<<"Número placa del taxi: ";
					cin>>filewrmPlaca;
				}while(checkForfilewrmString(vPlaca, filewrmPlaca));
				vPlaca.push_back(filewrmPlaca); //captura, validación e ingreso del campo de la placa taxi
				do{
					cout<<"Número motor del taxi: ";
					cin>>filewrmNumeroMotor;
				}while(checkForfilewrmString(vNumeroMotor, filewrmNumeroMotor));
				vNumeroMotor.push_back(filewrmNumeroMotor); //captura, validación e ingreso del campo número motor taxi
				
				cout<<"Modelo del taxi: ";
				cin.ignore();
				getline(cin,filewrmModelo);
				vModelo.push_back(filewrmModelo); //captura e ingreso del campo modelo taxi

				cout<<"Marca del taxi: ";
				getline(cin,filewrmMarca);
				vMarca.push_back(filewrmMarca); //captura e ingreso del campo marca taxi

				cout<<"Transmisión del taxi: 1- Estándar ó 2- Automático: ";
				cin>>decisionTransmision;

				if(decisionTransmision=="1"){ //validando la elección del usuario, respecto a la transmisión taxi 
					filewrmTransmision = "Estándar";
				}else{
					filewrmTransmision = "Automático";
				}
				vTransmision.push_back(filewrmTransmision); //captura e ingreso del campo transmisión taxi

				cout<<"Nombres del conductor: ";
				cin.ignore();
				getline(cin,filewrmConductorNombre);
				vConductorNombre.push_back(filewrmConductorNombre); //captura e ingreso del campo nombres del conductor

				cout<<"Apellidos del conductor: ";
				getline(cin,filewrmConductorApellido);
				vConductorApellido.push_back(filewrmConductorApellido); //captura e ingreso del campo apellidos del conductor

				cout<<"Edad del conductor: ";
				cin>>filewrmConductorEdad;
				vConductorEdad.push_back(filewrmConductorEdad); //captura e ingreso del campo edad del conductor

				do{
					cout<<"DUI del conductor: ";
					cin>>filewrmConductorDui;
				}while(checkForfilewrmString(vConductorDui, filewrmConductorDui));
				vConductorDui.push_back(filewrmConductorDui); //captura, validación e ingreso del campo DUI del conductor
				do{
					cout<<"ISSS del conductor: ";
					cin>>filewrmConductorIsss;
				}while(checkForfilewrmString(vConductorIsss, filewrmConductorIsss));
				vConductorIsss.push_back(filewrmConductorIsss); //captura, validación e ingreso del número de seguro del conductor
				do{
					cout<<"Número telefonico contacto del conductor: ";
					cin>>filewrmConductorTelefono;
				}while(checkForfilewrmString(vConductorTelefono, filewrmConductorTelefono));
				vConductorTelefono.push_back(filewrmConductorTelefono); //captura, validación e ingreso del número teléfonico conductor
				do{
					cout<<"Número licencia del conductor: ";
					cin>>filewrmConductorLicencia;
				}while(checkForfilewrmString(vConductorLicencia, filewrmConductorLicencia));
				vConductorLicencia.push_back(filewrmConductorLicencia); //captura, validación e ingreso del campo licencia del conductor

				//VALIDACIONES DEL AÑO DE FABRICACIÓN, LA CATEGORÍA ASIGNADA Y EL INGRESO DEL ID DEL TAXI EN LA COLA DISPONIBLE
				do{
					cout<<"Año fabricación de taxi: ";
					cin>>filewrmAnio;
				}while(checkForfilewrmDate(filewrmAnio));
				vAnio.push_back(filewrmAnio); //captura, validación e ingreso del campo año de fabricación taxi
				
				if(filewrmAnio>=2010 && filewrmAnio<2015){
					filewrmCategoria = "Tradicional";
				}
				else{

					cout<<"Al tener año fabricación mayor o igual a 2015, indique categoría del taxi 1- Tradicional ó 2- Ejecutiva: ";
					cin>>decisionCategoria;

					if(decisionCategoria=="1"){
						filewrmCategoria = "Tradicional";
					}else{
						filewrmCategoria = "Ejecutiva";
					}
				}
				vCategoria.push_back(filewrmCategoria); //captura, validación e ingreso del campo categoría del conductor

				//EVALUANDO EL TAXI PARA COLOCARLO EN CATEGORÍA
				if(filewrmCategoria=="Tradicional")
				{
					colaDisponibleT.push_back(filewrmTaxi);
				}
				else
				{
					colaDisponibleE.push_back(filewrmTaxi);
				}
				//Imprimir datos de conductores y autos en un fichero
				if(!vTaxi.empty()){
					ofstream filewr ("CARS_STORAGE.txt"); //Crear el archivo siendo destructivo con datos anteriores
					if(filewr.is_open()){
					//filewr<<"ID, PLACA, MODELO, MARCA, A�O, CATEGORIA, TRANSMISION, CONDUCTOR NOMBRE, CONDUCTOR APELLIDO, CONDUCTOR LICENCIA, CONDUCTOR DUI, CONDUCTOR TELEFONO, CONDUCTOR EDAD"<<endl;
					for(int i=0; i<vTaxi.size(); i++){
						filewr<<to_string(vTaxi.at(i))<<"\n"
						<<vPlaca.at(i)<<"\n"
						<<vModelo.at(i)<<"\n"
						<<vMarca.at(i)<<"\n"
						<<vAnio.at(i)<<"\n"
						<<vCategoria.at(i)<<"\n"
						<<vTransmision.at(i)<<"\n"
						<<vConductorNombre.at(i)<<"\n"
						<<vConductorApellido.at(i)<<"\n"
						<<vConductorLicencia.at(i)<<"\n"
						<<vConductorDui.at(i)<<"\n"
						<<vConductorTelefono.at(i)<<"\n"
						<<vConductorEdad.at(i)<<"\n";
					}
						filewr.close();
				    }
				    else{
					    cout<<"No se pudo crear el archivo";
				    }
				}
			break;
			case 2:
				//system("Color 0E");
				cout<<"\n***** Se encuentra en la opción 2 *****\n";
				if(colaDisponibleT.empty() && colaDisponibleE.empty()){ //mira que vectores de cola disponible (T & E) tengan datos
					cout <<"\nMensaje: Lo sentimos. No hay Taxis disponibles en este momento. Consultar después.\n";
				}
				else{
					//LLAMADO DE LA FUNCIÓN QUE IMPRIMIRÁ LOS DATOS DE LA COLA DISPONIBLE, COLOCANDO TRADICIONALES Y EJECUTIVOS
					printTableD(colaDisponibleT, colaDisponibleE, vTaxi, vPlaca, vModelo, vMarca, vAnio, vCategoria, vTransmision, vConductorNombre, vConductorApellido, vConductorLicencia, vConductorDui, vConductorTelefono, vConductorEdad);
				}
			break;
			case 3:
				//system("Color 0E");
				cout<<"\n***** Se encuentra en la opción 3 *****\n";
				cout<<"\nIndique la categoría (1. Tradicional, 2. Ejecutiva) del viaje: ";
				cin>>filewrmSolCategoriaViaje; //pregunta el tipo de taxi que ha solicitado el usuario, para validar si hay disponibles
				
				if(filewrmSolCategoriaViaje==1){ 
					if(colaDisponibleT.empty()){ //validando si hay taxis tradicionales disponibles
						cout<<"\nMensaje: Lo sentimos. Por el momento, no hay taxis tradicionales disponibles. Consultar después.\n";
						break; //si la cola de taxis tradicionales disponibles está vacía, entonces se sale de la opción
					}
				}else{
					if(colaDisponibleE.empty()){ //validando si hay taxis ejecutivos disponibles
						cout<<"\nMensaje: Lo sentimos. Por el momento, no hay taxis ejecutivos disponibles. Consultar después.\n";
						break; //si la cola de taxis ejecutivos disponibles está vacía, entonces se sale de la opción
					}
				}
				
				do{
					cout<<"ID solicitud: ";
					cin>>filewrmSol;
				}while(checkForfilewrmInt(vSol, filewrmSol));
				vSol.push_back(filewrmSol); //captura, validación e ingreso del campo para ID solicitud
				cout<<"Indique el punto de partida del viaje: ";
				cin.ignore();
				getline(cin, filewrmSolInicioViaje);
				vSolInicioViaje.push_back(filewrmSolInicioViaje); //captura e ingreso del inicio de la solicitud gestionada
				cout<<"Indique el punto de fin del viaje: ";
				cin.ignore();
				getline(cin, filewrmSolFinViaje);
				vSolFinViaje.push_back(filewrmSolFinViaje); //captura e ingreso del fin de la solicitud gestionada
				cout<<"Indique el costo del viaje: $";
				cin>>filewrmSolCostoViaje;
				vSolCostoViaje.push_back(filewrmSolCostoViaje); //captura e ingreso del costo de la solicitud gestionada

				if(filewrmSolCategoriaViaje==1){
					vSolIdTaxi.push_back(colaDisponibleT.at(0)); //captura directa del ID del taxi tradicional para la solicitud
					colaRutaT.push_back(colaDisponibleT.at(0)); //el primer valor del vector disponibleT se añade al final del otro
					pop_front(colaDisponibleT); //quitando el primer valor del vector disponibleT, ya que se pasó al vector en ruta

                    if(!vTaxi.empty()){
                        ofstream fileRutaT ("COLA_RUTA_T.txt"); //Crear el archivo siendo destructivo con datos anteriores
                        if(fileRutaT.is_open()){
                            for(int i=0; i<colaRutaT.size(); i++){
                                fileRutaT<<to_string(colaRutaT.at(i))<<"\n";
                            }
                            fileRutaT.close();
                        }
                        else{
                            cout<<"No se pudo crear el archivo";
                        }
				    }

                    if(!vTaxi.empty()){
                        ofstream fileDisponibleT ("COLA_DISPONIBLE_T.txt"); //Crear el archivo siendo destructivo con datos anteriores
                        if(fileDisponibleT.is_open()){
                            for(int i=0; i<colaDisponibleT.size(); i++){
                                fileDisponibleT<<to_string(colaDisponibleT.at(i))<<"\n";
                            }
                            fileDisponibleT.close();
                        }
                        else{
                            cout<<"No se pudo crear el archivo";
                        }
				    }
				}
				if(filewrmSolCategoriaViaje==2){
					vSolIdTaxi.push_back(colaDisponibleE.at(0)); //captura directa del ID del taxi ejecutivo para la solicitud
					colaRutaE.push_back(colaDisponibleE.at(0)); //el primer valor del vector disponibleE se añade al final del otro
					pop_front(colaDisponibleE); //quitando el primer valor del vector disponibleE, ya que se pasó al vector en ruta

                    if(!vTaxi.empty()){
                        ofstream fileRutaE ("COLA_RUTA_E.txt"); //Crear el archivo siendo destructivo con datos anteriores
                        if(fileRutaE.is_open()){
                            for(int i=0; i<colaRutaE.size(); i++){
                                fileRutaE<<to_string(colaRutaE.at(i))<<"\n";
                            }
                            fileRutaE.close();
                        }
                        else{
                            cout<<"No se pudo crear el archivo";
                        }
				    }

                    if(!vTaxi.empty()){
                        ofstream fileDisponibleE ("COLA_DISPONIBLE_E.txt"); //Crear el archivo siendo destructivo con datos anteriores
                        if(fileDisponibleE.is_open()){
                            for(int i=0; i<colaDisponibleE.size(); i++){
                                fileDisponibleE<<to_string(colaDisponibleE.at(i))<<"\n";
                            }
                            fileDisponibleE.close();
                        }
                        else{
                            cout<<"No se pudo crear el archivo";
                        }
				    }
				}

				if(filewrmSolCategoriaViaje==1){ //validación e ingreso de la categoría de la solicitud gestionada
					vSolCategoriaViaje.push_back("Tradicional");
				}else{
					vSolCategoriaViaje.push_back("Ejecutiva");
				}

				if(!vSol.empty()){ //Escribe datos de este viaje en especifico en un txt
				    ofstream filewr_viaje ("TRANSACTION_LOG.txt"); //Crear el registro siendo destructivo
                    if(filewr_viaje.is_open()){
                        for(int i=0; i<vSol.size(); i++){
                            filewr_viaje<<vSol.at(i)<<"\n"
                            <<vSolCategoriaViaje.at(i)<<"\n"
                            <<vSolInicioViaje.at(i)<<"\n"
                            <<vSolFinViaje.at(i)<<"\n"
                            <<vSolCostoViaje.at(i)<<"\n"
							<<vSolIdTaxi.at(i)<<"\n";
					    }
						filewr_viaje.close();
				    }
				    else{
					    cout<<"No se pudo crear el archivo";
				    }
			    }
			break;
			case 4:
				//system("Color 0E");
				cout<<"\n***** Se encuentra en la opción 4 *****\n";
				if(colaRutaT.empty() && colaRutaE.empty()){ //verifica que vectores de cola en ruta (T & E) tengan datos
					cout << "\nMensaje: Lo sentimos. No hay Taxis en ruta en este momento. Consultar después.\n";
				}
				else{
					//LLAMADO DE LA FUNCIÓN QUE IMPRIMIRÁ LOS DATOS DE LA COLA EN RUTA, COLOCANDO TRADICIONALES Y EJECUTIVOS
					printTableR(colaRutaT, colaRutaE, vTaxi, vPlaca, vModelo, vMarca, vAnio, vCategoria, vTransmision,vConductorNombre, vConductorApellido, vConductorLicencia, vConductorDui, vConductorTelefono, vConductorEdad);
				}
			break;
			case 5:
				//system("Color 0E");
				cout<<"\n***** Se encuentra en la opción 5 *****\n";
				cout<<"\nIndique la categor�a (1. Tradicional, 2. Ejecutiva) de reingreso del viaje en ruta: ";
				cin>>reCategoriaViaje; //se pregunta el tipo de taxi que se reingresará, para validar si hay en ruta

				if(reCategoriaViaje==1){ //validando si hay taxis tradicionales en ruta
					if(colaRutaT.empty()){
						cout<<"\nMensaje: Lo sentimos. Por el momento, no hay taxis tradicionales en ruta. Consultar después.\n";
						break; //si la cola de taxis tradicionales en ruta está vacía, entonces se sale de la opción
					}
				}else{
					if(colaRutaE.empty()){ //validando si hay taxis ejecutivos en ruta
						cout<<"\nMensaje: Lo sentimos. Por el momento, no hay taxis ejecutivos en ruta. Consultar después.\n";
						break; //si la cola de taxis ejecutivos en ruta está vacía, entonces se sale de la opción
					}
				}
				
				if(reCategoriaViaje==1){ //se valida si se quiere reingresar un tradicional, para imprimir justo esos taxis
					cout << "\n***** TAXIS TRADICIONALES EN RUTA *****\n";
					for(int m = 0; m<colaRutaT.size(); m++){
						cout << "ID Taxi: " << colaRutaT.at(m) << "\n";
					}
					cout<<"\nIndique el ID del Taxi tradicional que se enviará a la cola de taxis disponibles: ";
					cin>>reIdTaxi;
					cout << "\n";
					
					//SE RECORRE TODO EL VECTOR DE EN RUTAT PARA COMPARAR CADA VALOR CON EL ID INGRESADO POR USUARIO, SE TOMA POSICION
					for (int a=0; a<colaRutaT.size(); a++) {
						if(colaRutaT.at(a)==reIdTaxi){
							//cout << a << "posicion del ID en colarutaT que será cambiado \n";
							rePosicion = a;
						}
					}
					//agregando al final de cola disponiblesT, el ID que está en la posición encontrada en el for anterior
					colaDisponibleT.push_back(colaRutaT.at(rePosicion));
					//quitando de cola en rutaT el ID que está en la posición encontrada en el for anterior
					colaRutaT = eliminarPosicion(rePosicion, colaRutaT);

                    if(!vTaxi.empty()){
                        ofstream fileDisponibleT ("COLA_DISPONIBLE_T.txt"); //Crear el archivo siendo destructivo con datos anteriores
                        if(fileDisponibleT.is_open()){
                            for(int i=0; i<colaDisponibleT.size(); i++){
                                fileDisponibleT<<to_string(colaDisponibleT.at(i))<<"\n";
                            }
                            fileDisponibleT.close();
                        }
                        else{
                            cout<<"No se pudo crear el archivo";
                        }
				    }

                    if(!vTaxi.empty()){
                        ofstream fileRutaT ("COLA_RUTA_T.txt"); //Crear el archivo siendo destructivo con datos anteriores
                        if(fileRutaT.is_open()){
                            for(int i=0; i<colaRutaT.size(); i++){
                                fileRutaT<<to_string(colaRutaT.at(i))<<"\n";
                            }
                            fileRutaT.close();
                        }
                        else{
                            cout<<"No se pudo crear el archivo";
                        }
				    }
				}
				if(reCategoriaViaje==2){ //se valida si se quiere reingresar un ejecutivo, para imprimir justo esos taxis
					cout << "\n***** TAXIS EJECUTIVOS EN RUTA *****\n";
					for(int m = 0; m<colaRutaE.size(); m++){
						cout << "ID Taxi: " << colaRutaE.at(m) << "\n";
					}
					cout<<"\nIndique el ID del Taxi ejecutivo que se enviará a la cola de taxis disponibles: ";
					cin>>reIdTaxi;
					cout << "\n";

					//SE RECORRE TODO EL VECTOR DE EN RUTAE PARA COMPARAR CADA VALOR CON EL ID INGRESADO POR USUARIO, SE TOMA POSICION
					for (int a=0; a<colaRutaE.size(); a++) {
						if(colaRutaE.at(a)==reIdTaxi){
							//cout << a << "posicion de ID en ruta que será cambiado \n";
							rePosicion = a;
						}
					}
					//agregando al final de cola disponiblesE, el ID que está en la posición encontrada en el for anterior
					colaDisponibleE.push_back(colaRutaE.at(rePosicion));
					//quitando de cola en rutaE el ID que está en la posición encontrada en el for anterior
					colaRutaE = eliminarPosicion(rePosicion, colaRutaE);

                    if(!vTaxi.empty()){
                        ofstream fileDisponibleE ("COLA_DISPONIBLE_E.txt"); //Crear el archivo siendo destructivo con datos anteriores
                        if(fileDisponibleE.is_open()){
                            for(int i=0; i<colaDisponibleE.size(); i++){
                                fileDisponibleE<<to_string(colaDisponibleE.at(i))<<"\n";
                            }
                            fileDisponibleE.close();
                        }
                        else{
                            cout<<"No se pudo crear el archivo";
                        }
				    }

                    if(!vTaxi.empty()){
                        ofstream fileRutaE ("COLA_RUTA_E.txt"); //Crear el archivo siendo destructivo con datos anteriores
                        if(fileRutaE.is_open()){
                            for(int i=0; i<colaRutaE.size(); i++){
                                fileRutaE<<to_string(colaRutaE.at(i))<<"\n";
                            }
                            fileRutaE.close();
                        }
                        else{
                            cout<<"No se pudo crear el archivo";
                        }
				    }
				}
			break;
			case 6:
				//system("Color 0E");
				cout<<"\n***** Se encuentra en la opción 6 *****\n";
				if(vSol.empty()){ //mira que el vector de ID de solicitud de viaje tenga datos
					cout <<"\nMensaje: Lo sentimos. No se han realizado viajes en este momento. Consultar después.\n";
				}
				else{
					//LLAMADO DE LA FUNCIÓN QUE IMPRIMIRÁ LOS DATOS DE LAS SOLICITUDES DE VIAJE
					printTableV(vSol, vSolCategoriaViaje, vSolInicioViaje, vSolFinViaje, vSolCostoViaje, vSolIdTaxi, vTaxi, vPlaca, vModelo, vConductorNombre, vConductorApellido, vConductorLicencia);
				}
			break;
			case 7:
				//system("Color 0E");
				//INICIO MEJORA
				taxisEncontrados = 0;
				cout<<"Ingrese identificador de taxi para buscar datos: ";
                cin>>idBuscarTaxi; //se captura el ID del taxi que se va a buscar.
                
				//DEFINIENDO LOS HEADERS DE CADA COLUMNA
				//TextTable c( '-', '|', '+' );
				t.add("ID");
				t.add("Categor�a viaje");
				t.add("Punto inicio viaje");
				t.add("Punto final viaje");
				t.add("Costo viaje");
				t.add("ID taxi viaje");
				t.add("Placa taxi");
				t.add("Modelo taxi");
				t.add("Nombres conductor");
				t.add("Apellidos conductor");
				t.add("Licencia");
				t.endOfRow();

				//c.setAlignment( 2, TextTable::Alignment::RIGHT );
				//cout<<c;

				for(int i=0; i<vSolIdTaxi.size(); i++){ //se comienza a buscar el ID especifico entre los IDS dentro del arreglo
                    if(idBuscarTaxi==vSolIdTaxi[i]){ //si hay coincidencia entre lo que el usuario ingreso, y el ID de un taxi
                        //existe=true; //se activa la bandera a TRUE

						t.add(to_string(vSol.at(i)));
						t.add(vSolCategoriaViaje.at(i));
						t.add(vSolInicioViaje.at(i));
						t.add(vSolFinViaje.at(i));
						t.add(to_string(vSolCostoViaje.at(i)));
						t.add(to_string(vSolIdTaxi.at(i)));
						for(int j=0; j<vTaxi.size(); j++){
							if(vSolIdTaxi.at(i)==vTaxi.at(j)){
								t.add(vPlaca.at(j));
								t.add(vModelo.at(j));
								t.add(vConductorNombre.at(j));
								t.add(vConductorApellido.at(j));
								t.add(vConductorLicencia.at(j));
							}
						}
						t.endOfRow();
						taxisEncontrados = taxisEncontrados + 1;
						//break; //no es necesario rompe el ciclo for, ya que, un mismo taxi puede hacer multiples viajes
					}
					//else{ //si no hay coincidencia entonces la bandera se mantiene en falso
                    //    existe = false;
                    //}
                }
				
                if(taxisEncontrados==0){ //si no se encuentra ningun taxi, se muestra mensaje al usuario
                    cout<<"\nNo existe el taxi buscado o a�n no se han ingresado viajes..."<<endl<<endl;
                }
				else{
					t.setAlignment( 2, TextTable::Alignment::RIGHT );
					cout<<t;
				}
                //system("clear");
			break;
			case 8:
				//system("Color 0E");
				cout<<"\nEl sistema se está cerrando...\n";
				system("pause"); //pausa para que se note el mensaje escrito
				continuar='n'; //se fuerza a que la variable de control sea equivalente a NO, para que finalice el do-while
			break;
			default:
				cout<<"\nMensaje: Se ha seleccionado una opción que no existe en el menú.\n\n"<<endl;
			break;
		}
	if(continuar=='n'){
	}
	else{
		//system("Color 0E");
		cout<<"\n¿Desea continuar? (S/N)?: ";
  		continuar=getch(); //getchar, lee un solo caracter ingresado por teclado
	}
  	
	}while(continuar=='S' || continuar=='s');
}

//INICIO DE DEFINICIÓN DE LAS FUNCIONES QUE SE USARÁN EN EL CÓDIGO
bool checkForfilewrmInt(vector<int> arr, int data){ //función, verifica si se repfilewr dato Int que se intenta ingresar vector
	bool controlfilewrmInt = false; //bandera que cambiará si en el vector se encuentra el dato buscado
	for(int i=0;i<arr.size();i++) //se filewrra todo el vector que recibe
	{
		if(arr.at(i)==data){ //se compara cada elemento en el vector, con el dato buscado
			controlfilewrmInt = true; //se encuentra similitud, entonces la bandera cambia
		}
	}
	if(controlfilewrmInt==true){ //se evalua el valor final de la bandera, para saber si se encontraron similitudes
		cout<<"\nMensaje: El dato ["<<data<<"] ya está registrado. Favor, ingresar un dato diferente.\n\n";
		return true; //si se encontraron similitudes, entonces la función devuelve un true para que el while de captura siga
	}
	else{
		return false; //si no se encontraron similitudes, entonces la función devuelve un false para que el while de captura pare
	}
}

bool checkForfilewrmString(vector<string> arr, string data){ //función, verifica si se repfilewr dato String que se intenta ingresar vector
	bool controlfilewrmString = false; //bandera que cambiará si en el vector se encuentra el dato buscado
	for(int i=0;i<arr.size();i++) //se filewrra todo el vector que recibe
	{
		if(arr.at(i)==data){ //se compara cada elemento en el vector, con el dato buscado
			controlfilewrmString = true; //se encuentra similitud, entonces la bandera cambia
		}
	}
	if(controlfilewrmString==true){ //se evalua el valor final de la bandera, para saber si se encontraron similitudes
		cout<<"\nMensaje: El dato ["<<data<<"] ya está registrado. Favor, ingresar un dato diferente.\n\n";
		return true; //si se encontraron similitudes, entonces la función devuelve un true para que el while de captura siga
	}
	else{
		return false; //si no se encontraron similitudes, entonces la función devuelve un false para que el while de captura pare
	}
}

bool checkForfilewrmDate(int anioTaxi){ //función que recibe el año de fabricación y verifica que sea mayor o igual a 2010
	if(anioTaxi<2010) //si el año de fabricación es menor a 2010 se imprime un mensaje y volverá a preguntar el año fabricación
	{
		cout<<"\nMensaje: No se pueden registrar taxis con año de fabricación menor a 2010.\n\n";
		return true;
	}
	else
	{
		return false;
	}
}

vector<int> eliminarPosicion(int rePosicion, vector<int> &colaRuta){ //función que eliminará de vector el dato en la posición dada
	//desplazamiento de valores (a partir de la posición dada), de modo que se corran a derecha y quede en ultima posicion un 0
	for(int i = rePosicion; i<colaRuta.size(); i++){
		colaRuta[i]=colaRuta[i+1];
	}
	colaRuta.pop_back(); //eliminando el cero que está en la última posición
	return colaRuta; //la función devuelve el vector ya sin el elemento que se debía quitar de cola en ruta hacia cola disponible
}



void printTableD(vector<int> colaDisponibleT, vector<int> colaDisponibleE, vector<int> vTaxi, vector<string> vPlaca, vector<string> vModelo, vector<string> vMarca, vector<int> vAnio, vector<string> vCategoria, vector<string> vTransmision, vector<string> vConductorNombre, vector<string> vConductorApellido, vector<string> vConductorLicencia, vector<string> vConductorDui, vector<string> vConductorTelefono, vector<int> vConductorEdad) //función que imprimirá la cola disponible, tanto para tradicionales y ejecutivos
{
	//DEFINIENDO LOS HEADERS DE CADA COLUMNA
	TextTable t( '-', '|', '+' );
	t.add("# Fila");
	t.add("ID");
	t.add("Placa");
	t.add("Modelo");
	t.add("Marca");
	t.add("Año fabricación");
	t.add("Categoría");
	t.add("Transmisión");
	t.add("Nombres conductor");
	t.add("Apellidos conductor");
	t.add("Licencia");
	t.add("DUI");
	t.add("Teléfono");
	t.add("Edad");
	t.endOfRow();

	//TAXIS DISPONIBLES, CATEGORÍA TRADICIONAL
	for(int i=0; i<colaDisponibleT.size(); i++){
		for(int j=0; j<vTaxi.size(); j++){
			if(colaDisponibleT.at(i)==vTaxi.at(j)){
				t.add(to_string(i+1)); //orden número fila
				t.add(to_string(vTaxi.at(j)));
				t.add(vPlaca.at(j));
				t.add(vModelo.at(j));
				t.add(vMarca.at(j));
				t.add(to_string(vAnio.at(j)));
				t.add(vCategoria.at(j));
				t.add(vTransmision.at(j));
				t.add(vConductorNombre.at(j));
				t.add(vConductorApellido.at(j));
				t.add(vConductorLicencia.at(j));
				t.add(vConductorDui.at(j));
				t.add(vConductorTelefono.at(j));
				t.add(to_string(vConductorEdad.at(j)));
				t.endOfRow();
			}
		}
	}
	//TAXIS DISPONIBLES, CATEGORÍA EJECUTIVA
	for(int i=0; i<colaDisponibleE.size(); i++){
		for(int j=0; j<vTaxi.size(); j++){
			if(colaDisponibleE.at(i)==vTaxi.at(j)){
				t.add(to_string(colaDisponibleT.size()+1+i)); //orden número fila, tomando en cuenta el número final de disponibleT
				t.add(to_string(vTaxi.at(j)));
				t.add(vPlaca.at(j));
				t.add(vModelo.at(j));
				t.add(vMarca.at(j));
				t.add(to_string(vAnio.at(j)));
				t.add(vCategoria.at(j));
				t.add(vTransmision.at(j));
				t.add(vConductorNombre.at(j));
				t.add(vConductorApellido.at(j));
				t.add(vConductorLicencia.at(j));
				t.add(vConductorDui.at(j));
				t.add(vConductorTelefono.at(j));
				t.add(to_string(vConductorEdad.at(j)));
				t.endOfRow();
			}
		}
	}
	t.setAlignment( 2, TextTable::Alignment::RIGHT );
	cout<<t;
}

void printTableR(vector<int> colaRutaT, vector<int> colaRutaE, vector<int> vTaxi, vector<string> vPlaca, vector<string> vModelo, vector<string> vMarca, vector<int> vAnio, vector<string> vCategoria, vector<string> vTransmision, vector<string> vConductorNombre, vector<string> vConductorApellido, vector<string> vConductorLicencia, vector<string> vConductorDui, vector<string> vConductorTelefono, vector<int> vConductorEdad) //función que imprimirá la cola en ruta, tanto para tradicionales y ejecutivos
{
	//DEFINIENDO LOS HEADERS DE CADA COLUMNA
	TextTable t( '-', '|', '+' );
	t.add("# Fila");
	t.add("ID");
	t.add("Placa");
	t.add("Modelo");
	t.add("Marca");
	t.add("Año fabricación");
	t.add("Categoría");
	t.add("Transmisión");
	t.add("Nombres conductor");
	t.add("Apellidos conductor");
	t.add("Licencia");
	t.add("DUI");
	t.add("Teléfono");
	t.add("Edad");
	t.endOfRow();

	//TAXIS EN RUTA, CATEGORÍA TRADICIONAL
	for(int i=0; i<colaRutaT.size(); i++){
		for(int j=0; j<vTaxi.size(); j++){
			if(colaRutaT.at(i)==vTaxi.at(j)){
				t.add(to_string(i+1)); //orden número fila
				t.add(to_string(vTaxi.at(j)));
				t.add(vPlaca.at(j));
				t.add(vModelo.at(j));
				t.add(vMarca.at(j));
				t.add(to_string(vAnio.at(j)));
				t.add(vCategoria.at(j));
				t.add(vTransmision.at(j));
				t.add(vConductorNombre.at(j));
				t.add(vConductorApellido.at(j));
				t.add(vConductorLicencia.at(j));
				t.add(vConductorDui.at(j));
				t.add(vConductorTelefono.at(j));
				t.add(to_string(vConductorEdad.at(j)));
				t.endOfRow();
			}
		}
	}

	//TAXIS EN RUTA, CATEGORÍA EJECUTIVA
	for(int i=0; i<colaRutaE.size(); i++){
		for(int j=0; j<vTaxi.size(); j++){
			if(colaRutaE.at(i)==vTaxi.at(j)){
				t.add(to_string(colaRutaT.size()+1+i)); //orden número fila, tomando en cuenta el número final de en rutaT
				t.add(to_string(vTaxi.at(j)));
				t.add(vPlaca.at(j));
				t.add(vModelo.at(j));
				t.add(vMarca.at(j));
				t.add(to_string(vAnio.at(j)));
				t.add(vCategoria.at(j));
				t.add(vTransmision.at(j));
				t.add(vConductorNombre.at(j));
				t.add(vConductorApellido.at(j));
				t.add(vConductorLicencia.at(j));
				t.add(vConductorDui.at(j));
				t.add(vConductorTelefono.at(j));
				t.add(to_string(vConductorEdad.at(j)));
				t.endOfRow();
			}
		}
	}

	t.setAlignment( 2, TextTable::Alignment::RIGHT );
	cout<<t;
}

void printTableV(vector<int> vSol, vector<string> vSolCategoriaViaje, vector<string> vSolInicioViaje, vector<string> vSolFinViaje, vector<double> vSolCostoViaje, vector<int> vSolIdTaxi, vector<int> vTaxi, vector<string> vPlaca, vector<string> vModelo, vector<string> vConductorNombre, vector<string> vConductorApellido, vector<string> vConductorLicencia) //función que imprimirá los viajes, tanto los T y E
{
	//DEFINIENDO LOS HEADERS DE CADA COLUMNA
	TextTable t( '-', '|', '+' );
	t.add("ID");
	t.add("Categor�a viaje");
	t.add("Punto inicio viaje");
	t.add("Punto final viaje");
	t.add("Costo viaje");
	t.add("ID taxi viaje");
	t.add("Placa taxi");
	t.add("Modelo taxi");
	t.add("Nombres conductor");
	t.add("Apellidos conductor");
	t.add("Licencia");
	t.endOfRow();

	//BITACORA VIAJES DE TAXIS TIPO TRADICIONAL
	for(int i=0; i<vSol.size(); i++){
		if(vSolCategoriaViaje.at(i)=="Tradicional"){
			t.add(to_string(vSol.at(i)));
			t.add(vSolCategoriaViaje.at(i));
			t.add(vSolInicioViaje.at(i));
			t.add(vSolFinViaje.at(i));
			t.add(to_string(vSolCostoViaje.at(i)));
			t.add(to_string(vSolIdTaxi.at(i)));
			for(int j=0; j<vTaxi.size(); j++){
				if(vSolIdTaxi.at(i)==vTaxi.at(j)){
					t.add(vPlaca.at(j));
					t.add(vModelo.at(j));
					t.add(vConductorNombre.at(j));
					t.add(vConductorApellido.at(j));
					t.add(vConductorLicencia.at(j));
				}
			}
			t.endOfRow();
		}
	}

	//BITACORA VIAJES DE TAXIS TIPO EJECUTIVO
	for(int i=0; i<vSol.size(); i++){
		if(vSolCategoriaViaje.at(i)=="Ejecutiva"){
			t.add(to_string(vSol.at(i)));
			t.add(vSolCategoriaViaje.at(i));
			t.add(vSolInicioViaje.at(i));
			t.add(vSolFinViaje.at(i));
			t.add(to_string(vSolCostoViaje.at(i)));
			t.add(to_string(vSolIdTaxi.at(i)));
			for(int j=0; j<vTaxi.size(); j++){
				if(vSolIdTaxi.at(i)==vTaxi.at(j)){
					t.add(vPlaca.at(j));
					t.add(vModelo.at(j));
					t.add(vConductorNombre.at(j));
					t.add(vConductorApellido.at(j));
					t.add(vConductorLicencia.at(j));
				}
			}
			t.endOfRow();
		}
	}
	
	t.setAlignment( 2, TextTable::Alignment::RIGHT );
	cout<<t;
}
