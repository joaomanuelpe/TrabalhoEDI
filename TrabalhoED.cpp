#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>

struct TpAutor{ //struct para dados de autor
	char sobrenome[200], nome[200];
	TpAutor *prox;
};


struct TpLAutor{ //struct para lista de autores
	TpAutor *pAutor;
	TpLAutor *prox;
};

struct TpLivros{ //struct para livros
	int ano, paginas;
	char titulo[150];
	TpLivros *ant, *prox;
	TpLAutor *pListaAutor;
};

struct TpEditora{ //struct para editora
	char editora[150];
	TpLivros *pLivros;
	TpEditora *prox;
};

struct TpDescritor{ //struct descritor
	int qtd;
	TpEditora *inicio, *fim;
};

struct TpLivro{ //struct para leitura do arquivo binário
	int ano, paginas;
	char autores[150], titulo[150], editora[150], statusLivro;
};

void LimpaMenu()
{
	int i, j;
	textbackground(0);
	for(i=5;i<26;i++)
		for(j=10;j<26;j++)
		{
			gotoxy(i,j);
			printf(" ");
		}
}

void LimpaMensagem()
{
	int i, j = 7;
	textbackground(0);
	for(i=16;i<98;i++)
	{
		gotoxy(i,j);
		printf(" ");
	}
}

void LimpaTela()
{
	int i, j;
	textbackground(0);
	for(i=28;i<99;i++)
		for(j=10;j<26;j++)
		{
			gotoxy(i,j);
			printf(" ");
		}
}

void LimpaRelatorio(int j)
{
	int i, k;
	textbackground(0);
	for(i=2;i<=101;i++)
		for(k=27;k<=j;k++)
		{
			gotoxy(i,k);
			printf(" ");
		}
}

void Bordas(int ci, int li, int cf, int lf, int corTexto) {
	int i;
 	textcolor(corTexto);
	gotoxy(ci, li);
	printf("%c", 201);
	gotoxy(cf, li);
	printf("%c", 187);
	gotoxy(ci, lf);
	printf("%c", 200);
	gotoxy(cf, lf);
	printf("%c", 188);

	for(i=ci+1; i<cf; i++) {
		gotoxy(i, li);
		printf("%c", 205);
		gotoxy(i, lf);
		printf("%c", 205);
	}

	for(i=li+1; i<lf; i++) {
		gotoxy(ci, i);
		printf("%c", 186);
		gotoxy(cf, i);
		printf("%c", 186);
	}
	textcolor(7);
}

void LimpaTudo(int ci, int li, int cf, int lf)
{
	int i;
	gotoxy(ci, li);
	printf(" ");
	gotoxy(cf, li);
	printf(" ");
	gotoxy(ci, lf);
	printf(" ");
	gotoxy(cf, lf);
	printf(" ");

	for(i=ci+1; i<cf; i++) {
		gotoxy(i, li);
		printf(" ");
		gotoxy(i, lf);
		printf(" ");
	}

	for(i=li+1; i<lf; i++) {
		gotoxy(ci, i);
		printf(" ");
		gotoxy(cf, i);
		printf(" ");
	}
}
void Moldura()
{
	int i;
	
	Bordas(2,2,101,28,6);//Principal
	textcolor(6);
	gotoxy(38,3); printf("TRABALHO ESTRUTURA DE DADOS I");
	gotoxy(45,4); printf("MULTIPLAS LISTAS");
	textcolor(1);
	gotoxy(36, 3); printf("%c",245);
	gotoxy(68, 3); printf("%c",245);
	gotoxy(36, 4); printf("%c",245);
	gotoxy(68, 4); printf("%c",245);
	
	Bordas(4,6,99,8,1);//Mensagem
	Bordas(4,9,26,26,1);// Menu de Escolha
	Bordas(27,9,99,26,1);//Menu de Apresentar
}

void LimpaBorda()
{
	int i, j;
	for(i = 28; i < 99; i++)
	{
		gotoxy(i,26);
		printf(" ");
	}
	for(i = 3; i < 101; i++)
	{
		gotoxy(i,28);
		printf(" ");
	}
	
}

void LeDadosTxt(){ //tirando dados do arquivo texto e colocando no arquivo binário
	FILE *Ptr = fopen("livros.txt", "r");
	FILE *PtrBi = fopen("livros.dat", "wb+");
	TpLivro livro;
	fscanf(Ptr, "%[^|]|%[^|]|%[^|]|%d|%d\n", &livro.autores, &livro.titulo, &livro.editora, &livro.ano, &livro.paginas);
	while(!feof(Ptr))
	{
		//printf("%s %s %s %d %d\n", livro.autores, livro.titulo, livro.editora, livro.ano, livro.paginas);
		livro.statusLivro = 'A';
		fwrite(&livro, sizeof(livro), 1, PtrBi);
		fscanf(Ptr, "%[^|]|%[^|]|%[^|]|%d|%d\n", &livro.autores, &livro.titulo, &livro.editora, &livro.ano, &livro.paginas);
	}
	//printf("%s %s %s %d %d\n", livro.autores, livro.titulo, livro.editora, livro.ano, livro.paginas);
	livro.statusLivro = 'A';
	fwrite(&livro, sizeof(livro), 1, PtrBi);
	
	fclose(Ptr); 
	fclose(PtrBi);
}

