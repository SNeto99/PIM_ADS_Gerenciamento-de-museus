#include "funcs.h"
#include <dirent.h>

//para rodar o código:
// gcc -o meu_programa v2.c funcs.c

//!Fazer:
// descriçao das obras
// comentar o código
// adicionar mais questões
// tratamento de erros
// help()



void listarNomesArquivosCSV2(const char *caminho, char ***nomesArquivos, int *numArquivos) {
    DIR *dir;
    struct dirent *entrada;
    int numArq = 0;
    char **nomes = NULL;

    dir = opendir(caminho);

    if (dir == NULL) {
        perror("Erro ao abrir a pasta");
        exit(EXIT_FAILURE);
    }

    while ((entrada = readdir(dir)) != NULL) {
        if (strstr(entrada->d_name, ".txt")) {
            // Alocar memória para armazenar o nome do arquivo
            nomes = (char **)realloc(nomes, (numArq + 1) * sizeof(char *));
            nomes[numArq] = strdup(entrada->d_name);
            numArq++;
        }
    }

    closedir(dir);

    *nomesArquivos = nomes;
    *numArquivos = numArq;
}

void listarNomesPastas(const char *caminho, char ***nomesPastas, int *numPastas) {
    DIR *dir;
    struct dirent *entrada;
    int numPasta = 0;
    char **nomes = NULL;

    dir = opendir(caminho);

    if (dir == NULL) {
        perror("Erro ao abrir a pasta");
        exit(EXIT_FAILURE);
    }

    while ((entrada = readdir(dir)) != NULL) {
        if (entrada->d_type == DT_DIR) { // Verifica se é um diretório
            // Ignora as entradas '.' e '..'
            if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
                continue;
            }

            // Alocar memória para armazenar o nome da pasta
            nomes = (char **)realloc(nomes, (numPasta + 1) * sizeof(char *));
            nomes[numPasta] = strdup(entrada->d_name);
            numPasta++;
        }
    }

    closedir(dir);

    *nomesPastas = nomes;
    *numPastas = numPasta;
}


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

    credenciais = atoi(argv[1]);
    if (!credenciais){
        int linhas=0, colunas=0;
        char ***arquivo_credenciais = lerarquivo(CAM_CREDENCIAL, &linhas, &colunas);
        credenciais=atoi(arquivo_credenciais[0][1]);
    }

    // int linhas=0;
    // int colunas=0;
    // char ***configs = lerarquivo("Temas\\CONFIGS.csv", &linhas, &colunas);
    // n_temas=linhas-1;

    const char *caminho = "Temas/";  // Substitua pelo caminho da sua pasta
    char **nomesPastas;
    int numPastas;

    listarNomesPastas(caminho, &nomesPastas, &numPastas);

    n_temas=numPastas;
    // printf("Nomes dos arquivos CSV na pasta '%s':\n", caminho);
    for (int i = 0; i < numPastas; i++) {
        // printf("%s\n", nomesPastas[i]);
        strcpy(Temass[i].nome, nomesPastas[i]);
        strcpy(Temass[i].caminho_defs, nomesPastas[i]);
        free(nomesPastas[i]);
    }
    free(nomesPastas);

    printf("\n\n\n");
    // for (int i = 1; i < linhas; i++) {
    //     strcpy(Temass[i - 1].nome, configs[i][0]);
    //     strcpy(Temass[i - 1].caminho_defs, configs[i][1]);
    //     strcat(Temass[i - 1].caminho_defs, "\\CONFIGS.csv");
    // }
    
    for (int i=0;i<n_temas;i++)
    {
        char caminho[T_MAX_STR*2] = "Temas/";
        strcat(caminho, Temass[i].caminho_defs);  // Substitua pelo caminho da sua pasta
        char **nomesPastas2;
        int numPastas2=0;


    // printf("caminho:%s", caminho);
        listarNomesPastas(caminho, &nomesPastas2, &numPastas2);
        // printf("Nomes dos arquivos CSV na pasta '%s':\n", caminho);
        for (int j = 0; j < numPastas2; j++) {
            // printf("%s\n", nomesPastas2[j]);
            strcpy(Temass[i].obras[j].nome, nomesPastas2[j]);
            strcpy(Temass[i].obras[j].caminho_quest, nomesPastas2[j]);
            free(nomesPastas2[j]);
        }
        free(nomesPastas2);
        Temass[i].n_obras=numPastas2;

        // linhas=0;
        // colunas=0;
        // char ***def_obras = lerarquivo(Temass[i].caminho_defs, &linhas, &colunas);
        // int n_obras_tema=linhas-1;

        // for (int j = 1; j < linhas; j++) {
        //     strcpy(Temass[i].obras[j - 1].nome         , def_obras[j][0]);
        //     strcpy(Temass[i].obras[j - 1].caminho_quest, def_obras[j][1]);
        // }


        // n_obras_total=n_obras_total + n_obras_tema;
        // Temass[i].n_obras=n_obras_tema;
    }


    
    // system("pause");
    menuCredencial(credenciais);

