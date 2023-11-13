#include "funcs.h"

//para rodar o código:
// gcc -o meu_programa v3.c funcs.c

//!Fazer:
// comentar o código
// tratamento de erros
// help()





void administracao();
void venderBilhetes();
void validarBilhetes();
void acessarObras();
void resumoVendas();
void ajuda();

void responderquestionario(int tema, int obra);
void salvarCompra(int obra, int meiaouinteira);
void menuCredencial(int credenciais);


struct Tema Temass[N_MAX_TEMAS];
int n_temas=0;
int n_obras_total=0;
int credenciais;


int main(int argc, char *argv[]){
    
    system("chcp 65001 > null");

    //Ler credenciais
    credenciais = atoi(argv[1]);
    if (!credenciais){
        int linhas=0, colunas=0;
        char ***arquivo_credenciais = lerarquivo(CAM_CREDENCIAL, &linhas, &colunas);
        credenciais=atoi(arquivo_credenciais[0][1]);
    }
    //Listar o nome e o caminho das pastas na pasta PASTA_TEMAS
    char **nomesPastas;
    int numPastas;
    listarNomesPastas(PASTA_TEMAS, &nomesPastas, &numPastas);
    n_temas=numPastas;
    for (int i = 0; i < numPastas; i++) {
        strcpy(Temass[i].nome, nomesPastas[i]);

        strcpy(Temass[i].caminho_pasta, PASTA_TEMAS);  
        strcat(Temass[i].caminho_pasta, nomesPastas[i]);
        strcat(Temass[i].caminho_pasta, "/");  

        free(nomesPastas[i]);
    }
    free(nomesPastas);
    //Listar os nomes e os caminhos dentro da pasta dentro da PASTA_TEMAS
    for (int i=0;i<n_temas;i++)
    {
        char **nomesPastas2;
        int numPastas2=0;

        listarNomesPastas(Temass[i].caminho_pasta, &nomesPastas2, &numPastas2);
        Temass[i].n_obras=numPastas2;
      
        for (int j = 0; j < numPastas2; j++) {
            strcpy(Temass[i].obras[j].nome, nomesPastas2[j]);
            strcpy(Temass[i].obras[j].caminho_pasta_obra, Temass[i].caminho_pasta);
            strcat(Temass[i].obras[j].caminho_pasta_obra, nomesPastas2[j]);
            strcat(Temass[i].obras[j].caminho_pasta_obra, "/");  
            strcpy(Temass[i].obras[j].caminho_quest, Temass[i].obras[j].caminho_pasta_obra);  
            free(nomesPastas2[j]);
        }

        for (int j=0;j<Temass[i].n_obras;j++)
            {
                char **nomesArquivosTXT;
                int numArquivosTXT;

                listarNomesArquivos(Temass[i].obras[j].caminho_quest, ".txt", &nomesArquivosTXT, &numArquivosTXT);
                for (int k = 0; k < numArquivosTXT; k++) {
                    strcat(Temass[i].obras[j].caminho_quest, nomesArquivosTXT[k]);
                    free(nomesArquivosTXT[k]);
                }
                free(nomesArquivosTXT);
            }

        for (int j=0;j<Temass[i].n_obras;j++)
            {
                char **nomesArquivosCSV;
                int numArquivosCSV=0;
                listarNomesArquivos(Temass[i].obras[j].caminho_pasta_obra, ".csv", &nomesArquivosCSV, &numArquivosCSV);
                char caminhodescricao[T_MAX_STR*2];
                for (int k = 0; k < numArquivosCSV; k++) {
                    strcpy(caminhodescricao, Temass[i].obras[j].caminho_pasta_obra);
                    strcat(caminhodescricao, nomesArquivosCSV[k]);
                    free(nomesArquivosCSV[k]);
                    strcpy(Temass[i].obras[j].caminho_descr, caminhodescricao);
                }
                free(nomesArquivosCSV);
            }


        free(nomesPastas2);
    }
   
    menuCredencial(credenciais);

return 0;
}



