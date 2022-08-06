#define _CRT_SECURE_NO_WARNINGS // Needed to use scanf with no compile errors 
								// in Visual Studios
#define _USE_MATH_DEFINES // Used to retieve the constants from math.h

#include <stdio.h>
#include <math.h> // used to get euler's number and sqrt() function
#include <time.h> // used to measure function performance in terms of time

/* constants */
#define EXIT_SUCCESS 0
#define TRUE 1
#define FALSE 0
#define MAXIMUM_INVALID_INPUT 0

/* function prototypes */
double validateUserInput();
long double computeEulersNumber();
long double computeSquareRoot(double);
unsigned long long int factorial(unsigned long long int);
void printOutput(double, long double, long long, long double, long long);

/*------------------------------------------------------------------------------
|  function: main()
|
|  Purpose: Entry point of program execution
|
|  @return  0  -- flag indicating program executed successfully
------------------------------------------------------------------------------*/
int main() {
	clock_t start;
	clock_t stop;
	double numberToSquare = validateUserInput();
	start = clock();
	long double squareRoot = computeSquareRoot(numberToSquare);
	stop = clock();
	long double sqrtExecutionTime = stop - start;
	start = clock();
	long double eulersNumber = computeEulersNumber();
	stop = clock();
	long double eulerExecutionTime = stop - start;
	printOutput(numberToSquare, squareRoot, sqrtExecutionTime, eulersNumber, 
		eulerExecutionTime);
	return EXIT_SUCCESS;
} // end main function


/*------------------------------------------------------------------------------
|  function: validateUserInput()
|
|  Purpose: Assures the user enters a positive real number 
|  @return  the number entered by the user which we will use to square root
------------------------------------------------------------------------------*/
double validateUserInput() {
	int validInput = FALSE;
	double numberToSquare;
	char nextInBuffer;
	do {
		printf(" Please enter positive number to square: ");
		validInput = scanf("%lf", &numberToSquare);
		nextInBuffer = getchar();
		while (nextInBuffer != '\n') {
			validInput = FALSE;
			nextInBuffer = getchar();
		} // end while-loop
	} while (validInput == FALSE || numberToSquare <= MAXIMUM_INVALID_INPUT);
	printf("\n");
	return numberToSquare;
} // end validateUserInput function



/*------------------------------------------------------------------------------
|  function: factorial(num)
|
|  Purpose: Computes the factorial of a given number
|			More information regarding this operation can be foung at the link
|			here: https://en.wikipedia.org/wiki/Factorial
|			The base case is that if num is less than or equal to 1 we return 1.
|  @param	num - a number to perform the factorial operation on
|  @return  the result of performing a factorial operation on a given number
------------------------------------------------------------------------------*/
unsigned long long int factorial(unsigned long long int num) {
	const int PREVIOUS = 1;
	unsigned long long int temp;
	if (num <= 1) {
		return 1;
	}
	temp = num * factorial(num - PREVIOUS);
	return temp;
} // end factorial function

/*------------------------------------------------------------------------------
|  function: computeEulersNumber()
|
|  Purpose: Computes euler's number by using the sum of an infinite series found
|			here: https://en.wikipedia.org/wiki/E_(mathematical_constant)
|  @return  the computed value for euler's number with 16 decimal places of 
|			precision
------------------------------------------------------------------------------*/
long double computeEulersNumber() {
	const double SIXTEEN_DIG_PRECISION = 1e-17;
	const int NEXT = 1;
	long double current = 1;
	long double previous = 0;
	long double epsilon = current - previous;
	int iterations = 1;
	long double factorial;
	while (epsilon > SIXTEEN_DIG_PRECISION) {
		previous = current;
		factorial = 1;
		int index;
		for (index = 1; index <= iterations; index++) {
			factorial *= index;
		} // end for-loop
		current = current + NEXT / factorial;
		epsilon = current - previous;
		iterations++;
	} // end while-loop
	return current;
} // end computeEulersNumber function

/*------------------------------------------------------------------------------
|  function: computeSquareRoot(numberToSquare)
|
|  Purpose: Computes the square root of a number by using the sum of an infinite
|			series (Babylonian method) found here: 
|			https://en.wikipedia.org/wiki/Methods_of_computing_square_roots 
|  @param   numberToSquare - the number entered by the user to obtain its square
|			root
|  @return  the computed square root with 16 decimal places of precision
------------------------------------------------------------------------------*/
long double computeSquareRoot(double numberToSquare) {
	const double SIXTEEN_DIG_PRECISION = 1e-17;
	const int HALF = 2;
	long double squareGuess = numberToSquare;
	int iterations = 0;
	while (squareGuess - numberToSquare / squareGuess > SIXTEEN_DIG_PRECISION) {
		iterations++;
		squareGuess = (squareGuess + numberToSquare / squareGuess) / HALF;
	} // end while-loop
	return squareGuess;
} // end computeSquareRoot function

/*------------------------------------------------------------------------------
|  function: printOutput(numberToSquare, mySquareRoot, sqrtExecutionTime
|			 myEulersNumber, eurlersExecutionTime)
|
|  Purpose: Prints the output of all the computations we've gathered plus their
|			execution time.
|  @param   numberToSquare - number entered by the user
|  @param   mySquareRoot - my computation of the square of the number entered by
|			user
|  @param   sqrtExecutionTime - the execution time in milliseconds it took me to
|			compute the square root
|  @param   myEulersNumber - my computation of euler's number
|  @param   eurlersExecutionTime - the execution time in milliseconds it took me
|			to compute euler's number
------------------------------------------------------------------------------*/
void printOutput(double numberToSquare, long double mySquareRoot, 
	long long sqrtExecutionTime, long double myEulersNumber,
	long long eurlersExecutionTime) {
	long double mathHsquareRoot = sqrt(numberToSquare);
	long double mathHeulersNumber = M_E;
	printf(" Math.h square root computation: %39.16Lf", mathHsquareRoot);
	printf("\n My square root computation: %43.16Lf", mySquareRoot);
	printf("\n Execution time of my square root computation: %8lli milliseconds", 
		sqrtExecutionTime);
	printf("\n");
	printf("\n Math.h euler's number computation: %36.16Lf", mathHeulersNumber);
	printf("\n My euler's number computation: %40.16Lf", myEulersNumber);
	printf("\n Execution time of my eulers number computation: %6lli milliseconds", 
		eurlersExecutionTime);
	printf("\n");
} // end printOutput function