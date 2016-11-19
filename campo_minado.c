//-------------------------------------------------------------------- 
// Estrutura básica para o desenvolvimento de um jogo de campo minado
//--------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

//--------------------------------------------
//Struct básica para cada célula do tabuleiro
//--------------------------------------------
struct celula {
	char imprime; // Membro que deverá conter o valor a ser impresso da célula
	int valor;    // Membro que deverá conter o valor de controle da célula
};

//--------------------------------------------
// (2) Escreva aqui a rotina responsável por
// criar bombas no tabuleiro de forma
// aleatória
//--------------------------------------------
// A função srand(time(NULL)) lê os segundos do computador, que sempre será diferente,garantindo que a semente também será sempre
//será diferente e que o numero será sempre aleatório, ao fazer o módulo da semente por algum número se tem um número aleatório entre 0 e esse número.
//Para cada bomba que precisa ser espalhada pelo tabuleiro é gerado um número aleatório entre 0 e o valor do lado menos 1 para x e para y, e o campo valor da celula do tabuleiro nessa posição é atualizada para -1
void gera_bombas(struct celula *tabuleiro, int lado, int num_bombas){
int i,x,y;

srand(time(NULL));
for(i=0;i<num_bombas;i++){
	x = (rand()%lado-1)*lado;
	y = rand()%lado-1;
	(tabuleiro+x+y)->valor = -1;
}
}

//--------------------------------------------
// (3) Escreva aqui a função responsável por
// ler o valor de uma casa vizinha
//--------------------------------------------
int le_vizinho(int x, int y, int posicao, int controle, struct celula *tabuleiro, int lado){
	
	if ((y==-1 && posicao<lado) || (y==1 && posicao>=(lado-1)) || (x==-1 && (posicao%lado)==0) || (x==1 && (posicao%lado)==(lado-1))) {
		if(controle==0)
		return -2;
		else
		return 'd';
	}
	int r=posicao+x+y*lado; // r=posicao+x+y*lado
	if(controle==0)
		return tabuleiro[r].valor;
	else return tabuleiro[r].imprime;
}

//--------------------------------------------
// (4) Escreva aqui a rotina responsável por
// calcular os valores de controle de todas
// as células que não contem uma bomba
//--------------------------------------------
void calcula_celulas(struct celula *tabuleiro, int lado){
	int i,x,y,c;
	for(i=0;i<lado*lado;i++){
c=0;
if(tabuleiro[i].valor==-1)
continue;
		for(x=-1;x<=1;x++){
			for(y=-1;y<=1;y++){
				if(le_vizinho(x,y,i,0,tabuleiro,lado) == -1)
					c++;
				}
		tabuleiro[i].valor=c;


		}
	}
}
//--------------------------------------------
// Rotina para impressão do tabuleiro
// mostrando valores invisíveis para o
// jogador
//--------------------------------------------
void imprime_tabuleiro_debug(struct celula *tabuleiro, int lado){
	int i, celulas=lado*lado;
	//Imprime índices do eixo x
	printf("    ");
	for(i=0;i<lado;i++){
		printf(" %2d",i);
	}
	//Imprime barra para separar o tabuleiro
	printf("\n   ----");
	for(i=1;i<lado;i++){
		printf("---");
	}
	printf("\n");
	i=0;
	//Imprime todas
	while(celulas--){
		if(i%lado==0) printf("%2d |",i/lado);
		printf(" %2d",tabuleiro->valor);
		tabuleiro++;
		if(++i%lado==0) printf("\n");
	}
	printf("\n");
}

