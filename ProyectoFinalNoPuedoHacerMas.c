/* sistema que simule un inventario de una tienda de abarrotes: se requiere crear archivos con los
productos, precios, existencias, listas ligadas para manipular el inventario diario, guardar en archivos
los reportes de venta diarios y un menú para dar de alta, baja o modificar los productos, precios y ver
reportes por fechas.*/

#include <stdio.h>

#include <string.h>

#include <malloc.h>

#include <stdlib.h>

#include <time.h>

typedef struct{ 
	char nombre[30];
	int codigo;
	float precio;
	int existencia;
}Producto;

typedef struct nodoPr {
	Producto  p;
	struct nodoPr *siguiente;
}Nodo;
//1.-Vaciar memoria
void vaciar(){
	fflush(stdin);
	fflush(stdout);
}
//2.-Crear una lista
Nodo *crearlista(){
	Nodo *cabeza=NULL;
	return cabeza;
}
//3.-Comprobar si un valor es int
int comprobar_Codigo(Nodo *tempC,Nodo **cabeza){
	Nodo *nodo = *cabeza;
		int a,bandera=0;
		if(scanf("%i", &a) != 1){
			return 0;
		}
		else{
			while((nodo!=NULL)&&(nodo->p.codigo == a)){
				if(nodo->p.codigo==a){
					printf("Ese codigo ya existe\n");
					bandera = 1;
				}
				nodo=nodo->siguiente;
			}
			if (bandera==1){
				vaciar();
				return 0;
			}
			else{
				tempC->p.codigo=a;
				vaciar();
				return 1;
			}
		}
}
//4.-Comprobar si un valor es int
int comprobar_Existencia(Nodo *tempC){
	int d;
	if(scanf("%i", &d) != 1){
		return 0;
	}
	else{
		tempC->p.existencia=d;
		return 1;
	}
}
//5.-Comprobar si un valor es int
int comprobar_float(Nodo *tempC){
	float b;
	if(scanf("%f", &b) != 1)
		return 0;
	else{
		tempC->p.precio=b;
		return 1;
	}
}
	
//6.-Crear un Nodo
Nodo *crearNodo(Nodo **cabeza){
	Nodo *temp;
	int comprobar=0;
	temp=(struct nodoPr *) malloc(sizeof(struct nodoPr));
	printf("Proporciona el nombre del producto: \n");
	gets(temp->p.nombre);
	vaciar();
	printf("Proporciona el codigo del producto: \n");
	comprobar=comprobar_Codigo(temp,cabeza);
	vaciar();
	while(comprobar==0){
		printf("Digite nuevamente el codigo: \n");
		comprobar=comprobar_Codigo(temp,cabeza);
		vaciar();
	}
	vaciar();
	//Producto
	printf("Proporciona el precio del producto: \n");
	comprobar=comprobar_float(temp);
	vaciar();
	while(comprobar==0){
		printf("Digite nuevamente el precio: \n");
		comprobar=comprobar_float(temp);
		vaciar();
	}
	vaciar();
	//Existencia
	printf("Proporciona la existencia: \n");
	comprobar=comprobar_Existencia(temp);
	vaciar();
	while(comprobar==0){
		printf("Digite nuevamente la existencia: \n");
		comprobar=comprobar_Existencia(temp);
		vaciar();
	}
	vaciar();
	temp->siguiente=NULL;
	return temp;
}
//7.-Insertar al final de la lista
void insertarFinal(Nodo **cabeza)
	
