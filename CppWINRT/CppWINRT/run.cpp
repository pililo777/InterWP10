#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS

#include "nodo.h"
#include "stdio.h"
extern FILE * fichero;

elnodo * procedimientos[127]; //cambiar esta forma
  int idx_prc = 0;   //se ha quitado static de aqui y de abajo

elnodo * pila_programas[32];
  int idx_prg = 0;


extern "C" char * strcpy ( char *  , const char *   );
extern "C"  int strcmp ( const char *  , const char *   );
extern  int linenumber;
extern   int LineaInicial;

extern  char variables[127][127];
extern   char constantes[127][127];
double evalua (elnodo *);

double var[127];  // 127 variables numericas e indices
static int counter1[32];
static int indice_ctr = 0;  
static int error_getstring = 0;

char *getstring(char *s)
{
    int i, k = getchar();
    error_getstring = 0; 
    /* Return NULL if no input is available */
    if (k == EOF)
        return NULL;

	if (k == 10) { 
		//k = getchar();
		error_getstring = 1;
		//printf("se leyo un caracter 10\n");
		return NULL;
	}
    /* Read and store characters until reaching a newline or end-of-file */
    for (i = 0; k != EOF && k != '\n'; ++i) {
        s[i] = k;
        k = getchar();
 
        /* If a read error occurs, the resulting buffer is not usable. */
        if (k == EOF && !feof(stdin))
            return NULL;
    }
 
    /* Null-terminate and return the buffer on success.
    The newline is not stored in the buffer. */
    s[i] = '\0';
 
    return s;
}



elnodo *nodo1(tiponodo, elnodo *);
elnodo *nodo2(tiponodo, elnodo *,elnodo *);
elnodo *nodo3(tiponodo, elnodo *,elnodo *,elnodo *);
elnodo *nodo4(tiponodo, elnodo *,elnodo *,elnodo *,elnodo *);


extern struct elnodo * nuevonodo();

elnodo * nodo1(tiponodo  Tipo, elnodo * a)
{
elnodo * p;
p = nuevonodo();
p->tipo = Tipo;
p->num = 777;
p->nodo1 = a;
//p->nrolinea2 = linenumber;
p->subnodos = 1;



return p;
}

elnodo * nodo2(tiponodo Tipo, elnodo * a, elnodo * b)

{
elnodo * p;
p = nuevonodo();
p->tipo = Tipo;
p->num = 777;
p->nodo1 = a;
p->nodo2 = b;
p->subnodos = 2;
//p->nrolinea2 = linenumber;
p->nrolinea1 = LineaInicial;

return p;

}

elnodo * nodo3(tiponodo Tipo, elnodo * a, elnodo * b, elnodo *  c)
{
elnodo * p;
p = nuevonodo();
p->tipo = Tipo;
p->num = 777;
p->nodo1 = a;
p->nodo2 = b;
p->nodo3 = c;
p->subnodos = 3;
//p->nrolinea2 = linenumber;


return p;


}

elnodo * nodo4(tiponodo Tipo, elnodo *  a, elnodo * b, elnodo * c, elnodo * d)
{
elnodo * p;
p = nuevonodo();
p->tipo = Tipo;
p->num = 777;
p->nodo1 = a;
p->nodo2 = b;
p->nodo3 = c;
p->nodo4 = d;
p->subnodos = 4;
//p->nrolinea2 = linenumber;

return p;

}