//--------------------------------------------
// (5) Escreva aqui a rotina responsável por
// imprimir o tabuleiro, mostrando apenas os
// caracteres de impressão para o jogador
//--------------------------------------------
void imprime_tabuleiro(struct celula *tabuleiro, int lado){
		int i, celulas=lado*lado;

	printf("    ");
	for(i=0;i<lado;i++){
		printf(" %2d",i);
	}
	printf("\n   ----");
	for(i=1;i<lado;i++){
		printf("---");
	}
	printf("\n");
	i=0;
	while(celulas--){
		if(i%lado==0) printf("%2d |",i/lado);
		printf(" %2c",tabuleiro->imprime);
		tabuleiro++;
		if(++i%lado==0) printf("\n");
	}
	printf("\n");
}

//--------------------------------------------
// (6) Escreva aqui a rotina responsável por
// abrir todas as células até as bordas de
// células próximas a bombas
//--------------------------------------------
//Abre todas células até as bordas de células próximas a bombas
void expande_zero(struct celula *tabuleiro, int lado){
	int i,x,y,o,a;	
	for(i=0;i<lado*lado;i++){	
		if (tabuleiro[i].imprime==' '){
			for(x=-1;x<=1;x++)
				for(y=-1;y<=1;y++){
					if(x!=0 || y!=0){
					o=le_vizinho(x,y,i,0,tabuleiro,lado);
					if(o==-2)
					continue;
					a=i+x+y*lado;
					switch(o){
					case 1 : tabuleiro[a].imprime='1';
					break;
					case 2 : tabuleiro[a].imprime='2';
					break;
					case 3 : tabuleiro[a].imprime='3';
					break;
					case 4 : tabuleiro[a].imprime='4';
					break;
					case 5 : tabuleiro[a].imprime='5';
					break;
					case 6 : tabuleiro[a].imprime='6';
					break;
					case 7 : tabuleiro[a].imprime='7';
					break;
					case 8 : tabuleiro[a].imprime='8';
					break;
					case 0 : tabuleiro[a].imprime=' ';
						 expande_zero(tabuleiro,lado);
					break;
					}
				}		
	
			}
		}	
	}
}

//--------------------------------------------
// (7) Escreva aqui a rotina responsável por
// solicitar uma coordenada XY e abrir uma
// célula no tabuleiro
//--------------------------------------------
void abrir_celula(struct celula *tabuleiro, int lado){
	int x,y;	
	printf("Informe as coordenadas X e Y para abertura da celula: ");
	scanf("%d %d", &x, &y);
	if((tabuleiro+x+y*lado)->imprime=='B')
		printf("Celula já marcada!");
	if((tabuleiro+x+y*lado)->valor>0)
	(tabuleiro+x+y*lado)->imprime=(tabuleiro+x+y*lado)->valor;
	else if((tabuleiro+x+y*lado)->valor==0)
		expande_zero(tabuleiro,lado);

	
	

}

//--------------------------------------------
// (8) Escreva aqui a função responsável por
// verificar se o jogo acabou. Ela
// contabiliza se o numero de bombas
// marcadas e casas fechadas são iguais ao
// numero de bombas do jogo ou se o jogador
// abriu uma bomba
//--------------------------------------------
//
int fim_jogo(struct celula *tabuleiro, int lado, int total_bombas){
	int i,cont=0;
	for(i=0;i<lado*lado;i++){
		if(tabuleiro[i].imprime=='#' || tabuleiro[i].imprime=='B')
			cont++;
	}
	if(cont==total_bombas)
	return 1;
	else 
	return 0;
}

//--------------------------------------------
// (9) Escreva aqui a rotina responsável por
// solicitar uma coordenada XY e marcar uma
// célula no tabuleiro como bomba. Caso a
// célula já esteja marcada como bomba, a
// rotina desmarca a célula
//--------------------------------------------
void marcar_bomba(struct celula *tabuleiro, int lado){
	int x,y;
	printf("Informe as coordenadas X e Y para marcar bomba: ");
	scanf("%d %d", &x, &y);
	if((tabuleiro+x+y)->imprime=='#')
		(tabuleiro+x+y*lado)->imprime='B';
	else if((tabuleiro+x+y*lado)->valor=='B')
		(tabuleiro+x+y*lado)->imprime='#';
}