{   
	Nodo *ultimo;
	ultimo = *cabeza;
	if(ultimo==NULL){
		*cabeza = crearNodo(cabeza);
	}
	else{
		while(ultimo->siguiente!= NULL){
			ultimo=ultimo->siguiente;
		}
		ultimo->siguiente=crearNodo(cabeza);
	}
}
//8.-Borra un nodo de la lista
void eliminar_Nodo(int codigoB, Nodo **cabeza){
	Nodo *actual=*cabeza;
	Nodo *anterior=NULL;
	while((actual!=NULL)&&(actual->p.codigo != codigoB)){
		anterior=actual;
		actual=actual->siguiente;
	}
	if(actual==NULL){//No se encontro el nodo o esta vacia la lista
		if(*cabeza==NULL)printf("La lista esta vacia\n");
		else printf("No se encontro el elemento en la lista\n");
	}
	else{
		if(*cabeza==actual){//Borraremos el primer elemento
			*cabeza=actual->siguiente;
		}
		else {
			anterior->siguiente=actual->siguiente;
			free(actual);
			printf("Elemento borrado\n");
		}
	}
		
	}	
//9.-Modificar un nodo de la lista
void modificar_Nodo(int codigoB, Nodo **cabeza){
		Nodo *actual=*cabeza;
		Nodo *anterior;
		while((actual!=NULL)&&(actual->p.codigo != codigoB)){
			anterior=actual;
			actual=actual->siguiente;
		}
		if(actual==NULL){//No se encontro el nodo o esta vacia la lista
			if(*cabeza==NULL)printf("La lista esta vacia\n");
			else printf("No se encontro el elemento en la lista\n");
		}
		else{
			if(*cabeza==actual){//Borraremos el primer elemento
				*cabeza = crearNodo(cabeza);
			}
			else {
				anterior->siguiente=crearNodo(cabeza);
				printf("Producto modificado correctamente \n");
			}
		}
}	

//10.-Eliminar lista	
void eliminarLista(Nodo **cabeza){
	Nodo *primero;//Eliminaremos el nodo al inicio de la lista
	while(*cabeza != NULL){
		primero = *cabeza;
		*cabeza = primero->siguiente;
		free(primero);
	}
	printf("Lista eliminada\n");
	
}
//11.-Guardar en un archivo
void guardarT(char nombreF[],Nodo *cabeza){
	Nodo *aux=cabeza;
	FILE *archivo;
	archivo = fopen(nombreF,"w+");
	if(archivo!=NULL){
		while (aux!=NULL){
			fprintf(archivo,"%d %s %.2f %d\n",aux->p.codigo,aux->p.nombre,aux->p.precio,aux->p.existencia);
			aux=aux->siguiente;
		}
		}
	fclose(archivo);
}


//12.-Mostrar la lista 
void mostrarLista(Nodo *cabeza){
	if (cabeza==NULL){
		printf("No hay elementos en la lista\n");
	}
	else{
		Nodo *aux;
		printf("Los elementos de la lista son:\n");
		for(aux=cabeza; aux!=NULL ;aux=aux->siguiente){
			printf("Codigo:%d Producto:%s Precio:%.2f Existencia:%d \n",aux->p.codigo,aux->p.nombre, aux->p.precio, aux->p.existencia);
		}
	}
}
//---Funciones que retornan valores para el menú---
//13.-Pedir codigo
int pedir_codigo(){
	int a;
	scanf("%d",&a);
	return a;
}
	
