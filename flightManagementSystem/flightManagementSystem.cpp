#include <iostream>
#include <string.h>
#include <windows.h>
#include <locale.h>
using namespace std;

//Declaracion de constantes
const int numPasajeros = 26;
const int FILAS = 5;
const int COLUMNAS = 5;

//Declaracion de estructuras
struct Pasajeros {
	int num;
    char nombre[50];
    int dni;
    int telefono;
    char correo[30];
    int fila;
    int columna;
};

struct Aviones {
    char asiento[FILAS][COLUMNAS] = {        
		{'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O'},
	};
};

struct Informacion {
	char fecha[20];
	int num_vuelo;
	char hora[20];
	char destino[20];
	char aerolinea[20];
	int precio;
};

//Declaracion de prototipos
int MenuGeneral();
	void General(FILE *V, FILE *P, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[]);
int MenuHorarios();
	void BuscarPorDestino(Informacion vuelos[], int numVuelos);
	void ImprimirDatos(Informacion vuelo);
int MenuReservas();
	void GeneralReservas(FILE *P, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int& x, int numVuelos);
	void BuscarPasajero(Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int x, int numVuelos);
	void MostrarAvion(Aviones avion[], int posicion, int num_vuelo);
	int BuscarPorCodigo(Informacion vuelos[], int numVuelos, int num_vuelo);
	void BuscarReserva(Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int numVuelos, int x);
	void InformacionPasajero(Pasajeros pasajero_reservado[], int& x, int num_vuelo, int i);
	void LeerArchivoPasajeros(FILE *P, Pasajeros pasajero_reservado[], int& x);
	int Reserva(Aviones avion[], int posicion, int num_vuelo, int fila, int columna);
	void ReservarAsiento(FILE *P, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int& x, int numVuelos);
	void ImprimirReserva(Informacion vuelos[], Pasajeros pasajero_reservado[], int posicion, int x);
	void GuardarArchivoPasajeros(FILE *P, Pasajeros pasajero_reservado);
	void CancelarReserva(FILE *P, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int& x, int& numVuelos);
	void eliminarPasajero(FILE* P, int dni, int numVuelos, int x, Aviones avion[], Pasajeros pasajero_reservado[]);
int MenuVuelos();
	void GeneralVuelos(FILE *V, FILE *P, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int x, int& numVuelos);
	void LeerArchivoVuelos(FILE *V, int& numVuelos, Informacion vuelos[]);
	void IngresarVuelo(FILE *V, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int x, int& numVuelos);
	int RegistrarVuelo(Informacion vuelos[], int& numVuelos);
	void GuardarArchivoVuelos(FILE *V, Informacion vuelos);
	void EliminarVuelo(FILE* V, FILE*P, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int x, int& numVuelos);
	void eliminarVuelo(FILE* V, FILE *P, Aviones avion[], int num_vuelo, int pos);
	void ImprimirVuelos(Informacion vuelos[], int numVuelos);
void crearV(FILE *V);
void crearP(FILE *P);
	
//PROGRAMA PRINCIPAL
int main() {
	setlocale(LC_ALL, "");
	
	//Declaracion de archivos
	FILE *V;
	FILE *P;
	
	//Declaracion de estructuras
	Informacion vuelos[50];
	Aviones avion[50];
	Pasajeros pasajero_reservado[numPasajeros];
		
	General(V, P, vuelos, avion, pasajero_reservado);	

}
//Fin PROGRAMA PRINCIPAL

//------------------------------------------

//Menu general de opciones
int MenuGeneral() {
    int op;
    cout << "\n";
    system("pause");
    system("cls");
	
    cout << "\n---- GESTI�N DE VUELOS ----" << endl;
	cout << "     Men� Principal" << endl;
	cout << " 1. Crear archivos" << endl;	
	cout << " 2. Horario de vuelos" << endl;
	cout << " 3. Reservas"<< endl;
	cout << " 4. Vuelos " << endl;
	cout << " 5. Salir del men�" << endl;
	cout << "---------------------------" << endl;
	cout << " Ingrese una opci�n: ";
    cin >> op;
    return op;
}

