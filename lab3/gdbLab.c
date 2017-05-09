/*
 * This file is meant to be used with lab3. There is an error in this file which
 * results in a segmentation fault.
 *
 * Your job is to figure out which line of code causes this segmentation fault
 * and you also need to figure out why the segmentation fault occurs.
 *
 * TODO: 1. Compile Using
 *  gcc -Wall -Wextra -Werror -Wpedantic -std=c99 -g -o gdbLab gdbLab.c -lm
 *
 * TODO: 2. Execute Using
 *  ./gdbLab
 *
 * TODO: 3. Debug Using
 *  gdb ./gdbLab
 *
 * TIPS
 * -> Run the executable in GDB. It should tell you where the segmentation fault
 *    is occuring. Boom, thats one thing out of the way.
 *
 * -> Now is the hard part. Why is is occuring? This is where your brain might
 *    hurt. You will need to step through each instruction one at a time and
 *    validate the values held in the variables. Read the tutorial properly.
 *
 * -> Read all the comments in this file. The answer lies in them. It is an
 *    obvious answer as soon as you spot the problem.
 *
 * NOTE: In case you want to experiment with this source code, copy it
 *       into a new file and then experiment with it.
 */
# include <stdio.h>
# include <math.h>
# include <stdlib.h> // added this to fix the segfault (needed for malloc and free)
# define FIRST_X         (3.0f)
# define FIRST_Y         (5.0f)
# define SECOND_X        (4.0f)
# define SECOND_Y        (7.0f)

/* --- DO NOT CHANGE THIS CODE. THIS IS NOT WHAT SEG FAULTS THE CODE --- */
/* YOU MAY IGNORE WHAT IT DOES. BUT MAYBE YOU SHOULDN'T. */
# ifdef __clang__
# pragma clang diagnostic ignored "-Wreturn-stack-address"
# else
# ifdef __GNUC__
# pragma GCC diagnostic ignored "-Wreturn-local-addr"
# endif
# endif

# ifdef __linux__
int correctOS = 1;
# else
int correctOS = 0;
# endif
/* --- END --- */

struct cartesianCoordinate
{
    /* These two variables represent a point on the cartesian plane. */
    float x;
    float y;
};

/**
 * This function creates a new structure which can hold two integers. These two
 * integers collectively represent a point on the cartesian plane.
 *
 * @param x The value of the x axis.
 * @param y The value of the y axis.
 * @return Pointer to a structure of type cartesianCoordinate.
 */
struct cartesianCoordinate *makePoint(float x, float y)
{
    /* We make space to hold two points */
    struct cartesianCoordinate *thisCoordinate = (struct cartesianCoordinate *) malloc(sizeof(struct cartesianCoordinate));

    /* We set the respective values */
    thisCoordinate->x = x;
    thisCoordinate->y = y;

    /*
     * We return the pointer to our new coordinate structure. We need to use the
     * no additional operator here because we are returning the value of variable.
     * We need to do this because we are returning a pointer, and a pointer itself
     * holds an address in memory (in this case, on the heap, allocated by malloc).
     */
    return thisCoordinate;
}

/**
 * This function is used to find out the distance between two points on the
 * cartesian plane. Notice how I broke the line in my function because my
 * arguments were too long.  This helps make the code more readable.
 *
 * Recall that the distance formula is:
 *  dist = sqrt((x2-x1)^2 + (y2-y1)^2)
 *
 * @param firstPoint The first point.
 * @param secondPoint The second point.
 * @return The distance between the two points.
 */
float findDistance(struct cartesianCoordinate *firstPoint,
                   struct cartesianCoordinate *secondPoint)
{
    float distance;
    float xDistance;
    float yDistance;

    /* Get x part */
    xDistance = secondPoint->x - firstPoint->x;
    xDistance = xDistance * xDistance;

    /* Get y part */
    yDistance = secondPoint->y - firstPoint->y;
    yDistance = yDistance * yDistance;

    /* Combine them together */
    distance = xDistance + yDistance;
    distance = sqrt(distance);

    return distance;
}

/**
 * The main function simply constructs two cartesian points and finds the
 * distance between them.
 *
 * @return 0
 */
int main(void)
{
    float distance;
    struct cartesianCoordinate *firstPoint;
    struct cartesianCoordinate *secondPoint;

    /* --- DO NOT CHANGE --- */
    if (!correctOS)
    {
        printf("Not using Linux. Please switch to the timeshare\n");
        return 1;
    }
    /* --- END --- */

    /* Get first point */
    firstPoint = makePoint(FIRST_X, FIRST_Y);

    /* Get second point */
    secondPoint = makePoint(SECOND_X, SECOND_Y);

    /* Get the distance and print it */
    distance = findDistance(firstPoint, secondPoint);
    printf("Distance Between Points: %.2f\n", distance);

    free(firstPoint);
    free(secondPoint);
    firstPoint = NULL;
    secondPoint = NULL;
    return 0;
}