//--------------------------------------------
// (10) Escreva aqui a rotina responsável por
// ler os resultados do arquivo e mostrar na
// tela a pontuação histórica do jogo
//--------------------------------------------
void lista_pontuacao(){	
	char rank[500];
	int i;	
	FILE * pFile;
	pFile = fopen("pontos.txt", "r");
	if (pFile!=NULL){
		do{
			for(i=0;i<10;i++)
				if(fgets(rank,i, pFile) != NULL)
				printf("%s\n",rank);
		}while(!feof(pFile));
		fclose(pFile);
	}
	else
		printf("Erro ao listar pontuação.\n");
}

//--------------------------------------------
// Função que será executada na função main,
// ela serve para que o jogador realize suas
// jogadas até o final do jogo
//--------------------------------------------
int jogada(struct celula *tabuleiro, int lado, int total_bombas){
	char opcao;
	do{
		printf("\nEntre com a operação (a/b/p/c/s): ");
		scanf(" %c",&opcao);
	} while (opcao!='a' && opcao!='b' && opcao!='p' && opcao!='c' && opcao!='s');
	
 	if (opcao=='a') {
		printf("Abrir posição\n");
		abrir_celula(tabuleiro, lado);
		return fim_jogo(tabuleiro, lado, total_bombas);
 	}
 	else if (opcao=='b') {
		printf("Marcar bomba\n");
	  marcar_bomba(tabuleiro, lado);
		return 1;
 	}
 	else if (opcao=='p') {
		printf("Pontuação:\n");
		lista_pontuacao();
 		return 1;
 	}
 	else if (opcao=='c') {
		printf("Comandos:\n a - Abrir posição no tabuleiro;\n b - Marcar/Desmarcar posição no tabuleiro como bomba;\n p - Listar pontuações;\n c - Listar comandos;\n s - Sair do jogo.\n\n");
 		return 1;
 	}
	else return 0;
}

//--------------------------------------------
// (11) Escreva aqui a função responsável por
// calcular e retornar os pontos feitos pelo
// jogador
//--------------------------------------------
double calcula_pontos(struct celula *tabuleiro, int lado, int total_bombas){
	int P,pct_celulas,celulas_abertas,i;
	for(i=0;i<lado*lado;i++){
		switch(tabuleiro[i].imprime){
		case ' ' : celulas_abertas++;
		break;
		case '1' : celulas_abertas++;
		break;
		case '2' : celulas_abertas++;
		break;
		case '3' : celulas_abertas++;
		break;
		case '4' : celulas_abertas++;
		break;
		case '5' : celulas_abertas++;
		break;
		case '6' : celulas_abertas++;
		break;
		case '7' : celulas_abertas++;
		break;
		case '8' : celulas_abertas++;
		break;
		}
	}
	pct_celulas=celulas_abertas/((lado*lado)-total_bombas);
	
return P=(lado*lado)*(total_bombas*pct_celulas);

}

//--------------------------------------------
// (12) Escreva aqui a rotina responsável por
// salvar a pontuação do jogador no arquivo
// texto pontos.txt.
//--------------------------------------------
void imprime_resultado(char jogador[20], double pontos){	
	//Comparar cada linha com o resultado atual
	// Ordenar de acordo com a colocação(Comparação)
	//Para análise de resultados, converter número do arquivo para reais.
	/*************************
	SUBSTITUA PELO SEU CODIGO
	*************************/
}

