#include <openssl/md5.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct charlist charlist_t;
struct charlist
{
	unsigned char character;
	charlist_t* next;
};

charlist_t* new_charlist_element()
{
	charlist_t* element;

	if ((element = malloc(sizeof(charlist_t))) != 0)
	{
		element->character = 0;
		element->next = NULL;
	}
	else
	{
		perror("malloc() failed.");
	}

	return element;
}

void free_charlist(charlist_t* list)
{
	charlist_t* current = list;
	charlist_t* next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void print_charlist(charlist_t* list)
{
	charlist_t* next = list;
	while (next != NULL)
	{
		printf("%d ", next->character);
		next = next->next;
	}
	printf("\n");
}

void next(charlist_t* list)
{
	list->character++;
	if (list->character == 0)
	{
		if (list->next == NULL)
		{
			list->next = new_charlist_element();
		}
		else
		{
			next(list->next);
		}
	}
}

int main()
{
	charlist_t* sequence;
	sequence = new_charlist_element();

	while (1)
	{
		next(sequence);
		print_charlist(sequence);
	}

	free_charlist(sequence);
}