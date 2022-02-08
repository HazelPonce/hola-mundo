#include <iostream>
#include <fstream> // TIENE FUNCIONES DE LECTURA Y ESCRITURA DENTRO DEL ARCHIVO
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

/* cin>> // lectura de numeros
   cin.getline(cadena, longitud) // para leer tipos de datos char
   getline(cin, cadena) // para leer tipos de datos string
*/

using namespace std;

class Productos
{
public:
    char codigo[50], descripcion[50], precio[50]; //ARREGLOS UNIDIMENSIONALES
    void Capturar(); //METODOS
    void Mostrar();
    void Buscar();
    void Eliminar();
    void Modificar();
}p;


/////METODO CAPTURAR
void Productos::Capturar() // DE LA CLASE ALUMNO PERTENECE CAPTURAR ESO SIGNIFICAN LOS DOS PUNTOS
{
    cout<<"Dame el codigo del producto  ";
    cin.getline(codigo, 50);
    cin.getline(codigo, 50); //EN LUGAR DE FFLUSH X QUE NO SIRVE CON GETLINE PARA LEER CADENAS
    cout<<"Dame la descripcion  ";
    cin.getline(descripcion,50);
    cout<<"Dame el precio  ";
    cin.getline(precio,50);
    ofstream Archivo("Prodauto.txt",ios::app); // ofstream crea un objeto para escritura en el archivo llamado "Archivo", ios::app = entrada y salida de datos
    Archivo<<codigo<<':'<<descripcion<<':'<<precio<<':'; // se escribiendo en el archivo creado campo por campo separado por el delimitador '|'
    Archivo.close(); // cerrar el archivo
}

//////METODO MOSTRAR
void Productos::Mostrar()
{
    int i;
    char alubus[50];
    int iguales;
    ifstream Lectura("Prodauto.txt"); // abrir archivo en formato de lectura, "Lectura" que es un objeto
    if(!Lectura.good()) // good ( libreria fstream) nos verifica si hubo problema al abrir el archivo a traves de true o false
    {
        cout<<"No existe el archivo\n";
        system("pause");
    }
    else
    {
        while(!Lectura.eof()) // eof = end of file
        {
            //Lectura de la variable user
            i=0;
            do
            {
                Lectura.read((char *)&codigo[i],1); //leo el objeto de tipo char, lo asigno a la variable user en la posicion que tenga el subindice, y se lee de caracter en car�cter
                if(Lectura.eof())
                    break;
                i++;
            }while(codigo[i-1]!=':'); // mientras user en la posicion del subindice menos 1 sea diferente al delimitador, sigues escribiendo en el arreglo "user"
            codigo[i-1]='\0'; // si no se cumple el while anterior, entonces escribe en la posicion del delimitador '\0' que significa final de la cadena para saber que se termino ese campo "user"
            //Lectura de la variable pass
            i=0;
            do
            {
                Lectura.read((char *)&descripcion[i],1);
                if(Lectura.eof())
                    break;
                i++;
            }while(descripcion[i-1]!=':');
            descripcion[i-1]='\0';
            //Lectura de la variable nom
            i=0;
            do
            {
                Lectura.read((char *)&precio[i],1);
                if(Lectura.eof())
                    break;
                i++;
            }while(precio[i-1]!=':');
            precio[i-1]='\0';
            //Lectura de la variable ape

            if(Lectura.eof())
                break;

            //Imprimes valores
            cout<<"------------------------------------>Cabecera Ethernet<------------------------------------";
            cout<<endl<<"\nDireccion MAC destino/Destination MAC address  "<<codigo<<endl<<"\nDireccion MAC de origen/Address of origin 0x "<<descripcion<<endl<<"\nTipo de Servicio/Type of service 0x  "<<precio<<endl; // endl=salto de linea
            
            iguales = strcmp(precio,alubus);

            if(iguales == 0){
                cout<<"Protocolo en servicio\n\n";
            }
            else{
                cout<<"El tipo de servicio corresponde a 0x0800 Internet protocol (Ipv4) \n";
                cout<<endl<<endl;
            }       
            if(Lectura.eof())
                break;
        }
        system("pause");
    }
    Lectura.close(); // cierras el archivo a traves del objeto "Lectura"
}
/* PARA BUSCAR POR CUALQUIER ATRIBUTO O VARIABLE SE TIENE QUE RECORRER TODOS LOS CAMPOS DEL REGISTRO CARACTER POR CARACTER */
void Productos::Buscar(){
    int b;  b = 0; // Bandera
    int i; // Contador
    int iguales;
    char caracter;
    char alubus[10];


    ifstream arc("Prodauto.txt");/* Abrimos el archivo */
    if(!arc.good())   /* Verificamos si el archivo existe */
    {
        cout<<"\n NO EXISTE ARCHIVO...\n";
    }

    else{
        cout<<"\n Escribe el codigo del producto a buscar  ";
        cin.getline(alubus,50);
        cin.getline(alubus,50);


        while(!arc.eof()){
            i = 0;
            do{ // ciclo para leer cada uno de los campos
                arc.read((char*)&caracter,1); // Leo 1 caracter y se lo asigno a la variable caracter
                if(caracter!=':')
                {
                    codigo[i] = caracter; // Le asigna al arreglo en la posicion i, el valor del caracter leido
                    i++;
                }

            }while(caracter != ':');

            codigo[i]= '\0'; // Finaliza la cadena despues del fin del atributo

            i = 0;
            do
            {
                arc.read((char*)&caracter,1);
                if(caracter!=':')
                {
                   descripcion[i] = caracter;
                    i++;
                }

            }while(caracter != ':');
            descripcion[i]= '\0';


            i = 0;
            do
            {
                arc.read((char*)&caracter,1);
                if(caracter!=':' && !arc.eof()) // Validacion que se debe hacer con el ultimo campo
                {
                    precio[i] = caracter;
                    i++;
                }

            }while(caracter != ':' && !arc.eof()); // Validacion que se debe hacer con el ultimo campo
            precio[i]= '\0';


            if(arc.eof())
            {
                break;
            }

            iguales = strcmp(codigo,alubus);

            if(iguales == 0){
                cout<<"\n CODIGO  " <<codigo <<"\n DESCRIPCION  " <<descripcion <<"\n PRECIO  " <<precio <<endl<<"\n";
                b = 1; // Activamos la bandera
                break;
            }
        }

        if( b == 0){
            cout<<"\n\n NO EXISTE EL REGISTRO... \n\n";
        }
        arc.close();
    }
}