//--------------------------------------------
// Função principal (main).
//--------------------------------------------
int main (int argc, char *argv[]){
	//Tabuleiro e variáveis para controle
	struct celula *tabuleiro, *tabuleiro_aux;
	int lado_tabuleiro, num_bombas;
	double pontos;
	//Nome do jogador
	char jogador[20];
	//Variavel para controle de laços
	int i;
	i=0;
  //------------------------------------------
  // (1A) Escreva aqui um trecho de código
	// para verificar a consistência de dados
	// de entrada do programa (argc e argv).
  //------------------------------------------
//É verificado se foram informados todos os argumentos necessários para inicialização do programa: Nome do jogador, lado do tabuleiro e numero de bombas.
//Caso não seja informado o número necessario de argumentos o jogo não inicia.

if(argc>5 && argc<4){
printf("Quantidade de argumentos invalida");
return 0;
}
if(atoi(argv[2])<0){
printf("Quantidade invalida de lados");
return 0;
}

if(atoi(argv[3])>atoi(argv[2])*atoi(argv[2]) || atoi(argv[3])<0){
printf("Quantidade invalida de bombas");
return 0;
}





  //------------------------------------------
  // (1B) Escreva aqui um trecho de código
	// para inicializar as variáveis do jogo.
  //------------------------------------------
//As variaveis recebem os argumentos(nome do jogador, lado do tabuleiro e numero de bombas) verificados anteriormente
//Como todos os argumentos são do tipo char, e para inicializar as variaveis correspondentes ao lado do tabuleiro e numero de bombas é preciso dados do tipo int, usamos o comando atoi para converter esses argumentos para int
//Para preencher o vetor --> jogador <-- criamos um ponteiro para o argumento correspondente ao nome do jogador(argv[1]), usamos um laço para avançar as posições do vetor jogador e preenche-lo com cada valor das respectivas posições de argv[1]. O laço termina quando o ponteiro apontar para a ultima posição do argv[1]( quando o valor na posição for \0)
num_bombas=atoi(argv[3]);
lado_tabuleiro=atoi(argv[2]);
char *ponteiro;
ponteiro = argv[1];

while(*ponteiro != '\0'){
jogador[i] = *ponteiro;
i++;
ponteiro++;
}

jogador[i] = '\0';


  //------------------------------------------
  // (1C) Escreva aqui um trecho de código
	// para inicialização do tabuleiro e
	// alocação de espaço em memória
	// (usar malloc).
  //------------------------------------------
//Cada celula do tabuleiro precisa de um espaço na memória do tamanho da struct, que contém um char(para o campo imprime) e um int(para o campo valor). Esse espaço precisa ser alocado dinâmicamente de acordo com a area do tabuleiro, multiplicando essa area com cada espaço de memória necessário para cada celula.
//Depois de alocar o espaço necessário, cada campo imprime de cada celula do tabuleiro precisa ser preenchido com o char '#', e cada campo valor de cada celula precisa ser preenchido com 0.
tabuleiro = malloc((lado_tabuleiro*lado_tabuleiro)*sizeof(struct celula));
for(i=0;i<lado_tabuleiro*lado_tabuleiro;i++){
	tabuleiro[i].valor=0;	
	tabuleiro[i].imprime='#';
}

tabuleiro_aux = tabuleiro;

	// Neste momento, as bombas devem ser criadas no
	// tabuleiro e os valores de controle de todas
	// células devem ser calculados.
	gera_bombas(tabuleiro, lado_tabuleiro, num_bombas);
	calcula_celulas(tabuleiro, lado_tabuleiro);
	if ((argc == 5) && (!strcmp("DEBUG",argv[4])))
	  imprime_tabuleiro_debug(tabuleiro, lado_tabuleiro);
			
	// Este trecho de código é o laço do jogo, ele
	// só sai do laço quando o jogo acaba.
	do{
		imprime_tabuleiro(tabuleiro, lado_tabuleiro);
	}while(jogada(tabuleiro, lado_tabuleiro, num_bombas));
	imprime_tabuleiro(tabuleiro, lado_tabuleiro);
	
	// Neste momento, devemos calcular e imprimir o
	// resultado no arquivo.
	pontos = calcula_pontos(tabuleiro, lado_tabuleiro, num_bombas);
  imprime_resultado(jogador, pontos);
	lista_pontuacao();

	return 0;
}