void InicializaDescritor(TpDescritor &descritor)
{
	descritor.inicio = descritor.fim = NULL;
	descritor.qtd = 0;
}

TpLAutor *NovaCaixaLAutor()
{
	TpLAutor *NC = new TpLAutor;
	NC -> pAutor = NULL;
	NC -> prox = NULL;
	return NC;
}

TpAutor *NovaCaixaAutor(TpAutor autor)
{
	TpAutor *NC = new TpAutor;
	strcpy(NC -> nome, autor.nome);
	strcpy(NC -> sobrenome, autor.sobrenome);
	NC -> prox = NULL;
	return NC;
}

TpEditora *NovaCaixaEdi(char editor[50])
{
	TpEditora *NC = new TpEditora;
	strcpy(NC -> editora, editor);
	NC -> pLivros = NULL;
	NC -> prox = NULL;
	return NC;
}

TpLivros *NovaCaixaLivros(TpLivros informacao)
{
	TpLivros *NC = new TpLivros;
	NC -> ano = informacao.ano;
	NC -> paginas = informacao.paginas;
	strcpy(NC -> titulo, informacao.titulo);
	NC -> ant = NULL;
	NC -> prox = NULL;
	NC -> pListaAutor = NULL;
	return NC;
}

TpAutor *BuscaAutor(TpAutor *pAutor, TpAutor autor)
{
	while(pAutor != NULL && (stricmp(autor.nome, pAutor->nome) != 0 || stricmp(autor.sobrenome, pAutor->sobrenome) != 0))
		pAutor = pAutor->prox;
	if(pAutor != NULL && (stricmp(autor.nome, pAutor->nome) == 0 && stricmp(autor.sobrenome, pAutor->sobrenome) == 0))
		return pAutor;
	return NULL;
}

TpAutor *InsereAutorNaUltima(TpAutor *pAutor, TpAutor autor)
{
	TpAutor *NC, *atual, *ant, *aux;
	aux = BuscaAutor(pAutor, autor);

	if(aux == NULL)
	{
		NC = NovaCaixaAutor(autor);
		if(pAutor == NULL)
			pAutor = NC;
		else
		{
			aux = pAutor;
			while(aux -> prox != NULL)
				aux = aux -> prox;
			aux -> prox = NC;
		}
	}
	return pAutor;
}

void pegaAutor(char autores[150], int &i, char sobrenome[100], char nome[100])
{
	int j;
	j = 0;
	while(autores[i] == 32)
		i++;
	while(autores[i] != ',')//colocando sobrenome
	{
		sobrenome[j] = autores[i];
		j++;
		i++;
	}
	sobrenome[j] = '\0';
	i+=2;
	j=0;
	while(autores[i] == 32)
		i++;
	while(autores[i] != '\0' && autores[i] != ';')
	{
		nome[j] = autores[i];
		i++;
		j++;
	}
	nome[j] = '\0';
}

TpAutor *InsereListaAutor(TpAutor *pAutor, char autores[150])
{
	int i;
	char sobrenome[80], nome[80];
	TpAutor autor;
	for(i=0; i<strlen(autores); i++)
	{
		pegaAutor(autores,i,sobrenome,nome);
		strcpy(autor.nome, nome);
		strcpy(autor.sobrenome, sobrenome);
		pAutor = InsereAutorNaUltima(pAutor, autor);//busca sobrenome + nome na lista pAutor
		
	}
	return pAutor;
}

TpLivros *BuscaLivro(TpLivros *pLivros, char titulo[100])
{
	while(pLivros != NULL && stricmp(titulo, pLivros->titulo) > 0)
			pLivros = pLivros->prox;
	if(pLivros != NULL && stricmp(titulo, pLivros->titulo) == 0) 
		return pLivros;
	return NULL;
}
void Exibir(TpEditora *ptr)
{
	int coluna = 6;
	TpEditora *aux = ptr;
	TpLivros *auxPLivros;
	if(aux == NULL)
		printf("Lista Vazia!!!\n");
	else
	{
		while(aux != NULL)
		{
			gotoxy(15, coluna);printf("Editora: %s\n",aux -> editora);
			coluna++;
			auxPLivros = aux->pLivros;
			 while(auxPLivros != NULL)
			 {
			 	gotoxy(15, coluna);printf("Titulo: %s - Ano: %d - Paginas: %d\n",auxPLivros->titulo, auxPLivros->ano, auxPLivros->paginas);
			 	auxPLivros = auxPLivros->prox;
			 	coluna++;
			 }
			 gotoxy(15, coluna);printf("---------------------------------------------------------");
			 coluna++;
			aux = aux->prox;
		}
	}
}

void ExibirListaAutor(TpAutor *ptr)
{
	if(ptr == NULL)
		printf("### LISTA VAZIA ###\n");
	else
	{
		printf("\n### Conteudo da Lista ###\n");
		while(ptr != NULL)
		{
			printf("NOME: %s - SOBRENOME: %s\n", ptr->nome, ptr->sobrenome);
			ptr = ptr -> prox;
		}
	}
}