void Productos::Eliminar(){
    int b = 0; // Bandera
    int i; // Contador
    int iguales,respuesta; respuesta = 0;
    char caracter;
    char alubus[50];


    ifstream arc("Prodauto.txt"); /* Abrimos el archivo */
    if(!arc.good())   /* Verificamos si el archivo existe */
    {
        cout<<"\n NO EXISTE ARCHIVO...\n";
    }
    else{
        cout<<"\n Escribe el codigo del producto  ";
        cin.getline(alubus,50);
        cin.getline(alubus,50);

        while(!arc.eof()){
            i = 0;
            do{ // ciclo para leer cada uno de los campos
                arc.read((char*)&caracter,1); // Leo 1 caracter y se lo asigno a la variable caracter
                if(caracter!=':')
                {
                    codigo[i] = caracter; // Le asigna al arreglo en la posicion i, el valor del caracter leido
                    i++;
                }

            }while(caracter != ':');

            codigo[i]= '\0'; // Finaliza la cadena despues del fin de la cadena

            i = 0;
            do
            {
                arc.read((char*)&caracter,1);
                if(caracter!='|')
                {
                    descripcion[i] = caracter;
                    i++;
                }

            }while(caracter != ':');
            descripcion[i]= '\0';

            i = 0;
            do
            {
                arc.read((char*)&caracter,1);
                if(caracter!=':' && !arc.eof()) // Validacion que se debe hacer con el ultimo campo
                {
                    precio[i] = caracter;
                    i++;
                }

            }while(caracter != ':' && !arc.eof()); // Validacion que se debe hacer con el ultimo campo
            precio[i]= '\0';


            if(arc.eof())
            {
                break;
            }

            iguales = strcmp(codigo,alubus); // COMPARACION DE LOS CAMPOS 0 ES VERDADERO

            if(iguales == 0){
                cout<<"\n CODIGO  " <<codigo <<"\n DESCRIPCION  " <<descripcion <<"\n PRECIO  " <<precio <<endl<<"\n";
                b = 1; // Activamos la bandera            }
        }


        }
        arc.close();
        }

        if(b == 0) {
            cout<<"\n\n EL REGISTRO NO EXISTE \n\n";
        }
        if(b == 1){

            cout<<"\n Escribe 1 si deseas eliminar este registro  ";

            cin>>respuesta;

            if(respuesta == 1){
                ifstream arc ("Prodauto.txt"); // Abrimos el archivo de datos
                ofstream temporal ("temporalauto.txt",ios::app); // Creamos el archivo temporal

                while(!arc.eof()){
                    i = 0;
                    do{ // ciclo para leer cada uno de los campos
                        arc.read((char*)&caracter,1); // Leo 1 caracter y se lo asigno a la variable caracter
                        if(caracter!=':')

                        {
                            codigo[i] = caracter; // Le asigna al arreglo en la posicion i, el valor del caracter leido
                            i++;
                        }

                    }while(caracter != ':');
                    codigo[i]= '\0'; // Finaliza la cadena despues del fin de la cadena

                    i = 0;
                    do
                    {
                        arc.read((char*)&caracter,1);
                        if(caracter!=':')
                        {

                            descripcion[i] = caracter;
                            i++;
                        }

                    }while(caracter != ':');
                    descripcion[i]= '\0';

                    i = 0;
                    do
                    {
                        arc.read((char*)&caracter,1);
                        if(caracter!=':' && !arc.eof()) // Validacion que se debe hacer con el ultimo campo
                        {
                            precio[i] = caracter;
                            i++;
                        }

                    }while(caracter != ':' && !arc.eof()); // Validacion que se debe hacer con el ultimo campo
                    precio[i]= '\0';

                   if(arc.eof())
                    {
                        break;
                    }

                    iguales = strcmp(codigo,alubus);
                    if(iguales != 0){
                        temporal <<codigo<<":"<<descripcion<<":"<<precio<<":";

                    }
                } // while

                arc.close();
                temporal.close();
                remove("Prodauto.txt");
                rename("temporalauto.txt","Prodauto.txt");
                cout<<"\n\n EL REGISTRO FUE ELIMINADO... \n\n";
                b = 1;
            } // if

            else {
                cout<<"\n EL REGISTRO NO FUE ELIMINADO... \n\n";
            }

        }


}