//Operaciones del men� general
void General(FILE *V, FILE *P, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[]){
	int op, x = 0, numVuelos = 0;
	
	LeerArchivoVuelos(V, numVuelos, vuelos);
	LeerArchivoPasajeros(P, pasajero_reservado, x);
	BuscarPasajero(vuelos, avion, pasajero_reservado, x, numVuelos);
	
    do {
    	op = MenuGeneral();
    	switch(op) {
    		case 1:
                crearV(V);
                crearP(P);
    			break;
    		case 2:
    			BuscarPorDestino(vuelos, numVuelos);
    			break;
    		case 3:
                GeneralReservas(P, vuelos, avion, pasajero_reservado, x, numVuelos);
    			break;
    		case 4:
				GeneralVuelos(V, P, vuelos, avion, pasajero_reservado, x, numVuelos);
				break;
    		default:
    			break;
		}
	} while (op != 5);	
	cout << " \n GRACIAS POR USAR EL SISTEMA DE GESTI�N DE VUELOS " << endl;
}

void crearV(FILE *V){
	V = fopen("Info_vuelos.txt", "w");
	if(V != NULL){
		cout << "\nCreaci�n exitosa de archivo Info_vuelos" << endl;
		fclose(V);
	}
	else{
		cout << "\nNo se puede crear el archivo Vuelos" << endl;
	}	
}

void crearP(FILE *P){
	P = fopen("Pasajeros.txt", "w");
	if(P != NULL){
		cout << "\nCreaci�n exitosa de archivo Pasajeros" << endl;
		fclose(P);
	}
	else{
		cout << "\nNo se puede crear el archivo Vuelos" << endl;
	}	
}

//Menu de opciones de destinos
int MenuHorarios() {
	int i;
	system("cls");
	cout << "\n--- MEN� HORARIO DE VUELOS ---" << endl;
	cout << " 1. Arequipa" << endl;
	cout << " 2. Trujillo" << endl ;
	cout << " 3. Cajamarca" << endl ;
	cout << " 4. Pucallpa" << endl ;
	cout << " 5. Ayacucho" << endl ;
	cout << " 6. Salir" << endl ;	
	cout << "------------------------------" << endl;
	cout << " Ingrese una opci�n: ";
	cin >> i;
	return i;
}

//Buscar todos los vuelos de un destino e imprimirlos
void BuscarPorDestino(Informacion vuelos[], int numVuelos) {
	int d;
	char s2[20];
	do{
		d = MenuHorarios();
		switch(d){	// Poner en orden segun las opciones de MenuHorarios
			case 1:
				strcpy(s2,"Arequipa");
				break;
			case 2:
				strcpy(s2,"Trujillo");
				break;
			case 3:
				strcpy(s2,"Cajamarca");
				break;
			case 4:
				strcpy(s2,"Pucallpa");
				break;
			case 5:
				strcpy(s2,"Ayacucho");
				break;
			default:
				strcpy(s2," ");
				break;
		}
	    if(d > 0 && d < 6){
	    	system("cls");
	        cout << "\n";
	        cout << "\nNUM VUELO    " << "FECHA         " << "HORA     " << "PRECIO    " << "DESTINO     " << "AEROLINEA" << endl;
			for (int i = 0; i < numVuelos; i++) {
		        if (strcmp(vuelos[i].destino, s2) == 0) {  
		            ImprimirDatos(vuelos[i]);
		        }
		    }  	
		   	cout<<endl;
			system("pause");
		}
	}while(d != 6);
}

void ImprimirDatos(Informacion vuelo) {
    cout << "   " << vuelo.num_vuelo << "       " << vuelo.fecha << "    " << vuelo.hora << "    " << vuelo.precio << "       " << vuelo.destino << "    " << vuelo.aerolinea << endl;
}

