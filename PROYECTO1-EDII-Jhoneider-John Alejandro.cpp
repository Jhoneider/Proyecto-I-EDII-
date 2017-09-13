/*
*	Proyecto de: Software de Facturacion con apuntadores
*	Fecha de elaboracion: 4 de Septiembre hasta 13 de septiembre del 2017 
*	Presentado por: Jhoneider Hincapie Aguirre -  John Alejandro Giraldo M 
*/

#include <iostream>
#include <cstdlib>
#include <stdio.h>  
#include <windows.h> 
#include <conio.h>
#define F_Arriba 72
#define F_Abajo 80
#define ENTER 13

using namespace std;

//Contadores de registros en las estructuras / hacen las veces de ID
int Cont_cliente = 0;
int Cont_producto = 0;
int Cont_facturas = 0;

//Estructuras del sistema
struct clientes{
	int id;
	char cedula[15];
	char nombre[20];
	char direccion[20];
	char telefono[20];
}cliente[1000],*Pcliente=&cliente[0];

struct productos{
	int id;
	char nombre[20];
	int valor;
}producto[1000],*Pproducto=&producto[0];

//Esta estructura contendra los productos de cada factura , hay 1000 posibles facturas, por lo tanto es una matriz de 1000(facturas) x 50 articulos
struct Lista_productos_factura{
	char nombre[20];
	int cantidad;
	int subtotal;
}Lista_Productos[50][1000],*Plista_Produc_Fact=&Lista_Productos[0][0];

struct facturas {
	int id;
	int id_cliente;
	char nombre_cliente[20];
	char cedula_cliente[15];
	int Cantidad_productos;
	int total;
	bool estado;
}factura[1000],*Pfactura=&factura[0];

//Prototipos de funciones del sistema
void gotoxy(int,int);
void MostrarMenuPrincipal();
void MostrarGestionClientes();
void Nuevo_Cliente();
void ListarClientes();
void ListarTodosLosClientes();
void MostrarClientes();
void EditarCliente();
void MostrarGestionProductos();
void Nuevo_Producto();
void ListarProductos();
void MostrarProductos();
void EditarProductos();
void MostrarGestionFacturas();
void Nueva_Factura();
void MostrarFacturas();
void ListarFacturas();
void EditarFacturas();
void MostrarListaComprimidaFacturas();
void ListaComprimidaFacturas();
void ListaProductosVendidos();
void MostrarProductoCantidadVendida();
void ListaFacturasPorCliente();
void ListaFacturasPagadasYSinPagar();
int Buscar_Cliente_Para_Factura(char[]);

int DezplegarMenu(char[],const char *[],int);

 //funcion principal
int main(int argc, char *argv[]) {
	
	MostrarMenuPrincipal();
	
	return 0;
}

//Funcion que maqueta en pantalla el menu principal o inicial
void MostrarMenuPrincipal(){
	char titulo[] = "MENU PRINCIPAL - SISTEMA DE FACTURACION";
	const char *opciones[] = {"GESTION DE CLIENTES","GESTION DE PRODUCTOS","GESTION DE FACTURAS","MOSTRAR TODAS LAS FACTURAS","MOSTRAR TODOS LOS CLIENTES","MOSTRAR TODAS LAS FACTURAS GENERADAS POR CLIENTE","MOSTRAR TODOS LOS PRODUCTOS CON LA CANTIDAD VENDIDA DE CADA UNO","LISTAR FACTURAS PAGADAS Y SIN PAGAR","SALIR"};
	const int Nopciones = 9;
	int opcionelegida;
	opcionelegida = DezplegarMenu(titulo,opciones,Nopciones);
	
	switch(opcionelegida){
	case 1:
		MostrarGestionClientes();
		break;
	case 2:
		MostrarGestionProductos();
		break;
	case 3:
		MostrarGestionFacturas();
		break;
	case 4:
		ListarFacturas();
		break;
	case 5:
		ListarTodosLosClientes();
		break;
	case 6:
		ListaFacturasPorCliente();
		break;
	case 7:
		MostrarProductoCantidadVendida();
		break;
	case 8:
		ListaFacturasPagadasYSinPagar();
		break;
	case Nopciones:
		exit(0);
		break;
	}
}

//funcion que maqueta el menu de clientes
void MostrarGestionClientes(){
	char titulo[] = "GESTION DE CLIENTES - SISTEMA DE FACTURACION";
	const char *opciones[] = {"CREAR CLIENTE","LISTAR CLIENTES","EDITAR CLIENTES","ATRAS"};
	const int Nopciones = 4;
	int opcionelegida;
	opcionelegida = DezplegarMenu(titulo,opciones,Nopciones);
	
	switch(opcionelegida){
	case 1:
		Nuevo_Cliente();
		break;
	case 2:
		ListarClientes();
		break;
	case 3:
		EditarCliente();
		break;
	case Nopciones:
		MostrarMenuPrincipal();
		break;
	}
}

