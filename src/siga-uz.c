#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define system_clear system("cls") // macro para limpar a tela
#define system_pause system("pause") // macro para pausar o sistema
#define MAX_TAMANHO_ESTUDANTE 10 // Este e o tamanho maximo de estudante que o sistema esta atender.
#define MAX_TAMANHO_DOCENTE 7 // Tamanho maximo de docentes, cada docente esta para uma discplina/cadeira.
#define MAX_TAMANHO_DISCIPLINAS 7 // Este e o tamanho maximo de discplina para curso de eng. de processo industriais 1.o ano 2.o semestre.

// O siga tem tres estruturas de dados, definidos por mim. Abaixo, disciplina, docente e estudante.
typedef struct {
    int id; // id da disciplina que vai relacionar o docente e o estudante.
    char nome[20]; // nome da disciplina
    float teste1, teste2, media; // As avaliacoes...
} Disciplina;

// Nesta sistema o estudante tera a capacidade maxima de se inscrever a 7 disciplinas do segundo semestre do curso de eng. de processos industriais.
typedef struct {
    int id;
    char nome[20];
    int senha;
    Disciplina disciplinas[7]; // disciplinas...
    int qtdDisciplinas; // quantidade de disciplinas.
} Estudante;

typedef struct {
    int id;
    char nome[20];
    int senha;
    int idDisciplina;
} Docente;

// Aqui sao definidas todas as funcoes que o estudante vai manipular, durante a execucao do sistema. 

void cadastrar_estudante(Estudante estudantes[], int *qtdEstudantes) {
    /*
        funcao que faz o cadastro do novo estudante, esta funcao tambem faz uma verificao
        caso o estudante ja esteja cadastrado.
    */
    char nome[30];
    int entrada = 0, senha = 0;
    printf("Bem-vido\n");
    printf("Digite o seu nome: ");
    scanf("%s", nome);
    printf("Escolhe um PIN: ");
    scanf("%i", &senha);

    {
        // esta seccao e responsavel por verificar se o estudante ja ou na existe no "banco de dados".
        // essa verificacao e feita por uma busca sequencial.
        for (int j = 0 ; j < *qtdEstudantes ; ++j) {
            if ((strcmp(nome, estudantes[j].nome) == 0) && (senha == estudantes[j].senha)) {
                printf("Estudante ja registrado!\n");
                system_pause;
                return;
            }
        }
    }

    { // Esta seccao e responsavel efetuar o registro do novo estudante.
        strcpy(estudantes[*qtdEstudantes].nome, nome);
        estudantes[*qtdEstudantes].senha = senha;
        estudantes[*qtdEstudantes].id = *qtdEstudantes;
        estudantes[*qtdEstudantes].qtdDisciplinas = 0;
        * qtdEstudantes += 1;
    }
    printf("0. Voltar\nEntrada: ");
    scanf("%i", &entrada);
    system_clear;
}

bool autenticar_estudante(Estudante estudantes[], int tamanho, int *id) {
    /*
        funcao responsavel por autenticar um estudante, a autenticao e feita pelo
        algoritmo de busca sequencial, como sao apenas 10 estudantes que o sistema vai suportar, penso que nao sera muito trabalho.
    */
    char nome[50];
    int senha = 0;
    printf("Insira o seu nome: ");
    scanf("%s", nome);
    printf("Insira o seu PIN: ");
    scanf("%i", &senha);

    for (int j = 0 ; j < tamanho ; ++j) {

        // a funcao strcmp() e da biblioteca <string.h>, e usada para comparar duas strings. 
        if ((strcmp(nome, estudantes[j].nome) == 0) && (senha == estudantes[j].senha)) {
            *id = j; // este id sera utilizado em outras funcoes, como a de ver_notas()... 
            return true;
        }
    }
    return false;
}

void inscrever_disciplina(Disciplina disciplina[], int tamanho, Estudante * estudante) {
    int id = -1, entrada = 0;
    bool ja_inscrito = false;
    do {
        system_clear;
        ja_inscrito = false;
        printf("Id|\tNome da disciplina\n");
        for (int j = 0 ; j < tamanho ; ++j) {
            printf("%i |\t%s\n", j+1, disciplina[j].nome);
        }

        printf("Escolhe o id da disciplina\nEntrada: ");
        scanf("%i", &id);

        { // nesta seccao verifica se o estudante ja esta inscrito a um certa disciplina.
            for (int j = 0 ; j < estudante->qtdDisciplinas ; ++j) {

                if (estudante->disciplinas[j].id == id) {
                    ja_inscrito = true;
                    break;
                }
            }        
        }

        if (ja_inscrito) {
            // caso o estudante esteja inscrito, a iteraco do loop e saltada, assim a inscricao nao e concluida.
            printf("Ja esta inscrito a esta disciplina!\n");
            system_pause;            
            continue;
        } else {
            // Validadacao da inscricao.
            strcpy(estudante->disciplinas[estudante->qtdDisciplinas].nome, disciplina[id-1].nome);
            estudante->disciplinas[estudante->qtdDisciplinas].id = disciplina[id-1].id;
            estudante->qtdDisciplinas += 1;
        }

        printf("1. Continuar\n");
        printf("0. Sair\nEntrada: ");
        scanf("%i", &entrada);
    } while (entrada != 0);
}