void administracao()
{
    int escolha = 0;
    int *p_escolha = &escolha;
    char alternativas[][30] = {"Vender Bilhetes", "Validar Bilhetes", "Acessar Temas", "Resumo Vendas","Ajuda","Sair"};
    char *alt = &alternativas[0][0];
    int num_op = 6;
    
    while (true)
    {   
        system("cls");
        printf("\nBem vindo ao Programa de Administracao de Museus\nO que voce deseja fazer?\n\n");
        telainicial(escolha, alt , 1, num_op);  //cria os textos da tela inicial, incluindo aonde esta selecionado
    
        int isenter = retornar_selecao(p_escolha, num_op);
        if ((isenter == 1) && (escolha == 0)){
            venderBilhetes();
        }
        if ((isenter == 1) && (escolha == 1)){
            validarBilhetes();
        }
        if ((isenter == 1) && (escolha == 2)){
            acessarObras();
        }
        if ((isenter == 1) && (escolha == 3)){
            resumoVendas();
        }
        if ((isenter == 1) && (escolha == 4)){
            ajuda();
        }
        if ((isenter == 1) && (escolha == 5)){
            printf("\n\n");
            break;
        }
    }
}

void venderBilhetes()
{
    int escolha = 0;
    int *p_escolha = &escolha;

    char *alt[N_MAX_TEMAS];
    for (int i=0; i<n_temas; i++){
        alt[i]= Temass[i].nome;
    }
    alt[n_temas] = "Voltar";

    int numop;
    if (credenciais == 1)
    {
        numop=n_temas+1;
    } 
    else {
        numop=n_temas;
    }
        
    while (true)
    {   
        system("cls");
        printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
        telainicial2(escolha, alt , 1, numop);
    
        int isenter = retornar_selecao(p_escolha, numop);
        if (isenter == 1){
            int escolhatipo = 0;
            int *p_escolhatipo = &escolhatipo;
            char meiaouinteira[][30] = {"Inteira", "Meia", "Isento", "Voltar"};
            char *moi = &meiaouinteira[0][0];

            while (true)
            {   
                system("cls");
                printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
                telainicial2(escolha, alt , 1, numop);
                if (escolha !=n_temas){
                    printf("\nSELECIONE O TIPO DE INGRESSO:\n\n");
                    telainicial(escolhatipo, moi , 0, 4);
                    int isinteira = retornar_selecao(p_escolhatipo, 4);
                    if ((isinteira == 1)&&(escolhatipo != 3)){

                        int confirmar = 0;
                        int *p_confirmar = &confirmar;
                        char escolha_conf[][15] = {"CONFIRMAR", "CANCELAR"};
                        char *p_escolha_conf = &escolha_conf[0][0]; 
                        int comprado = 0; 

                        while (true)
                        {
                            system("cls");
                            printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
                            telainicial2(escolha, alt , 1, n_temas+1);
                            printf("\nSELECIONE O TIPO DE INGRESSO:\n\n");
                            telainicial(escolhatipo, moi , 0, 4);

                            printf("\n\n\n");
                            telainicial(confirmar, p_escolha_conf, 1, 2);
                            comprado = retornar_selecao(p_confirmar, 2);

                            if ((comprado == 1)&&(confirmar==0))
                            {
                                salvarCompra(escolha, escolhatipo);
                                break;   
                            }
                            else if ((comprado == 1)&&(confirmar==1)){
                                break;
                            }
                        }
                        if (comprado == 1){
                            break;
                        }
                    }
                    if ((isinteira == 1)&&(escolhatipo == 3)){
                        break;
                    }
                }
                else{
                    break;
                }
            }
        }
        if ((isenter == 1) && (escolha == n_temas)){
            printf("\n\n");
            break;
        }
    }
}

void validarBilhetes()
{
    while (true)
    {
        system("cls");
        printf("MENU DE VALIDACAO DE BILHETES:\n\n\n");
    
        char ticket_validar[13];
        printf("Digite o nº do ticket para validar ");
        if (credenciais == 1){
            printf("(ou \"sair\" para sair)");
        }
        printf("\n\n\t\t\tno do ticket: ");
        scanf("%s", ticket_validar);
    
        if (strcmp(ticket_validar, "sair")&strcmp(ticket_validar, "SAIR"))
        {
            int nlinhas, ncolunas;
            char ***tickets = lerarquivo(CAM_TICKETS,&nlinhas, &ncolunas); 
            int buscaFinalizada = false;
            int i=0;
            while (!buscaFinalizada && i < nlinhas-1)
            {
                if (strcmp(tickets[i][0], ticket_validar) == 0)
                {
                    printf("\nTicket validado:\n\n");
                    ticket(tickets[i][1], *tickets[i][2], tickets[i][0], tickets[i][3]);
                    buscaFinalizada = true;
                    system("pause");
                }
                i++;
                if (i==nlinhas-1){
                    printf("\n\tTicket nao encontrado.\n\t\t\t");
                    system("pause");
                    break;
                }
            }    
        }
        else{
            break;
        }   
    }
}