TpLAutor *InsereAutorListaLivros(TpLAutor *pListaAutor, char autores[150], TpAutor *pAutor)
{
	int i;
	char sobrenome[80], nome[80];
	TpAutor autor;
	TpLAutor *NC, *aux;
	for(i = 0; i < strlen(autores); i++)
	{
		pegaAutor(autores, i, sobrenome, nome);
		strcpy(autor.nome, nome);
		strcpy(autor.sobrenome, sobrenome);
		NC = NovaCaixaLAutor();
		NC->pAutor = BuscaAutor(pAutor, autor);
		if(pListaAutor == NULL)
			pListaAutor = NC;
		else
		{
			aux = pListaAutor;
			while(aux->prox != NULL)
				aux = aux->prox;
			aux -> prox = NC;
		}
	}
	return pListaAutor;
}

TpLivros *InsereOrdenaLivro(TpLivros *pLivros, TpLivro livro, TpAutor *pAutor)
{
	//insere ou localiza o Livro
	TpLivros *NC, *atual, livro2, *aux;
	livro2.ano = livro.ano;
	livro2.paginas = livro.paginas;
	strcpy(livro2.titulo,livro.titulo);
	aux = BuscaLivro(pLivros, livro2.titulo);
	if(aux == NULL)
	{
		NC = NovaCaixaLivros(livro2);
		if(pLivros == NULL)
			pLivros = NC;
		else
		{
			if(stricmp(NC -> titulo, pLivros -> titulo) < 0)
			{
				NC -> prox = pLivros;
				pLivros -> ant = NC;
				pLivros = NC;
			}
			else
			{
				atual = pLivros;
				while(atual -> prox != NULL && (stricmp(NC -> titulo, atual -> titulo) > 0))
					atual = atual -> prox;
				if(stricmp(atual -> titulo, NC -> titulo) > 0)
				{
					NC -> prox = atual;
					NC -> ant = atual -> ant;
					atual -> ant -> prox = NC;
					atual -> ant = NC;
				}
				else
				{
					atual -> prox = NC;
					NC -> ant = atual;
				}
			}
		}
	}
	else
		NC = aux;
	NC -> pListaAutor = InsereAutorListaLivros(NC -> pListaAutor, livro.autores, pAutor);
	return pLivros;
}

TpEditora *BuscaEditora(TpEditora *inicio, char editora[150])
{
	while(inicio != NULL && stricmp(editora, inicio -> editora) > 0)
		inicio = inicio -> prox;
	if (inicio != NULL && stricmp(editora, inicio -> editora)==0)
		return inicio;
	return NULL;
}

void InsereOrdenaEditora(TpDescritor &desc, TpLivro livro, TpAutor *pAutor)
{
	TpEditora *NoEditora, *atual, *ant, *aux;
	aux = BuscaEditora(desc.inicio, livro.editora);//insere ou localiza a Editora
	if(aux == NULL)//não existe essa editora, ou seja, a inserção direta pode ser feita
	{
		NoEditora = NovaCaixaEdi(livro.editora);
		desc.qtd++;
		if(desc.inicio == NULL)
			desc.inicio = desc.fim = NoEditora;
		else
		{
			if(stricmp(NoEditora -> editora, desc.inicio -> editora) < 0)
			{
				NoEditora -> prox = desc.inicio;
				desc.inicio = NoEditora;
			}
			else
			{
				ant = desc.inicio;
				atual = ant->prox;
				while(atual!=NULL && stricmp(NoEditora -> editora, atual -> editora) > 0)
				{
					ant = atual;
					atual = atual -> prox;
				}
				ant->prox = NoEditora;
				NoEditora->prox = atual;
				if (atual == NULL)
					desc.fim = NoEditora;
			}
		}
	}
	else
		NoEditora = aux; //recebe a posição onde está a caixa editora para inserir outro livro
		
	 NoEditora->pLivros = InsereOrdenaLivro(NoEditora->pLivros, livro, pAutor);
	
}

TpAutor *EstruturaLista(TpDescritor &ptr, TpAutor *pAutor)
{
	TpLivro livro; //struct para ler do binário
	FILE *ptrBi = fopen("livros.dat", "rb");
	fread(&livro, sizeof(livro), 1, ptrBi);
	while(!feof(ptrBi))
	{
		pAutor = InsereListaAutor(pAutor, livro.autores); //insere sobrenome e nome na lista pAutor
		InsereOrdenaEditora(ptr, livro, pAutor);
		
		fread(&livro, sizeof(livro), 1, ptrBi);
	}
	gotoxy(39, 7);printf("QUANTIDADE DE EDITORAS: %d\n", ptr.qtd);
	return pAutor;
}

int ValidaNome(char nome[200])
{
	int i = 0;
	while(i < strlen(nome) && (nome[i] < 65 || nome[i] > 122))
		i++;
	if(i < strlen(nome) && stricmp(nome, "\0") != 0)
		return i;
	return -1;
}