//funcion que maqueta el menu de productos
void MostrarGestionProductos(){
	char titulo[] = "GESTION DE PRODUCTOS - SISTEMA DE FACTURACION";
	const char *opciones[] = {"CREAR PRODUCTO","LISTAR PRODUCTOS","EDITAR PRODUCTO","ATRAS"};
	const int Nopciones = 4;
	int opcionelegida;
	opcionelegida = DezplegarMenu(titulo,opciones,Nopciones);
	
	switch(opcionelegida){
	case 1:
		 Nuevo_Producto();
		break;
	case 2:
		ListarProductos();
		break;
	case 3:
		EditarProductos();
		break;
	case Nopciones:
		MostrarMenuPrincipal();
		break;
	}
}

//funcion que maqueta el menu de facturas
void MostrarGestionFacturas(){
	char titulo[] = "GESTION DE FACTURAS - SISTEMA DE FACTURACION";
	const char *opciones[] = {"CREAR FACTURA","LISTAR FACTURAS","EDITAR FACTURA","ATRAS"};
	const int Nopciones = 4;
	int opcionelegida;
	opcionelegida = DezplegarMenu(titulo,opciones,Nopciones);
	
	switch(opcionelegida){
	case 1:
		Nueva_Factura();
		break;
	case 2:
		MostrarListaComprimidaFacturas();
		break;
	case 3:
		EditarFacturas();
		break;
	case Nopciones:
		MostrarMenuPrincipal();
		break;
	}
}

//funcion que permite posicionar en 2 dimensiones sobre la pantalla
//x corresponde al valor horizontal de pantalla (desde 0 a + o - 80
//y corresponde el valor vertical desde 0 hasta n
void gotoxy(int x,int y){  
	HANDLE hcon;  
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
	COORD dwPos;  
	dwPos.X = x;  
	dwPos.Y= y;  
	SetConsoleCursorPosition(hcon,dwPos);  
} 

//Funcion general que despliega un menu determinado por sus partametros
//titulo : texto que se pondra de cabecera debidamente ubicado
//opciones : maqueta las posibles opciones en listadas
//Nopc : numero de opciones servira de referencia a el posicionamiento de el puntero de navegacion ->
int DezplegarMenu(char titulo[],const char *opciones[],int Nopc){
	int Opcionelegida = 1;
	int teclapresionada;
	bool navegar = true;
	
	do{
		int x = 15,y = 2;
		
		system("cls");
		gotoxy(x,y);
		printf("%s",titulo);
		
		gotoxy(1,4 + Opcionelegida);printf("->");
		
		x=5;y=5;
		gotoxy(x,y);
		for(int i = 0; i < Nopc;i++){
			y+=1;
			printf("%d.\t %s",i +1,opciones[i]);
			gotoxy(x,y);
		}
		
		x = 0,y+=2;
		gotoxy(x,y);
		printf("Utilice flecha Arriba/flecha abajo para navegar en el menu, presione ENTER para elegir");
		
		do{
			teclapresionada = getch(); //espera que sea presionado arriba - abajo - enter
		} while(teclapresionada != F_Arriba && teclapresionada != F_Abajo && teclapresionada != ENTER);
		
		switch(teclapresionada){
		case F_Arriba:
			Opcionelegida--;
			if(Opcionelegida<=0)Opcionelegida=Nopc;
			break;
		case F_Abajo:
			Opcionelegida++;
			if(Opcionelegida>Nopc)Opcionelegida=1;
			break;
		case ENTER:
				navegar=false;
			break;
		}
	}
	while(navegar);
	
	return Opcionelegida;
}