void acessarObras()
{
 
    int escolha = 0;
    int *p_escolha = &escolha;
    char *alt[N_MAX_TEMAS];
    for (int i=0; i<n_temas; i++){
        alt[i]= Temass[i].nome;
    }
    alt[n_temas] = "Voltar";

    int numop;
    if (credenciais == 1)
    {
        numop=n_temas+1;
    } 
    else {
        numop=n_temas;
    }


    while (true)
    {   
        system("cls");
        printf("\n\tSELECIONE O TEMA QUE VOCE DESEJA:\n\n");
        telainicial2(escolha, alt , 1, numop);  //cria os textos da tela inicial, incluindo aonde esta selecionado
        int isenter = 0;
        isenter= retornar_selecao(p_escolha, numop);
        
        if ((isenter)&&(escolha != n_temas))
        {
            int escolha_obra = 0;
            int *p_escolha_obra = &escolha_obra;
            int num_op_obras = Temass[escolha].n_obras+1;

            char *alt_2[N_MAX_OBRAS];
            for (int i=0; i<Temass[escolha].n_obras; i++){
                alt_2[i]= Temass[escolha].obras[i].nome;
            }
            alt_2[Temass[escolha].n_obras] = "Voltar";


            while (true)
            {
                system("cls");
                printf("\n\tSELECIONE A OBRA QUE VOCE DESEJA:\n\n");
                //cria os textos da tela inicial, incluindo aonde esta selecionado
                telainicial2(escolha_obra, alt_2 , 1, num_op_obras);  
                int isenter_2 = 0;
                isenter_2= retornar_selecao(p_escolha_obra, num_op_obras);

                if ((isenter_2) && (escolha_obra != num_op_obras-1))
                {
                    int linhas=0, colunas=0;
                    char ***descricao = lerarquivo(Temass[escolha].obras[escolha_obra].caminho_descr, &linhas, &colunas);

                    int confirmar = 0;
                    int *p_confirmar = &confirmar;
                    char alternativas_3[][30] = {"Iniciar", "Voltar"};
                    char *alt_3 = &alternativas_3[0][0];

                    while (true)
                    {
                        system("cls");
                        printf("\n");
                        printarquivo(descricao, linhas, colunas);
                        printf("\n\n\nQUESTIONARIO:\n");
                        //cria os textos da tela inicial, incluindo aonde esta selecionado
                        telainicial(confirmar, alt_3 , 1, 2);  
                        int isenter_3 = 0;
                        isenter_3= retornar_selecao(p_confirmar, 2);
                        if ((isenter_3 == 1) && (confirmar == 0))
                        {
                            responderquestionario(escolha, escolha_obra);
                        }
                        if ((isenter_3 == 1) && (confirmar == 1)){
                            break;
                        }
                    }
                }

                if ((isenter_2 == 1) && (escolha_obra == num_op_obras-1)){
                    break;
                }
            }
        }

        if ((isenter) && (escolha == n_temas)){
            printf("\n\n");
            break;
        }
    }
}

void resumoVendas() 
{
    system("cls");

    int linhas=0;
    int colunas=0;
    char ***tickets = lerarquivo(CAM_TICKETS, &linhas, &colunas);
    
    struct Ingresso ingressos[linhas];
    
    for (int i = 0; i < linhas; i++) {
        strcpy(ingressos[i].codigo   , tickets[i][0]);
        strcpy(ingressos[i].nome     , tickets[i][1]);
        strcpy(ingressos[i].tipo     , tickets[i][2]);
        strcpy(ingressos[i].data_hora, tickets[i][3]);
    }


    // Calcula a somatória a cada 3 meses para cada tipo de ingresso sendo I (inteira), 
    // M (Meia) e X (isento) separando por trimestre.
    int somatoria_trimestre_I[4] = {0, 0, 0, 0}; 
    int somatoria_trimestre_X[4] = {0, 0, 0, 0};
    int somatoria_trimestre_M[4] = {0, 0, 0, 0};

    for (int i = 0; i < linhas; i++) {
        char *data_hora = ingressos[i].data_hora;
        int trimestre = calcularTrimestre(data_hora);

        if (trimestre != -1) 
        {
            if (strcmp(ingressos[i].tipo, "I") == 0) {
                somatoria_trimestre_I[trimestre - 1] += 1;
            } 
            else if (strcmp(ingressos[i].tipo, "X") == 0) {
                somatoria_trimestre_X[trimestre - 1] += 1;
            } 
            else if (strcmp(ingressos[i].tipo, "M") == 0) {
                somatoria_trimestre_M[trimestre - 1] += 1;
            }
        }
    }

    printf(" 10 ultimas vendas:\n\n");
    printf(" Codigo       Tema\t\t\t\t\t    Tipo   Data       Hora\n");

    for (int i = linhas - 1; i > linhas - 11; i --){
       printf(" %s %s %s\t   %s\n", ingressos[i].codigo, ingressos[i].nome, ingressos[i].tipo, ingressos[i].data_hora);
    }
    // 

    printf("\n\n\nSomatoria por trimestre: \n");
                        printf("\t ______________________________________ \n");
                        printf("\t|            |Inteira |Meia    |Isento |\n");
    for (int t = 0; t < 4; t++) {
                        printf("\t|            |        |        |       |\n");
          printf("\t|%do Trimestre| % 4d   | % 4d   | % 4d  |\n", t + 1, somatoria_trimestre_I[t], somatoria_trimestre_M[t], somatoria_trimestre_X[t]);}
                        printf("\t|____________|________|________|_______|");

    voltar();
    

   }

