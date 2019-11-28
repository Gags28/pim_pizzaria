#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1000
const int PossicaoColuna=8;
const int COLUNA=80;
const int LINHA=20;


void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);

}

void pintar(int cor){
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, cor);
}

void tela(char nome[30]){
    int x,y;
    pintar(112);
    system("cls");
    pintar(12);
    for(y=0;y<3;y++){
        gotoxy(0,y);
            for(x=0;x<80;x++){
                printf("%c",219);
            }
    }
    pintar(207);
    gotoxy(2,1);
    printf("%s",nome);
    pintar(112);
    //pintar(119);
}

int FazerLogin(){ //Recebe um logim e senha e confirma se esta correto com o logim e a senha previamente escolhida
    char login[255], senha[255], login_confirmar[255], senha_confirmar[255];
    char ops;
    char login_l[255],senha_s[255],senha_confirmar_l[255];
    int OpsLogin=1,OpsLogin1=1,OpsLogin2=1,OpsLogin3=1;
    char nome[8]={'L','o','g','i','n'};
    FILE *log,*sen,*log_g,*sen_g;
    while(OpsLogin!=0){
    tela(nome);
    gotoxy(PossicaoColuna,5);
    printf("O que voce gostaria de fazer?");
    gotoxy(PossicaoColuna,7);
    printf("Login = l");
    gotoxy(PossicaoColuna,9);
    printf("Sair = s");
    gotoxy(PossicaoColuna,11);
    if((log=fopen("bancodedados\\Login\\Login.txt","r")==NULL)||(log_g=fopen("bancodedados\\Login\\LoginGerente.txt","r")==NULL))
    printf("Primeira vez entrando? = p");
    gotoxy(PossicaoColuna,13);
    printf("___");
    gotoxy(PossicaoColuna+1,13);
    scanf(" %c",&ops);
    switch(ops){
        case 'l':
        while(OpsLogin1!=0){
            tela(nome);
            log = fopen("bancodedados\\Login\\Login","r");
            sen = fopen("bancodedados\\Login\\Senha.txt","r");
            log_g = fopen("bancodedados\\Login\\LoginGerente.txt","r");
            sen_g = fopen("bancodedados\\Login\\SenhaGerente.txt","r");
            gotoxy(PossicaoColuna,5);
            printf("Login:");
            gotoxy(PossicaoColuna,7);
            printf("Senha:");
            gotoxy(14,5);
            scanf(" %254s", login);
            gotoxy(14,7);
            scanf(" %254s", senha);
            fgets(login_confirmar,sizeof(login_confirmar), log);
            fgets(senha_confirmar,sizeof(senha_confirmar), sen);
                if(strcmp(login_confirmar,login)==0){
                    if(strcmp(senha_confirmar,senha)==0){
                        fclose(log);
                        fclose(sen);
                        fclose(log_g);
                        fclose(sen_g);
                        OpsLogin1=0;
                        OpsLogin=0;
                        return 3;
                    }
                }
            fgets(login_confirmar,sizeof(login_confirmar), log_g);
            fgets(senha_confirmar,sizeof(senha_confirmar), sen_g);
                if(strcmp(login_confirmar,login)==0){
                    if(strcmp(senha_confirmar,senha)==0){
                        fclose(log);
                        fclose(sen);
                        fclose(log_g);
                        fclose(sen_g);
                        OpsLogin1=0;
                        OpsLogin=0;
                        return 4;
                    }
                }
        }
            break;
        case 's':
            return 10;
            break;
        case 'p':
            log_g=fopen("bancodedados\\Login\\LoginGerente.txt","r");
            if(log_g==NULL){
                log_g=fopen("bancodedados\\Login\\LoginGerente.txt","w+");
                sen_g=fopen("bancodedados\\Login\\SenhaGerente.txt","w+");
                while(OpsLogin2==1){
                tela(nome);
                gotoxy(70,1);
                pintar(207);
                printf("Gerente");
                pintar(112);
                gotoxy(PossicaoColuna,5);
                printf("Digite um Login:");
                gotoxy(PossicaoColuna,7);
                printf("Digite uma Senha:");
                gotoxy(PossicaoColuna,9);
                printf("Confirmar Senha:");
                gotoxy(24,5);
                scanf(" %254s",&login_l);
                gotoxy(25,7);
                scanf(" %254s",&senha_s);
                gotoxy(24,9);
                scanf(" %254s",&senha_confirmar_l);
                if(strcmp(senha_s,senha_confirmar_l)==0){
                    fprintf(log_g,"%s",login_l);
                    fprintf(sen_g,"%s",senha_s);
                    OpsLogin2=0;
                }
                }
                fclose(log_g);
                fclose(sen_g);
                log=fopen("bancodedados\\Login\\Login.txt","w+");
                sen=fopen("bancodedados\\Login\\Senha.txt","w+");
                while(OpsLogin3==1){
                tela(nome);
                gotoxy(70,1);
                pintar(207);
                printf("Gerente");
                pintar(112);
                gotoxy(PossicaoColuna,4);
                printf("Login para funcionarios");
                gotoxy(PossicaoColuna,6);
                printf("Digite um Login:");
                gotoxy(PossicaoColuna,8);
                printf("Digite uma Senha:");
                gotoxy(PossicaoColuna,10);
                printf("Confirmar Senha:");
                gotoxy(24,6);
                scanf(" %254s",&login_l);
                gotoxy(25,8);
                scanf(" %254s",&senha_s);
                gotoxy(24,10);
                scanf(" %254s",&senha_confirmar_l);
                if(strcmp(senha_s,senha_confirmar_l)==0){
                    fprintf(log,"%s",login_l);
                    fprintf(sen,"%s",senha_s);
                    OpsLogin3=0;
                }
                }
                fclose(log);
                fclose(sen);
            }
            break;
        default:
            printf("Opcao invalido.");
        }
    }
}

void CardapioPizza(){ //Mostrar o cardapio de pizzas
	FILE *card,*arq;
    arq=fopen("bancodedados\\Pizza\\IDPizza.txt","r");
    int ops=fgetc(arq);
    int x;
    fclose(arq);
    for(x=1;x<=ops;x++){
        char Pizza[250]={};
        strcpy(Pizza,"bancodedados\\Pizza\\CardapioPizza");
        char Addvariavel[50];
        sprintf(Addvariavel,"%d",x);
        strcat(Pizza,&Addvariavel);
        strcat(Pizza,".txt");
        card=fopen(Pizza,"r");
        char frase[sizeof(card)];
            while(fgets(frase,sizeof(frase),card)!= NULL){
                printf("%s",frase);
        }
        fclose(card);
    }
}

