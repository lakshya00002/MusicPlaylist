#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct songData
{
    char *name;
    char *artist;
    char *album;
};

struct songNode
{
    struct songData song_Data;
    struct songNode *next;
    struct songNode *prev;
};

void create_playlist(struct songNode **head, struct songNode **tail, char *song_name, char *Artist_name, char *Album)
{
    struct songNode *s = (struct songNode *)malloc(sizeof(struct songNode));
    s->song_Data.name = strdup(song_name);
    s->song_Data.artist = strdup(Artist_name);
    s->song_Data.album = strdup(Album);
    s->next = NULL;
    if (*head == NULL)
    {
        *head = s;
        *tail = s;
        s->prev = NULL;
    }
    else
    {
        s->prev = *tail;
        (*tail)->next = s;
        (*tail) = s;
    }
}

void add_song(struct songNode *head, struct songNode **tail, char *song_name, char *Artist_name, char *Album)
{
    int n;
    struct songNode *s = (struct songNode *)malloc(sizeof(struct songNode));
    s->song_Data.name = strdup(song_name);
    s->song_Data.artist = strdup(Artist_name);
    s->song_Data.album = strdup(Album);
    s->next = NULL;
    printf("enter 1 for add at end\n2 for in between\n");
    scanf("%d", &n);

    if (n == 1)
    {
        s->prev = *tail;
        (*tail)->next = s;
        (*tail) = s;
    }

    if (n == 2)
    {
        int ind, i = 1;
        printf("enter index\n");
        scanf("%d", &ind);
        struct songNode *ptr;
        struct songNode *ptr_next;
        ptr = head;
        while (i < ind)
        {
            ptr = ptr->next;
            i++;
        }
        ptr_next = ptr->next;
        s->prev = ptr;
        ptr->next = s;
        s->next = ptr_next;
        ptr_next->prev = s;
    }
}

void next_song(struct songNode **current_playing, struct songNode *head)
{
    if ((*current_playing)->next == NULL)
    {
        (*current_playing) = head;
    }
    else
    {
        (*current_playing) = (*current_playing)->next;
    }
}

void previous_song(struct songNode **current_playing, struct songNode *tail)
{
    if ((*current_playing)->prev == NULL)
    {
        (*current_playing) = tail;
    }
    else
    {
        (*current_playing) = (*current_playing)->prev;
    }
}

void now_playing(struct songNode *current_playing)
{
    if (current_playing != NULL)
    {
        printf("current playing song's name is: %s\n", current_playing->song_Data.name);
        printf("current playing song's artist is: %s\n", current_playing->song_Data.artist);
        printf("current playing song's album is: %s\n", current_playing->song_Data.album);
    }
    else
    {
        printf("currently song is not playing\n");
    }
}

void shuffle_playlist(struct songNode *head)
{
    int i = 0;
    struct songNode *ptr = head;
    while (ptr != NULL)
    {
        ptr = ptr->next;
        i++;
    }
    srand(time(NULL));
    for (int j = 0; j < i; j++)
    {
        ptr = head;
        struct songNode *ptr1 = head;
        int k = 0;
        int q = 0;
        int random_number1 = rand() % i;
        int random_number2 = rand() % i;
        while (k < random_number1 && ptr->next != NULL)
        {
            ptr = ptr->next;
            k++;
        }

        while (q < random_number2 && ptr1->next != NULL)
        {
            ptr1 = ptr1->next;
            q++;
        }

        struct songData temp = ptr->song_Data;
        ptr->song_Data = ptr1->song_Data;
        ptr1->song_Data = temp;
    }
}

void repeat_song(struct songNode **current_playing)
{
    if (*current_playing != NULL)
    {
        *current_playing = *current_playing;
    }
}

void repeatPlaylist(struct songNode *head, struct songNode **current_playing)
{
    if (head == NULL)
    {
        printf("Playlist is empty.\n");
        return;
    }

    printf("Repeating the playlist:\n");
    *current_playing = head;
}

void display_playlist(struct songNode *head)
{
    struct songNode *ptr = head;
    while (ptr != NULL)
    {
        printf("song's name is: %s\n", ptr->song_Data.name);
        printf("song's artist is: %s\n", ptr->song_Data.artist);
        printf("song's album is: %s\n", ptr->song_Data.album);
        printf("\n");
        ptr = ptr->next;
    }
}

void remove_song(struct songNode *ptr, struct songNode **head, struct songNode **tail)
{
    if (ptr->next != NULL && ptr != *head)
    {
        struct songNode *prev = ptr->prev;
        prev->next = ptr->next;
        ptr->next->prev = prev;
        free(ptr);
    }
    else if (ptr == *head)
    {
        *head = ptr->next;
        free(ptr);
    }
    else
    {
        struct songNode *prev = ptr->prev;
        *tail = prev;
        prev->next = NULL;
        free(ptr);
    }
}

void removeSongByTitle(struct songNode **head, char *songname, struct songNode **tail)
{
    struct songNode *ptr = *head;
    while (ptr != NULL && strcmp(ptr->song_Data.name, songname) != 0)
    {
        ptr = ptr->next;
    }
    if (ptr != NULL)
    {
        remove_song(ptr, head, tail);
    }
    else
    {
        printf("No song found with this title\n");
    }
}

void removeSongByArtist(struct songNode **head, char *artist, struct songNode **tail)
{
    struct songNode *ptr = *head;
    while (ptr != NULL && strcmp(ptr->song_Data.artist, artist) != 0)
    {
        ptr = ptr->next;
    }
    if (ptr != NULL)
    {
        remove_song(ptr, head, tail);
    }
    else
    {
        printf("No song found with this artist\n");
    }
}

void removeSongByPosition(struct songNode **head, int ind, struct songNode **tail)
{
    struct songNode *ptr = *head;
    int i = 0;
    while (ptr != NULL && i < ind)
    {
        ptr = ptr->next;
        i++;
    }
    if (ptr != NULL)
    {
        remove_song(ptr, head, tail);
    }
    else
    {
        printf("No song found at this position\n");
    }
}


int main()
{
    struct songNode *head = NULL;
    struct songNode *tail = NULL;
    char *song_name, Artist_name, Album;
    create_playlist(&head, &tail, song_name, Artist_name, Album);
    add_song(head, &tail, song_name, Artist_name, Album);
    struct songNode *current_playing;
    next_song(&current_playing, head);
    previous_song(&current_playing, tail);
    now_playing(current_playing, head);
    shuffle_playlist(head);
    repeat_song(&current_playing);
    repeatPlaylist(head, &current_playing);
    display_playlist(head);
    return 0;
}