void ajuda(){
    system("cls");

    int linhas, colunas;
    char ***tutorial = lerarquivo(CAM_TUTORIAL, &linhas, &colunas);
    printarquivo(tutorial, linhas, colunas);

    printf("\n\n\t\t");
    voltar();
}


void menuCredencial(int credenciais){
    switch (credenciais)
    {
    case 1:
        administracao();
        break;
    case 2:
        venderBilhetes();
        break;
    case 3:
        validarBilhetes();
        break;
    case 4:
        acessarObras();
        break;
    }
}

void responderquestionario(int tema, int obra) {


        int linhas=0;
        int colunas=0;
        char ***questionario = lerarquivo(Temass[tema].obras[obra].caminho_quest, &linhas, &colunas);
        int n_questoes = linhas/(2+N_ALTERNATIVAS);

        for (int i = 0; i < n_questoes; i++) 
        {
            int rowIndex = i * (N_ALTERNATIVAS + 2);  // Calcula o índice da linha para a pergunta atual

            strcpy(Temass[tema].obras[obra].Questoes[i].pergunta               , questionario[rowIndex][0]);

            for (int j = 1; j <= N_ALTERNATIVAS; j++) 
            {
                strcpy(Temass[tema].obras[obra].Questoes[i].alternativas[j - 1], questionario[rowIndex + j][0]);
            }

            strcpy(Temass[tema].obras[obra].Questoes[i].resposta               , questionario[rowIndex + N_ALTERNATIVAS + 1][0]);
        }

    char resposta;
    int pontuacao = 0;

    for (int i=0; i<3; i++) 
    {
        char respostacorreta = Temass[tema].obras[obra].Questoes[i].resposta[0];

        system("cls");
        printf("Questao %d:\n", i+1);
        printf("%s\n", Temass[tema].obras[obra].Questoes[i].pergunta);  

        for (int j = 0; j < N_ALTERNATIVAS; j++) {
            printf("%s\n", Temass[tema].obras[obra].Questoes[i].alternativas[j]);  
        }

        printf("\nResposta: ");
        scanf(" %c", &resposta);

        if (resposta == respostacorreta) {
            pontuacao++;  
        }
    }

    
    system("cls");

    printf("\n\n");
    printf("\t ________________________________________ \n");
    printf("\t|                                        |\n");
    printf("\t|     Voce acertou %02d de %02d questoes     |\n", pontuacao, n_questoes);
    printf("\t|________________________________________|\n");
    printf("\n\n\n");
    system("pause");
}

void salvarCompra(int tema, int meiaouinteira){

    char char_meiaouinteira;
    double codigo = codigoID();

    switch (meiaouinteira){
        case 0:
            char_meiaouinteira = 'I';
            break;

        case 1:
            char_meiaouinteira = 'M';
            break;

        case 2:
            char_meiaouinteira = 'X';
            break;
    }
        
    
    FILE *arquivo = fopen(CAM_TICKETS, "a");
    

    if (arquivo != NULL)
    {
            char nome[T_MAX_STR];
            strcpy(nome, Temass[tema].nome);
            strNomalize(nome);

            char *hora = horaAtual();
            fprintf(arquivo, "%.f;", codigo);
            fprintf(arquivo, "%s;" , nome);
            fprintf(arquivo, "%c;" , char_meiaouinteira);
            fprintf(arquivo, "%s\n", hora);
            fclose(arquivo);

            char str_codigo[50];
            sprintf(str_codigo, "%.f", codigo);
            ticket(Temass[tema].nome, char_meiaouinteira, str_codigo, hora);
            system("pause");


        }
    else {
        printf("Erro ao abrir o arquivo para salvar os tickets.\n");
        system("pause");
    }
}