void CardapioBebidasNaoAlcolicas(){ //Mostrar o cardapio de bebidas nao alcolicas
	FILE *card,*arq;
    arq=fopen("bancodedados\\Bebidas\\BebidaNaoAlcolica\\IDBebidaNA.txt","r");
    int ops=fgetc(arq);
    int x;
    fclose(arq);
    for(x=1;x<=ops;x++){
        char Bebida[250]={};
        strcpy(Bebida,"bancodedados\\Bebidas\\BebidaNaoAlcolica\\CardapioBebidaN");
        char Addvariavel[50];
        sprintf(Addvariavel,"%d",x);
        strcat(Bebida,&Addvariavel);
        strcat(Bebida,".txt");
        card=fopen(Bebida,"r");
        char frase[sizeof(card)];
            while(fgets(frase,sizeof(frase),card)!= NULL){
                printf("%s",frase);
        }
        fclose(card);
    }
}

void CardapioBebidasAlcolicas(){ //Mostrar o cardapio de bebidas alcolicas
	FILE *card,*arq;
    arq=fopen("bancodedados\\Bebidas\\BebidaAlcolica\\IDBebidaA.txt","r");
    int ops=fgetc(arq);
    int x;
    fclose(arq);
    for(x=1;x<=ops;x++){
        char Bebida[250]={};
        strcpy(Bebida,"bancodedados\\Bebidas\\BebidaAlcolica\\CardapioBebidaA");
        char Addvariavel[50];
        sprintf(Addvariavel,"%d",x);
        strcat(Bebida,&Addvariavel);
        strcat(Bebida,".txt");
        card=fopen(Bebida,"r");
        char frase[sizeof(card)];
            while(fgets(frase,sizeof(frase),card)!= NULL){
                printf("%s",frase);
        }
        fclose(card);
    }
}

void AdicionarCardapioPizza(){ //Area de modifica�ao de cardapio que pode ser somente acessada pelo gerente da unidade
	FILE *card,*arq;
    char sabor[25],ingredientes[255];
    char frase[sizeof(card)];
    float Preco;
    int a=1;
    char AdicionarP[50];
    if(arq=fopen("bancodedados\\Pizza\\IDPizza.txt","r")==NULL){
        arq=fopen("bancodedados\\Pizza\\IDPizza.txt","w");
        fputc(1,arq);
        fclose(arq);
    }
    strcpy(AdicionarP,"bancodedados\\Pizza\\CardapioPizza");
    arq=fopen("bancodedados\\Pizza\\IDPizza.txt","r");
    int ops=fgetc(arq);
    fclose(arq);
    char Addvariavel[50];
    sprintf(Addvariavel,"%d",ops);
    strcat(AdicionarP,&Addvariavel);
    strcat(AdicionarP,".txt");
    if(card=fopen(AdicionarP,"r")==NULL){
        card=fopen(AdicionarP,"a");
        fclose(card);
    }
    fclose(card);
    fflush(stdin);
    gotoxy(PossicaoColuna,5);
    printf("Digite o sabor da pizza: ");
    gotoxy(PossicaoColuna,7);
    printf("Digite os ingredientes: ");
    gotoxy(PossicaoColuna,10);
    printf("Digite o preco da pizza");
    gotoxy(PossicaoColuna,11);
    printf("Preco: ");
    gotoxy(PossicaoColuna,6);
    fgets(sabor, 25,stdin);
    gotoxy(PossicaoColuna,8);
    fgets(ingredientes,255,stdin);
    gotoxy(15,11);
    scanf(" %f",&Preco);
    //fprintf(card,"%s",frase) Nao fazer isso, ele adiciona a ultima string salva no txt fazendo ter erro de sintaxe4
    arq=fopen("bancodedados\\Pizza\\IDPizza.txt","r");
    int numero=fgetc(arq);
    fclose(arq);
    card=fopen(AdicionarP,"a");
    fprintf(card,"\t%d Pizza %s",numero,sabor);
    fprintf(card,"\tValor %2.f\n",Preco);
    fprintf(card,"\tIngredientes %s\n",ingredientes);
    fclose(card);
    arq=fopen("bancodedados\\Pizza\\IDPizza.txt","w");
    numero=numero+1 ;
    fputc(numero,arq);
    fclose(arq);
}

void AdicionarCardapioBebidasNaoAlcolicas(){ //Area de modifica�ao de cardapio para as bebidas nao alcolicas que pode ser somente acessada pelo gerente da unidade
	FILE *arq,*BebidasNaoAlcolicas;
    char BebidaNA[25];
    char BebidaNAlco[sizeof(BebidasNaoAlcolicas)];
    float Preco;
    char AdicionarBN[250];
    if(arq=fopen("bancodedados\\Bebidas\\BebidaNaoAlcolica\\IDBebidaNA.txt","r")==NULL){
        arq=fopen("bancodedados\\Bebidas\\BebidaNaoAlcolica\\IDBebidaNA.txt","w");
        fputc(1,arq);
        fclose(arq);
    }
    strcpy(AdicionarBN,"bancodedados\\Bebidas\\BebidaNaoAlcolica\\CardapioBebidaN");
    arq=fopen("bancodedados\\Bebidas\\BebidaNaoAlcolica\\IDBebidaNA.txt","r");
    int ops=fgetc(arq);
    fclose(arq);
    char Addvariavel[50];
    sprintf(Addvariavel,"%d",ops);
    strcat(AdicionarBN,&Addvariavel);
    strcat(AdicionarBN,".txt");
    if(BebidasNaoAlcolicas=fopen(AdicionarBN,"r")==NULL){
        BebidasNaoAlcolicas=fopen(AdicionarBN,"a");
        fclose(BebidasNaoAlcolicas);
    }
    fflush(stdin);
    gotoxy(PossicaoColuna,5);
    printf("Digite o nome da bebida NAO alcolica: ");
    gotoxy(PossicaoColuna,7);
    printf("Digite o preco da bebida:");
    gotoxy(PossicaoColuna,6);
    fgets(BebidaNA,25,stdin);
    gotoxy(PossicaoColuna,8);
    scanf(" %f",&Preco);
    //fprintf(BebidasNaoAlcolicas,"%s",Bebida) Nao fazer isso, ele adiciona a ultima string salva no txt fazendo ter erro de sintaxe
    arq=fopen("bancodedados\\Bebidas\\BebidaNaoAlcolica\\IDBebidaNA.txt","r");
    int numero=fgetc(arq);
    fclose(arq);
    BebidasNaoAlcolicas=fopen(AdicionarBN,"a");
    fprintf(BebidasNaoAlcolicas,"\t%d Bebida %s \tValor %.2f\n",numero,BebidaNA,Preco);
    fclose(BebidasNaoAlcolicas);
    arq=fopen("bancodedados\\Bebidas\\BebidaNaoAlcolica\\IDBebidaNA.txt","w");
    numero=numero+1 ;
    fputc(numero,arq);
    fclose(arq);
}