void FormataNome(char resultado[150], char nome[100], char sobrenome[100])
{
	strupr(sobrenome);
	strcat(sobrenome, ", ");
	strcpy(resultado, sobrenome);
	strcat(resultado, nome);
	strcat(resultado, "; ");
}

void AutorAlterado(TpLivro &auxLivro, TpAutor auxAutor, TpAutor autorAltera)
{
	int i;
	char autorAlterado[150], nome[100], sobrenome[100], resultado[150], autorAux[150] = "";
	
	for(i = 0; i < strlen(auxLivro.autores); i++)
	{
		pegaAutor(auxLivro.autores, i, sobrenome, nome);
		if(stricmp(auxAutor.nome, nome) == 0 && stricmp(auxAutor.sobrenome, sobrenome) == 0)
		{
			strcpy(nome, autorAltera.nome);
			strcpy(sobrenome, autorAltera.sobrenome);
		}
		FormataNome(resultado, nome, sobrenome);
		strcat(autorAux, resultado);
	}
	i = strlen(autorAux) - 2;
	autorAux[i] = '\0';
	strcpy(auxLivro.autores, autorAux);
}

void BuscaNoArquivoBinarioAutor(FILE *ptr, TpAutor autor, TpAutor autorAltera)
{
	rewind(ptr);
	int i, pos, j = 0, fimArquivo;
	char nome[100], sobrenome[100];
	TpLivro aux;
	fseek(ptr, 0, 2);
	i = ftell(ptr);
	fimArquivo = i /sizeof(aux);
	
	rewind(ptr);
	
	fread(&aux, sizeof(aux), 1, ptr);
	j = 0;
	while(j < fimArquivo)
	{
		//pos = ftell(ptr) - sizeof(aux);
		for(i = 0; i < strlen(aux.autores); i++)
		{
			pegaAutor(aux.autores,i,sobrenome,nome);
			if(stricmp(autor.nome, nome) == 0 && stricmp(autor.sobrenome, sobrenome) == 0 && aux.statusLivro == 'A')
			{
				AutorAlterado(aux, autor, autorAltera);
				pos = ftell(ptr) - sizeof(aux);
				fseek(ptr, pos, 0);
				fwrite(&aux, sizeof(aux), 1, ptr);
				fseek(ptr, pos + sizeof(aux), 0);
			}
		}	
		fread(&aux, sizeof(aux), 1, ptr);
		j++;
	}

}

void ExibeBinario(FILE *ptr)
{
	rewind(ptr);
	TpLivro aux;
	
	fread(&aux, sizeof(aux), 1, ptr);
	while(!feof(ptr))
	{
		if(aux.statusLivro == 'A')
			printf("AUTOR(ES): %s - EDITORA: %s - TITULO: %s - ANO: %d - PAGINAS: %d\n" , aux.autores, aux.editora, aux.titulo, aux.ano, aux.paginas);
		fread(&aux, sizeof(aux), 1, ptr);
	}
}

TpLivros *BuscaLivroNaLista(TpDescritor ptr, char titulo[150])
{
	TpDescritor aux = ptr;
	while(aux.inicio != NULL && stricmp(aux.inicio->pLivros->titulo, titulo) != 0)
	{
		while(aux.inicio->pLivros != NULL && stricmp(aux.inicio->pLivros->titulo,titulo) != 0)
			aux.inicio->pLivros = aux.inicio->pLivros->prox;
		aux.inicio = aux.inicio->prox;
	}
	if(aux.inicio != NULL)
		return aux.inicio->pLivros;
	return NULL;
}

int ExcluirLivro(TpEditora *ptr, char titulo[150])
{
	
	int flag = 1;
	TpEditora *auxPtr = ptr;
	TpLivros *aux, *ant;
	LimpaTela();
	while(auxPtr != NULL && flag == 1)
	{
		LimpaMensagem();
		aux = auxPtr->pLivros;
		ant = NULL;
		while(aux != NULL && stricmp(aux->titulo, titulo) != 0)
		{
			ant = aux;
			aux = aux->prox;
		}
		if(aux == NULL)
		{
			gotoxy(29, 10);printf("TITULO NAO EXISTE NA EDITORA: %s!!!\n", auxPtr->editora);
		}
		else
		{
			if(ant == NULL) // O livro a ser excluído é o primeiro na lista de livros da editora
				auxPtr->pLivros = aux->prox;
			else
				ant->prox = aux->prox;
			delete(aux);
			gotoxy(29,12);printf("TITULO: [%s] DELETADO COM SUCESSO!\n", titulo);
			flag = 0;
		}
		auxPtr = auxPtr->prox;
	}
	if(flag == 1)
	{
		LimpaTela();
		gotoxy(29,10);printf("### TITULO [%s] NAO EXISTE!!! ###", titulo);
		getch();
		return -1;
	}
	return 1;
}

int BuscaTitulo(FILE *ptr,char titulo[150])
{
	TpLivro aux;
	fread(&aux, sizeof(aux), 1, ptr);
	while(!feof(ptr) && stricmp(aux.titulo, titulo) != 0)
		fread(&aux, sizeof(aux), 1, ptr);
	if(!feof(ptr) && aux.statusLivro == 'A')
		return ftell(ptr) - sizeof(aux);
	return -1;
}

