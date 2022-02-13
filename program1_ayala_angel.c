//Angel Ayala
//Dr. Steinberg
//COP3502C Spring 2022
//Programming Assignment 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LIMIT 20

char ** doubleIt(char **arr, int *maxsize); 
char ** populate(char ** words, FILE *fptr, int *currentsize, int *maxsize);
char* generateSentence(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize); //write sentence to console window
void generateStory(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize, FILE *fptr); //write story to txt file
void displaySentence(char * sentence);
void cleanUp(char ** nouns, char ** verbs, char ** adjectives, char ** prepositions, char ** articles, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize);

int main()
{
	//setup randomness
	int x;
	printf("Enter seed: ");
	scanf("%d", &x);
	srand(x); //set seed
	
	//declare necessary variables
	int nounsize = 0;
	int verbsize = 0;
	int adjsize = 0;
	int prepositionsize = 0;
	
	int nounmaxsize = 5;
	int verbmaxsize = 5;
	int adjmaxsize = 5;
	int prepositionmaxsize = 5;
	const int articlemaxsize = 3; //there are only 3 articles in the english language a, an, and the. that is why const is applied
	
	printf("Welcome to the random sentence generator.\n");
	
	//double pointers
	char ** nouns = NULL;
	char ** verbs = NULL;
	char ** adjectives = NULL;
	char ** preposition = NULL;
	char ** articles = NULL;
	
	nouns = (char **) malloc(sizeof(char *) * nounmaxsize); 
	verbs = (char **) malloc(sizeof(char *) * verbmaxsize);
	adjectives = (char **) malloc(sizeof(char *) * adjmaxsize); 
	preposition = (char **) malloc(sizeof(char *) * prepositionmaxsize); 
	articles = (char **) malloc(sizeof(char *) * articlemaxsize); 
	
	//make sure malloc was able to allocate memory
	if(nouns == NULL || verbs == NULL || adjectives == NULL || preposition == NULL || articles == NULL) 
	{
		printf("malloc was not successful\n");
		printf("Program will now terminate.\n");
		exit(1);
	}
	
	//populate articles using strcpy. numbers represent how many characters are needed. this includes \0 character
	articles[0] = (char *) malloc(sizeof(char) * 2);
	strcpy(articles[0], "A");
	articles[1] = (char *) malloc(sizeof(char) * 3);
	strcpy(articles[1], "An");
	articles[2] = (char *) malloc(sizeof(char) * 4);
	strcpy(articles[2], "The");
	
	//open the file of words
	FILE *fptr = fopen("nouns.txt", "r");
	FILE *fptr2 = fopen("verbs.txt", "r");
	FILE *fptr3 = fopen("adjectives.txt", "r");
	FILE *fptr4 = fopen("preposition.txt", "r");
	
	//make sure the files were opened properly
	if(fptr == NULL || fptr2 == NULL || fptr3 == NULL || fptr4 == NULL)
	{
		printf("file was not successful in opening.");
		printf("Program will now terminate.\n");
		exit(1);
	}
	
	//populate the dynamic array
	nouns = populate(nouns, fptr, &nounsize, &nounmaxsize); //populate nouns
	verbs = populate(verbs, fptr2, &verbsize, &verbmaxsize); //populate verbs
	adjectives = populate(adjectives, fptr3, &adjsize, &adjmaxsize); //populate adjectives
	preposition = populate(preposition, fptr4, &prepositionsize, &prepositionmaxsize); //populate prepositions
	
	//close the files
	fclose(fptr);
	fclose(fptr2);
	fclose(fptr3);
	fclose(fptr4);
	
	//now lets generate 5 sentences and write them to the console window
	
	printf("Let's generate some random sentences that don't make sense.\n");
	
	for(int x = 0; x < 5; ++x)
	{
		char * sentence = generateSentence(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize);
		displaySentence(sentence);
		free(sentence);
	}
	
	printf("Now let's create three stories that just don't make sense.\n");
	fptr = fopen("story1.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 1
	fclose(fptr);
	
	fptr = fopen("story2.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 2
	fclose(fptr);

	fptr = fopen("story3.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 3
	fclose(fptr);

	cleanUp(nouns,verbs, adjectives, preposition, articles, nounmaxsize, verbmaxsize, adjmaxsize, prepositionmaxsize, 3);

	
	printf("The stories were generated successfully and stored in their respective text files.\n");
	printf("Check them out!\n");
	
	return 0;
}

//Doubles the heap space if needed
char ** doubleIt(char **arr, int *maxsize)
{
	char ** head = NULL;
	//New string array double size of argument array
	char ** tmp = (char**)malloc(2 * sizeof(char*) * *maxsize);

	//Check if memory allocation was successful
	if (tmp == NULL)
	{
		printf("malloc was not successful\n");
		printf("Program will now terminate.\n");
		exit(1);
	}

	//Allocate space for each word and populate each space with word from old array
	for (int i = 0; i < *maxsize; ++i)
	{
		tmp[i] = (char*) malloc(sizeof(char) * LIMIT);
		if(tmp[i] == NULL)
		{
			printf("Oh no... malloc wasn't successful\n");
			exit(1);
		}
		tmp[i] = arr[i];
		free(arr[i]);
	}

	//Free old array
	free(arr);
	arr = NULL;

	//Point to first element in array
	head = tmp;

    
    return head;
}





char ** populate(char ** words, FILE *fptr, int *currentsize, int *maxsize)
{

    //Alocate heap space for each word in array
	for(int x = 0; x < *maxsize; ++x)
	{
		words[x] = (char*) malloc(sizeof(char) * LIMIT);
		if(words[x] == NULL)
		{
			printf("Oh no... malloc wasn't successful\n");
			exit(1);
		}
		//Double heap space when array is full
        while (26 > *maxsize)
        {
            words = doubleIt(words, &*maxsize);
            *maxsize *= 2;
        }
	}
	//Populate string array with file
    while(fscanf(fptr, "%s\n", words[*currentsize]) == 1)
    {
        ++*currentsize;
    }

    return words;
}


//Generate a random sentence given 
char * generateSentence(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize)
{
	//Maximum number of characters in each sentence
    int size = 100;

    //Allocating memory for a string with a max of 100 characters
    char *sentence = (char *) malloc(sizeof(char) * size);
    //Make sure memory allocation was successful
    if (sentence == NULL)
    {
        printf("Oh no... malloc wasn't successful\n");
        exit(1);
    }

   
    //Series of string concatenations to consruct a sentence
    strcat(strcpy(sentence, article[rand() % articlesize]), " ");
    strcat(strcat(sentence, adjective[rand() % adjsize]), " ");
    strcat(strcat(sentence, noun[rand() % nounsize]), " ");
    strcat(strcat(sentence, verb[rand() % verbsize]), " ");
    strcat(strcat(sentence, preposition[rand() % prepositionsize]), " ");
    strcat(strcat(sentence, article[rand() % articlesize]), " ");
    strcat(strcat(sentence, adjective[rand() % adjsize]), " ");
    strcat(strcat(sentence, noun[rand() % nounsize]), ".\n");


    return sentence;
}

void generateStory(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize, FILE *fptr) //write story to txt file
{

    //Generate random number from 100-500
    int numSentences = (rand() % 401) + 100;

    //Iterate through number of random sentences and write each sentence into a file
    for(int i = 0; i < numSentences; ++i)
    {
        //Generate random sentence
        char * sentence = generateSentence(noun, verb, adjective, preposition, article, nounsize, verbsize, adjsize, prepositionsize, articlesize);

        //Write random sentence into a file
        fprintf(fptr, "%s", sentence);

        //Free allocated heap space for each random sentence
        free(sentence);
    }
}



//Print random sentence to the terminal
void displaySentence(char * sentence)
{
    printf("%s", sentence);
}



//Free the allocated heap space for each character element in the 2d dynamic arrays
void cleanUp(char ** nouns, char ** verbs, char ** adjectives, char ** prepositions, char ** articles, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize)
{
    for (int i = 0; i < nounsize; ++i)
    {
        free(nouns[i]);
    }
    free(nouns);

    //Assign pointers to null after freeing to avoid segmentation faults
    nouns = NULL;

    for (int i = 0; i < verbsize; ++i)
    {
        free(verbs[i]);
    }
    free(verbs);
    verbs = NULL;

    for (int i = 0; i < adjsize; ++i)
    {
        free(adjectives[i]);
    }
    free(adjectives);
    adjectives = NULL;

    for (int i = 0; i < prepositionsize; ++i)
    {
        free(prepositions[i]);
    }
    free(prepositions);
    prepositions = NULL;

    for (int i = 0; i < articlesize; ++i)
    {
        free(articles[i]);
    }
    free(articles);
    articles = NULL;

}