//Menu de Reservas
int MenuReservas(){
	int op;
    cout << "\n";
    system("cls");
    cout << "\n------- MEN� RESERVAS -------" << endl;
	cout << " 1. Consultar asientos" << endl;
	cout << " 2. Reservar asientos" << endl;
	cout << " 3. Cancelar reserva " << endl;
	cout << " 4. Salir" << endl;
	cout << "------------------------------" << endl;
	cout << " Ingrese una opci�n: ";
	cin >> op;
	return op;
}

//Operaciones de Reservas
void GeneralReservas(FILE *P, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int& x, int numVuelos){
	int op;
    do {
    	op = MenuReservas();
    	switch(op) {
    		case 1:
                BuscarReserva(vuelos, avion, pasajero_reservado, numVuelos, x);
                cout << endl;
                system("pause");
    			break;
    		case 2:
				ReservarAsiento(P, vuelos, avion, pasajero_reservado, x, numVuelos);
				cout << endl;
				system("pause");
    			break;
    		case 3:
    			CancelarReserva(P, vuelos, avion, pasajero_reservado, x, numVuelos);
    			cout << endl;
    			system("pause");
    			break;
    		default:
    			break;
		}
	} while (op != 4);
}

//Marcar con 'X' los asientos reservados le�dos de Pasajeros.txt
void BuscarPasajero(Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int x, int numVuelos){
	int fila, columna;
	for (int j = 0; j < numVuelos; j++){
		for (int i = 0; i < x; i++){
			if (pasajero_reservado[i].num == vuelos[j].num_vuelo){
				fila = pasajero_reservado[i].fila;
				columna = pasajero_reservado[i].columna;
				avion[j].asiento[fila - 1][columna - 1] = 'X';
			}
		}
	}
}