void AdicionarCardapioBebidasAlcolicas(){ //Area de modifica�ao de cardapio de bebidas alcolicas que pode ser somente acessada pelo gerente da unidade
    FILE *arq,*BebidasAlcolicas;
    char BebidaA[25];
    char BebidaAlco[sizeof(BebidasAlcolicas)];
    float Preco;
    char AdicionarB[250];
    if(arq=fopen("bancodedados\\Bebidas\\BebidaAlcolica\\IDBebidaA.txt","r")==NULL){
        arq=fopen("bancodedados\\Bebidas\\BebidaAlcolica\\IDBebidaA.txt","w");
        fputc(1,arq);
        fclose(arq);
    }
    strcpy(AdicionarB,"bancodedados\\Bebidas\\BebidaAlcolica\\CardapioBebidaA");
    arq=fopen("bancodedados\\Bebidas\\BebidaAlcolica\\IDBebidaA.txt","r");
    int ops=fgetc(arq);
    fclose(arq);
    char Addvariavel[50];
    sprintf(Addvariavel,"%d",ops);
    strcat(AdicionarB,&Addvariavel);
    strcat(AdicionarB,".txt");
    if(BebidasAlcolicas=fopen(AdicionarB,"r")==NULL){
        BebidasAlcolicas=fopen(AdicionarB,"a");
        fclose(BebidasAlcolicas);
    }
    fflush(stdin);
    gotoxy(PossicaoColuna,5);
    printf("Digite o nome da bebida alcolica: ");
    gotoxy(PossicaoColuna,7);
    printf("Digite o preco da bebida:");
    gotoxy(PossicaoColuna,6);
    fgets(BebidaA,25,stdin);
    gotoxy(PossicaoColuna,8);
    scanf(" %f",&Preco);
    //fprintf(BebidasAlcolicas,"%s",Bebida) Nao fazer isso, ele adiciona a ultima string salva no txt fazendo ter erro de sintaxe
    arq=fopen("bancodedados\\Bebidas\\BebidaAlcolica\\IDBebidaA.txt","r");
    int numero=fgetc(arq);
    fclose(arq);
    BebidasAlcolicas=fopen(AdicionarB,"a");
    fprintf(BebidasAlcolicas,"\t%d Bebida %s \tValor %.2f\n",numero,BebidaA,Preco);
    fclose(BebidasAlcolicas);
    arq=fopen("bancodedados\\Bebidas\\BebidaAlcolica\\IDBebidaA.txt","w");
    numero=numero+1 ;
    fputc(numero,arq);
    fclose(arq);
}

void CriarPedidos(int z){
    FILE *arq;
    int ops,x=0;
    char nome[15]={'C','r','i','a','r',' ','p','e','d','i','d','o'};
    tela(nome);
    if(x==1){
        gotoxy(PossicaoColuna,4);
        printf("Opcao invalida");
    }
    gotoxy(PossicaoColuna,5);
    printf("O que deseja fazer");
    gotoxy(PossicaoColuna,7);
    printf("0.Voltar");
    gotoxy(PossicaoColuna,9);
    printf("1.Criar novo pedido");
    gotoxy(PossicaoColuna,11);
    printf("2.Pedidos em andamento");
    gotoxy(PossicaoColuna,13);
    printf("3.Finalizar pedido");
    gotoxy(PossicaoColuna,14);
    printf("___");
    gotoxy(PossicaoColuna+1,14);
    scanf("%d",&ops);
    switch(ops){
        case 0:
            MenuPrincipal(z);
        break;
        case 1:
            NovoPedido();
        break;
        case 2:
            PedidosEmAndamento();
        break;
        case 3:
            FinalizarPedido();
        break;
        default:
            x=1;

    }

}

void MenuPrincipal(int z){ //Menu principal para e sele�ao da fanquia
    int ops1=1,x=1;
    char  ops,nome[15]={'M','e','n','u',' ','P','r','i','n','c','i','p','a','l'};
    do{
    tela(nome);
    if(x==0){
    gotoxy(PossicaoColuna*3,4);
    printf("Opcao invalida");
    x=1;
    }
    gotoxy(PossicaoColuna*2,5);
    printf("Bem vindo a Pizzaria Do Ze");
    gotoxy(PossicaoColuna,7);
    printf("1.Cardapio");
    gotoxy(PossicaoColuna,9);
    printf("2.Pedidos");
    gotoxy(PossicaoColuna,11);
    printf("3.Sair");
    if(z == 4){
        gotoxy(PossicaoColuna*5,7);
        printf("4.Modificar Cardapio");
        gotoxy(PossicaoColuna*5,9);
        printf("5.Relatorio");
        gotoxy(PossicaoColuna*5,11);
        printf("6.Impregados");
    }
    gotoxy(PossicaoColuna,13);
    printf("___");
    gotoxy(PossicaoColuna+1,13);
    scanf(" %c", &ops);
        switch(ops){
            case '1':
                TelaCardapio();
            break;
            case '2':
                CriarPedidos(z);
            break;
            case '3':
                return 0;
            break;
            if(z == 4){
            case '4':
                TelaOpsCardapio();
            break;
            case '5':
                TelaRelatorio();
            break;
            case '6':
                //TelaImpregados();//tem que ser feita ainda
            break;
            }
            default:
                x=0;

	  }
	}while(ops1!=0);
}

void TelaAdicionarPizza(){
    char nome[30]={'A','d','i','c','i','o','n','a','r','P','i','z','z','a'};
    char ops= 's';
    do{
    tela(nome);
    AdicionarCardapioPizza();
	gotoxy(PossicaoColuna,13);
	printf("Adiconar mais uma pizza?");
	gotoxy(PossicaoColuna,14);
	printf("Sim = s");
	gotoxy(PossicaoColuna,15);
	printf("Nao = n");
	gotoxy(PossicaoColuna,16);
	printf("___");
    gotoxy(PossicaoColuna+1,16);
	scanf(" %c",&ops);
    }while(ops!='n');
}

void TelaAdicionarBebidaNaoAlcolica(){
    char nome[30]={'A','d','i','c','i','o','n','a','r','B','e','b','i','d','a','N','a','o','A','l','c','o','l','i','c','a'};
    char ops= 's';
    do{
    tela(nome);
    AdicionarCardapioBebidasNaoAlcolicas();
	gotoxy(PossicaoColuna,11);
	printf("Adiconar mais uma Bebida?");
	gotoxy(PossicaoColuna,12);
	printf("Sim = s");
	gotoxy(PossicaoColuna,13);
	printf("Nao = n");
	gotoxy(PossicaoColuna,14);
	printf("___");
	gotoxy(PossicaoColuna+1,14);
	scanf(" %c",&ops);
    }while(ops!='n');
}

void TelaAdicionarBebidaAlcolica(){
    char nome[30]={'A','d','i','c','i','o','n','a','r','B','e','b','i','d','a','A','l','c','o','l','i','c','a'};
    char ops= 's';
	do{
    tela(nome);
    AdicionarCardapioBebidasAlcolicas();
	gotoxy(PossicaoColuna,11);
	printf("Adiconar mais uma Bebida?");
	gotoxy(PossicaoColuna,12);
	printf("Sim = s");
	gotoxy(PossicaoColuna,13);
	printf("Nao = n");
	gotoxy(PossicaoColuna,14);
	printf("___");
	gotoxy(PossicaoColuna+1,14);
	scanf(" %c",&ops);
	}while(ops!='n');
}