void ExcluirLivroBinario(char titulo[150])
{
	int pos;
	TpLivro livro;
	FILE *ptr = fopen("livros.dat", "rb+");
	LimpaTela();
	gotoxy(29, 10);printf("### EXCLUSAO LOGICA DO LIVRO ###\n");
	if(ptr == NULL)
	{
		gotoxy(16,7);printf("ERRO DE ABERTURA!!!\n");
	}
	else
	{
		pos = BuscaTitulo(ptr, titulo);
		if(pos == -1)
		{
			gotoxy(29,12);printf("### O TITULO SELECIONADO NAO EXISTE!!! ###\n");
		}
		else
		{
			fseek(ptr, pos, 0);
			fread(&livro, sizeof(livro), 1, ptr);
			livro.statusLivro = 'I';
			fseek(ptr, pos, 0);
			fwrite(&livro, sizeof(livro), 1, ptr);
			gotoxy(29, 12);printf("LIVRO DELETADO NO ARQUIVO BINARIO E NA LISTA!!!\n");
		}
	}
//	ExibeBinario(ptr);
}

void BuscaNaListaMostrando(TpEditora *ptr, char nome[100], char sobrenome[100], int &coluna)
{
    TpEditora *aux = ptr;
    TpLivros *auxPLivros;
    TpLAutor *auxPLAutor;
    TpAutor *auxPAutor;
    while(aux != NULL)
    {
        auxPLivros = aux->pLivros;
        while(auxPLivros != NULL)
        {
            auxPLAutor = auxPLivros->pListaAutor;
            while(auxPLAutor != NULL)
            {
            	gotoxy(15, coluna);
                auxPAutor = auxPLAutor->pAutor;
                if(stricmp(auxPAutor->nome, nome) == 0 && stricmp(auxPAutor->sobrenome, sobrenome) == 0)
                {
                    	printf("TITULO: %s - ANO: %d - PAGINAS: %d\n", auxPLivros->titulo, auxPLivros->ano, auxPLivros->paginas);
                    	coluna++;
                }
                auxPAutor = auxPAutor->prox;
                auxPLAutor = auxPLAutor->prox;
            }
            auxPLivros = auxPLivros->prox;
        }
        aux = aux->prox;
    }
}

void RelatorioLivrosAutor(TpAutor *pAutor, TpEditora *ptr)
{
	int coluna = 6;
	TpEditora *auxPtr = ptr;
	TpAutor *auxPAutor = pAutor;
	while(auxPAutor != NULL)
	{
		gotoxy(15, coluna);
		coluna++;
		printf("AUTOR: %s %s", auxPAutor->nome, auxPAutor->sobrenome);
		gotoxy(15,coluna);printf("LIVROS:------------------------------------------------");
		coluna++;
		BuscaNaListaMostrando(auxPtr, auxPAutor->nome, auxPAutor->sobrenome, coluna);
		auxPAutor = auxPAutor->prox;
		coluna++;
	}
}

int BuscaNaListaSemLivro(TpEditora *ptr, char nome[100], char sobrenome[100])
{
	int cont = 0;
    TpEditora *aux = ptr;
    TpLivros *auxPLivros;
    TpLAutor *auxPLAutor;
    TpAutor *auxPAutor;
    while(aux != NULL)
    {
        auxPLivros = aux->pLivros;
        while(auxPLivros != NULL)
        {
            auxPLAutor = auxPLivros->pListaAutor;
            while(auxPLAutor != NULL)
            {
                auxPAutor = auxPLAutor->pAutor;
                if(stricmp(auxPAutor->nome, nome) == 0 && stricmp(auxPAutor->sobrenome, sobrenome) == 0)
 					cont++;
                auxPAutor = auxPAutor->prox;
                auxPLAutor = auxPLAutor->prox;
            }
            auxPLivros = auxPLivros->prox;
        }
        aux = aux->prox;
    }
    return cont;
}

void RelatorioLivrosSemAutor(TpAutor *pAutor, TpEditora *ptr)
{
	int cont, cont2 = 0, coluna = 6;
	TpEditora *auxPtr = ptr;
	TpAutor *auxPAutor = pAutor;
	gotoxy(15, coluna);printf("AUTORES SEM LIVRO:\n");
	coluna++;
	while(auxPAutor != NULL)
	{
		cont = BuscaNaListaSemLivro(auxPtr, auxPAutor->nome, auxPAutor->sobrenome);
		if(cont == 0)
		{
			gotoxy(15, coluna),printf("%s %s\n", auxPAutor->nome, auxPAutor->sobrenome);
			coluna++;
			cont2++;
		}
		auxPAutor = auxPAutor->prox;
	}
	if(cont2 == 0)
	{
		gotoxy(15, coluna);printf("NAO HA AUTORES SEM LIVROS!!!\n");
	}
}

