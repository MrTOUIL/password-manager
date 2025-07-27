#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>

#define MAX 100
#define SHIFT 3

// Structure des données
typedef struct Node {
    char id[50];
    char password[50];
    char platform[50];
    struct Node* next;
} Node;

Node* head = NULL;

// Chiffrement César
void encrypt(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] += SHIFT;
    }
}

void decrypt(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] -= SHIFT;
    }
}

// Créer un nouveau noeud
Node* createNode(char* id, char* pass, char* plat) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->id, id);
    strcpy(newNode->password, pass);
    strcpy(newNode->platform, plat);
    newNode->next = NULL;
    return newNode;
}

// Ajouter un mot de passe
void addPassword(char* id, char* pass, char* plat) {
    encrypt(pass);
    Node* newNode = createNode(id, pass, plat);
    newNode->next = head;
    head = newNode;
}

// Afficher les mots de passe
void viewPasswords() {
    clear();
    attron(COLOR_PAIR(3));
    printw("\nListe des mots de passe:\n\n");
    attroff(COLOR_PAIR(3));

    Node* temp = head;
    while (temp) {
        char decrypted[50];
        strcpy(decrypted, temp->password);
        decrypt(decrypted);

        attron(COLOR_PAIR(2));
        printw("Plateforme: %s\nIdentifiant: %s\nMot de passe: %s\n\n", temp->platform, temp->id, decrypted);
        attroff(COLOR_PAIR(2));

        temp = temp->next;
    }
    getch();
}

// Modifier un mot de passe
void modifyPassword(char* id) {
    Node* temp = head;
    while (temp) {
        if (strcmp(temp->id, id) == 0) {
            char newpass[50];
            echo();
            mvprintw(15, 2, "Nouveau mot de passe: ");
            getstr(newpass);
            noecho();
            encrypt(newpass);
            strcpy(temp->password, newpass);
            return;
        }
        temp = temp->next;
    }
}

// Supprimer un mot de passe
void deletePassword(char* id) {
    Node *temp = head, *prev = NULL;
    while (temp && strcmp(temp->id, id) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return;
    if (!prev)
        head = head->next;
    else
        prev->next = temp->next;
    free(temp);
}

// Menu animé
void animateQuit() {
    clear();
    attron(COLOR_PAIR(4));
    mvprintw(5, 10, "Merci d'avoir utilise le gestionnaire !\n");
    mvprintw(7, 10, "TOUIL ABDEREZAK - ETUDIANT ESI ALGER");
    mvprintw(9, 10, "HAMIDI SELMA - ETUDIANTE USTHB");
    attroff(COLOR_PAIR(4));
    refresh();
    sleep(3);
}

// Interface interactive
void interactiveMenu() {
    char* options[] = {
        "1.Ajouter un mot de passe",
        "2.Afficher les mots de passe",
        "3.Modifier un mot de passe",
        "4.Supprimer un mot de passe",
        "5.Quitter"
    };
    int choice = 0, ch;

    while (1) {
        clear();
        box(stdscr, 0, 0);
        attron(COLOR_PAIR(1));
        mvprintw(1, 2, "=== Gestionnaire de mots de passe ===");
        attroff(COLOR_PAIR(1));

        for (int i = 0; i < 5; i++) {
            if (i == choice)
                attron(A_REVERSE);
            mvprintw(3 + i, 4, options[i]);
            if (i == choice)
                attroff(A_REVERSE);
        }

        ch = getch();
        switch (ch) {
            case KEY_UP:    choice = (choice + 4) % 5; break;
            case KEY_DOWN:  choice = (choice + 1) % 5; break;
            case '\n':
                if (choice == 0) {
                    char id[50], pass[50], plat[50];
                    echo();
                    mvprintw(10, 2, "Identifiant: "); getstr(id);
                    mvprintw(11, 2, "Mot de passe: "); getstr(pass);
                    mvprintw(12, 2, "Plateforme: "); getstr(plat);
                    noecho();
                    addPassword(id, pass, plat);
                } else if (choice == 1) {
                    viewPasswords();
                } else if (choice == 2) {
                    char id[50];
                    echo();
                    mvprintw(10, 2, "Identifiant à modifier: "); getstr(id);
                    noecho();
                    modifyPassword(id);
                } else if (choice == 3) {
                    char id[50];
                    echo();
                    mvprintw(10, 2, "Identifiant à supprimer: "); getstr(id);
                    noecho();
                    deletePassword(id);
                } else {
                    animateQuit();
                    return;
                }
                break;
        }
    }
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);

    interactiveMenu();

    endwin();
    return 0;
}
