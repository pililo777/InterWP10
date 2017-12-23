using namespace Windows;
#define _CRT_SECURE_NO_WARNINGS
/*  * * * * * * * * * * * * * *  main.cpp   * * * * * * * * * * */

#include "pch.h"

#include "stdio.h"
#include "nodo.h"
#include <string>
#include <iostream>
#include <stdlib.h>
 


extern int idx_prg;
FILE * fichero = (FILE *) 0;
extern double var[127];
extern FILE * yyin;
extern   char instalavar(char );
extern char *yytext;
extern  char contadorvar;
extern   int yyparse(void);
extern   void *  execut(elnodo *);
extern   elnodo * pila_programas[32];
extern   elnodo * nuevonodo();
extern "C" char * strcpy ( char *  , const char *   );
// extern "C" char * strcmp ( char *, const char * );
extern char variables[127][127];
int nodos = 0;

using namespace Platform;


/* ----------------------------------------------------------------*/
namespace CppWINRT  // test
{



 

 

//const char * to_cStr(String ^str)
//{
//char * rStr = new char[256];
//const char* c_str = (const char*)
//(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str)).ToPointer();
//strcpy(rStr,c_str);
//Runtime::InteropServices::MarshalAsAttribute::FreeHGlobal(IntPtr((void*)c_str));
//return rStr;
//}

   

public ref class clase1 sealed
	{

		
		/*~clase1(); 

	public: clase1();*/
	public:
			 void main (int argc, String ^s);
			
			 int  asignar_num(int num, String ^s);
		     double  run(   String ^s); //retorna la primer variable
			 double  buscar_valor(String ^nombre);
 
	private:
		 void liberar_nodo( elnodo * p, int n);
 	
	};
 //clase1





//
//clase1::clase1()   //constructor 
//{
//
//}
//
//
//clase1::~clase1()  //dest.
//{
//
//}

void clase1::liberar_nodo( elnodo * p, int n)

{
    
        
        if (p==NULL) return;
        
 
        if (p == pila_programas[n]) {
                if (p->subnodos == 0) 
                    {
                        free(p);
                        nodos--;
                        //printf("no hay nodos para liberar\n");
                        return;
                    }
        
            if (p->subnodos > 0) {
                liberar_nodo(p->nodo1, n);
 
            }

        if (p->subnodos > 1) {
            liberar_nodo(p->nodo2, n);
 
        }

        if (p->subnodos > 2) {
            liberar_nodo(p->nodo3,n);
 
        }

        if (p->subnodos > 3) {
            liberar_nodo(p->nodo4,n );
 
        }
		 
           free(p);
           //memoria -= (long) sizeof (struct ast);
           nodos--;
       //    printf("librando el nodo raiz: %ld\n", memoria);
            
            
        
        pila_programas[n] = NULL;
		fprintf(fichero, "%s\n", "hemos liberado memoria");
        return;
    }
    else {
           
        if (p->subnodos == 0) 
        {
            free(p);
            //memoria -= (long) sizeof (struct ast);
            nodos--;
         //   printf("librando un nodo sin subnodos: %ld\n", memoria);
            return;
        }

           
           if (p->subnodos > 0) {
            liberar_nodo(p->nodo1, n);
            
 
    }

        if (p->subnodos > 1) {
            liberar_nodo(p->nodo2, n);
 
}
 
        if (p->subnodos > 2) {
            liberar_nodo(p->nodo3, n);
 
        }

        if (p->subnodos > 3) {
            liberar_nodo(p->nodo4, n);
 
        }
 
           
           free(p);
           // memoria -= (long) sizeof (struct ast);
           nodos--;
           
       //    printf("librando el nodo: %ld\n", memoria);
		   //fprintf(fichero, "%s\n", "hemos liberado memoria(2)");
           return;

    }
    //return
        
}