void LimpaTelaParaMenu3()
{
	int i;
	gotoxy(38,3); printf("                             ");
	gotoxy(44,4); printf("                ");
	gotoxy(36, 3); printf(" ");
	gotoxy(68, 3); printf(" ");
	gotoxy(36, 4); printf(" ");
	gotoxy(68, 4); printf(" ");
	
	LimpaTudo(2,2,101,28);
	LimpaTudo(4,6,99,8);
	LimpaTudo(4,9,26,26);
	LimpaTudo(27,9,99,26);
	    											
}

void LimpaOpcoes()
{
	int coluna;
	for(coluna = 13; coluna <= 19; coluna++)
	{
		gotoxy(7,coluna);printf("										");
	}
}

void LimpaMenu3()
{
	int linha, coluna;
	for(linha = 3;linha < 119; linha++)
	{
		for(coluna = 5; coluna < 83; coluna++)
		{
			gotoxy(linha, coluna);printf(" ");
			
		}
	}
}

void LimpaMenu3Opcoes()
{
	int linha, coluna;
	for(linha = 3;linha < 119; linha++)
	{
		for(coluna = 3; coluna < 83; coluna++)
		{
			gotoxy(linha, coluna);printf(" ");
		}
	}
}

char Menu3(TpDescritor descritor, TpAutor *pAutor)
{
	TpEditora *auxDescritorIni = descritor.inicio;
	TpAutor *auxPAutor = pAutor;
	char itemP[6][100]={"LIVROS DE CADA AUTOR","LIVROS DE CADA EDITORA","AUTORES SEM LIVRO","VOLTAR"}, item2P[6][100]={"RELATORIOS","EXCLUSAO DE LIVRO","ALTERACAO DE NOME","SAIR"};
	int coordP[6][2]={{10,4},{41,4},{75,4},{104,4}}, coord2P[6][2]={{7,13},{7,15},{7,17},{7,19}};
	int i,op=0;
	char tecla, opcao;
	
	LimpaMenu3();
	LimpaTelaParaMenu3();
	
	Bordas(2,2,119,83,6);
	

	for(i=0; i<4; i++)
	{
		gotoxy(coordP[i][0],coordP[i][1]);
		printf("%s",itemP[i]);
	}
	textbackground(1);
	gotoxy(coordP[0][0],coordP[0][1]);
	printf("%s",itemP[0]);
	do 
	{
		tecla=getch();
		if (tecla==-32)
		{
			textbackground(0);
			gotoxy(coordP[op][0],coordP[op][1]);
			printf("%s",itemP[op]);
			tecla=getch();
			switch(tecla)
			{
				case 75:if (op>0)				
							op--;
						break;
				case 77:if (op<3)
							op++;
			}	
			textbackground(1);
			gotoxy(coordP[op][0],coordP[op][1]);
			printf("%s",itemP[op]);
		}
		if (tecla==13)
		{
			textbackground(0);
			LimpaMensagem();
			if (op==0)
			{
				opcao = 'A';
				RelatorioLivrosAutor(auxPAutor, auxDescritorIni);
				getch();
				LimpaMenu3();
			}
			else if (op==1)
			{
				opcao = 'B';
				Exibir(auxDescritorIni);
				getch();
				LimpaMenu3();
			}
			else if (op==2)
			{
				opcao = 'C';
				RelatorioLivrosSemAutor(auxPAutor, auxDescritorIni);
				getch();
				LimpaMenu3();
			}
			else if (op==3)
				opcao = 'D';
		}
	if (tecla==-32)
		{
			textbackground(0);
			gotoxy(coordP[op][0],coordP[op][1]);
			printf("%s",itemP[op]);
			tecla=getch();
			switch(tecla)
			{
				case 75:if (op>0)				
							op--;
						break;
				case 77:if (op<3)
							op++;
			}	
			textbackground(1);
			gotoxy(coordP[op][0],coordP[op][1]);
			printf("%s",itemP[op]);
		}			
	}while(opcao != 'D');
	LimpaTudo(2,2,119,83);
	LimpaMenu3Opcoes();
	Moldura();
	for(i=0; i<4; i++)
	{
		gotoxy(coord2P[i][0],coord2P[i][1]);
		printf("%s",item2P[i]);
	}
}