int TelaLogin(){
    int x;
    char nome[7]={'L','o','g','i','n'};
    tela(nome);
    x=FazerLogin();
    return x;
}

void TelaCardapio(){//Nao esta funcionando, procurando erro 8/10/2019 6:37, erro encontrado por volta das 3:30
    char nome[10]={'C','a','r','d','a','p','i','o'};
    tela(nome);
    gotoxy(0,5);
    CardapioPizza();
	CardapioBebidasNaoAlcolicas();
	CardapioBebidasAlcolicas();
    system("pause");
}

void ModificarPizza(){//Adicionar o caminho do txt
    FILE *arq;
    int id,ops,id_txt,d=1;
    char confirm[20];
    char sabor[50],ingredientes[255];
    char sabor_txt[50],ingredientes_txt[255],Pizza_txt[10],valor_txt[10],ingred_txt[20];
    float custo;
    float custo_txt;
    char nome[50]={'M','o','d','i','f','i','c','a','r',' ','P','i','z','z','a'};
    tela(nome);
    char Pizza[250]={};
    strcpy(Pizza,"bancodedados\\Pizza\\CardapioPizza");
    gotoxy(0,9);
    CardapioPizza();
    gotoxy(PossicaoColuna,5);
    printf("Qual pizza deseja modificar");
    gotoxy(PossicaoColuna,6);
    printf("ID ____");
    gotoxy(PossicaoColuna+4,6);
    scanf("%i",&id);
    sprintf(confirm,"%d",id);
    strcat(Pizza,&confirm);
    strcat(Pizza,".txt");
    arq = fopen(Pizza,"r");
    fflush(stdin);
    fscanf(arq,"%i",&id_txt);
    fscanf(arq,"%s",Pizza_txt);
    fgets(sabor_txt,"%s",arq);
    fscanf(arq,"%s",valor_txt);
    fscanf(arq,"%f",&custo_txt);
    fscanf(arq,"%s",ingred_txt);
    fgets(ingredientes_txt,"%s",arq);
    fclose(arq);
    while(d==1){
    tela(nome);
    gotoxy(0,16);
    arq = fopen(Pizza,"r");
    char frase[sizeof(arq)];
            while(fgets(frase,sizeof(frase),arq)!= NULL){
                printf("%s",frase);
        }
    fclose(arq);
        int z=1;
        if(z==0){
            gotoxy(PossicaoColuna,4);
            printf("Opcao invalida");
           }
        gotoxy(PossicaoColuna,5);
        printf("O que deseja fazer");
        gotoxy(PossicaoColuna,7);
        printf("0.Voltar");
        gotoxy(PossicaoColuna,9);
        printf("1.Modificar Nome");
        gotoxy(PossicaoColuna,11);
        printf("2.Modificar Preco");
        gotoxy(PossicaoColuna,13);
        printf("3.Modificar ingredientes");
        gotoxy(PossicaoColuna,14);
        printf("___");
        gotoxy(PossicaoColuna+1,14);
        scanf("%i",&ops);
        switch(ops){
            case 0:
                TelaModificarCardapio();
            break;
            case 1:
                arq=fopen(Pizza,"w");
                fflush(stdin);
                tela(nome);
                gotoxy(PossicaoColuna,5);
                printf("Digite o novo nome");
                gotoxy(PossicaoColuna,7);
                printf("__________________");
                gotoxy(PossicaoColuna,7);
                fgets(sabor,sizeof(sabor),stdin);
                fprintf(arq,"\t%d Pizza %s",id_txt,sabor);
                fprintf(arq,"\tValor %2.f\n",custo_txt);
                fprintf(arq,"\tIngredientes %s\n",ingredientes_txt);
                fclose(arq);
            break;
            case 2:
                arq=fopen(Pizza,"w");
                fflush(stdin);
                tela(nome);
                gotoxy(PossicaoColuna,5);
                printf("Digite o novo valor");
                gotoxy(PossicaoColuna,7);
                printf("_________");
                gotoxy(PossicaoColuna,7);
                scanf(" %f",&custo);
                fprintf(arq,"\t%d Pizza %s",id_txt,sabor_txt);
                fprintf(arq,"\tValor %2.f\n",custo);
                fprintf(arq,"\tIngredientes %s\n",ingredientes_txt);
                fclose(arq);
            break;
            case 3:
                arq=fopen(Pizza,"w");
                fflush(stdin);
                tela(nome);
                gotoxy(PossicaoColuna,5);
                printf("Digite os ingredientes ");
                gotoxy(PossicaoColuna,7);
                printf("__________________");
                gotoxy(PossicaoColuna,7);
                fgets(ingredientes,sizeof(ingredientes),stdin);
                fprintf(arq,"\t%d Pizza %s",id_txt,sabor_txt);
                fprintf(arq,"\tValor %2.f\n",custo_txt);
                fprintf(arq,"\tIngredientes %s\n",ingredientes);
                fclose(arq);
                break;
            default:
                z=0;
        }
    }
}

void ModificarBebidaA(){//Adicionar o caminho do txt
    FILE *arq;
    int id,ops,id_txt,d=1;
    char confirm[20];
    char sabor[50];
    char sabor_txt[50],Bebida_txt[10],valor_txt[10];
    float custo;
    float custo_txt;
    char nome[50]={'M','o','d','i','f','i','c','a','r',' ','B','e','b','i','d','a','s'};
    tela(nome);
    char BebidaA[250]={};
    strcpy(BebidaA,"Bebidas\\BebidaAlcolica\\CardapioBebidaA");
    gotoxy(0,9);
    CardapioBebidasAlcolicas();
    gotoxy(PossicaoColuna,5);
    printf("Qual Bebida deseja modificar");
    gotoxy(PossicaoColuna,6);
    printf("ID ____");
    gotoxy(PossicaoColuna+4,6);
    scanf("%i",&id);
    sprintf(confirm,"%d",id);
    strcat(BebidaA,&confirm);
    strcat(BebidaA,".txt");
    arq = fopen(BebidaA,"r");
    fflush(stdin);
    fscanf(arq,"%i",&id_txt);
    fscanf(arq,"%s",Bebida_txt);
    fgets(sabor_txt,"%s",arq);
    fscanf(arq,"%s",valor_txt);
    fscanf(arq,"%f",&custo_txt);
    fclose(arq);
    while(d==1){
    tela(nome);
    gotoxy(0,16);
    arq = fopen(BebidaA,"r");
    char frase[sizeof(arq)];
            while(fgets(frase,sizeof(frase),arq)!= NULL){
                printf("%s",frase);
        }
    fclose(arq);
        int z=1;
        if(z==0){
            gotoxy(PossicaoColuna,4);
            printf("Opcao invalida");
           }
        gotoxy(PossicaoColuna,5);
        printf("O que deseja fazer");
        gotoxy(PossicaoColuna,7);
        printf("0.Voltar");
        gotoxy(PossicaoColuna,9);
        printf("1.Modificar Nome");
        gotoxy(PossicaoColuna,11);
        printf("2.Modificar Preco");
        gotoxy(PossicaoColuna,12);
        printf("___");
        gotoxy(PossicaoColuna+1,12);
        scanf("%i",&ops);
        switch(ops){
            case 0:
                TelaModificarCardapio();
            break;
            case 1:
                arq=fopen(BebidaA,"w");
                fflush(stdin);
                tela(nome);
                gotoxy(PossicaoColuna,5);
                printf("Digite o novo nome");
                gotoxy(PossicaoColuna,7);
                printf("__________________");
                gotoxy(PossicaoColuna,7);
                fgets(sabor,sizeof(sabor),stdin);
                fprintf(arq,"\t%d Bebida %s",id_txt,sabor);
                fprintf(arq,"\tValor %2.f\n",custo_txt);
                fclose(arq);
            break;
            case 2:
                arq=fopen(BebidaA,"w");
                fflush(stdin);
                tela(nome);
                gotoxy(PossicaoColuna,5);
                printf("Digite o novo valor");
                gotoxy(PossicaoColuna,7);
                printf("_________");
                gotoxy(PossicaoColuna,7);
                scanf(" %f",&custo);
                fprintf(arq,"\t%d Bebida %s",id_txt,sabor_txt);
                fprintf(arq,"\tValor %2.f\n",custo);
                fclose(arq);
            break;
            default:
                z=0;
        }
    }
}

