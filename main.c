#include "tree.c"
#include "edit_distance.c"

int limit;

void hint(char wrong_word[50], Node* tree, int sensibility) {
    if(tree == NULL || limit <= 0)
		return;
	hint(wrong_word, tree->left, sensibility);

    memset(dp, -1, sizeof(dp));

    int len_a = strlen(wrong_word);
    int len_b = strlen(tree->str);

    int dist = edit_distance(wrong_word, tree->str, len_a, len_b, 0, 0);

    if(dist <= sensibility) {
        limit--;
        printf("%s ", tree->str);
    }

	hint(wrong_word, tree->right, sensibility);
}

int menu() {
    system("cls");
    printf("1 - Inserir palavra no dicionario\n");
    printf("2 - Inserir palavra incorreta e veja a sugestao\n");
    printf("3 - Sensibilidade\n");
    printf("4 - Mostrar Dicionario\n");
    printf("5 - Inserir dicionario a partir de um arquivo (uma palavra por linha)\n");
    printf("6 - Sair\n");
    int i; scanf("%d", &i);
    getchar();
    return i;
}

void tirar_newline(char buf[50]) {
    if(buf[strlen(buf)-1] == '\n') {
        buf[strlen(buf)-1] = 0;
    }
}

int main() {
    Node* tree = NULL;

    char buf[50];

    // até 3 pontos de distancia a palavra é considerada na sugestão
    int sensibility = 3;

    while(1) {
        switch (menu())
        {
        case 1: {
            printf("Digite uma palavra\n");
            fgets(buf, 50, stdin);
            tirar_newline(buf);
            if(inserir(&tree, buf)) {
                printf("Palavra inserida com sucesso\n");
            } else {
                printf("Palavra ja existe no dicionario\n");
            }
            getchar();
            break;
        }

        case 2: {
            if(tree == NULL) {
                printf("O dicionario esta vazio\n");
                getchar();
                break;
            }
            printf("Digite uma errada\n");
            fgets(buf, 50, stdin);
            tirar_newline(buf);

            if(buscar(tree, buf) == 1) {
                printf("A palavra ja existe no dicionario\n");
                getchar();
                break;
            }

            printf("Sugestoes\n\n");
            limit = 10;
            hint(buf, tree, sensibility);
            printf("\n");
            getchar();
            break;
        }

        case 3: {
            printf("Digite a nova sensibilidade\n");
            scanf("%d", &sensibility);
            printf("Sensibilidade alterada com sucesso\n");
            getchar();
            break;
        }
        
        case 4: {
            percorrer(tree);
            getchar();
            break;
        }

        case 5: {
            printf("Digite o nome do arquivo\n");
            fgets(buf, 50, stdin);
            tirar_newline(buf);

            FILE* fp = fopen(buf, "r");

            while(fscanf(fp, "%s", buf) != EOF) {
                inserir(&tree, buf);
            }

            printf("Dicionario carregado com sucesso\n");

            fclose(fp);
            getchar();
            break;
        }

        case 6: {
            return 0;
        }

        default:
            break;
        }
    }

    return 0;  
}