void Productos::Modificar()
{
    int i;//contador
    int opcion;
    char prodMod[50];
    bool b;

    ifstream Lectura("Prodauto.txt");/* Abrimos el archivo */
    ofstream LecturaTemporal("temporalauto.txt",ios::app);

    if(!Lectura.good())
        cout<<"\n EL REGISTRO NO EXISTE \n ";
    else
    {
        cout<<"\n Introduce el codigo a modificar    ";
        cin.getline(prodMod,50);
        cin.getline(prodMod,50);

        b = false;

        while(!Lectura.eof()){

            i=0;
            do{
                Lectura.read((char*)&codigo[i],1);// Leo 1 caracter y se lo asigno a la variable caracter
                if(Lectura.eof()) break;
                i++;
            }while(codigo[i-1]!=':');
            codigo[i-1]='\0';//Finaliza la cadena despues del fin de la cadena
            if(Lectura.eof()) break;


            i=0;
            do{
                Lectura.read((char*)&descripcion[i],1);// Leo 1 caracter y se lo asigno a la variable caracter
                if(Lectura.eof()) break;
                i++;
            }while(descripcion[i-1]!=':' && !Lectura.eof());
            descripcion[i-1]='\0';//Finaliza la cadena despues del fin de la cadena
            if(Lectura.eof()) break;


            //NOMBRE
            i=0;
            do{// ciclo para leer cada uno de los campos
                Lectura.read((char*)&precio[i],1);// Leo 1 caracter y se lo asigno a la variable caracter
                if(Lectura.eof()) break;
                i++;
            }while(precio[i-1]!=':');
            precio[i-1]='\0';// Finaliza la cadena despues del fin de la cadena
            if(Lectura.eof()) break;

            if(strcmp(codigo,prodMod)==0 && !b)
            {
                cout<<endl<<"\n  Codigo : "<<codigo<<endl<<"\n  Descripcion : "<<descripcion<<endl<<"\n  Precio : "<<precio<<endl;

                cout <<"\n 1) Que desea realiza ?\n ";
                cout <<"\n 1) Modificar Codigo  ";
                cout <<"\n 2) Modificar Descripcion ";
                cout <<"\n 3) Modificar Precio  ";
                cout <<"\n 4) Regresar  ";

                cout<<"\n   Elige la opcion a realizar  ";
                cin>>opcion;


                switch(opcion) ///switch para realizar las modificaciones
                {
                    case 1:///////nombre del alumno
                        cout<<"\n Codigo del Producto  ";
                        cin.getline(codigo,50);
                        cin.getline(codigo,50);
                        break;
                    case 2://////apellido
                        cout<<"\n Descripcion  ";
                        cin.getline(descripcion,50);
                        cin.getline(descripcion,50);
                        break;
                    case 3:///correo electronico
                        cout<<"\n Precio  ";
                        cin.getline(precio,50);
                        cin.getline(precio,50);
                        break;
                    default: cout<<"\n No se encontro la opcion ";
                }

                if(opcion!=6 && opcion>0 && opcion<7)
                    b = true;
            }
            LecturaTemporal<<codigo<<'|'<<descripcion<<'|'<<precio<<'|';
        }
        Lectura.close();
        LecturaTemporal.close();
        if(!b)
            cout<<"\n No se encontro arhcivo ";

        remove("Prodauto.txt");
        rename("temporalauto.txt","Prodauto.txt");
    }
}