void ver_notas(Estudante estudante) {
    int entrada = 0;
    printf("Nome da disciplina\t|Teste1\t|Teste2\t|Media\t|Resultado\n");

    for (int j = 0 ; j < estudante.qtdDisciplinas ; ++j) {
        char resultado[10];
        printf("%s", estudante.disciplinas[j].nome);
        {
            // esta seccao e apenas para formatar a saida, ou seja, a tabela que vai mostrar as notas.
            if (strlen(estudante.disciplinas[j].nome) < 17) {
                printf("\t\t");
            } else if (strlen(estudante.disciplinas[j].nome) >= 17) {
                printf("\t");
            }        
        }

        {
            // Resultado obtido pelo estudante.
            if (estudante.disciplinas[j].media >= 10 && estudante.disciplinas[j].media < 14) {
                strcpy(resultado, "Admitido");
            } else if (estudante.disciplinas[j].media >= 14) {
                strcpy(resultado, "Dispensado");
            } else {
                strcpy(resultado, "Excluido");
            }
        }
        printf("| %.2f\t| %.2f\t| %.2f\t| %s\n", estudante.disciplinas[j].teste1, estudante.disciplinas[j].teste2, estudante.disciplinas[j].media, resultado);
    }

    printf("0. Sair\nEntrada: ");
    scanf("%i", &entrada);
    system_pause;
    system_clear;
    return;
}

// Docente...
/*
    A logica deste sistema para o docente e, quando o docente faz um cadastro
    ele deve escolher uma cadeira/disciplina para lecionar, as cadeiras sao deste semestre 
    do curso de Eng. de Processo Industriais.
*/
void cadastrar_docente(Docente docentes[], int *qtdDocentes, Disciplina disciplinas[], int tam) {
    int entrada = 0, senha = 0;
    char nome[30];

    printf("Insira o seu nome: ");
    scanf("%s", nome);
    printf("Escolhe um PIN: ");
    scanf("%i", &senha);
    {
        // Aqui o sistema verifica se o docente ja esta cadastrado, caso sim o fluxo e cortado.
        for (int j = 0 ; j < *qtdDocentes ; ++j) {
            if ((strcmp(nome, docentes[j].nome) == 0) && (docentes[j].senha == senha)) {
                printf("Docente ja cadastrado\nId: %i\n", docentes[j].id);
                system_pause;
                system_clear;
                return;
            }
        }        
    }{
        // Caso o docente nao esteja cadastrado o sistema faz o registro na sua "base de dados".
        strcpy(docentes[*qtdDocentes].nome, nome);
        docentes[*qtdDocentes].senha = senha;
    } 

    system_clear;
    printf("Id|\t|Nome da Discplina\n");
    for (int j = 0 ; j < tam ; ++j) {
        printf("%i |\t|%s\n", j+1, disciplinas[j].nome);
    }
  
    printf("Escolhe a disciplina, insira o id da disc: ");
    scanf("%i", &docentes[*qtdDocentes].idDisciplina);
    printf("0. Sair\nEntrada: ");
    scanf("%i", &entrada);
    *qtdDocentes += 1; // a cada cadastro a quantidade e incrementada. Este e o contador de docentes. sera usado para manipular o array de docentes...
    system_clear;
    return;
}

// Esta funcao vai verificar a autenticidade do docente.
bool autenticar_docente(Docente docentes[], int qtdDocentes, int *id) {
    char nome[50];
    int senha  = 0;

    printf("Insera o seu nome: ");
    scanf("%s", nome);
    printf("Insira o seu PIN: ");
    scanf("%i", &senha);

    // A verificao e feita pela busca sequencial, como e uma lista pequena...
    for (int j = 0 ; j < qtdDocentes ; ++j) {
        if ((strcmp(nome, docentes[j].nome) == 0) && (docentes[j].senha == senha)) {
            *id = j;
            return true;
        }
    }
    return false;
}