void ModificarBebidaNA(){//Adicionar o caminho do txt
    FILE *arq;
    int id,ops,id_txt,d=1;
    char confirm[20];
    char sabor[50];
    char sabor_txt[50],Bebida_txt[10],valor_txt[10];
    float custo;
    float custo_txt;
    char nome[50]={'M','o','d','i','f','i','c','a','r',' ','B','e','b','i','d','a','s'};
    tela(nome);
    char BebidaN[250]={};
    strcpy(BebidaN,"Bebidas\\BebidaNaoAlcolica\\CardapioBebidaN");
    gotoxy(0,9);
    CardapioBebidasNaoAlcolicas();
    gotoxy(PossicaoColuna,5);
    printf("Qual Bebida deseja modificar");
    gotoxy(PossicaoColuna,6);
    printf("ID ____");
    gotoxy(PossicaoColuna+4,6);
    scanf("%i",&id);
    sprintf(confirm,"%d",id);
    strcat(BebidaN,&confirm);
    strcat(BebidaN,".txt");
    arq = fopen(BebidaN,"r");
    fflush(stdin);
    fscanf(arq,"%i",&id_txt);
    fscanf(arq,"%s",Bebida_txt);
    fgets(sabor_txt,"%s",arq);
    fscanf(arq,"%s",valor_txt);
    fscanf(arq,"%f",&custo_txt);
    fclose(arq);
    while(d==1){
    tela(nome);
    gotoxy(0,16);
    arq = fopen(BebidaN,"r");
    char frase[sizeof(arq)];
            while(fgets(frase,sizeof(frase),arq)!= NULL){
                printf("%s",frase);
        }
    fclose(arq);
        int z=1;
        if(z==0){
            gotoxy(PossicaoColuna,4);
            printf("Opcao invalida");
           }
        gotoxy(PossicaoColuna,5);
        printf("O que deseja fazer");
        gotoxy(PossicaoColuna,7);
        printf("0.Voltar");
        gotoxy(PossicaoColuna,9);
        printf("1.Modificar Nome");
        gotoxy(PossicaoColuna,11);
        printf("2.Modificar Preco");
        gotoxy(PossicaoColuna,12);
        printf("___");
        gotoxy(PossicaoColuna+1,12);
        scanf("%i",&ops);
        switch(ops){
            case 0:
                TelaModificarCardapio();
            break;
            case 1:
                arq=fopen(BebidaN,"w");
                fflush(stdin);
                tela(nome);
                gotoxy(PossicaoColuna,5);
                printf("Digite o novo nome");
                gotoxy(PossicaoColuna,7);
                printf("__________________");
                gotoxy(PossicaoColuna,7);
                fgets(sabor,sizeof(sabor),stdin);
                fprintf(arq,"\t%d Bebida %s",id_txt,sabor);
                fprintf(arq,"\tValor %2.f\n",custo_txt);
                fclose(arq);
            break;
            case 2:
                arq=fopen(BebidaN,"w");
                fflush(stdin);
                tela(nome);
                gotoxy(PossicaoColuna,5);
                printf("Digite o novo valor");
                gotoxy(PossicaoColuna,7);
                printf("_________");
                gotoxy(PossicaoColuna,7);
                scanf(" %f",&custo);
                fprintf(arq,"\t%d Bebida %s",id_txt,sabor_txt);
                fprintf(arq,"\tValor %2.f\n",custo);
                fclose(arq);
            break;
            default:
                z=0;
        }
    }
}

