#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>

struct Lista
{
    int nr_klienta;
    struct Lista *next;
};

sem_t klienci;
sem_t fryzjer;
pthread_mutex_t fotel;
pthread_mutex_t poczekalnia;

int liczbaMiejsc=10;
int liczbaKrzesel=10;
int nie_weszli=0;
int czas_fryzjera=2;
int czas_klienta=8;
bool debug=false;
bool skonczone=false;
int akt_klient=-1;

void czekaj(int sec)
{
    int x = (rand()%sec) * (rand()%1000000) + 1000000;
    usleep(x);
}

struct Lista *odrzuceni = NULL;
struct Lista *czekajacy = NULL;

void Wypisz_odrzuceni()
{
    struct Lista *temp = odrzuceni;
    printf("Nie weszli: ");
    while(temp!=NULL)
    {
        printf("%d ",temp->nr_klienta);
        temp = temp->next;
    }
    printf("\n");
}
void Wypisz_czekajacy()
{
    struct Lista *temp = czekajacy;
    printf("Czekaja : ");
    while(temp!=NULL)
    {
        printf("%d " ,temp->nr_klienta);
        temp = temp->next;
    }
    printf("\n");
}
void Umiesc_odrzuceni(int x)
{
    struct Lista *temp = (struct Lista*)malloc(sizeof(struct Lista));
    temp->nr_klienta = x;
    temp->next = odrzuceni;
    odrzuceni = temp;
    Wypisz_odrzuceni();
}
void Umiesc_czekajacy(int x)
{
    struct Lista *temp = (struct Lista*)malloc(sizeof(struct Lista));
    temp->nr_klienta = x;
    temp->next = czekajacy;
    czekajacy = temp;

    Wypisz_czekajacy();
}
void usun_klienta(int x)
{
    struct Lista *temp = czekajacy;
    struct Lista *pop = czekajacy;
    while (temp!=NULL)
    {
        if(temp->nr_klienta==x)
        {
            if(temp->nr_klienta==czekajacy->nr_klienta)
            {
                czekajacy=czekajacy->next;
                free(temp);
            }
            else
            {
                pop->next=temp->next;
                free(temp);
            }
            break;
        }
        pop=temp;
        temp=temp->next;
    }
    Wypisz_czekajacy();

}

void *Klient(void *nr_klienta)
{
    czekaj(czas_klienta);
    int nr = *(int *)nr_klienta;
    pthread_mutex_lock(&poczekalnia);
    if(liczbaMiejsc>0)
    {
        liczbaMiejsc--;
        printf("Res:%d WRomm: %d/%d [in: %d]  -  zajeto miejsce w poczekalni\n",nie_weszli, liczbaKrzesel-liczbaMiejsc, liczbaKrzesel, akt_klient);
        if(debug==true)
        {
            Umiesc_czekajacy(nr);
        }
        sem_post(&klienci);
        pthread_mutex_unlock(&poczekalnia);
        sem_wait(&fryzjer);
        pthread_mutex_lock(&fotel);
        akt_klient=nr;
        printf("Res:%d WRomm: %d/%d [in: %d]  -  zaczeto scinac\n",nie_weszli, liczbaKrzesel-liczbaMiejsc, liczbaKrzesel, akt_klient);
        if(debug==true)
        {
            usun_klienta(nr);
        }
    }
    else
    {
        pthread_mutex_unlock(&poczekalnia);
        nie_weszli++;
        printf("Res:%d WRomm: %d/%d [in: %d]  -  klient nie wszedl\n",nie_weszli, liczbaKrzesel-liczbaMiejsc, liczbaKrzesel, akt_klient);
        if(debug==true)
        {
            Umiesc_odrzuceni(nr);
        }
    }
}
void *Fryzjer()
{
    while(!skonczone)
    {
    if(!skonczone){
        sem_wait(&klienci);
        pthread_mutex_lock(&poczekalnia);
        liczbaMiejsc++;
        pthread_mutex_unlock(&poczekalnia);
        sem_post(&fryzjer);
        czekaj(czas_fryzjera);
        printf("Res:%d WRomm: %d/%d [in: %d]  -  skonczono scinac\n",nie_weszli, liczbaKrzesel-liczbaMiejsc, liczbaKrzesel, akt_klient);
        pthread_mutex_unlock(&fotel);
        }
    }
    printf("fryzjer idzie do domu\n");
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    static struct option parametry[] =
    {
        {"klient", required_argument, NULL, 'k'},
        {"krzesla", required_argument, NULL, 'r'},
        {"czas_k", required_argument, NULL, 'c'},
        {"czas_f", required_argument, NULL, 'f'},
        {"debug", no_argument, NULL, 'd'}

    };
    int liczbaKlientow =20;
    int wybor = 0;
    while((wybor = getopt_long(argc, argv, "k:r:c:f:d",parametry,NULL)) != -1)
    {
        switch(wybor)
        {
        case 'k':
            liczbaKlientow=atoi(optarg);
            break;
        case 'r':
            liczbaMiejsc=atoi(optarg);
            liczbaKrzesel=atoi(optarg);
            break;
        case 'c':
            czas_klienta=atoi(optarg);
            break;
        case 'f':
            czas_fryzjera=atoi(optarg);
            break;
        case 'd':
            debug=true;
            break;
        }
    }

    pthread_t *klienci_watki = malloc(sizeof(pthread_t)*liczbaKlientow);
    pthread_t fryzjer_watek;
    int *tablica=malloc(sizeof(int)*liczbaKlientow);

    int i;
    for (i=0; i<liczbaKlientow; i++)
    {
        tablica[i] = i;
    }

    sem_init(&klienci,0,0);
    sem_init(&fryzjer,0,0);

    pthread_mutex_init(&fotel, NULL);
    pthread_mutex_init(&poczekalnia, NULL);
    pthread_create(&fryzjer_watek, NULL, Fryzjer, NULL);

    for (i=0; i<liczbaKlientow; ++i)
    {
        pthread_create(&klienci_watki[i], NULL, Klient, (void *)&tablica[i]);
    }

    for (i=0; i<liczbaKlientow; i++)
    {
        pthread_join(klienci_watki[i],NULL);
    }
    skonczone=true;
    pthread_join(fryzjer_watek,NULL);

    pthread_mutex_destroy(&fotel);
    pthread_mutex_destroy(&poczekalnia);
    sem_destroy(&klienci);
    sem_destroy(&fryzjer);
    free(czekajacy);
    free(odrzuceni);
    return 0;
}