void ver_inscritos(Docente docente, Estudante estudantes[], int qtdEstudante, bool *ha_inscritos) {
    *ha_inscritos = false;
    if (qtdEstudante > 0) {
        printf("Id\tNome de Estudante\n");
        for (int j = 0 ; j < qtdEstudante ; ++j) {

            for (int i = 0 ; i < estudantes[j].qtdDisciplinas ; ++i) {
                if (estudantes[j].disciplinas[i].id == docente.idDisciplina) {
                    printf("%i\t%s\n", estudantes[j].id, estudantes[j].nome);
                    *ha_inscritos = true;
                }
            }
        }

    } else {
        printf("Sem inscritos\n");
        return;
    }
}

void lancar_notas(Docente docente, Estudante estudantes[], int qtdEstudantes) {
    int idEstudante = -1, entrada = 0;
    bool ha_inscritos = false;
    system_clear;
    float teste1 = 0, teste2 = 0, media = 0;

    do {
        ver_inscritos(docente, estudantes, qtdEstudantes, &ha_inscritos);
        if (ha_inscritos) {
            printf("Digite o id do estudante: \nEntrada: ");
            scanf("%i", &idEstudante);
            
            for (int j = 0 ; j < estudantes[idEstudante].qtdDisciplinas ; ++j) {
				if (estudantes[idEstudante].disciplinas[j].id == docente.idDisciplina) {
		
			        printf("Digite a nota do 1.o teste: ");
			        scanf("%f", &teste1);
			        printf("Digite a nota do 2.o teste: ");
			        scanf("%f", &teste2);
			        
                    { // @media...
                        // Esta operacao e do calculo da media do estudante, ou seja, o sistema calcula a media aritmetica das duas notas inseridas pelo docente.
                        if ((teste1 >= 0 && teste1 <= 20) && (teste2 >= 0 && teste2 <= 20)) {
                            estudantes[idEstudante].disciplinas[j].teste1 = teste1;
                            estudantes[idEstudante].disciplinas[j].teste2 = teste2;
                            media = (teste1 + teste2) / 2;
                            estudantes[idEstudante].disciplinas[j].media = media;
                        } else {
                            printf("Nota invalida!\n");
                            system_pause;
                            break;
                        }
                    }
					break;				
				}
			}

        } else {
            return;
        }
        system_clear;
        printf("1. Continuar\n0. Voltar\nEntrada: ");
        scanf("%i", &entrada);
        system_clear;

    } while (entrada != 0);
}

bool imprimirNotas(Estudante estudantes[], int qtdEstudantes, int idDisciplina) {
    FILE *txt_inscritos;

    txt_inscritos = fopen("lista_incritos.txt", "+a");
    if (txt_inscritos != NULL) {
		fprintf(txt_inscritos, "Nome de estudante\n");        

        for (int j = 0 ; j < qtdEstudantes ; ++j) {
            for (int i = 0 ; i < estudantes[j].qtdDisciplinas ; ++i) {
                if (estudantes[j].disciplinas[i].id == idDisciplina) {
                    fprintf(txt_inscritos, "%s", estudantes[j].nome);  
                    break;                
                }
            }
        }
        fclose(txt_inscritos);
        return true;
    }

    fclose(txt_inscritos);
    return false;
}

// Este e o array de disciplinas que e inicializado com as disciplinas do corrente semestre do curso de Eng. de Processos Industriais.
Disciplina disciplinas[MAX_TAMANHO_DISCIPLINAS] = {
    {.id = 1,.nome = "Fisica 2",.teste1 = 0,.teste2 = 0,.media = 0}, // Fisica 2
    {.id = 2,.nome = "A. Matematica 2",.teste1 = 0,.teste2 = 0,.media = 0}, // A.M.2
    {.id = 3,.nome = "INFORMATICA 2",.teste1 = 0,.teste2 = 0,.media = 0},// Info. 2
    {.id = 4,.nome = "A.L.G.A.",.teste1 = 0,.teste2 = 0,.media = 0}, // A.L.G.A
    {.id = 5,.nome = "T.E.L.P.",.teste1 = 0,.teste2 = 0,.media = 0}, // T.E.L.P.
    {.id = 6,.nome = "Desenho Tecnico",.teste1 = 0,.teste2 = 0,.media = 0}, // Desenho Tecnico 
    {.id = 7,.nome = "Quimica Analitica",.teste1 = 0,.teste2 = 0,.media = 0} // Quimica Analitica
};