int relatorio_quantidade(){
    FILE *fptr;
    int next = 0, opt, temp = 0, j, i;
    char raiz[200], diretorio[200], path[200], pasta[200], word[50], ano[5], mes[12], myfile[200];
    int wCount[32], size_check;
    strcpy(raiz, "bandodedados\\");
    strcpy(pasta, "pedidos\\finalizados\\");
    char pizza[50][200];
    char nome[20]={'P','i','z','z','a','s',' ','m','a','i','s',' ','v','e','n','d','i','d','a','s'};
    strcpy(pizza[0], "calabresa");
    strcpy(pizza[1], "mussarela");
    strcpy(pizza[2], "portuguesa");
    /* Input file path */
    while (next == 0)
    {
        tela(nome);
        gotoxy(PossicaoColuna,5);
        printf("Digite o ANO do relatorio que deseja ver");
        gotoxy(PossicaoColuna,7);
        printf("Ex: 2019");
        gotoxy(PossicaoColuna,9);
        printf("Ano: ____");
        gotoxy(PossicaoColuna+5,9);
        scanf("%s", ano);
        if (ano == 0)
        {
            MenuPrincipal(0);
        }
        size_check = strlen(ano);
        if (size_check == 4)
        {
            next = 1;
        }
        else
        {
            gotoxy(PossicaoColuna,4);
            printf("Valor invalido, digite o valor requisitado ou 0 para sair");
        }
    }
    next = 0;
    while (next == 0)
    {
        tela(nome);
        gotoxy(PossicaoColuna,5);
        printf("Escolhe o mes que deseja ver");
        gotoxy(PossicaoColuna,7);
        printf("0 - Sair");
        gotoxy(PossicaoColuna,9);
        printf("1 - Janeiro");
        gotoxy(PossicaoColuna,11);
        printf("2 - Fevereiro");
        gotoxy(PossicaoColuna,13);
        printf("3 - Marco");
        gotoxy(PossicaoColuna,15);
        printf("4 - Abril");
        gotoxy(PossicaoColuna,17);
        printf("5 - Maio");
        gotoxy(PossicaoColuna*3,7);
        printf("6 - Junho");
        gotoxy(PossicaoColuna*3,9);
        printf("7 - Julho");
        gotoxy(PossicaoColuna*3,11);
        printf("8 - Agosto");
        gotoxy(PossicaoColuna*3,13);
        printf("9 - Setembro");
        gotoxy(PossicaoColuna*3,15);
        printf("10 - Outubro");
        gotoxy(PossicaoColuna*3,17);
        printf("11 - Novembro");
        gotoxy(PossicaoColuna*5 ,7);
        printf("12 - Dezembro");
        gotoxy(PossicaoColuna,18);
        printf("___");
        gotoxy(PossicaoColuna+1,18);
        scanf("%d", &opt);
        if (opt >= 1 && opt <= 12)
        {
            next = 1;
        }
        else
        {
            gotoxy(PossicaoColuna,4);
            printf("Valor invalido, pro favor selecione uma opcao valida");
        }
    }
    devolveMes(opt, mes);

    strcpy(diretorio, raiz);
    strcat(diretorio, pasta);
    strcat(diretorio, ano);
    strcat(diretorio, "\\");
    strcat(diretorio, mes);

    if (fptr == NULL)
    {
        exit(EXIT_FAILURE);
    }

     for(j = 0; j < 3; j++ ){
        wCount[j] = 0;
        if(pizza[j] != NULL){
            printf("\nBuscando pizzas");
            system("cls");
            for(i = 0; i < 32; i++){
                strcpy(path, diretorio);
                snprintf(myfile, 30, "\\produto\\%d.txt", i);
                strcat(path, myfile);
                fptr = fopen(path, "r");
                if(fptr != NULL){
                    temp = contarOcorrencias(fptr, pizza[j]);
                    wCount[j] =  wCount[j] + temp;
                }
            }
        }
     }
     // Close file
    fclose(fptr);
    tela(nome);
    gotoxy(PossicaoColuna,5);
    printf("Relatorio de Pizzas vendidas no mes de %s de %s", mes, ano);

    for(j = 0; j < 3; j++){
        gotoxy(PossicaoColuna,5+j);
        printf("'pizza de %s': %d", pizza[j], wCount[j]);
    }


    return 0;
}

/**
 * Returns total occurrences of a word in given file.
 */
int contarOcorrencias(FILE *fptr, const char *word){
    char str[BUFFER_SIZE];
    char *pos;

    int index, count;

    count = 0;

    // Read line from file till end of file.
    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        index = 0;

        // Find next occurrence of word in str
        while ((pos = strstr(str + index, word)) != NULL)
        {
            // Index of word in str is
            // Memory address of pos - memory
            // address of str.
            index = (pos - str) + 1;

            count++;
        }
    }

    return count;
}