return 0;
}



void administracao(){
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
            break;
        }
        if ((isenter == 1) && (escolha == 5)){
            printf("\n\n");
            break;
        }
    }
}

void venderBilhetes(){
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

void validarBilhetes(){
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

void acessarObras(){
 
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
            // printf("\nn_obras=%d\n", Temass[escolha].n_obras);
            //     system("pause");

            for (int i=0;i<Temass[escolha].n_obras;i++)
            {
                char caminho[T_MAX_STR*2]="Temas/";
                // printf("\ncaminho123:%s", caminho);

                strcat(caminho, Temass[escolha].caminho_defs);
                // printf("\ncaminho123:%s", caminho);

                strcat(caminho, "/");  
                // printf("\ncaminho123:%s", caminho);

                strcat(caminho, Temass[escolha].obras[i].caminho_quest);  
                // printf("\ncaminho123:%s", caminho);
                
                strcat(caminho, "/");  
                // printf("\ncaminho123:%s", caminho);

                // strcat(caminho, ".txt");  
                // printf("\ncaminho123:%s", caminho);

                strcpy(Temass[escolha].obras[i].caminho_quest, caminho);
                

                char **nomesArquivos;
                int numArquivos;

                // printf("\ncaminho123:%s\n", caminho);
                listarNomesArquivosCSV2(caminho, &nomesArquivos, &numArquivos);
                for (int j = 0; j < numArquivos; j++) {
                    // printf("%s\n", nomesArquivos[escolha]);
                    strcat(Temass[escolha].obras[i].caminho_quest, nomesArquivos[j]);
                    // free(nomesArquivos[j]);
                }
                // free(nomesArquivos);
            }
                // printf("\nNomes dos arquivos CSV na pasta '%s':\n", Temass[escolha].caminho_defs);
                // system("pause");

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
                telainicial2(escolha_obra, alt_2 , 1, num_op_obras);  //cria os textos da tela inicial, incluindo aonde esta selecionado
                int isenter_2 = 0;
                isenter_2= retornar_selecao(p_escolha_obra, num_op_obras);

                if ((isenter_2) && (escolha_obra != num_op_obras-1))
                {
                    int confirmar = 0;
                    int *p_confirmar = &confirmar;
                    char alternativas_3[][30] = {"Iniciar", "Voltar"};
                    char *alt_3 = &alternativas_3[0][0];
                    while (true)
                    {
                        system("cls");
                        printf("\n\tQUESTIONARIO: %s", alt[escolha]);
                        printf("\n\n\t");
                        telainicial(confirmar, alt_3 , 0, 2);  //cria os textos da tela inicial, incluindo aonde esta selecionado
                        int isenter_3 = 0;
                        isenter_3= retornar_selecao(p_confirmar, 2);
                        if ((isenter_3 == 1) && (confirmar == 0)){
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

void resumoVendas() {
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


    // Calcula a somatória a cada 3 meses para cada tipo de ingresso sendo I (inteira), M (Meia) e X (isento) separando por trimestre.
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

   printf("\t\t--->Voltar");
   int tecla;
   while((tecla!=13) && (tecla!=27)){
    tecla=getch();
    // printf("\n%d", tecla);
   }
    

   }

void ajuda(){
    system("cls");
    printf("\n");
    for (int i=0; i<n_temas;i++){
        printf("\nnome:%s\n\n", Temass[i].nome);
        system("pause");
    }
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
    case 5:
        resumoVendas();
        break;
    }
}

void responderquestionario(int tema, int obra) {


        int linhas=0;
        int colunas=0;
        printf("\ncaminho questionario:%s\n",Temass[tema].obras[obra].caminho_quest);
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
        printf("foi salvo");
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
            char *hora = horaAtual();
            fprintf(arquivo, "%.f;", codigo);
            fprintf(arquivo, "%s;" , Temass[tema].nome);
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