char Menu2(TpDescritor descritor, TpAutor *pAutor)
{
	TpEditora auxEditora, auxDeleta, *auxDescritorIni = descritor.inicio, auxPlivros;
	TpDescritor auxMain, aux2Descritor = descritor;
	TpLivro auxLivro;
	TpAutor auxAutor, auxAutorAltera, *auxPAutor = pAutor;
	TpLivros auxLivro2, *auxPtrLivros;
	FILE *ptrAlteracao = fopen("livros.dat", "rb+");
	TpAutor *altera, *novo;
	char itemP[6][100]={"RELATORIOS","EXCLUSAO DE LIVRO","ALTERACAO DE NOME","SAIR"}, tecla, opcao2, resposta, resposta2;
	int coordP[6][2]={{7,13},{7,15},{7,17},{7,19}},i,op=0, opcao, listaDel;
	
	LimpaTela();
	Moldura();
	
	for(i=0; i<4; i++)
	{
		gotoxy(coordP[i][0],coordP[i][1]);
		printf("%s",itemP[i]);
	}
	textbackground(1);
	gotoxy(coordP[0][0],coordP[0][1]);
	printf("%s",itemP[0]);
	do 
	{
		tecla=getch();
		if (tecla==-32)
		{
			textbackground(0);
			gotoxy(coordP[op][0],coordP[op][1]);
			printf("%s",itemP[op]);
			tecla=getch();
			switch(tecla)
			{
				case 72:if (op>0)				
							op--;
						break;
				case 80:if (op<3)
							op++;
			}	
			textbackground(1);
			gotoxy(coordP[op][0],coordP[op][1]);
			printf("%s",itemP[op]);
		}
		if (tecla==13)
		{
			textbackground(0);
			LimpaMensagem();
			if (op==0)
			{
				opcao2 = 'A';
				Menu3(descritor, pAutor);
			}
			else if (op==1)
			{
				opcao2 = 'B';
				//EXCLUIR LIVRO
				gotoxy(29, 10);printf("### EXCLUSAO DE LIVRO ###");
				gotoxy(29, 12);printf("DIGITE O TITULO DO LIVRO A SER EXCLUIDO:");
				fflush(stdin);
				gotoxy(29, 14);gets(auxLivro2.titulo);
				while(ValidaNome(auxLivro2.titulo) == -1)
				{
					LimpaTela();
					gotoxy(16,7);printf("TITULO INVALIDO!!!");
					gotoxy(29,10);printf("DIGITE OUTRO TITULO PARA SER EXCLUIDO:");
					fflush(stdin);
					gotoxy(29,12);gets(auxLivro2.titulo);
				}
				LimpaMensagem();
				gotoxy(29, 14);printf("NOME DO TITULO DIGITADO: %s\n", auxLivro2.titulo);
				
					gotoxy(29, 16);printf("DESEJA REALMENTE EXCLUIR ESSE LIVRO? (S/N)");
					fflush(stdin);
					gotoxy(29, 18); resposta2 = toupper(getche());
					while(resposta2 != 'S' && resposta2 != 'N')
					{
						gotoxy(16, 7);printf("RESPOSTA INVALIDA!!!");
						fflush(stdin);
						gotoxy(29, 20);resposta2 = toupper(getche());
					}
					LimpaMensagem();
					if(resposta2 == 'S')
					{
						LimpaMensagem();
						listaDel = ExcluirLivro(auxDescritorIni, auxLivro2.titulo); //somente para saber se foi possivel excluir para aparecer a mensagem
						ExcluirLivroBinario(auxLivro2.titulo); //EXCLUSÃO LÓGICA NO ARQUIVO BINÁRIO
						LimpaTela();
						if(listaDel == 1)
						{
							gotoxy(16, 7);printf("### EXCLUSAO REALIZADA!!! ###");
						}
						else
						{
							gotoxy(16,7);printf("### EXCLUSAO NAO REALIZADA POR INVALIDACAO DOS DADOS!!! ###");
						}
					}
			}
			else if (op==2)
			{
				opcao2 = 'C';
				//ALTERAÇÃO DE NOME E SOBRENOME
				gotoxy(29, 10);printf("### ALTERACAO DE NOME E SOBRENOME AUTOR ###");
				if(ptrAlteracao == NULL)
				{
					gotoxy(29, 12);printf("Erro de abertura");
				}
				else
				{
					gotoxy(29, 12);printf("Digite o nome para ser alterado:");
					fflush(stdin);
					gotoxy(29, 14);gets(auxAutor.nome);
					while(ValidaNome(auxAutor.nome) == -1)
					{
						LimpaTela();
						gotoxy(16,7);printf("NOME INVALIDO!");
						gotoxy(29, 10);printf("DIGITE OUTRO NOME:");
						fflush(stdin);
						gotoxy(29, 12);gets(auxAutor.nome);
					}
					LimpaMensagem();
					gotoxy(29, 14);printf("Digite o sobrenome tambem:");
					fflush(stdin);
					gotoxy(29, 16);gets(auxAutor.sobrenome);
					while(ValidaNome(auxAutor.sobrenome) == -1)
					{
						gotoxy(16, 7);printf("SOBRENOME INVALIDO!");
						gotoxy(29, 18);printf("DIGITE OUTRO SOBRENOME:");
						fflush(stdin);
						gotoxy(29, 20);gets(auxAutor.sobrenome);
					}
					LimpaMensagem();
					altera = BuscaAutor(auxPAutor, auxAutor);
					while(altera == NULL)
					{
						LimpaTela();
						gotoxy(29, 10);printf("### NOMES NAO EXISTEM!!! ###");
						gotoxy(29, 12);printf("Digite o nome para ser alterado:");
						fflush(stdin);
						gotoxy(29, 14);gets(auxAutor.nome);
						while(ValidaNome(auxAutor.nome) == -1)
						{
							LimpaTela();
							gotoxy(29, 10);printf("NOME INVALIDO!\n");
							fflush(stdin);
							gotoxy(29, 12);gets(auxAutor.nome);
						}
						gotoxy(29, 14);printf("Digite o sobrenome tambem:");
						fflush(stdin);
						gotoxy(29, 16);gets(auxAutor.sobrenome);
						while(ValidaNome(auxAutor.sobrenome) == -1)
						{
							LimpaTela();
							gotoxy(16, 7);printf("SOBRENOME INVALIDO!");
							fflush(stdin);
							gotoxy(29, 16);gets(auxAutor.sobrenome);
						}
						altera = BuscaAutor(auxPAutor, auxAutor);
					}
					LimpaTela();
					gotoxy(29, 10);printf("DESEJA REALMENTE ALTERAR? (S/N)");
					gotoxy(29, 12);resposta = toupper(getche());
					while(resposta != 'S' && resposta != 'N')
					{
						LimpaTela();
						gotoxy(16, 7);printf("RESPOSTA INVALIDA!!!\n");
						gotoxy(29, 10);printf("DESEJA REALMENTE ALTERAR? (S/N)");
						gotoxy(29, 12);resposta = toupper(getche());
					}
					LimpaMensagem();
					if(resposta == 'S')
					{
						LimpaTela();
						gotoxy(29, 10);printf("Digite o novo nome:");
						fflush(stdin);
						gotoxy(29, 12);gets(auxAutorAltera.nome);
						while(ValidaNome(auxAutorAltera.nome) == -1)
						{
							LimpaTela();
							gotoxy(16, 7);printf("NOME INVALIDO!!!");
							gotoxy(29, 10);printf("DIGITE OUTRO NOME:");
							fflush(stdin);
							gotoxy(29, 12);gets(auxAutorAltera.nome);
						}
						LimpaMensagem();
						gotoxy(29, 14);printf("Digite o novo sobrenome:");
						fflush(stdin);
						gotoxy(29, 16);gets(auxAutorAltera.sobrenome);
						while(ValidaNome(auxAutorAltera.sobrenome) == -1)
						{
							gotoxy(16,7);printf("SOBRENOME INVALIDO!\n");
							gotoxy(29, 14);printf("DIGITE OUTRO SOBRENOME:");
							fflush(stdin);
							gotoxy(29, 16);gets(auxAutorAltera.sobrenome);
						}
						LimpaMensagem();
						while(BuscaAutor(auxPAutor, auxAutorAltera) != NULL) 
						{
							LimpaTela();
							gotoxy(16,7);printf("NOME JA CADASTRADO!!!\n");
							gotoxy(29, 10);printf("Digite outro nome para realizar a alteracao:\n");
							fflush(stdin);
							gotoxy(29, 12);gets(auxAutorAltera.nome);
							while(ValidaNome(auxAutorAltera.nome) == -1)
							{
								LimpaTela();
								gotoxy(16, 7);printf("NOME INVALIDO!\n");
								gotoxy(29, 10);printf("DIGITE OUTRO NOME:\n");
								fflush(stdin);
								gotoxy(29, 12);gets(auxAutorAltera.nome);
							}
							LimpaMensagem();
							gotoxy(29, 14);printf("Digite o sobrenome tambem:\n");
							fflush(stdin);
							gotoxy(29, 16);gets(auxAutorAltera.sobrenome);
							while(ValidaNome(auxAutorAltera.sobrenome) == -1)
							{
								gotoxy(16, 7);printf("SOBRENOME INVALIDO!\n");
								gotoxy(29, 14);printf("DIGITE OUTRO SOBRENOME:\n");
								fflush(stdin);
								gotoxy(29, 16);gets(auxAutorAltera.sobrenome);
							}
							LimpaMensagem();
						}
						if(auxAutorAltera.nome[0] >= 'a' && auxAutorAltera.nome[0] <= 'z')
							auxAutorAltera.nome[0] -= 32;

							strupr(auxAutorAltera.sobrenome);
							strcpy(altera->nome, auxAutorAltera.nome);
							strcpy(altera->sobrenome, auxAutorAltera.sobrenome);
														
							BuscaNoArquivoBinarioAutor(ptrAlteracao, auxAutor, auxAutorAltera);
							
							LimpaTela();
							
							gotoxy(29, 10);printf("---ALTERACAO CONCLUIDA---\n");
					}
				}
			}
			else if (op==3)
				opcao2 = 'D';
		}
		if (tecla==-32)
		{
			textbackground(0);
			gotoxy(coordP[op][0],coordP[op][1]);
			printf("%s",itemP[op]);
			tecla=getch();
			switch(tecla)
			{
				case 72:if (op>0)				
							op--;
						break;
				case 80:if (op<3)
							op++;
			}	
			textbackground(1);
			gotoxy(coordP[op][0],coordP[op][1]);
			printf("%s",itemP[op]);
		}
				
	}while(opcao2 != 'D');
}


int main()
{
	TpAutor *pAutor = NULL;
	TpDescritor descritor;
	InicializaDescritor(descritor);

	LeDadosTxt();
	pAutor = EstruturaLista(descritor, pAutor);
	
	Menu2(descritor, pAutor);
	
	gotoxy(3,30);

	return 0;
}