int main(){
    int opc1;
    cout<<"----------------------BIENVENIDO------------------------\n\n";
    cout<<"Analizador de protocolos para principiantes\n\n";
    cout<<"Este es nuestro paquete\n\n";
    cout<<" 00 80 5F 18 10 15 00 A0 24 57 75 BA 08 00 45 00 \n 00 60 21 08 40 00 20 06 32 23 82 82 01 37 82 82 \n 01 32 04 07 00 8B 00 18 D6 B3 02 31 70 23 50 18 \n 21 E6 81 94 00 00 00 00 0034 FF 53 4D 42 10 00 \n 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \n 00 00 07 40 79 53 03 08 81 7A 00 11 00 04 5C 44 \n 49 50 4C 4F 54 45 43 5C 4D 4F 44 30 31 00 00 00 \n 00 00 ";
      
    
    cout<<"\n***Indica una opcion valida***\n\n-----------------------MENU PRINCIPAL-----------------\n\n 1.- Analizar paquete de datos alojado en el ordenador \n 2.- Analizar un paquete Wifi\n 3.-SALIR \n\n SELECCIONA UNA OPCION (1-3): ";
    cin>>opc1;
        if (opc1==1)
        {
            p.Mostrar();
            main();
        }
        if (opc1==2)
        {
            cout<<"\nSeguimos desarrollando esta parte del programa/We continue to develop this part of the program\n\n";
            main();
        }
        if (opc1==3)
        {
            cout<<"\nGracias / Thank you / Mercy";
        }
        if (opc1!=1&&opc1!=2&&opc1!=3)
        {
            main();   
        }
    /*
    
    
    do{
        cout<<"\n 1.- CAPTURAR \n 2.- MOSTRAR \n 3.- BUSCAR \n 4.- ELIMINAR \n 5.- MODIFICAR \n 6-SALIR \n\n SELECCIONA LA OPCION (1-5): ";
        cin>>opc;
        switch(opc){
            case 1: p.Capturar();
                break;

            case 2: p.Mostrar();
                break;

            case 3: p.Buscar();
                break;

            case 4: p.Eliminar();
                break;

            case 5: p.Modificar();
                break;
        }

    }while(opc!=6);
    */
}