//Funcion que permite ingresar un nuevo cliente
void Nuevo_Cliente(){
	int x = 15,y = 2;
	system("cls");
	gotoxy(x,y);
	printf("NUEVO CLIENTE");
	x = 0,y = 4;
	gotoxy(x,y);

	(Pcliente + Cont_cliente)->id = Cont_cliente;
	fflush(stdin);
	printf("Ingrese la cedula del cliente : ");
	fgets((Pcliente + Cont_cliente)->cedula,15,stdin);
	fflush(stdin);
	printf("\nIngrese el nombre completo del cliente : ");
	fgets((Pcliente + Cont_cliente)->nombre,20,stdin);
	fflush(stdin);
	printf("\nIngrese la direccion del cliente : ");
	fgets((Pcliente + Cont_cliente)->direccion,20,stdin);
	fflush(stdin);
	printf("\nIngrese el telefono del cliente : ");
	fgets((Pcliente + Cont_cliente)->telefono,20,stdin);
	fflush(stdin);
	Cont_cliente++;
	
	printf("\n\n *** El cliente se ha creado satisfactoriamente *** \n");
	printf("Presione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarGestionClientes();
}

//funcion que permite enlistar clientes
void ListarClientes(){
	MostrarClientes();
	
	printf("\n\nPresione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarGestionClientes();
}

//Funcion de enlistado de clientes en el menu principal
void ListarTodosLosClientes(){
	MostrarClientes();
	
	printf("\n\nPresione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarMenuPrincipal();
}

//maqueta el listado de clientes en pantalla
void MostrarClientes(){
	int x = 15,y = 2;
	system("cls");
	gotoxy(x,y);
	printf("LISTADO DE CLIENTES");
	x = 1,y = 4;
	gotoxy(x,y);printf("ID");x+=4;
	gotoxy(x,y);printf("CEDULA");x+=15;
	gotoxy(x,y);printf("NOMBRE");x+=20;
	gotoxy(x,y);printf("DIRECCION");x+=20;
	gotoxy(x,y);printf("TELEFONO");
	x = 1,y++;
	gotoxy(x,y);printf("==============================================================================");

	for(int i = 0; i < Cont_cliente; i++){
		x = 1,y++;
		gotoxy(x,y);printf("%d",(Pcliente + i)->id);x+=4;
		gotoxy(x,y);printf("%s",(Pcliente + i)->cedula);x+=15;
		gotoxy(x,y);printf("%s",(Pcliente + i)->nombre);x+=20;
		gotoxy(x,y);printf("%s",(Pcliente + i)->direccion);x+=20;
		gotoxy(x,y);printf("%s",(Pcliente + i)->telefono);
	}
	
	if(Cont_cliente==0){
		x = 1,y++;gotoxy(x,y);
		printf("* No hay datos *");
	}
	y++;
	gotoxy(0,y);
}

//permite por medio del ID escojer un registro de un cliente para editarlo
void EditarCliente(){
	MostrarClientes(); //enlista para que el usuario tenga una referencia
	int IdAEditar;
	printf("\n\t EDITAR CLIENTE \n");
	fflush(stdin);
	printf("digite el ID del cliente que desea editar : ");
	scanf("%d",&IdAEditar);
	
	if(IdAEditar >= Cont_cliente || IdAEditar < 0){
		printf("El ID ingresado no es valido\n");
	}
	else {
		printf("CEDULA ACTUAL : %s Ingrese el nuevo valor de cedula : ",(Pcliente + IdAEditar)->cedula);
		fflush(stdin);
		fgets((Pcliente + IdAEditar)->cedula,15,stdin);
		printf("NOMBRE ACTUAL : %s Ingrese el nuevo valor del nombre : ",(Pcliente + IdAEditar)->nombre);
		fflush(stdin);
		fgets((Pcliente + IdAEditar)->nombre,20,stdin);
		printf("DIRECCION ACTUAL : %s Ingrese el nuevo valor de la direccion : ",(Pcliente + IdAEditar)->direccion);
		fflush(stdin);
		fgets((Pcliente + IdAEditar)->direccion,20,stdin);
		printf("TELEFONO ACTUAL : %s Ingrese el nuevo valor de telefono : ",(Pcliente + IdAEditar)->telefono);
		fflush(stdin);
		fgets((Pcliente + IdAEditar)->telefono,20,stdin);
		
		printf("\n\n *** El cliente se ha modificado satisfactoriamente *** \n");
	}
	
	
	printf("Presione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarGestionClientes();
}

//permite ingresar un nuevo producto , pidienddo los datos de la estructura productos
void Nuevo_Producto(){
	int x = 15,y = 2;
	system("cls");
	gotoxy(x,y);
	printf("NUEVO PRODUCTO");
	x = 0,y = 4;
	gotoxy(x,y);
	
	(Pproducto + Cont_producto)->id = Cont_producto;
	fflush(stdin);
	printf("Ingrese el nombre del producto : ");
	fgets((Pproducto + Cont_producto)->nombre,20,stdin);
	fflush(stdin);
	printf("Ingrese el precio unitario del producto : ");
	scanf("%d",&(Pproducto + Cont_producto)->valor);
	//fgets((Pproducto + Cont_producto)->valor,20,stdin);
	fflush(stdin);
	Cont_producto++;
	
	printf("\n\n *** El producto se ha creado satisfactoriamente *** \n");
	printf("Presione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarGestionProductos();
}

//lista los productos creados
void ListarProductos(){
	MostrarProductos();//maqueta lista en pantalla
	
	printf("\n\nPresione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarGestionProductos();
}
//dispone la pantalla para maquetar el listado de productos en pantalla
void MostrarProductos(){
	int x = 15,y = 2;
	system("cls");
	gotoxy(x,y);
	printf("LISTADO DE PRODUCTOS");
	x = 2,y = 4;
	gotoxy(x,y);printf("ID");x+=5;
	gotoxy(x,y);printf("NOMBRE");x+=20;
	gotoxy(x,y);printf("VALOR UNITARIO");x+=20;

	x = 1,y++;
	gotoxy(x,y);printf("=============================================");
	
	for(int i = 0; i < Cont_producto; i++){
		x = 2,y++;
		gotoxy(x,y);printf("%d",(Pproducto + i)->id);x+=5;
		gotoxy(x,y);printf("%s",(Pproducto + i)->nombre);x+=20;
		gotoxy(x,y);printf("%d",(Pproducto + i)->valor);x+=20;
	}
	
	if(Cont_producto==0){
		x = 1,y++;gotoxy(x,y);
		printf("* No hay datos *");
	}
	y++;
	gotoxy(0,y);
}
//Permite escojer segun el ID del producto para editar su registro
void EditarProductos(){
	MostrarProductos();
	int IdAEditar;
	printf("\n\t EDITAR PRODUCTO \n");
	fflush(stdin);
	printf("digite el ID del producto que desea editar : ");
	scanf("%d",&IdAEditar);
	
	if(IdAEditar >= Cont_producto || IdAEditar < 0){
		printf("El ID ingresado no es valido\n");
	}
	else {
		printf("NOMBRE ACTUAL : %s Ingrese el nuevo valor del nombre : ",(Pproducto + IdAEditar)->nombre);
		fflush(stdin);
		fgets((Pproducto + IdAEditar)->nombre,20,stdin);
		printf("VALOR ACTUAL : %d Ingrese el nuevo valor del nombre : ",(Pproducto + IdAEditar)->valor);
		fflush(stdin);
		scanf("%d",&(Pproducto + IdAEditar)->valor);
		
		printf("\n\n *** El producto se ha modificado satisfactoriamente *** \n");
	}
	
	
	printf("Presione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarGestionProductos();
}
//permite ingresar una factura y los datos necesarios para la estructura
void Nueva_Factura(){
	MostrarProductos();//lista productos para que el usuario tenga referencia a la mano
	
	printf("\n\nNUEVA FACTURA");
	

	//BUSCAR CLIENTE
	char cedulacliente[15];
	char intentarbuscar = 'n';
	bool clienteEncontrado = false;
	int Iddelcliente;
	
	do{
				fflush(stdin);
				printf("\nIngrese la cedula del cliente : ");
				fgets(&cedulacliente[0],15,stdin);
				
				Iddelcliente = Buscar_Cliente_Para_Factura(cedulacliente);
				
				if(Iddelcliente < 0){
					printf("\nno se ha podido encontrar el cliente. Desar volver a intentarlo ? (s. Si - n. No) : ");
					scanf("%c",&intentarbuscar);
					fflush(stdin);
					clienteEncontrado = false;
				}else {
					intentarbuscar = 'n';
					printf("\nNOMBRE DEL CLIENTE : %sID CLIENTE : %d\tCEDULA : %s",(Pcliente + Iddelcliente)->nombre,Iddelcliente,(Pcliente + Iddelcliente)->cedula);
					clienteEncontrado = true;
				}
	} while(intentarbuscar=='s');
	
	if(clienteEncontrado){
		(Pfactura + Cont_facturas)->id = Cont_facturas;
		(Pfactura + Cont_facturas)->id_cliente = Iddelcliente;
		strcpy((Pfactura + Cont_facturas)->cedula_cliente,(Pcliente + Iddelcliente)->cedula);
		strcpy((Pfactura + Cont_facturas)->nombre_cliente,(Pcliente + Iddelcliente)->nombre);
		fflush(stdin);
		int idproductoingresado;
		int ProductosIngresados = 0;
		int TotalValorFactura = 0;
		int cantidaddelproducto=0;
		char masproductos='s';
		printf("\n");
		do{
			printf("\nIngrese el ID del producto para agregar al pedido (ver listado arriba) : ");
			scanf("%d",&idproductoingresado);
			fflush(stdin);
			if(idproductoingresado < 0 || idproductoingresado >= Cont_producto){
				printf("\nEl id del producto no es valido, por favor rectifique");
			}
			else{
				fflush(stdin);
				printf("\nPRODUCTO: %s\tVALOR UNITARIO : %d\t CANTIDAD : ",(Pproducto + idproductoingresado)->nombre,(Pproducto + idproductoingresado)->valor);
				scanf("%d",&cantidaddelproducto);
				fflush(stdin);
				strcpy((Plista_Produc_Fact + ProductosIngresados + (Cont_facturas * 50))->nombre,(Pproducto + idproductoingresado)->nombre);
				(Plista_Produc_Fact + ProductosIngresados + (Cont_facturas * 50))->cantidad = cantidaddelproducto;
				(Plista_Produc_Fact + ProductosIngresados + (Cont_facturas * 50))->subtotal = cantidaddelproducto * (Pproducto + idproductoingresado)->valor;
				TotalValorFactura += (Plista_Produc_Fact + ProductosIngresados + (Cont_facturas * 50))->subtotal;
				fflush(stdin);
				ProductosIngresados++;
				printf("\nDesea ingresar otro producto ? (s. Si - n. No) : ");
				scanf("%c",&masproductos);
			}
		} while(masproductos=='s' || masproductos=='S');
		
		(Pfactura + Cont_facturas)->Cantidad_productos = ProductosIngresados;
		(Pfactura + Cont_facturas)->total = TotalValorFactura;
		printf("\nPRECIO TOTAL : %d",TotalValorFactura);
		int pagoodebe = 0;
		fflush(stdin);
		printf("\nEl cliente quedo debiendo o pago la factura ? (0. PAGO - 1. DEBE) : ");
		scanf("%d",&pagoodebe);
		
		if(pagoodebe==1)
		{
			(Pfactura + Cont_facturas)->estado = true;
		}
		else{
			(Pfactura + Cont_facturas)->estado = false;
		}
		
		Cont_facturas++;
		printf("\n\n *** La factura se ha creado satisfactoriamente *** \n");
	}

	printf("Presione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarGestionFacturas();
}

//subfuncion que busca datos del cliente ya existente para asignarlos a su factura
int Buscar_Cliente_Para_Factura(char cedula[]){
	int IdEncontrado;
	for(int i = 0; i < Cont_cliente;i++){
		int comp = strcmp(cedula,(Pcliente + i)->cedula);
		if(comp==0){
			IdEncontrado = (Pcliente + i)->id;
			return IdEncontrado;
		}
	}
	
	return -1;
}

//lista generalizada de facturas sin detalle de compra
void ListaComprimidaFacturas(){
	int x = 15,y = 2;
	system("cls");
	gotoxy(x,y);
	printf("LISTADO GENERAL DE FACTURAS");
	x = 0,y = 4;gotoxy(x,y);
	printf("ID FACT.");x+=9;
	gotoxy(x,y);printf("CLIENTE");x+=20;
	gotoxy(x,y);printf("CEDULA");x+=15;
	gotoxy(x,y);printf("# ARTICULOS");x+=15;
	gotoxy(x,y);printf("TOTAL");x+=11;
	gotoxy(x,y);printf("ESTADO");
	y++;x=0;gotoxy(x,y);
	printf("===============================================================================");y++;gotoxy(x,y);
	
	for(int i = 0; i < Cont_facturas;i++){
		printf("%d",(Pfactura + i)->id);x+=10;
		gotoxy(x,y);printf("%s",(Pfactura + i)->nombre_cliente);x+=20;
		gotoxy(x,y);printf("%s",(Pfactura + i)->cedula_cliente);x+=15;
		gotoxy(x,y);printf("%d",(Pfactura + i)->Cantidad_productos);x+=15;
		gotoxy(x,y);printf("%d",(Pfactura + i)->total);x+=11;
		gotoxy(x,y);if((Pfactura + i)->estado){ printf("**DEBE**"); } else { printf("**PAGO**"); } ;
		y++;x=0;gotoxy(x,y);
	}

	
}
//dispone pantalla para listar facturas generalizadas
void MostrarListaComprimidaFacturas(){
	ListaComprimidaFacturas();
	
	printf("\n\nPresione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarGestionFacturas();
}
//dispone pantalla para listar facturas Completas
void ListarFacturas(){
	MostrarFacturas();
	
	printf("\n\nPresione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarMenuPrincipal();
}
//muestras facturas completas con encabezado y detalle de compra
void MostrarFacturas(){
	int x = 15,y = 2;
	system("cls");
	gotoxy(x,y);
	printf("LISTADO DE FACTURAS");
	x = 0,y = 4;gotoxy(x,y);
	
	for(int i = 0; i < Cont_facturas;i++){
		int idfact = (Pfactura + i)->id;
		fflush(stdin);
		printf("----------------------------------------------------------\n");
		printf("ID FACTURA : %d \t ID CLIENTE : %d",(Pfactura + i)->id,(Pfactura + i)->id_cliente);
		fflush(stdin);
		printf("\nNOMBRE : %s",(Pfactura + i)->nombre_cliente);
		printf("CEDULA : %s",(Pfactura + i)->cedula_cliente);
		y+=4;if(i>0)y++;
		gotoxy(x,y);printf("PRODUCTO");x+=20;
		gotoxy(x,y);printf("CANTIDAD");x+=10;
		gotoxy(x,y);printf("SUBTTOTAL");y++;x=0;
		gotoxy(x,y);printf("===================================================");y++;
		
		int cantprod = (Pfactura + i)->Cantidad_productos; 
		for(int p = 0;p < cantprod;p++){
			gotoxy(x,y);printf("%s",(Plista_Produc_Fact + p + (idfact * 50))->nombre);x+=20;
			gotoxy(x,y);printf("%d",(Plista_Produc_Fact + p + (idfact * 50))->cantidad);x+=10;
			gotoxy(x,y);printf("%d",(Plista_Produc_Fact + p + (idfact * 50))->subtotal);x=0;y++;
		}
		gotoxy(x,y);printf("**** TOTAL **** : ");x+=30;
		gotoxy(x,y);printf("%d",(Pfactura + i)->total);y++;x=0;gotoxy(x,y);
		printf("===================================================");y++;gotoxy(x,y);
		if((Pfactura + i)->estado == 1)printf("ESTADO : *DEBE*");else printf("ESTADO : *PAGO*");
		printf("\n----------------------------------------------------------");
		printf("\n\n");
		y+=2;
		
	}
}
//funcion con la cual seleccionamos la ID de la factura que queramos editar 
//al escojer el ID no pregunta si quieremos editar el cliente s - n
//si escojemos editarlo , nos pedira el nuevo id del cliente - si no, seguira
//nos dice si queremos editar el detalle de la compra, con opciones de - 1 agregar producto a la compra - 2 nueva ListaComprimidaFacturas
//1 agregar nuevo : agrega nuevos productos a partir del ID de la ultima
//2 nueva lista : agrega nuevos productos a partir del id 0;
void EditarFacturas(){
	ListaComprimidaFacturas();
	int IdAEditar;
	printf("\n\t EDITAR FACTURA \n");
	fflush(stdin);
	printf("digite el ID de la factura que desea editar : ");
	scanf("%d",&IdAEditar);
	
	if(IdAEditar >= Cont_facturas || IdAEditar < 0){
		printf("El ID ingresado no es valido\n");
	}
	else {
		
				int idfact = IdAEditar;
				fflush(stdin);
				printf("\n*VA A EDITAR ESTA FACTURA*\n");
				printf("\n----------------------------------------------------------\n");
				printf("ID FACTURA : %d \t ID CLIENTE : %d",(Pfactura + IdAEditar)->id,(Pfactura + IdAEditar)->id_cliente);
				fflush(stdin);
				printf("\nNOMBRE : %s",(Pfactura + IdAEditar)->nombre_cliente);
				printf("CEDULA : %s",(Pfactura + IdAEditar)->cedula_cliente);
				printf("\n");
				printf("PRODUCTO");
				printf(" - CANTIDAD  - SUBTTOTAL"); //especifica que los datos de abajo son estos
				printf("\n===================================================");
				
				int cantprod = (Pfactura + IdAEditar)->Cantidad_productos; 
				for(int p = 0;p < cantprod;p++){
					printf("\n");
					printf("%s",(Plista_Produc_Fact + p + (idfact * 50))->nombre);
					printf("\t\t%d",(Plista_Produc_Fact + p + (idfact * 50))->cantidad); //tabula de manera que se comprenda visualmente
					printf("\t%d",(Plista_Produc_Fact + p + (idfact * 50))->subtotal);
				}
				printf("\n**** TOTAL **** : ");
				printf("\t%d",(Pfactura + IdAEditar)->total);
				printf("\n===================================================\n");
				
				if((Pfactura + IdAEditar)->estado == 1)printf("ESTADO : *DEBE*");else printf("ESTADO : *PAGO*");
				printf("\n----------------------------------------------------------");
				printf("\n");
				
				//comienza a Editar
				char quiereeditar ='n';
				char cedulacliente[15];
				char intentarbuscar = 'n';
				bool clienteEncontrado = false;
				int Iddelcliente=(Pfactura + IdAEditar)->id_cliente;
				
				printf("\n Desea editar el cliente de esta factura ? (s. Si - n. No) : ");
				scanf("%c",&quiereeditar);
				if(quiereeditar=='s' || quiereeditar =='S'){
				
					do{
						fflush(stdin);
						printf("\nIngrese la cedula del cliente : ");
						fgets(&cedulacliente[0],15,stdin);
						
						Iddelcliente = Buscar_Cliente_Para_Factura(cedulacliente);
						
						if(Iddelcliente < 0){
							printf("\nno se ha podido encontrar el cliente. Desar volver a intentarlo ? (s. Si - n. No) : ");
							scanf("%c",&intentarbuscar);
							fflush(stdin);
							clienteEncontrado = false;
						}else {
							intentarbuscar = 'n';
							printf("\nNOMBRE DEL CLIENTE : %sID CLIENTE : %d\tCEDULA : %s",(Pcliente + Iddelcliente)->nombre,Iddelcliente,(Pcliente + Iddelcliente)->cedula);
							clienteEncontrado = true;
						}
					} while(intentarbuscar=='s');
					
				}
				
				if(clienteEncontrado)
				{
					//editar el cliente de la factura
					(Pfactura + IdAEditar)->id_cliente = Iddelcliente;
					strcpy((Pfactura + IdAEditar)->nombre_cliente,(Pcliente + Iddelcliente)->nombre);
					strcpy((Pfactura + IdAEditar)->cedula_cliente,(Pcliente + Iddelcliente)->cedula);
				} 
				
				fflush(stdin);
				printf("\n Desea editar los articulos de esta factura ? (s. Si - n. No) : ");
				scanf("%c",&quiereeditar);
				if(quiereeditar=='s' || quiereeditar =='S'){
					//agregar articulos - nueva lista de articulos - 
					int OpciondeEdicion=1;
					printf("\n Que desea hacer ? (1. Agregar mas articulos - 2. Nueva lista de aticulos) : ");
					scanf("%d",&OpciondeEdicion);
					
					int poscisionproducto,idproductoingresado,cantidaddelproducto,TotalValorFactura; //retoma la pocision de producto para agregar mas
					char masproductos;
					
					if(OpciondeEdicion==1){ //agregar productos a la lista
						
						poscisionproducto = (Pfactura + IdAEditar)->Cantidad_productos; //retoma la pocision de producto para agregar mas
						cantidaddelproducto=0;
						masproductos='s';
						TotalValorFactura = (Pfactura + IdAEditar)->total; //retoma desde el total actual
						
						printf("\n");
						do{
							printf("\nIngrese el ID del producto para agregar al pedido : ");
							scanf("%d",&idproductoingresado);
							fflush(stdin);
							if(idproductoingresado < 0 || idproductoingresado >= Cont_producto){
								printf("\nEl id del producto no es valido, por favor rectifique");
							}
							else{
								fflush(stdin);
								printf("\nPRODUCTO: %s\tVALOR UNITARIO : %d\t CANTIDAD : ",(Pproducto + idproductoingresado)->nombre,(Pproducto + idproductoingresado)->valor);
								scanf("%d",&cantidaddelproducto);
								fflush(stdin);
								strcpy((Plista_Produc_Fact + poscisionproducto + (IdAEditar * 50))->nombre,(Pproducto + idproductoingresado)->nombre);
								(Plista_Produc_Fact + poscisionproducto + (IdAEditar * 50))->cantidad = cantidaddelproducto;
								(Plista_Produc_Fact + poscisionproducto + (IdAEditar * 50))->subtotal = cantidaddelproducto * (Pproducto + idproductoingresado)->valor;
								TotalValorFactura += (Plista_Produc_Fact + poscisionproducto + (IdAEditar * 50))->subtotal;
								fflush(stdin);
								poscisionproducto++;
								printf("\nDesea ingresar otro producto ? (s. Si - n. No) : ");
								scanf("%c",&masproductos);
							}
						} while(masproductos=='s' || masproductos=='S');
					}
					else if(OpciondeEdicion==2){
						
						poscisionproducto = 0; //retoma la pocision inicial
						cantidaddelproducto=0;
						masproductos='s';
						TotalValorFactura = 0; //el total se pone en cero
						
						printf("\n");
						do{
							printf("\nIngrese el ID del producto para agregar al pedido : ");
							scanf("%d",&idproductoingresado);
							fflush(stdin);
							if(idproductoingresado < 0 || idproductoingresado >= Cont_producto){
								printf("\nEl id del producto no es valido, por favor rectifique");
							}
							else{
								fflush(stdin);
								printf("\nPRODUCTO: %s\tVALOR UNITARIO : %d\t CANTIDAD : ",(Pproducto + idproductoingresado)->nombre,(Pproducto + idproductoingresado)->valor);
								scanf("%d",&cantidaddelproducto);
								fflush(stdin);
								strcpy((Plista_Produc_Fact + poscisionproducto + (IdAEditar * 50))->nombre,(Pproducto + idproductoingresado)->nombre);
								(Plista_Produc_Fact + poscisionproducto + (IdAEditar * 50))->cantidad = cantidaddelproducto;
								(Plista_Produc_Fact + poscisionproducto + (IdAEditar * 50))->subtotal = cantidaddelproducto * (Pproducto + idproductoingresado)->valor;
								TotalValorFactura += (Plista_Produc_Fact + poscisionproducto + (IdAEditar * 50))->subtotal;
								fflush(stdin);
								poscisionproducto++;
								printf("\nDesea ingresar otro producto ? (s. Si - n. No) : ");
								scanf("%c",&masproductos);
							}
						} while(masproductos=='s' || masproductos=='S');
					}
					
					(Pfactura + IdAEditar)->Cantidad_productos = poscisionproducto;
					(Pfactura + IdAEditar)->total = TotalValorFactura;
					printf("\nPRECIO TOTAL : %d",TotalValorFactura);
				}
				
				int pagoodebe = 0;
				fflush(stdin);
				printf("\nEl cliente quedo debiendo o pago la factura ? (0. PAGO - 1. DEBE) : ");
				scanf("%d",&pagoodebe);
				
				if(pagoodebe==1)
				{
					(Pfactura + IdAEditar)->estado = true;
				}
				else{
					(Pfactura + IdAEditar)->estado = false;
				}
			
				printf("\n\n *** La factura se ha modificado satisfactoriamente *** \n");
	}
	
	
	printf("Presione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarGestionFacturas();
}

//Funcion que va a la estructura detalle de factura y cuenta la cantidad de productos vendidos en cada venta referenciado por el nombre
//producto : nombre del producto
int BuscarCantidadVendida(char producto[]){
	int Cantidadvendida=0;
	//ir a detalles de factura
	for(int f = 0;f < Cont_facturas; f++){
		int cantarticulos = (Pfactura + f)->Cantidad_productos;
		for(int a = 0; a < cantarticulos;a++){
			int comp = strcmp(producto,(Plista_Produc_Fact + a + (f * 50))->nombre);
			if(comp==0){
				Cantidadvendida+=(Plista_Produc_Fact + a + (f * 50))->cantidad;
			}
		}
	}
	
	return Cantidadvendida;
	
}
//enlista la cantidad de productos y los enlista de acuerdo a los productos registrados
void MostrarProductoCantidadVendida(){
	ListaProductosVendidos();
	
	printf("\n\nPresione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarMenuPrincipal();
}

//maqueta la pantalla para enlistar productos vendidos
void ListaProductosVendidos(){
	int x = 15,y = 2;
	system("cls");
	gotoxy(x,y);
	printf("LISTADO DE PRODUCTOS VENDIDOS");
	x = 2,y = 4;
	gotoxy(x,y);printf("ID");x+=5;
	gotoxy(x,y);printf("NOMBRE");x+=20;
	gotoxy(x,y);printf("VALOR UNITARIO");x+=20;
	gotoxy(x,y);printf("CANT. VENDIDAS");
	
	x = 1,y++;
	gotoxy(x,y);printf("=========================================================");
	
	for(int i = 0; i < Cont_producto; i++){
		x = 2,y++;
		gotoxy(x,y);printf("%d",(Pproducto + i)->id);x+=5;
		gotoxy(x,y);printf("%s",(Pproducto + i)->nombre);x+=20;
		gotoxy(x,y);printf("%d",(Pproducto + i)->valor);x+=20;
		int cantvendida = BuscarCantidadVendida((Pproducto + i)->nombre);
		gotoxy(x,y);printf("%d",cantvendida);
	}
	
	if(Cont_producto==0){
		x = 1,y++;gotoxy(x,y);
		printf("* No hay datos *");
	}
	y++;
	gotoxy(0,y);
}

//segun los registros de clientes que hay en el sistema , hace un escaneo de las facturas existentes y verifica si cada una pertece al cliente
//si pertenece la agrega a su lista (del cliente que se esta evaluando)
void ListaFacturasPorCliente(){
	int x = 15,y = 2;
	system("cls");
	gotoxy(x,y);
	printf("LISTADO DE FACTURAS POR CLIENTE");
	x = 0,y = 4;gotoxy(x,y);
	
	for(int c = 0; c < Cont_cliente;c++){
		printf("--------------------------------------------------------------------");y++;gotoxy(x,y);
		printf("CLIENTE : %s",(Pcliente + c)->nombre);y++;gotoxy(x,y);
		printf("CEDULA : %s",(Pcliente + c)->cedula);y++;gotoxy(x,y);
		printf("*FACTURAS A SU NOMBRE*");y+=2;gotoxy(x,y);
		
		printf("ID FACT.");x+=9;
		gotoxy(x,y);printf("# ARTICULOS");x+=15;
		gotoxy(x,y);printf("TOTAL");x+=11;
		gotoxy(x,y);printf("ESTADO");
		y++;x=0;gotoxy(x,y);
		printf("=============================================");y++;gotoxy(x,y);
		int contfacturas=0;
		for(int i = 0; i < Cont_facturas;i++){
			int comp = strcmp((Pcliente + c)->nombre,(Pfactura + i)->nombre_cliente);
			
			if(comp==0){
				printf("%d",(Pfactura + i)->id);x+=10;
				gotoxy(x,y);printf("%d",(Pfactura + i)->Cantidad_productos);x+=15;
				gotoxy(x,y);printf("%d",(Pfactura + i)->total);x+=11;
				gotoxy(x,y);if((Pfactura + i)->estado){ printf("**DEBE**"); } else { printf("**PAGO**"); } ;
				y++;x=0;gotoxy(x,y);
				contfacturas++;
			}
		}
		
		if(contfacturas==0){
			printf("*NO TIENE FACTURAS*");y++;gotoxy(x,y);
		}
		
		printf("--------------------------------------------------------------------");y+=2;gotoxy(x,y);
	}
	
	printf("\n\nPresione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarMenuPrincipal();
}
//Realiza un escaneo con los registros de facturas en el sistema y verificar el estado de cada una, discriminandolas en 2 listas
void ListaFacturasPagadasYSinPagar(){
	int x = 15,y = 2;
	system("cls");
	gotoxy(x,y);
	printf("FACTURAS SIN PAGAR");
	x = 0,y = 4;gotoxy(x,y);
	printf("ID FACT.");x+=9;
	gotoxy(x,y);printf("CLIENTE");x+=20;
	gotoxy(x,y);printf("CEDULA");x+=15;
	gotoxy(x,y);printf("# ARTICULOS");x+=15;
	gotoxy(x,y);printf("TOTAL");x+=11;
	gotoxy(x,y);printf("ESTADO");
	y++;x=0;gotoxy(x,y);
	printf("===============================================================================");y++;gotoxy(x,y);
	
	for(int i = 0; i < Cont_facturas;i++){
		if((Pfactura + i)->estado == true){
			printf("%d",(Pfactura + i)->id);x+=10;
			gotoxy(x,y);printf("%s",(Pfactura + i)->nombre_cliente);x+=20;
			gotoxy(x,y);printf("%s",(Pfactura + i)->cedula_cliente);x+=15;
			gotoxy(x,y);printf("%d",(Pfactura + i)->Cantidad_productos);x+=15;
			gotoxy(x,y);printf("%d",(Pfactura + i)->total);x+=11;
			gotoxy(x,y);printf("**DEBE**");
			y++;x=0;gotoxy(x,y);
		}
	}
	y+=2;x=0;gotoxy(x,y);
	printf("-----------------------------------------------------------------------------");y+=2;x=15;gotoxy(x,y);
	
	printf("FACTURAS PAGADAS");
	x = 0,y+= 2;gotoxy(x,y);
	printf("ID FACT.");x+=9;
	gotoxy(x,y);printf("CLIENTE");x+=20;
	gotoxy(x,y);printf("CEDULA");x+=15;
	gotoxy(x,y);printf("# ARTICULOS");x+=15;
	gotoxy(x,y);printf("TOTAL");x+=11;
	gotoxy(x,y);printf("ESTADO");
	y++;x=0;gotoxy(x,y);
	printf("===============================================================================");y++;gotoxy(x,y);
	
	for(int i = 0; i < Cont_facturas;i++){
		if((Pfactura + i)->estado == false){
			printf("%d",(Pfactura + i)->id);x+=10;
			gotoxy(x,y);printf("%s",(Pfactura + i)->nombre_cliente);x+=20;
			gotoxy(x,y);printf("%s",(Pfactura + i)->cedula_cliente);x+=15;
			gotoxy(x,y);printf("%d",(Pfactura + i)->Cantidad_productos);x+=15;
			gotoxy(x,y);printf("%d",(Pfactura + i)->total);x+=11;
			gotoxy(x,y);printf("**PAGO**");
			y++;x=0;gotoxy(x,y);
		}
	}
	y+=2;x=0;gotoxy(x,y);
	printf("------------------------------------------------------------------------------");y+=2;gotoxy(x,y);
	
	printf("\n\nPresione ENTER para continuar ...");
	int teclapresionada;
	do{teclapresionada = getch();} while(teclapresionada != ENTER);
	MostrarMenuPrincipal();
}


