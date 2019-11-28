#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

void gotoxy(int x, int y);
void pintar(int cor);
void tela(char nome[30]);
int FazerLogin();
void CardapioPizza();
void CardapioBebidasNaoAlcolicas();
void CardapioBebidasAlcolicas();
void AdicionarCardapioPizza();
void AdicionarCardapioBebidasNaoAlcolicas();
void AdicionarCardapioBebidasAlcolicas();
void CriarPedidos(int z);
void MenuPrincipal(int z);
void TelaAdicionarPizza();
void TelaAdicionarBebidaNaoAlcolica();
void TelaAdicionarBebidaAlcolica();
int TelaLogin();
void TelaCardapio();
void ModificarPizza();
void ModificarBebidaA();
void ModificarBebidaNA();
int relatorio_quantidade();
int contarOcorrencias(FILE *fptr, const char *word);
int relatorio_faturamento();
void devolveMes(int opt, char mes[15]);
int dataAtual();
void TelaModificarCardapio();
void TelaOpsCardapio();
void TelaAdicionarCardapio();
void TelaRelatorio();
void FinalizarPedido();
void PedidosEmAndamento();
void FinalizarPedido();


#endif // HEADERS_H_INCLUDED