//14.-Fecha
char *cadena_Fecha(){
	char *output=(char*)malloc(15);
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	strftime(output,10,"%d-%m-%y",tlocal);
	return output;
}
//15.-Regresa un valor entero para la opcion
int opcion(int o,char *temp){
		o=atoi(temp);
		return o;
		
}
//------
//16.-Mostrar lo que tienen un archivo
	void leerT(char nombreFile[]){
	FILE *archivo;
	char nombre[30];
	int codigo;
	float precio;
	int existencia;
	puts("el contenido del archivo es");
	archivo = fopen(nombreFile,"r");
	if (archivo!=NULL)
	{
	while( fscanf(archivo,"%d\n%s\n%f\n%d\n",&codigo,nombre,&precio,&existencia)!=-1 )
	{
		printf("Codigo:%d\nProducto:%s\nPrecio:%.2f\nExistencia:%d\n",codigo,nombre,precio,existencia);
	}
		fclose(archivo);
	
	}
}
//17.-Menu
void menu(){
		printf("------\tMenú\t------\n");
		printf("1.- Dar de alta productos \n");
		printf("2.- Mostrar lista \n");
		printf("3.- Borrar un elemento de la lista \n");
		printf("4.- Modificar un elemento de la lista\n");
		printf("5.- Gurdar el reporte\n");
		printf("6.- Borrar toda la lista\n");
		printf("7.- Mostrar lo que tiene un documento\n");
		printf("8.- Venta de producto\n");
		printf("9.- Salir\n");
}
//18.-Encabezado Nice
void encabezadoUWU(){
		printf("\n===========================================================================\n");
		printf("\t\t\t      PROYECTO FINAL\t\t\t\n");
		printf("\t\t\t   Abarroterias Don Diws\t\t\t\n");
		printf("\t\t\t    Fundada desde 2021\t\t\t\n");
		printf("\t\t     Copyright 2021 | Equipo quesadilla\t\t\t\n");
		printf("===========================================================================\n");
}
//19.-Total a pagar
float Total_pagar(int codigoB, Nodo **cabeza){
			Nodo *actual=*cabeza;
			Nodo *anterior;
			int numProduct,total;
			while((actual!=NULL)&&(actual->p.codigo != codigoB)){
				anterior=actual;
				actual=actual->siguiente;
			}
			if(actual==NULL){//No se encontro el nodo o esta vacia la lista
				if(*cabeza==NULL)printf("La lista esta vacia\n");
				else printf("No se encontro el elemento en la lista\n");
			}
			else{
				if(*cabeza==actual){//Modificamos el primer nodo
					printf("Cuanto productos va a vender:\n");
					scanf("%d",&numProduct);
					total=(actual->p.precio)*numProduct;
					actual->p.existencia=actual->p.existencia-numProduct;
				}
				else {
					printf("Cuanto productos va a vender(2):\n");
					scanf("%d",&numProduct);
					total=(anterior->siguiente->p.precio)*numProduct;
					anterior->siguiente->p.existencia=anterior->siguiente->p.existencia-numProduct;
				}
			}
	return total;
}	

//20.-Punto de venta
void punto_venta(Nodo *cabeza){
	int i,o;
	float totalP=0,totalT=0;
	do{
	if(cabeza==NULL){
		break;
	}
	mostrarLista(cabeza);
	printf("Escoge el codigo de un producto:\n");
	scanf("%d",&i);
	totalP=Total_pagar(i,&cabeza);
	totalT=totalT+totalP;
	vaciar();
	printf("¿Va a vender otro producto?(Sí:1/No:0)\n");
	scanf("%d",&o);
	}while(o!=0);
	if(totalT==0){
		printf("La lista esta vacia\n");
	}
	else{
		printf("El total a pagar es: %f\n",totalT);
		vaciar();
	}
}
//Funcion principal 
		int main(){
			encabezadoUWU();
			char *output;
			output=cadena_Fecha();
			int op=0;
			char temp[5];
			Nodo *ap = crearlista();
			int borrarP, modificarP;
			do{
			menu();
			fgets(temp,5,stdin);
			op=opcion(op,temp);
			switch(op){
				case 1: 
					insertarFinal(&ap);
					break;
				case 2:
					mostrarLista(ap);
					break;	
				case 3:
					printf("Digite el codigo del producto que quiere eliminar:\n");
					borrarP = pedir_codigo();
					eliminar_Nodo(borrarP,&ap);
					break;
				case 4:
					printf("Digite el codigo del producto que quiere modificar:\n");
					modificarP=pedir_codigo();
					modificar_Nodo(modificarP,&ap);
					break;
				case 5:
					guardarT(output,ap);
					break;
				case 6:
					eliminarLista(&ap);
					break;
				case 7: 
					leerT("16-11-21");
					break;
				case 8:
					punto_venta(ap);
					break;
				case 9:
					printf("Saliendo...");
					break;
				default:
					printf("Escoga una opción dentro del menú");
					break;
				}
			}while(op!=9);
			return 0;
		}