Estudante estudantes[MAX_TAMANHO_ESTUDANTE]; // Array que vai guardar os 10 estudantes.
Docente docentes[MAX_TAMANHO_DOCENTE]; // Array que vai guardar os 7 docentes.

int qtdDocentes = 0, qtdEstudantes = 0, qtdDisciplinas = 7; // Quantidades iniciais das entidades do sistema.

// A funcao main(), ela vai manipular todas funcoes definidas anteriormente.
int main( ) {
    int entrada = 0;
    // os comandos goto sao os que vao implentar as funcionalidades de nas paginas do sistema, isto e, opcoes como "voltar" sao implementadas por esses comandos.
inicio: system_clear;
    printf("BEM-VINDO AO SIGA-UZ\n");
    printf("1. Seccao de Docente\n");
    printf("2. Seccao de Estudante\n");
    printf("0. Sair\nEntrada: ");
    scanf("%i", &entrada);
    system_clear;
    switch (entrada) {
    case 1: {
area_docente: system_clear;
        int entrada = 0;
        printf("Area de Docente\n");
        printf("1. Fazer cadastro\n2. Entrar\n0. Voltar\nEntrada: ");
        scanf("%i", &entrada);
        system_clear;
        switch (entrada) {
        case 0:
            goto inicio;
            break;
        case 1:
            cadastrar_docente(docentes, &qtdDocentes, disciplinas, qtdDisciplinas);
            goto area_docente;
            break;
        case 2:
        {
            int idDocente = 0, entrada = 0;
            if (autenticar_docente(docentes, qtdDocentes, &idDocente)) {
acessado: system_clear;
                printf("Acesso autorizado\n");
                printf("Nome de docente: %s\n", docentes[idDocente].nome);
                printf("Disciplina: %s\n", disciplinas[docentes[idDocente].idDisciplina - 1].nome);
                printf("1. Ver inscritos\n2. Lancar Notas\n3. Imprimir Notas\n0. Voltar\nEntrada: ");
                scanf("%i", &entrada);
                system_clear;
                switch (entrada) {
                case 1: {
                    bool n;
                    ver_inscritos(docentes[idDocente], estudantes, qtdEstudantes, &n);
                    system_pause;
                    goto acessado;
                }
                break;
                case 2:
                    lancar_notas(docentes[idDocente], estudantes, qtdEstudantes);
                    system_pause;
                    goto acessado;
                    break;
                case 3:
                    if (imprimirNotas(estudantes, qtdEstudantes, docentes[idDocente].idDisciplina)) {
                        printf("Sucesso lista ja disponivel\n");
                    } else {
                        printf("Falha, houve um erro ao solicitar a lista\n");
                    }
                    system_pause;
                    goto acessado;
                    break;    
                case 0:
                    goto area_docente;
                default:
                    printf("Entrada Invalida!\n");
                    goto acessado;
                    break;
                }
            }
            else {
                printf("Dados Incorretos\n");
                system_pause;
                goto area_docente;
            }
        }
        }
    }
    break;
	case 2: {
area_estudante: system_clear;
    int entrada = 0, idEstudante = -1;
    printf("1. Cadastrar\n2. Entrar\n0. Voltar\nEntrada: ");
    scanf("%i", &entrada);
    system_clear;
    switch (entrada) {
        case 0:
            goto inicio;
            break;
        case 1:
            cadastrar_estudante(estudantes, &qtdEstudantes);
            goto area_estudante;
            break;
        case 2: {
            if (autenticar_estudante(estudantes, qtdEstudantes, &idEstudante)) {
area_estudante_verificado: system_clear;
                printf("Acesso autorizado\n");
                printf("1. Inscrever-se a disciplinas\n2. Ver notas\n0. Voltar\nEntrada: ");
                scanf("%i", &entrada);
                system_clear;
                switch (entrada) {
                    case 1:
                        inscrever_disciplina(disciplinas, qtdDisciplinas, &estudantes[idEstudante]);
                        goto area_estudante_verificado;
                        break;
                    case 2:
                        ver_notas(estudantes[idEstudante]);
                        goto area_estudante_verificado;
                        break;
                    case 0:
                        goto area_estudante;
                        break;
                    default:
                        printf("Entrada Invalida!\n");
                        goto area_estudante_verificado;
                        break;
                }
        } else {
            printf("Dados Incorretos\n");
            goto area_estudante;
        }		
		break;
	}
	}				
		break;	
	}
    case 0:
        exit(0);
    default:
        printf("Entrada Invalida!\n");
        goto inicio;
    }
    return 0;
}