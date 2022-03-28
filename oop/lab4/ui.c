#include "ui.h"
UI* create_ui(Service* srv)
{
	UI* user_interface = malloc(sizeof(UI));
	user_interface->srv = srv;
	return user_interface;
}
void destroy_ui(UI* user_interface)
{
    destroy_service(user_interface->srv);
	free(user_interface);
}
void menu()
{
    printf("Alegeti una dintre urmatoarele optiuni: \n");
    printf("0. Exit\n");
    printf("1. Adaugare materie prima\n");
    printf("2. Modificare materie prima\n");
    printf("3. Stergere materie prima\n");
    printf("4 .Afisare criteriu\n");
    printf("5. Afisare ordonat\n");
}

void add(UI* user_interface)
{
    char nume[30];
    char producator[30];
    float cant;
    // CODEREVIEW: nu merge sa pui nume/producator cu spatii
    printf("Dati numele materiei prime: ");
    scanf("%s", nume);
    printf("Dati numele producatorului: ");
    scanf("%s", producator);
    printf("Dati cantitate: ");
    scanf("%f", &cant);
    if (addEntity(user_interface->srv,nume, producator, cant) == 0)
        printf("Comanda realizata cu succes!\n");
    else
        printf("Comanda nereusita!\n");


}

// CODEREVIEW: si aici cred ca apare un memory leak
void ui_printbycriteria(UI* user_interface)
{
    int i;
    float cantitate;
    printf("Dati cantitatea maxima pe care trebuie sa o aiba materia prima: ");
    scanf("%f", &cantitate);
    Lista* print = criterialist(user_interface->srv,cantitate);
    if (print->lg== 0)
    {
        printf("Nu exista nicio materie prima cu cantitatea mai mica decat cea data\n");
    }
    else
    {
        for (i = 0;i < print->lg;i++)
        {
            Materie* temp = get(print, i);
            printf("nume: %s\n\tproducator: %s\n\tcantitate: %f\n\n",temp->nume, temp->producator, temp->cantitate);

        }
    }
}

void ui_modify(UI* user_interface)
{
    char nume[30];
    char producator[30];
    float cant;
    printf("Dati noile informatii: \n");
    printf("Dati numele materiei prime: ");
    scanf("%s", nume);
    printf("Dati numele producatorului: ");
    scanf("%s", producator);
    printf("Dati cantitate: ");
    scanf("%f", &cant);
    int rez = modifyEntity(user_interface->srv, nume, producator, cant);
    if (rez == 0)
        printf("Modificare realizata cu succes!\n");
    else
        if (rez == -1)
            printf("Nu exista materie prima cu acest nume\n");
        else
            printf("Datele materiei prime sunt incorecte\n");
}

void delete(UI* user_interface)
{
    char name[30];
    printf("Dati numele materiei prime pe care doriti sa o eliminati: ");
    scanf("%s", name);
    if (deleteEntity(user_interface->srv,name) == 0)
    {
        printf("Comanda realizata cu succes!\n");
    }
    else
    {
        printf("Nu exista materie prima cu numele dat\n");
    }
}

// CODEREVIEW: cred ca aici apare un memory leak
void ui_printsorted(UI* user_interface)
{
    int i;
    Lista* print = sortedEntities(user_interface->srv);
    if (print->lg == 0)
    {
        printf("Nu exista nicio materie prima\n");
    }
    else
    {
        for (i = 0;i < print->lg;i++)
        {
            Materie* temp = get(print, i);
            printf("nume: %s\n\tproducator: %s\n\tcantitate: %f\n\n", temp->nume, temp->producator, temp->cantitate);

        }
    }
}

void run(UI* user_interface)
{
    menu();
    int command = 0;
    while (1)
    {
        
        scanf("%d",&command);
        switch (command)
        {
        case 1:
            add(user_interface);
            break;
        case 2:
            ui_modify(user_interface);
            break;
        case 3:
            delete(user_interface);
            break;
        case 4:
            ui_printbycriteria(user_interface);
            break;
        case 5:
            ui_printsorted(user_interface);
            break;
        case 0:
            return;
        default:
            printf("Comanda invalida\n");
            break;
        }
    }
}