int relatorio_faturamento(){
    float salarios = 1000.00, despesas, venda_pizzas, lucro_dia[32], ganho_total = 0, gastos, gastos_dia[32];
    double temp_gastos;
    char data[10], ano[4], mes[15];
    int size_check, opt, next = 0, i = 0, close = 1, dia_find[50];
    char raiz[200], banco[200], pasta[200], file_name[100], conteudo[200], ch[200], cha, aux[300], gastos_estoque[1000], temp[300], nome_pizza[300];
    FILE *file;
    strcpy(pasta, "relatorios\\");
    strcpy(raiz, "bancodedados\\");
    strcpy(banco, raiz);
    strcat(banco, pasta);
    char nome[15]={'F','a','t','u','r','a','m','e','n','t','o'};
    tela(nome);
    int x=0;
    for (i = 0; i < 50; i++)
    {
        dia_find[i] = 1;
    }

    while (next == 0)
    {
        gotoxy(PossicaoColuna,5);
        printf("Digite o ANO do relatorio que deseja ver");
        gotoxy(PossicaoColuna,7);
        printf("Ex: 2019");
        gotoxy(PossicaoColuna,9);
        printf("Ano: ____");
        gotoxy(PossicaoColuna+5,9);
        scanf("%s", ano);
        if (ano == 0)
        {
            //CHAMA FUN�AO PARA SAIR
        }
        size_check = strlen(ano);
        if (size_check == 4)
        {
            next = 1;
        }
        else
        {
            gotoxy(PossicaoColuna,4);
            printf("Valor invalido, digite o valor requisitado ou 0 para sair");
        }
    }

    next = 0;
    while (close != 0)
    {

        while (next == 0)
        {
            tela(nome);
            gotoxy(PossicaoColuna,5);
            printf("Escolhe o mes que deseja ver");
            gotoxy(PossicaoColuna,7);
            printf("0 - Sair");
            gotoxy(PossicaoColuna,9);
            printf("1 - Janeiro");
            gotoxy(PossicaoColuna,11);
            printf("2 - Fevereiro");
            gotoxy(PossicaoColuna,13);
            printf("3 - Marco");
            gotoxy(PossicaoColuna,15);
            printf("4 - Abril");
            gotoxy(PossicaoColuna,17);
            printf("5 - Maio");
            gotoxy(PossicaoColuna*3,7);
            printf("6 - Junho");
            gotoxy(PossicaoColuna*3,9);
            printf("7 - Julho");
            gotoxy(PossicaoColuna*3,11);
            printf("8 - Agosto");
            gotoxy(PossicaoColuna*3,13);
            printf("9 - Setembro");
            gotoxy(PossicaoColuna*3,15);
            printf("10 - Outubro");
            gotoxy(PossicaoColuna*3,17);
            printf("11 - Novembro");
            gotoxy(PossicaoColuna*5 ,7);
            printf("12 - Dezembro");
            gotoxy(PossicaoColuna,18);
            printf("___");
            gotoxy(PossicaoColuna+1,18);
            scanf("%d", &opt);
            if (opt >= 1 && opt <= 12)
            {
                next = 1;
            }
            else
            {
                gotoxy(PossicaoColuna,4);
                printf("Valor invalido, pro favor selecione uma opcao valida");
            }
        }
        devolveMes(opt, mes);
        char diretorio[30];
        char diretorio2[50];
        char diretorio3[300];
        char path[300];
        strcpy(diretorio, "\\");
        strcpy(diretorio2, ano);
        strcpy(diretorio3, banco);
        strcat(diretorio, mes);
        strcat(diretorio2, diretorio);
        strcat(diretorio3, diretorio2);

        DIR *dir = opendir(diretorio3);
        if (dir)
        {
            /* Directory exists. */
            memset(diretorio, 0, sizeof diretorio);

            strcpy(pasta, "estoque\\");
            strcpy(banco, raiz);
            strcat(banco, pasta);
            strcpy(diretorio, banco);
            strcat(diretorio, "gastos\\");
            strcat(diretorio, ano);
            strcat(diretorio, "\\");
            strcat(diretorio, mes);
            strcpy(path, diretorio);
            int x = 0;
            char myfile[200];
            for (i = 0; i < 32; i++)
            {

                strcpy(diretorio, path);
                snprintf(myfile, 12, "\\%d.txt", i);
                strcat(diretorio, myfile);
                file = fopen(diretorio, "r");
                if (file != NULL)
                {
                    dia_find[i] = 0;
                    while (!feof(file))
                    {
                        //                       gastos_dia[i] = 0.00;
                        fscanf(file, "%lf", &temp_gastos);
                        gastos = gastos + temp_gastos;
                        //                        gastos_dia[i] = gastos_dia[i] + temp_gastos;
                    }
                }
            }

            fclose(file);

            memset(diretorio, 0, sizeof diretorio);
            strcpy(pasta, "relatorios\\");
            strcpy(banco, raiz);
            strcat(banco, pasta);
            strcpy(diretorio, banco);
            strcat(diretorio, ano);
            strcat(diretorio, "\\");
            strcat(diretorio, mes);
            strcpy(file_name, "\\despesas.txt");
            strcat(diretorio, file_name);
            file = fopen(diretorio, "r");
            if (file == NULL)
            {
                gotoxy(PossicaoColuna,4);
                perror("Não foi possivel abrir o arquivo de despesas.\n");
                exit(EXIT_FAILURE);
            }
            while (fgets(ch, sizeof(ch), file) != NULL)
            {
                strcmp(aux[i], ch);
                i++;
            }
            fclose(file);

            memset(diretorio, 0, sizeof diretorio);
            strcpy(pasta, "pedidos\\finalizados\\");
            strcpy(banco, raiz);
            strcat(banco, pasta);
            strcpy(diretorio, banco);
            strcat(diretorio, ano);
            strcat(diretorio, "\\");
            strcat(diretorio, mes);
            strcpy(path, diretorio);

            for (i = 0; i < 32; i++)
            {
                strcpy(diretorio, path);
                snprintf(myfile, 20, "\\valor\\%d.txt", i);
                strcat(diretorio, myfile);
                file = fopen(diretorio, "r");
                lucro_dia[i] = 0.00;
                if (file != NULL)
                {
                    dia_find[i] = 0;
                    while (!feof(file))
                    {
                        fscanf(file, "%f", &venda_pizzas);
                        lucro_dia[i] = lucro_dia[i] + venda_pizzas;
                        ganho_total = ganho_total + venda_pizzas;
                        // gastos_dia[i] = gastos_dia[i] + temp_gastos;
                    }
                }
            }

            fclose(file);

            despesas = atof(ch);
            gastos = gastos + despesas + salarios;
            fclose(file);
            tela(nome);
            gotoxy(PossicaoColuna,5);
            printf("Relatorio de gastos do ano de %s do mes de %s", ano, mes);
            gotoxy(PossicaoColuna,7);
            printf("Lucro total do mes: %.2f", ganho_total - gastos);
            gotoxy(PossicaoColuna,9);
            printf("Faturamento total do mes: %.2f", ganho_total);
            gotoxy(PossicaoColuna,11);
            printf("Gasto total do mes: %.2f", gastos);
            int count = 0;
            int achou_relatorio = 0;
            for (i = 1; i < 32; i++)
            {
                if (dia_find[i] == 0)
                {
                    count++;
                }
            }

            for (i = 1; i < 32; i++)
            {
                if (dia_find[i] == 0)
                {
                    achou_relatorio = 1;
                    gotoxy(PossicaoColuna,14+x);
                    if((lucro_dia[i] = lucro_dia[i] - gastos / count)>0){
                        printf("dia %d: R$%.2f", i, lucro_dia[i] = lucro_dia[i] - gastos / count);
                        x++;
                    }
                }
                // gastos_dia[i] = 0.00;
            }

            if (achou_relatorio == 0)
            {
                gotoxy(PossicaoColuna,4);
                printf("Nao foi encontrado nenhuma pedido feito no mes de %s de %s", mes, ano);
            }
            gotoxy(PossicaoColuna,12);
            printf("Digite 0 para sair ou 1 para repetir");
            gotoxy(PossicaoColuna,13);
            printf("___");
            gotoxy(PossicaoColuna+1,13);
            scanf("%d", &close);
            if (close == 1)
            {
                next = 0;
            }
        }
        else if (ENOENT == errno)
        {
            /* Directory does not exist. */
            tela(nome);
            gotoxy(PossicaoColuna,5);
            printf("Este relatorio ainda nao foi criado,");
            gotoxy(PossicaoColuna,6);
            printf("por favor informe as despesas do mes de %s para que possa continuar.",mes);
            gotoxy(PossicaoColuna,8);
            printf("As depesas referenciadas sao a soma de gastos como");
            gotoxy(PossicaoColuna,9);
            printf("agua, luz, gas, internet, aluguel entre outros que achar necessario.");
            gotoxy(PossicaoColuna,11);
            printf("ATENCAO: nao incluir salarios de seus funcionarios nesta conta,");
            gotoxy(PossicaoColuna,12);
            printf("pois os mesmo sao pegos de seus cadastros.");
            gotoxy(PossicaoColuna,14);
            printf("Despesas : ");
            gotoxy(PossicaoColuna+10,14);
            scanf("%f", &despesas);

            if (despesas > 0)
            {

                memset(diretorio, 0, sizeof diretorio);
                strcpy(diretorio, banco);
                strcat(diretorio, ano);
                int dire;
                DIR *dir = opendir(diretorio);
                if (dir)
                {
                    strcat(diretorio, "\\");
                    strcat(diretorio, mes);
                    dire = mkdir(diretorio);
                    //diretorio criado
                }
                else
                {
                    //cria diretorio para o ano quando ele nao existe
                    dire = mkdir(diretorio);
                    if (!dire)
                    {
                        strcat(diretorio, "\\");
                        strcat(diretorio, mes);
                        int dire;
                        dire = mkdir(diretorio);
                    }
                    else
                    {
                        gotoxy(PossicaoColuna,4);
                        printf("Nao foi possivel criar os diretorios necessarios %s", diretorio);
                        system("pause");
                    }
                }
                if (!dire)
                {
                    gotoxy(PossicaoColuna,4);
                    printf("Diretorio Criado %s", diretorio);
                    strcpy(file_name, "\\despesas.txt");
                    strcat(diretorio, file_name);
                    file = fopen(diretorio, "w");
                    fprintf(file, "%f", despesas);
                    fclose(file);
                }
                else
                {
                    gotoxy(PossicaoColuna,4);
                    printf("Nao foi possivel criar os diretorios necessarios %s", diretorio);
                }
            }
        }
        else
        {
            /* opendir() failed for some other reason. */
            gotoxy(PossicaoColuna,4);
            printf("Erro ao abrir diretorio");
        }
    }

    return 0;
}