//Mostrar asientos disponibles del avion
void MostrarAvion(Aviones avion[], int posicion, int num_vuelo) {
    cout << "\n--------- VUELO " << num_vuelo << " ---------" << endl;
    cout << "     (1)  (2)  (3)  (4)  (5)" << endl;
    for (int j = 0; j < FILAS; j++) {
        cout << " (" << j + 1 << ")";
        for (int k = 0; k < COLUMNAS; k++) {
            cout << " [" << avion[posicion].asiento[j][k] << "]" << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

//Buscar por codigo de vuelo
int BuscarPorCodigo(Informacion vuelos[], int numVuelos, int num_vuelo) {
    for (int i = 0; i < numVuelos; i++) {
        if (vuelos[i].num_vuelo == num_vuelo) {
            return i;
        }
    }
    return -1;
}

//Buscar el numero de pasajero que reserva el asiento seleccionado
void BuscarReserva(Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int numVuelos, int x){
	int num_vuelo, posicion, op, fila, columna, p = -1, b = 0;
	system("cls");
	cout << "\n------- CONSULTAR ASIENTOS -------" << endl;
	cout << "\n DATOS DE VUELO" << endl;
    cout << " Ingrese el n�mero de vuelo: ";
    cin >> num_vuelo;
    posicion = BuscarPorCodigo(vuelos, numVuelos, num_vuelo);   
    if (posicion != -1){
    	MostrarAvion(avion, posicion, num_vuelo);
    	cout << "\n  �Desea solicitar informaci�n de alg�n asiento?" << endl << "  (1. S� / 2. No): ";
		cin >> op;
		if (op == 1){
			do{
				cout << "\n  Ingrese la fila del asiento a consultar: ";
    			cin >> fila;
    			cout << "  Ingrese la columna del asiento a consultar: ";
   				cin >> columna;
   				for (int y = 0; y < x; y++){
   					if (pasajero_reservado[y].num == num_vuelo){
   						if (pasajero_reservado[y].fila == fila){
   							if (pasajero_reservado[y].columna == columna){
   								p = y;
							}	
						}
					}
				}
				if (p != -1){
					ImprimirReserva(vuelos, pasajero_reservado, posicion, p);
					p = -1;
					system("pause");
					system("cls");
				}
				else {
					cout << "\n  El asiento se encuentra desocupado." << endl;
					cout << "\n";
					system("pause");
					system("cls");
				}
				
				MostrarAvion(avion, posicion, num_vuelo);
				cout << "\n  �Desea consultar otro asiento?" << endl << "  (1. S� / 2. No): ";
				cin >> b;
			} while (b == 1);
		}
		
	}
	else {
		cout << "\n El n�mero de vuelo no existe." << endl;
		cout << "\n";
		system("pause");
	}
	system("cls");
	cout << "\n  �Desea consultar otro asiento de otro vuelo?" << endl << "  (1. S� / 2. No): ";
	cin >> b;
			
	if(b == 1){
		BuscarReserva(vuelos, avion, pasajero_reservado, numVuelos, x);		
	}
}

//Solicitud de Datos a los pasajeros
void InformacionPasajero(Pasajeros pasajero_reservado[], int& x, int num_vuelo, int i) {
	cout << "\n DATOS PERSONALES DEL PASAJERO " << i + 1 << endl;
    cout << " Ingrese su nombre completo: ";
    cin.ignore();
	cin.getline(pasajero_reservado[x].nombre, 50);
	do{
		cout << " Ingrese su DNI: ";
		cin >> pasajero_reservado[x].dni;
	} while(pasajero_reservado[x].dni < 10000000 || pasajero_reservado[x].dni > 100000000 );
	do{
		cout << " Ingrese su n�mero de celular: ";
		cin >> pasajero_reservado[x].telefono;
	} while(pasajero_reservado[x].telefono < 100000000 || pasajero_reservado[x].telefono > 1000000000 );
    cout << " Ingrese su nombre correo electr�nico: ";
    cin.ignore();
	cin.getline(pasajero_reservado[x].correo, 30);
	pasajero_reservado[x].num = num_vuelo;
	x++;
}

//Leer pasajeros del txt y guardarlo en el vector pasajero_reservado[]
void LeerArchivoPasajeros(FILE *P, Pasajeros pasajero_reservado[], int& x){
	x = 0;
	Pasajeros p;
	P = fopen("Pasajeros.txt", "rb");
	if (P != NULL){
		while(!feof(P)){
			fread(&p, sizeof(p), 1, P);	
			if(!feof(P)){
				pasajero_reservado[x] = p;
				x++;
			}
		}
	}	
	else {
		cout << endl << " ERROR NO SE PUDO ABRIR" << endl;
	}
	fclose(P);
}

//Reservar un asiento 'O' --> 'X'
int Reserva(Aviones avion[], int posicion, int num_vuelo, int fila, int columna) {
    int b = 0;
    if (avion[posicion].asiento[fila - 1][columna - 1] == 'O') {
        avion[posicion].asiento[fila - 1][columna - 1] = 'X';
        b = 1;
        system("cls");
        cout << "Asiento seleccionado: " << endl;
        MostrarAvion(avion, posicion, num_vuelo);
        cout << "Fila: " << fila << endl;
        cout << "Columna: " << columna << endl;
	}
	return b;
}

//Reservar asiento
void ReservarAsiento(FILE *P, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int& x, int numVuelos){
	int num_vuelo, posicion, asientos, fila, columna, b, y, z, i = 0;
	system("cls");
	cout << "\n------- RESERVAR ASIENTOS -------" << endl;
	cout << "\n DATOS DE VUELO" << endl;
    cout << " Ingrese el n�mero de vuelo: ";
    cin >> num_vuelo;
	posicion = BuscarPorCodigo(vuelos, numVuelos, num_vuelo);
	if (posicion == -1){
		cout << "\nEl n�mero de vuelo no existe." << endl;
	}
	else {
		InformacionPasajero(pasajero_reservado, x, num_vuelo, i);
		system("cls");
		cout << "\n  �Cu�ntos asientos quiere reservar?: ";
        cin >> asientos;
        for (int i = 1; i < asientos; i++){
        	InformacionPasajero(pasajero_reservado, x, num_vuelo, i);
		}
		y = x - asientos;
		z = y;
        MostrarAvion(avion, posicion, num_vuelo);
        for (int i = 0; i < asientos; i++){
        	do {
        		cout << "Ingrese el n�mero de fila para el asiento " << i + 1 << ": ";
                cin >> fila;
                cout << "Ingrese el n�mero de columna para el asiento " << i + 1 << ": ";
                cin >> columna;
                if (fila >= 1 && fila <= FILAS && columna >= 1 && columna <= COLUMNAS){
                	b = Reserva(avion, posicion, num_vuelo, fila, columna);
                	if (b == 1){
                		pasajero_reservado[z].fila = fila;
                      	pasajero_reservado[z].columna = columna;
                		GuardarArchivoPasajeros(P, pasajero_reservado[z]);
                		LeerArchivoPasajeros(P, pasajero_reservado, x);
						BuscarPasajero(vuelos, avion, pasajero_reservado, x, numVuelos);		           
                        z++;
                        cout << "Asiento reservado con �xito." << endl << endl;        		
					}
					else {
						cout << "\nAsiento ya reservado. Por favor, seleccione otro." << endl << endl;
					}
				}
				else {
					cout << "\nEl n�mero de fila o columna es inv�lido." << endl << endl;
				}
			} while (fila < 1 || fila > FILAS || columna < 1 || columna > COLUMNAS || b == 0);
		}
		if (b == 1){
		    system("cls");
            MostrarAvion(avion, posicion, num_vuelo);
            cout << "Reserva realizada con �xito." << endl;
            for (int i = 0; i < asientos; i++){
            	ImprimirReserva(vuelos, pasajero_reservado, posicion, y);
            	y++;
			}
		}
	}
}

//Mostrar detalles de la reserva
void ImprimirReserva(Informacion vuelos[], Pasajeros pasajero_reservado[], int posicion, int x){
	cout << "\n------------------------------------------" << endl;
	cout << "          DETALLES DE LA RESERVA           " << endl;
	cout << "------------------------------------------" << endl;
	cout << "    Nombre completo: " << pasajero_reservado[x].nombre << endl;
    cout << "    DNI: " << pasajero_reservado[x].dni << endl;
    cout << "    N�mero de celular: " << pasajero_reservado[x].telefono << endl;
    cout << "    Correo electr�nico: " << pasajero_reservado[x].correo << endl;
	cout << "    N�mero de vuelo: " << vuelos[posicion].num_vuelo << endl;
    cout << "    Aerol�nea: "<< vuelos[posicion].aerolinea << endl;
    cout << "    Fecha: " << vuelos[posicion].fecha << endl;
	cout << "    Hora: " << vuelos[posicion].hora << endl;
    cout << "    Origen: Lima" << endl;
    cout << "    Destino: " << vuelos[posicion].destino << endl;
    cout << "    Asiento reservado:" << endl;
   	cout << "       Fila " << pasajero_reservado[x].fila << ", Columna " << pasajero_reservado[x].columna << endl;
    cout << "    Precio: $" << vuelos[posicion].precio << endl;
    cout << "------------------------------------------" << endl;
}

//Guardar la informaci�n del pasajero (con el asiento reservado) en Pasajeros.txt
void GuardarArchivoPasajeros(FILE *P, Pasajeros pasajero_reservado){
	Pasajeros p;
	P = fopen("Pasajeros.txt", "ab");
	if (P != NULL){	
		p = pasajero_reservado;	
		fwrite(&p, sizeof(p), 1, P);
		if(!ferror(P)){
			fclose(P);
			cout << endl << " ARCHIVO.Pasajeros.txt GUARDADO"  << endl << endl;
		}
		else {
			cout << endl << " ERROR NO SE GUARD� " << endl;
		}
	}
	else{
		cout << endl << " NO SE PUDO ABRIR EL ARCHIVO " << endl ;
	}
}

//Cancelar una reserva
void CancelarReserva(FILE *P, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int& x, int& numVuelos){
	int num_vuelo, dni, posicion, y, b = 0, op;
	system("cls");
	cout<<"\n------ CANCELAR RESERVA ------" << endl;
	cout << "\n Ingrese el n�mero de vuelo: ";
	cin >> num_vuelo;
	posicion = BuscarPorCodigo(vuelos, numVuelos, num_vuelo);
	if (posicion != -1){
		do{
			cout << " Ingrese su DNI: ";
			cin >> dni;
		} while(dni < 10000000 || dni > 100000000 );
		for (int i = 0; i < numPasajeros; i++){
			if (pasajero_reservado[i].dni == dni){
				y = i;
				b = 1;
			}
		}
		if (b == 1){
			ImprimirReserva(vuelos, pasajero_reservado, posicion, y);
			cout<<"\n  �Seguro de que desea eliminar los datos de la reserva?" << endl << "  (1. S� / 2. No): ";
        	do{
           	 	cin >> op;
            	switch(op){
                case 1: eliminarPasajero(P, dni, numVuelos, x, avion, pasajero_reservado);
                		LeerArchivoPasajeros(P, pasajero_reservado, x);
               			BuscarPasajero(vuelos, avion, pasajero_reservado, x, numVuelos);
                        cout << "\n  La reserva ha sido cancelada con �xito." << endl;
                        break;
                case 2: break;
                default: cout << "\n  Digit� una opci�n no v�lida." << endl;
            	}
       		 } while(op != 1 && op != 2);
		}
		else {
			cout << "\n No existe reserva a ese n�mero de DNI." << endl;
		}
	}	
	else {
		cout << "\n El n�mero de vuelo no existe." << endl;
	}
}

//Eliminar pasajero de Pasajeros.txt a partir del dni
void eliminarPasajero(FILE* P, int dni, int numVuelos, int x, Aviones avion[], Pasajeros pasajero_reservado[]) {
    FILE* temp;
    Pasajeros p;
	int fila, columna;
	
	for (int j = 0; j < numVuelos; j++){
		for (int i = 0; i < x; i++){
			if (pasajero_reservado[i].dni == dni){
				fila = pasajero_reservado[i].fila;
				columna = pasajero_reservado[i].columna;
				avion[j].asiento[fila - 1][columna - 1] = 'O';				
			}
		}
	}    
    
    P = fopen("Pasajeros.txt", "rb");
    temp = fopen("temp.txt", "wb");
    if (P != NULL && temp != NULL) {
        while (!feof(P)) {
            fread(&p, sizeof(p), 1, P);
            if (!feof(P) && p.dni != dni) {
                fwrite(&p, sizeof(p), 1, temp);
            }
        }
        fclose(P);
        fclose(temp);
        remove("Pasajeros.txt");
        rename("temp.txt", "Pasajeros.txt");
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

//Menu de vuelos
int MenuVuelos(){
	int op;
    cout << "\n";
    system("cls");
    cout << "\n-------- MEN� VUELOS --------" << endl;
	cout << " 1. Registrar vuelo "<< endl;
	cout << " 2. Cancelar vuelo " << endl;
	cout << " 3. Mostrar vuelos registrados " << endl;
	cout << " 4. Salir" << endl;
	cout << "------------------------------" << endl;
	cout << " Ingrese una opci�n: ";
	cin >> op;
	return op;	
}

void GeneralVuelos(FILE *V, FILE *P, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int x, int& numVuelos){
	int op;
	LeerArchivoVuelos(V, numVuelos, vuelos);
	LeerArchivoPasajeros(P, pasajero_reservado, x);
    do {
    	op = MenuVuelos();
    	switch(op) {
    		case 1:
    			IngresarVuelo(V, vuelos, avion, pasajero_reservado, x, numVuelos);
    			cout << endl;
    			system("pause");
    			break;
    		case 2:
    			EliminarVuelo(V, P, vuelos, avion, pasajero_reservado, x, numVuelos);
    			cout << endl;
    			system("pause");
    			break;
    		case 3: 
    			ImprimirVuelos(vuelos, numVuelos);
    			cout << endl;
    			system("pause");
    			break;
    		default:
    			break;
		}
	} while (op != 4);	
}

//Leer vuelos de Info_vuelos.txt
void LeerArchivoVuelos(FILE *V, int& numVuelos, Informacion vuelos[]){
	numVuelos = 0;
	Informacion vuelo;
	V = fopen("Info_vuelos.txt", "rb");
	if (V != NULL){
		while(!feof(V)){
			fread(&vuelo, sizeof(vuelo), 1, V);	
			if(!feof(V)){
				vuelos[numVuelos] = vuelo;
				numVuelos++;
			}
		}
	}	
	else {
		cout << endl << " ERROR NO SE PUDO ABRIR" << endl;
	}
	fclose(V);
}

//Registrar un vuelo
void IngresarVuelo(FILE *V, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int x, int& numVuelos){
	system("cls");
	int s, b = 0;
	cout << "\n------ REGISTRAR VUELO ------" << endl;
	s = RegistrarVuelo(vuelos, numVuelos);
	if (s == 1){
		GuardarArchivoVuelos(V, vuelos[numVuelos - 1]);
		LeerArchivoVuelos(V, numVuelos, vuelos);
		BuscarPasajero(vuelos, avion, pasajero_reservado, x, numVuelos);
	}
	cout << "\n  �Desea registrar otro vuelo?" << endl << "  (1. S� / 2. No): ";
	cin >> b;	
	if(b == 1){
		system("cls");
		IngresarVuelo(V, vuelos, avion, pasajero_reservado, x, numVuelos);		
	} 
}

int RegistrarVuelo(Informacion vuelos[], int& numVuelos){
	int num_vuelo, posicion, s = 0;
	char destino[20];
	cout << "\n Ingrese el n�mero de vuelo: ";
	cin >> num_vuelo;
	posicion = BuscarPorCodigo(vuelos, numVuelos, num_vuelo);
	if(posicion == -1){
		vuelos[numVuelos].num_vuelo = num_vuelo;
		cout << "\n Ingrese la fecha (dd-mm-aaaa): ";
		cin.ignore();
		cin.getline(vuelos[numVuelos].fecha, 20);
		cout << " Ingrese la hora (hh:mm): ";
		cin.getline(vuelos[numVuelos].hora, 20);
		cout << " Ingrese el precio: ";
		cin >> vuelos[numVuelos].precio;
		cout << " Ingrese la aerolinea: ";
		cin.ignore();
		cin.getline(vuelos[numVuelos].aerolinea, 20);
		cout << " Ingrese el destino: ";
		cin.getline(destino, 20);
		if(strcmp(destino,"Arequipa")==0 || strcmp(destino,"Trujillo")==0 || strcmp(destino,"Cajamarca")==0 || strcmp(destino,"Pucallpa")==0 || strcmp(destino,"Ayacucho")==0){
			s = 1;
			strcpy(vuelos[numVuelos].destino, destino);
			cout << "\nNUM VUELO    " << "FECHA         " << "HORA     " << "PRECIO    " << "DESTINO     " << "AEROL�NEA" << endl;
			ImprimirDatos(vuelos[numVuelos]);
			numVuelos++;
			cout << "\n Registro de vuelo realizada con �xito." << endl;
		}
		if(s == 0){
			cout << "\n El destino no est� habilitado." << endl;
		}
	}
	else{
		cout << "\n El n�mero de vuelo ya existe." << endl;
	}
	return s;
}

//Guardar vuelo en Info_vuelos.txt
void GuardarArchivoVuelos(FILE *V, Informacion vuelos){
	Informacion p;
	V = fopen("Info_vuelos.txt", "ab");
	if (V != NULL){	
		p = vuelos;	
		fwrite(&p, sizeof(p), 1, V);
		if(!ferror(V)){
			fclose(V);
			cout << endl << " ARCHIVO.Info_vuelos.txt GUARDADO"  << endl << endl;
		}
		else {
			cout << endl << " ERROR NO SE GUARD� " << endl;
		}
	}
	else{
		cout << endl << " NO SE PUDO ABRIR EL ARCHIVO " << endl ;
	}
}

//Cancelar un vuelo
void EliminarVuelo(FILE* V, FILE *P, Informacion vuelos[], Aviones avion[], Pasajeros pasajero_reservado[], int x, int& numVuelos) {
	system("cls");
	LeerArchivoVuelos(V, numVuelos, vuelos);
	LeerArchivoPasajeros(P, pasajero_reservado, x);
    int num_vuelo, pos, op, b = 0;
    cout << "\n--------- CANCELAR VUELO ---------" << endl;
    cout << "\n  Ingrese el n�mero de vuelo: ";
    cin >> num_vuelo;
    pos = BuscarPorCodigo(vuelos, numVuelos, num_vuelo);
    if (pos != -1) {
    	cout << "\n  Vuelo a eliminar: " << endl;
    	cout << "\nNUM VUELO    " << "FECHA         " << "HORA     " << "PRECIO    " << "DESTINO     " << "AEROL�NEA" << endl;
		ImprimirDatos(vuelos[pos]);
		cout<<"\n  �Seguro de que desea eliminar los datos del vuelo?" << endl << "  (1. S� / 2. No): ";
        do{
            cin >> op;
            switch(op){
                case 1: eliminarVuelo(V, P, avion, num_vuelo, pos);
               			LeerArchivoVuelos(V, numVuelos, vuelos);
               			LeerArchivoPasajeros(P, pasajero_reservado, x);
               			BuscarPasajero(vuelos, avion, pasajero_reservado, x, numVuelos);
                        cout << "\n  El vuelo ha sido eliminado con �xito." << endl;
                        break;
                case 2: break;
                default: cout<<"\n  Digit� una opci�n no v�lida."<<endl;
            }
        } while(op!=1 && op!=2);
    } else {
        cout << "\n  No se encontr� el vuelo con el n�mero indicado." << endl;
    }
    cout << "\n  �Desea eliminar otro vuelo?" << endl << "  (1. S� / 2. No): ";
	cin >> b;	
	if(b == 1){
		system("cls");
		LeerArchivoPasajeros(P, pasajero_reservado, x);
		EliminarVuelo(V, P, vuelos, avion, pasajero_reservado, x, numVuelos);		
	}
}

//Eliminar vuelo de Info_vuelos.txt y pasajeros de Pasajeros.txt a partir del n�mero de vuelo
void eliminarVuelo(FILE* V, FILE *P, Aviones avion[], int num_vuelo, int pos) {
    FILE *temp, *temp2;
    Informacion vuelo;
    Pasajeros p;
    
	for (int i = 0; i < FILAS; i++){
		for (int j = 0; j < COLUMNAS; j++){
			avion[pos].asiento[i][j] = 'O';
		}
	}
	
    V = fopen("Info_vuelos.txt", "rb");
    temp = fopen("temp.txt", "wb");
    if (V != NULL && temp != NULL) {
        while (!feof(V)) {
            fread(&vuelo, sizeof(vuelo), 1, V);
            if (!feof(V) && vuelo.num_vuelo != num_vuelo) {
                fwrite(&vuelo, sizeof(vuelo), 1, temp);
            }
        }
        fclose(V);
        fclose(temp);
        remove("Info_vuelos.txt");
        rename("temp.txt", "Info_vuelos.txt");
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
    
    P = fopen("Pasajeros.txt", "rb");
    temp2 = fopen("temp2.txt", "wb");
    if (P != NULL && temp2 != NULL) {
        while (!feof(P)) {
            fread(&p, sizeof(p), 1, P);
            if (!feof(P) && p.num != num_vuelo) {
                fwrite(&p, sizeof(p), 1, temp2);
            }
        }
        fclose(P);
        fclose(temp2);
        remove("Pasajeros.txt");
        rename("temp2.txt", "Pasajeros.txt");
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

//Imprimir todos los vuelos que se encuentran en Info_vuelos.txt
void ImprimirVuelos(Informacion vuelos[], int numVuelos) {
	system("cls");
    cout << "\nNUM VUELO    " << "FECHA         " << "HORA     " << "PRECIO    " << "DESTINO     " << "AEROL�NEA" << endl;
    for (int i = 0; i < numVuelos; i++) {
        ImprimirDatos(vuelos[i]);
    }
}
