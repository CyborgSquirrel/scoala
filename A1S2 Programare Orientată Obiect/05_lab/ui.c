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
    printf("4. Afisare criteriu cantitate mai mica\n");
    printf("5. Afisare criteriu cantitate mai mare\n");
    printf("6. Afisare ordonat crescator\n");
    printf("7. Afisare ordonat descrescator\n");
    printf("8. Undo\n");
}

void add(UI* user_interface)
{
    char nume[30];
    char producator[30];
    float cant;
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
void ui_printbycriteria(UI* user_interface)
{
    int i;
    float cantitate;
    printf("Dati cantitatea maxima pe care trebuie sa o aiba materia prima: ");
    scanf("%f", &cantitate);
    Vec* print = criterialist(user_interface->srv,cantitate);
    if (print->lg== 0)
    {
        printf("Nu exista nicio materie prima cu cantitatea mai mica decat cea data\n");
    }
    else
    {
        for (i = 0;i < print->lg;i++)
        {
            Materie* temp;
            vec_get(print, &temp, i);
            printf("nume: %s\n\tproducator: %s\n\tcantitate: %f\n\n",temp->nume, temp->producator, temp->cantitate);

        }
    }
    destroy_vec(print);
}

void ui_printbycriteria_above(UI* user_interface)
{
    int i;
    float cantitate;
    printf("Dati cantitatea minima pe care trebuie sa o aiba materia prima: ");
    scanf("%f", &cantitate);
    Vec* print = criterialist_above(user_interface->srv,cantitate);
    if (print->lg== 0)
    {
        printf("Nu exista nicio materie prima cu cantitatea mai mare decat cea data\n");
    }
    else
    {
        for (i = 0;i < print->lg;i++)
        {
            Materie* temp;
            vec_get(print, &temp, i);
            printf("nume: %s\n\tproducator: %s\n\tcantitate: %f\n\n",temp->nume, temp->producator, temp->cantitate);

        }
    }
    destroy_vec(print);
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
    // int rez = modifyEntity(user_interface->srv, nume, producator, cant);
    // if (rez == 0)
    //     printf("Modificare realizata cu succes!\n");
    // else
    //     if (rez == -1)
    //         printf("Nu exista materie prima cu acest nume\n");
    //     else
    //         printf("Datele materiei prime sunt incorecte\n");
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

void ui_printsorted(UI* user_interface)
{
    int i;
    Vec* print = ascendingCantitateSort(user_interface->srv);
    if (print->lg == 0)
    {
        printf("Nu exista nicio materie prima\n");
    }
    else
    {
        for (i = 0;i < print->lg;i++)
        {
            Materie* temp;
            vec_get(print, &temp, i);
            printf("nume: %s\n\tproducator: %s\n\tcantitate: %f\n\n", temp->nume, temp->producator, temp->cantitate);

        }
    }
    destroy_vec(print);
}
void ui_printsorted_descending(UI* user_interface)
{
    int i;
    Vec* print = descendingCantitateSort(user_interface->srv);
    if (print->lg == 0)
    {
        printf("Nu exista nicio materie prima\n");
    }
    else
    {
        for (i = 0;i < print->lg;i++)
        {
            Materie* temp;
            vec_get(print, &temp, i);
            printf("nume: %s\n\tproducator: %s\n\tcantitate: %f\n\n", temp->nume, temp->producator, temp->cantitate);

        }
    }
    destroy_vec(print);
}

void ui_undo(UI* user_interface)
{
	int rez = undo(user_interface->srv);
	if (rez == 0) printf("Ultima operatie a fost refacuta cu succes!\n");
	else printf("Nu mai exista operatii care sa fie refacute\n");
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
            ui_printbycriteria_above(user_interface);
            break;
        case 6:
            ui_printsorted(user_interface);
            break;
        case 7:
            ui_printsorted_descending(user_interface);
            break;
        case 8:
            ui_undo(user_interface);
            break;
        case 0:
            return;
        default:
            printf("Comanda invalida\n");
            break;
        }
    }
}