 void clase1::main (int argc, String ^s)
{
    int i;

	/*
	elnodo * comando, * numero, * variable;

	variable = nuevonodo();
	variable->tipo = indice_strings;  //nombre de variables numéricas.
	yytext = "numerito";
	variable->num = (char) instalavar(contadorvar++);

	numero = nuevonodo();
	numero->tipo = un_numero;
	numero->num = 4;
	//
	comando = nuevonodo();
	comando->tipo = asigna_num;
	comando->nodo1 = variable;
	comando->nodo2 = numero;
	comando->subnodos = 2;

	execut(comando);
*/

	//yytext = "numerito2";
	//numero->num = 8;
	//variable->num = (char) instalavar(contadorvar++);
	//execut(comando);
	//

	// free(comando), numero, variable.....eliminar estos nodos de memoria.

	

	//printf("hola\n");
	//system ("cd");
	//printf("%d\n", argc);
	//printf("%s\n", argv[0]);

	long sz;

	if   (argc > 1) {     //  {     //LO normal es :   (argc > 1)  --  para depurar con un programa: (argc = 1)
		//yyin = fopen("c:\\inter\\tst10.pr", "r");
		i = 1;
		
		do {
			//fprintf( fichero, &argv );
			//return;
			
		    yyin = fopen("p1.pr", "r");    //comentar para depurar

			errno_t err = fopen_s(&yyin, "p1.pr", "rb");

			
			
		    if (yyin != NULL){
				// vemos el tamaño del fichero
				fseek(yyin, 0L, SEEK_END);
				sz = ftell(yyin);
				fseek(yyin, 0L, SEEK_SET);
				fprintf(fichero, "Tamaño programa: %ld bytes\n", sz);
			    //printf("abierto.....\n");
			    {
					   idx_prg = 0;
					   yyparse();
					   fprintf (fichero, "parse: %d nodos\n", nodos);
					   fclose(yyin);
					   i++;
				}
			} 
			else {
				fprintf(fichero, "imposible abrir fichero.\n");
				break;
			}
		} while    (i != argc) ; //  (i != argc);  //   // ; para depurar:  (i==1); modificar abajo tambien(run)

		//ejecuciona los programas de la pila.


		// CORRE HASTA 32 PROGRAMAS:


		i = 1;
		do {
				execut(pila_programas[i-1]);
				i++;
		} while (i != argc);  // (i != argc);     //para depurar:  ( (i == 1); //

		fprintf (fichero, "se crearon: %d nodos\n", nodos);
		
		 liberar_nodo(pila_programas[0], 0);

		 fprintf (fichero, "quedan: %d nodos\n", nodos);

		 //nodos = 0;

	}

	else
			printf("usar: inter.exe nombreprograma [nombreprograma....]\n");
		

}



double clase1::run(String ^s)
			{
			    int argc = 2;
				char test[80];

				Platform::String^ localfolder = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
				Platform::String^ myFileName = Platform::String::Concat(localfolder, "\\test.txt");
				Platform::String^ mode = "w";
				//Platform::String^ mensaje = "hola, mundo";
				

				

				std::wstring stlString = myFileName->Data();
				std::wstring   modeWrite = mode->Data();

				const wchar_t * stlString2;
				stlString2 = stlString.c_str() ;
				const wchar_t  * mode1 =  modeWrite.c_str()   ;
				 
				strcpy (test, "p1.pr") ;
				fichero = _wfsopen (stlString2  , mode1  , _SH_DENYNO); 
	 
				main(argc, "p1.pr" );

				fclose (fichero);
				return(::var[0]);  //gracias, intellisense
				
				
			}

int clase1::asignar_num (int num, String ^s)
   {
				char test[80];
				elnodo * comando, * numero, * variable;

				std::wstring stlString = s->Data();
				const wchar_t *  s2 =   stlString.c_str() ;
				int i = 0;

				int l = stlString.length() ;
				for (i=0; i<l; i++) {
					test[i] = (char) s2[i];
				}
				test[i++] = '\0';


				//wctomb(test, (wchar_t ) s2);
				
				//strcpy (test,   s2  ) ;
				

				
				variable = nuevonodo();

			

				variable->tipo = indice_strings;  //nombre de variables numéricas.
				yytext = test;
				variable->num = (char) instalavar(contadorvar++);
				
				
				numero = nuevonodo();
				numero->tipo = un_numero;
				numero->num = num;
	//
	
				comando = nuevonodo();
				comando->tipo = asigna_num;
				comando->nodo1 = variable;
				comando->nodo2 = numero;
				comando->subnodos = 2;
				execut(comando);
				return(1);
				
   }

double  clase1::buscar_valor(String ^nombre)
{
	char test[80];
	//strcpy (test, to_cStr(nombre) ) ;
	int i= 0;
	double valor = 0;
	for (i=0; i<127; i++) {
		if (!strcmp (variables[i], test)) {
			valor = var[i];
			i=127;
		}
	}
	return (valor);
}

}
//namespace prueba