void * execut(elnodo *  a)
{
elnodo * p;
//p = nuevonodo();

p = a;
switch (p->tipo) {

	case decimales:

		nro_decimales =  ( (int) p->nodo1->num  );
		break;



	case secuencia:
		// printf("secuencia\n");
		execut(p->nodo1);
		// printf("secuencia 2\n");
		execut(p->nodo2);
		break;

	case imprimir_literal :
				fprintf(fichero, "%s", constantes [(int)p->nodo1->num] ) ;
				break;

	case imprimir_var_alfa:
				//fprintf("%s", constantes [(int) var [(int)p->nodo1->num]] ) ;
				fprintf(fichero, "%s", constantes [ (int)  var   [(int)p->nodo1->num]    ]) ;
				break;

	case imprimir_expresion :


		switch(nro_decimales ) {

			case 0:
				fprintf(fichero, "%.0f", evalua(p->nodo1) );
				break;

			case 1:
				fprintf(fichero, "%.1f", evalua(p->nodo1) );
				break;

			case 2:

				fprintf(fichero, "%.2f", evalua(p->nodo1) );
				break;

			case 3:
				fprintf(fichero, "%.3f", evalua(p->nodo1) );
				break;
			case 4:
				fprintf(fichero, "%.4f", evalua(p->nodo1) );
				break;
			case 5:
				fprintf(fichero, "%.5f", evalua(p->nodo1) );
				break;
			case 6:
				fprintf(fichero, "%.6f", evalua(p->nodo1) );
				break;
			case 7:
				fprintf(fichero, "%.7f", evalua(p->nodo1) );
				break;
			case 8:
				fprintf(fichero, "%.8f", evalua(p->nodo1) );
				break;
			case 9:
				fprintf(fichero, "%.9f", evalua(p->nodo1) );
				break;
			case 10:
				fprintf(fichero, "%.10f", evalua(p->nodo1) );
				break;
			case 11:
				fprintf(fichero, "%.11f", evalua(p->nodo1) );
				break;
			case 12:
				fprintf(fichero, "%.12f", evalua(p->nodo1) );
				break;
			case 13:
				fprintf(fichero, "%.13f", evalua(p->nodo1) );
				break;
			case 14:
				fprintf(fichero, "%.14f", evalua(p->nodo1) );
				break;
			case 15:
				fprintf(fichero, "%.15f", evalua(p->nodo1) );
				break;

			default:
				fprintf(fichero, "%.15f", evalua(p->nodo1) );
				break;

		};

		break;



	case imprimir_varios:
		//fprintf("imprimir varios\n");
		execut(p->nodo1);
		fprintf(fichero, "\n");
		break;

	
	case llamar:
		//fprintf("\nllamar un procedimiento\n");
		if (procedimientos[(int)p->nodo1->num] == NULL)
		   {
			   fprintf(fichero, "procedimiento no encontrado en linea: \n");
			   getchar();
			   //exit (1);
		   }

		execut ( procedimientos[ (int) (p->nodo1->num) ]  );
		//fprintf("volvemos del procedimiento\n\n");
		break;

	case asigna_num:
		//fprintf("asignar numerico\n");
		var[(int) p->nodo1->num] = evalua ( p->nodo2 );
		break;

	case asigna_alfa:
		//fprintf("asignar alfanumerico\n");
		var[(int) p->nodo1->num] = p->nodo2->num;
		break;

	case mientras:
		//fprintf ("mientras se cumple la condicion\n");
		while (evalua(p->nodo1 )) 
 
			execut(p->nodo2);
		//fprintf ("fin del bloque-mientras\n");
 
		break;

	case leer:
		//fprintf("leer var numerica\n");
		{
		 elnodo *pp;   //se puso esto para depuracion (watch)
		 int inum = 0;
		double fnum;
		pp = p;
		inum = (int)p->nodo1->num;
		//fprintf("i = %d\n", inum);
		scanf("%lf", &fnum );
		var[inum] = fnum;
		}
		break;

	case leertexto:
		//fprintf("leer var numerica\n");
		{
		int indice;
		elnodo * pp ;
	 
		char texto[255]  ;
        //pp = p;
		 getstring(texto); 
		 if (error_getstring )
			 getstring (texto);
		//gets(texto2);
		//scanf("%[^\n]",texto);

		///scanf_s("%[^\n]", texto, 21);

		//fflush(stdin);
		indice = (int)p->nodo1->num;
		strcpy ( constantes [(int)var[indice]], texto);
		}
		break;

	case si:
		//fprintf("si se cumple la condicion\n");
		if (evalua(p->nodo1 )) {
			execut(p->nodo2); }
		else
			if (p->subnodos == 3) {
				//fprintf("sino se cumple\n");
				execut(p->nodo3);
			};
		//fprintf("fin del bloque-si\n");
		
		break;

	case desde:
		//fprintf("desde\n");
		{
		int x = (int) p->nodo1->num;
		//int y = evalua(p->nodo3);
		indice_ctr++;
		counter1[indice_ctr] = var[x] = evalua(p->nodo2);

		for (counter1[indice_ctr]; counter1[indice_ctr] <= (int) evalua(p->nodo3 ); counter1[indice_ctr]++)
			{
				//y = evalua(p->nodo3);
				var[x] = counter1[indice_ctr];
				execut(p->nodo4 );
			}

		indice_ctr--;
		
		}
		
		break;


	default:
		break;

	}
return (0);
}

void evalua_doble(elnodo * p, elnodo * q) {
		double result1, result2;

}


double evalua (elnodo * p) {
 

	switch (p->tipo) {
	
	case indice_strings:    //una variable numerica
		 return var [(int)p->num];
	
	case un_numero:
		return p->num ;     //un numero constante
		


	case resta:
		
		return evalua(p->nodo1) - evalua(p->nodo2);

	case suma:
		return evalua(p->nodo1) + evalua(p->nodo2);

	case multiplica:
		return evalua(p->nodo1) * evalua(p->nodo2);

	case divide:
		if (evalua(p->nodo2) == 0 ) {
			fprintf(fichero, "\nerror: division por cero.\n");
			//exit (1);
		}
		return evalua(p->nodo1) / evalua(p->nodo2);

	case mayorque:
		return evalua(p->nodo1 ) > evalua(p->nodo2 );

	case mayorigualque:
		return evalua(p->nodo1 ) >= evalua(p->nodo2 );

	case noigualque:
		return evalua(p->nodo1 ) != evalua(p->nodo2 );

	case menorque:
		return evalua(p->nodo1 ) < evalua(p->nodo2 );

	case igualque:
		return evalua(p->nodo1 ) == evalua(p->nodo2 );

	case menorigualque:
		return evalua(p->nodo1 ) <= evalua(p->nodo2 );

	case negativo:
		return - evalua(p->nodo1 );

	case comparaliteral:

		{
		char string1[255];
		char string2[255];
		
		strcpy (string1, constantes[(int) var[(int)p->nodo1->num]]);
		strcpy (string2, constantes[(int)p->nodo2->num]);
		return !strcmp(string1, string2);

		}

	default:

		break;
		
	
	
	}
}