void devolveMes(int opt, char mes[15]){

    if (opt == 1)
    {
        strcpy(mes, "janeiro");
    }
    if (opt == 2)
    {
        strcpy(mes, "fevereiro");
    }
    if (opt == 3)
    {
        strcpy(mes, "marco");
    }
    if (opt == 4)
    {
        strcpy(mes, "abril");
    }
    if (opt == 5)
    {
        strcpy(mes, "maio");
    }
    if (opt == 6)
    {
        strcpy(mes, "junho");
    }
    if (opt == 7)
    {
        strcpy(mes, "julho");
    }
    if (opt == 8)
    {
        strcpy(mes, "agosto");
    }
    if (opt == 9)
    {
        strcpy(mes, "setembro");
    }
    if (opt == 10)
    {
        strcpy(mes, "outubro");
    }
    if (opt == 11)
    {
        strcpy(mes, "novembro");
    }
    if (opt == 12)
    {
        strcpy(mes, "dezembro");
    }
}

int dataAtual(){
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    printf("Data: %d/%d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void TelaModificarCardapio(){
    char nome[30]={'M','o','d','i','f','i','c','a','r',' ','c','a','r','d','a','p','i','o'};
    int x,y=1;
    tela(nome);
    if(y==0){
        gotoxy(PossicaoColuna,4);
        printf("Opcao invalida");
    }
    gotoxy(PossicaoColuna,5);
    printf("Qual cardapio deseja modificar");
    gotoxy(PossicaoColuna,7);
    printf("0.Voltar");
    gotoxy(PossicaoColuna,9);
    printf("1.Cardapio de Pizza");
    gotoxy(PossicaoColuna,11);
    printf("2.Cardapio de bebida alcolica");
    gotoxy(PossicaoColuna,13);
    printf("3.Cardapio de bebida nao alcolica");
    gotoxy(PossicaoColuna,15);
    printf("___");
    gotoxy(PossicaoColuna+1,15);
    scanf("%d",&x);
    switch(x){
        case 0:
            TelaOpsCardapio();
        break;
        case 1:
            ModificarPizza();
        break;
        case 2:
            ModificarBebidaA();
        break;
        case 3:
            ModificarBebidaNA();
        break;
        default:
            y=0;
    }
}

void TelaOpsCardapio(){
    char nome[15]={'T','e','l','a',' ','C','a','r','d','a','p','i','o'};
    int x,y=1;
    tela(nome);
    if(y==0){
        gotoxy(PossicaoColuna,4);
        printf("Opcao invalida");
    }
    gotoxy(PossicaoColuna,5);
    printf("O que deseja fazer");
    gotoxy(PossicaoColuna,7);
    printf("0.Voltar");
    gotoxy(PossicaoColuna,9);
    printf("1.Adicionar cardapio");
    gotoxy(PossicaoColuna,11);
    printf("2.Modificar cardapio");
    gotoxy(PossicaoColuna,13);
    printf("___");
    gotoxy(PossicaoColuna+1,13);
    scanf("%d",&x);
    switch(x){
        case 0:
            MenuPrincipal(4);
        break;
        case 1:
            TelaAdicionarCardapio();
        break;
        case 2:
            TelaModificarCardapio();
        break;
        default:
            y=0;
    }

}

void TelaAdicionarCardapio(){

    char nome[15]={'T','e','l','a',' ','C','a','r','d','a','p','i','o'};
    int x,y=1;
    tela(nome);
    if(y==0){
        gotoxy(PossicaoColuna,4);
        printf("Opcao invalida");
    }
    gotoxy(PossicaoColuna,5);
    printf("O que deseja fazer");
    gotoxy(PossicaoColuna,7);
    printf("0.Voltar");
    gotoxy(PossicaoColuna,9);
    printf("1.Adicionar pizza");
    gotoxy(PossicaoColuna,11);
    printf("2.Adicionar bebida alcolica");
    gotoxy(PossicaoColuna,13);
    printf("3.Adicionar bebida nao alcolica");
    gotoxy(PossicaoColuna,15);
    printf("___");
    gotoxy(PossicaoColuna+1,15);
    scanf("%d",&x);
    switch(x){
        case 0:
            TelaOpsCardapio();
        break;
        case 1:
            TelaAdicionarPizza();
        break;
        case 2:
            TelaAdicionarBebidaAlcolica();
        break;
        case 3:
            TelaAdicionarBebidaNaoAlcolica();
        break;
        default:
            y=0;
    }
}

void TelaRelatorio(){
    char nome[10]={'R','e','l','a','t','o','r','i','o'};
    tela(nome);
    int x,z=1;
    if(z == 0){
        gotoxy(PossicaoColuna,4);
        printf("Opcao invalida");
    }
    gotoxy(PossicaoColuna,5);
    printf("Oque gostaria de fazer");
    gotoxy(PossicaoColuna,7);
    printf("0.Voltar");
    gotoxy(PossicaoColuna,9);
    printf("1.Relatoria de faturamento");
    gotoxy(PossicaoColuna,11);
    printf("2.Relatoria de quantidade de pizzas vendidas");
    gotoxy(PossicaoColuna,13);
    printf("___");
    gotoxy(PossicaoColuna+1,13);
    scanf("%d",&x);
    switch(x){
        case 0:
            MenuPrincipal(4);
        break;
        case 1:
            relatorio_faturamento();
        break;
        case 2:
            relatorio_quantidade();
        break;
        default:
            z=0;
    }

}

void NovoPedido(){
    FILE *arq;
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    char nome[15]={'N','o','v','o',' ','p','e','d','i','d','o'};
    tela(nome);
    char Pedido[150]={};
    char confirmar[50];
    char Pessoa[50];
     if(arq=fopen("bancodedados\\pedidos\\andamento\\IDPedido.txt","r")==NULL){
        arq=fopen("bancodedados\\pedidos\\andamento\\IDPedido.txt","w");
        fputc(1,arq);
        fclose(arq);
    }
    strcpy(Pedido,"bancodedados\\pedidos\\andamento\\Pedido");
    arq=fopen("bancodedados\\pedidos\\andamento\\IDPedido.txt","r");
    int ops=fgetc(arq);
    fclose(arq);
    sprintf(confirmar,"%d",ops);
    strcat(Pedido,&confirmar);
    strcat(Pedido,".txt");
    if((arq = fopen(Pedido,"r"))==NULL){
        arq = fopen(Pedido,"a");
        fclose(arq);
    }

    arq=fopen("bancodedados\\pedidos\\andamento\\IDPedido.txt","r");
    int numero=fgetc(arq);
    fclose(arq);
    arq=fopen(Pedido,"a");
    fprintf(arq,"%d Nome %s",numero,Pessoa);
    fclose(arq);
    arq=fopen("bancodedados\\pedidos\\andamento\\IDPedido.txt","w");
    numero=numero+1 ;
    fputc(numero,arq);
    fclose(arq);

    system('pause');
}

void FinalizarPedido(){


}

void PedidosEmAndamento(){


}


